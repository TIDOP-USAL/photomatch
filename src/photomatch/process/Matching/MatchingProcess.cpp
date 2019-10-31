#include "MatchingProcess.h"

#include "photomatch/core/features/features.h"
#include "photomatch/core/features/matcher.h"

#include <tidop/core/messages.h>

#include <QFileInfo>

namespace photomatch
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

}

} // namespace photomatch
