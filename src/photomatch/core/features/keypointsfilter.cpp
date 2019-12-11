#include "keypointsfilter.h"

#include <tidop/core/messages.h>

namespace photomatch
{


KeyPointsFilterNBestProperties::KeyPointsFilterNBestProperties()
  : KeyPointsFilter(KeyPointsFilter::Type::n_best),
    mPointsNumber(5000)
{
}

int KeyPointsFilterNBestProperties::nPoints() const
{
  return mPointsNumber;
}

void KeyPointsFilterNBestProperties::setNPoints(int nPoints)
{
  mPointsNumber = nPoints;
}

void KeyPointsFilterNBestProperties::reset()
{
  mPointsNumber = 5000;
}



/*----------------------------------------------------------------*/



KeyPointsFilterNBest::KeyPointsFilterNBest()
  : KeyPointsFilterNBestProperties(),
    KeyPointsFilterProcess()
{
}

KeyPointsFilterNBest::KeyPointsFilterNBest(int nPoints)
  : KeyPointsFilterNBestProperties(),
    KeyPointsFilterProcess()
{
  this->setNPoints(nPoints);
}

void KeyPointsFilterNBest::setNPoints(int nPoints)
{
  KeyPointsFilterNBestProperties::setNPoints(nPoints);
}

bool KeyPointsFilterNBest::filter(const std::vector<cv::KeyPoint> &keypoints, std::vector<cv::KeyPoint> &filteredKeypoints)
{

  try {
    filteredKeypoints = keypoints;
    cv::KeyPointsFilter::retainBest(filteredKeypoints, KeyPointsFilterNBestProperties::nPoints());
    if (filteredKeypoints.size() != static_cast<size_t>(KeyPointsFilterNBestProperties::nPoints())){
      /// Los keypoints no tienen 'response'. Por ahora...
      filteredKeypoints.resize(static_cast<size_t>(KeyPointsFilterNBestProperties::nPoints()));
    }
    msgInfo("Filtered retaining %i best keypoints", KeyPointsFilterNBestProperties::nPoints());
  } catch (cv::Exception &e) {
    msgError("Filtered keypoints error: %s", e.what());
    return true;
  }
  return false;

}

void KeyPointsFilterNBest::reset()
{
  KeyPointsFilterNBestProperties::reset();
}


/*----------------------------------------------------------------*/



KeyPointsFilterBySizeProperties::KeyPointsFilterBySizeProperties()
  : KeyPointsFilter(KeyPointsFilter::Type::size),
    mMinSize(0.),
    mMaxSize(TL_DOUBLE_MAX)
{
}

double KeyPointsFilterBySizeProperties::minSize() const
{
  return mMinSize;
}

void KeyPointsFilterBySizeProperties::setMinSize(double minSize)
{
  mMinSize = minSize;
}

double KeyPointsFilterBySizeProperties::maxSize() const
{
  return mMaxSize;
}

void KeyPointsFilterBySizeProperties::setMaxSize(double maxSize)
{
  mMaxSize = maxSize;
}

void KeyPointsFilterBySizeProperties::reset()
{
  mMinSize = 0.;
  mMaxSize = TL_DOUBLE_MAX;
}


/*----------------------------------------------------------------*/


KeyPointsFilterBySize::KeyPointsFilterBySize()
  : KeyPointsFilterBySizeProperties(),
    KeyPointsFilterProcess()
{}

KeyPointsFilterBySize::KeyPointsFilterBySize(double minSize, double maxSize)
  : KeyPointsFilterBySizeProperties(),
    KeyPointsFilterProcess()
{
  this->setMinSize(minSize);
  this->setMaxSize(maxSize);
}

void KeyPointsFilterBySize::setMinSize(double minSize)
{
  KeyPointsFilterBySizeProperties::setMinSize(minSize);
}

void KeyPointsFilterBySize::setMaxSize(double maxSize)
{
  KeyPointsFilterBySizeProperties::setMaxSize(maxSize);
}

bool KeyPointsFilterBySize::filter(const std::vector<cv::KeyPoint> &keypoints, std::vector<cv::KeyPoint> &filteredKeypoints)
{
  try {
    filteredKeypoints = keypoints;
    size_t size = keypoints.size();
    double min_size = KeyPointsFilterBySizeProperties::minSize();
    double max_size = KeyPointsFilterBySizeProperties::maxSize();
    cv::KeyPointsFilter::runByKeypointSize(filteredKeypoints, static_cast<float>(min_size), static_cast<float>(max_size));
    size_t new_size = filteredKeypoints.size();
    msgInfo("Filtered keypoints by size (min=%f,max=%f): %i", min_size, max_size, size - new_size);
  } catch (cv::Exception &e) {
    msgError("Filtered keypoints error: %s", e.what());
    return true;
  }
  return false;
}

void KeyPointsFilterBySize::reset()
{
  KeyPointsFilterBySizeProperties::reset();
}


/*----------------------------------------------------------------*/


KeyPointsFilterRemoveDuplicated::KeyPointsFilterRemoveDuplicated()
  : KeyPointsFilterProcess()
{
}

bool KeyPointsFilterRemoveDuplicated::filter(const std::vector<cv::KeyPoint>& keypoints, std::vector<cv::KeyPoint>& filteredKeypoints)
{
  try {
    filteredKeypoints = keypoints;
    int size = static_cast<int>(keypoints.size());
    cv::KeyPointsFilter::removeDuplicated(filteredKeypoints);
    int new_size = static_cast<int>(filteredKeypoints.size());
    msgInfo("Remove duplicated keypoints: %i", size - new_size);

  } catch (cv::Exception &e) {
    msgError("Filtered keypoints error: %s", e.what());
    return true;
  }
  return false;
}

} // namespace photomatch







