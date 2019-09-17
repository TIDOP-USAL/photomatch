#ifndef FME_DECOLOR_H
#define FME_DECOLOR_H

#include "fme/fme_global.h"

#include "fme/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace fme
{

class FME_EXPORT DecolorProperties
  : public IDecolor
{

public:

  DecolorProperties();
  ~DecolorProperties() override = default;

// Preprocess interface

public:

  virtual void reset() override;
  QString name() const final;

};


/*----------------------------------------------------------------*/


class FME_EXPORT DecolorPreprocess
  : public DecolorProperties,
    public ImageProcess
{

public:

  DecolorPreprocess();
  ~DecolorPreprocess() override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;

};


} // namespace fme

#endif // FME_DECOLOR_H
