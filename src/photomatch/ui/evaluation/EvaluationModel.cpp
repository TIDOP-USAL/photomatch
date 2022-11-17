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


#include "EvaluationModel.h"

#include <tidop/core/messages.h>
#include <tidop/math/statistics.h>
#include <tidop/geometry/algorithms/distance.h>
#include <tidop/geometry/entities/segment.h>

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
#include <QPainter>

#include <fstream>

namespace photomatch
{

EvaluationModelImp::EvaluationModelImp(photomatch::ProjectModel *projectModel)
  : EvaluationModel(),
    mProjectModel(projectModel),
    mMatrix("Fundamental Matrix")
{
  init();
}

EvaluationModelImp::~EvaluationModelImp()
{

}

std::vector<QString> EvaluationModelImp::images() const
{
  std::vector<QString> images;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    images.push_back((*it)->path());
  }
  return images;
}

std::vector<QString> EvaluationModelImp::imagePairs(const QString &imageName) const
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

std::vector<QString> EvaluationModelImp::sessionNames() const
{
  std::vector<QString> session_names;

  for (auto it = mProjectModel->sessionBegin(); it != mProjectModel->sessionEnd(); it++){
    if(!(*it)->matches().empty()){
      session_names.push_back((*it)->name());
    }
  }

  return session_names;
}

std::vector<std::tuple<QString, QString, QString> > EvaluationModelImp::sessions() const
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

