#include "MutualInformation_KPDescProcess.h"
#include "opencv/cv.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.hpp"
#include "boost/thread.hpp"
using namespace cv;

bool myfunction (DMatch i,DMatch j) { return (i.distance > j.distance); }

bool myfunction2 (DMatch i,DMatch j) { return (i.distance<j.distance); }

// myEntropy calculates relative occurrence of different symbols within given input sequence using histogram
Mat hist_simple(Mat seq, int histSize)
{


    const float hRange[] = {0.f, 256.f};
    const float* ranges[] = {hRange};


    bool uniform = true; bool accumulate = false;

    Mat hist;

    /// Compute the histograms:
    calcHist( &seq, 1, 0, Mat(), hist, 1, &histSize, ranges, uniform, accumulate );

    return hist;

}



float entropy(Mat hist, Size size_patch, int numbins)
{

  float entr = 0;
  float total_size = size_patch.height * size_patch.width; //total size of all symbols in an image

  for(int i=0;i<numbins;i++)
  {


    float sym_occur = hist.at<float>(i); //the number of times a sybmol has occured
    if(sym_occur>0) //log of zero goes to infinity
      {

        entr += (sym_occur/total_size)*(std::log(total_size/sym_occur));
      }

  }

  return entr;

}


float joint_entropy(Mat hist, Size size_patch, int numbins)

{

  float entr = 0;
  float total_size = size_patch.height * size_patch.width; //total size of all symbols in an image

  for(int i=0;i<numbins;i++)
  {
      for(int j=0;j<numbins;j++)
      {

    float sym_occur = hist.at<float>(i, j); //the number of times a sybmol has occured
    if(sym_occur>0) //log of zero goes to infinity
      {

        entr += (sym_occur/total_size)*(std::log(total_size/sym_occur));
      }
      }
  }

  return entr;

}

Mat jointhist(Mat seq,Mat dos, int histSize)
{
    Mat channel[2];

    Mat prueba(seq.rows,seq.cols,CV_8UC2);
    seq.copyTo(channel[0]);
    dos.copyTo(channel[1]);
    cv::merge(channel,2,prueba);
    int histSize2[] = {histSize, histSize};
    int channels[] = {0, 1};
    const float hRange[] = {0.f, 256.f};
    const float* ranges[] = {hRange, hRange};

    bool uniform = true; bool accumulate = false;

    Mat hist;

    /// Compute the histograms:
    calcHist( &prueba, 1, channels, Mat(), hist, 2, histSize2, ranges, uniform, accumulate );

    return hist;
}

void compute_mi(Mat left_patch, int i, std::vector<Mat> right_patchs, int nbins, float entropy_left, int first, int last,DMatch* matchesltor_aux)
{
    for (int j=first;j<=last;j++)
    {

        Mat hist_right;
        hist_right=hist_simple(right_patchs[j], nbins);
        float entropyright=entropy(hist_right,right_patchs[j].size(),nbins);
        Mat hist_joint_aux;
        hist_joint_aux= jointhist(left_patch,right_patchs[j],nbins);
        float joinentropy=joint_entropy(hist_joint_aux,right_patchs[j].size(),nbins);
        float final_entropy = (entropy_left+entropyright)-joinentropy;
        DMatch aux;
        aux.distance= final_entropy;
        aux.queryIdx=i;
        aux.trainIdx=j;
        matchesltor_aux[j]=aux;

    }
}



MutualInformation_KPDescProcess::MutualInformation_KPDescProcess(cv::Mat &cvImgLeft,cv::Mat &cvImgRight, std::vector<cv::KeyPoint> &cvkeyLeft,std::vector<cv::KeyPoint> &cvkeyRight,std::vector<std::vector<cv::DMatch>> &matchesL2R,std::vector<std::vector<cv::DMatch>> &matchesR2L,int sizePatch,int nBins,QString leftImageName,QString rightImageName):
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

MutualInformation_KPDescProcess::~MutualInformation_KPDescProcess()
{

}

