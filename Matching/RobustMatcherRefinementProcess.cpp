#include "RobustMatcherRefinementProcess.h"
#include "opencv/cv.hpp"
#include <QFileInfo>
#define MATCHINGREFINEMENT_LMSE             0
#define MATCHINGREFINEMENT_RANSAC           1
#define MATCHINGREFINEMENT_8POINT           2

using namespace cv;

int ratioTest(std::vector<std::vector<cv::DMatch>>& matches,float ratio) {

    int removed=0;

    // for all matches
    for (std::vector<std::vector<cv::DMatch>>::iterator matchIterator= matches.begin();
         matchIterator!= matches.end(); ++matchIterator) {

        // if 2 NN has been identified
        if (matchIterator->size() > 1) {

            // check distance ratio
            if ((*matchIterator)[0].distance/(*matchIterator)[1].distance > ratio) {

                matchIterator->clear(); // remove match
                removed++;
            }

        } else { // does not have 2 neighbours

            matchIterator->clear(); // remove match
            removed++;
        }
    }

    return removed;
}
// Insert symmetrical matches in symMatches vector
void symmetryTest(const std::vector<std::vector<cv::DMatch>>& matches1,
                  const std::vector<std::vector<cv::DMatch>>& matches2,
                  std::vector<cv::DMatch>& symMatches) {

    // for all matches image 1 -> image 2
    for (std::vector<std::vector<cv::DMatch>>::const_iterator matchIterator1= matches1.begin();
         matchIterator1!= matches1.end(); ++matchIterator1) {

        if (matchIterator1->size() < 2) // ignore deleted matches
            continue;

        // for all matches image 2 -> image 1
        for (std::vector<std::vector<cv::DMatch>>::const_iterator matchIterator2= matches2.begin();
             matchIterator2!= matches2.end(); ++matchIterator2) {

            if (matchIterator2->size() < 2) // ignore deleted matches
                continue;

            // Match symmetry test
            if ((*matchIterator1)[0].queryIdx == (*matchIterator2)[0].trainIdx  &&
                    (*matchIterator2)[0].queryIdx == (*matchIterator1)[0].trainIdx) {

                // add symmetrical match
                symMatches.push_back(cv::DMatch((*matchIterator1)[0].queryIdx,
                                     (*matchIterator1)[0].trainIdx,
                        (*matchIterator1)[0].distance));
                break; // next match in image 1 -> image 2
            }
        }
    }
}

