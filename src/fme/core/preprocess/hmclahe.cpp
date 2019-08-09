#include "hmclahe.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
{


HmclaheProperties::HmclaheProperties()
  : IHmclahe(),
    mBlockSize(17,17),
    mL(0.03),
    mPhi(0.5)
{
}

HmclaheProperties::~HmclaheProperties()
{}

QSize HmclaheProperties::blockSize() const
{
  return mBlockSize;
}

void HmclaheProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

double HmclaheProperties::l() const
{
  return mL;
}

void HmclaheProperties::setL(double l)
{
  mL = l;
}

double HmclaheProperties::phi() const
{
  return mPhi;
}

void HmclaheProperties::setPhi(double phi)
{
  mPhi = phi;
}

void HmclaheProperties::reset()
{
  mBlockSize = QSize(17, 17);
  mL = 0.03;
  mPhi = 0.5;
}


/*----------------------------------------------------------------*/


HmclahePreprocess::HmclahePreprocess()
  : HmclaheProperties(),
    ImageProcess()
{
}

HmclahePreprocess::HmclahePreprocess(const QSize &blockSize, double l, double phi)
  : HmclaheProperties(),
    ImageProcess()
{
  setBlockSize(blockSize);
  setL(l);
  setPhi(phi);
}

HmclahePreprocess::~HmclahePreprocess()
{

}

void HmclahePreprocess::reset()
{
  HmclaheProperties::reset();
}

void HmclahePreprocess::setBlockSize(const QSize &blockSize)
{
  HmclaheProperties::setBlockSize(blockSize);
}

void HmclahePreprocess::setL(double l)
{
  HmclaheProperties::setL(l);
}

void HmclahePreprocess::setPhi(double phi)
{
  HmclaheProperties::setPhi(phi);
}

cv::Mat HmclahePreprocess::process(const cv::Mat &img)
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
  pixkit::enhancement::local::Sundarami2011(temp, img_out,
                                            cv::Size(HmclaheProperties::blockSize().width(),
                                            HmclaheProperties::blockSize().height()),
                                            static_cast<float>(HmclaheProperties::l()),
                                            static_cast<float>(HmclaheProperties::phi()));
  temp.release();
  return img_out;
}

} // namespace fme







