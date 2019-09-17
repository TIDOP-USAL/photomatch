#include "msrcp.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
{


MsrcpProperties::MsrcpProperties()
  : IMsrcp(),
    mSmallScale(10.),
    mMidScale(100.),
    mLargeScale(220.)
{
}

MsrcpProperties::~MsrcpProperties()
{
}

double MsrcpProperties::smallScale() const
{
  return mSmallScale;
}

void MsrcpProperties::setSmallScale(double smallScale)
{
  mSmallScale = smallScale;
}

double MsrcpProperties::midScale() const
{
  return mMidScale;
}

void MsrcpProperties::setMidScale(double midScale)
{
  mMidScale = midScale;
}

double MsrcpProperties::largeScale() const
{
  return mLargeScale;
}

void MsrcpProperties::setLargeScale(double largeScale)
{
  mLargeScale = largeScale;
}

void MsrcpProperties::reset()
{
  mSmallScale = 10.;
  mMidScale = 100.;
  mLargeScale = 220.;
}

QString MsrcpProperties::name() const
{
  return QString("MSRCP");
}


/*----------------------------------------------------------------*/


MsrcpPreprocess::MsrcpPreprocess()
  : MsrcpProperties(),
    ImageProcess()
{
}

MsrcpPreprocess::MsrcpPreprocess(double smallScale, double midScale, double largeScale)
  : MsrcpProperties(),
    ImageProcess()
{
  TL_TODO("Ver por que aparecen estos parametros que MSRCP2014 no admite")
  this->setSmallScale(smallScale);
  this->setMidScale(midScale);
  this->setLargeScale(largeScale);
}

MsrcpPreprocess::~MsrcpPreprocess()
{

}

cv::Mat MsrcpPreprocess::process(const cv::Mat &img)
{
  cv::Mat tmp;
  if (img.channels() == 1) cv::cvtColor(img, tmp, cv::COLOR_GRAY2BGR);
  else img.copyTo(tmp);

  cv::Mat tmp2;
  pixkit::enhancement::local::MSRCP2014(tmp, tmp2);
  tmp.release();

  cv::Mat color_boost;
  cv::Mat out;
  if (img.channels() >= 3){
    cv::decolor(tmp2, out, color_boost);
    color_boost.release();
  } else {
    cv::cvtColor(tmp2, out, cv::COLOR_BGR2GRAY);
  }
  tmp2.release();

  return out;
}


} // namespace fme