// Identify good matches using RANSAC
// Return fundemental matrix
void ransacTest(const std::vector<cv::DMatch>& matches,
                const std::vector<cv::KeyPoint>& keypoints1,
                const std::vector<cv::KeyPoint>& keypoints2,
                std::vector<cv::DMatch>& outMatches,int method,float confidence,float distance) {

    // Convert keypoints into Point2f
    std::vector<cv::Point2f> points1, points2;
    for (std::vector<cv::DMatch>::const_iterator it= matches.begin();
         it!= matches.end(); ++it) {

        // Get the position of left keypoints
        float x= keypoints1[it->queryIdx].pt.x;
        float y= keypoints1[it->queryIdx].pt.y;
        points1.push_back(cv::Point2f(x,y));
        // Get the position of right keypoints
        x= keypoints2[it->trainIdx].pt.x;
        y= keypoints2[it->trainIdx].pt.y;
        points2.push_back(cv::Point2f(x,y));
    }

    // Compute F matrix using RANSAC
    std::vector<uchar> inliers(points1.size(),0);
    if (method==FM_RANSAC)
    {
        cv::Mat fundemental= cv::findFundamentalMat(
                    cv::Mat(points1),cv::Mat(points2), // matching points
                    inliers,      // match status (inlier ou outlier)
                    method, // RANSAC method
                    distance);// distance to epipolar line
    }
    else{
        cv::Mat fundemental= cv::findFundamentalMat(
                    cv::Mat(points1),cv::Mat(points2), // matching points
                    inliers,      // match status (inlier ou outlier)
                    method);
    }
    // extract the surviving (inliers) matches
    std::vector<uchar>::const_iterator itIn= inliers.begin();
    std::vector<cv::DMatch>::const_iterator itM= matches.begin();
    // for all matches
    for ( ;itIn!= inliers.end(); ++itIn, ++itM) {

        if (*itIn) { // it is a valid match

            outMatches.push_back(*itM);
        }
    }


}
RobustMatcherRefinementProcess::RobustMatcherRefinementProcess(cv::Mat &cvImgLeft,cv::Mat &cvImgRight,std::vector<cv::KeyPoint> &cvkeyLeft,std::vector<cv::KeyPoint> &cvkeyRight,std::vector<std::vector<cv::DMatch>> &matchesL2R,std::vector<std::vector<cv::DMatch>> &matchesR2L,std::vector<cv::DMatch> &correctMatches,std::vector<cv::DMatch> &wrongMatches,int refinementMethod,float k, float ratio,float distance,float confidence,bool fromMI,bool haveGroundTruth,cv::Mat &groundTruth,QString leftImageName,QString rightImageName,QDir outputHomographyDir):
    mCvImgLeft(cvImgLeft),
    mCvImgRight(cvImgRight),
    mCvKeyLeft(cvkeyLeft),
    mCvKeyRight(cvkeyRight),
    mCvMatchesL2R(matchesL2R),
    mCvMatchesR2L(matchesR2L),
    mCvCorrectMatches(correctMatches),
    mCvWrongMatches(wrongMatches),
    mRefinementMethod(refinementMethod),
    mK(k),
    mRatio(ratio),
    mDistance(distance),
    mConfidence(confidence),
    mFromMI(fromMI),
    mHaveGroundTruth(haveGroundTruth),
    mGroundTruth(groundTruth),
    mLeftImageName(leftImageName),
    mRightImageName(rightImageName),
    mOutputHomographyDir(outputHomographyDir)
{

}

RobustMatcherRefinementProcess::~RobustMatcherRefinementProcess()
{

}

