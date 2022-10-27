/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  An OpenCV Implementation of affine-covariant matching (matching with different viewpoints)
//  Further Information Refer to:
//  Author: Evgeny Toropov
//  etoropov@andrew.cmu.edu
//
// IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
// 
// By downloading, copying, installing or using the software you agree to this license.
// If you do not agree to this license, do not download, install,
// copy or use the software.
// 
// 
//                           License Agreement
//                For Open Source Computer Vision Library
// 
// Copyright (C) 2000-2008, Intel Corporation, all rights reserved.
// Copyright (C) 2008-2013, Willow Garage Inc., all rights reserved.
// Third party copyrights are property of their respective owners.
// 
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
// 
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
// 
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include <iostream>
#include <map>
#include <iomanip>

#include <opencv2/imgproc/imgproc.hpp>

//#include "precomp.hpp"
#include "aff_features2d.hpp"


using namespace std;

namespace cv { namespace affma {


/****************************************************************************************\
*                                  Filters                                              *
\****************************************************************************************/

class DuplicateFilter {
private:
    const float DetectorAccuracy;
    typedef vector< vector<KeyPoint> > KeypointsByViewType;
    
    void splitKeypointsByView (const vector<KeyPoint>& keypoints, KeypointsByViewType& split)
    {
        split.clear();
        for (vector<KeyPoint>::const_iterator it = keypoints.begin(); it != keypoints.end(); ++it)
        {
            int view = it->class_id;
            CV_Assert (view >= 0);
            if (split.size() < view) split.resize(view);
            split[view].push_back(*it);
        }
    }
public:
    DuplicateFilter() : DetectorAccuracy(1.5f) { }
    
    void mergeDuplicates (const vector<KeyPoint>& keypoints1, const vector<KeyPoint>& keypoints2,
                          vector<DMatch>& matches, vector<float>& scores)
    {
        // split keypoints by view
        KeypointsByViewType keysByView1, keysByView2;
        splitKeypointsByView (keypoints1, keysByView1);
        splitKeypointsByView (keypoints2, keysByView2);
        
        // get the keypoint info in one Mat
        Mat elems (4, int(matches.size()), CV_32F);
        for (vector<DMatch>::const_iterator it = matches.begin(); it != matches.end(); ++it)
        {
            elems.at<float>(keypoints1[it->queryIdx].pt.x);
            elems.at<float>(keypoints1[it->queryIdx].pt.y);
            elems.at<float>(keypoints2[it->trainIdx].pt.x);
            elems.at<float>(keypoints2[it->trainIdx].pt.y);
        }
        
        Mat sortedIndices;
        sortIdx(elems, sortedIndices, cv::SORT_EVERY_ROW | cv::SORT_ASCENDING);
    }
};





/****************************************************************************************\
*                                  Helper                                               *
\****************************************************************************************/


class AffMatcherHelperImpl : public AffMatcherHelper {
protected:

    Mat _queryDescriptors, _trainDescriptors;

    Ptr<AffAngles>              _angles;
    Ptr<AffFeatureDetector>     _adetector;
    Ptr<AffDescriptorExtractor> _aextractor;
    Ptr<AffDescriptorMatcher>   _amatcher;
    
    int                         _verbosity;
    
    void withMaxTiltImpl( const Mat& im1, const Mat& im2,
                          vector<KeyPoint>& keypoints1, vector<KeyPoint>& keypoints2,
                          vector<DMatch>& matches, const float threshNNDR, const unsigned int maxTilt);
    
    void matchImpl ( const vector<KeyPoint>& queryKeypoints, const vector<KeyPoint>& trainKeypoints,
                     const Mat& queryDescriptors, const Mat& trainDescriptors,
                     vector<DMatch>& matches, const float knnThresh);
public:

    AffMatcherHelperImpl( Ptr<FeatureDetector> detector_,
                          Ptr<DescriptorExtractor> extractor_,
                          Ptr<DescriptorMatcher> matcher_ );
    
