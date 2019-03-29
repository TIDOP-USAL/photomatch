#include "LambertiMontrucchioSanna2006_Process.h"
#include <pixkit-image.hpp>

LambertiMontrucchioSanna2006_Process::LambertiMontrucchioSanna2006_Process(cv::Mat& cvImg_Left, cv::Mat& cvImg_Right, cv::Size blockSize, cv::Size blockRegions, QDir outputDir):
    mCvImg_left(cvImg_Left),
    mCvImg_right(cvImg_Right),
    mBlockSize(blockSize),
    mBlockRegions(blockRegions),
    mOutputDir(outputDir)
{

}

void LambertiMontrucchioSanna2006_Process::run()
{

    cv::Mat color_boost;
    if (mCvImg_left.channels() >= 3){
        cv::decolor(mCvImg_left, mCvImg_left, color_boost);
    }
    if (mCvImg_right.channels() >= 3){
        cv::decolor(mCvImg_right, mCvImg_right, color_boost);
    }

    cv::Mat tmpLeft;
    cv::Mat tmpRight;
    pixkit::enhancement::local::LambertiMontrucchioSanna2006(mCvImg_left,tmpLeft,mBlockSize,mBlockRegions);
    pixkit::enhancement::local::LambertiMontrucchioSanna2006(mCvImg_right,tmpRight,mBlockSize,mBlockRegions);
    tmpLeft.copyTo(mCvImg_left);
    tmpRight.copyTo(mCvImg_right);

    cv::imwrite(mOutputDir.absoluteFilePath("leftPreprocessed.png").toStdString(), mCvImg_left);
    cv::imwrite(mOutputDir.absoluteFilePath("rightPreprocessed.png").toStdString(), mCvImg_right);

}
