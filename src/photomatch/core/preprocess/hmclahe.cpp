#include "hmclahe.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
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

QString HmclaheProperties::name() const
{
  return QString("HMCLAHE");
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
  this->setBlockSize(blockSize);
  this->setL(l);
  this->setPhi(phi);
}

HmclahePreprocess::~HmclahePreprocess()
{

}

bool HmclahePreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{

  try {

    cv::Mat temp;
    cv::Mat color_boost;
    if (imgIn.channels() >= 3) {
      cv::decolor(imgIn, temp, color_boost);
      color_boost.release();
    } else {
      imgIn.copyTo(temp);
    }

    pixkit::enhancement::local::Sundarami2011(temp, imgOut,
                                              cv::Size(HmclaheProperties::blockSize().width(),
                                              HmclaheProperties::blockSize().height()),
                                              static_cast<float>(HmclaheProperties::l()),
                                              static_cast<float>(HmclaheProperties::phi()));
    temp.release();

  } catch (cv::Exception &e) {
    msgError("HMCLAHE image preprocess error: %s", e.what());
    return true;
  }

  return false;
}

} // namespace photomatch







