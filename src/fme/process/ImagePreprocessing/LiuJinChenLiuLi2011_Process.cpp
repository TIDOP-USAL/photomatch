#include "LiuJinChenLiuLi2011_Process.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

LiuJinChenLiuLi2011_Process::LiuJinChenLiuLi2011_Process(cv::Mat& cvImg_Left, cv::Mat& cvImg_Right, const cv::Size &blockSize, const QDir &outputDir)
  : mCvImg_left(cvImg_Left),
    mCvImg_right(cvImg_Right),
    mBlockSize(blockSize),
    mOutputDir(outputDir)
{

}

void LiuJinChenLiuLi2011_Process::run()
{

  cv::Mat color_boost;

  if (mCvImg_left.channels() >= 3) {
    cv::decolor(mCvImg_left, mCvImg_left, color_boost);
  }
  if (mCvImg_right.channels() >= 3) {
    cv::decolor(mCvImg_right, mCvImg_right, color_boost);
  }

  cv::Mat tmpLeft;
  cv::Mat tmpRight;
  pixkit::enhancement::local::LiuJinChenLiuLi2011(mCvImg_left, tmpLeft, mBlockSize);
  pixkit::enhancement::local::LiuJinChenLiuLi2011(mCvImg_right, tmpRight, mBlockSize);
  tmpLeft.copyTo(mCvImg_left);
  tmpRight.copyTo(mCvImg_right);

  cv::imwrite(mOutputDir.absoluteFilePath("leftPreprocessed.png").toStdString(), mCvImg_left);
  cv::imwrite(mOutputDir.absoluteFilePath("rightPreprocessed.png").toStdString(), mCvImg_right);

}