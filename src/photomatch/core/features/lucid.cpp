#include "lucid.h"

#include <tidop/core/messages.h>


namespace photomatch
{


LucidProperties::LucidProperties()
  : ILucid(),
    mLucidKernel(1),
    mBlurKernel(2)
{}

LucidProperties::~LucidProperties()
{

}

int LucidProperties::lucidKernel() const
{
  return mLucidKernel;
}

int LucidProperties::blurKernel() const
{
  return mBlurKernel;
}

void LucidProperties::setLucidKernel(int lucidKernel)
{
  mLucidKernel = lucidKernel;
}

void LucidProperties::setBlurKernel(int blurKernel)
{
  mBlurKernel = blurKernel;
}

void LucidProperties::reset()
{
  mLucidKernel = 1;
  mBlurKernel = 2;
}

QString LucidProperties::name() const
{
  return QString("LUCID");
}


/*----------------------------------------------------------------*/


LucidDescriptor::LucidDescriptor()
  : LucidProperties(),
    DescriptorExtractor()
{
  update();
}

LucidDescriptor::LucidDescriptor(int lucidKernel, int blurKernel)
  : LucidProperties(),
    DescriptorExtractor()
{
  LucidProperties::setLucidKernel(lucidKernel);
  LucidProperties::setBlurKernel(blurKernel);
  update();
}

LucidDescriptor::~LucidDescriptor()
{

}

void LucidDescriptor::update()
{
  mLUCID = cv::xfeatures2d::LUCID::create(LucidProperties::lucidKernel(),
                                          LucidProperties::blurKernel());
}

bool LucidDescriptor::extract(const cv::Mat &img,
                              std::vector<cv::KeyPoint> &keyPoints,
                              cv::Mat &descriptors)
{

  try {
    mLUCID->compute(img, keyPoints, descriptors);
  } catch (cv::Exception &e) {
    msgError("LUCID Descriptor error: %s", e.what());
    return true;
  }

  return false;
}

void LucidDescriptor::setLucidKernel(int lucidKernel)
{
  LucidProperties::setLucidKernel(lucidKernel);
  update();
}

void LucidDescriptor::setBlurKernel(int blurKernel)
{
  LucidProperties::setBlurKernel(blurKernel);
  update();
}

void LucidDescriptor::reset()
{
  LucidProperties::reset();
  update();
}



} // namespace photomatch
