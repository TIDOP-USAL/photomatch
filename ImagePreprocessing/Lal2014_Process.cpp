#include "Lal2014_Process.h"
#include <pixkit-image.hpp>

Lal2014_Process::Lal2014_Process(cv::Mat& cvImg_Left,cv::Mat& cvImg_Right,cv::Size blockSize, QDir outputDir):
    mCvImg_left(cvImg_Left),mCvImg_right(cvImg_Right),mBlockSize(blockSize),mOutputDir(outputDir)
{

}

void Lal2014_Process::run(){

        cv::Mat color_boost;
        cv::decolor(mCvImg_left, mCvImg_left, color_boost);
        cv::decolor(mCvImg_right, mCvImg_right, color_boost);

        pixkit::enhancement::local::Lal2014(mCvImg_left,mCvImg_left,mBlockSize);
        pixkit::enhancement::local::Lal2014(mCvImg_right,mCvImg_right,mBlockSize);
        cv::imwrite(mOutputDir.absoluteFilePath("leftPreprocessed.png").toStdString(), mCvImg_left);
        cv::imwrite(mOutputDir.absoluteFilePath("rightPreprocessed.png").toStdString(), mCvImg_right);

}
