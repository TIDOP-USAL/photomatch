#ifndef WRITEMATCHESTOAPEROPROCESS_H
#define WRITEMATCHESTOAPEROPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"

class WriteMatchesToAperoProcess: public ProcessConcurrent
{
public:
    WriteMatchesToAperoProcess(QString filename,std::vector<cv::KeyPoint> &cvkeyLeft,std::vector<cv::KeyPoint> &cvkeyRight,std::vector<cv::DMatch> &cvMatches);
    ~WriteMatchesToAperoProcess();
    void run();
private:
    QString mFileName;
    std::vector<cv::DMatch> &mCvMatches;
    std::vector<cv::KeyPoint> &mCvKeyLeft, &mCvKeyRight;

};

#endif // WRITEMATCHESTOAPEROPROCESS_H
