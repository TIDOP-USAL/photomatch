#include "pohe.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
{


PoheProperties::PoheProperties()
  : IPohe(),
    mBlockSize(127, 127)
{
}

PoheProperties::~PoheProperties()
{

}

QSize PoheProperties::blockSize() const
{
  return mBlockSize;
}

void PoheProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void PoheProperties::reset()
{
  mBlockSize = QSize(127, 127);
}

QString PoheProperties::name() const
{
  return QString("POHE");
}


/*----------------------------------------------------------------*/


PohePreprocess::PohePreprocess()
  : PoheProperties(),
    ImageProcess()
{
}

PohePreprocess::PohePreprocess(const QSize &blockSize)
  : PoheProperties(),
    ImageProcess()
{
  this->setBlockSize(blockSize);
}

PohePreprocess::~PohePreprocess()
{

}

cv::Mat PohePreprocess::process(const cv::Mat &img)
{
  cv::Mat tmp;
  if (img.channels() == 1)  cv::cvtColor(img, tmp, cv::COLOR_GRAY2BGR);
  else img.copyTo(tmp);

  cv::Mat out;
  pixkit::enhancement::local::MSRCP2014(tmp, out);
  tmp.release();

  cv::Mat color_boost;
  if (img.channels() >= 3) {
    cv::decolor(out, out, color_boost);
    color_boost.release();
  } else {
    cv::cvtColor(out, out, cv::COLOR_BGR2GRAY);
  }

  return out;
}


} // namespace fme

