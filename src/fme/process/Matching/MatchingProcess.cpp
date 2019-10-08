#include "MatchingProcess.h"

#include "fme/core/features/features.h"
#include "fme/core/features/matcher.h"

#include <tidop/core/messages.h>

#include <QFileInfo>

namespace fme
{

MatchingProcess::MatchingProcess(const QString &queryDescriptors,
                                 const QString &trainDescriptors,
                                 const QString &matches,
                                 const std::shared_ptr<RobustMatching> &descriptorMatcher)
  : ProcessConcurrent(),
    mQueryDescriptors(queryDescriptors),
    mTrainDescriptors(trainDescriptors),
    mMatches(matches),
    mDescriptorMatcher(descriptorMatcher)
{

}

QString MatchingProcess::queryDescriptors() const
{
  return mQueryDescriptors;
}

void MatchingProcess::setQueryDescriptors(const QString &descriptors)
{
  mQueryDescriptors = descriptors;
}

QString MatchingProcess::trainDescriptors() const
{
  return mTrainDescriptors;
}

void MatchingProcess::setTrainDescriptors(const QString &descriptors)
{
  mTrainDescriptors = descriptors;
}

QString MatchingProcess::matches() const
{
  return mMatches;
}

void MatchingProcess::setMatches(const QString &matches)
{
  mMatches = matches;
}

void MatchingProcess::run()
{

  std::vector<cv::KeyPoint> keyPoints1;
  cv::Mat descriptors1;
  featuresRead(mQueryDescriptors, keyPoints1, descriptors1);

  std::vector<cv::KeyPoint> keyPoints2;
  cv::Mat descriptors2;
  featuresRead(mTrainDescriptors, keyPoints2, descriptors2);

  std::vector<cv::DMatch> wrongMatches;
  std::vector<cv::DMatch> goodMatches = mDescriptorMatcher->match(descriptors1, descriptors2, &wrongMatches);

  std::vector<cv::DMatch> filter_matches = mDescriptorMatcher->geometricFilter(goodMatches, keyPoints1, keyPoints2, &wrongMatches);

  matchesWrite(mMatches, filter_matches, wrongMatches);

  QByteArray ba = mMatches.toLocal8Bit();
  const char *cfeat = ba.data();
  msgInfo("Write matches at: %s", cfeat);

  emit matchCompute(QFileInfo(mQueryDescriptors).baseName(), QFileInfo(mTrainDescriptors).baseName(), mMatches);
  emit statusChangedNext();


//#ifdef _DEBUG
///// Para sacar automaticamente una verdad terreno para las pruebas
///// TODO: Borrar una vez se terminen las pruebas

//  std::string ground_truth("C:\\Users\\Tido\\Documents\\fme\\Projects\\Test\\GroundTruth.txt");

//  QString idImg1 = QFileInfo(mQueryDescriptors).baseName();
//  QString idImg2 = QFileInfo(mTrainDescriptors).baseName();
//  QByteArray ba2 = idImg1.toLocal8Bit();
//  const char *c_idImg1 = ba2.data();
//  QByteArray ba3 = idImg2.toLocal8Bit();
//  const char *c_idImg2 = ba3.data();

//  std::ofstream ofs(ground_truth, std::ofstream::app);
//  if (ofs.is_open()){

//    std::vector<cv::Point2f> pts_query;
//    std::vector<cv::Point2f> pts_train;
//    for (size_t i = 0; i < filter_matches.size(); i++){
//      size_t query_id = static_cast<size_t>(filter_matches[i].queryIdx);
//      size_t train_id = static_cast<size_t>(filter_matches[i].trainIdx);
//      pts_query.push_back(keyPoints1[query_id].pt);
//      pts_train.push_back(keyPoints2[train_id].pt);
//      ofs << c_idImg1 << ";" << c_idImg2 << ";" <<
//             keyPoints1[query_id].pt.x << ";" << keyPoints1[query_id].pt.y << ";" <<
//             keyPoints2[train_id].pt.x << ";" << keyPoints2[train_id].pt.y << std::endl;
//    }

//    ofs.close();
//  }

//#endif // _DEBUG

}

} // namespace fme
