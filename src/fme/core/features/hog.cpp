#include "hog.h"

namespace fme
{


HogProperties::HogProperties()
  : IHog(),
    mWinSize(128,64),
    mBlockSize(16,16),
    mBlockStride(8,8),
    mCellSize(8,8),
    mNbins(9),
    mDerivAperture(1)
{}

HogProperties::~HogProperties()
{

}

QSize HogProperties::winSize() const
{
  return mWinSize;
}

QSize HogProperties::blockSize() const
{
  return mBlockSize;
}

QSize HogProperties::blockStride() const
{
  return mBlockStride;
}

QSize HogProperties::cellSize() const
{
  return mCellSize;
}

int HogProperties::nbins() const
{
  return mNbins;
}

int HogProperties::derivAperture() const
{
  return mDerivAperture;
}

void HogProperties::setWinSize(const QSize &winSize)
{
  mWinSize = winSize;
}

void HogProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void HogProperties::setBlockStride(const QSize &blockStride)
{
  mBlockStride = blockStride;
}

void HogProperties::setCellSize(const QSize &cellSize)
{
  mCellSize = cellSize;
}

void HogProperties::setNbins(int nbins)
{
  mNbins = nbins;
}

void HogProperties::setDerivAperture(int derivAperture)
{
  mDerivAperture = derivAperture;
}

void HogProperties::reset()
{
  mWinSize = QSize(128,64);
  mBlockSize = QSize(16,16);
  mBlockStride = QSize(8,8);
  mCellSize = QSize(8,8);
  mNbins = 9;
  mDerivAperture = 1;
}


/*----------------------------------------------------------------*/


HogDescriptor::HogDescriptor()
  : HogProperties(),
    DescriptorExtractor()
{
  update();
}

HogDescriptor::HogDescriptor(QSize winSize,
                             QSize blockSize,
                             QSize blockStride,
                             QSize cellSize,
                             int nbins,
                             int derivAperture)
  : HogProperties(),
    DescriptorExtractor()
{
  HogProperties::setWinSize(winSize);
  HogProperties::setBlockSize(blockSize);
  HogProperties::setBlockStride(blockStride);
  HogProperties::setCellSize(cellSize);
  HogProperties::setNbins(nbins);
  HogProperties::setDerivAperture(derivAperture);
  update();
}

HogDescriptor::~HogDescriptor()
{

}

void HogDescriptor::update()
{
}

cv::Mat HogDescriptor::extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints)
{
  cv::Mat descriptors;
  //mFREAK->compute(img, keyPoints, descriptors);
  return descriptors;
}

void fme::HogDescriptor::setWinSize(const QSize &winSize)
{
  HogProperties::setWinSize(winSize);
}

void HogDescriptor::setBlockSize(const QSize &blockSize)
{
  HogProperties::setBlockSize(blockSize);
}

void HogDescriptor::setBlockStride(const QSize &blockStride)
{
  HogProperties::setBlockStride(blockStride);
}

void HogDescriptor::setCellSize(const QSize &cellSize)
{
  HogProperties::setCellSize(cellSize);
}

void HogDescriptor::setNbins(int nbins)
{
  HogProperties::setNbins(nbins);
}

void HogDescriptor::setDerivAperture(int derivAperture)
{
  HogProperties::setDerivAperture(derivAperture);
}

void HogDescriptor::reset()
{
  HogProperties::reset();
  update();
}


/*----------------------------------------------------------------*/

} // namespace fme
