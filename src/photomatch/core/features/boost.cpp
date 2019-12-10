#include "boost.h"

#include <tidop/core/messages.h>

namespace photomatch
{

BoostProperties::BoostProperties()
  : IBoost(),
    mDescriptorType("BINBOOST_256"),
    bUseOrientation(true),
    mScaleFactor(6.25)
{

}

BoostProperties::BoostProperties(const BoostProperties &boostProperties)
  : IBoost(),
    mDescriptorType(boostProperties.mDescriptorType),
    bUseOrientation(boostProperties.bUseOrientation),
    mScaleFactor(boostProperties.mScaleFactor)
{

}

BoostProperties::~BoostProperties()
{

}

QString BoostProperties::descriptorType() const
{
  return mDescriptorType;
}

bool BoostProperties::useOrientation() const
{
  return bUseOrientation;
}

double BoostProperties::scaleFactor() const
{
  return mScaleFactor;
}

void BoostProperties::setDescriptorType(const QString &descriptorType)
{
  if (descriptorType.compare("BGM") == 0 ||
      descriptorType.compare("BGM_HARD") == 0 ||
      descriptorType.compare("BGM_BILINEAR") == 0 ||
      descriptorType.compare("LBGM") == 0||
      descriptorType.compare("BINBOOST_64") == 0||
      descriptorType.compare("BINBOOST_128") == 0||
      descriptorType.compare("BINBOOST_256") == 0) {
    mDescriptorType = descriptorType;
  }
}

void BoostProperties::setUseOrientation(bool useOrientation)
{
  bUseOrientation = useOrientation;
}

void BoostProperties::setScaleFactor(double scaleFactor)
{
  mScaleFactor = scaleFactor;
}

void BoostProperties::reset()
{
  mDescriptorType = "BINBOOST_256";
  bUseOrientation = true;
  mScaleFactor = 6.25;
}

QString BoostProperties::name() const
{
  return QString("BOOST");
}


/*----------------------------------------------------------------*/


BoostDescriptor::BoostDescriptor()
  : BoostProperties(),
    DescriptorExtractor()
{
  update();
}

BoostDescriptor::BoostDescriptor(const BoostDescriptor &boostDescriptor)
  : BoostProperties(boostDescriptor),
    DescriptorExtractor()
{
  update();
}

BoostDescriptor::BoostDescriptor(QString descriptorType,
                                 bool useOrientation,
                                 double scaleFactor)
  : BoostProperties(),
    DescriptorExtractor()
{
  BoostProperties::setDescriptorType(descriptorType);
  BoostProperties::setUseOrientation(useOrientation);
  BoostProperties::setScaleFactor(scaleFactor);
  update();
}

BoostDescriptor::~BoostDescriptor()
{

}

void BoostDescriptor::update()
{
  int descriptor_type = cv::xfeatures2d::BoostDesc::BGM;
  QString descriptorType = BoostProperties::descriptorType();
  if (descriptorType.compare("BGM") == 0 ) {
    descriptor_type = cv::xfeatures2d::BoostDesc::BGM;
  } else if (descriptorType.compare("BGM_HARD") == 0){
    descriptor_type = cv::xfeatures2d::BoostDesc::BGM_HARD;
  } else if (descriptorType.compare("BGM_BILINEAR") == 0){
    descriptor_type = cv::xfeatures2d::BoostDesc::BGM_BILINEAR;
  } else if (descriptorType.compare("LBGM") == 0){
    descriptor_type = cv::xfeatures2d::BoostDesc::LBGM;
  } else if (descriptorType.compare("BINBOOST_64") == 0){
    descriptor_type = cv::xfeatures2d::BoostDesc::BINBOOST_64;
  } else if (descriptorType.compare("BINBOOST_128") == 0){
    descriptor_type = cv::xfeatures2d::BoostDesc::BINBOOST_128;
  } else if (descriptorType.compare("BINBOOST_256") == 0){
    descriptor_type = cv::xfeatures2d::BoostDesc::BINBOOST_256;
  }

#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  mBoost = cv::xfeatures2d::BoostDesc::create(descriptor_type,
                                              BoostProperties::useOrientation(),
                                              static_cast<float>(BoostProperties::scaleFactor()));
#endif

}

void BoostDescriptor::reset()
{
  BoostProperties::reset();
  update();
}

void BoostDescriptor::setDescriptorType(const QString &descriptorType)
{
  BoostProperties::setDescriptorType(descriptorType);
  update();
}

void BoostDescriptor::setUseOrientation(bool useOrientation)
{
  BoostProperties::setUseOrientation(useOrientation);
  update();
}

void BoostDescriptor::setScaleFactor(double scaleFactor)
{
  BoostProperties::setScaleFactor(scaleFactor);
  update();
}

bool BoostDescriptor::extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints, cv::Mat &descriptors)
{

#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  try {
    mBoost->compute(img, keyPoints, descriptors);
  } catch (cv::Exception &e) {
    msgError("BOOST Descriptor error: %s", e.what());
    return true;
  }

#  else
  QString msg("Boost Descriptor not supported in OpenCV ");
  msg.append(CV_VERSION);
  QByteArray ba = msg.toLocal8Bit();
  const char *cmsg = ba.data();
  TL_COMPILER_WARNING(cmsg)
#endif
  return false;
}




} // namespace photomatch


