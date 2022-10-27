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

#ifndef _OPENCV_AFFMATCH_HPP_
#define _OPENCV_AFFMATCH_HPP_ 

#include <set>
#include <algorithm>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#ifdef __cplusplus


namespace cv { namespace affma {



/*
 *  AffAngles manages viewpoints [see asift paper].
 *    It is used by FeatureDetector and DescriptorExtractor to decide how to warp image
 *    The user is currently responsible for setting the highest bound of tilt
 */
class AffAngles {
public:

    virtual ~AffAngles() { }

    static const unsigned int MaxPossibleTilt = 6;
    static const unsigned int MaxPossibleNumViews = 41; // = 1 + 4 + 5 + 7 + 10 + 14

    /*
     * tilt (latitude) is the level of image affine distortion. Image(tilt=0) == Image
     * the following should hold: 0 <= minTilt <= tilt < maxTilt <= MaxPossibleTilt == 6
     *   'minTilt', 'maxTilt' - are set by the user and can be changed
     *                          by default, minTilt=begin() and maxTilt=begin()+3
     *   'tilt' goes through all available values during matching
     *
     * roll (longitude) goes through a set of predefined values, different for every tilt
     *   roll is not controlled by the user
     */
    
    virtual void          setMinTilt(unsigned int minTilt) = 0;
    virtual unsigned int  getMinTilt() const = 0;
    virtual void          setMaxTilt(unsigned int maxTilt) = 0;
    virtual unsigned int  getMaxTilt() const = 0;
    
    virtual unsigned int  getNumViews() const = 0;
    virtual unsigned int  getNumTilts() const = 0;
    virtual unsigned int  getNumRolls(unsigned int tilt) const = 0;
    
    virtual std::vector<float>  getActiveTilts() const = 0;
    virtual std::vector<float>  getActiveRolls() const = 0;
    
    virtual void          printActiveAngles (std::ostream& os) const = 0;
};

CV_EXPORTS Ptr<AffAngles> createAffAngles (unsigned int maxTilt = 1, unsigned int minTilt = 0);



class AffFeatureDetector : public FeatureDetector {
    public: virtual ~AffFeatureDetector() { }
};

CV_EXPORTS Ptr<AffFeatureDetector> createAffFeatureDetector
    (const Ptr<FeatureDetector>& detector,
     const Ptr<AffAngles>& angles);

CV_EXPORTS Ptr<AffFeatureDetector> createAffFeatureDetector
    (const Ptr<FeatureDetector>& detector,
     unsigned int maxTilt, unsigned int minTilt = 0);



class AffDescriptorExtractor : public DescriptorExtractor {
    public: virtual ~AffDescriptorExtractor() { }
};

// TODO: make angles optional
CV_EXPORTS Ptr<AffDescriptorExtractor> createAffDescriptorExtractor
    (const Ptr<DescriptorExtractor>& extractor,
     const Ptr<AffAngles>& angles);

CV_EXPORTS Ptr<AffDescriptorExtractor> createAffDescriptorExtractor
    (const Ptr<DescriptorExtractor>& detector,
     unsigned int maxTilt, unsigned int minTilt = 0);



//class AffFeature2D;
//
//CV_EXPORTS Ptr<AffFeature2D> createAffFeature2D
//    (const Ptr<Feature2D>& feature2d,
//     const Ptr<AffAngles>& angles);
//
//CV_EXPORTS Ptr<AffFeature2D> createAffFeature2D
//    (const Ptr<Feature2D>& feature2d,
//     unsigned int maxTilt, unsigned int minTilt = 0);
//


// does not inherit from DescriptorMatcher because method signatures are different
class AffDescriptorMatcher : public Algorithm {
public:

    virtual ~AffDescriptorMatcher() { }

    virtual bool isMaskSupported() const = 0;
    
    virtual void setViewPairsPool (std::set< std::pair<int, int> > viewPairsPool) = 0;

