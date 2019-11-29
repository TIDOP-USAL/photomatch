#include "lce_bsescs.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


LceBsescsProperties::LceBsescsProperties()
  : ILceBsescs(),
    mBlockSize(33, 33)
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

QString LceBsescsProperties::name() const
{
  return QString("LCE_BSESCS");
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
  this->setBlockSize(blockSize);
}

LceBsescsPreprocess::~LceBsescsPreprocess()
{

}

bool LceBsescsPreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
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

    pixkit::enhancement::local::LCE_BSESCS2014(temp, imgOut,
                                               cv::Size(LceBsescsProperties::blockSize().width(),
                                                        LceBsescsProperties::blockSize().height()));
    temp.release();

  } catch (cv::Exception &e) {
    msgError("LCE-BSESCS Image preprocess error: %s", e.what());
    return true;
  }

  return false;
}

} // namespace photomatch