    void matchWithMaxTilt(    const Mat& im1, const Mat& im2,
                              vector<KeyPoint>& keypoints1, vector<KeyPoint>& keypoints2,
                              vector<DMatch>& matches,
                              const float threshNNDR,
                              const unsigned int maxTilt);
    
    void matchIncreasingTilt( const Mat& im1, const Mat& im2,
                              vector<KeyPoint>& keypoints1, vector<KeyPoint>& keypoints2,
                              vector<DMatch>& matches,
                              const float threshNNDR,
                              const int minMatches = 10);

    void matchMultiRes(       const Mat& im1, const Mat& im2,
                              vector<KeyPoint>& keypoints1, vector<KeyPoint>& keypoints2,
                              vector<cv::DMatch>& matches,
                              const float threshNNDR,
                              const unsigned int maxTilt,
                              const float subsamplingFactor = 0.33f,
                              const unsigned int keepViewPairs = 5);
    
    void getDescriptors(      cv::Mat& queryDescr, cv::Mat& trainDescr );

    inline void setVerbosity(int verbosity) { _verbosity = verbosity; }
};

CV_EXPORTS Ptr<AffMatcherHelper> createAffMatcherHelper
       (Ptr<FeatureDetector> detector,
        Ptr<DescriptorExtractor> extractor,
        Ptr<DescriptorMatcher> matcher)
{
    return new AffMatcherHelperImpl( detector, extractor, matcher );
}


AffMatcherHelperImpl::AffMatcherHelperImpl( Ptr<FeatureDetector> detector_,
                                            Ptr<DescriptorExtractor> extractor_,
                                            Ptr<DescriptorMatcher> matcher_ )
    : _angles     (createAffAngles (AffAngles::MaxPossibleTilt, 0)),
      _adetector  (createAffFeatureDetector (detector_, _angles)),
      _aextractor (createAffDescriptorExtractor (extractor_, _angles)),
      _amatcher   (createAffDescriptorMatcher (matcher_)),
      _verbosity  (0)
    { }


void AffMatcherHelperImpl::matchImpl
                   ( const vector<KeyPoint>& queryKeypoints, const vector<KeyPoint>& trainKeypoints,
                     const Mat& queryDescriptors, const Mat& trainDescriptors,
                     vector<DMatch>& matches, const float threshNNDR)
{
    vector<vector<DMatch> > matchesKnn;
    _amatcher->knnMatch( queryKeypoints, trainKeypoints, queryDescriptors, trainDescriptors,
                         matchesKnn, 2 );
    
    // keep only good matches
    matches.clear();
    for (int i = 0; i != matchesKnn.size(); ++i)
    {
        if (matchesKnn[i].size() < 2)
        {
            if (_verbosity > 1)
                cout << "AffMatcherHelperImpl::matchImpl warning: less than 2 matches found" << endl;
            continue;
        }
        if (matchesKnn[i][1].distance == 0)
        {
            if (_verbosity > 1)
                cout << "AffMatcherHelperImpl::matchImpl warning: match distance = 0 detected" << endl;
            continue;
        }
        
        // finally comparing two closest matches
        if (matchesKnn[i][0].distance / matchesKnn[i][1].distance < threshNNDR)
            matches.push_back (matchesKnn[i][0]);
    }
    
    if (_verbosity) cout << matches.size() << " matches" << endl;
}


void AffMatcherHelperImpl::withMaxTiltImpl
                   ( const Mat& im1, const Mat& im2,
                     vector<KeyPoint>& queryKeypoints, vector<KeyPoint>& trainKeypoints,
                     vector<DMatch>& matches, const float threshNNDR, const unsigned int maxTilt )
{
    cout << "with " << endl;
    _queryDescriptors = Mat();
    _trainDescriptors = Mat();
    
    queryKeypoints.clear();
    trainKeypoints.clear();
    matches.clear();

    CV_Assert (maxTilt <= AffAngles::MaxPossibleTilt);
    _angles->setMinTilt(0);
    _angles->setMaxTilt(maxTilt);

    _adetector->detect (im1, queryKeypoints);
    _adetector->detect (im2, trainKeypoints);
    if (_verbosity)
        cout << queryKeypoints.size() << " vs " << trainKeypoints.size() << " keypoints, " << flush;
    
    _aextractor->compute( im1, queryKeypoints, _queryDescriptors );
    _aextractor->compute( im2, trainKeypoints, _trainDescriptors );
    if (_verbosity)
        cout << _queryDescriptors.rows << " vs " << _trainDescriptors.rows << " descr., " << flush;

    matchImpl(queryKeypoints, trainKeypoints, _queryDescriptors, _trainDescriptors, matches, threshNNDR);
}


void AffMatcherHelperImpl::matchWithMaxTilt
                (const Mat& im1, const Mat& im2,
                 vector<KeyPoint>& queryKeypoints, vector<KeyPoint>& trainKeypoints,
                 vector<DMatch>& matches, const float knnThresh, const unsigned int maxPitch)
{
    cout << "tttt" << endl;
    withMaxTiltImpl (im1, im2, queryKeypoints, trainKeypoints, matches, knnThresh, maxPitch);
}


void AffMatcherHelperImpl::matchIncreasingTilt
                (const Mat& im1, const Mat& im2,
                 vector<KeyPoint>& queryKeypoints, vector<KeyPoint>& trainKeypoints,
                 vector<DMatch>& matches, const float knnThresh, const int minMatches)
{
    _queryDescriptors = Mat();
    _trainDescriptors = Mat();
    
    queryKeypoints.clear();
    trainKeypoints.clear();
    matches.clear();
    
    for (int tilt = 1; tilt != AffAngles::MaxPossibleTilt; ++tilt)
    {
        _angles->setMinTilt (tilt - 1);
        _angles->setMaxTilt (tilt);
        
        vector<KeyPoint> queryKeypointsLevel, trainKeypointsLevel;
        Mat queryDescriptorLevel, trainDescriptorLevel;
        vector<DMatch> matchesLevel;
        
        if (_verbosity) cout << "tilt " << tilt << ", " << flush;
 
        _adetector->detect( im1, queryKeypointsLevel );
        _adetector->detect( im2, trainKeypointsLevel );

        _aextractor->compute( im1, queryKeypointsLevel, queryDescriptorLevel );
        _aextractor->compute( im2, trainKeypointsLevel, trainDescriptorLevel );
    
        queryKeypoints.insert( queryKeypoints.end(),
                               queryKeypointsLevel.begin(), queryKeypointsLevel.end() );
        trainKeypoints.insert( trainKeypoints.end(),
                               trainKeypointsLevel.begin(), trainKeypointsLevel.end() );
        _queryDescriptors.push_back( queryDescriptorLevel );
        _trainDescriptors.push_back( trainDescriptorLevel );
        if (_verbosity)
        {
            cout << queryKeypoints.size() << " vs " << trainKeypoints.size() << " points, " << flush;
            cout << _queryDescriptors.rows << " vs " << _trainDescriptors.rows << " descr., " << flush;
        }
        
        matchImpl( queryKeypoints, trainKeypoints, _queryDescriptors, _trainDescriptors,
                   matches, knnThresh );
        
        if (matches.size() >= minMatches) break;
    }
    
    CV_Assert (queryKeypoints.size() == _queryDescriptors.rows);
    CV_Assert (trainKeypoints.size() == _trainDescriptors.rows);
}


// used for partial_sort_copy
bool mapElemHigherThan (const map<pair<int, int>, int>::value_type& a,
                        const map<pair<int, int>, int>::value_type& b) { return a.second > b.second; }

void AffMatcherHelperImpl::matchMultiRes
              ( const Mat& im1, const Mat& im2,
                vector<KeyPoint>& keypoints1, vector<KeyPoint>& keypoints2, vector<DMatch>& matches,
                const float threshNNDR, const unsigned int maxTilt,
                const float subsamplingFactor, const unsigned int keepViewPairs)
{
    // resample image
    Mat im1sm, im2sm;
    resize (im1, im1sm, Size(), subsamplingFactor, subsamplingFactor);
    resize (im2, im2sm, Size(), subsamplingFactor, subsamplingFactor);

    // match with lower resolution
    if (_verbosity) cout << "AffMatcherHelperImpl::matchMultiRes max_tilt: " << maxTilt << endl;
    withMaxTiltImpl( im1sm, im2sm, keypoints1, keypoints2, matches, threshNNDR, maxTilt);
    
    map<pair<int, int>, int> numByViewPairs;
    for (int iMatch = 0; iMatch != matches.size(); ++iMatch)
    {
        const DMatch& match = matches[iMatch];
        int view1 = keypoints1[match.queryIdx].class_id;
        int view2 = keypoints2[match.trainIdx].class_id;
        numByViewPairs[make_pair(view1, view2)] ++;
    }
    
    // get the best N = keepViewPairs view pairs from numByViewPairs map
    vector< pair<pair<int, int>, int> > vect (keepViewPairs);
    partial_sort_copy( numByViewPairs.begin(), numByViewPairs.end(),
                       vect.begin(), vect.end(), mapElemHigherThan );

    if (_verbosity)
        cout << "AffMatcherHelperImpl::matchMultiRes lowres. matches number: " << matches.size() << endl;

    // ... and put these N view pairs into a set
    set< pair<int, int> > bestViewPairs;
    for (int i = 0; i != vect.size(); ++i)
        bestViewPairs.insert( vect[i].first );
    
    // set the best view pairs
    _amatcher->setViewPairsPool( bestViewPairs );
    
    // match with original resolution only the chosen view pairs
    withMaxTiltImpl( im1, im2, keypoints1, keypoints2, matches, threshNNDR, maxTilt );

    if (_verbosity)
        cout << "AffMatcherHelperImpl::matchMultiRes fullres. matches number: " << matches.size() << endl;
}


void AffMatcherHelperImpl::getDescriptors( cv::Mat& queryDescr, cv::Mat& trainDescr )
{
    queryDescr = _queryDescriptors;
    trainDescr = _trainDescriptors;
}





bool isDuplicatePair (const Mat& match1, const Mat& match2, const float cutoff)
{
    float dx1 = std::abs(match1.at<float>(0) - match2.at<float>(0));
    float dy1 = std::abs(match1.at<float>(1) - match2.at<float>(1));
    float ds1 = std::abs(match1.at<float>(2) - match2.at<float>(2));
    float dx2 = std::abs(match1.at<float>(4) - match2.at<float>(4));
    float dy2 = std::abs(match1.at<float>(5) - match2.at<float>(5));
    float ds2 = std::abs(match1.at<float>(6) - match2.at<float>(6));
    if (dx1 == 0 && dx2 == 0 && dy1 == 0 && dy2 == 0) return false;
    if (dx1 + dy1 < cutoff && dx2 + dy2 < cutoff && ds1 < cutoff && ds2 < cutoff) return true;
    return false;
}


void filterDuplicateMatches   (const std::vector<cv::KeyPoint>& queryKeypoints,
                               const std::vector<cv::KeyPoint>& trainKeypoints,
                               std::vector<cv::DMatch>& matches, float cutoff)
{
    Mat matchesDescr;
    const float SizeWeight = 0.1;
    const float AngleWeight = 0.025f;
    for (int i = 0; i != matches.size(); ++i)
    {
        const KeyPoint& key1 = queryKeypoints[matches[i].queryIdx];
        const KeyPoint& key2 = trainKeypoints[matches[i].trainIdx];
        float row[8] = { key1.pt.x, key1.pt.y, key1.size * SizeWeight, key1.angle * AngleWeight,
                         key2.pt.x, key2.pt.y, key2.size * SizeWeight, key2.angle * AngleWeight };
        matchesDescr.push_back(Mat(1, 8, CV_32FC1, &row));
    }
    assert (matchesDescr.rows == matches.size());

    
    // matches marked for removal
    vector<bool> toBeRemoved = vector<bool>(matches.size(), false);
    
    // bruteforce matching since the number is usually low
    for (int i = 0; i != matchesDescr.rows; ++i)
        // only for those that are still alive
        if (! toBeRemoved[i] )
            // mark all duplicates for a match
            for (int j = 0; j != i; ++j)
                if (isDuplicatePair(matchesDescr.row(i), matchesDescr.row(j), cutoff))
                {
                    // kill it
                    toBeRemoved[j] = true;
                    #ifdef DEBUG_FILTER
                        cout << "indices: " << i << " (" << matches[i].queryIdx << "," << matches[i].trainIdx
                             << ") vs "     << j << " (" << matches[j].queryIdx << "," << matches[j].trainIdx
                             << ") = " << sum(abs(matchesDescr.row(i) - matchesDescr.row(j)))[0] << endl;
                        cout << "descr: " << matchesDescr.row(i) << " vs " << endl
                             << "       " << matchesDescr.row(j) << endl;
                    #endif
                }

    for (int i = int(toBeRemoved.size())-1; i > 0; --i)
        if (toBeRemoved[i])
            matches.erase(matches.begin() + i);
            
    cout << toBeRemoved.size() - matches.size() << " out of " << toBeRemoved.size()
         << " matches were erased by duplicateMatches filter" << endl;

//    #ifdef DEBUG_FILTER
//        // remove trailing zeros
//        while ( duplicHist.back() == 0 )
//            duplicHist.pop_back();
//        cout << "Duplicate statistics: { ";
//        for (int i = 0; i != duplicHist.size(); ++i)
//            cout << duplicHist[i] << " ";
//        cout << "}" << endl;
//    #endif

}




void printMatchHistogram (const vector<KeyPoint>& keypoints1, const vector<KeyPoint>& keypoints2,
                          const vector<DMatch>& matches, const unsigned int maxTilt )
{
    cout << "affma::printMatchHistogram: total matches number: " << matches.size() << endl;
    
    Ptr<AffAngles> angles = createAffAngles (maxTilt); 
    
    // get histogram of matches
    int numViews = angles->getNumViews();
    Mat histogram = Mat::zeros (numViews, numViews, CV_32S);
    for (int i = 0; i != matches.size(); ++i)
        ++histogram.at<int> (keypoints1[matches[i].queryIdx].class_id,
                             keypoints2[matches[i].trainIdx].class_id);
    
    const int MaxNumPrinted = 15;
    int iTilt1 = 0, iRoll1 = 0;
    for (int iView1 = 0; iView1 != numViews && iView1 != MaxNumPrinted; ++iView1)
    {
        // print a line of numbers
        int iTilt2 = 0, iRoll2 = 0;
        for (int iView2 = 0; iView2 != numViews && iView2 != MaxNumPrinted; ++iView2)
        {
            int num = histogram.at<int>(iView1, iView2);
            ostringstream oss;
            oss << num;
            cout << std::fixed << std::setw(4) << (num > 0 ? oss.str() : ".");
            ++iRoll2;
            if (iRoll2 == angles->getNumRolls(iTilt2)) { ++iTilt2; iRoll2 = 0; cout << " |"; }
        }
        cout << endl;
        ++iRoll1;
        
        // next tilt
        if (iRoll1 == angles->getNumRolls(iTilt1))
        {
            ++iTilt1;
            iRoll1 = 0;
            
            // print a separation line
            int iTilt2 = 0, iRoll2 = 0;
            for (int iView2 = 0; iView2 != numViews && iView2 != MaxNumPrinted; ++iView2)
            {
                cout << "----";
                ++iRoll2;
                if (iRoll2 == angles->getNumRolls(iTilt2)) { ++iTilt2; iRoll2 = 0; cout << "-+"; }
            }
            cout << endl;
        }
    }
}




}} // namespaces