    virtual void match(       const std::vector<KeyPoint>& queryKeypoints,
                              const std::vector<KeyPoint>& trainKeypoints,
                              const Mat& queryDescriptors, const Mat& trainDescriptors,
                              CV_OUT std::vector<DMatch>& matches, const Mat& mask=Mat() ) const = 0;

    virtual void knnMatch(    const std::vector<KeyPoint>& queryKeypoints,
                              const std::vector<KeyPoint>& trainKeypoints,
                              const Mat& queryDescriptors, const Mat& trainDescriptors,
                              CV_OUT std::vector<std::vector<DMatch> >& matches, int k,
                              const Mat& mask=Mat(), bool compactResult=false ) const = 0;

    virtual void radiusMatch( const std::vector<KeyPoint>& queryKeypoint,
                              const std::vector<KeyPoint>& trainKeypoints,
                              const Mat& queryDescriptors, const Mat& trainDescriptors,
                              std::vector<std::vector<DMatch> >& matches, float maxDistance,
                              const Mat& mask=Mat(), bool compactResult=false ) const = 0;
};

CV_EXPORTS Ptr<AffDescriptorMatcher> createAffDescriptorMatcher
     (const Ptr<DescriptorMatcher>& matcher);




class AffMatcherHelper {
public:
    virtual ~AffMatcherHelper() { }

    // threshNNDR - is for getting good matches based on ratio of descriptor distance
    //              to the 2nd best and to the best match.
    //              The higher, the fewer matches are kept.
    //              Typical value for SIFT could be ~0.3, for ORB -- ~0.7

    // pipeline from [2]
    virtual void matchWithMaxTilt(    const cv::Mat& im1, const cv::Mat& im2,
                                      std::vector<cv::KeyPoint>& keypoints1,
                                      std::vector<cv::KeyPoint>& keypoints2,
                                      std::vector<cv::DMatch>& matches,
                                      const float threshNNDR,
                                      const unsigned int maxTilt) = 0;
    
    // alternative pipeline from [2]
    virtual void matchIncreasingTilt( const cv::Mat& im1, const cv::Mat& im2,
                                      std::vector<cv::KeyPoint>& keypoints1,
                                      std::vector<cv::KeyPoint>& keypoints2,
                                      std::vector<cv::DMatch>& matches,
                                      const float threshNNDR,
                                      const int minMatches = 10) = 0;
    
    // pipeline from [1]
    virtual void matchMultiRes(       const cv::Mat& im1, const cv::Mat& im2,
                                      std::vector<cv::KeyPoint>& keypoints1,
                                      std::vector<cv::KeyPoint>& keypoints2,
                                      std::vector<cv::DMatch>& matches,
                                      const float threshNNDR,
                                      const unsigned int maxTilt,
                                      const float subsamplingFactor = 0.33f,
                                      const unsigned int numViewPairs = 5) = 0;
    
    // use this function to collect descriptors after matching if necessary
    virtual void getDescriptors(      cv::Mat& queryDescr, cv::Mat& trainDescr ) = 0;

    virtual void setVerbosity(        int verbosity) = 0;
};

CV_EXPORTS Ptr<AffMatcherHelper> createAffMatcherHelper
       (Ptr<FeatureDetector> detector,
        Ptr<DescriptorExtractor> extractor,
        Ptr<DescriptorMatcher> matcher);




///    Helper functions    ///

// list of matches will be reduced to non-duplicates
void filterDuplicateMatches   (const std::vector<cv::KeyPoint>& queryKeypoints,
                               const std::vector<cv::KeyPoint>& trainKeypoints,
                               std::vector<cv::DMatch>& matches, float minDist);


void printMatchHistogram( const std::vector<KeyPoint>& queryKeypoints,
                          const std::vector<KeyPoint>& trainKeypoints,
                          const std::vector<DMatch>& matches,
                          const unsigned int maxTilt );


}} // namespace
#endif
#endif
