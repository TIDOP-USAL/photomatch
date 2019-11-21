#include "rswhe.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


RswheProperties::RswheProperties()
  : IRswhe(),
    mHistogramCut(HistogramCut::by_mean),
    mHistogramDivisions(2)
{
}

RswheProperties::~RswheProperties()
{

}

int RswheProperties::histogramDivisions() const
{
  return mHistogramDivisions;
}

void RswheProperties::setHistogramDivisions(int histogramDivisions)
{
  mHistogramDivisions = histogramDivisions;
}

IRswhe::HistogramCut RswheProperties::histogramCut() const
{
  return mHistogramCut;
}

void RswheProperties::setHistogramCut(photomatch::IRswhe::HistogramCut histogramCut)
{
  mHistogramCut = histogramCut;
}

void RswheProperties::reset()
{
  mHistogramDivisions = 2;
  mHistogramCut = HistogramCut::by_mean;
}

QString RswheProperties::name() const
{
  return QString("RSWHE");
}


/*----------------------------------------------------------------*/


RswhePreprocess::RswhePreprocess()
  : RswheProperties(),
    ImageProcess()
{
}

RswhePreprocess::RswhePreprocess(int histogramDivisions, HistogramCut histogramCut)
  : RswheProperties(),
    ImageProcess()
{
  this->setHistogramDivisions(histogramDivisions);
  this->setHistogramCut(histogramCut);
}

RswhePreprocess::~RswhePreprocess()
{

}

bool RswhePreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{
  try {

    cv::Mat temp;
    if (imgIn.channels() >= 3) {
      cv::Mat color_boost;
      cv::decolor(imgIn, temp, color_boost);
      color_boost.release();
    } else {
      imgIn.copyTo(temp);
    }

    int histogram_cut;
    if (RswheProperties::histogramCut() == HistogramCut::by_mean)
      histogram_cut = 1;
    else {
      histogram_cut = 2;
    }

    pixkit::enhancement::global::MaryKim2008(temp, imgOut, histogram_cut, RswheProperties::histogramDivisions());
    temp.release();

  } catch (cv::Exception &e) {
    msgError("RSWHE Image preprocess error: %s", e.what());
    return true;
  }

  return false;
}


} // namespace photomatch







