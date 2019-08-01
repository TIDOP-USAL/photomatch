#include "latch.h"

namespace fme
{

LatchProperties::LatchProperties()
  : ILatch(),
    mBytes("32"),
    mRotationInvariance(true),
    mHalfSsdSize(3)
{}

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


/*----------------------------------------------------------------*/


LatchDescriptor::LatchDescriptor()
  : LatchProperties(),
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

cv::Mat LatchDescriptor::extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints)
{
  cv::Mat descriptors;
  mLATCH->compute(img, keyPoints, descriptors);
  return descriptors;
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

/*----------------------------------------------------------------*/

} // namespace fme
