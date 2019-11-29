#ifndef PHOTOMATCH_SIFT_DETECTOR_DESCRIPTOR_H
#define PHOTOMATCH_SIFT_DETECTOR_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <opencv2/xfeatures2d.hpp>

#include <QString>

namespace photomatch
{


/*!
 * \brief SIFT detector/descriptor properties class
 */
class PHOTOMATCH_EXPORT SiftProperties
  : public ISift
{

public:

  SiftProperties();
  ~SiftProperties() override;

// ISift interface

public:

  virtual int featuresNumber() const override;
  virtual int octaveLayers() const override;
  virtual double contrastThreshold() const override;
  virtual double edgeThreshold() const override;
  virtual double sigma() const override;
  virtual void setFeaturesNumber(int featuresNumber) override;
  virtual void setOctaveLayers(int octaveLayers) override;
  virtual void setContrastThreshold(double contrastThreshold) override;
  virtual void setEdgeThreshold(double edgeThreshold) override;
  virtual void setSigma(double sigma) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  int mFeaturesNumber;
  int mOctaveLayers;
  double mContrastThreshold;
  double mEdgeThreshold;
  double mSigma;
};


/*----------------------------------------------------------------*/

#ifdef OPENCV_ENABLE_NONFREE

class PHOTOMATCH_EXPORT SiftDetectorDescriptor
  : public SiftProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  SiftDetectorDescriptor();
  SiftDetectorDescriptor(int featuresNumber,
                         int octaveLayers,
                         double contrastThreshold,
                         double edgeThreshold,
                         double sigma);

  ~SiftDetectorDescriptor() override;

private:

  void update();

// KeypointDetector interface

public:

  bool detect(const cv::Mat &img,
              std::vector<cv::KeyPoint> &keyPoints,
              cv::InputArray &mask = cv::noArray()) override;

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img,
               std::vector<cv::KeyPoint> &keyPoints,
               cv::Mat &descriptors) override;

// ISift interface

public:

  void setFeaturesNumber(int featuresNumber) override;
  void setOctaveLayers(int octaveLayers) override;
  void setContrastThreshold(double contrastThreshold) override;
  void setEdgeThreshold(double edgeThreshold) override;
  void setSigma(double sigma) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::xfeatures2d::SIFT> mSift;
};

#endif

} // namespace photomatch

#endif // PHOTOMATCH_SIFT_DETECTOR_DESCRIPTOR_H