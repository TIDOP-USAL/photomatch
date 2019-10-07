#include "MatchViewerModel.h"

#include "fme/ui/ProjectModel.h"

#include <QImageReader>
#include <QFileInfo>

namespace fme
{

MatchViewerModel::MatchViewerModel(IProjectModel *mProjectModel)
  : IMatchViewerModel(),
    mProjectModel(mProjectModel)
{
  init();
}

void MatchViewerModel::init()
{
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

std::vector<std::tuple<QPointF, QPointF, float>> MatchViewerModel::loadMatches(const QString &imgName1, const QString &imgName2) const
{
  std::vector<std::tuple<QPointF, QPointF, float>> r_matches;

  QString imgPath1 = mProjectModel->findImageByName(imgName1)->path();
  QString imgPath2 = mProjectModel->findImageByName(imgName2)->path();

  if (QFileInfo(imgPath1).exists() == false || QFileInfo(imgPath2).exists() == false)
    return r_matches;

//  /// Una escala para cada imagen por si tienen tamaño diferente
//  double scale1 = 1.;
//  double scale2 = 1.;
//  if (mProjectModel->fullImageSize() == false){
//    int maxSize = mProjectModel->maxImageSize();
//    QImageReader imageReader1(imgPath1);
//    QSize size = imageReader1.size();
//    int w = size.width();
//    int h = size.height();
//    if (w > h){
//      scale1 = w / static_cast<double>(maxSize);
//    } else {
//      scale1 = h / static_cast<double>(maxSize);
//    }
//    if (scale1 < 1.) scale1 = 1.;

//    QImageReader imageReader2(imgPath2);
//    size = imageReader2.size();
//    w = size.width();
//    h = size.height();
//    if (w > h){
//      scale2 = w / static_cast<double>(maxSize);
//    } else {
//      scale2 = h / static_cast<double>(maxSize);
//    }
//    if (scale2 < 1.) scale2 = 1.;

////    if (scale1 > 1.) {
////      for (size_t i = 0; i < keyPoints.size(); i++){
////        keyPoints[i]*= scale;
////      }
////    }
//  }

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
          for (size_t i = 0; i < match.size(); i++){
            size_t query_id = (idx == 0) ? static_cast<size_t>(match[i].queryIdx) : static_cast<size_t>(match[i].trainIdx);
            size_t train_id = (idx == 0) ? static_cast<size_t>(match[i].trainIdx) : static_cast<size_t>(match[i].queryIdx);
            QPointF pt_query(static_cast<double>(keyPoints1[query_id].pt.x) /** scale1*/,
                             static_cast<double>(keyPoints1[query_id].pt.y) /** scale1*/);
            QPointF pt_train(static_cast<double>(keyPoints2[train_id].pt.x) /** scale2*/,
                             static_cast<double>(keyPoints2[train_id].pt.y) /** scale2*/);

            r_matches.push_back(std::make_tuple(pt_query, pt_train, match[i].distance));
          }

          break;
        }
      }
    }
  }

  return r_matches;
}

} // namespace fme
