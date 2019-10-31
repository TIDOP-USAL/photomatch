#include "dhe.h"

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

cv::Mat DhePreprocess::process(const cv::Mat &img)
{
  cv::Mat temp;
  cv::Mat color_boost;
  if (img.channels() >= 3) {
    cv::decolor(img, temp, color_boost);
    color_boost.release();
  } else {
    img.copyTo(temp);
  }

  cv::Mat img_out;
  pixkit::enhancement::global::WadudKabirDewanChae2007(temp, img_out, DheProperties::x());
  temp.release();
  return img_out;
}

} // namespace photomatch







