/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#ifndef PHOTOMATCH_FEATURES_H
#define PHOTOMATCH_FEATURES_H

#include "photomatch/photomatch_global.h"

#include <memory>

#include <QSize>
#include <QString>

#include <opencv2/features2d.hpp>

#include <tidop/core/flags.h>

namespace photomatch
{


class PHOTOMATCH_EXPORT Feature
{

public:

  enum class Type
  {
    agast,
    akaze,
    asift,
    boost,
    brief,
    brisk,
    d2net,
    daisy,
    fast,
    freak,
    gftt,
    hog,
    kaze,
    latch,
    lucid,
    lss,
    msd,
    mser,
    orb,
    r2d2,
    sift,
    star,
    surf,
    vgg
  };
///TODO: GLOH -> https://www.robots.ox.ac.uk/~vgg/research/affine/det_eval_files/mikolajczyk_pami2004.pdf

public:

  Feature() {}
  virtual ~Feature() = default;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;

  virtual Type type() const = 0;
  virtual QString name() const = 0;

//protected:
//
//  tl::EnumFlags<Type> mFeatType;

};
ALLOW_BITWISE_FLAG_OPERATIONS(Feature::Type)



class PHOTOMATCH_EXPORT FeatureBase
  : public Feature
{

public:

  FeatureBase(Type type) : mFeatType(type) {}
  ~FeatureBase() override = default;

  Type type() const override 
  { 
    return mFeatType.flags(); 
  }

protected:

  tl::EnumFlags<Type> mFeatType;

};



/*----------------------------------------------------------------*/


/*!
 * \brief Keypoint Detector class
 */
class PHOTOMATCH_EXPORT KeypointDetector
{

public:

  KeypointDetector() {}
  virtual ~KeypointDetector() = default;

  /*!
   * \brief Detects keypoints in an image
   * \param[in] img Image
   * \param[in] mask Optional mask
   * \return key points detected
   */
  virtual std::vector<cv::KeyPoint> detect(const cv::Mat &img,
                                           const cv::Mat &mask = cv::Mat()) = 0;
};



/*----------------------------------------------------------------*/


/*!
 * \brief Descriptor Extractor class
 */
class PHOTOMATCH_EXPORT DescriptorExtractor
{

public:

  DescriptorExtractor() {}
  virtual ~DescriptorExtractor() = default;

  /*!
   * \brief Extract descriptors
   * \param[in] img Image
   * \param[in] keyPoints KeyPoints
   * \return Computed descriptors
   */
  virtual cv::Mat extract(const cv::Mat &img,
                          std::vector<cv::KeyPoint> &keyPoints) = 0;
};



/*----------------------------------------------------------------*/



class PHOTOMATCH_EXPORT FeatureExtractorPython
{

public:

  FeatureExtractorPython() {}
  virtual ~FeatureExtractorPython() = default;

