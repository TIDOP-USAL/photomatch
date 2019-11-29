#include "msrcp.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
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

bool MsrcpPreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{

  try {

    cv::Mat tmp;
    if (imgIn.channels() == 1)
      cv::cvtColor(imgIn, tmp, cv::COLOR_GRAY2BGR);
    else
      imgIn.copyTo(tmp);

    cv::Mat tmp2;
    pixkit::enhancement::local::MSRCP2014(tmp, tmp2);
    tmp.release();

    if (imgIn.channels() >= 3){
      cv::Mat color_boost;
      cv::decolor(tmp2, imgOut, color_boost);
      color_boost.release();
    } else {
      cv::cvtColor(tmp2, imgOut, cv::COLOR_BGR2GRAY);
    }
    tmp2.release();

  } catch (cv::Exception &e) {
    msgError("MSRCP Image preprocess error: %s", e.what());
    return true;
  }

  return false;
}


} // namespace photomatch







