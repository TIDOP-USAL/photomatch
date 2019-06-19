#include "MSD_KPDetProcess.h"

#include "MSD.h"

using namespace cv;
using namespace std;
#define _USE_MATH_DEFINES
#define ABS(x)    (((x) > 0) ? (x) : (-(x)))
#define M_PI 3.14159265358979323846

MSD_KPDetProcess::MSD_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey,int patchRadius,
                                   int SearchAreaRadius, int NMSRadius, int NMSScaleRadius, float ThSaliency,int KNN, float ScaleFactor,
                                   int NScales,bool computeOrientations,bool affine,int affineTilts, const QString &imageName):
    mCvImg(cvImg),
    mCvKey(cvKey),
    msdPatchRadius(patchRadius),
    msdSearchAreaRadius(SearchAreaRadius),
    msdNMSRadius(NMSRadius),
    msdNMSScaleRadius(NMSScaleRadius),
    msdThSaliency(ThSaliency),
    msdKNN(KNN),
    msdScaleFactor(ScaleFactor),
    msdNScales(NScales),
    msdComputeOrientations(computeOrientations),
    mAffine(affine),
    mAffineTilts(affineTilts),
    mImageName(imageName)
{

}

MSD_KPDetProcess::~MSD_KPDetProcess()
{

}
void MSD_KPDetProcess::run()
{
  //    cv::cvtColor(mCvImg,mCvImg,CV_RGB2GRAY);

  if (mAffine) {
    emit newStdData("Searching Affine-MSD key-points for image " + mImageName);

    MsdDetector MSDDetector;

    MSDDetector.setPatchRadius(msdPatchRadius);
    MSDDetector.setSearchAreaRadius(msdSearchAreaRadius);

    MSDDetector.setNMSRadius(msdNMSRadius);
    MSDDetector.setNMSScaleRadius(msdNMSScaleRadius);

    MSDDetector.setThSaliency(msdThSaliency);
    MSDDetector.setKNN(msdKNN);

    MSDDetector.setScaleFactor(msdScaleFactor);
    MSDDetector.setNScales(msdNScales);

    MSDDetector.setComputeOrientation(msdComputeOrientations);


    float maxX = 0;
    float maxY = 0;
//    int cols = mCvImg.cols;
//    int rows = mCvImg.rows;
    int i = 0;
    for (int tl = 1; tl <= mAffineTilts; tl++)
    {
      double t = pow(2, 0.5*tl);
      for (int phi = 0; phi < 180; phi += 72.0 / t)
      {
        i++;
        std::vector<KeyPoint> kps;
        kps.clear();
        Mat timg, mask, Ai;

        mCvImg.copyTo(timg);
        affineSkew(t, phi, timg, mask, Ai);

        kps = MSDDetector.detect(timg);


        for (unsigned int i = 0; i < kps.size(); i++)
        {
          Point3f kpt(kps[i].pt.x, kps[i].pt.y, 1);
          Mat kpt_t = Ai*Mat(kpt);

          kps[i].pt.x = kpt_t.at<float>(0, 0);
          kps[i].pt.y = kpt_t.at<float>(1, 0);
          if (phi == 0 || pointIsAcceptable(kps[i], mCvImg.cols, mCvImg.rows)) {
            if (kps[i].pt.x > maxX) {
              maxX = kps[i].pt.x;
            }
            if (kps[i].pt.y > maxY) {
              maxY = kps[i].pt.y;
            }
            mCvKey.push_back(kps[i]);
          }
          kpt_t.release();
        }


        timg.release();
        mask.release();
        Ai.release();
      }
    }
    emit newStdData("Affine-MSD Key-points found in image " + mImageName + ": " + QString::number(mCvKey.size()));

  }
  else {
    emit newStdData("Searching MSD key-points for image " + mImageName);

    MsdDetector MSDDetector;

    MSDDetector.setPatchRadius(msdPatchRadius);
    MSDDetector.setSearchAreaRadius(msdSearchAreaRadius);

    MSDDetector.setNMSRadius(msdNMSRadius);
    MSDDetector.setNMSScaleRadius(msdNMSScaleRadius);

    MSDDetector.setThSaliency(msdThSaliency);
    MSDDetector.setKNN(msdKNN);

    MSDDetector.setScaleFactor(msdScaleFactor);
    MSDDetector.setNScales(msdNScales);

    MSDDetector.setComputeOrientation(msdComputeOrientations);


    mCvKey = MSDDetector.detect(mCvImg);
    emit newStdData("MSD Key-points found in image " + mImageName + ": " + QString::number(mCvKey.size()));

  }

}

void MSD_KPDetProcess::compensate_affine_coor1(float *x0, float *y0, int w1, int h1, float t1, float t2, float Rtheta)
{
  float x_ori, y_ori;
  float x_tmp, y_tmp;

  float x1 = *x0;
  float y1 = *y0;


  Rtheta = Rtheta*M_PI/180;

  if ( Rtheta <= M_PI/2 )
  {
    x_ori = 0;
    y_ori = w1 * sin(Rtheta) / t1;
  }
  else
  {
    x_ori = -w1 * cos(Rtheta) / t2;
    y_ori = ( w1 * sin(Rtheta) + h1 * sin(Rtheta-M_PI/2) ) / t1;
  }

  float sin_Rtheta = sin(Rtheta);
  float cos_Rtheta = cos(Rtheta);


  /* project the coordinates of im1 to original image before tilt-rotation transform */
  /* Get the coordinates with respect to the 'origin' of the original image before transform */
  x1 = x1 - x_ori;
  y1 = y1 - y_ori;
  /* Invert tilt */
  x1 = x1 * t2;
  y1 = y1 * t1;
  /* Invert rotation (Note that the y direction (vertical) is inverse to the usual concention. Hence Rtheta instead of -Rtheta to inverse the rotation.) */
  x_tmp = cos_Rtheta*x1 - sin_Rtheta*y1;
  y_tmp = sin_Rtheta*x1 + cos_Rtheta*y1;
  x1 = x_tmp;
  y1 = y_tmp;

  *x0 = x1;
  *y0 = y1;
}



