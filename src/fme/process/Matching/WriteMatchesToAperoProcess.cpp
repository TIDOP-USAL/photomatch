#include "WriteMatchesToAperoProcess.h"

#include <QFile>
#include <QTextStream>

WriteMatchesToAperoProcess::WriteMatchesToAperoProcess(QString filename,std::vector<cv::KeyPoint> &cvkeyLeft,std::vector<cv::KeyPoint> &cvkeyRight,std::vector<cv::DMatch> &cvMatches):
    mFileName(filename),
    mCvMatches(cvMatches),
    mCvKeyLeft(cvkeyLeft),
    mCvKeyRight(cvkeyRight)
{

}

WriteMatchesToAperoProcess::~WriteMatchesToAperoProcess()
{

}

void WriteMatchesToAperoProcess::run()
{
  QFile outputFile(mFileName);
  outputFile.open(QIODevice::ReadWrite | QIODevice::Append);

  QTextStream outStream(&outputFile);

  foreach(cv::DMatch match, mCvMatches) {
    outStream << QString::number(mCvKeyLeft.at(match.queryIdx).pt.x) << " " << QString::number(mCvKeyLeft.at(match.queryIdx).pt.y) << " " << QString::number(mCvKeyRight.at(match.trainIdx).pt.x) << " " << QString::number(mCvKeyRight.at(match.trainIdx).pt.y) << "\n";
  }

  outputFile.close();
}