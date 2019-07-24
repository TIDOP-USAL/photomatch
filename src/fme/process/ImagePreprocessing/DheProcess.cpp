#include "DheProcess.h"

#include "fme/core/utils.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
{

DheProcess::DheProcess()
  : ProcessConcurrent(),
    IDhe(),
    mImgInput(""),
    mImgOutput(""),
    mX(1)
{

}

DheProcess::DheProcess(const QString &imgInput, const QString &imgOutput, int x)
  : ProcessConcurrent(),
    IDhe(),
    mImgInput(imgInput),
    mImgOutput(imgOutput),
    mX(x)
{

}

DheProcess::~DheProcess()
{

}

QString DheProcess::imgInput() const
{
  return mImgInput;
}

void DheProcess::setImgInput(const QString &imgInput)
{
  mImgInput = imgInput;
}

QString DheProcess::imgOutput() const
{
  return mImgOutput;
}

void DheProcess::setImgOutput(const QString &imgOutput)
{
  mImgOutput = imgOutput;
}

int DheProcess::x() const
{
  return mX;
}

void DheProcess::setX(int x)
{
  mX = x;
}

void DheProcess::reset()
{
  mImgInput.clear();
  mImgOutput.clear();
  mX = 1;
}

void DheProcess::run()
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

  cv::Mat color_boost;
  if (img.channels() >= 3) {
    cv::decolor(img, img, color_boost);
    color_boost.release();
  }

  cv::Mat out;
  pixkit::enhancement::global::WadudKabirDewanChae2007(img, out, mX);
  img.release();

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();
  cv::imwrite(output_img, out);

}

} // namespace fme
