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


#include "CurvesViewerModel.h"

#include <tidop/core/messages.h>

#include "photomatch/core/features/featio.h"
#include "photomatch/core/features/matchio.h"
#include "photomatch/core/utils.h"
#include "photomatch/core/features/evaluation.h"
#include "photomatch/core/features/groundtruth.h"
#include "photomatch/ui/ProjectModel.h"

#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>

#include <QFileInfo>

namespace photomatch
{

CurvesViewerModelImp::CurvesViewerModelImp(photomatch::ProjectModel *projectModel)
  : CurvesViewerModel(),
    mProjectModel(projectModel)
{
  init();
}

CurvesViewerModelImp::~CurvesViewerModelImp()
{

}

std::vector<QString> CurvesViewerModelImp::images() const
{
  std::vector<QString> images;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    images.push_back((*it)->path());
  }
  return images;
}

std::vector<QString> CurvesViewerModelImp::imagePairs(const QString &imageName) const
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

std::vector<QString> CurvesViewerModelImp::sessionNames() const
{
  std::vector<QString> session_names;

  for (auto it = mProjectModel->sessionBegin(); it != mProjectModel->sessionEnd(); it++){
    if(!(*it)->matches().empty()){
      session_names.push_back((*it)->name());
    }
  }

  return session_names;
}

std::vector<std::tuple<QString, QString, QString> > CurvesViewerModelImp::sessions() const
{
  std::vector<std::tuple<QString, QString, QString>> sessions;

  for (auto it = mProjectModel->sessionBegin(); it != mProjectModel->sessionEnd(); it++){
    if(!(*it)->matches().empty()){
      QString sessionName = (*it)->name();
      QString detectorName = (*it)->detector()->name();
      QString descriptorName = (*it)->descriptor()->name();
      sessions.push_back(std::make_tuple(sessionName, detectorName, descriptorName));
    }
  }

  return sessions;
}

