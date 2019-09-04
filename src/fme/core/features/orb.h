#ifndef FME_ORB_DETECTOR_DESCRIPTOR_H
#define FME_ORB_DETECTOR_DESCRIPTOR_H

#include "fme/fme_global.h"

#include "fme/core/features/features.h"

#include <QString>

namespace fme
{

/*----------------------------------------------------------------*/


class FME_EXPORT OrbProperties
  : public IOrb
{
public:

  OrbProperties();
   ~OrbProperties() override;

// IOrb interface

public:

  virtual int featuresNumber() const override;
  virtual double scaleFactor() const override;
  virtual int levelsNumber() const override;
  virtual int edgeThreshold() const override;
  virtual int wta_k() const override;
  virtual QString scoreType() const override;
  virtual int patchSize() const override;
  virtual int fastThreshold() const override;
  virtual void setFeaturesNumber(int featuresNumber) override;
  virtual void setScaleFactor(double scaleFactor) override;
  virtual void setLevelsNumber(int levelsNumber) override;
  virtual void setEdgeThreshold(int edgeThreshold) override;
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
  int mWTA_K;
  QString mScoreType;
  int mPatchSize;
  int mFastThreshold;
};


/*----------------------------------------------------------------*/


class FME_EXPORT OrbDetectorDescriptor
  : public OrbProperties,
    public KeypointDetector,
    public DescriptorExtractor
{

public:

  OrbDetectorDescriptor();
  OrbDetectorDescriptor(int featuresNumber,
                        double scaleFactor,
                        int levelsNumber,
                        int edgeThreshold,
                        int wta_k,
                        QString scoreType,
                        int patchSize,
                        int fastThreshold);

  ~OrbDetectorDescriptor() override;

// KeypointDetector interface

public:

  std::vector<cv::KeyPoint> detect(const cv::Mat &img, cv::InputArray &mask) override;

// DescriptorExtractor interface

public:

  cv::Mat extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints) override;

// IOrb interface

public:

  void setFeaturesNumber(int featuresNumber) override;
  void setScaleFactor(double scaleFactor) override;
  void setLevelsNumber(int levelsNumber) override;
  void setEdgeThreshold(int edgeThreshold) override;
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

} // namespace fme

#endif // FME_ORB_DETECTOR_DESCRIPTOR_H
