#include "CurvesViewerModel.h"

#include <tidop/core/messages.h>

#include "fme/ui/ProjectModel.h"
#include "fme/core/utils.h"
#include "fme/core/features/evaluation.h"

#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgcodecs.hpp>

#include <QFileInfo>

namespace fme
{

CurvesViewerModel::CurvesViewerModel(fme::IProjectModel *projectModel)
  : ICurvesViewerModel(),
    mProjectModel(projectModel)
{
  init();
}

CurvesViewerModel::~CurvesViewerModel()
{

}

std::vector<QString> CurvesViewerModel::images() const
{
  std::vector<QString> images;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    images.push_back((*it)->path());
  }
  return images;
}

std::vector<QString> CurvesViewerModel::imagePairs(const QString &imageName) const
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

std::vector<std::tuple<QString, QString, QString> > CurvesViewerModel::sessions() const
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

void CurvesViewerModel::init()
{
}




ROCCurvesViewerModel::ROCCurvesViewerModel(IProjectModel *projectModel)
  : CurvesViewerModel(projectModel)
{

}

ROCCurvesViewerModel::~ROCCurvesViewerModel()
{

}

std::vector<QPointF> ROCCurvesViewerModel::computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight) const
{
  std::vector<QPointF> curve;

  msgInfo("Compute Curve for session %s", session.toStdString().c_str());

  QString imgPath1 = mProjectModel->findImageByName(imgLeft)->path();
  QString imgPath2 = mProjectModel->findImageByName(imgRight)->path();

  if (QFileInfo(imgPath1).exists() == false || QFileInfo(imgPath2).exists() == false)
    return curve;

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

  cv::Mat H = cv::findHomography(pts_query, pts_train);

  cv::Mat img1 = cv::imread(imgPath1.toStdString().c_str());
  cv::Mat img2 = cv::imread(imgPath2.toStdString().c_str());

  if (std::shared_ptr<Session> _session = mProjectModel->findSession(session)){
    std::vector<std::pair<QString, QString>> matches = _session->matches(imgLeft);
    if (!matches.empty()){
      for (auto &m : matches){
        if (m.first.compare(imgRight) == 0){

          std::vector<cv::DMatch> goodMatches;
          std::vector<cv::DMatch> wrongMatches;
          matchesRead(m.second, &goodMatches, &wrongMatches);

          std::vector<cv::KeyPoint> keyPoints1, keyPoints2;
          cv::Mat descriptors;
          featuresRead(_session->features(imgLeft), keyPoints1, descriptors);
          featuresRead(_session->features(imgRight), keyPoints2, descriptors);

          std::vector<std::pair<double, int>> matchClassification;


          for (size_t i = 0; i < goodMatches.size(); i++){
            std::vector<cv::KeyPoint> key1;
            std::vector<cv::KeyPoint> key2;
            key1.push_back(keyPoints1[static_cast<size_t>(goodMatches[i].queryIdx)]);
            key2.push_back(keyPoints2[static_cast<size_t>(goodMatches[i].trainIdx)]);

            float repeteability = 0;
            int corres = 0;
            cv::evaluateFeatureDetector(img1, img2, H, &key1, &key2, repeteability, corres);

            int classification = corres == -1 ? 0 : 1;
            std::pair<double, int> pair = std::make_pair(goodMatches[i].distance, classification);
            matchClassification.push_back(pair);
          }


          for (size_t i = 0; i < wrongMatches.size(); i++){

            std::vector<cv::KeyPoint> key1;
            std::vector<cv::KeyPoint> key2;
            key1.push_back(keyPoints1[static_cast<size_t>(wrongMatches[i].queryIdx)]);
            key2.push_back(keyPoints2[static_cast<size_t>(wrongMatches[i].trainIdx)]);
            
            float repeteability = 0;
            int corres = 0;
            cv::evaluateFeatureDetector(img1, img2, H, &key1, &key2, repeteability, corres);

            int classification = corres == -1 ? 0 : 1;
            std::pair<double, int> pair = std::make_pair(wrongMatches[i].distance, classification);
            matchClassification.push_back(pair);
          }


          ROCCurve rocCurve(matchClassification);
          curve = rocCurve.compute();

          break;
        }
      }
    }
  }
  return curve;
}


PRCurvesViewerModel::PRCurvesViewerModel(IProjectModel *projectModel)
  : CurvesViewerModel(projectModel)
{

}

PRCurvesViewerModel::~PRCurvesViewerModel()
{

}