std::vector<std::pair<double, int> > CurvesViewerModelImp::classifiedMatches(const QString &session,
                                                                             const QString &imgLeft,
                                                                             const QString &imgRight) const
{
  std::vector<std::pair<double, int>> classified_matches;

  try {
    QString imgPath1 = mProjectModel->findImageByName(imgLeft)->path();
    QString imgPath2 = mProjectModel->findImageByName(imgRight)->path();

    if (QFileInfo(imgPath1).exists() == false || QFileInfo(imgPath2).exists() == false)
      return classified_matches;

    QString groundTruth = mProjectModel->groundTruth();
    std::ifstream ifs(groundTruth.toStdString(), std::ifstream::in);

    std::vector<cv::Point2f> pts_query;
    std::vector<cv::Point2f> pts_train;
    std::string line;

    if (ifs.is_open()){

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

    if (pts_query.size() == 0) {
      msgWarning("Ground Truth not available for these images");
      return classified_matches;
    }

    cv::Mat homography;
    cv::Mat fundamental_matrix;
    if (0 /*bHomography*/){
      homography = cv::findHomography(pts_query, pts_train);
    } else {
      fundamental_matrix = cv::findFundamentalMat(pts_query, pts_train);
    }

    ///TODO: revisar findPair. ¿Devolver puntos homologos independientemente del orden de image1 y image2?
//    GroundTruth groundTruth(mProjectModel->groundTruth());
//    std::shared_ptr<HomologusPoints> homologusPoints = groundTruth.findPair(imgLeft, imgRight);
//    if (homologusPoints == nullptr)
//      return 0.0;

//    cv::Mat H = homologusPoints->homography();

    cv::Mat img1 = cv::imread(imgPath1.toStdString().c_str());
    cv::Mat img2 = cv::imread(imgPath2.toStdString().c_str());

    if (std::shared_ptr<Session> _session = mProjectModel->findSession(session)){
      std::vector<std::pair<QString, QString>> matches = _session->matches(imgLeft);
      if (!matches.empty()){
        for (auto &m : matches){
          if (m.first.compare(imgRight) == 0){

            ///TODO: Codigo repetido
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

            ///TODO: repetido en HomographyViewerModel
            QString nameMatchesFile = QFileInfo(m.second).baseName();
            int idx = nameMatchesFile.indexOf(imgLeft);
            std::vector<cv::Point2f> pts_query;
            std::vector<cv::Point2f> pts_train;

            if (0 /*bHomography*/){
              for (size_t i = 0; i < goodMatches.size(); i++){
                size_t query_id = (idx == 0) ? static_cast<size_t>(goodMatches[i].queryIdx) : static_cast<size_t>(goodMatches[i].trainIdx);
                size_t train_id = (idx == 0) ? static_cast<size_t>(goodMatches[i].trainIdx) : static_cast<size_t>(goodMatches[i].queryIdx);
                std::vector<cv::KeyPoint> key1;
                std::vector<cv::KeyPoint> key2;
                key1.push_back(keyPoints1[query_id]);
                key2.push_back(keyPoints2[train_id]);

                float repeteability = 0;
                int corres = 0;
                cv::evaluateFeatureDetector(img1, img2, homography, &key1, &key2, repeteability, corres);

                int classification = corres == -1 ? 0 : 1;
                std::pair<double, int> pair = std::make_pair(goodMatches[i].distance, classification);
                classified_matches.push_back(pair);
              }

              for (size_t i = 0; i < wrongMatches.size(); i++){
                std::vector<cv::KeyPoint> key1;
                std::vector<cv::KeyPoint> key2;
                size_t query_id = (idx == 0) ? static_cast<size_t>(wrongMatches[i].queryIdx) : static_cast<size_t>(wrongMatches[i].trainIdx);
                size_t train_id = (idx == 0) ? static_cast<size_t>(wrongMatches[i].trainIdx) : static_cast<size_t>(wrongMatches[i].queryIdx);
                key1.push_back(keyPoints1[query_id]);
                key2.push_back(keyPoints2[train_id]);

                float repeteability = 0;
                int corres = 0;
                cv::evaluateFeatureDetector(img1, img2, homography, &key1, &key2, repeteability, corres);

                int classification = corres == -1 ? 0 : 1;
                std::pair<double, int> pair = std::make_pair(wrongMatches[i].distance, classification);
                classified_matches.push_back(pair);
              }

            } else {

              std::vector<cv::Point2f> query_points;
              std::vector<cv::Point2f> train_points;

              for (size_t i = 0; i < goodMatches.size(); i++){
                size_t query_id = (idx == 0) ? static_cast<size_t>(goodMatches[i].queryIdx) : static_cast<size_t>(goodMatches[i].trainIdx);
                size_t train_id = (idx == 0) ? static_cast<size_t>(goodMatches[i].trainIdx) : static_cast<size_t>(goodMatches[i].queryIdx);
                query_points.push_back(keyPoints1[query_id].pt);
                train_points.push_back(keyPoints2[train_id].pt);
              }

              for (size_t i = 0; i < wrongMatches.size(); i++){
                size_t query_id = (idx == 0) ? static_cast<size_t>(wrongMatches[i].queryIdx) : static_cast<size_t>(wrongMatches[i].trainIdx);
                size_t train_id = (idx == 0) ? static_cast<size_t>(wrongMatches[i].trainIdx) : static_cast<size_t>(wrongMatches[i].queryIdx);
                query_points.push_back(keyPoints1[query_id].pt);
                train_points.push_back(keyPoints2[train_id].pt);
              }

              std::vector<cv::Vec3f> lines1;
              std::vector<cv::Vec3f> lines2;
              cv::computeCorrespondEpilines(query_points, 1, fundamental_matrix, lines1);
              cv::computeCorrespondEpilines(train_points, 2, fundamental_matrix, lines2);

              float inlierDistance = 1.f;

              size_t i = 0;
              for (; i < goodMatches.size(); i++){
                if(distancePointLine(train_points[i], lines1[i]) < inlierDistance &&
                  distancePointLine(query_points[i], lines2[i]) < inlierDistance) {
                  std::pair<double, int> pair = std::make_pair(goodMatches[i].distance, 1);
                  classified_matches.push_back(pair);
                } else {
                  std::pair<double, int> pair = std::make_pair(goodMatches[i].distance, 0);
                  classified_matches.push_back(pair);
                }
              }

              for (; i < wrongMatches.size(); i++){
                if(distancePointLine(train_points[i], lines1[i]) < inlierDistance &&
                  distancePointLine(query_points[i], lines2[i]) < inlierDistance) {
                  std::pair<double, int> pair = std::make_pair(wrongMatches[i].distance, 1);
                  classified_matches.push_back(pair);
                } else {
                  std::pair<double, int> pair = std::make_pair(wrongMatches[i].distance, 0);
                  classified_matches.push_back(pair);
                }
              }

            }

            break;
          }
        }
      }
    }
  } catch (cv::Exception &e) {
    msgError(e.what());
  } catch (std::exception &e) {
    msgError(e.what());
  }

  return classified_matches;
}

void CurvesViewerModelImp::init()
{
}




ROCCurvesViewerModel::ROCCurvesViewerModel(ProjectModel *projectModel)
  : CurvesViewerModelImp(projectModel)
{

}

ROCCurvesViewerModel::~ROCCurvesViewerModel()
{

}

std::vector<QPointF> ROCCurvesViewerModel::computeCurve(const QString &session,
                                                        const QString &imgLeft,
                                                        const QString &imgRight) const
{
  std::vector<QPointF> curve;
  this->computeCurve(session, imgLeft, imgRight, curve);
  return curve;
}

double ROCCurvesViewerModel::computeCurve(const QString &session,
                                          const QString &imgLeft,
                                          const QString &imgRight,
                                          std::vector<QPointF> &curve) const
{
  double auc = 0.0;
  msgInfo("Compute ROC Curve for session %s", session.toStdString().c_str());

  try {
    std::vector<std::pair<double, int>> classified_matches = classifiedMatches(session, imgLeft, imgRight);

    ROCCurve<double> rocCurve(classified_matches);
    rocCurve.compute();
    curve = rocCurve.curve();
    auc = rocCurve.auc();
  } catch (std::exception &e) {
    msgError(e.what());
  }

  return auc;
}


PRCurvesViewerModel::PRCurvesViewerModel(ProjectModel *projectModel)
  : CurvesViewerModelImp(projectModel)
{

}

PRCurvesViewerModel::~PRCurvesViewerModel()
{

}

std::vector<QPointF> PRCurvesViewerModel::computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight) const
{
  std::vector<QPointF> curve;
  this->computeCurve(session, imgLeft, imgRight, curve);
  return curve;
}

