#include "noshp.h"

#include <tidop/core/messages.h>

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

bool NoshpPreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{

  try {

    cv::Mat  temp;
    if (imgIn.channels() >= 3) {
      cv::Mat color_boost;
      cv::decolor(imgIn, temp, color_boost);
      color_boost.release();
    } else {
      imgIn.copyTo(temp);
    }

    pixkit::enhancement::local::LiuJinChenLiuLi2011(temp, imgOut,
                                                    cv::Size(NoshpProperties::blockSize().width(),
                                                             NoshpProperties::blockSize().height()));
    temp.release();

  } catch (cv::Exception &e) {
    msgError("NOSHP Image preprocess error: %s", e.what());
    return true;
  }


  return false;
}


} // namespace photomatch