Report EvaluationModelImp::computeErrors(const QString &session,
                                         const QString &imgLeft,
                                         const QString &imgRight,
                                         double errorThreshold) const
{
  Report report{};

  try {
	  
    QString imgPath1 = mProjectModel->findImageByName(imgLeft)->path();
    QString imgPath2 = mProjectModel->findImageByName(imgRight)->path();

    if (QFileInfo(imgPath1).exists() == false || QFileInfo(imgPath2).exists() == false)
      return report;

    cv::Mat homography;
    cv::Mat fundamental_matrix;
    {
      std::vector<cv::Point2f> pts_query;
      std::vector<cv::Point2f> pts_train;

      loadGroundTruth(mProjectModel->groundTruth(), imgLeft, imgRight, pts_query, pts_train);

      std::vector<double> err;

      if (mMatrix.compare("Homography") == 0) {

        homography = computeHomography(pts_query, pts_train);
        err = computeHomographyError(pts_query, pts_train, homography);

      } else {

        fundamental_matrix = computeFundamentalMatrix(pts_query, pts_train);

        if (!fundamental_matrix.empty()) {
          err = computeFundamentalMatrixError(pts_query, pts_train, fundamental_matrix);
        }
      }

      auto minmax = std::minmax_element(err.begin(), err.end());
      double err_mean = tl::math::mean(err.begin(), err.end());

      msgInfo("Error in Ground Truth points");
      msgInfo("Mean error: %lf", err_mean);
      msgInfo("Max error: %lf", *minmax.second);

    }

    //cv::Mat img1 = cv::imread(imgPath1.toStdString().c_str());
    //cv::Mat img2 = cv::imread(imgPath2.toStdString().c_str());

    if (std::shared_ptr<Session> _session = mProjectModel->findSession(session)){
      std::vector<std::pair<QString, QString>> matches = _session->matches(imgLeft);

      cv::Mat img1 = cv::imread(imgPath1.toStdString().c_str(), cv::IMREAD_IGNORE_ORIENTATION | cv::IMREAD_COLOR);
      cv::Mat img2 = cv::imread(imgPath2.toStdString().c_str(), cv::IMREAD_IGNORE_ORIENTATION | cv::IMREAD_COLOR);
      cv::Mat pair = cv::Mat::zeros(std::max(img1.rows, img2.rows), img1.cols + img2.cols, CV_8UC3);
      img1.copyTo(pair(cv::Rect(0, 0, img1.cols, img1.rows)));
      img2.copyTo(pair(cv::Rect(img1.cols, 0, img2.cols, img2.rows)));

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
            //std::vector<cv::Point2f> pts_query;
            //std::vector<cv::Point2f> pts_train;


            std::vector<cv::Point2f> query_points(goodMatches.size());
            std::vector<cv::Point2f> train_points(goodMatches.size());

            for (size_t i = 0; i < goodMatches.size(); i++) {

              size_t query_id = (idx == 0) ? static_cast<size_t>(goodMatches[i].queryIdx) : static_cast<size_t>(goodMatches[i].trainIdx);
              size_t train_id = (idx == 0) ? static_cast<size_t>(goodMatches[i].trainIdx) : static_cast<size_t>(goodMatches[i].queryIdx);

              query_points[i] = keyPoints1[query_id].pt;
              train_points[i] = keyPoints2[train_id].pt;

            }

            //for (size_t i = 0; i < wrongMatches.size(); i++){
            //  size_t query_id = (idx == 0) ? static_cast<size_t>(wrongMatches[i].queryIdx) : static_cast<size_t>(wrongMatches[i].trainIdx);
            //  size_t train_id = (idx == 0) ? static_cast<size_t>(wrongMatches[i].trainIdx) : static_cast<size_t>(wrongMatches[i].queryIdx);
            //  query_points.push_back(keyPoints1[query_id].pt);
            //  train_points.push_back(keyPoints2[train_id].pt);
            //}

            std::vector<double> err(query_points.size());

            if (mMatrix.compare("Homography") == 0){

              cv::Mat H = cv::findHomography(query_points, train_points);

              //for (size_t i = 0; i < wrongMatches.size(); i++){
              //  std::vector<cv::KeyPoint> key1;
              //  std::vector<cv::KeyPoint> key2;
              //  size_t query_id = (idx == 0) ? static_cast<size_t>(wrongMatches[i].queryIdx) : static_cast<size_t>(wrongMatches[i].trainIdx);
              //  size_t train_id = (idx == 0) ? static_cast<size_t>(wrongMatches[i].trainIdx) : static_cast<size_t>(wrongMatches[i].queryIdx);
              //  key1.push_back(keyPoints1[query_id]);
              //  key2.push_back(keyPoints2[train_id]);

              //  float repeteability = 0;
              //  int corres = 0;
              //  cv::evaluateFeatureDetector(img1, img2, homography, &key1, &key2, repeteability, corres);

              //  int classification = corres == -1 ? 0 : 1;
              //  std::pair<double, int> pair = std::make_pair(wrongMatches[i].distance, classification);
              //  classified_matches.push_back(pair);
              //}

            } else {

              ////std::vector<cv::Vec3f> lines1;
              //std::vector<cv::Vec3f> lines2;
              ////cv::computeCorrespondEpilines(query_points, 1, fundamental_matrix, lines1);
              //cv::computeCorrespondEpilines(train_points, 2, fundamental_matrix, lines2);

              //for (size_t i = 0; i < train_points.size(); i++) {
              //  err[i] = distancePointLine(query_points[i], lines2[i]);
              //}
              if (!fundamental_matrix.empty()) {
                err = computeFundamentalMatrixError(query_points, train_points, fundamental_matrix);
              }
            }

            auto min_max = std::minmax_element(err.begin(), err.end());
            double err_mean = tl::math::mean(err.begin(), err.end());

            int pts_below_5_px{};
            int pts_below_10_px{};
            int pts_below_20_px{};
            int pts_below_30_px{};

            /// Pintado de los matches
            
            cv::Scalar color;
            cv::Point2f dx(img1.cols, 0);

            for (size_t i = 0; i < err.size(); i++) {
              if (err[i] <= 5) {
                pts_below_5_px++;
              } else if (err[i] <= 10) {
                pts_below_10_px++;
              } else if (err[i] <= 20) {
                pts_below_20_px++;
              } else if (err[i] <= 30) {
                pts_below_30_px++;
              }

              if (err[i] <= errorThreshold) {
                color = cv::Scalar(0, 255, 0);
              } else {
                color = cv::Scalar(0, 0, 255);
              }

              cv::Point2f pt2 = train_points[i] + dx;
              cv::line(pair, query_points[i], pt2, color, 1);
              cv::circle(pair, query_points[i], 5, cv::Scalar(255,0,0), -1);
              cv::circle(pair, pt2, 5, cv::Scalar(255, 0, 0), -1);
            }

            pts_below_10_px += pts_below_5_px;
            pts_below_20_px += pts_below_10_px;
            pts_below_30_px += pts_below_20_px;

            report.total_matches = static_cast<int>(query_points.size());
            report.average_error = err_mean;
            report.max_error = *min_max.second;
            report.pts_below_5_px = pts_below_5_px;
            report.pts_below_10_px = pts_below_10_px;
            report.pts_below_20_px = pts_below_20_px;
            report.pts_below_30_px = pts_below_30_px;

            break;
          }
        }
      }

      report.image = std::move(cvMatToQImage(pair));

    }
  } catch (...) {
    TL_THROW_EXCEPTION_WITH_NESTED("Exception caught in error computation");
  }

  return report;
}
cv::Mat EvaluationModelImp::computeFundamentalMatrix(std::vector<cv::Point2f> &ptsQuery,
                                                      std::vector<cv::Point2f> &ptsTrain) const
{
  TL_ASSERT(ptsQuery.size() > 3, "Insufficient number of points to calculate the fundamental matrix");

  return cv::findFundamentalMat(ptsQuery, ptsTrain);
}

