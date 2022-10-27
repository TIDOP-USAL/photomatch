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

#include <sstream>
#include <map>
#include <iomanip>
#include <algorithm>

//#include "precomp.hpp"
#include <opencv2/imgproc/imgproc.hpp>

#include "aff_features2d.hpp"


using namespace std;

namespace cv { namespace affma {




/****************************************************************************************\
*                                  Geometry helpers                                      *
\****************************************************************************************/

Matx33f rotAxisX (const float angle)
{
    return Matx33f (1,  0,           0,
                    0,  cos(angle), -sin(angle),
                    0,  sin(angle),  cos(angle) );
}

Matx33f rotAxisY (const float angle)
{
    return Matx33f (cos(angle),  0,  sin(angle),
                    0,           1,  0,
                   -sin(angle),  0,  cos(angle) );
}

Matx33f rotAxisZ (const float angle)
{
    return Matx33f (cos(angle), -sin(angle),  0,
                    sin(angle),  cos(angle),  0,
                    0,           0,           1 );
}

Matx33f cameraK (const Size& imageSize, const float f)
{
    return Matx33f(f, 0, imageSize.width / 2,
                   0, f, imageSize.height / 2,
                   0, 0, 1 );
}

Matx44f makePose (const Matx33f& R)
{
    return Matx44f (R(0,0), R(0,1), R(0,2), 0,
                    R(1,0), R(1,1), R(1,2), 0,
                    R(2,0), R(2,1), R(2,2), 0,
                    0,      0,      0,      1  );
}

Matx33f pose2H (const Matx33f& K0, const Matx44f& p, const Matx33f& K)
{
    // init R and t separately
    Matx33f absR (p(0,0),p(0,1),p(0,2), p(1,0),p(1,1),p(1,2), p(2,0),p(2,1),p(2,2));
    Matx31f absT (p(0,3),p(1,3),p(2,3));
    // camera cannot be on the ground (z!=0)
    CV_Assert (absT(2) != 0);
    // from absolute reference frame to relative reference frame
    Matx33f R = absR.t();
    Matx31f t = - absR.t() * absT;
    // build H
    Matx33f H = R;
    H(0,2) = t(0);
    H(1,2) = t(1);
    H(2,2) = t(2);
    H = K * H * K0.inv();
    return H;
}




/****************************************************************************************\
*                                  Detectors                                             *
\****************************************************************************************/


// TODO: when affine-transformed part of the image is out of view
class AffFeatureDetectorImpl : public AffFeatureDetector {
protected:

    //! _detector will do actual matching on every viewpoint pair
    const Ptr<FeatureDetector> _detector;
    
    //! _angles contain information about viewpoints
    const Ptr<AffAngles> _angles;
    
private:
    //! used by computeImpl to process a single viewpoint
    vector<KeyPoint> detectFromView (const Mat& im_, const Matx33f& H_, const int viewId_) const;
    
protected:
    // TODO: implement mask
    void detectImpl (const Mat& image, vector<KeyPoint>& keypoints,
                     const Mat& mask=Mat()) const;

public:
    explicit AffFeatureDetectorImpl (const Ptr<FeatureDetector>& detector_,
                                     const Ptr<AffAngles>& angles_)
        : _detector(detector_), _angles(angles_)
        { CV_Assert(_detector); CV_Assert(_angles); }

