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


#include "RepeatabilityModel.h"

#include <tidop/core/messages.h>

#include "photomatch/ui/ProjectModel.h"
#include "photomatch/core/utils.h"
#include "photomatch/core/features/featio.h"
#include "photomatch/core/features/matchio.h"
#include "photomatch/core/features/evaluation.h"

#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>

#include <QFileInfo>

namespace photomatch
{

RepeatabilityModelImp::RepeatabilityModelImp(photomatch::ProjectModel *projectModel)
  : RepeatabilityModel(),
    mProjectModel(projectModel)
{
  init();
}

RepeatabilityModelImp::~RepeatabilityModelImp()
{

}

std::vector<QString> RepeatabilityModelImp::images() const
{
  std::vector<QString> images;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    images.push_back((*it)->path());
  }
  return images;
}

std::vector<QString> RepeatabilityModelImp::imagePairs(const QString &imageName) const
{
  std::vector<QString> pairs;
  if (std::shared_ptr<Session> session = mProjectModel->currentSession()){
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

std::vector<std::tuple<QString, QString, QString> > RepeatabilityModelImp::sessions() const
{
  std::vector<std::tuple<QString, QString, QString>> sessions;

  for (auto it = mProjectModel->sessionBegin(); it != mProjectModel->sessionEnd(); it++){
    if ((*it)->detector() && (*it)->descriptor()){
      QString sessionName = (*it)->name();
      QString detectorName = (*it)->detector()->name();
      QString descriptorName = (*it)->descriptor()->name();
      sessions.push_back(std::make_tuple(sessionName, detectorName, descriptorName));
    }
  }

  return sessions;
}

void RepeatabilityModelImp::init()
{
}

std::vector<std::tuple<QString, QString, QString, float, int>>
RepeatabilityModelImp::computeRepeatability(const QString &session) const
{

  std::vector<std::tuple<QString, QString, QString, float, int>> repeatability;

  if (std::shared_ptr<Session> _session = mProjectModel->findSession(session)){

    QString groundTruth = mProjectModel->groundTruth();

    std::vector<QString> imagesLeft = this->images();

    for (size_t i = 0; i < imagesLeft.size(); i++){

      QString imgPath1 = imagesLeft[i];
      QString imgLeft = QFileInfo(imgPath1).baseName();
      std::vector<QString> imagesRight = this->imagePairs(QFileInfo(imgPath1).baseName());
      cv::Mat img1 = cv::imread(imgPath1.toStdString().c_str());

      for (size_t j = 0; j < imagesRight.size(); j++){

        QString imgPath2 = imagesRight[j];

        if (QFileInfo(imgPath1).exists() == false || QFileInfo(imgPath2).exists() == false)
          continue;


        QString imgRight = QFileInfo(imgPath2).baseName();

        std::ifstream ifs(groundTruth.toStdString(), std::ifstream::in);

        std::vector<cv::Point2f> pts_query;
        std::vector<cv::Point2f> pts_train;


        if (ifs.is_open()){

          std::string line;

          while (std::getline(ifs, line)) {

            QStringList list = QString(line.c_str()).split(";");
            if (list[0].compare(imgLeft) == 0 && list[1].compare(imgRight) == 0){
              cv::Point2f pt_query(list[2].toFloat(), list[3].toFloat());
              cv::Point2f pt_train(list[4].toFloat(), list[5].toFloat());
              pts_query.push_back(pt_query);
              pts_train.push_back(pt_train);
            } else if (list[0].compare(imgRight) == 0 && list[1].compare(imgLeft) == 0){
              cv::Point2f pt_query(list[4].toFloat(), list[5].toFloat());
              cv::Point2f pt_train(list[2].toFloat(), list[3].toFloat());
              pts_query.push_back(pt_query);
              pts_train.push_back(pt_train);
            }

          }

          ifs.close();

        }


        if (pts_query.size() > 0 && pts_train.size() > 0 && pts_query.size() == pts_train.size()){

          cv::Mat H = cv::findHomography(pts_query, pts_train);

          std::vector<std::pair<QString, QString>> matches = _session->matches(imgLeft);

          if (!matches.empty()){
            for (auto &m : matches){
              if (m.first.compare(imgRight) == 0){

                std::unique_ptr<MatchesReader> matchesReader = MatchesReaderFactory::createReader(m.second);
                matchesReader->read();
                std::vector<cv::DMatch> goodMatches = matchesReader->goodMatches();
                std::vector<cv::DMatch> wrongMatches = matchesReader->wrongMatches();
                matchesReader.reset();

                std::unique_ptr<FeaturesReader> featuresRead = FeaturesReaderFactory::createReader(_session->features(imgLeft));
                featuresRead->read();
                std::vector<cv::KeyPoint> keyPoints1 = featuresRead->keyPoints();
                featuresRead = FeaturesReaderFactory::createReader(_session->features(imgRight));
                featuresRead->read();
                std::vector<cv::KeyPoint> keyPoints2 = featuresRead->keyPoints();

                std::vector<std::pair<double, int>> matchClassification;

                std::vector<cv::KeyPoint> key1;
                std::vector<cv::KeyPoint> key2;
                for (size_t i = 0; i < goodMatches.size(); i++){
                  key1.push_back(keyPoints1[static_cast<size_t>(goodMatches[i].queryIdx)]);
                  key2.push_back(keyPoints2[static_cast<size_t>(goodMatches[i].trainIdx)]);
                }

                for (size_t i = 0; i < wrongMatches.size(); i++){
                  key1.push_back(keyPoints1[static_cast<size_t>(wrongMatches[i].queryIdx)]);
                  key2.push_back(keyPoints2[static_cast<size_t>(wrongMatches[i].trainIdx)]);
                }

                float repeat = 0;
                int corres = 0;
                cv::Mat img2 = cv::imread(imgPath2.toStdString().c_str());
                cv::evaluateFeatureDetector(img1, img2, H, &key1, &key2, repeat, corres);
                img2.release();

                repeatability.push_back(std::make_tuple(_session->name(), imgLeft, imgRight, repeat, corres));
              }
            }
          }
        }

      }

    }
  }

  return repeatability;
}

} // namespace photomatch

