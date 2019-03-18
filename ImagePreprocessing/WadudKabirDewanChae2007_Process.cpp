#include "WadudKabirDewanChae2007_Process.h"
#include <pixkit-image.hpp>

WadudKabirDewanChae2007_Process::WadudKabirDewanChae2007_Process(cv::Mat& cvImg_Left,cv::Mat& cvImg_Right,int power, QDir outputDir):
    mCvImg_left(cvImg_Left),mCvImg_right(cvImg_Right),mPower(power),mOutputDir(outputDir)
{

}

void WadudKabirDewanChae2007_Process::run(){

        cv::Mat color_boost;
        cv::decolor(mCvImg_left, mCvImg_left, color_boost);
        cv::decolor(mCvImg_right, mCvImg_right, color_boost);
        cv::Mat tmpLeft;
        cv::Mat tmpRight;
        pixkit::enhancement::global::WadudKabirDewanChae2007(mCvImg_left,tmpLeft,mPower);
        pixkit::enhancement::global::WadudKabirDewanChae2007(mCvImg_right,tmpRight,mPower);
        tmpLeft.copyTo(mCvImg_left);
        tmpRight.copyTo(mCvImg_right);
        cv::imwrite(mOutputDir.absoluteFilePath("leftPreprocessed.png").toStdString(), mCvImg_left);
        cv::imwrite(mOutputDir.absoluteFilePath("rightPreprocessed.png").toStdString(), mCvImg_right);

}