 /** Detects keypoints and computes the descriptors */
 void detectAndCompute( InputArray image, InputArray mask,
                                           CV_OUT std::vector<KeyPoint>& keypoints,
                                           OutputArray descriptors,
                                           bool useProvidedKeypoints=false )
                                           {
                                               _detector->detectAndCompute(image, mask,keypoints, descriptors, useProvidedKeypoints);
                                           }

virtual void detect( InputArray image, std::vector<KeyPoint>& keypoints,InputArray mask=noArray() )
                                 {
                                     detectImpl(image.getMat(),keypoints,mask.getMat());
                                 }

};

Ptr<AffFeatureDetector>
createAffFeatureDetector (const Ptr<FeatureDetector>& detector,
                          const Ptr<AffAngles>& angles)
{
    return new AffFeatureDetectorImpl (detector, angles);
}

Ptr<AffFeatureDetector>
createAffFeatureDetector (const Ptr<FeatureDetector>& detector,
                          unsigned int maxTilt, unsigned int minTilt)
{
    return new AffFeatureDetectorImpl (detector, createAffAngles(maxTilt, minTilt));
}


vector<KeyPoint> AffFeatureDetectorImpl::detectFromView (const Mat& im_, const Matx33f& H_,
                                                         const int viewId_) const
{
    Mat imWarped;
    warpPerspective (im_, imWarped, H_, im_.size());
    
    std::vector<cv::KeyPoint> keypointsWarped;
    _detector->detect( imWarped, keypointsWarped );
    
    // transform CPs with H and assign viewId
    Matx33f H_inv = H_.inv();
    for (int i = 0; i != keypointsWarped.size(); ++i)
    {
        // transform the keypoint according to the inverse homography
        Point2f point = keypointsWarped[i].pt;
        Matx31f homog (point.x, point.y, 1);
        homog = H_inv * homog;
        homog = homog * (1 / homog(2));
        keypointsWarped[i].pt = Point2f (homog(0), homog(1));
        // assign viewId
        keypointsWarped[i].class_id = viewId_;
    }

    // filter points that turned out to be on the border or outside the image
    vector<KeyPoint> keypoints;
    keypoints.reserve (keypointsWarped.size());
    for (int i = 0; i != keypointsWarped.size(); ++i)
    {
        Point2f& point (keypointsWarped[i].pt);
        int offset = keypointsWarped[i].size * 2;
        if (point.x > offset  &&  point.x < im_.cols - offset &&
            point.y > offset  &&  point.y < im_.rows - offset)
            keypoints.push_back (keypointsWarped[i]);
    }
    
    return keypoints;
}


void AffFeatureDetectorImpl::detectImpl (const Mat& image, vector<KeyPoint>& keypoints,
                                         const Mat& mask) const
{
    keypoints.clear();

    // initialize pose, H, K
    Matx33f H;
    Matx33f K = cameraK (image.size(), (image.rows + image.cols) * 1000);
    Matx44f pose0 (1,0,0,0, 0,1,0,0, 0,0,-1,1, 0,0,0,1);
    
    // create vectors of all pitches and rolls
    std::vector<float> tiltPool = _angles->getActiveTilts();
    std::vector<float> rollPool = _angles->getActiveRolls();
    
    // collect keypoints
    for (int i = 0; i != tiltPool.size(); ++i)
    {
        // turn camera with pitch and roll
        Matx44f pose;
        pose = makePose(rotAxisX (float(tiltPool[i] / 180 * CV_PI))) * pose0;
        pose = makePose(rotAxisZ (float(rollPool[i] / 180 * CV_PI))) * pose;
        H = pose2H (K, pose, K);

        vector<KeyPoint> keypointsView = detectFromView (image, H, i);

        // add keypointsView to the pool
        keypoints.insert (keypoints.end(), keypointsView.begin(), keypointsView.end());
    }
}





/****************************************************************************************\
*                                  Extractors                                           *
\****************************************************************************************/


class AffDescriptorExtractorImpl : public AffDescriptorExtractor
{
private:
    void initAngles (const vector<KeyPoint>& keypoints);
    
protected:
    typedef vector< vector<KeyPoint> > KeypointsByViewType;

    const Ptr<DescriptorExtractor> _extractor;
    Ptr<AffAngles> _angles;
    
    //! helper to extractAllViews for processing a single viewpoint
    Mat extractFromView (const Mat& im_, const Matx33f& H_, vector<KeyPoint>& keypoints_) const;
    
    //! helper to computeImpl
    KeypointsByViewType splitKeypointsByView (const vector<KeyPoint>& keypoints_) const;
    
    //! helper to computeImpl for collecting all descriptors after all initial filtering
    Mat extractAllViews (const Mat& im_,
                         KeypointsByViewType& keypointsByView_,
                         vector<KeyPoint>& keypoints_) const;

