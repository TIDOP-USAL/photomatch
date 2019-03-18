#include "MTM_KPDescProcess.h"
#include "opencv/cv.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.hpp"
#include "boost/thread.hpp"
#include "MTM/mtm.h"
using namespace cv;


bool myfunction3 (DMatch i,DMatch j) { return (i.distance<j.distance); }

void calculate_distmap (Mat patch_left,int npatch,std::vector<Mat> patchs_norm_right,std::vector<int> steps,int first,int last,DMatch* matchesltor_aux)
{
     mtm vasss;

    for (int j=first;j<=last;j++)
         {
             cv::Mat distancemap;

            int prueba = vasss.PWCw2p(patch_left,patchs_norm_right[j],steps,distancemap);
            double final_entropy = distancemap.at<double>(cv::Point(0,0));
            DMatch aux;
            aux.distance= final_entropy;
            aux.queryIdx=npatch;
            aux.trainIdx=j;
            matchesltor_aux[j]=aux;

         }

}

MTM_KPDescProcess::MTM_KPDescProcess(cv::Mat &cvImgLeft,cv::Mat &cvImgRight, std::vector<cv::KeyPoint> &cvkeyLeft,std::vector<cv::KeyPoint> &cvkeyRight,std::vector<std::vector<cv::DMatch>> &matchesL2R,std::vector<std::vector<cv::DMatch>> &matchesR2L,int sizePatch,int nBins,QString leftImageName,QString rightImageName):
    mCvImgLeft(cvImgLeft),
    mCvkeyLeft(cvkeyLeft),
    mCvImgRight(cvImgRight),
    mCvkeyRight(cvkeyRight),
    mMatchesL2R(matchesL2R),
    mMatchesR2L(matchesR2L),
    mSizePatch(sizePatch),
    mNBins(nBins),
    mLeftImageName(leftImageName),
    mRightImageName(rightImageName)
{

}

MTM_KPDescProcess::~MTM_KPDescProcess()
{

}

void MTM_KPDescProcess::run(){
    int left_max= mCvkeyLeft.size();
    int right_max= mCvkeyRight.size();
    std::vector<int> steps;
//    Mat gray_left,gray_right;
//    cv::cvtColor(mCvImgRight,gray_right,CV_BGR2GRAY);
//    cv::cvtColor(mCvImgLeft,gray_left,CV_BGR2GRAY);
//    gray_right.convertTo(gray_right, CV_64F);
//    gray_left.convertTo(gray_left, CV_64F);

//    mCvImgLeft.convertTo(mCvImgLeft, CV_64F);
//    mCvImgRight.convertTo(mCvImgRight, CV_64F);
    emit newStdData("Starting MTM key-point description for image "+mLeftImageName);
    std::vector<cv::Mat> patchs_norm_left;
    for(int i =0;i<left_max;i++)
    {
        cv::Mat patch;
        normalizepatch(i,patch,0);
        patch.convertTo(patch, CV_64F);
        patchs_norm_left.push_back(patch);
    }
    emit newStdData("MTM key-point description finished for image "+mLeftImageName);

    emit newStdData("Starting MTM key-point description for image "+mRightImageName);

    std::vector<cv::Mat> patchs_norm_right;
    for(int i =0;i<right_max;i++)
    {

        cv::Mat patch;
        normalizepatch(i,patch,1);
        patch.convertTo(patch, CV_64F);
        patchs_norm_right.push_back(patch);
    }

    emit newStdData("MTM key-point description finished for image "+mRightImageName);

    emit newStdData("MTM process includes a brute-force matching approach.");

    emit newStdData("Starting brute force matching");

    for (int i =0; i<=255;i=i+(255/mNBins))steps.push_back(i);


    for( int i = 0; i < left_max; i++ )
    {
        std::vector<DMatch> matchesltor2;
        DMatch* matchesltor_aux;
        matchesltor_aux = new DMatch[right_max];

        unsigned nThreads = boost::thread::hardware_concurrency();
        unsigned stepThread = right_max / nThreads;
        std::vector<boost::thread*> threads;
        for (unsigned j = 0; j < nThreads - 1; j++)
        {
            threads.push_back(new boost::thread(&calculate_distmap,patchs_norm_left[i],i,patchs_norm_right,steps,j*stepThread,((j+1)*stepThread)-1,matchesltor_aux));
        }
        threads.push_back(new boost::thread(&calculate_distmap,patchs_norm_left[i],i,patchs_norm_right,steps,(nThreads - 1)*stepThread,right_max-1,matchesltor_aux));

        for (unsigned j = 0; j < threads.size(); j++)
        {
            threads[j]->join();
            delete threads[j];
        }


       // calculate_distmap(patchs_norm_left[i],i,patchs_norm_right,steps,0,right_max,matchesltor_aux);
        std::sort(matchesltor_aux,matchesltor_aux+right_max , myfunction3);
        matchesltor2.push_back(matchesltor_aux[0]);
        matchesltor2.push_back(matchesltor_aux[1]);
        mMatchesL2R.push_back(matchesltor2);
        delete matchesltor_aux;
    }


    for( int i = 0; i < right_max; i++ )
    {
        std::vector<DMatch> matchesltor2;
        DMatch* matchesltor_aux;
        matchesltor_aux = new DMatch[left_max];

        unsigned nThreads = boost::thread::hardware_concurrency();
        unsigned stepThread = left_max / nThreads;
        std::vector<boost::thread*> threads;
        for (unsigned j = 0; j < nThreads - 1; j++)
        {
            threads.push_back(new boost::thread(&calculate_distmap,patchs_norm_right[i],i,patchs_norm_left,steps,j*stepThread,((j+1)*stepThread)-1,matchesltor_aux));
        }
        threads.push_back(new boost::thread(&calculate_distmap,patchs_norm_right[i],i,patchs_norm_left,steps,(nThreads - 1)*stepThread,left_max-1,matchesltor_aux));

        for (unsigned j = 0; j < threads.size(); j++)
        {
            threads[j]->join();
            delete threads[j];
        }
        // calculate_distmap(patchs_norm_right[i],i,patchs_norm_left,steps,0,left_max,matchesltor_aux);
        std::sort(matchesltor_aux,matchesltor_aux+left_max , myfunction3);
        matchesltor2.push_back(matchesltor_aux[0]);
        matchesltor2.push_back(matchesltor_aux[1]);
        mMatchesR2L.push_back(matchesltor2);

    }
    emit newStdData("Matching process finished.");
    emit newStdData("Matches found from image "+mLeftImageName+" to image "+mRightImageName+": "+QString::number(mMatchesL2R.size()*2));
    emit newStdData("Matches found from image "+mRightImageName+" to image "+mLeftImageName+": "+QString::number(mMatchesR2L.size()*2));
}

