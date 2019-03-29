#include "MaryKim2008_Process.h"
#include <pixkit-image.hpp>

MaryKim2008_Process::MaryKim2008_Process(cv::Mat& cvImg_Left, cv::Mat& cvImg_Right, int morD, int r, QDir outputDir):
    mCvImg_left(cvImg_Left),
    mCvImg_right(cvImg_Right),
    mMorD(morD),mR(r),
    mOutputDir(outputDir)
{

}

void MaryKim2008_Process::run()
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
    pixkit::enhancement::global::MaryKim2008(mCvImg_left,tmpLeft,mMorD,mR);
    pixkit::enhancement::global::MaryKim2008(mCvImg_right,tmpRight,mMorD,mR);
    tmpLeft.copyTo(mCvImg_left);
    tmpRight.copyTo(mCvImg_right);

    cv::imwrite(mOutputDir.absoluteFilePath("leftPreprocessed.png").toStdString(), mCvImg_left);
    cv::imwrite(mOutputDir.absoluteFilePath("rightPreprocessed.png").toStdString(), mCvImg_right);

}