    //! implements actual computing descriptors
    void computeImpl (const Mat& im_, vector<KeyPoint>& keypoints_, Mat& descriptors_) const;

public:
    explicit AffDescriptorExtractorImpl (const Ptr<DescriptorExtractor>& extractor_,
                                         const Ptr<AffAngles>& angles_)
        : _extractor(extractor_), _angles(angles_)
        { CV_Assert(_extractor != nullptr); }
    
    //! returns the descriptor size
    int descriptorSize() const { return _extractor->descriptorSize(); }
        
    //! returns the descriptor type
    inline int descriptorType() const { return _extractor->descriptorType(); }

     /** Detects keypoints and computes the descriptors */
 void detectAndCompute( InputArray image, InputArray mask,
                                           CV_OUT std::vector<KeyPoint>& keypoints,
                                           OutputArray descriptors,
                                           bool useProvidedKeypoints=false )
                                           {
                                               _extractor->detectAndCompute(image, mask,keypoints, descriptors, useProvidedKeypoints);
                                           }
virtual void compute( InputArray image,std::vector<KeyPoint>& keypoints,OutputArray descriptors )
{
    computeImpl(image.getMat(),keypoints,descriptors.getMatRef());
}
};

Ptr<AffDescriptorExtractor>
createAffDescriptorExtractor (const Ptr<DescriptorExtractor>& extractor,
                              const Ptr<AffAngles>& angles)
{
    return new AffDescriptorExtractorImpl (extractor, angles);
}

Ptr<AffDescriptorExtractor>
createAffDescriptorExtractor (const Ptr<DescriptorExtractor>& extractor,
                              unsigned int maxTilt, unsigned int minTilt)
{
    return new AffDescriptorExtractorImpl (extractor, createAffAngles(maxTilt, minTilt));
}


// TODO: this function will be used when switching to default _angles
void AffDescriptorExtractorImpl::initAngles (const vector<KeyPoint>& keypoints)
{
    _angles = createAffAngles (AffAngles::MaxPossibleTilt, 0);
    int maxPossibleViews = _angles->getNumViews();
    
    //int minView = maxPossibleViews;
    int maxView = 0;
    for (int i = 0; i != keypoints.size(); ++i)
    {
        //minView = min(keypoints[i].class_id, minView);
        maxView = max(keypoints[i].class_id, maxView);
    }
    
    // make sure that class_id is reasonable, so it is used only by affine-matching
    CV_Assert (maxView <= maxPossibleViews); 
}


Mat AffDescriptorExtractorImpl::extractFromView (const Mat& im_, const Matx33f& H_,
                                                 vector<KeyPoint>& keypoints_) const
{
    // TODO: this warping duplicates warping in featureDetector. It is slow
    Mat imWarped;
    warpPerspective (im_, imWarped, H_, im_.size());

    // transform CPs with H
    vector<KeyPoint> keypointsWarped (keypoints_.size());
    for (int i = 0; i != keypoints_.size(); ++i)
    {
        // transform the keypoint according to the homography
        Point2f point = keypoints_[i].pt;
        Matx31f homog (point.x, point.y, 1);
        homog = H_ * homog;
        assert (homog(2) != 0);
        homog = homog * (1 / homog(2));
        // fill in warped keypoints object
        keypointsWarped[i] = keypoints_[i];
        keypointsWarped[i].pt = Point2f (homog(0), homog(1));
    }

    Mat descriptors;
    _extractor->compute(imWarped, keypointsWarped, descriptors);
    
    // keypoints or their number may change (like in BRISK), so need to get them back
    keypoints_ = vector<KeyPoint> (keypointsWarped.size());
    Matx33f inverseH = H_.inv();
    for (int i = 0; i != keypointsWarped.size(); ++i)
    {
        // transform the keypoint according to the inverse homography
        Point2f point = keypointsWarped[i].pt;
        Matx31f homog (point.x, point.y, 1);
        homog = inverseH * homog;
        assert (homog(2) != 0);
        homog = homog * (1 / homog(2));
        // fill in warped keypoints object
        keypoints_[i] = keypointsWarped[i];
        keypoints_[i].pt = Point2f (homog(0), homog(1));
    }

    CV_Assert (keypoints_.size() == descriptors.rows);

    return descriptors;
}


//! split keypoints by view
AffDescriptorExtractorImpl::KeypointsByViewType
AffDescriptorExtractorImpl::splitKeypointsByView (const vector<KeyPoint>& keypoints_) const
{
    KeypointsByViewType keypointsByView (_angles->getNumViews());
    for (unsigned long i = 0; i != keypoints_.size(); ++i)
    {
        const KeyPoint& keypoint = keypoints_[i];
        CV_Assert (keypoint.class_id >= 0 && keypoint.class_id < keypointsByView.size());
        keypointsByView[keypoint.class_id].push_back(keypoint);
    }
    return keypointsByView;
}


//! helper to computeImpl for collecting all descriptors after all initial filtering
Mat AffDescriptorExtractorImpl::extractAllViews (const Mat& im_,
                                                 vector< vector<KeyPoint> >& keypointsByView_,
                                                 vector<KeyPoint>& keypoints_) const
{
    keypoints_.clear();
    Mat descriptors (0, 0, CV_8U);

    // create sets of all pitches and rolls
    std::vector<float> tiltPool = _angles->getActiveTilts();
    std::vector<float> rollPool = _angles->getActiveRolls();
    unsigned long numViews = _angles->getNumViews();
    CV_Assert(numViews == tiltPool.size());
    
    // initialize pose, H, K
    // FIXME: make an affine camera
    Matx33f H;
    Matx33f K = cameraK (im_.size(), (im_.rows + im_.cols) * 1000);
    Matx44f pose0 (1,0,0,0, 0,1,0,0, 0,0,-1,1, 0,0,0,1);
    
    // extract descriptors by view
    vector<Mat> descriptorsByView (numViews);
    for (int view = 0; view != numViews; ++view)
    {
        // turn camera with pitch and roll
        Matx44f pose;
        pose = makePose(rotAxisX (float(tiltPool[view] / 180 * CV_PI))) * pose0;
        pose = makePose(rotAxisZ (float(rollPool[view] / 180 * CV_PI))) * pose;
        H = pose2H (K, pose, K);
        descriptorsByView[view] = extractFromView (im_, H, keypointsByView_[view]);
        CV_Assert (keypointsByView_[view].size() == descriptorsByView[view].rows);
    }

    // combine descriptors and refill keypoints (keypointsByView could have changed, e.g. in BRISK)
    for (int view = 0; view != numViews; ++view)
    {
        keypoints_.insert (keypoints_.end(),
                           keypointsByView_[view].begin(), keypointsByView_[view].end());
        descriptors.push_back (descriptorsByView[view]);
    }

    CV_Assert (keypoints_.size() == descriptors.rows);
    return descriptors;
}


void AffDescriptorExtractorImpl::computeImpl (const Mat& im_, vector<KeyPoint>& keypoints_,
                                              Mat& descriptors_) const
{
    KeypointsByViewType keypointsByView = splitKeypointsByView (keypoints_);
    descriptors_ = extractAllViews (im_, keypointsByView, keypoints_);
}






/****************************************************************************************\
*                                   Feature2D                                           *
\****************************************************************************************/
//
//
//// when Feature2D can be used instead of both Detector and Descriptor
//class AffFeature2D : public AffFeatureDetectorImpl, AffDescriptorExtractorImpl {
//
//    explicit AffFeature2D (const Ptr<Feature2D>& feature2d_, const Ptr<AffAngles>& angles_)
//        : AffFeatureDetectorImpl (Ptr<FeatureDetector>(feature2d_), angles_),
//          AffDescriptorExtractorImpl (Ptr<DescriptorExtractor>(feature2d_), angles_)
//        { }
//    
//    explicit AffFeature2D (const Ptr<Feature2D>& feature2d_,
//                           unsigned int maxTilt, unsigned int minTilt = 0)
//        : AffFeatureDetectorImpl( Ptr<FeatureDetector>(feature2d_),
//                                  createAffAngles(maxTilt, minTilt)),
//          AffDescriptorExtractorImpl( Ptr<DescriptorExtractor>(feature2d_),
//                                      createAffAngles(maxTilt, minTilt))
//        { }
//};





}} // namespace