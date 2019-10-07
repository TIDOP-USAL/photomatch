#include "HomographyViewerModel.h"

#include <tidop/core/messages.h>

#include "fme/ui/ProjectModel.h"
#include "fme/core/utils.h"

#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#ifdef HAVE_CUDA
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudaarithm.hpp>
#endif

#include <QFileInfo>

namespace fme
{

HomographyViewerModel::HomographyViewerModel(IProjectModel *mProjectModel)
  : IHomographyViewerModel(),
    mProjectModel(mProjectModel)
{
  init();
}

fme::HomographyViewerModel::~HomographyViewerModel()
{

}

std::vector<QString> HomographyViewerModel::images() const
{
  std::vector<QString> images;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    images.push_back((*it)->path());
  }
  return images;
}

std::vector<QString> HomographyViewerModel::imagePairs(const QString &imageName) const
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

QImage HomographyViewerModel::homography(const QString &imgName1, const QString &imgName2) const
{
  QImage image;
  QString imgPath1 = mProjectModel->findImageByName(imgName1)->path();
  QString imgPath2 = mProjectModel->findImageByName(imgName2)->path();

  if (QFileInfo(imgPath1).exists() == false || QFileInfo(imgPath2).exists() == false)
    return image;

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

  if (std::shared_ptr<Session> session = mProjectModel->currentSession()){
    std::vector<std::pair<QString, QString>> matches = session->matches(imgName1);

    if (!matches.empty()){
      for (auto &m : matches){
        if (m.first.compare(imgName2) == 0){
          std::vector<cv::DMatch> match;
          matchesRead(m.second, match);
          std::vector<cv::KeyPoint> keyPoints1, keyPoints2;
          cv::Mat descriptors;
          featuresRead(session->features(imgName1), keyPoints1, descriptors);
          featuresRead(session->features(imgName2), keyPoints2, descriptors);

          /// Un tanto artificioso.... Revisar
          QString nameMatchesFile = QFileInfo(m.second).baseName();
          int idx = nameMatchesFile.indexOf(imgName1);
          std::vector<cv::Point2f> pts_query;
          std::vector<cv::Point2f> pts_train;
//          std::vector<cv::KeyPoint> kps1;
//          std::vector<cv::KeyPoint> kps2;
          for (size_t i = 0; i < match.size(); i++){
            size_t query_id = (idx == 0) ? static_cast<size_t>(match[i].queryIdx) : static_cast<size_t>(match[i].trainIdx);
            size_t train_id = (idx == 0) ? static_cast<size_t>(match[i].trainIdx) : static_cast<size_t>(match[i].queryIdx);
            pts_query.push_back(keyPoints1[query_id].pt * scale1);
            pts_train.push_back(keyPoints2[train_id].pt * scale2);
//            cv::KeyPoint kp1 = keyPoints1[query_id];
//            cv::KeyPoint kp2 = keyPoints2[train_id];
//            kp1.pt *= scale1;
//            kp2.pt *= scale2;
//            kps1.push_back(kp1);
//            kps2.push_back(kp2);
          }

          cv::Mat H = cv::findHomography(pts_query, pts_train);

//          /// RMS
//          size_t n = pts_query.size();
//          std::vector<cv::Point2f> pts_out(n);
//          std::vector<double> err(n);
//          double sumErr = 0.;
//          cv::perspectiveTransform(pts_query, pts_out, H);
//          for (size_t i = 0; i < n; i++) {
//            pts_out[i] -= pts_train[i];
//            err[i] = static_cast<double>(pts_out[i].x * pts_out[i].x + pts_out[i].y * pts_out[i].y);
//            sumErr += err[i];
//          }
//          double rms = sqrt(sumErr/(2 * (n - 4)));
//          msgInfo("Homography transformation RMS: %f", rms);

          QByteArray ba = imgPath1.toLocal8Bit();
          const char *img_left = ba.data();
          cv::Mat imgLeft = cv::imread(img_left, cv::IMREAD_IGNORE_ORIENTATION);
          ba = imgPath2.toLocal8Bit();
          const char *img_right = ba.data();
          cv::Mat imgRight = cv::imread(img_right, cv::IMREAD_IGNORE_ORIENTATION);
          cv::Mat out;
          cv::warpPerspective(imgLeft, out, H, imgRight.size(), cv::INTER_LINEAR);
          ///cv::cuda::warpPerspective

//          float repeatability;
//          int corrCounter;
//          cv::evaluateFeatureDetector(imgLeft, imgRight, H, &kps1, &kps2, repeatability, corrCounter);
//          msgInfo("Repeatability: %f", repeatability);
//          msgInfo("Correspondence: %i", corrCounter);

          cv::Mat merged;
          cv::addWeighted(imgRight, 0.5, out, 0.3, 0.0, merged);
          ///cv::cuda::addWeighted

          image = cvMatToQImage(merged);
          break;
        }
      }
    }
  }

  return image;
}

void HomographyViewerModel::init()
{
}

} // namespace fme


