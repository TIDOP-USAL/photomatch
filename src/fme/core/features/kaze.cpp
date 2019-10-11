#include "kaze.h"

#include <tidop/core/messages.h>


namespace fme
{


KazeProperties::KazeProperties()
  : IKaze(),
    mExtended(false),
    mUpright(false),
    mThreshold(0.001),
    mOctaves(4),
    mOctaveLayers(4),
    mDiffusivity("DIFF_PM_G2")
{}

KazeProperties::~KazeProperties()
{

}

bool KazeProperties::extendedDescriptor() const
{
  return mExtended;
}

bool KazeProperties::upright() const
{
  return mUpright;
}

double KazeProperties::threshold() const
{
  return mThreshold;
}

int KazeProperties::octaves() const
{
  return mOctaves;
}

int KazeProperties::octaveLayers() const
{
  return mOctaveLayers;
}

QString KazeProperties::diffusivity() const
{
  return mDiffusivity;
}

void KazeProperties::setExtendedDescriptor(bool extended)
{
  mExtended = extended;
}

void KazeProperties::setUpright(bool upright)
{
  mUpright = upright;
}

void KazeProperties::setThreshold(double threshold)
{
  mThreshold = threshold;
}

void KazeProperties::setOctaves(int octaves)
{
  mOctaves = octaves;
}

void KazeProperties::setOctaveLayers(int octaveLayers)
{
  mOctaveLayers = octaveLayers;
}

void KazeProperties::setDiffusivity(const QString &diffusivity)
{
  if (diffusivity.compare("DIFF_PM_G1") == 0 ||
      diffusivity.compare("DIFF_PM_G2") == 0 ||
      diffusivity.compare("DIFF_WEICKERT") == 0 ||
      diffusivity.compare("DIFF_CHARBONNIER") == 0){
    mDiffusivity = diffusivity;
  }
}

void KazeProperties::reset()
{
  mExtended = false;
  mUpright = false;
  mThreshold = 0.001;
  mOctaves = 4;
  mOctaveLayers = 4;
  mDiffusivity = "DIFF_PM_G2";
}

QString KazeProperties::name() const
{
  return QString("KAZE");
}

/*----------------------------------------------------------------*/



KazeDetectorDescriptor::KazeDetectorDescriptor()
  : KazeProperties(),
    KeypointDetector(),
    DescriptorExtractor(),
    mKaze(cv::KAZE::create())
{
  setExtendedDescriptor(KazeProperties::extendedDescriptor());
  setUpright(KazeProperties::upright());
  setThreshold(KazeProperties::threshold());
  setOctaves(KazeProperties::octaves());
  setOctaveLayers(KazeProperties::octaveLayers());
  setDiffusivity(KazeProperties::diffusivity());
}

KazeDetectorDescriptor::KazeDetectorDescriptor(bool extendedDescriptor,
                                               bool upright,
                                               double threshold,
                                               int octaves,
                                               int octaveLayers,
                                               QString diffusivity)
  : KazeProperties(),
    KeypointDetector(),
    DescriptorExtractor(),
    mKaze(cv::KAZE::create())
{
  setExtendedDescriptor(extendedDescriptor);
  setUpright(upright);
  setThreshold(threshold);
  setOctaves(octaves);
  setOctaveLayers(octaveLayers);
  setDiffusivity(diffusivity);
}

KazeDetectorDescriptor::~KazeDetectorDescriptor()
{

}

bool KazeDetectorDescriptor::detect(const cv::Mat &img,
                                    std::vector<cv::KeyPoint> &keyPoints,
                                    cv::InputArray &mask)
{

  try {
    mKaze->detect(img, keyPoints, mask);
  } catch (cv::Exception &e) {
    msgError("KAZE Detector error: %s", e.what());
    return true;
  }

  return false;
}

bool KazeDetectorDescriptor::extract(const cv::Mat &img,
                                     std::vector<cv::KeyPoint> &keyPoints,
                                     cv::Mat &descriptors)
{

  try {
    mKaze->compute(img, keyPoints, descriptors);
  } catch (cv::Exception &e) {
    msgError("KAZE Descriptor error: %s", e.what());
    return true;
  }

  return false;
}

void KazeDetectorDescriptor::setExtendedDescriptor(bool extended)
{
  KazeProperties::setExtendedDescriptor(extended);
  mKaze->setExtended(extended);
}

void KazeDetectorDescriptor::setUpright(bool upright)
{
  KazeProperties::setUpright(upright);
  mKaze->setUpright(upright);
}

void KazeDetectorDescriptor::setThreshold(double threshold)
{
  KazeProperties::setThreshold(threshold);
  mKaze->setThreshold(threshold);
}

void KazeDetectorDescriptor::setOctaves(int octaves)
{
  KazeProperties::setOctaves(octaves);
  mKaze->setNOctaves(octaves);
}

void KazeDetectorDescriptor::setOctaveLayers(int octaveLayers)
{
  KazeProperties::setOctaveLayers(octaveLayers);
  mKaze->setNOctaveLayers(octaveLayers);
}

void KazeDetectorDescriptor::setDiffusivity(const QString &diffusivity)
{
  KazeProperties::setDiffusivity(diffusivity);

#if CV_VERSION_MAJOR >= 4  
  cv::KAZE::DiffusivityType diff = cv::KAZE::DIFF_PM_G1;
#else
  int diff = cv::KAZE::DIFF_PM_G1;
#endif

  if (diffusivity.compare("DIFF_PM_G1") == 0){
    diff = cv::KAZE::DIFF_PM_G1;
  } else if (diffusivity.compare("DIFF_PM_G2") == 0){
    diff = cv::KAZE::DIFF_PM_G2;
  } else if (diffusivity.compare("DIFF_WEICKERT") == 0){
    diff = cv::KAZE::DIFF_WEICKERT;
  } else if (diffusivity.compare("DIFF_CHARBONNIER") == 0){
    diff = cv::KAZE::DIFF_CHARBONNIER;
  }
  mKaze->setDiffusivity(diff);
}

void KazeDetectorDescriptor::reset()
{
  KazeProperties::reset();
  mKaze->setExtended(KazeProperties::extendedDescriptor());
  mKaze->setUpright(KazeProperties::upright());
  mKaze->setThreshold(KazeProperties::threshold());
  mKaze->setNOctaves(KazeProperties::octaves());
  mKaze->setNOctaveLayers(KazeProperties::octaveLayers());
  setDiffusivity(KazeProperties::diffusivity());
}


} // namespace fme







