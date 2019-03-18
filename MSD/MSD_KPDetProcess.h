#ifndef MSD_KPDETPROCESS_H
#define MSD_KPDETPROCESS_H
#include "ProcessManager/ProcessConcurrent.h"
#include "opencv/cv.hpp"
#include "MSD.h"
class MSD_KPDetProcess: public ProcessConcurrent
{
public:
    MSD_KPDetProcess(cv::Mat &cvImg,std::vector<cv::KeyPoint> &cvKey,int patchRadius,
                     int SearchAreaRadius, int NMSRadius, int NMSScaleRadius, float ThSaliency,int KNN, float ScaleFactor,
                     int NScales,bool computeOrientations,bool affine,int affineTilts,QString imageName);
    ~MSD_KPDetProcess();
    void run();
private:
    QString mImageName;
    cv::Mat &mCvImg;
    std::vector<cv::KeyPoint> &mCvKey;

    //MSD parameters
    int msdPatchRadius;
    int msdSearchAreaRadius;
    int msdNMSRadius;
    int msdNMSScaleRadius;
    float msdThSaliency;
    int msdKNN;
    float msdScaleFactor;
    int msdNScales;
    bool msdComputeOrientations;
    bool mAffine;
    int mAffineTilts;
    bool pointIsAcceptable( cv::KeyPoint vl_keypoint, int width, int height);
    void compensate_affine_coor1(float *x0, float *y0, int w1, int h1, float t1, float t2, float Rtheta);
    void affineSkew(double tilt, double phi, cv::Mat& img, cv::Mat& mask, cv::Mat& Ai);
//    std::vector<std::vector<int>> detectMSD(cv::Mat img, std::vector< cv::KeyPoint >& keypoints);

};

#endif // MSD_KPDETPROCESS_H
