#include "Cmbfhe.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
{


CmbfheProperties::CmbfheProperties()
  : ICmbfhe(),
    mBlockSize(11,11)
{}

QSize CmbfheProperties::blockSize() const
{
  return mBlockSize;
}

void CmbfheProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void CmbfheProperties::reset()
{
  mBlockSize = QSize(11,11);
}


/*----------------------------------------------------------------*/


CmbfhePreprocess::CmbfhePreprocess()
  : CmbfheProperties(),
    ImageProcess()
{
}

CmbfhePreprocess::CmbfhePreprocess(const QSize &blockSize)
  : CmbfheProperties(),
    ImageProcess()
{
  setBlockSize(blockSize);
}

CmbfhePreprocess::~CmbfhePreprocess()
{

}

void CmbfhePreprocess::reset()
{
  CmbfheProperties::reset();
}

void CmbfhePreprocess::setBlockSize(const QSize &blockSize)
{
  CmbfheProperties::setBlockSize(blockSize);
}

cv::Mat CmbfhePreprocess::process(const cv::Mat &img)
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
  pixkit::enhancement::local::LambertiMontrucchioSanna2006(temp, img_out, cv::Size(CmbfheProperties::blockSize().width(), CmbfheProperties::blockSize().height()), cv::Size(44,44));

  return img_out;
}

} // namespace fme