double PRCurvesViewerModel::computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight, std::vector<QPointF> &curve) const
{
  double auc = 0.0;

  msgInfo("Compute PR Curve for session %s", session.toStdString().c_str());

  std::vector<std::pair<double, int>> classified_matches = classifiedMatches(session, imgLeft, imgRight);

  PRCurve<double> prCurve(classified_matches);
  prCurve.compute();
  curve = prCurve.curve();
  auc = prCurve.auc();

  return auc;
}


DETCurvesViewerModel::DETCurvesViewerModel(ProjectModel *projectModel)
  : CurvesViewerModelImp(projectModel)
{

}

DETCurvesViewerModel::~DETCurvesViewerModel()
{

}

std::vector<QPointF> DETCurvesViewerModel::computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight) const
{
  std::vector<QPointF> curve;
  this->computeCurve(session, imgLeft, imgRight, curve);
  return curve;
}

double DETCurvesViewerModel::computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight, std::vector<QPointF> &curve) const
{
  double auc = 0.0;

  msgInfo("Compute DET Curve for session %s", session.toStdString().c_str());

  std::vector<std::pair<double, int>> classified_matches = classifiedMatches(session, imgLeft, imgRight);

  DETCurve<double> detCurve(classified_matches);
  detCurve.compute();
  curve = detCurve.curve();
  auc = detCurve.auc();

  return auc;
}


} // namespace photomatch



