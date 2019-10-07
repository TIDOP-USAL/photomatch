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

  /// Una escala para cada imagen por si tienen tamaño diferente
  double scale1 = 1.;
  double scale2 = 1.;
  if (mProjectModel->fullImageSize() == false){
    int maxSize = mProjectModel->maxImageSize();
    QImageReader imageReader1(imgPath1);
    QSize size = imageReader1.size();
    int w = size.width();
    int h = size.height();
    if (w > h){
      scale1 = w / static_cast<double>(maxSize);
    } else {
      scale1 = h / static_cast<double>(maxSize);
    }
    if (scale1 < 1.) scale1 = 1.;

    QImageReader imageReader2(imgPath2);
    size = imageReader2.size();
    w = size.width();
    h = size.height();
    if (w > h){
      scale2 = w / static_cast<double>(maxSize);
    } else {
      scale2 = h / static_cast<double>(maxSize);
    }
    if (scale2 < 1.) scale2 = 1.;
  }


  std::vector<cv::Point2f> pts_query;
  std::vector<cv::Point2f> pts_train;
  std::string line;

  if (ifs.is_open()){

    while (std::getline(ifs, line)) {

      QStringList list = QString(line.c_str()).split(";");
      if (list[0].compare(imgLeft) == 0 && list[1].compare(imgRight) == 0){
        cv::Point2f pt_query(list[2].toFloat(), list[3].toFloat());
        cv::Point2f pt_train(list[4].toFloat(), list[5].toFloat());
        pts_query.push_back(pt_query *= scale1);
        pts_train.push_back(pt_train *= scale2);
      } else if (list[0].compare(imgRight) == 0 && list[1].compare(imgLeft) == 0){
        cv::Point2f pt_query(list[4].toFloat(), list[5].toFloat());
        cv::Point2f pt_train(list[2].toFloat(), list[3].toFloat());
        pts_query.push_back(pt_query *= scale1);
        pts_train.push_back(pt_train *= scale2);
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
          std::vector<cv::DMatch> match;
          matchesRead(m.second, match);
          std::vector<cv::KeyPoint> keyPoints1, keyPoints2;
          cv::Mat descriptors;
          featuresRead(_session->features(imgLeft), keyPoints1, descriptors);
          featuresRead(_session->features(imgRight), keyPoints2, descriptors);

          for (size_t i = 0; i < keyPoints1.size(); i++){
            keyPoints1[i].pt *= scale1;
          }
          for (size_t i = 0; i < keyPoints2.size(); i++){
            keyPoints2[i].pt *= scale2;
          }

          std::vector<uchar> inliers(match.size(), 1);

          for (size_t i = 0; i < match.size(); i++){
            std::vector<cv::KeyPoint> key1;
            std::vector<cv::KeyPoint> key2;
            key1.push_back(keyPoints1[static_cast<size_t>(match[i].queryIdx)]);
            key2.push_back(keyPoints2[static_cast<size_t>(match[i].trainIdx)]);

            float repeteability = 0;
            int corres = 0;
            cv::evaluateFeatureDetector(img1, img2, H, &key1, &key2, repeteability, corres);

            if (corres == -1) inliers[i] = 0;
          }

          computeROCCurve(match, inliers, curve);

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

  /// Una escala para cada imagen por si tienen tamaño diferente
  double scale1 = 1.;
  double scale2 = 1.;
  if (mProjectModel->fullImageSize() == false){
    int maxSize = mProjectModel->maxImageSize();
    QImageReader imageReader1(imgPath1);
    QSize size = imageReader1.size();
    int w = size.width();
    int h = size.height();
    if (w > h){
      scale1 = w / static_cast<double>(maxSize);
    } else {
      scale1 = h / static_cast<double>(maxSize);
    }
    if (scale1 < 1.) scale1 = 1.;

    QImageReader imageReader2(imgPath2);
    size = imageReader2.size();
    w = size.width();
    h = size.height();
    if (w > h){
      scale2 = w / static_cast<double>(maxSize);
    } else {
      scale2 = h / static_cast<double>(maxSize);
    }
    if (scale2 < 1.) scale2 = 1.;
  }


  std::vector<cv::Point2f> pts_query;
  std::vector<cv::Point2f> pts_train;
  std::string line;

  if (ifs.is_open()){

    while (std::getline(ifs, line)) {

      QStringList list = QString(line.c_str()).split(";");
      if (list[0].compare(imgLeft) == 0 && list[1].compare(imgRight) == 0){
        cv::Point2f pt_query(list[2].toFloat(), list[3].toFloat());
        cv::Point2f pt_train(list[4].toFloat(), list[5].toFloat());
        pts_query.push_back(pt_query *= scale1);
        pts_train.push_back(pt_train *= scale2);
      } else if (list[0].compare(imgRight) == 0 && list[1].compare(imgLeft) == 0){
        cv::Point2f pt_query(list[4].toFloat(), list[5].toFloat());
        cv::Point2f pt_train(list[2].toFloat(), list[3].toFloat());
        pts_query.push_back(pt_query *= scale1);
        pts_train.push_back(pt_train *= scale2);
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
          std::vector<cv::DMatch> match;
          matchesRead(m.second, match);
          std::vector<cv::KeyPoint> keyPoints1, keyPoints2;
          cv::Mat descriptors;
          featuresRead(_session->features(imgLeft), keyPoints1, descriptors);
          featuresRead(_session->features(imgRight), keyPoints2, descriptors);

          for (size_t i = 0; i < keyPoints1.size(); i++){
            keyPoints1[i].pt *= scale1;
          }
          for (size_t i = 0; i < keyPoints2.size(); i++){
            keyPoints2[i].pt *= scale2;
          }

          std::vector<uchar> inliers(match.size(), 1);

          for (size_t i = 0; i < match.size(); i++){
            std::vector<cv::KeyPoint> key1;
            std::vector<cv::KeyPoint> key2;
            key1.push_back(keyPoints1[static_cast<size_t>(match[i].queryIdx)]);
            key2.push_back(keyPoints2[static_cast<size_t>(match[i].trainIdx)]);

            float repeteability = 0;
            int corres = 0;
            cv::evaluateFeatureDetector(img1, img2, H, &key1, &key2, repeteability, corres);

            if (corres == -1) inliers[i] = 0;
          }

          computePRCurve(match, inliers, curve);

          break;
        }
      }
    }
  }
  return curve;
}

} // namespace fme



