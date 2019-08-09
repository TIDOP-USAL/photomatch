#include "noshp.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
{


NoshpProperties::NoshpProperties()
  : INoshp(),
    mBlockSize(127, 127)
{
}

NoshpProperties::~NoshpProperties()
{

}

QSize NoshpProperties::blockSize() const
{
  return mBlockSize;
}

void NoshpProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void NoshpProperties::reset()
{
  mBlockSize = QSize(127, 127);
}


/*----------------------------------------------------------------*/


NoshpPreprocess::NoshpPreprocess()
  : NoshpProperties(),
    ImageProcess()
{
}

NoshpPreprocess::NoshpPreprocess(const QSize &blockSize)
  : NoshpProperties(),
    ImageProcess()
{
  setBlockSize(blockSize);
}

NoshpPreprocess::~NoshpPreprocess()
{

}

void NoshpPreprocess::reset()
{
  NoshpProperties::reset();
}

void NoshpPreprocess::setBlockSize(const QSize &blockSize)
{
  NoshpProperties::setBlockSize(blockSize);
}

cv::Mat NoshpPreprocess::process(const cv::Mat &img)
{
  cv::Mat color_boost;
  cv::Mat  temp;
  if (img.channels() >= 3) {
    cv::decolor(img, temp, color_boost);
    color_boost.release();
  } else {
    img.copyTo(temp);
  }

  cv::Mat out;
  pixkit::enhancement::local::LiuJinChenLiuLi2011(temp, out,
                                                  cv::Size(NoshpProperties::blockSize().width(),
                                                           NoshpProperties::blockSize().height()));
  temp.release();

  return out;
}


} // namespace fme







