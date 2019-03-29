#include "Kimori2013_Process.h"
#include <pixkit-image.hpp>

Kimori2013_Process::Kimori2013_Process(cv::Mat& cvImg_Left,cv::Mat& cvImg_Right,cv::Size blockSize, QDir outputDir):
    mCvImg_left(cvImg_Left),
    mCvImg_right(cvImg_Right),
    mBlockSize(blockSize),
    mOutputDir(outputDir)
{

}

void Kimori2013_Process::run()
{

    cv::Mat color_boost;    
    
    cv::Mat tmpLeft;
    cv::Mat tmpRight;
    if (mCvImg_left.channels() >= 3){
        cv::decolor(mCvImg_left, tmpLeft, color_boost);
    } else {
        mCvImg_left.copyTo(tmpLeft);
    }
    if (mCvImg_right.channels() >= 3){
        cv::decolor(mCvImg_right, tmpRight, color_boost);
    } else {
        mCvImg_right.copyTo(tmpRight);
    }
    pixkit::enhancement::local::Kimori2013(tmpLeft, mCvImg_left, mBlockSize);
    pixkit::enhancement::local::Kimori2013(tmpRight, mCvImg_right, mBlockSize);

    cv::imwrite(mOutputDir.absoluteFilePath("leftPreprocessed.png").toStdString(), mCvImg_left);
    cv::imwrite(mOutputDir.absoluteFilePath("rightPreprocessed.png").toStdString(), mCvImg_right);

}
