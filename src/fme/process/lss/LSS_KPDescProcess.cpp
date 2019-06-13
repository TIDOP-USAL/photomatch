#include "LSS_KPDescProcess.h"

#include "fme/process/lss/lss.h"

#include <opencv2/imgproc.hpp>

using namespace cv;

LSS_KPDescProcess::LSS_KPDescProcess(cv::Mat &cvImg, std::vector<cv::KeyPoint> &cvkey,
                                     cv::Mat &cvDesc, const QString &imageName)
  : mImageName(imageName),
    mCvImg(cvImg),
    mCvkey(cvkey),
    mCvDesc(cvDesc)
{

}

LSS_KPDescProcess::~LSS_KPDescProcess()
{

}

void LSS_KPDescProcess::run()
{
  emit newStdData("Starting LSS key-point description for image " + mImageName);

  cv::Mat cvImg = mCvImg;
  //    cv::cvtColor(img_left,cvImg,CV_BGR2GRAY);
  cvImg.convertTo(cvImg, CV_32F);
  std::vector<cv::Mat_<float>> aux_des_left;
  LSS lssDetector;
  //    mCvkey.clear();

  std::vector<cv::KeyPoint> lss_key;

  for (int i = 0; i < mCvkey.size(); i++) {
    cv::Mat_<float> enter;
    int error = lssDetector.compute(mCvkey[i].pt, cvImg, enter);
    if (error == 1) {
      aux_des_left.push_back(enter);
      lss_key.push_back(mCvkey[i]);
    }
  }

  //    this->ui->key_lss_l->setText(QString::number(lss_key.size()));
  //    mCvDesc.resize(aux_des_left.size(),aux_des_left[0].rows*aux_des_left[0].cols);
  //    mCvDesc.convertTo(mCvDesc,CV_32FC1);
  cv::Mat tempDesc = cv::Mat(aux_des_left.size(), aux_des_left[0].rows*aux_des_left[0].cols, CV_32FC1);

  for (int i = 0; i < aux_des_left.size(); i++) {
    int i1 = 0;
    for (int j = 0; j < aux_des_left[i].cols; j++) {

      for (int k = 0; k < aux_des_left[i].rows; k++) {
        float aux = aux_des_left[i].at<float>(k, j);
        tempDesc.at<float>(i, i1) = aux;
        i1++;
      }

    }
  }
  mCvDesc = tempDesc;
  mCvkey = lss_key;
  emit newStdData("LSS key-point description finished for image " + mImageName);

}