std::vector<QPointF> PRCurvesViewerModel::computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight) const
{
  std::vector<QPointF> curve;

  msgInfo("Compute Curve for session %s", session.toStdString().c_str());

  QString imgPath1 = mProjectModel->findImageByName(imgLeft)->path();
  QString imgPath2 = mProjectModel->findImageByName(imgRight)->path();

  if (QFileInfo(imgPath1).exists() == false || QFileInfo(imgPath2).exists() == false)
    return curve;

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

  cv::Mat H = cv::findHomography(pts_query, pts_train);

  cv::Mat img1 = cv::imread(imgPath1.toStdString().c_str());
  cv::Mat img2 = cv::imread(imgPath2.toStdString().c_str());

  if (std::shared_ptr<Session> _session = mProjectModel->findSession(session)){
    std::vector<std::pair<QString, QString>> matches = _session->matches(imgLeft);
    if (!matches.empty()){
      for (auto &m : matches){
        if (m.first.compare(imgRight) == 0) {

          std::vector<cv::DMatch> goodMatches;
          std::vector<cv::DMatch> wrongMatches;
          matchesRead(m.second, &goodMatches, &wrongMatches);

          std::vector<cv::KeyPoint> keyPoints1, keyPoints2;
          cv::Mat descriptors;
          featuresRead(_session->features(imgLeft), keyPoints1, descriptors);
          featuresRead(_session->features(imgRight), keyPoints2, descriptors);

          std::vector<std::pair<double, int>> matchClassification;

          for (size_t i = 0; i < goodMatches.size(); i++){
            std::vector<cv::KeyPoint> key1;
            std::vector<cv::KeyPoint> key2;
            key1.push_back(keyPoints1[static_cast<size_t>(goodMatches[i].queryIdx)]);
            key2.push_back(keyPoints2[static_cast<size_t>(goodMatches[i].trainIdx)]);

            float repeteability = 0;
            int corres = 0;
            cv::evaluateFeatureDetector(img1, img2, H, &key1, &key2, repeteability, corres);

            int classification = corres == -1 ? 0 : 1;
            std::pair<double, int> pair = std::make_pair(goodMatches[i].distance, classification);
            matchClassification.push_back(pair);
          }

          for (size_t i = 0; i < wrongMatches.size(); i++){

            std::vector<cv::KeyPoint> key1;
            std::vector<cv::KeyPoint> key2;
            key1.push_back(keyPoints1[static_cast<size_t>(wrongMatches[i].queryIdx)]);
            key2.push_back(keyPoints2[static_cast<size_t>(wrongMatches[i].trainIdx)]);
           
            float repeteability = 0;
            int corres = 0;
            cv::evaluateFeatureDetector(img1, img2, H, &key1, &key2, repeteability, corres);

            int classification = corres == -1 ? 0 : 1;
            std::pair<double, int> pair = std::make_pair(wrongMatches[i].distance, classification);
            matchClassification.push_back(pair);
          }

          PRCurve prCurve(matchClassification);
          curve = prCurve.compute();

          break;
        }
      }
    }
  }
  return curve;
}


DETCurvesViewerModel::DETCurvesViewerModel(IProjectModel *projectModel)
  : CurvesViewerModel(projectModel)
{

}

DETCurvesViewerModel::~DETCurvesViewerModel()
{

}

std::vector<QPointF> DETCurvesViewerModel::computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight) const
{
  std::vector<QPointF> curve;

  msgInfo("Compute Curve for session %s", session.toStdString().c_str());

  QString imgPath1 = mProjectModel->findImageByName(imgLeft)->path();
  QString imgPath2 = mProjectModel->findImageByName(imgRight)->path();

  if (QFileInfo(imgPath1).exists() == false || QFileInfo(imgPath2).exists() == false)
    return curve;

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

  cv::Mat H = cv::findHomography(pts_query, pts_train);

  cv::Mat img1 = cv::imread(imgPath1.toStdString().c_str());
  cv::Mat img2 = cv::imread(imgPath2.toStdString().c_str());

  if (std::shared_ptr<Session> _session = mProjectModel->findSession(session)){
    std::vector<std::pair<QString, QString>> matches = _session->matches(imgLeft);
    if (!matches.empty()){
      for (auto &m : matches){
        if (m.first.compare(imgRight) == 0) {

          std::vector<cv::DMatch> goodMatches;
          std::vector<cv::DMatch> wrongMatches;
          matchesRead(m.second, &goodMatches, &wrongMatches);

          std::vector<cv::KeyPoint> keyPoints1, keyPoints2;
          cv::Mat descriptors;
          featuresRead(_session->features(imgLeft), keyPoints1, descriptors);
          featuresRead(_session->features(imgRight), keyPoints2, descriptors);

          std::vector<std::pair<double, int>> matchClassification;

          for (size_t i = 0; i < goodMatches.size(); i++){
            std::vector<cv::KeyPoint> key1;
            std::vector<cv::KeyPoint> key2;
            key1.push_back(keyPoints1[static_cast<size_t>(goodMatches[i].queryIdx)]);
            key2.push_back(keyPoints2[static_cast<size_t>(goodMatches[i].trainIdx)]);

            float repeteability = 0;
            int corres = 0;
            cv::evaluateFeatureDetector(img1, img2, H, &key1, &key2, repeteability, corres);

            int classification = corres == -1 ? 0 : 1;
            std::pair<double, int> pair = std::make_pair(goodMatches[i].distance, classification);
            matchClassification.push_back(pair);
          }

          for (size_t i = 0; i < wrongMatches.size(); i++){

            std::vector<cv::KeyPoint> key1;
            std::vector<cv::KeyPoint> key2;
            key1.push_back(keyPoints1[static_cast<size_t>(wrongMatches[i].queryIdx)]);
            key2.push_back(keyPoints2[static_cast<size_t>(wrongMatches[i].trainIdx)]);
           
            float repeteability = 0;
            int corres = 0;
            cv::evaluateFeatureDetector(img1, img2, H, &key1, &key2, repeteability, corres);

            int classification = corres == -1 ? 0 : 1;
            std::pair<double, int> pair = std::make_pair(wrongMatches[i].distance, classification);
            matchClassification.push_back(pair);
          }

          DETCurve detCurve(matchClassification);
          curve = detCurve.compute();

          break;
        }
      }
    }
  }
  return curve;
}


} // namespace fme



