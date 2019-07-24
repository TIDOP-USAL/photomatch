#include "LceBsescsProcess.h"

#include "fme/core/utils.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
{

LceBsescsProcess::LceBsescsProcess()
  : ProcessConcurrent(),
    ILceBsescs(),
    mImgInput(""),
    mImgOutput(""),
    mBlockSize(33, 33)
{

}

LceBsescsProcess::LceBsescsProcess(const QString &imgInput,
                                   const QString &imgOutput,
                                   const QSize &blockSize)
  : ProcessConcurrent(),
    ILceBsescs(),
    mImgInput(imgInput),
    mImgOutput(imgOutput),
    mBlockSize(blockSize)
{

}

QString LceBsescsProcess::imgInput() const
{
  return mImgInput;
}

void LceBsescsProcess::setImgInput(const QString &imgInput)
{
  mImgInput = imgInput;
}

QString LceBsescsProcess::imgOutput() const
{
  return mImgOutput;
}

void LceBsescsProcess::setImgOutput(const QString &imgOutput)
{
  mImgOutput = imgOutput;
}

QSize LceBsescsProcess::blockSize() const
{
  return mBlockSize;
}

void LceBsescsProcess::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void LceBsescsProcess::reset()
{
  mImgInput.clear();
  mImgOutput.clear();
  mBlockSize = QSize(33, 33);
}

void LceBsescsProcess::run()
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

  pixkit::enhancement::local::LCE_BSESCS2014(img, img, cv::Size(mBlockSize.width(), mBlockSize.height()));

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();
  cv::imwrite(output_img, img);
}

} // namespace fme
