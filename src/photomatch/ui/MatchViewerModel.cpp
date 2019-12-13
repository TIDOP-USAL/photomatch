#include "MatchViewerModel.h"

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
}

QString MatchViewerModel::sessionName() const
{
  return mProjectModel->currentSession()->name();
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

//std::vector<std::tuple<size_t, QPointF, size_t, QPointF, float>> MatchViewerModel::loadMatches(const QString &imgName1, const QString &imgName2) const
//{
//  std::vector<std::tuple<size_t, QPointF, size_t, QPointF, float>> r_matches;

//  QString imgPath1 = mProjectModel->findImageByName(imgName1)->path();
//  QString imgPath2 = mProjectModel->findImageByName(imgName2)->path();

//  if (QFileInfo(imgPath1).exists() == false || QFileInfo(imgPath2).exists() == false)
//    return r_matches;

//  if (std::shared_ptr<Session> session = mProjectModel->currentSession()){
//    std::vector<std::pair<QString, QString>> matches = session->matches(imgName1);

//    if (!matches.empty()){
//      for (auto &m : matches){
//        if (m.first.compare(imgName2) == 0){
//          std::vector<cv::DMatch> match;
//          matchesRead(m.second, &match);
//          std::vector<cv::KeyPoint> keyPoints1, keyPoints2;
//          cv::Mat descriptors;
//          featuresRead(session->features(imgName1), keyPoints1, descriptors);
//          featuresRead(session->features(imgName2), keyPoints2, descriptors);

//          /// Un tanto artificioso.... Revisar
//          QString nameMatchesFile = QFileInfo(m.second).baseName();
//          int idx = nameMatchesFile.indexOf(imgName1);
//          for (size_t i = 0; i < match.size(); i++){
//            size_t query_id = (idx == 0) ? static_cast<size_t>(match[i].queryIdx) : static_cast<size_t>(match[i].trainIdx);
//            size_t train_id = (idx == 0) ? static_cast<size_t>(match[i].trainIdx) : static_cast<size_t>(match[i].queryIdx);
//            QPointF pt_query(static_cast<double>(keyPoints1[query_id].pt.x),
//                             static_cast<double>(keyPoints1[query_id].pt.y));
//            QPointF pt_train(static_cast<double>(keyPoints2[train_id].pt.x),
//                             static_cast<double>(keyPoints2[train_id].pt.y));

//            r_matches.push_back(std::make_tuple(query_id, pt_query, train_id, pt_train, match[i].distance));
//          }

//          break;
//        }
//      }
//    }
//  }

//  return r_matches;
//}

std::vector<std::tuple<size_t, size_t, QPointF, size_t, QPointF, float>>
MatchViewerModel::loadMatches(const QString &imgName1, const QString &imgName2) const
{
  std::vector<std::tuple<size_t, size_t, QPointF, size_t, QPointF, float>> r_matches;

  if (std::shared_ptr<Session> session = mProjectModel->currentSession()){

    std::vector<cv::KeyPoint> keyPoints1, keyPoints2;
    cv::Mat descriptors;
    featuresRead(session->features(imgName1), keyPoints1, descriptors);
    featuresRead(session->features(imgName2), keyPoints2, descriptors);
    descriptors.release();

    std::vector<std::pair<QString, QString>> matches = session->matches(imgName1);
    std::vector<cv::DMatch> match;
    //int idx = 0;
    if (!matches.empty()){
      for (auto &m : matches){
        if (m.first.compare(imgName2) == 0){
          matchesRead(m.second, &match);
          //QString nameMatchesFile = QFileInfo(m.second).baseName();
          //7idx = nameMatchesFile.indexOf(imgName1);
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
    if (std::shared_ptr<Session> session = mProjectModel->currentSession()){
      std::vector<std::pair<QString, QString>> matches = session->matches(imgName1);

      if (!matches.empty()){
        for (auto &m : matches){
          if (m.first.compare(imgName2) == 0){
            std::vector<cv::DMatch> good_matches;
            std::vector<cv::DMatch> wrong_matches;
            matchesRead(m.second, &good_matches, &wrong_matches);

            for (size_t i = 0; i < good_matches.size(); i++){
              if (good_matches[i].queryIdx == query_id &&
                  good_matches[i].trainIdx == train_id){
                wrong_matches.push_back(good_matches[i]);
                good_matches.erase(good_matches.begin()+static_cast<long long>(i));
                break;
              }
            }

            matchesWrite(m.second, good_matches, wrong_matches);

            break;
          }
        }
      }
    }
    }
}

void MatchViewerModel::loadPassPoints()
{
  if (std::shared_ptr<Session> session = mProjectModel->currentSession()){
    passPointsRead(session->passPoints(), mPassPoints);
  } else {
    mPassPoints.clear();
  }
}

} // namespace photomatch
