#include "Downsample_Process.h"

#include <opencv2/imgproc.hpp>

Downsample_Process::Downsample_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right,  int resolution)
  : mCvImg_left(cvImg_Left),
    mCvImg_right(cvImg_Right),
    mResolution(resolution)
{

}

Downsample_Process::~Downsample_Process()
{
}

void Downsample_Process::run()
{

  cv::Size size;

  if (mCvImg_left.cols > mResolution || mCvImg_left.rows > mResolution) {
    if (mCvImg_left.cols >= mCvImg_left.rows) {
      size.width = mResolution;
      size.height = mCvImg_left.rows*((float)mResolution / mCvImg_left.cols);
    }
    else {
      size.height = mResolution;
      size.width = mCvImg_left.cols*(mResolution / mCvImg_left.rows);
    }
    cv::resize(mCvImg_left, mCvImg_left, size);
  }

  if (mCvImg_right.cols > mResolution || mCvImg_right.rows > mResolution) {

    if (mCvImg_right.cols >= mCvImg_right.rows) {
      size.width = mResolution;
      size.height = mCvImg_right.rows*((float)mResolution / mCvImg_right.cols);
    }
    else {
      size.height = mResolution;
      size.width = mCvImg_right.cols*(mResolution / mCvImg_right.rows);
    }
    cv::resize(mCvImg_right, mCvImg_right, size);
  }
}
