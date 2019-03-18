#include "YuBajaj2004_Process.h"
#include <pixkit-image.hpp>

YuBajaj2004_Process::YuBajaj2004_Process(cv::Mat& cvImg_Left,cv::Mat& cvImg_Right,cv::Size blockSize,float c,bool anisotropicMode,float r, QDir outputDir):
    mCvImg_left(cvImg_Left),mCvImg_right(cvImg_Right),mBlockSize(blockSize),mC(c),mAnisotropicMode(anisotropicMode),mR(r),mOutputDir(outputDir)
{

}

void YuBajaj2004_Process::run(){

        cv::Mat color_boost;
        cv::decolor(mCvImg_left, mCvImg_left, color_boost);
        cv::decolor(mCvImg_right, mCvImg_right, color_boost);
        cv::Mat tmpLeft;
        cv::Mat tmpRight;

        pixkit::enhancement::local::YuBajaj2004(mCvImg_left,tmpLeft,mBlockSize.height,mBlockSize.width,mC,mAnisotropicMode,mR);
        pixkit::enhancement::local::YuBajaj2004(mCvImg_right,tmpRight,mBlockSize.height,mBlockSize.width,mC,mAnisotropicMode,mR);
        tmpLeft.copyTo(mCvImg_left);
        tmpRight.copyTo(mCvImg_right);
        cv::imwrite(mOutputDir.absoluteFilePath("leftPreprocessed.png").toStdString(), mCvImg_left);
        cv::imwrite(mOutputDir.absoluteFilePath("rightPreprocessed.png").toStdString(), mCvImg_right);

}
