#include "MsrcpProcess.h"

#include "fme/core/utils.h"

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

  QImageReader imageReader(input_img);
  QSize size = imageReader.size();
  double scale = 1.;
  int w = size.width();
  int h = size.height();
  if (w > h){
    scale = w / static_cast<double>(mMaxSize);
  } else {
    scale = h / static_cast<double>(mMaxSize);
  }

  cv::Mat img;
  if (scale > 1.) {
    size /= scale;
    imageReader.setScaledSize(size);
    QImage image_scaled = imageReader.read();
    img = qImageToCvMat(image_scaled);

  } else {
    img = cv::imread(input_img);
  }


  cv::Mat tmp;
  if (img.channels() == 1)  cv::cvtColor(img, tmp, cv::COLOR_GRAY2BGR);
  else img.copyTo(tmp);

  cv::Mat tmp2;
  pixkit::enhancement::local::MSRCP2014(tmp, tmp2);
  tmp.release();

  cv::Mat color_boost;
  cv::Mat out;
  if (img.channels() >= 3){
    cv::decolor(tmp2, out, color_boost);
    color_boost.release();
  } else {
    cv::cvtColor(tmp2, out, cv::COLOR_BGR2GRAY);
  }
  img.release();
  tmp2.release();

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();
  cv::imwrite(output_img, out);
}

} // namespace fme
