#ifndef PHOTOMATCH_DECOLOR_H
#define PHOTOMATCH_DECOLOR_H

#include <tidop/core/messages.h>

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace photomatch
{

class PHOTOMATCH_EXPORT DecolorProperties
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


class PHOTOMATCH_EXPORT DecolorPreprocess
  : public DecolorProperties,
    public ImageProcess
{

public:

  DecolorPreprocess();
  ~DecolorPreprocess() override;

// ImageProcess interface

public:

  bool process(const cv::Mat &imgIn, cv::Mat &imgOut) override;

};


} // namespace photomatch

#endif // PHOTOMATCH_DECOLOR_H
