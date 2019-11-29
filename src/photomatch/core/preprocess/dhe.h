#ifndef PHOTOMATCH_DHE_PREPROCESS_H
#define PHOTOMATCH_DHE_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT DheProperties
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
  QString name() const final;

private:

  int mX;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT DhePreprocess
  : public DheProperties,
    public ImageProcess
{

public:

  DhePreprocess();
  DhePreprocess(int x);
  ~DhePreprocess() override;

// ImageProcess interface

public:

  bool process(const cv::Mat &imgIn, cv::Mat &imgOut) override;

};

} // namespace photomatch

#endif // PHOTOMATCH_DHE_PREPROCESS_H