void RobustMatcherRefinementProcess::run(){
    emit newStdData("Starting Robust matching refinement");


    float max_dist=0;
    //    ratio= ui->rat_val->value();
    //    distance= ui->dis_val->value();
    //    confidence=ui->confidence_val->value();



    for (size_t i = 0; i < mCvMatchesL2R.size(); ++i)
    {
        std::vector<cv::DMatch> aux =  mCvMatchesL2R[i];
        for (size_t j = 0; j < aux.size(); ++j)
        {
            cv::DMatch aux_dis = aux[j];
            double dist = aux_dis.distance;
            if( dist > max_dist ) max_dist = dist;

        }
    }
    for (size_t i = 0; i < mCvMatchesR2L.size(); ++i)
    {
        std::vector<cv::DMatch> aux =  mCvMatchesR2L[i];
        for (size_t j = 0; j < aux.size(); ++j)
        {
            cv::DMatch aux_dis = aux[j];
            double dist = aux_dis.distance;
            if( dist > max_dist ) max_dist = dist;

        }
    }

    //find the "good" matches
    std::vector<std::vector< DMatch > > good_matchesl;
    for (size_t i = 0; i < mCvMatchesL2R.size(); ++i)
    {
        std::vector<cv::DMatch> aux =  mCvMatchesL2R[i];
        std::vector<cv::DMatch> good_matchesr_aux;
        for (size_t j = 0; j < aux.size(); ++j)
        {

            cv::DMatch aux_dos = aux[j];
            if (mFromMI)
            {
                if (aux_dos.distance > mK*max_dist) good_matchesr_aux.push_back(aux_dos);
            }
            else
            {
                if (aux_dos.distance < mK*max_dist) good_matchesr_aux.push_back(aux_dos);
            }
        }
        if(good_matchesr_aux.size()>0)good_matchesl.push_back(good_matchesr_aux);
    }

    std::vector< std::vector< DMatch > > good_matchesr;

    for (size_t i = 0; i < mCvMatchesR2L.size(); ++i)
    {
        std::vector<cv::DMatch> aux =  mCvMatchesR2L[i];
        std::vector<cv::DMatch> good_matchesr_aux;
        for (size_t j = 0; j < aux.size(); ++j)
        {

            cv::DMatch aux_dos = aux[j];

            if (mFromMI)
            {
                if (aux_dos.distance > mK*max_dist) good_matchesr_aux.push_back(aux_dos);
            }
            else
            {
                if (aux_dos.distance < mK*max_dist) good_matchesr_aux.push_back(aux_dos);
            }
        }
        if(good_matchesr_aux.size()>0)good_matchesr.push_back(good_matchesr_aux);

    }

    std::vector<cv::DMatch> greenl;
    std::vector<cv::DMatch> greenr;
    std::vector<cv::DMatch> redl;
    std::vector<cv::DMatch> redr;
    cv::Mat rot_mat;
    if (mHaveGroundTruth) {
        mGroundTruth.copyTo(rot_mat);

    }else{
        rot_mat=cv::Mat::eye(3, 3, CV_32F);
    }

    if (good_matchesl.size()>0&&good_matchesr.size()>0)
    {

        if (mRatio!=-1) {
            emit newStdData("Starting ratio test");
            int removed= ratioTest(good_matchesl,mRatio);
            removed = ratioTest(good_matchesr,mRatio);
            emit newStdData("Ratio test finished");
        }

        // 4. Remove non-symmetrical matches
        std::vector<cv::DMatch> symMatches;
        std::vector<cv::DMatch> matches;

        emit newStdData("Starting symmetry test");

        symmetryTest(good_matchesl,good_matchesr,symMatches);
        emit newStdData("Symmetry test finished");

        // 5. Validate matches using RANSAC
        int method;
        switch (mRefinementMethod)
        {
        case 0:
            emit newStdData("Starting LMEDS refinement");
            method =CV_FM_LMEDS;
            break;
        case 1:
            emit newStdData("Starting RANSAC refinement");

            method=CV_FM_RANSAC;
            break;
        case 2:
            emit newStdData("Starting 8-Points refinement");

            method=CV_FM_8POINT;
            break;
        }


        ransacTest(symMatches,mCvKeyLeft, mCvKeyRight, matches,method,mConfidence,mDistance);
        emit newStdData("Refinement test finished");

        if (mHaveGroundTruth){
            emit newStdData("Starting ground truth evaluation");

            for (size_t j = 0; j < matches.size(); ++j)
            {
                float repeteability =0;
                int corres =0;
                cv::DMatch auxxxx;
                auxxxx=matches[j];
                std::vector<cv::KeyPoint> key1;
                std::vector<cv::KeyPoint> key2;
                key1.push_back(mCvKeyLeft[auxxxx.queryIdx]);
                key2.push_back(mCvKeyRight[auxxxx.trainIdx]);
                cv::evaluateFeatureDetector(mCvImgLeft,mCvImgRight,rot_mat,&key1,&key2,repeteability,corres);
                if( corres >0) mCvCorrectMatches.push_back(matches[j]);
                else mCvWrongMatches.push_back(matches[j]);

            }
            emit newStdData("Correct matches: "+QString::number(mCvCorrectMatches.size()));
            emit newStdData("Wrong matches: "+QString::number(mCvWrongMatches.size()));
        }else {
            mCvCorrectMatches=matches;
            emit newStdData("Correct matches: "+QString::number(mCvCorrectMatches.size()));
        }

        //Homography aqui
        //-- Localize the object
          std::vector<Point2f> obj;
          std::vector<Point2f> scene;

          for( int i = 0; i < mCvCorrectMatches.size(); i++ )
          {
            //-- Get the keypoints from the good matches
            obj.push_back( mCvKeyLeft[ mCvCorrectMatches[i].queryIdx ].pt );
            scene.push_back( mCvKeyRight[ mCvCorrectMatches[i].trainIdx ].pt );
          }
        Mat H = findHomography(obj,scene);
        Mat salida;
        warpPerspective(mCvImgLeft, salida, H, mCvImgRight.size(), INTER_LINEAR);

        Mat merged;

        addWeighted(mCvImgRight, 0.5, salida, 0.3, 0.0, merged);
        QString outputHomographyPath =mOutputHomographyDir.absoluteFilePath("homography.png");
        imwrite(outputHomographyPath.toStdString(),merged);
    }
}
