#include "MSRCP2014_Process.h"
#include <pixkit-image.hpp>

MSRCP2014_Process::MSRCP2014_Process(cv::Mat& cvImg_Left,cv::Mat& cvImg_Right, QDir outputDir):
    mCvImg_left(cvImg_Left),
    mCvImg_right(cvImg_Right),
    mOutputDir(outputDir)
{

}

void MSRCP2014_Process::run()
{

    cv::Mat color_boost;

    cv::Mat tmpLeft;
    cv::Mat tmpRight;
    if (mCvImg_left.channels() == 1)  cv::cvtColor(mCvImg_left, tmpLeft, cv::COLOR_GRAY2BGR);
    else mCvImg_left.copyTo(tmpLeft);
    if (mCvImg_right.channels() == 1) cv::cvtColor(mCvImg_right, tmpRight, cv::COLOR_GRAY2BGR);
    else mCvImg_right.copyTo(tmpRight);

    cv::Mat tmpLeft2;
    cv::Mat tmpRight2;
    pixkit::enhancement::local::MSRCP2014(tmpLeft,tmpLeft2);
    pixkit::enhancement::local::MSRCP2014(tmpRight, tmpRight2);

    if (mCvImg_left.channels() >= 3){
        cv::decolor(tmpLeft2, mCvImg_left, color_boost);
    } else {
        cv::cvtColor(tmpLeft2, mCvImg_left, cv::COLOR_BGR2GRAY);
    }
    if (mCvImg_right.channels() >= 3){
        cv::decolor(tmpRight2, mCvImg_right, color_boost);
    } else {
        cv::cvtColor(tmpRight2, mCvImg_right, cv::COLOR_BGR2GRAY);
    }

    cv::imwrite(mOutputDir.absoluteFilePath("leftPreprocessed.png").toStdString(), mCvImg_left);
    cv::imwrite(mOutputDir.absoluteFilePath("rightPreprocessed.png").toStdString(), mCvImg_right);

}
