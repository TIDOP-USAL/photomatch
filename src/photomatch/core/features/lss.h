#ifndef PHOTOMATCH_LSS_DESCRIPTOR_H
#define PHOTOMATCH_LSS_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include <memory>

#include <opencv2/xfeatures2d.hpp>

#include <QString>

#include "photomatch/core/features/features.h"
#include "lss/lss.h"

namespace photomatch
{



class PHOTOMATCH_EXPORT LssProperties
  : public ILss
{
public:

  LssProperties();
  ~LssProperties() override;

// Feature interface

public:

  virtual void reset() override;
  QString name() const final;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT LssDescriptor
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


} // namespace photomatch

#endif // PHOTOMATCH_LSS_DESCRIPTOR_H
