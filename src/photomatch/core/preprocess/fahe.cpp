#include "fahe.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


FaheProperties::FaheProperties()
  : IFahe(),
    mBlockSize(QSize(11, 11))
{
}

QSize FaheProperties::blockSize() const
{
  return mBlockSize;
}

void FaheProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void FaheProperties::reset()
{
  mBlockSize = QSize(11, 11);
}

QString FaheProperties::name() const
{
  return QString("FAHE");
}


/*----------------------------------------------------------------*/


FahePreprocess::FahePreprocess()
  : FaheProperties(),
    ImageProcess()
{
}

FahePreprocess::FahePreprocess(const QSize &blockSize)
  : FaheProperties(),
    ImageProcess()
{
  this->setBlockSize(blockSize);
}

FahePreprocess::~FahePreprocess()
{

}

cv::Mat FahePreprocess::process(const cv::Mat &img)
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
  pixkit::enhancement::local::FAHE2006(temp, img_out,
                                       cv::Size(FaheProperties::blockSize().width(),
                                                FaheProperties::blockSize().height()));
  temp.release();
  return img_out;
}

} // namespace photomatch







