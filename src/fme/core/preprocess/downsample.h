#ifndef FME_DOWNSAMPLE_PREPROCESS_H
#define FME_DOWNSAMPLE_PREPROCESS_H

#include "fme/fme_global.h"

#include "fme/core/preprocess/preprocess.h"

#include <QString>

namespace fme
{


class FME_EXPORT DownsampleProperties
  : public IDownsample
{

public:

  DownsampleProperties();
  ~DownsampleProperties() override {}

// IDownsample interface

public:

  virtual int maxImageSize() const override;
  virtual void setMaxImageSize(int size) override;

public:

// Preprocess interface

public:

  virtual void reset() override;

private:

  int mMaxSize;

};



class FME_EXPORT DownsamplePreprocess
  : public DownsampleProperties,
    public ImageProcess
{

public:

  DownsamplePreprocess();
  DownsamplePreprocess(int size);
  ~DownsamplePreprocess() override;

// Preprocess interface

public:

  void reset() override;

// IAcebsf interface

public:

  void setMaxImageSize(int size) override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;
};

} // namespace fme

#endif // FME_DOWNSAMPLE_PREPROCESS_H
