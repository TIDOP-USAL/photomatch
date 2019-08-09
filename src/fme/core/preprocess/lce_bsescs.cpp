#include "lce_bsescs.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
{


LceBsescsProperties::LceBsescsProperties()
  : ILceBsescs(),
    mBlockSize(17,17)
{}

LceBsescsProperties::~LceBsescsProperties()
{
}

QSize LceBsescsProperties::blockSize() const
{
  return mBlockSize;
}

void LceBsescsProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void LceBsescsProperties::reset()
{
  mBlockSize = QSize(33, 33);
}


/*----------------------------------------------------------------*/


LceBsescsPreprocess::LceBsescsPreprocess()
  : LceBsescsProperties(),
    ImageProcess()
{
}

LceBsescsPreprocess::LceBsescsPreprocess(const QSize &blockSize)
  : LceBsescsProperties(),
    ImageProcess()
{
  setBlockSize(blockSize);
}

LceBsescsPreprocess::~LceBsescsPreprocess()
{

}

void LceBsescsPreprocess::reset()
{
  LceBsescsProperties::reset();
}

void LceBsescsPreprocess::setBlockSize(const QSize &blockSize)
{
  LceBsescsProperties::setBlockSize(blockSize);
}

cv::Mat LceBsescsPreprocess::process(const cv::Mat &img)
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
  pixkit::enhancement::local::LCE_BSESCS2014(temp, img_out, cv::Size(LceBsescsProperties::blockSize().width(), LceBsescsProperties::blockSize().height()));
  temp.release();

  return img_out;
}

} // namespace fme