//// improve the function for a patch, not taking the images and this kind of things
//void MTM_KPDescProcess::normalizepatch(int i, Mat &output,int leftorright)
// {
//    Mat gray;
//    cv::KeyPoint aux_key;
////    for (int i =0;i>img_left_key.size();i++)
////    {


//    if (leftorright==0){
//        gray=mCvImgLeft;
//        aux_key= mCvkeyLeft[i];
//    }

//    if (leftorright==1){
//        gray=mCvImgRight;
//        aux_key= mCvkeyRight[i];
//    }

//    Point center = aux_key.pt;
//    // in this case area_radius should be impar
//    // take the same area that in the
//    //    Point a;
//    //    Point b;
//    //MxM rectangle
//    //    a.x = center.x - M/2;
//    //    a.y = center.y - M/2;
////    b.x = center.x + M/2;
////    b.y = center.y + M/2;

//    output = Mat::zeros(mSizePatch,mSizePatch,CV_8UC1);
//    cv::Size maskenter;
//    maskenter.height= cvRound(aux_key.size);
//    maskenter.width =  cvRound(aux_key.size);

//    cv::Size outsize;
//    outsize.height=mSizePatch;
//    outsize.width =mSizePatch;
//    cv::Mat input;// = gray(cv::Range(a.x,a.y), cv::Range(b.x , b.y));

//    gray.convertTo(gray, CV_64FC1);

//    // Rotation and scale comes from the left corner, that is the center.
//    getRectSubPix(gray,maskenter,center, input );
////    namedWindow("Input Patch", 0 );
////    imshow("Input Patch", input );


//    cv::Point2f pt;

//// here there are a problem with the center, it depends on the value it´s not a trivial thing.
//    // solved
//    if ((input.cols%4)==1)
//    {
//        pt.x=cvRound(input.cols/2.0);
//        pt.y =cvRound(input.rows/2.0);
//    }
//    else if((input.cols%4)==0)
//    {

//        pt.x=(input.cols/2.0)-0.5;
//        pt.y =(input.rows/2.0)-0.5;
//    }
//    else if((input.cols%4)==2)
//    {

