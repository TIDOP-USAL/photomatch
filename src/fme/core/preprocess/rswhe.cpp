#include "rswhe.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
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

void RswheProperties::setHistogramCut(fme::IRswhe::HistogramCut histogramCut)
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

cv::Mat RswhePreprocess::process(const cv::Mat &img)
{
  cv::Mat color_boost;
  cv::Mat temp;
  if (img.channels() >= 3) {
    cv::decolor(img, temp, color_boost);
    color_boost.release();
  } else {
    img.copyTo(temp);
  }

  int histogram_cut;
  if (RswheProperties::histogramCut() == HistogramCut::by_mean)
    histogram_cut = 1;
  else {
    histogram_cut = 2;
  }

  cv::Mat out;
  pixkit::enhancement::global::MaryKim2008(temp, out, histogram_cut, RswheProperties::histogramDivisions());
  temp.release();

  return out;
}


} // namespace fme