  virtual void extract(const QString &imagePath,
                       const QString &featuresPath) = 0;
};



/*----------------------------------------------------------------*/



/*!
 * \brief Agast Interface
 * AGAST: Adaptive and Generic Corner Detection Based on the Accelerated Segment Test
 *
 * Mair E., Hager G.D., Burschka D., Suppa M., Hirzinger G. (2010) Adaptive and Generic
 * Corner Detection Based on the Accelerated Segment Test. In: Daniilidis K., Maragos P.,
 * Paragios N. (eds) Computer Vision – ECCV 2010. ECCV 2010.
 * Lecture Notes in Computer Science, vol 6312. Springer, Berlin, Heidelberg
 * https://mediatum.ub.tum.de/doc/1287456/1287456.pdf
 */
class PHOTOMATCH_EXPORT Agast
  : public FeatureBase
{

public:

  Agast() : FeatureBase(Feature::Type::agast) {}
  ~Agast() override = default;

  /*!
   * \brief threshold
   * The AST applies a minimum difference threshold when comparing
   * the value of a pixel on the pattern with the brightness of
   * the nucleus. This parameter controls the sensitivity of the
   * corner response.
   * A large threshold value results in few but therefore only
   * strong corners, while a small threshold value yields also
   * corners with smoother gradients.
   * \return
   */
  virtual int threshold() const = 0;

  /*!
   * \brief Non Maximal Suppression for removing adjacent corners
   * \return
   */
  virtual bool nonmaxSuppression() const = 0;

  /*!
   * \brief Detector Types
   * - AGAST_5_8: AGAST-5 decision tree whith the 8 pixels mask
   * - AGAST_7_12d: AGAST-7 decision tree whith the Diamond shaped 12 pixels mask
   * - AGAST_7_12s: AGAST-7 decision tree whith the Squared shaped 12 pixels mask
   * - OAST_9_16: OAST-9 (Optimal AST) decision tree whith the 16 pixels mask
   * \return Detector Type
   */
  virtual QString detectorType() const = 0;

  /*!
   * \brief Set Threshold
   * \param[in] threshold Default=10
   */
  virtual void setThreshold(int threshold) = 0;

  /*!
   * \brief Set Non Maximal Suppression
   * \param[in] nonmaxSuppression Non Maximal Suppression for removing adjacent corners (Default=true)
   */
  virtual void setNonmaxSuppression(bool nonmaxSuppression) = 0;

  /*!
   * \brief Set the Detector Type
   * Suported types:
   * - AGAST_5_8: AGAST-5 decision tree with the 8 pixels mask
   * - AGAST_7_12d: AGAST-7 decision tree with the Diamond shaped 12 pixels mask
   * - AGAST_7_12s: AGAST-7 decision tree with the Squared shaped 12 pixels mask
   * - OAST_9_16: OAST-9 (Optimal AST) decision tree with the 16 pixels mask
   *
   * \param[in] detectorType Detector Type (Default = OAST_9_16)
   */
  virtual void setDetectorType(const QString &detectorType) = 0;

};




/*----------------------------------------------------------------*/




/*!
 * \brief The Akaze class
 */
class PHOTOMATCH_EXPORT Akaze
  : public FeatureBase
{

public:

  Akaze() : FeatureBase(Feature::Type::akaze) {}
  ~Akaze() override = default;

  /*!
   * \brief Type of the extracted descriptor
   * \return KAZE, KAZE_UPRIGHT, MLDB or MLDB_UPRIGHT
   */
  virtual QString descriptorType() const = 0;

  /*!
   * \brief Size of the descriptor in bits. 0 -\> Full size
   * \return Descriptor size
   */
  virtual int descriptorSize() const = 0;

  /*!
   * \brief Number of channels in the descriptor [1, 2, 3 (default)]
   * \return Number of channels
   */
  virtual int descriptorChannels() const = 0;

  /*!
   * \brief Detector response threshold to accept point
   * \return threshold
   */
  virtual double threshold() const = 0;

  /*!
   * \brief Maximum octave evolution of the image
   * \return
   */
  virtual int octaves() const = 0;

  /*!
   * \brief Default number of sublevels per scale level
   * \return
   */
  virtual int octaveLayers() const = 0;

  /*!
   * \brief Diffusivity type
   * \return DIFF_PM_G1, DIFF_PM_G2 (default), DIFF_WEICKERT or DIFF_CHARBONNIER
   */
  virtual QString diffusivity() const = 0;

  /*!
   * \brief Set the type of the extracted descriptor
   * \param[in] descriptorType Descriptor type: KAZE, KAZE_UPRIGHT, MLDB or MLDB_UPRIGHT
   */
  virtual void setDescriptorType(const QString &descriptorType) = 0;

  /*!
   * \brief Set the size of the descriptor in bits.
   * \param[in] descriptorSize
   */
  virtual void setDescriptorSize(int descriptorSize) = 0;

  /*!
   * \brief Set the number of channels in the descriptor
   * \param[in] channels 1, 2 or 3 (default)
   */
  virtual void setDescriptorChannels(int channels) = 0;

  /*!
   * \brief Set the detector response threshold to accept point
   * \param[in] threshold
   */
  virtual void setThreshold(double threshold) = 0;

  /*!
   * \brief Set the maximum octave evolution of the image
   * \param[in] octaves
   */
  virtual void setOctaves(int octaves) = 0;

  /*!
   * \brief Sets the default number of sublevels per scale level
   * \param[in] octaveLayers
   */
  virtual void setOctaveLayers(int octaveLayers) = 0;

  /*!
   * \brief Set diffusivity type
   * \param[in] diffusivity DIFF_PM_G1, DIFF_PM_G2 (default), DIFF_WEICKERT or DIFF_CHARBONNIER
   */
  virtual void setDiffusivity(const QString &diffusivity) = 0;

};




/*----------------------------------------------------------------*/




/*!
 * \brief The ASift class
 */
class PHOTOMATCH_EXPORT ASift
  : public FeatureBase
{

public:

  ASift() : FeatureBase(Feature::Type::asift)
  {
  }
  ~ASift() override = default;

  /*!
   * \brief The number of best features to retain
   * The features are ranked by their scores (measured in
   * SIFT algorithm as the local contrast)
   * \return
   */
  virtual int featuresNumber() const = 0;

  /*!
   * \brief The number of layers in each octave.
   * 3 is the value used in D. Lowe paper. The number of octaves
   * is computed automatically from the image resolution.
   * \return
   */
  virtual int octaveLayers() const = 0;

  /*!
   * \brief The contrast threshold used to filter out weak features in semi-uniform (low-contrast) regions.
   * The larger the threshold, the less features are produced by the detector.
   * \return
   */
  virtual double contrastThreshold() const = 0;

  /*!
   * \brief The threshold used to filter out edge-like features
   * Note that the its meaning is different from the contrastThreshold, i.e. the larger
   * the edgeThreshold, the less features are filtered out (more features are retained).
   * \return
   */
  virtual double edgeThreshold() const = 0;

  /*!
   * \brief The sigma of the Gaussian applied to the input image at the octave 0.
   * If your image is captured with a weak camera with soft lenses, you might want to reduce the number.
   * \return
   */
  virtual double sigma() const = 0;

  /*!
   * \brief Set the number of best features to retain
   * \param[in] featuresNumber Number of features
   */
  virtual void setFeaturesNumber(int featuresNumber) = 0;

  /*!
   * \brief Set the number of layers in each octave
   * \param[in] octaveLayers The number of layers in each octave (3 by default)
   */
  virtual void setOctaveLayers(int octaveLayers) = 0;

  /*!
   * \brief Set the contrast threshold
   * \param[in] contrastThreshold Contrast threshold
   */
  virtual void setContrastThreshold(double contrastThreshold) = 0;

  /*!
   * \brief Set the threshold used to filter out edge-like features
   * \param[in] edgeThreshold Edge threshold
   */
  virtual void setEdgeThreshold(double edgeThreshold) = 0;

  /*!
   * \brief Set sigma of the Gaussian
   * \param[in] sigma Sigma of the Gaussian
   */
  virtual void setSigma(double sigma) = 0;

  virtual int minTilt() const = 0;
  virtual int maxTilt() const = 0;
  virtual void setMinTilt(int minTilt) = 0;
  virtual void setMaxTilt(int maxTilt) = 0;

};



/*----------------------------------------------------------------*/




/*!
 * \brief The Boost class
 */
class PHOTOMATCH_EXPORT Boost
  : public FeatureBase
{

public:

  Boost() : FeatureBase(Feature::Type::boost){}
  ~Boost() override = default;

  /*!
   * \brief Type of descriptor used
   * Available types are BINBOOST_256 (default), BGM, BGM_HARD,
   * BGM_BILINEAR, LBGM, BINBOOST_64, BINBOOST_128, BINBOOST_256
   * \return Descriptor type
   */
  virtual QString descriptorType() const = 0;

  /*!
   * \brief Sample patterns using keypoints orientation
   * \return true if use keypoints orientation
   */
  virtual bool useOrientation() const = 0;

  /*!
   * \brief Scale factor for adjust the sampling window of detected keypoints
   * \return Scale factor
   */
  virtual double scaleFactor() const = 0;

  /*!
   * \brief Set the type of descriptor to use
   * Available types are BINBOOST_256 (default), BGM, BGM_HARD,
   * BGM_BILINEAR, LBGM, BINBOOST_64, BINBOOST_128, BINBOOST_256
   * \param[in] descriptorType Type of descriptor to use.
   */
  virtual void setDescriptorType(const QString &descriptorType) = 0;

  /*!
   * \brief Sample patterns using keypoints orientation
   * \param[in] useOrientation true for use keypoints orientation
   */
  virtual void setUseOrientation(bool useOrientation) = 0;

  /*!
   * \brief Adjust the sampling window of detected keypoints
   * \param[in] scaleFactor Scale factor
   */
  virtual void setScaleFactor(double scaleFactor) = 0;
};



/*----------------------------------------------------------------*/



/*!
 * \brief Interface for BRIEF
 *
 * Michael Calonder, Vincent Lepetit, Christoph Strecha, and Pascal Fua.
 * Brief: Binary robust independent elementary features. In Computer
 * Vision–ECCV 2010, pages 778–792. Springer, 2010
 * https://www.cs.ubc.ca/~lowe/525/papers/calonder_eccv10.pdf
 */
class PHOTOMATCH_EXPORT Brief
  : public FeatureBase
{

public:

  Brief() : FeatureBase(Feature::Type::brief) {}
  ~Brief() override = default;

  /*!
   * \brief Legth of the descriptor in bytes
   * Valid values are: 16, 32 (default) or 64
   * \return Legth of the descriptor
   */
  virtual QString bytes() const = 0;

  /*!
   * \brief Sample patterns using keypoints orientation
   * \return true if use keypoints orientation
   */
  virtual bool useOrientation() const = 0;

  /*!
   * \brief Set the length of the descriptor in bytes
   * \param[in] bytes Descriptor length
   */
  virtual void setBytes(const QString &bytes) = 0;

  /*!
   * \brief Sample patterns using keypoints orientation
   * \param[in] useOrientation true for use keypoints orientation
   */
  virtual void setUseOrientation(bool useOrientation) = 0;

};



/*----------------------------------------------------------------*/



/*!
 * \brief Interface for BRISK class
 * Stefan Leutenegger, Margarita Chli, and Roland Yves Siegwart.
 * Brisk: Binary robust invariant scalable keypoints. In Computer
 * Vision (ICCV), 2011 IEEE International Conference on, pages
 * 2548–2555. IEEE, 2011
 * http://margaritachli.com/papers/ICCV2011paper.pdf
 */
class PHOTOMATCH_EXPORT Brisk
  : public FeatureBase
{

public:

  Brisk() : FeatureBase(Feature::Type::brisk) {}
  ~Brisk() override = default;

  /*!
   * \brief AGAST detection threshold score (Default=30)
   * \return Threshold
   */
  virtual int threshold() const = 0;

  /*!
   * \brief Detection octaves (Default=3)
   * \return
   */
  virtual int octaves() const = 0;

  /*!
   * \brief Pattern Scale (Default=1.0)
   * \return
   */
  virtual double patternScale() const = 0;

  /*!
   * \brief Set the AGAST detection threshold score
   * \param[in] threshold AGAST detection threshold
   */
  virtual void setThreshold(int threshold) = 0;

  /*!
   * \brief Set detection octaves
   * \param[in] octaves Octaves
   */
  virtual void setOctaves(int octaves) = 0;

  /*!
   * \brief Set Pattern Scale
   * \param[in] patternScale Pattern Scale
   */
  virtual void setPatternScale(double patternScale) = 0;

};






/*----------------------------------------------------------------*/



class PHOTOMATCH_EXPORT D2Net
  : public FeatureBase
{

public:

  D2Net() : FeatureBase(Feature::Type::d2net) {}
  ~D2Net() override = default;

  virtual bool multiscale() const = 0;
  virtual void setMultiscale(bool multiscale) = 0;

};



/*----------------------------------------------------------------*/



/*!
 * \brief Interface for DAISY class
 * E. Tola, V. Lepetit, and P. Fua.
 * DAISY: An Efficient Dense Descriptor Applied to Wide Baseline
 * Stereo. IEEE Transactions on Pattern Analysis and Machine
 * Intelligence, 32(5):815–830, May 2010.
 */
class PHOTOMATCH_EXPORT Daisy
  : public FeatureBase
{

public:

  Daisy() : FeatureBase(Feature::Type::daisy) {}
  ~Daisy() override = default;

  /*!
   * \brief Radius of the descriptor at the initial scale (Default=15.)
   * \return
   */
  virtual double radius() const = 0;

  /*!
   * \brief Amount of radial range division quantity (Default=3)
   * \return
   */
  virtual int qRadius() const = 0;

  /*!
   * \brief Amount of angular range division quantity (Default=8)
   * \return
   */
  virtual int qTheta() const = 0;

  /*!
   * \brief Amount of gradient orientations range division quantity (Default=8)
   * \return
   */
  virtual int qHist() const = 0;

  /*!
   * \brief Descriptor normalization type
   * Normalization types:
   * - NRM_NONE: not make any normalization (Default)
   * - NRM_PARTIAL: mean that histograms are normalized independently for L2 norm equal to 1.0
   * - NRM_FULL: mean that descriptors are normalized for L2 norm equal to 1.0
   * - NRM_SIFT: mean that descriptors are normalized for L2 norm equal to 1.0 but no individual one is bigger than 0.154 as in SIFT
   * \return
   */
  virtual QString norm() const = 0;

  //virtual homography() const = 0;

  /*!
   * \brief Interpolation disabled or enabled (Default)
   * \return
   */
  virtual bool interpolation() const = 0;

  /*!
   * \brief Using orientation (Default=false)
   * \return
   */
  virtual bool useOrientation() const = 0;

  /*!
   * \brief Set the radius of the descriptor at the initial scale
   * \param[in] radius Radius of the descriptor
   */
  virtual void setRadius(double radius) = 0;

  /*!
   * \brief Set radial range division
   * \param[in] qRadius Radial range division
   */
  virtual void setQRadius(int qRadius) = 0;

  /*!
   * \brief Set angular range division
   * \param[in] qTheta Angular range division
   */
  virtual void setQTheta(int qTheta) = 0;

  /*!
   * \brief Set gradient orientations range division
   * \param[in] qHist gradient orientations range division
   */
  virtual void setQHist(int qHist) = 0;

  /*!
   * \brief Set normalization type
   * Normalization types:
   * - NRM_NONE: not make any normalization (Default)
   * - NRM_PARTIAL: mean that histograms are normalized independently for L2 norm equal to 1.0
   * - NRM_FULL: mean that descriptors are normalized for L2 norm equal to 1.0
   * - NRM_SIFT: mean that descriptors are normalized for L2 norm equal to 1.0 but no individual one is bigger than 0.154 as in SIFT
   * \param[in] norm Normalization type
   */
  virtual void setNorm(const QString &norm) = 0;

  /*!
   * \brief Enable or disable interpolation
   * \param[in] interpolation true for enable interpolation or false for disable
   */
  virtual void setInterpolation(bool interpolation) = 0;

  /*!
   * \brief Enable or disable orientation use
   * \param[in] useOrientation true for enable orientation or false for disable
   */
  virtual void setUseOrientation(bool useOrientation) = 0;

};



/*----------------------------------------------------------------*/



/*!
 * \brief Interface for FAST class
 * Rosten E., Drummond T. (2006) Machine Learning for High-Speed Corner Detection.
 * In: Leonardis A., Bischof H., Pinz A. (eds) Computer Vision – ECCV 2006. ECCV 2006.
 * Lecture Notes in Computer Science, vol 3951. Springer, Berlin, Heidelberg
 */
class PHOTOMATCH_EXPORT Fast
  : public FeatureBase
{

public:

  Fast() : FeatureBase(Feature::Type::fast) {}
  ~Fast() override = default;

  /*!
   * \brief threshold (Default=10)
   * \return
   */
  virtual int threshold() const = 0;

  /*!
   * \brief Non Maximal Suppression for removing adjacent corners (default=true)
   * \return
   */
  virtual bool nonmaxSuppression() const = 0;

  /*!
   * \brief Detector Types
   * - TYPE_5_8: FAST-5 decision tree whith the 8 pixels mask
   * - TYPE_7_12: FAST-7 decision tree whith the 12 pixels mask
   * - TYPE_9_16: FAST-9 decision tree whith the 16 pixels mask (default)
   * \return Detector Type
   */
  virtual QString detectorType() const = 0;

  /*!
   * \brief Set the threshold
   * \param threshold Threshold
   */
  virtual void setThreshold(int threshold) = 0;

  /*!
   * \brief Set Non Maximal Suppression
   * \param[in] nonmaxSuppression Non Maximal Suppression for removing adjacent corners (Default=true)
   */
  virtual void setNonmaxSuppression(bool nonmaxSuppression) = 0;

  /*!
   * \brief Set the Detector Type
   * Suported types:
   * - TYPE_5_8: FAST-5 decision tree whith the 8 pixels mask
   * - TYPE_7_12: FAST-7 decision tree whith the 12 pixels mask
   * - TYPE_9_16: FAST-9 decision tree whith the 16 pixels mask (default)
   *
   * \param[in] detectorType Detector Type
   */
  virtual void setDetectorType(const QString &detectorType) = 0;

};



/*----------------------------------------------------------------*/



/*!
 * \brief Interface for FREAK class
 * Alexandre Alahi, Raphael Ortiz, and Pierre Vandergheynst.
 * Freak: Fast retina keypoint. In Computer Vision and Pattern
 * Recognition (CVPR), 2012 IEEE Conference on, pages 510–517. Ieee, 2012.
 */
class PHOTOMATCH_EXPORT Freak
  : public FeatureBase
{

public:

  Freak() : FeatureBase(Feature::Type::freak) {}
  ~Freak() override = default;

  /*!
   * \brief Orientation normalization (Default=true)
   * \return
   */
  virtual bool orientationNormalized() const = 0;

  /*!
   * \brief Scale normalization (Default=true)
   * \return
   */
  virtual bool scaleNormalized() const = 0;

  /*!
   * \brief Scaling of the description pattern (Default=22.)
   * \return
   */
  virtual double patternScale() const = 0;

  /*!
   * \brief Number of octaves covered by the detected keypoints (Default=4)
   * \return Number of octaves
   */
  virtual int octaves() const = 0;

  /*!
   * \brief Enable/disable orientation normalization
   * \param[in] orientationNormalized true for Enable
   */
  virtual void setOrientationNormalized(bool orientationNormalized) = 0;

  /*!
   * \brief Enable/disable scale normalization
   * \param[in] scaleNormalized true for Enable
   */
  virtual void setScaleNormalized(bool scaleNormalized) = 0;

  /*!
   * \brief Set scaling of the description pattern
   * \param[in] patternScale Pattern Scale
   */
  virtual void setPatternScale(double patternScale) = 0;

  /*!
   * \brief Number of octaves covered by the detected keypoints
   * \param[in] octaves Number of octaves covered by the detected keypoints
   */
  virtual void setOctaves(int octaves) = 0;

};



/*----------------------------------------------------------------*/


/*!
 * \brief The GFTT class
 */
class PHOTOMATCH_EXPORT Gftt
  : public FeatureBase
{

public:

  Gftt() : FeatureBase(Feature::Type::gftt) {}
  ~Gftt() override = default;

  virtual int maxFeatures() const = 0;
  virtual double qualityLevel() const = 0;
  virtual double minDistance() const = 0;
  virtual int blockSize() const = 0;
  virtual bool harrisDetector() const = 0;
  virtual double k() const = 0;

  virtual void setMaxFeatures(int maxFeatures) = 0;
  virtual void setQualityLevel(double qlevel) = 0;
  virtual void setMinDistance(double minDistance) = 0;
  virtual void setBlockSize(int blockSize) = 0;
  virtual void setHarrisDetector(bool value) = 0;
  virtual void setK(double k) = 0;

};



/*----------------------------------------------------------------*/



/*!
 * \brief HOG (Histogram of Oriented Gradients)
 * Navneet Dalal and Bill Triggs @cite Dalal2005
 */
class PHOTOMATCH_EXPORT Hog
  : public FeatureBase
{

public:

  Hog() : FeatureBase(Feature::Type::hog) {}
  ~Hog() override = default;

  virtual QSize winSize() const = 0;
  virtual QSize blockSize() const = 0;
  virtual QSize blockStride() const = 0;
  virtual QSize cellSize() const = 0;
  virtual int nbins() const = 0;
  virtual int derivAperture() const = 0;
//  virtual double winSigma() const = 0;
//  virtual QString histogramNormType() const = 0;
//  virtual double l2HysThreshold() const = 0;
//  virtual bool gammaCorrection() const = 0;
//  virtual double freeCoef() const = 0;
//  virtual int nlevels() const = 0;
//  virtual bool signedGradient() const = 0;

  virtual void setWinSize(const QSize &winSize) = 0;
  virtual void setBlockSize(const QSize &blockSize) = 0;
  virtual void setBlockStride(const QSize &blockStride) = 0;
  virtual void setCellSize(const QSize &cellSize) = 0;
  virtual void setNbins(int nbins) = 0;
  virtual void setDerivAperture(int derivAperture) = 0;
//  virtual void setWinSigma(double winSigma) = 0;
//  virtual void setHistogramNormType(const QString &histogramNormType) = 0;
//  virtual void setL2HysThreshold(double l2HysThreshold) = 0;
//  virtual void setGammaCorrection(bool gammaCorrection) = 0;
//  virtual void setFreeCoef(double freeCoef) = 0;
//  virtual void setNlevels(int nlevels) = 0;
//  virtual void setSignedGradient(bool signedGradient) = 0;

};



/*----------------------------------------------------------------*/



/*!
 * \brief Kaze Interface
 *
 * Multiscale 2D feature detection and description algorithm in nonlinear scale spaces.
 *
 * Alcantarilla P.F., Bartoli A., Davison A.J. (2012) KAZE Features.
 * In: Fitzgibbon A., Lazebnik S., Perona P., Sato Y., Schmid C. (eds)
 * Computer Vision – ECCV 2012. ECCV 2012. Lecture Notes in Computer
 * Science, vol 7577. Springer, Berlin, Heidelberg
 *
 * https://www.doc.ic.ac.uk/~ajd/Publications/alcantarilla_etal_eccv2012.pdf
 */
class PHOTOMATCH_EXPORT Kaze
  : public FeatureBase
{

public:

  Kaze() : FeatureBase(Feature::Type::kaze) {}
  ~Kaze() override = default;

  /*!
   * \brief Extended descriptor
   * \return true if use extended 128-element descriptors or false if use 64-element descriptors (Default)
   */
  virtual bool extendedDescriptor() const = 0;

  /*!
   * \brief Use of upright descriptors (non rotation-invariant)
   * \return true if use upright descriptors (Default=false)
   */
  virtual bool uprightDescriptor() const = 0;

  /*!
   * \brief Detector response threshold to accept point
   * \return threshold
   */
  virtual double threshold() const = 0;

  /*!
   * \brief Maximum octave evolution of the image
   * \return octaves
   */
  virtual int octaves() const = 0;

  /*!
   * \brief Default number of sublevels per scale level
   * \return
   */
  virtual int octaveLayers() const = 0;

  /*!
   * \brief Diffusivity type
   * \return DIFF_PM_G1, DIFF_PM_G2 (default), DIFF_WEICKERT or DIFF_CHARBONNIER
   */
  virtual QString diffusivity() const = 0;

  /*!
   * \brief Set extended descriptor
   * \param[in] extended true for use extended 128-element descriptors or false for use 64-element descriptors (default)
   */
  virtual void setExtendedDescriptor(bool extended) = 0;

  /*!
   * \brief Set to enable use of upright descriptors (non rotation-invariant)
   * \param[in] upright
   */
  virtual void setUprightDescriptor(bool uprightDescriptor) = 0;

  /*!
   * \brief Set the detector response threshold to accept point
   * \param[in] threshold Threshold
   */
  virtual void setThreshold(double threshold) = 0;

  /*!
   * \brief Set the maximum octave evolution of the image
   * \param[in] octaves
   */
  virtual void setOctaves(int octaves) = 0;

  /*!
   * \brief Sets the default number of sublevels per scale level
   * \param[in] octaveLayers
   */
  virtual void setOctaveLayers(int octaveLayers) = 0;

  /*!
   * \brief Set diffusivity type
   * \param[in] diffusivity DIFF_PM_G1, DIFF_PM_G2 (default), DIFF_WEICKERT or DIFF_CHARBONNIER
   */
  virtual void setDiffusivity(const QString &diffusivity) = 0;

};



/*----------------------------------------------------------------*/



class PHOTOMATCH_EXPORT Latch
  : public FeatureBase
{

public:

  Latch() : FeatureBase(Feature::Type::latch) {}
  ~Latch() override = default;

  virtual QString bytes() const = 0;
  virtual bool rotationInvariance() const = 0;
  virtual int halfSsdSize() const = 0;

  virtual void setBytes(const QString &bytes) = 0;
  virtual void setRotationInvariance(bool rotationInvariance) = 0;
  virtual void setHalfSsdSize(int halfSsdSize) = 0;

};



/*----------------------------------------------------------------*/



/*!
 * \brief LUCID Interface
 * Eric Christiansen David Kriegman Ziegler, Andrew and Serge J. Belongie.
 * Locally uniform comparison image descriptor
 */
class PHOTOMATCH_EXPORT Lucid
  : public FeatureBase
{
public:

  Lucid() : FeatureBase(Feature::Type::lucid) {}
  ~Lucid() override = default;

  /*!
   * \brief kernel for descriptor construction
   * 1=3x3, 2=5x5, 3=7x7 and so forth. Default=1
   * \return
   */
  virtual int lucidKernel() const = 0;

  /*!
   * \brief kernel for blurring image prior to descriptor construction
   * 1=3x3, 2=5x5, 3=7x7 and so forth. Default=2
   * \return
   */
  virtual int blurKernel() const = 0;

  /*!
   * \brief Set the kernel for descriptor construction
   * \param[in] lucidKernel kernel for descriptor construction
   */
  virtual void setLucidKernel(int lucidKernel) = 0;

  /*!
   * \brief Set the kernel for descriptor construction
   * \param[in] blurKernel kernel for descriptor construction
   */
  virtual void setBlurKernel(int blurKernel) = 0;

};



/*----------------------------------------------------------------*/



class PHOTOMATCH_EXPORT Lss
  : public FeatureBase
{

public:

  Lss() : FeatureBase(Feature::Type::lss) {}
  ~Lss() override = default;

};



/*----------------------------------------------------------------*/



class PHOTOMATCH_EXPORT Msd
  : public FeatureBase
{

public:

  Msd() : FeatureBase(Feature::Type::msd) {}
  ~Msd() override = default;

  virtual double thresholdSaliency() const = 0;//
  virtual int patchRadius() const = 0;//
  virtual int knn() const = 0;//
  virtual int searchAreaRadius() const = 0;//
  virtual double scaleFactor() const = 0;//
  virtual int NMSRadius() const = 0;//
  virtual int nScales() const = 0;//
  virtual int NMSScaleRadius() const = 0;//
  virtual bool computeOrientation() const = 0;//
  virtual bool affineMSD() const = 0;
  //virtual int tilts() const = 0;
  virtual int affineTilts() const = 0;

  virtual void setThresholdSaliency(double thresholdSaliency) = 0;
  virtual void setPatchRadius(int patchRadius) = 0;
  virtual void setKNN(int knn) = 0;
  virtual void setSearchAreaRadius(int searchAreaRadius) = 0;
  virtual void setScaleFactor(double scaleFactor) = 0;
  virtual void setNMSRadius(int NMSRadius) = 0;
  virtual void setNScales(int nScales) = 0;
  virtual void setNMSScaleRadius(int NMSScaleR) = 0;
  virtual void setComputeOrientation(bool computeOrientation) = 0;
  virtual void setAffineMSD(bool affineMSD) = 0;
  virtual void setAffineTilts(int affineTilts) = 0;
};



/*----------------------------------------------------------------*/



class PHOTOMATCH_EXPORT Mser
  : public FeatureBase
{

public:

  Mser() : FeatureBase(Feature::Type::mser) {}
  ~Mser() override = default;

  virtual int delta() const = 0;
  virtual int minArea() const = 0;
  virtual int maxArea() const = 0;
  virtual double maxVariation() const = 0;
  virtual double minDiversity() const = 0;
  virtual int maxEvolution() const = 0;
  virtual double areaThreshold() const = 0;
  virtual double minMargin() const = 0;
  virtual int edgeBlurSize() const = 0;

  virtual void setDelta(int delta) = 0;
  virtual void setMinArea(int minArea) = 0;
  virtual void setMaxArea(int maxArea) = 0;
  virtual void setMaxVariation(double maxVariation) = 0;
  virtual void setMinDiversity(double minDiversity) = 0;
  virtual void setMaxEvolution(int maxEvolution) = 0;
  virtual void setAreaThreshold(double areaThreshold) = 0;
  virtual void setMinMargin(double minMargin) = 0;
  virtual void setEdgeBlurSize(int edgeBlurSize) = 0;

};



/*----------------------------------------------------------------*/



/*!
 * \brief Interface ORB
 */
class PHOTOMATCH_EXPORT Orb
  : public FeatureBase
{

public:

  Orb() : FeatureBase(Feature::Type::orb)  {}
  ~Orb() override = default;

  /*!
   * \brief The maximum number of features to retain
   * \return Number of features to retain
   */
  virtual int featuresNumber() const = 0;

  /*!
   * \brief Pyramid decimation ratio
   * ScaleFactor==2 means the classical pyramid, where each next
   * level has 4x less pixels than the previous, but such a big
   * scale factor will degrade feature matching scores dramatically.
   * On the other hand, too close to 1 scale factor will mean that to
   * cover certain scale range you will need more pyramid levels and
   * so the speed will suffer.
   * \return
   */
  virtual double scaleFactor() const = 0;

  /*!
   * \brief Returns the number of pyramid levels
   * The smallest level will have linear size equal to
   * input_image_linear_size/pow(scaleFactor, nlevels - firstLevel)
   * \return
   */
  virtual int levelsNumber() const = 0;

  /*!
   * \brief Size of the border where the features are not detected
   * \return
   */
  virtual int edgeThreshold() const = 0;

  /*!
   * \brief The level of pyramid to put source image to
   * \return
   */
  virtual int firstLevel() const = 0;

  /*!
   * \brief The number of points that produce each element of the oriented BRIEF descriptor
   * \return
   */
  virtual int wta_k() const = 0;

  /*!
   * \brief scoreType
   * \return
   */
  virtual QString scoreType() const = 0;

  /*!
   * \brief Size of the patch used by the oriented BRIEF descriptor
   * \return
   */
  virtual int patchSize() const = 0;

  /*!
   * \brief Returns the fast threshold
   * \return
   */
  virtual int fastThreshold() const = 0;

  /*!
   * \brief setScaleFactor
   * \param[in] scaleFactor
   */
  virtual void setScaleFactor(double scaleFactor) = 0;

  /*!
   * \brief setFeaturesNumber
   * \param[in] featuresNumber
   */
  virtual void setFeaturesNumber(int featuresNumber) = 0;

  /*!
   * \brief Set the number of pyramid levels
   * \param[in] levelsNumber Number of pyramid levels
   */
  virtual void setLevelsNumber(int levelsNumber) = 0;

  /*!
   * \brief setEdgeThreshold
   * \param[in] edgeThreshold
   */
  virtual void setEdgeThreshold(int edgeThreshold) = 0;

  /*!
   * \brief Set the first level of pyramid
   * \param[in] firstLevel First level
   */
  virtual void setFirstLevel (int firstLevel) = 0;

  /*!
   * \brief Set the number of points that produce each element of the oriented BRIEF descriptor
   * The default value 2 means the BRIEF where we take a random point pair and compare their
   * brightnesses, so we get 0/1 response. Other possible values are 3 and 4.
   * \param[in] WTA_K
   */
  virtual void setWTA_K(int WTA_K) = 0;

  /*!
   * \brief Set HARRIS_SCORE (Harris algorithm) or FAST_SCORE
   * \param[in] scoreType
   */
  virtual void setScoreType(const QString &scoreType) = 0;

  /*!
   * \brief Set the size of the patch used by the oriented BRIEF descriptor.
   * \param[in] patchSize
   */
  virtual void setPatchSize(int patchSize) = 0;

  /*!
   * \brief Set the fast threshold
   * \param[in] fastThreshold
   */
  virtual void setFastThreshold(int fastThreshold) = 0;

};



/*----------------------------------------------------------------*/



class PHOTOMATCH_EXPORT R2D2
  : public FeatureBase
{

public:

  R2D2() : FeatureBase(Feature::Type::r2d2) {}
  ~R2D2() override = default;

  virtual double scaleF() const = 0;
  virtual void setScaleF(double scaleF) = 0;
  virtual int minSize() const = 0;
  virtual void setMinSize(int size) = 0;
  virtual int maxSize() const = 0;
  virtual void setMaxSize(int size) = 0;
  virtual double minScale() const = 0;
  virtual void setMinScale(double minScale) = 0;
  virtual double maxScale() const = 0;
  virtual void setMaxScale(double maxScale) = 0;
  virtual double reliabilityThreshold() const = 0;
  virtual void setReliabilityThreshold(double reliabilityThreshold) = 0;
  virtual double repeatabilityThreshold() const = 0;
  virtual void setRepeatabilityThreshold(double repeatabilityThreshold) = 0;
};


/*----------------------------------------------------------------*/



class PHOTOMATCH_EXPORT Sift
  : public FeatureBase
{
public:
  Sift() : FeatureBase(Feature::Type::sift)  {}
  ~Sift() override = default;

  /*!
   * \brief The number of best features to retain
   * The features are ranked by their scores (measured in
   * SIFT algorithm as the local contrast)
   * \return
   */
  virtual int featuresNumber() const = 0;

  /*!
   * \brief The number of layers in each octave.
   * 3 is the value used in D. Lowe paper. The number of octaves
   * is computed automatically from the image resolution.
   * \return
   */
  virtual int octaveLayers() const = 0;

  /*!
   * \brief The contrast threshold used to filter out weak features in semi-uniform (low-contrast) regions.
   * The larger the threshold, the less features are produced by the detector.
   * \return
   */
  virtual double contrastThreshold() const = 0;

  /*!
   * \brief The threshold used to filter out edge-like features
   * Note that the its meaning is different from the contrastThreshold, i.e. the larger
   * the edgeThreshold, the less features are filtered out (more features are retained).
   * \return
   */
  virtual double edgeThreshold() const = 0;

  /*!
   * \brief The sigma of the Gaussian applied to the input image at the octave 0.
   * If your image is captured with a weak camera with soft lenses, you might want to reduce the number.
   * \return
   */
  virtual double sigma() const = 0;

  /*!
   * \brief Set the number of best features to retain
   * \param[in] featuresNumber Number of features
   */
  virtual void setFeaturesNumber(int featuresNumber) = 0;

  /*!
   * \brief Set the number of layers in each octave
   * \param[in] octaveLayers The number of layers in each octave (3 by default)
   */
  virtual void setOctaveLayers(int octaveLayers) = 0;

  /*!
   * \brief Set the contrast threshold
   * \param[in] contrastThreshold Contrast threshold
   */
  virtual void setContrastThreshold(double contrastThreshold) = 0;

  /*!
   * \brief Set the threshold used to filter out edge-like features
   * \param[in] edgeThreshold Edge threshold
   */
  virtual void setEdgeThreshold(double edgeThreshold) = 0;

  /*!
   * \brief Set sigma of the Gaussian
   * \param[in] sigma Sigma of the Gaussian
   */
  virtual void setSigma(double sigma) = 0;

};




/*----------------------------------------------------------------*/



class PHOTOMATCH_EXPORT Star
  : public FeatureBase
{

public:

  Star() : FeatureBase(Feature::Type::star) {}
  ~Star() override = default;

  virtual int maxSize() const  = 0;
  virtual int responseThreshold() const  = 0;
  virtual int lineThresholdProjected() const  = 0;
  virtual int lineThresholdBinarized() const  = 0;
  virtual int suppressNonmaxSize() const  = 0;

  virtual void setMaxSize(int maxSize) = 0;
  virtual void setResponseThreshold(int responseThreshold) = 0;
  virtual void setLineThresholdProjected(int lineThresholdProjected) = 0;
  virtual void setLineThresholdBinarized(int lineThresholdBinarized) = 0;
  virtual void setSuppressNonmaxSize(int suppressNonmaxSize) = 0;

};



/*----------------------------------------------------------------*/



class PHOTOMATCH_EXPORT Surf
  : public FeatureBase
{
public:

  Surf() : FeatureBase(Feature::Type::surf) {}
  ~Surf() override = default;

  /*!
   * \brief Threshold for hessian keypoint detector used in SURF
   * \return Threshold
   */
  virtual double hessianThreshold() const = 0;

  /*!
   * \brief Threshold for hessian keypoint detector used in SURF
   * \param[in] hessianThreshold Threshold for hessian keypoint detector
   */
  virtual void setHessianThreshold(double hessianThreshold) = 0;

  /*!
   * \brief Number of a gaussian pyramid octaves that the detector uses.
   * \return Number of octaves
   */
  virtual int octaves() const = 0;

  /*!
   * \brief Set the number of a gaussian pyramid octaves that the detector uses.
   * It is set to 4 by default. If you want to get very large features, use the
   * larger value. If you want just small features, decrease it.
   * \param[in] octaves The number of a gaussian pyramid octaves that the detector uses.
   */
  virtual void setOctaves(int octaves) = 0;

  /*!
   * \brief Number of octave layers within each octave
   * \return
   */
  virtual int octaveLayers() const = 0;

  /*!
   * \brief Set the number of octave layers
   * \param[in] octaveLayers Number of octave layers within each octave
   */
  virtual void setOctaveLayers(int octaveLayers) = 0;

  /*!
   * \brief Extended descriptor
   * \return true (use extended 128-element descriptors) or false (use 64-element descriptors)
   */
  virtual bool extendedDescriptor() const = 0;

  /*!
   * \brief setExtendedDescriptor
   * \param[in] extendedDescriptor true for use extended 128-element descriptors or false for use 64-element descriptors)
   */
  virtual void setExtendedDescriptor(bool extendedDescriptor) = 0;

  /*!
   * \brief Up-right or rotated features
   * \return true (do not compute orientation of features) or false (compute orientation)
   */
  virtual bool upright() const = 0;

  /*!
   * \brief compute orientation of features
   * \param[in] rotatedFeatures false for compute orientation
   */
  virtual void setUpright(bool upright) = 0;

};



/*----------------------------------------------------------------*/



/*!
 * \brief Vgg interface
 * K. Simonyan, A. Vedaldi, and A. Zisserman. Learning local feature
 * descriptors using convex optimisation. IEEE Transactions on Pattern
 * Analysis and Machine Intelligence, 2014.
 */
class PHOTOMATCH_EXPORT Vgg
  : public FeatureBase
{
public:

  Vgg() : FeatureBase(Feature::Type::vgg) {}
  ~Vgg() override = default;

  /*!
   * \brief Type of descriptor to use
   * Available types are VGG_120 (default), VGG_80, VGG_64, VGG_48
   * \return Type of descriptor
   */
  virtual QString descriptorType() const = 0;

  /*!
   * \brief Set the type of descriptor to use
   * Available types are VGG_120 (default), VGG_80, VGG_64, VGG_48
   * \param[in] descriptorType Type of descriptor to use.
   */
  virtual void setDescriptorType(const QString &descriptorType) = 0;

  virtual double scaleFactor() const = 0;
  virtual void 	setScaleFactor(double scaleFactor) = 0;

  /*!
   * \brief Gaussian kernel value for image blur
   * \return Gaussian kernel value
   */
  virtual double sigma() const = 0;

  /*!
   * \brief Set gaussian kernel value for image blur (default is 1.4f)
   * \param[in] sigma
   */
  virtual void 	setSigma(double sigma) = 0;

  virtual bool 	useNormalizeDescriptor() const = 0;
  virtual void 	setUseNormalizeDescriptor(bool useNormalizeDescriptor) = 0;

  virtual bool 	useNormalizeImage() const = 0;
  virtual void 	setUseNormalizeImage(bool useNormalizeImage) = 0;

  virtual bool 	useScaleOrientation() const = 0;
  virtual void 	setUseScaleOrientation(bool useScaleOrientation) = 0;
};


} // namespace photomatch

#endif // PHOTOMATCH_FEATURES_H
