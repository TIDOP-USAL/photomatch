#ifndef FME_FEATURES_H
#define FME_FEATURES_H

#include "fme/fme_global.h"

namespace fme
{

class FME_EXPORT IAgast
{

public:

  IAgast() {}
  virtual ~IAgast() = default;

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
   * - AGAST_5_8: AGAST-5 decision tree whith the 8 pixels mask
   * - AGAST_7_12d: AGAST-7 decision tree whith the Diamond shaped 12 pixels mask
   * - AGAST_7_12s: AGAST-7 decision tree whith the Squared shaped 12 pixels mask
   * - OAST_9_16: OAST-9 (Optimal AST) decision tree whith the 16 pixels mask
   *
   * \param[in] detectorType Detector Type (Default = OAST_9_16)
   */
  virtual void setDetectorType(const QString &detectorType) = 0;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;
};



class FME_EXPORT IAkaze
{

public:

  IAkaze(){}
  virtual ~IAkaze() = default;

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

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;
};




class FME_EXPORT ISift
{
public:
  ISift() {}
  virtual ~ISift() = default;

  /*!
   * \brief featuresNumber
   * \return
   */
  virtual int featuresNumber() const = 0;

  /*!
   * \brief octaveLayers
   * \return
   */
  virtual int octaveLayers() const = 0;

  /*!
   * \brief contrastThreshold
   * \return
   */
  virtual double contrastThreshold() const = 0;

  /*!
   * \brief edgeThreshold
   * \return
   */
  virtual double edgeThreshold() const = 0;

  /*!
   * \brief sigma
   * \return
   */
  virtual double sigma() const = 0;

  /*!
   * \brief setFeaturesNumber
   * \param featuresNumber
   */
  virtual void setFeaturesNumber(int featuresNumber) = 0;

  /*!
   * \brief setOctaveLayers
   * \param octaveLayers
   */
  virtual void setOctaveLayers(int octaveLayers) = 0;

  /*!
   * \brief setContrastThreshold
   * \param contrastThreshold
   */
  virtual void setContrastThreshold(double contrastThreshold) = 0;

  /*!
   * \brief setEdgeThreshold
   * \param edgeThreshold
   */
  virtual void setEdgeThreshold(double edgeThreshold) = 0;

  /*!
   * \brief setSigma
   * \param sigma
   */
  virtual void setSigma(double sigma) = 0;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;
};




class FME_EXPORT ISurf
{
public:

  ISurf() {}
  virtual ~ISurf() = default;

  /*!
   * \brief Threshold for hessian keypoint detector used in SURF
   * \return
   */
  virtual double hessianThreshold() const = 0;

  /*!
   * \brief Threshold for hessian keypoint detector used in SURF
   * \param[in] hessianThreshold
   */
  virtual void setHessianThreshold(double hessianThreshold) = 0;

  /*!
   * \brief Number of pyramid octaves the keypoint detector will use.
   * \return
   */
  virtual int octaves() const = 0;

  /*!
   * \brief Set the number of pyramid octaves
   * \param[in] octaves Number of pyramid octaves the keypoint detector will use.
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
  virtual bool rotatedFeatures() const = 0;

  /*!
   * \brief compute orientation of features
   * \param[in] rotatedFeatures false for compute orientation
   */
  virtual void setRotatedFeatures(bool rotatedFeatures) = 0;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;
};

} // namespace fme

#endif // FME_FEATURES_H
