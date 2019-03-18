#include "MSRCP2014_Process.h"
#include <pixkit-image.hpp>

MSRCP2014_Process::MSRCP2014_Process(cv::Mat& cvImg_Left,cv::Mat& cvImg_Right, QDir outputDir):
    mCvImg_left(cvImg_Left),mCvImg_right(cvImg_Right),mOutputDir(outputDir)
{

}
void MSRCP2014_Process::run(){

        cv::Mat color_boost;

        cv::Mat tmpLeft;
        cv::Mat tmpRight;
        pixkit::enhancement::local::MSRCP2014(mCvImg_left,tmpLeft);
        pixkit::enhancement::local::MSRCP2014(mCvImg_right,tmpRight);
        tmpLeft.copyTo(mCvImg_left);
        tmpRight.copyTo(mCvImg_right);

        cv::decolor(mCvImg_left, mCvImg_left, color_boost);
        cv::decolor(mCvImg_right, mCvImg_right, color_boost);
        cv::imwrite(mOutputDir.absoluteFilePath("leftPreprocessed.png").toStdString(), mCvImg_left);
        cv::imwrite(mOutputDir.absoluteFilePath("rightPreprocessed.png").toStdString(), mCvImg_right);

}
