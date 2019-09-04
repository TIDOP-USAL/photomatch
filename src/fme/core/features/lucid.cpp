#include "lucid.h"

namespace fme
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

cv::Mat LucidDescriptor::extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints)
{
  cv::Mat descriptors;
  mLUCID->compute(img, keyPoints, descriptors);
  return descriptors;
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

/*----------------------------------------------------------------*/

} // namespace fme
