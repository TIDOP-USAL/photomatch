#include "dhe.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


DheProperties::DheProperties()
  : IDhe(),
    mX(1)
{
}

int DheProperties::x() const
{
  return mX;
}

void DheProperties::setX(int x)
{
  mX = x;
}

void DheProperties::reset()
{
  mX = 1;
}

QString DheProperties::name() const
{
  return QString("DHE");
}


/*----------------------------------------------------------------*/


DhePreprocess::DhePreprocess()
  : DheProperties(),
    ImageProcess()
{
}

DhePreprocess::DhePreprocess(int x)
  : DheProperties(),
    ImageProcess()
{
  this->setX(x);
}

DhePreprocess::~DhePreprocess()
{

}

bool DhePreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{

  try {

    cv::Mat temp;
    if (imgIn.channels() >= 3) {
      cv::Mat color_boost;
      cv::decolor(imgIn, temp, color_boost);
      color_boost.release();
    } else {
      imgIn.copyTo(temp);
    }

    pixkit::enhancement::global::WadudKabirDewanChae2007(temp, imgOut, DheProperties::x());
    temp.release();

  } catch (cv::Exception &e) {
    msgError("DHE image preprocess error: %s", e.what());
    return true;
  }

  return false;
}

} // namespace photomatch







