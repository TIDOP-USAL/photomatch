#include "ClaheProcess.h"

#include "fme/core/utils.h"

#include <opencv2/photo.hpp>
#include <opencv2/imgcodecs.hpp>

namespace fme
{

ClaheProcess::ClaheProcess()
  : ProcessConcurrent(),
    IClahe(),
    mImgInput(""),
    mImgOutput(""),
    mCvClahe(cv::createCLAHE())
{

}

ClaheProcess::ClaheProcess(const QString &imgInput,
                           const QString &imgOutput,
                           double clipLimit,
                           const QSize &tilesGridSize)
  : ProcessConcurrent(),
    IClahe(),
    mImgInput(imgInput),
    mImgOutput(imgOutput),
    mCvClahe(cv::createCLAHE())
{
  setClipLimit(clipLimit);
  setTilesGridSize(tilesGridSize);
}

QString ClaheProcess::imgOutput() const
{
  return mImgOutput;
}

void ClaheProcess::setImgOutput(const QString &imgOutput)
{
  mImgOutput = imgOutput;
}

QString ClaheProcess::imgInput() const
{
  return mImgInput;
}

void ClaheProcess::setImgInput(const QString &imgInput)
{
  mImgInput = imgInput;
}

double ClaheProcess::clipLimit() const
{
  return mCvClahe->getClipLimit();
}

void ClaheProcess::setClipLimit(double clipLimit)
{
  mCvClahe->setClipLimit(clipLimit);
}

QSize ClaheProcess::tilesGridSize() const
{
  cv::Size size = mCvClahe->getTilesGridSize();
  return QSize(size.width, size.height);
}

void ClaheProcess::setTilesGridSize(const QSize &tilesGridSize)
{
  mCvClahe->setTilesGridSize(cv::Size(tilesGridSize.width(), tilesGridSize.height()));
}

void ClaheProcess::reset()
{
  mImgInput.clear();
  mImgOutput.clear();
  setClipLimit(40.0);
  setTilesGridSize(QSize(8, 8));
}

void ClaheProcess::run()
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

  mCvClahe->apply(img, img);

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();
  cv::imwrite(output_img, img);
}

} // namespace fme
