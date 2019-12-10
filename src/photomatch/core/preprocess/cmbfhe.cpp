#include "cmbfhe.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


CmbfheProperties::CmbfheProperties()
  : ICmbfhe(),
    mBlockSize(11,11)
{}

CmbfheProperties::CmbfheProperties(const CmbfheProperties &cmbfheProperties)
  : ICmbfhe(),
    mBlockSize(cmbfheProperties.blockSize())
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

QString CmbfheProperties::name() const
{
  return QString("CMBFHE");
}


/*----------------------------------------------------------------*/


CmbfhePreprocess::CmbfhePreprocess()
  : CmbfheProperties(),
    ImageProcess()
{
}

CmbfhePreprocess::CmbfhePreprocess(const CmbfhePreprocess &cmbfhePreprocess)
  : CmbfheProperties(cmbfhePreprocess),
    ImageProcess()
{
}

CmbfhePreprocess::CmbfhePreprocess(const QSize &blockSize)
  : CmbfheProperties(),
    ImageProcess()
{
  this->setBlockSize(blockSize);
}

CmbfhePreprocess::~CmbfhePreprocess()
{

}

bool CmbfhePreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
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

    pixkit::enhancement::local::LambertiMontrucchioSanna2006(temp, imgOut,
                                                             cv::Size(CmbfheProperties::blockSize().width(),
                                                                      CmbfheProperties::blockSize().height()),
                                                             cv::Size(44,44));

  } catch (cv::Exception &e) {
    msgError("CMBFHE image preprocess error: %s", e.what());
    return true;
  }

  return false;
}

} // namespace photomatch







