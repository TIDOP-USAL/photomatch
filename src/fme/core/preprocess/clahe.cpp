#include "clahe.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
{


ClaheProperties::ClaheProperties()
  : IClahe(),
    mClipLimit(40.),
    mTilesGridSize(QSize(8, 8))
{
}

double ClaheProperties::clipLimit() const
{
  return mClipLimit;
}

void ClaheProperties::setClipLimit(double clipLimit)
{
  mClipLimit = clipLimit;
}

QSize ClaheProperties::tilesGridSize() const
{
  return mTilesGridSize;
}

void ClaheProperties::setTilesGridSize(const QSize &tilesGridSize)
{
  mTilesGridSize = tilesGridSize;
}

void ClaheProperties::reset()
{
  mClipLimit = 40.0;
  mTilesGridSize = QSize(8, 8);
}


/*----------------------------------------------------------------*/


ClahePreprocess::ClahePreprocess()
  : ClaheProperties(),
    ImageProcess(),
    mCvClahe(cv::createCLAHE())
{
  mCvClahe->setClipLimit(ClaheProperties::clipLimit());
  mCvClahe->setTilesGridSize(cv::Size(ClaheProperties::tilesGridSize().width(), ClaheProperties::tilesGridSize().height()));
}

ClahePreprocess::ClahePreprocess(double clipLimit, const QSize &tilesGridSize)
  : ClaheProperties(),
    ImageProcess(),
    mCvClahe(cv::createCLAHE())
{
  setClipLimit(clipLimit);
  setTilesGridSize(tilesGridSize);
}

ClahePreprocess::~ClahePreprocess()
{

}

void ClahePreprocess::reset()
{
  ClaheProperties::reset();
  mCvClahe->setClipLimit(ClaheProperties::clipLimit());
  mCvClahe->setTilesGridSize(cv::Size(ClaheProperties::tilesGridSize().width(), ClaheProperties::tilesGridSize().height()));
}

void ClahePreprocess::setClipLimit(double clipLimit)
{
  ClaheProperties::setClipLimit(clipLimit);
  mCvClahe->setClipLimit(clipLimit);
}

void ClahePreprocess::setTilesGridSize(const QSize &tilesGridSize)
{
  ClaheProperties::setTilesGridSize(tilesGridSize);
  mCvClahe->setTilesGridSize(cv::Size(tilesGridSize.width(), tilesGridSize.height()));
}

cv::Mat ClahePreprocess::process(const cv::Mat &img)
{
  cv::Mat img_out;
  cv::Mat color_boost;
  if (img.channels() >= 3) {
    cv::decolor(img, img_out, color_boost);
    color_boost.release();
  } else {
    img.copyTo(img_out);
  }

  mCvClahe->apply(img_out, img_out);

  return img_out;
}

} // namespace fme







