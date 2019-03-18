#include "ContrastPreservingDecolorization__Process.h"

ContrastPreservingDecolorization__Process::ContrastPreservingDecolorization__Process(cv::Mat& cvImg_Left,cv::Mat& cvImg_Right, QDir outputDir):
    mCvImg_left(cvImg_Left),mCvImg_right(cvImg_Right),mOutputDir(outputDir)
{

}
void ContrastPreservingDecolorization__Process::run(){

        cv::Mat color_boost;
        cv::decolor(mCvImg_left, mCvImg_left, color_boost);
        cv::decolor(mCvImg_right, mCvImg_right, color_boost);
        cv::imwrite(mOutputDir.absoluteFilePath("leftPreprocessed.png").toStdString(), mCvImg_left);
        cv::imwrite(mOutputDir.absoluteFilePath("rightPreprocessed.png").toStdString(), mCvImg_right);

}
