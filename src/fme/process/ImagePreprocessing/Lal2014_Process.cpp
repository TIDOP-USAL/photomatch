#include "Lal2014_Process.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

Lal2014_Process::Lal2014_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, const cv::Size &blockSize, const QDir &outputDir)
  : mCvImg_left(cvImg_Left),
    mCvImg_right(cvImg_Right),
    mBlockSize(blockSize),
    mOutputDir(outputDir)
{

}

void Lal2014_Process::run()
{

  cv::Mat color_boost;

  cv::Mat tmpLeft;
  cv::Mat tmpRight;
  if (mCvImg_left.channels() == 1)  cv::cvtColor(mCvImg_left, tmpLeft, cv::COLOR_GRAY2BGR);
  else mCvImg_left.copyTo(tmpLeft);
  if (mCvImg_right.channels() == 1) cv::cvtColor(mCvImg_right, tmpRight, cv::COLOR_GRAY2BGR);
  else mCvImg_left.copyTo(tmpRight);

  pixkit::enhancement::local::Lal2014(tmpLeft, tmpLeft, mBlockSize);
  pixkit::enhancement::local::Lal2014(tmpRight, tmpRight, mBlockSize);

  if (mCvImg_left.channels() >= 3) {
    cv::decolor(tmpLeft, mCvImg_left, color_boost);
  } else {
    cv::cvtColor(tmpLeft, mCvImg_left, cv::COLOR_BGR2GRAY);
  }

  if (mCvImg_right.channels() >= 3) {
    cv::decolor(tmpRight, mCvImg_right, color_boost);
  } else {
    cv::cvtColor(tmpRight, mCvImg_right, cv::COLOR_BGR2GRAY);
  }

  cv::imwrite(mOutputDir.absoluteFilePath("leftPreprocessed.png").toStdString(), mCvImg_left);
  cv::imwrite(mOutputDir.absoluteFilePath("rightPreprocessed.png").toStdString(), mCvImg_right);

}
