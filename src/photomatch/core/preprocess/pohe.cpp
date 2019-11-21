#include "pohe.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
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

bool PohePreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{
  try {

    cv::Mat tmp;
    if (imgIn.channels() == 1)
      cv::cvtColor(imgIn, tmp, cv::COLOR_GRAY2BGR);
    else
      imgIn.copyTo(tmp);

    pixkit::enhancement::local::MSRCP2014(tmp, imgOut);
    tmp.release();

    if (imgIn.channels() >= 3) {
      cv::Mat color_boost;
      cv::decolor(imgOut, imgOut, color_boost);
      color_boost.release();
    } else {
      cv::cvtColor(imgOut, imgOut, cv::COLOR_BGR2GRAY);
    }

  } catch (cv::Exception &e) {
    msgError("POHE Image preprocess error: %s", e.what());
    return true;
  }

  return false;
}


} // namespace photomatch

