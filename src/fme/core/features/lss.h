#ifndef FME_LSS_DESCRIPTOR_H
#define FME_LSS_DESCRIPTOR_H

#include "fme/fme_global.h"

#include <memory>

#include <opencv2/xfeatures2d.hpp>

#include <QString>

#include "fme/core/features/features.h"
#include "lss/lss.h"

namespace fme
{


/*----------------------------------------------------------------*/


class FME_EXPORT LssProperties
  : public ILss
{
public:

  LssProperties();
  ~LssProperties() override;

// Feature interface

public:

  virtual void reset() override;

};


/*----------------------------------------------------------------*/


class FME_EXPORT LssDescriptor
    : public LssProperties,
      public DescriptorExtractor
{

public:

  LssDescriptor();
  ~LssDescriptor() override;

private:

  void update();

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img,
               std::vector<cv::KeyPoint> &keyPoints,
               cv::Mat &descriptors) override;

// Feature interface

public:

  void reset() override;

protected:

  std::shared_ptr<LSS> mLSS;
};


/*----------------------------------------------------------------*/


} // namespace fme

#endif // FME_LSS_DESCRIPTOR_H
