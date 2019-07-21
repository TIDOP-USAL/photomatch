#include "MsrcpProcess.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
{

MsrcpProcess::MsrcpProcess()
  : ProcessConcurrent(),
    IMsrcp(),
    mImgInput(""),
    mImgOutput(""),
    mSmallScale(10.),
    mMidScale(100.),
    mLargeScale(220.)
{
}

MsrcpProcess::MsrcpProcess(const QString &imgInput,
                           const QString &imgOutput,
                           double mSmallScale,
                           double mMidScale,
                           double mLargeScale)
  : ProcessConcurrent(),
    IMsrcp(),
    mImgInput(imgInput),
    mImgOutput(imgOutput),
    mSmallScale(mSmallScale),
    mMidScale(mMidScale),
    mLargeScale(mLargeScale)
{

}

double MsrcpProcess::smallScale() const
{
  return mSmallScale;
}

void MsrcpProcess::setSmallScale(double smallScale)
{
  mSmallScale = smallScale;
}

double MsrcpProcess::midScale() const
{
  return mMidScale;
}

void MsrcpProcess::setMidScale(double midScale)
{
  mMidScale = midScale;
}

double MsrcpProcess::largeScale() const
{
  return mLargeScale;
}

void MsrcpProcess::setLargeScale(double largeScale)
{
  mLargeScale = largeScale;
}

void MsrcpProcess::reset()
{
  mImgInput.clear();
  mImgOutput.clear();
  mSmallScale = 10.;
  mMidScale = 100.;
  mLargeScale = 220.;
}

void MsrcpProcess::run()
{
  QByteArray ba = mImgInput.toLocal8Bit();
  const char *input_img = ba.data();
  cv::Mat img = cv::imread(input_img);

  cv::Mat color_boost;
  cv::Mat tmp;
  if (img.channels() == 1)  cv::cvtColor(img, tmp, cv::COLOR_GRAY2BGR);
  else img.copyTo(tmp);

  pixkit::enhancement::local::MSRCP2014(tmp, tmp);

  cv::Mat out;
  if (img.channels() >= 3){
    cv::decolor(tmp, out, color_boost);
  } else {
    cv::cvtColor(tmp, out, cv::COLOR_BGR2GRAY);
  }

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();
  cv::imwrite(output_img, out);
}

} // namespace fme
