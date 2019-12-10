#include "fahe.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


FaheProperties::FaheProperties()
  : IFahe(),
    mBlockSize(QSize(11, 11))
{
}

FaheProperties::FaheProperties(const FaheProperties &faheProperties)
  : IFahe(),
    mBlockSize(faheProperties.mBlockSize)
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

FahePreprocess::FahePreprocess(const FahePreprocess &fahePreprocess)
  : FaheProperties(fahePreprocess),
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

bool FahePreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{

  try {

    cv::Mat temp;
    if (imgIn.channels() >= 3) {
      cv::Mat color_boost;
      cv::decolor(imgIn, temp, color_boost);
      color_boost.release();
    } else {
      imgIn.copyTo(temp);
    }

    pixkit::enhancement::local::FAHE2006(temp, imgOut,
                                         cv::Size(FaheProperties::blockSize().width(),
                                                  FaheProperties::blockSize().height()));
    temp.release();

  } catch (cv::Exception &e) {
    msgError("FAHE image preprocess error: %s", e.what());
    return true;
  }

  return false;
}

} // namespace photomatch