std::vector<double> EvaluationModelImp::computeFundamentalMatrixError(std::vector<cv::Point2f> &ptsQuery,
                                                                      std::vector<cv::Point2f> &ptsTrain,
                                                                      cv::Mat &fundamentalMatrix) const
{
  std::vector<double> errors(ptsQuery.size());
  std::vector<cv::Vec3f> lines2;

  try {

    cv::computeCorrespondEpilines(ptsTrain, 2, fundamentalMatrix, lines2);

    for (size_t i = 0; i < ptsQuery.size(); i++) {

      errors[i] = distancePointLine(ptsQuery[i], lines2[i]);

    }

  } catch (...) {
    TL_THROW_EXCEPTION_WITH_NESTED("");
  }


  return errors;
}

cv::Mat EvaluationModelImp::computeHomography(std::vector<cv::Point2f> &ptsQuery, 
                                              std::vector<cv::Point2f> &ptsTrain) const
{
  TL_ASSERT(ptsQuery.size() > 3, "Insufficient number of points to calculate the homography");

  return cv::findHomography(ptsQuery, ptsTrain);
}

std::vector<double> EvaluationModelImp::computeHomographyError(std::vector<cv::Point2f> &ptsQuery, 
                                                               std::vector<cv::Point2f> &ptsTrain, 
                                                               cv::Mat &homography) const
{
  std::vector<double> errors(ptsQuery.size());

  std::vector<cv::Point2f> transform_points(ptsQuery.size());
  cv::perspectiveTransform(ptsQuery, transform_points, homography);

  for (size_t i = 0; i < ptsQuery.size(); i++) {
    ptsTrain[i] -= transform_points[i];
    errors[i] = sqrt(ptsTrain[i].x * ptsTrain[i].x + ptsTrain[i].y * ptsTrain[i].y);
    //err_mean += err[i];
  }

  return errors;
}



void EvaluationModelImp::loadGroundTruth(const QString &groundTruthFile,
                                         const QString &imgLeft,
                                         const QString &imgRight,
                                         std::vector<cv::Point2f> &ptsQuery,
                                         std::vector<cv::Point2f> &ptsTrain) const
{
  std::string line;

  std::ifstream ifs(groundTruthFile.toStdString(), std::ifstream::in);
  if (ifs.is_open()) {

    while (std::getline(ifs, line)) {

      QStringList list = QString(line.c_str()).split(";");
      if (list[0].compare(imgLeft) == 0 && list[1].compare(imgRight) == 0) {
        cv::Point2f pt_query(list[2].toFloat(), list[3].toFloat());
        cv::Point2f pt_train(list[4].toFloat(), list[5].toFloat());
        ptsQuery.push_back(pt_query);
        ptsTrain.push_back(pt_train);
      } else if (list[0].compare(imgRight) == 0 && list[1].compare(imgLeft) == 0) {
        cv::Point2f pt_query(list[4].toFloat(), list[5].toFloat());
        cv::Point2f pt_train(list[2].toFloat(), list[3].toFloat());
        ptsQuery.push_back(pt_query);
        ptsTrain.push_back(pt_train);
      }

    }

    ifs.close();

  }
}

QString EvaluationModelImp::adjustMatrix() const
{
  return mMatrix;
}

void EvaluationModelImp::setAdjustMatrix(const QString &adjustMatrix)
{
  mMatrix = adjustMatrix;
}

void EvaluationModelImp::init()
{
}



} // namespace photomatch



