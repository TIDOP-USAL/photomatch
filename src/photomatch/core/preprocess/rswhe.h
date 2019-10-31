#ifndef PHOTOMATCH_RSWHE_PREPROCESS_H
#define PHOTOMATCH_RSWHE_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT RswheProperties
  : public IRswhe
{

public:

  RswheProperties();
  ~RswheProperties() override;

// IRswhe interface

public:

  virtual int histogramDivisions() const override;
  virtual void setHistogramDivisions(int histogramDivisions) override;
  virtual HistogramCut histogramCut() const override;
  virtual void setHistogramCut(HistogramCut histogramCut) override;

// Preprocess interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  HistogramCut mHistogramCut;
  int mHistogramDivisions;

};



/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT RswhePreprocess
  : public RswheProperties,
    public ImageProcess
{

public:

  RswhePreprocess();
  RswhePreprocess(int histogramDivisions, HistogramCut histogramCut);
  ~RswhePreprocess() override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;

};

} // namespace photomatch

#endif // PHOTOMATCH_RSWHE_PREPROCESS_H
