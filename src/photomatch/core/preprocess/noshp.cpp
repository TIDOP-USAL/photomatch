#include "noshp.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
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

QString NoshpProperties::name() const
{
  return QString("NOSHP");
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
  this->setBlockSize(blockSize);
}

NoshpPreprocess::~NoshpPreprocess()
{

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


} // namespace photomatch







