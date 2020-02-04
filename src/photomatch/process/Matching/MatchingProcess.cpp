#include "MatchingProcess.h"

#include "photomatch/core/features/features.h"

#include <tidop/core/messages.h>

#include <QFileInfo>
#include <QImageReader>

namespace photomatch
{

MatchingProcess::MatchingProcess(const QString &queryDescriptors,
                                 const QString &trainDescriptors,
                                 const QString &matches,
                                 const std::shared_ptr<MatchingAlgorithm> &descriptorMatcher,
                                 const QString &queryImage,
                                 const QString &trainImage)
  : ProcessConcurrent(),
    mQueryDescriptors(queryDescriptors),
    mTrainDescriptors(trainDescriptors),
    mMatches(matches),
    mDescriptorMatcher(descriptorMatcher),
    mQueryImage(queryImage),
    mTrainImage(trainImage)
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
  std::vector<cv::DMatch> goodMatches;
//  std::vector<cv::DMatch> goodMatches = mDescriptorMatcher->match(descriptors1, descriptors2, &wrongMatches);

//  std::vector<cv::DMatch> filter_matches = mDescriptorMatcher->geometricFilter(goodMatches, keyPoints1, keyPoints2, &wrongMatches);
  QSize query_size;
  QSize train_size;
  if (mQueryImage.isEmpty() == false && mTrainImage.isEmpty() == false){
    QImageReader imageReader(mQueryImage);
    query_size = imageReader.size();
    imageReader.setFileName(mTrainImage);
    train_size = imageReader.size();
  }

  mDescriptorMatcher->compute(descriptors1, descriptors2, keyPoints1, keyPoints2, &goodMatches, &wrongMatches, query_size, train_size);

  matchesWrite(mMatches, goodMatches, wrongMatches);

  QByteArray ba = mMatches.toLocal8Bit();
  const char *cfeat = ba.data();
  msgInfo("Write matches at: %s", cfeat);

  emit matchCompute(QFileInfo(mQueryDescriptors).baseName(), QFileInfo(mTrainDescriptors).baseName(), mMatches);
  emit statusChangedNext();

}

QString MatchingProcess::trainImage() const
{
    return mTrainImage;
}

void MatchingProcess::setTrainImage(const QString &trainImage)
{
    mTrainImage = trainImage;
}

QString MatchingProcess::queryImage() const
{
    return mQueryImage;
}

void MatchingProcess::setQueryImage(const QString &queryImage)
{
    mQueryImage = queryImage;
}

} // namespace photomatch
