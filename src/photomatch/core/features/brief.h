#ifndef PHOTOMATCH_BRIEF_DESCRIPTOR_H
#define PHOTOMATCH_BRIEF_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <opencv2/xfeatures2d.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT BriefProperties
  : public IBrief
{
public:

  BriefProperties();
  ~BriefProperties() override;

// IBrief interface

public:

  virtual QString bytes() const override;
  virtual bool useOrientation() const override;
  virtual void setBytes(const QString &bytes) override;
  virtual void setUseOrientation(bool useOrientation) override;

// Feature interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  QString mBytes;
  bool mUseOrientation;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT BriefDescriptor
    : public BriefProperties,
      public DescriptorExtractor
{

public:

  BriefDescriptor();
  BriefDescriptor(QString bytes,
                  bool useOrientation);

  ~BriefDescriptor() override;

private:

  void update();

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img,
               std::vector<cv::KeyPoint> &keyPoints,
               cv::Mat &descriptors) override;


// IBrief interface

public:

  void setBytes(const QString &bytes) override;
  void setUseOrientation(bool useOrientation) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::xfeatures2d::BriefDescriptorExtractor> mBrief;
};


} // namespace photomatch

#endif // PHOTOMATCH_BRIEF_DESCRIPTOR_H
