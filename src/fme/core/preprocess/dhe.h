#ifndef FME_DHE_PREPROCESS_H
#define FME_DHE_PREPROCESS_H

#include "fme/fme_global.h"

#include "fme/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace fme
{


class FME_EXPORT DheProperties
  : public IDhe
{

public:

  DheProperties();
  ~DheProperties() override = default;

// IDhe interface

public:

  virtual int x() const override;
  virtual void setX(int x) override;

// Preprocess interface

public:

  virtual void reset() override;

private:

  int mX;
};


/*----------------------------------------------------------------*/


class FME_EXPORT DhePreprocess
  : public DheProperties,
    public ImageProcess
{

public:

  DhePreprocess();
  DhePreprocess(int x);
  ~DhePreprocess() override;

// Preprocess interface

public:

  void reset() override;

// IDhe interface

public:

  void setX(int x) override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;

};

} // namespace fme

#endif // FME_DHE_PREPROCESS_H
