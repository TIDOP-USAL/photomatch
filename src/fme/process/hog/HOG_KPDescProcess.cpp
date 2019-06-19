#include "HOG_KPDescProcess.h"

#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

HOG_KPDescProcess::HOG_KPDescProcess(cv::Mat &cvImgLeft, cv::Mat &cvImgRight, 
                                     std::vector<cv::KeyPoint> &cvkeyLeft, 
                                     std::vector<cv::KeyPoint> &cvkeyRight, 
                                     cv::Mat &cvDescLeft, cv::Mat &cvDescRight,
                                     int sizePatch, const QString &leftImageName, 
                                     const QString &rightImageName)
  : mLeftImageName(leftImageName),
    mRightImageName(rightImageName),
    mCvImgLeft(cvImgLeft),
    mCvImgRight(cvImgRight),
    mCvkeyLeft(cvkeyLeft),
    mCvkeyRight(cvkeyRight),
    mCvDescLeft(cvDescLeft),
    mCvDescRight(cvDescRight),
    mSizePatch(sizePatch)
{

}

HOG_KPDescProcess::~HOG_KPDescProcess()
{

}

void HOG_KPDescProcess::run()
{
  emit newStdData("Starting HOG key-point description for image " + mLeftImageName);

  std::vector<float> hogdescriptor_left, hogdescriptor_right;
  std::vector<Point> p_c;
  cv::Point punto_central;
  punto_central.x = mSizePatch / 2;
  punto_central.y = mSizePatch / 2;
  p_c.push_back(punto_central);

  int left_max = static_cast<int>(mCvkeyLeft.size());
  int right_max = static_cast<int>(mCvkeyRight.size());


  HOGDescriptor hog(Size(mSizePatch, mSizePatch), Size(4, 4),
    Size(2, 2), Size(2, 2), 9);
  mCvDescLeft = cv::Mat(left_max, static_cast<int>(hog.getDescriptorSize()), CV_32FC1);

  emit newStdData("Starting HOG key-point description for image " + mRightImageName);
  mCvDescRight = cv::Mat(right_max, static_cast<int>(hog.getDescriptorSize()), CV_32FC1);


  for (int i = 0; i < left_max; i++) {
    std::vector<float> hogdescriptor_left_aux;
    cv::Mat left_patch;
    normalizepatch(i, left_patch, 0);
    hog.compute(left_patch, hogdescriptor_left_aux);
    for (size_t j = 0; j < hogdescriptor_left_aux.size(); j++) mCvDescLeft.at<float>(i, static_cast<int>(j)) = hogdescriptor_left_aux[j];
  }
  emit newStdData("HOG key-point description finished for image " + mLeftImageName);


  for (int i = 0; i < right_max; i++) {
    std::vector<float> hogdescriptor_right_aux;
    cv::Mat right_patch;
    normalizepatch(i, right_patch, 1);
    hog.compute(right_patch, hogdescriptor_right_aux);
    for (size_t j  = 0; j < hogdescriptor_right_aux.size(); j++) mCvDescRight.at<float>(i, static_cast<int>(j)) = hogdescriptor_right_aux[j];
  }

  emit newStdData("HOG key-point description finished for image " + mRightImageName);
}


// improve the function for a patch, not taking the images and this kind of things
void HOG_KPDescProcess::normalizepatch(int i, Mat &output, int leftorright)
{
  Mat gray;
  cv::KeyPoint aux_key;
  //    for (int i =0;i>img_left_key.size();i++)
  //    {


  if (leftorright == 0) {
    gray = mCvImgLeft;
    aux_key = mCvkeyLeft[static_cast<size_t>(i)];
  }

  if (leftorright == 1) {
    gray = mCvImgRight;
    aux_key = mCvkeyRight[static_cast<size_t>(i)];
  }

  Point center = aux_key.pt;
  // in this case area_radius should be impar
  // take the same area that in the
  //    Point a;
  //    Point b;
  //MxM rectangle
  //    a.x = center.x - M/2;
  //    a.y = center.y - M/2;
//    b.x = center.x + M/2;
//    b.y = center.y + M/2;

  output = Mat::zeros(mSizePatch, mSizePatch, CV_8UC1);
  cv::Size maskenter;
  maskenter.height = cvRound(aux_key.size);
  maskenter.width = cvRound(aux_key.size);

  cv::Size outsize;
  outsize.height = mSizePatch;
  outsize.width = mSizePatch;
  cv::Mat input;// = gray(cv::Range(a.x,a.y), cv::Range(b.x , b.y));

  // Rotation and scale comes from the left corner, that is the center.
  getRectSubPix(gray, maskenter, center, input);
  //    namedWindow("Input Patch", 0 );
  //    imshow("Input Patch", input );


  cv::Point2f pt;

  // here there are a problem with the center, it depends on the value it´s not a trivial thing.
      // solved
  if ((input.cols % 4) == 1) {
    pt.x = cvRound(input.cols / 2.0);
    pt.y = cvRound(input.rows / 2.0);
  } else if ((input.cols % 4) == 0) {
    pt.x = (input.cols / 2.0f) - 0.5f;
    pt.y = (input.rows / 2.0f) - 0.5f;
  } else if ((input.cols % 4) == 2) {
    pt.x = (input.cols / 2.0f) - 0.5f;
    pt.y = (input.rows / 2.0f) - 0.5f;
  } else if ((input.cols % 4) == 3) {
    pt.x = (input.cols / 2.0f) - 0.5f;
    pt.y = (input.rows / 2.0f) - 0.5f;
  }
  // to calculate the scale, is the size of the keypoint between
  // the scale is related to the diagonal of both pathces
 // float scale = 1.0f*std::sqrt((maskenter.height*maskenter.height)+(maskenter.height*maskenter.height))/std::sqrt((outsize.height*outsize.height)+(outsize.height*outsize.height));

  Mat transform = cv::getRotationMatrix2D(pt, static_cast<double>(aux_key.angle), 1.0);
  Mat source1;

  //ROTATE
 // warpAffine(fromI, rotI, R, rotI.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar::all(0));
  cv::warpAffine(input, source1, transform, input.size(), INTER_LINEAR + cv::WARP_INVERSE_MAP, cv::BORDER_REPLICATE);//+cv::WARP_INVERSE_MAP

//    namedWindow("Rotated Patch", 0 );
//    imshow("Rotated Patch", source1 );

    // works best in 2 steps instead of one.
  if (outsize.height != input.cols) cv::resize(source1, output, outsize);
  else source1.copyTo(output);

  //    namedWindow("Normalized Patch", 0 );
  //    imshow("Normalized Patch", output );

    //asdfadsfadfs
}