void MutualInformation_KPDescProcess::run(){

    int left_max= mCvkeyLeft.size();
    int right_max= mCvkeyRight.size();

    emit newStdData("Starting Mutual Information key-point description for image "+mLeftImageName);

    std::vector<cv::Mat> patchs_norm_left;
    for(int i =0;i<left_max;i++)
    {
        cv::Mat patch;
        normalizepatch(i,patch,0);
        patchs_norm_left.push_back(patch);
    }
    emit newStdData("Mutual Information key-point description finished for image "+mLeftImageName);

    emit newStdData("Starting Mutual Information key-point description for image "+mRightImageName);
    std::vector<cv::Mat> patchs_norm_right;
    for(int i =0;i<right_max;i++)
    {

        cv::Mat patch;
        normalizepatch(i,patch,1);
        patchs_norm_right.push_back(patch);
    }
    emit newStdData("Mutual Information key-point description finished for image "+mRightImageName);

    emit newStdData("Mutual Information process includes a brute-force matching approach.");

    emit newStdData("Starting brute force matching");

    for( int i = 0; i < left_max; i++ )
    {

        DMatch* matchesltor_aux;
        std::vector<DMatch> matchesltor2;
        matchesltor_aux = new DMatch[right_max]();
        cv::Mat prueba;
        prueba= patchs_norm_left[i];
        Mat hist_left;
        hist_left=hist_simple(prueba, mNBins);
        float entropyleft= entropy(hist_left,patchs_norm_left[i].size(),mNBins);
        unsigned nThreads = boost::thread::hardware_concurrency();
        unsigned stepThread = right_max / nThreads;
        std::vector<boost::thread*> threads;

        for (unsigned j = 0; j <(nThreads - 1); j++)
        {
            threads.push_back(new boost::thread(compute_mi,patchs_norm_left[i],i,patchs_norm_right,mNBins,entropyleft,j* stepThread,((j+1)*stepThread)-1,matchesltor_aux));
        }

           threads.push_back(new boost::thread(compute_mi,patchs_norm_left[i],i,patchs_norm_right,mNBins,entropyleft,(nThreads - 1)* stepThread,(right_max-1),matchesltor_aux));

        for (unsigned j = 0; j < threads.size(); j++)
        {
            threads[j]->join();
             delete threads[j];
        }

//        compute_mi(patchs_norm_left[i],i,patchs_norm_right,mNBins,entropyleft,0,right_max,matchesltor_aux);

        std::sort(matchesltor_aux,matchesltor_aux+right_max,myfunction);
        matchesltor2.push_back(matchesltor_aux[0]);
        matchesltor2.push_back(matchesltor_aux[1]);

        mMatchesL2R.push_back(matchesltor2);
        delete matchesltor_aux;
    }

    for( int i = 0; i < right_max; i++ )
    {

        DMatch* matchesltor_aux2;
        std::vector<DMatch> matchesltor2;
        matchesltor_aux2 = new DMatch[left_max]();
        Mat hist_left;
        hist_left=hist_simple(patchs_norm_right[i], mNBins);
        float entropyleft= entropy(hist_left,patchs_norm_right[i].size(),mNBins);
        unsigned nThreads = boost::thread::hardware_concurrency();
        unsigned stepThread = left_max / nThreads;
        std::vector<boost::thread*> threads;
        for (unsigned j = 0; j < (nThreads - 1); j++)
        {
            threads.push_back(new boost::thread(compute_mi,patchs_norm_right[i],i,patchs_norm_left,mNBins,entropyleft,j*stepThread,((j+1)*stepThread)-1,matchesltor_aux2));
        }
        threads.push_back(new boost::thread(compute_mi,patchs_norm_right[i],i,patchs_norm_left,mNBins,entropyleft,(nThreads - 1)* stepThread,left_max-1,matchesltor_aux2));

        for (unsigned j = 0; j < threads.size(); j++)
        {
            threads[j]->join();
            delete threads[j];
        }
//        compute_mi(patchs_norm_right[i],i,patchs_norm_left,mNBins,entropyleft,0,left_max,matchesltor_aux2);

        std::sort(matchesltor_aux2,matchesltor_aux2+left_max,myfunction);
        matchesltor2.push_back(matchesltor_aux2[0]);
        matchesltor2.push_back(matchesltor_aux2[1]);
        mMatchesR2L.push_back(matchesltor2);
    }
    emit newStdData("Matching process finished.");
    emit newStdData("Matches found from image "+mLeftImageName+" to image "+mRightImageName+": "+QString::number(mMatchesL2R.size()*2));
    emit newStdData("Matches found from image "+mRightImageName+" to image "+mLeftImageName+": "+QString::number(mMatchesR2L.size()*2));

}

// improve the function for a patch, not taking the images and this kind of things
void MutualInformation_KPDescProcess::normalizepatch(int i, Mat &output,int leftorright)
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