bool MSD_KPDetProcess::pointIsAcceptable(KeyPoint vl_keypoint, int width, int height)
{
  bool retVal = false;
  double x0, y0, vx1, vy1, vx2, vy2, vx3, vy3, vx4, vy4, d1, d2, d3, d4, scale1, BorderTh;

  x0 = vl_keypoint.pt.x;
  y0 = vl_keypoint.pt.y;
  scale1 = vl_keypoint.size;

  if (x0 <= 0 || y0 <= 0 || x0 >= width || y0 >= height) {
    return false;
  }

  vx1 = 0;
  vy1 = 0;

  vx2 = 0;
  vy2 = height;

  vx3 = width;
  vy3 = 0;

  vx4 = width;
  vy4 = height;

  d1 = sqrt(pow((x0 - vx1), 2) + pow((y0 - vy1), 2));
  d2 = sqrt(pow((x0 - vx2), 2) + pow((y0 - vy2), 2));
  d3 = sqrt(pow((x0 - vx3), 2) + pow((y0 - vy3), 2));
  d4 = sqrt(pow((x0 - vx4), 2) + pow((y0 - vy4), 2));

  float BorderFact = width / 100 * sqrt(2.);
  //if (scale1 < 1){ scale1 = 1;}
  BorderTh = BorderFact*scale1;

  if (d1 < BorderTh || d2 < BorderTh || d3 < BorderTh || d4 < BorderTh) {
    retVal = false;
  }
  else {
    retVal = true;
  }
  return retVal;
}

void MSD_KPDetProcess::affineSkew(double tilt, double phi, Mat& img, Mat& mask, Mat& Ai)
{
  int h = img.rows;
  int w = img.cols;

  mask = Mat(h, w, CV_8UC1, Scalar(255));

  Mat A = Mat::eye(2,3, CV_32F);

  if(phi != 0.0)
  {
    phi *= CV_PI/180.;
    double s = sin(phi);
    double c = cos(phi);

    A = (Mat_<float>(2,2) << c, -s, s, c);

    Mat corners = (Mat_<float>(4,2) << 0, 0, w, 0, w, h, 0, h);
    Mat tcorners = corners*A.t();
    Mat tcorners_x, tcorners_y;
    tcorners.col(0).copyTo(tcorners_x);
    tcorners.col(1).copyTo(tcorners_y);
    std::vector<Mat> channels;
    channels.push_back(tcorners_x);
    channels.push_back(tcorners_y);
    merge(channels, tcorners);

    Rect rect = boundingRect(tcorners);
    A =  (Mat_<float>(2,3) << c, -s, -rect.x, s, c, -rect.y);

    warpAffine(img, img, A, Size(rect.width, rect.height), INTER_LINEAR, BORDER_REPLICATE);
  }
  if(tilt != 1.0)
  {
    double s = 0.8*sqrt(tilt*tilt-1);
    GaussianBlur(img, img, Size(0,0), s, 0.01);
    resize(img, img, Size(0,0), 1.0/tilt, 1.0, INTER_NEAREST);
    A.row(0) = A.row(0)/tilt;
  }
  if(tilt != 1.0 || phi != 0.0)
  {
    h = img.rows;
    w = img.cols;
    warpAffine(mask, mask, A, Size(w, h), INTER_NEAREST);
  }
  invertAffineTransform(A, Ai);
}

//vector<vector<int>> MSD_KPDetProcess::detectMSD(Mat img, vector< KeyPoint >& keypoints){
//    keypoints.clear();

//    vector<vector<int> > descriptorsOut;

//    MsdDetector msdLeft;


//    msdLeft.setPatchRadius(msdPatchRadius);
//    msdLeft.setSearchAreaRadius(msdSearchAreaRadius);

//    msdLeft.setNMSRadius(msdNMSRadius);
//    msdLeft.setNMSScaleRadius(msdNMSScaleRadius);

//    msdLeft.setThSaliency(msdThSaliency);
//    msdLeft.setKNN(msdKNN);

//    msdLeft.setScaleFactor(msdScaleFactor);

//    //Compute nscales max
//    int maxNscales;
//    maxNscales =cvFloor(std::log(cv::min(img.cols, img.rows) / ((msdPatchRadius + msdSearchAreaRadius)*2.0 + 1)) / std::log(msdScaleFactor));
//    if (maxNscales<msdNScales) {
//        msdLeft.setNScales(maxNscales);
//    }else {
//        msdLeft.setNScales(msdNScales);
//    }


//    msdLeft.setComputeOrientation(msdComputeOrientations);

////    cv::Mat auxImage;


////    keypoints = msdLeft.detectandcompute(img,auxImage,-1);
//    keypoints = msdLeft.detect(img);

//    cv::Ptr<cv::xfeatures2d::SIFT> detector = cv::xfeatures2d::SIFT::create();
//    cv::Mat cvDescriptors;

//    detector->compute(img,keypoints,cvDescriptors);

////    descriptorsOut.assign(cvDescriptors.datastart,cvDescriptors.dataend);
//    for (int i=0; i < cvDescriptors.rows; i++) {
//        std::vector<int> descriptor;
//        for (int j =0; j < cvDescriptors.cols; j++){
//            descriptor.push_back(cvDescriptors.at<float>(i,j));
//        }
//        descriptorsOut.push_back(descriptor);
//   }

//    return descriptorsOut;
//}
