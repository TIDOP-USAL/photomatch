#ifndef FME_RSWHE_PREPROCESS_H
#define FME_RSWHE_PREPROCESS_H

#include "fme/fme_global.h"

#include "fme/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace fme
{


class FME_EXPORT RswheProperties
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

private:

  HistogramCut mHistogramCut;
  int mHistogramDivisions;

};



/*----------------------------------------------------------------*/


class FME_EXPORT RswhePreprocess
  : public RswheProperties,
    public ImageProcess
{

public:

  RswhePreprocess();
  RswhePreprocess(int histogramDivisions, HistogramCut histogramCut);
  ~RswhePreprocess() override;

// Preprocess interface

public:

  void reset() override;

// IRswhe interface

public:

  void setHistogramDivisions(int histogramDivisions) ;
  void setHistogramCut(HistogramCut histogramCut) override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;

};

} // namespace fme

#endif // FME_RSWHE_PREPROCESS_H
