#include "downsample.h"

namespace fme
{


DownsampleProperties::DownsampleProperties()
  : IDownsample(),
    mMaxSize(-1)
{
}

int DownsampleProperties::maxImageSize() const
{
  return mMaxSize;
}

void DownsampleProperties::setMaxImageSize(int size)
{
  mMaxSize = size;
}

void DownsampleProperties::reset()
{
  mMaxSize = -1;
}


/*----------------------------------------------------------------*/


DownsamplePreprocess::DownsamplePreprocess()
  : DownsampleProperties(),
    ImageProcess()
{

}

DownsamplePreprocess::DownsamplePreprocess(int size)
  : DownsampleProperties(),
    ImageProcess()
{
  setMaxImageSize(size);
}

DownsamplePreprocess::~DownsamplePreprocess()
{

}

void DownsamplePreprocess::reset()
{
  DownsampleProperties::reset();
}

void DownsamplePreprocess::setMaxImageSize(int size)
{
  DownsampleProperties::setMaxImageSize(size);
}

cv::Mat DownsamplePreprocess::process(const cv::Mat &img)
{
  cv::Mat img_out;

  return img_out;
}

} // namespace fme