//        pt.x=(input.cols/2.0)-0.5;
//        pt.y =(input.rows/2.0)-0.5;
//    }
//    else if((input.cols%4)==3)
//    {

//        pt.x=(input.cols/2.0)-0.5;
//        pt.y =(input.rows/2.0)-0.5;
//    }
//    // to calculate the scale, is the size of the keypoint between
//    // the scale is related to the diagonal of both pathces
//   // float scale = 1.0f*std::sqrt((maskenter.height*maskenter.height)+(maskenter.height*maskenter.height))/std::sqrt((outsize.height*outsize.height)+(outsize.height*outsize.height));

//    Mat transform = cv::getRotationMatrix2D(pt,aux_key.angle,1.0);
//    Mat source1;

//    //ROTATE
//   // warpAffine(fromI, rotI, R, rotI.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar::all(0));
//    cv::warpAffine(input,source1,transform,input.size(),INTER_LINEAR+cv::WARP_INVERSE_MAP,cv::BORDER_REPLICATE);//+cv::WARP_INVERSE_MAP

////    namedWindow("Rotated Patch", 0 );
////    imshow("Rotated Patch", source1 );

//    // works best in 2 steps instead of one.
//    if (outsize.height!=input.cols)cv::resize(source1,output,outsize);
//    else source1.copyTo(output);

////    namedWindow("Normalized Patch", 0 );
////    imshow("Normalized Patch", output );

//  //asdfadsfadfs
//}

// improve the function for a patch, not taking the images and this kind of things
void MTM_KPDescProcess::normalizepatch(int i, Mat &output,int leftorright)
 {
    Mat gray;
    cv::KeyPoint aux_key;
//    for (int i =0;i>img_left_key.size();i++)
//    {


    if (leftorright==0){
        gray=mCvImgLeft;
        aux_key= mCvkeyLeft[i];
    }

    if (leftorright==1){
        gray=mCvImgRight;
        aux_key= mCvkeyRight[i];
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

    output = Mat::zeros(mSizePatch,mSizePatch,CV_8UC1);
    cv::Size maskenter;
    maskenter.height= cvRound(aux_key.size);
    maskenter.width =  cvRound(aux_key.size);

    cv::Size outsize;
    outsize.height=mSizePatch;
    outsize.width =mSizePatch;
    cv::Mat input;// = gray(cv::Range(a.x,a.y), cv::Range(b.x , b.y));

    // Rotation and scale comes from the left corner, that is the center.
    getRectSubPix(gray,maskenter,center, input );
//    namedWindow("Input Patch", 0 );
//    imshow("Input Patch", input );


    cv::Point2f pt;

// here there are a problem with the center, it depends on the value it´s not a trivial thing.
    // solved
    if ((input.cols%4)==1)
    {
        pt.x=cvRound(input.cols/2.0);
        pt.y =cvRound(input.rows/2.0);
    }
    else if((input.cols%4)==0)
    {

        pt.x=(input.cols/2.0)-0.5;
        pt.y =(input.rows/2.0)-0.5;
    }
    else if((input.cols%4)==2)
    {

        pt.x=(input.cols/2.0)-0.5;
        pt.y =(input.rows/2.0)-0.5;
    }
    else if((input.cols%4)==3)
    {

        pt.x=(input.cols/2.0)-0.5;
        pt.y =(input.rows/2.0)-0.5;
    }
    // to calculate the scale, is the size of the keypoint between
    // the scale is related to the diagonal of both pathces
   // float scale = 1.0f*std::sqrt((maskenter.height*maskenter.height)+(maskenter.height*maskenter.height))/std::sqrt((outsize.height*outsize.height)+(outsize.height*outsize.height));

    Mat transform = cv::getRotationMatrix2D(pt,aux_key.angle,1.0);
    Mat source1;

    //ROTATE
   // warpAffine(fromI, rotI, R, rotI.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar::all(0));
    cv::warpAffine(input,source1,transform,input.size(),INTER_LINEAR+cv::WARP_INVERSE_MAP,cv::BORDER_REPLICATE);//+cv::WARP_INVERSE_MAP

//    namedWindow("Rotated Patch", 0 );
//    imshow("Rotated Patch", source1 );

    // works best in 2 steps instead of one.
    if (outsize.height!=input.cols)cv::resize(source1,output,outsize);
    else source1.copyTo(output);

//    namedWindow("Normalized Patch", 0 );
//    imshow("Normalized Patch", output );

  //asdfadsfadfs
}
