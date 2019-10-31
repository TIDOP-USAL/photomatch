#include "mser.h"

#include <tidop/core/messages.h>


namespace photomatch
{


MserProperties::MserProperties()
  : IMser(),
    mDelta(5),
    mMinArea(60),
    mMaxArea(14400),
    mMaxVariation(0.25),
    mMinDiversity(0.2),
    mMaxEvolution(200),
    mAreaThreshold(1.01),
    mMinMargin(0.003),
    mEdgeBlurSize(5)
{}

MserProperties::~MserProperties()
{

}

int MserProperties::delta() const
{
  return mDelta;
}

int MserProperties::minArea() const
{
  return mMinArea;
}

int MserProperties::maxArea() const
{
  return mMaxArea;
}

double MserProperties::maxVariation() const
{
  return mMaxVariation;
}

double MserProperties::minDiversity() const
{
  return mMinDiversity;
}

int MserProperties::maxEvolution() const
{
  return mMaxEvolution;
}

double MserProperties::areaThreshold() const
{
  return mAreaThreshold;
}

double MserProperties::minMargin() const
{
  return mMinMargin;
}

int MserProperties::edgeBlurSize() const
{
  return mEdgeBlurSize;
}

void MserProperties::setDelta(int delta)
{
  mDelta = delta;
}

void MserProperties::setMinArea(int minArea)
{
  mMinArea = minArea;
}

void MserProperties::setMaxArea(int maxArea)
{
  mMaxArea = maxArea;
}

void MserProperties::setMaxVariation(double maxVariation)
{
  mMaxVariation = maxVariation;
}

void MserProperties::setMinDiversity(double minDiversity)
{
  mMinDiversity = minDiversity;
}

void MserProperties::setMaxEvolution(int maxEvolution)
{
  mMaxEvolution = maxEvolution;
}

void MserProperties::setAreaThreshold(double areaThreshold)
{
  mAreaThreshold = areaThreshold;
}

void MserProperties::setMinMargin(double minMargin)
{
  mMinMargin = minMargin;
}

void MserProperties::setEdgeBlurSize(int edgeBlurSize)
{
  mEdgeBlurSize = edgeBlurSize;
}

void MserProperties::reset()
{
  mDelta = 5;
  mMinArea = 60;
  mMaxArea = 14400;
  mMaxVariation = 0.25;
  mMinDiversity = .2;
  mMaxEvolution = 200;
  mAreaThreshold = 1.01;
  mMinMargin = 0.003;
  mEdgeBlurSize = 5;
}

QString MserProperties::name() const
{
  return QString("MSER");
}


/*----------------------------------------------------------------*/


MserDetector::MserDetector()
  : MserProperties(),
    KeypointDetector()
{
  update();
}

MserDetector::MserDetector(int delta,
                           int minArea,
                           int maxArea,
                           double maxVariation,
                           double minDiversity,
                           int maxEvolution,
                           double areaThreshold,
                           double minMargin,
                           int edgeBlurSize)
  : MserProperties(),
    KeypointDetector()
{
  MserProperties::setDelta(delta);
  MserProperties::setMinArea(minArea);
  MserProperties::setMaxArea(maxArea);
  MserProperties::setMaxVariation(maxVariation);
  MserProperties::setMinDiversity(minDiversity);
  MserProperties::setMaxEvolution(maxEvolution);
  MserProperties::setAreaThreshold(areaThreshold);
  MserProperties::setMinMargin(minMargin);
  MserProperties::setEdgeBlurSize(edgeBlurSize);
  update();
}

MserDetector::~MserDetector()
{

}

void MserDetector::update()
{
  mMSER = cv::MSER::create(MserProperties::delta(),
                           MserProperties::minArea(),
                           MserProperties::maxArea(),
                           MserProperties::maxVariation(),
                           MserProperties::minDiversity(),
                           MserProperties::maxEvolution(),
                           MserProperties::areaThreshold(),
                           MserProperties::minMargin(),
                           MserProperties::edgeBlurSize());
}

bool MserDetector::detect(const cv::Mat &img,
                          std::vector<cv::KeyPoint> &keyPoints,
                          cv::InputArray &mask)
{

  try {
    mMSER->detect(img, keyPoints, mask);
  } catch (cv::Exception &e) {
    msgError("MSER Detector error: %s", e.what());
    return true;
  }

  return false;
}

void MserDetector::setDelta(int delta)
{
  MserProperties::setDelta(delta);
  mMSER->setDelta(delta);
}

void MserDetector::setMinArea(int minArea)
{
  MserProperties::setMinArea(minArea);
  mMSER->setMinArea(minArea);
}

void MserDetector::setMaxArea(int maxArea)
{
  MserProperties::setMaxArea(maxArea);
  mMSER->setMaxArea(maxArea);
}

void MserDetector::setMaxVariation(double maxVariation)
{
  MserProperties::setMaxVariation(maxVariation);
  update();
}

void MserDetector::setMinDiversity(double minDiversity)
{
  MserProperties::setMinDiversity(minDiversity);
  update();
}

void MserDetector::setMaxEvolution(int maxEvolution)
{
  MserProperties::setMaxEvolution(maxEvolution);
  update();
}

void MserDetector::setAreaThreshold(double areaThreshold)
{
  MserProperties::setAreaThreshold(areaThreshold);
  update();
}

void MserDetector::setMinMargin(double minMargin)
{
  MserProperties::setMinMargin(minMargin);
  update();
}

void MserDetector::setEdgeBlurSize(int edgeBlurSize)
{
  MserProperties::setEdgeBlurSize(edgeBlurSize);
  update();
}

void MserDetector::reset()
{
  MserProperties::reset();
  update();
}


} // namespace photomatch
