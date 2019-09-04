#ifndef FME_BRIEF_DESCRIPTOR_H
#define FME_BRIEF_DESCRIPTOR_H

#include "fme/fme_global.h"

#include "fme/core/features/features.h"

#include <opencv2/xfeatures2d.hpp>

#include <QString>

namespace fme
{


/*----------------------------------------------------------------*/


class FME_EXPORT BriefProperties
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


class FME_EXPORT BriefDescriptor
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

  cv::Mat extract(const cv::Mat &img, std::vector<cv::KeyPoint> &keyPoints) override;


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


/*----------------------------------------------------------------*/


} // namespace fme

#endif // FME_BRIEF_DESCRIPTOR_H
