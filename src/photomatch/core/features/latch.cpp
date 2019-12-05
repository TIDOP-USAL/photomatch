#include "latch.h"

#include <tidop/core/messages.h>


namespace photomatch
{

LatchProperties::LatchProperties()
  : ILatch(),
    mBytes("32"),
    mRotationInvariance(true),
    mHalfSsdSize(3)
{
}

LatchProperties::LatchProperties(const LatchProperties &latchProperties)
  : ILatch(),
    mBytes(latchProperties.mBytes),
    mRotationInvariance(latchProperties.mRotationInvariance),
    mHalfSsdSize(latchProperties.mHalfSsdSize)
{
}

LatchProperties::~LatchProperties()
{

}

QString LatchProperties::bytes() const
{
  return mBytes;
}

bool LatchProperties::rotationInvariance() const
{
  return mRotationInvariance;
}

int LatchProperties::halfSsdSize() const
{
  return mHalfSsdSize;
}

void LatchProperties::setBytes(const QString &bytes)
{
  if (bytes.compare("1") == 0 ||
      bytes.compare("2") == 0 ||
      bytes.compare("4") == 0 ||
      bytes.compare("8") == 0 ||
      bytes.compare("16") == 0 ||
      bytes.compare("32") == 0 ||
      bytes.compare("64") == 0) {
    mBytes = bytes;
  }
}

void LatchProperties::setRotationInvariance(bool rotationInvariance)
{
  mRotationInvariance = rotationInvariance;
}

void LatchProperties::setHalfSsdSize(int halfSsdSize)
{
  mHalfSsdSize = halfSsdSize;
}

void LatchProperties::reset()
{
  mBytes = "32";
  mRotationInvariance = true;
  mHalfSsdSize = 3;
}

QString LatchProperties::name() const
{
  return QString("LATCH");
}


/*----------------------------------------------------------------*/


LatchDescriptor::LatchDescriptor()
  : LatchProperties(),
    DescriptorExtractor()
{
  update();
}

LatchDescriptor::LatchDescriptor(const LatchDescriptor &latchDescriptor)
  : LatchProperties(latchDescriptor),
    DescriptorExtractor()
{
  update();
}

LatchDescriptor::LatchDescriptor(QString bytes,
                                 bool rotationInvariance,
                                 int halfSsdSize)
  : LatchProperties(),
    DescriptorExtractor()
{
  LatchProperties::setBytes(bytes);
  LatchProperties::setRotationInvariance(rotationInvariance);
  LatchProperties::setHalfSsdSize(halfSsdSize);
  update();
}

LatchDescriptor::~LatchDescriptor()
{

}

void LatchDescriptor::update()
{
  mLATCH = cv::xfeatures2d::LATCH::create(LatchProperties::bytes().toInt(),
                                          LatchProperties::rotationInvariance(),
                                          LatchProperties::halfSsdSize());
}

bool LatchDescriptor::extract(const cv::Mat &img,
                              std::vector<cv::KeyPoint> &keyPoints,
                              cv::Mat &descriptors)
{

  try {
    mLATCH->compute(img, keyPoints, descriptors);
  } catch (cv::Exception &e) {
    msgError("LATCH Descriptor error: %s", e.what());
    return true;
  }

  return false;
}

void LatchDescriptor::setBytes(const QString &bytes)
{
  LatchProperties::setBytes(bytes);
  update();
}

void LatchDescriptor::setRotationInvariance(bool rotationInvariance)
{
  LatchProperties::setRotationInvariance(rotationInvariance);
  update();
}

void LatchDescriptor::setHalfSsdSize(int halfSsdSize)
{
  LatchProperties::setHalfSsdSize(halfSsdSize);
  update();
}

void LatchDescriptor::reset()
{
  LatchProperties::reset();
  update();
}



} // namespace photomatch
