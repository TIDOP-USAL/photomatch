#include "LCE_BSESCS2014_Process.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

LCE_BSESCS2014_Process::LCE_BSESCS2014_Process(cv::Mat &cvImg_Left, cv::Mat &cvImg_Right, 
                                               const cv::Size &blockSize, const QDir &outputDir)
  : mCvImg_left(cvImg_Left),
    mCvImg_right(cvImg_Right),
    mBlockSize(blockSize),
    mOutputDir(outputDir)
{

}

void LCE_BSESCS2014_Process::run()
{

  cv::Mat color_boost;
  if (mCvImg_left.channels() >= 3) {
    cv::decolor(mCvImg_left, mCvImg_left, color_boost);
  }
  if (mCvImg_right.channels() >= 3) {
    cv::decolor(mCvImg_right, mCvImg_right, color_boost);
  }

  pixkit::enhancement::local::LCE_BSESCS2014(mCvImg_left, mCvImg_left, mBlockSize);
  pixkit::enhancement::local::LCE_BSESCS2014(mCvImg_right, mCvImg_right, mBlockSize);

  cv::imwrite(mOutputDir.absoluteFilePath("leftPreprocessed.png").toStdString(), mCvImg_left);
  cv::imwrite(mOutputDir.absoluteFilePath("rightPreprocessed.png").toStdString(), mCvImg_right);

}
