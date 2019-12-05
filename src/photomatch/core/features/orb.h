#ifndef PHOTOMATCH_ORB_DETECTOR_DESCRIPTOR_H
#define PHOTOMATCH_ORB_DETECTOR_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#ifdef HAVE_CUDA
#include <opencv2/cudafeatures2d.hpp>
#endif // HAVE_CUDA

#include <QString>

namespace photomatch
{



class PHOTOMATCH_EXPORT OrbProperties
  : public IOrb
{
public:

  OrbProperties();
  OrbProperties(const OrbProperties &orbProperties);
   ~OrbProperties() override;

// IOrb interface

public:

  virtual int featuresNumber() const override;
  virtual double scaleFactor() const override;
  virtual int levelsNumber() const override;
  virtual int edgeThreshold() const override;
  virtual int firstLevel() const override;
  virtual int wta_k() const override;
  virtual QString scoreType() const override;
  virtual int patchSize() const override;
  virtual int fastThreshold() const override;
  virtual void setFeaturesNumber(int featuresNumber) override;
  virtual void setScaleFactor(double scaleFactor) override;
  virtual void setLevelsNumber(int levelsNumber) override;
  virtual void setEdgeThreshold(int edgeThreshold) override;
  virtual void setFirstLevel(int firstLevel) override;
  virtual void setWTA_K(int WTA_K) override;
  virtual void setScoreType(const QString &scoreType) override;
  virtual void setPatchSize(int patchSize) override;
  virtual void setFastThreshold(int fastThreshold) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  int mFeaturesNumber;
  double mScaleFactor;
  int mLevelsNumber;
  int mEdgeThreshold;
  int mFirstLevel;
  int mWTA_K;
  QString mScoreType;
  int mPatchSize;
  int mFastThreshold;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT OrbDetectorDescriptor
  : public OrbProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  OrbDetectorDescriptor();
  OrbDetectorDescriptor(const OrbDetectorDescriptor &orbDetectorDescriptor);
  OrbDetectorDescriptor(int featuresNumber,
                        double scaleFactor,
                        int levelsNumber,
                        int edgeThreshold,
                        int wta_k,
                        QString scoreType,
                        int patchSize,
                        int fastThreshold);
  ~OrbDetectorDescriptor() override;

private:

#if CV_VERSION_MAJOR >= 4
  cv::ORB::ScoreType convertScoreType(const QString &scoreType);
#else
  int convertScoreType(const QString &scoreType);
#endif

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

// IOrb interface

public:

  void setFeaturesNumber(int featuresNumber) override;
  void setScaleFactor(double scaleFactor) override;
  void setLevelsNumber(int levelsNumber) override;
  void setEdgeThreshold(int edgeThreshold) override;
  void setFirstLevel(int firstLevel) override;
  void setWTA_K(int WTA_K) override;
  void setScoreType(const QString &scoreType) override;
  void setPatchSize(int patchSize) override;
  void setFastThreshold(int fastThreshold) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::ORB> mOrb;
};



/*----------------------------------------------------------------*/

#ifdef HAVE_CUDA

class PHOTOMATCH_EXPORT OrbCudaDetectorDescriptor
  : public OrbProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  OrbCudaDetectorDescriptor();
  OrbCudaDetectorDescriptor(const OrbCudaDetectorDescriptor &orbCudaDetectorDescriptor);
  OrbCudaDetectorDescriptor(int featuresNumber,
                            double scaleFactor,
                            int levelsNumber,
                            int edgeThreshold,
                            int wta_k,
                            QString scoreType,
                            int patchSize,
                            int fastThreshold);

  ~OrbCudaDetectorDescriptor() override;

private:

#if CV_VERSION_MAJOR >= 4
  cv::ORB::ScoreType convertScoreType(const QString &scoreType);
#else
  int convertScoreType(const QString &scoreType);
#endif

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

// IOrb interface

public:

  void setFeaturesNumber(int featuresNumber) override;
  void setScaleFactor(double scaleFactor) override;
  void setLevelsNumber(int levelsNumber) override;
  void setEdgeThreshold(int edgeThreshold) override;
  void setFirstLevel(int firstLevel) override;
  void setWTA_K(int WTA_K) override;
  void setScoreType(const QString &scoreType) override;
  void setPatchSize(int patchSize) override;
  void setFastThreshold(int fastThreshold) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::cuda::ORB> mOrb;
};

#endif // HAVE_CUDA

} // namespace photomatch



#endif // PHOTOMATCH_ORB_DETECTOR_DESCRIPTOR_H
