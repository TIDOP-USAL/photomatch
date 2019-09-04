#ifndef FME_MSER_DETECTOR_H
#define FME_MSER_DETECTOR_H

#include "fme/fme_global.h"

#include "fme/core/features/features.h"

#include <QString>

namespace fme
{


/*----------------------------------------------------------------*/


class FME_EXPORT MserProperties
  : public IMser
{
public:

  MserProperties();
   ~MserProperties() override;

// IMser interface

public:

  virtual int delta() const override;
  virtual int minArea() const override;
  virtual int maxArea() const override;
  virtual double maxVariation() const override;
  virtual double minDiversity() const override;
  virtual int maxEvolution() const override;
  virtual double areaThreshold() const override;
  virtual double minMargin() const override;
  virtual int edgeBlurSize() const override;
  virtual void setDelta(int delta) override;
  virtual void setMinArea(int minArea) override;
  virtual void setMaxArea(int maxArea) override;
  virtual void setMaxVariation(double maxVariation) override;
  virtual void setMinDiversity(double minDiversity) override;
  virtual void setMaxEvolution(int maxEvolution) override;
  virtual void setAreaThreshold(double areaThreshold) override;
  virtual void setMinMargin(double minMargin) override;
  virtual void setEdgeBlurSize(int edgeBlurSize) override;

// Feature interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  int mDelta;
  int mMinArea;
  int mMaxArea;
  double mMaxVariation;
  double mMinDiversity;
  int mMaxEvolution;
  double mAreaThreshold;
  double mMinMargin;
  int mEdgeBlurSize;
};


/*----------------------------------------------------------------*/


class MserDetector
  : public MserProperties,
    public KeypointDetector
{

public:

  MserDetector();
  MserDetector(int delta,
               int minArea,
               int maxArea,
               double maxVariation,
               double minDiversity,
               int maxEvolution,
               double areaThreshold,
               double minMargin,
               int edgeBlurSize);
  ~MserDetector() override;

private:

  void update();

// KeypointDetector interface

public:

  std::vector<cv::KeyPoint> detect(const cv::Mat &img, cv::InputArray &mask) override;

// IFast interface

public:

  void setDelta(int delta) override;
  void setMinArea(int minArea) override;
  void setMaxArea(int maxArea) override;
  void setMaxVariation(double maxVariation) override;
  void setMinDiversity(double minDiversity) override;
  void setMaxEvolution(int maxEvolution) override;
  void setAreaThreshold(double areaThreshold) override;
  void setMinMargin(double minMargin) override;
  void setEdgeBlurSize(int edgeBlurSize) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::MSER> mMSER;

};


/*----------------------------------------------------------------*/


} // namespace fme

#endif // FME_MSER_DETECTOR_H
