/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#include "MatchViewerModel.h"

#include "photomatch/core/features/featio.h"
#include "photomatch/core/features/matchio.h"
#include "photomatch/ui/ProjectModel.h"

#include <QImageReader>
#include <QFileInfo>

namespace photomatch
{

MatchViewerModel::MatchViewerModel(IProjectModel *mProjectModel)
  : IMatchViewerModel(),
    mProjectModel(mProjectModel)
{
  init();
}

void MatchViewerModel::init()
{
  if (mProjectModel->currentSession())
    mSession = mProjectModel->currentSession()->name();
}

QString MatchViewerModel::sessionName() const
{
  return mSession;
}

void MatchViewerModel::setSessionName(const QString &session)
{
  mSession = session;
}

std::vector<QString> MatchViewerModel::images() const
{
  std::vector<QString> images;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    images.push_back((*it)->path());
  }
  return images;
}

std::vector<QString> MatchViewerModel::imagePairs(const QString &imageName) const
{
  std::vector<QString> pairs;
  if (std::shared_ptr<Session> session = mProjectModel->findSession(mSession)){
    std::vector<std::pair<QString, QString>> matches = session->matches(imageName);
    if (!matches.empty()){
      for (auto &m : matches){
        QString name = m.first;
        for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
          if ((*it)->name().compare(name) == 0){
            pairs.push_back((*it)->path());
            break;
          }
        }
      }
    }
  }

  return pairs;
}

std::vector<std::tuple<size_t, size_t, QPointF, size_t, QPointF, float>>
MatchViewerModel::loadMatches(const QString &imgName1, const QString &imgName2) const
{
  std::vector<std::tuple<size_t, size_t, QPointF, size_t, QPointF, float>> r_matches;

  if (std::shared_ptr<Session> session = mProjectModel->findSession(mSession)){

    std::unique_ptr<FeaturesReader> featuresRead = FeaturesReaderFactory::createReader(session->features(imgName1));
    featuresRead->read();
    std::vector<cv::KeyPoint> keyPoints1 = featuresRead->keyPoints();
    featuresRead = FeaturesReaderFactory::createReader(session->features(imgName2));
    featuresRead->read();
    std::vector<cv::KeyPoint> keyPoints2 = featuresRead->keyPoints();

    std::vector<std::pair<QString, QString>> matches = session->matches(imgName1);
    std::vector<cv::DMatch> match;
    if (!matches.empty()){
      for (auto &m : matches){
        if (m.first.compare(imgName2) == 0){
          std::unique_ptr<MatchesReader> matchesReader = MatchesReaderFactory::createReader(m.second);
          matchesReader->read();
          std::vector<cv::DMatch> match = matchesReader->goodMatches();
          matchesReader.reset();
          break;
        }
      }
    }

    for (size_t i = 0; i < mPassPoints.size(); i++) {

      size_t query_id = 0;
      size_t train_id = 0;
      int pt_find = 0;
      for (size_t j = 0; j < mPassPoints[i].size(); j++) {
        if (mPassPoints[i][j].first.compare(imgName1) == 0){
          query_id = static_cast<size_t>(mPassPoints[i][j].second);
          pt_find++;
        } else if (mPassPoints[i][j].first.compare(imgName2) == 0){
          train_id = static_cast<size_t>(mPassPoints[i][j].second);
          pt_find++;
        }

        if (pt_find == 2){
          QPointF pt_query(static_cast<double>(keyPoints1[query_id].pt.x),
                           static_cast<double>(keyPoints1[query_id].pt.y));
          QPointF pt_train(static_cast<double>(keyPoints2[train_id].pt.x),
                           static_cast<double>(keyPoints2[train_id].pt.y));

          float distance = -0.f;
          for (size_t k = 0; k < match.size(); k++){
            if ((static_cast<size_t>(match[k].queryIdx) == query_id && static_cast<size_t>(match[k].trainIdx) == train_id) ||
                (static_cast<size_t>(match[k].queryIdx) == train_id && static_cast<size_t>(match[k].trainIdx) == query_id)){
              distance = match[k].distance;
              break;
            }
          }

          r_matches.push_back(std::make_tuple(i, query_id, pt_query, train_id, pt_train, distance));
          break;
        }
      }

    }
  }
  return r_matches;
}

void MatchViewerModel::deleteMatch(const QString &imgName1, const QString &imgName2, int query_id, int train_id)
{
  QString imgPath1 = mProjectModel->findImageByName(imgName1)->path();
  QString imgPath2 = mProjectModel->findImageByName(imgName2)->path();

  if (QFileInfo(imgPath1).exists() == true && QFileInfo(imgPath2).exists() == true) {
    if (std::shared_ptr<Session> session = mProjectModel->findSession(mSession)){
      std::vector<std::pair<QString, QString>> matches = session->matches(imgName1);

      if (!matches.empty()){
        for (auto &m : matches){
          if (m.first.compare(imgName2) == 0){

            std::unique_ptr<MatchesReader> matchesReader = MatchesReaderFactory::createReader(m.second);
            matchesReader->read();
            std::vector<cv::DMatch> good_matches = matchesReader->goodMatches();
            std::vector<cv::DMatch> wrong_matches = matchesReader->wrongMatches();
            matchesReader.reset();

            for (size_t i = 0; i < good_matches.size(); i++){
              if (good_matches[i].queryIdx == query_id &&
                  good_matches[i].trainIdx == train_id){
                wrong_matches.push_back(good_matches[i]);
                good_matches.erase(good_matches.begin()+static_cast<long long>(i));
                break;
              }
            }

            //matchesWrite(m.second, good_matches, wrong_matches);
            std::unique_ptr<MatchesWriter> matchesWriter = MatchesWriterFactory::createWriter(m.second);
            matchesWriter->setGoodMatches(good_matches);
            matchesWriter->setWrongMatches(wrong_matches);
            matchesWriter->write();

            break;
          }
        }
      }
    }
  }
}

void MatchViewerModel::loadPassPoints()
{
  if (std::shared_ptr<Session> session = mProjectModel->findSession(mSession)){
    passPointsRead(session->passPoints(), mPassPoints);
  } else {
    mPassPoints.clear();
  }
}

} // namespace photomatch
