#include "vgg.h"

#include <tidop/core/messages.h>

namespace photomatch
{


VggProperties::VggProperties()
  : IVgg(),
    mDescriptorType("VGG_120"),
    mScaleFactor(6.25),
    mSigma(1.4),
    bUseNormalizeDescriptor(false),
    bUseNormalizeImage(true),
    bUseScaleOrientation(true)
{

}

VggProperties::~VggProperties()
{

}

QString VggProperties::descriptorType() const
{
  return mDescriptorType;
}

void VggProperties::setDescriptorType(const QString &descriptorType)
{
  if (descriptorType.compare("VGG_120") == 0 ||
      descriptorType.compare("VGG_80") == 0 ||
      descriptorType.compare("VGG_64") == 0 ||
      descriptorType.compare("VGG_48") == 0) {
    mDescriptorType = descriptorType;
  }
}

double VggProperties::scaleFactor() const
{
  return mScaleFactor;
}

void VggProperties::setScaleFactor(double scaleFactor)
{
  mScaleFactor = scaleFactor;
}

double VggProperties::sigma() const
{
  return mSigma;
}

void VggProperties::setSigma(double sigma)
{
  mSigma = sigma;
}

bool VggProperties::useNormalizeDescriptor() const
{
  return bUseNormalizeDescriptor;
}

void VggProperties::setUseNormalizeDescriptor(bool useNormalizeDescriptor)
{
  bUseNormalizeDescriptor = useNormalizeDescriptor;
}

bool VggProperties::useNormalizeImage() const
{
  return bUseNormalizeImage;
}

void VggProperties::setUseNormalizeImage(bool useNormalizeImage)
{
  bUseNormalizeImage = useNormalizeImage;
}

bool VggProperties::useScaleOrientation() const
{
  return bUseScaleOrientation;
}

void VggProperties::setUseScaleOrientation(bool useScaleOrientation)
{
  bUseScaleOrientation = useScaleOrientation;
}

void photomatch::VggProperties::reset()
{
  mDescriptorType = "VGG_120";
  mScaleFactor = 6.25;
  mSigma = 1.4;
  bUseNormalizeDescriptor = false;
  bUseNormalizeImage = true;
  bUseScaleOrientation = true;
}

QString photomatch::VggProperties::name() const
{
  return QString("VGG");
}



/*----------------------------------------------------------------*/



VggDescriptor::VggDescriptor()
  : VggProperties(),
    DescriptorExtractor()
{
  update();
}

VggDescriptor::VggDescriptor(QString descriptorType,
                             double scaleFactor,
                             double sigma,
                             bool useNormalizeDescriptor,
                             bool useNormalizeImage,
                             bool useScaleOrientation)
  : VggProperties(),
    DescriptorExtractor()
{
  VggProperties::setDescriptorType(descriptorType);
  VggProperties::setScaleFactor(scaleFactor);
  VggProperties::setSigma(sigma);
  VggProperties::setUseNormalizeDescriptor(useNormalizeDescriptor);
  VggProperties::setUseNormalizeImage(useNormalizeImage);
  VggProperties::setUseScaleOrientation(useScaleOrientation);
  update();
}

VggDescriptor::~VggDescriptor()
{

}

void VggDescriptor::update()
{
  int descriptor_type = cv::xfeatures2d::VGG::VGG_120;
  QString descriptorType = VggProperties::descriptorType();
  if (descriptorType.compare("VGG_120") == 0 ) {
    descriptor_type = cv::xfeatures2d::VGG::VGG_120;
  } else if (descriptorType.compare("VGG_80") == 0){
    descriptor_type = cv::xfeatures2d::VGG::VGG_80;
  } else if (descriptorType.compare("VGG_64") == 0){
    descriptor_type = cv::xfeatures2d::VGG::VGG_64;
  } else if (descriptorType.compare("VGG_48") == 0){
    descriptor_type = cv::xfeatures2d::VGG::VGG_48;
  }

#if CV_VERSION_MAJOR >= 3
#  if CV_VERSION_MINOR > 2
  mVGG = cv::xfeatures2d::VGG::create(descriptor_type,
                                      static_cast<float>(VggProperties::sigma()),
                                      VggProperties::useNormalizeImage(),
                                      VggProperties::useScaleOrientation(),
                                      static_cast<float>(VggProperties::scaleFactor()),
                                      VggProperties::useNormalizeDescriptor());
#  endif
#endif
}

void VggDescriptor::reset()
{
  VggProperties::reset();
  update();
}

void VggDescriptor::setDescriptorType(const QString &descriptorType)
{
  VggProperties::setDescriptorType(descriptorType);
  update();
}

void VggDescriptor::setScaleFactor(double scaleFactor)
{
  VggProperties::setScaleFactor(scaleFactor);
  update();
}

void VggDescriptor::setSigma(double sigma)
{
  VggProperties::setSigma(sigma);
  update();
}

void VggDescriptor::setUseNormalizeDescriptor(bool useNormalizeDescriptor)
{
  VggProperties::setUseNormalizeDescriptor(useNormalizeDescriptor);
  update();
}

void VggDescriptor::setUseNormalizeImage(bool useNormalizeImage)
{
  VggProperties::setUseNormalizeImage(useNormalizeImage);
  update();
}

void VggDescriptor::setUseScaleOrientation(bool useScaleOrientation)
{
  VggProperties::setUseScaleOrientation(useScaleOrientation);
  update();
}

bool VggDescriptor::extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints, cv::Mat &descriptors)
{
#if CV_VERSION_MAJOR >= 3
#  if CV_VERSION_MINOR > 2
  try {
    mVGG->compute(img, keyPoints, descriptors);
  } catch (cv::Exception &e) {
    msgError("VGG Descriptor error: %s", e.what());
    return true;
  }

#  else
  QString msg("VGG Descriptor not supported in OpenCV ");
  msg.append(CV_VERSION);
  QByteArray ba = msg.toLocal8Bit();
  const char *cmsg = ba.data();
  TL_COMPILER_WARNING(cmsg);
#  endif
#endif
  return false;
}

} // namespace photomatch


