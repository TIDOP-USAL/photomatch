#include "CmbfheProcess.h"

#include "fme/core/utils.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
{

CmbfheProcess::CmbfheProcess()
  : ProcessConcurrent(),
    ICmbfhe(),
    mImgInput(""),
    mImgOutput(""),
    mBlockSize(11, 11)
{

}

CmbfheProcess::CmbfheProcess(const QString &imgInput,
                             const QString &imgOutput,
                             const QSize &blockSize)
  : ProcessConcurrent(),
    ICmbfhe(),
    mImgInput(imgInput),
    mImgOutput(imgOutput),
    mBlockSize(blockSize)
{

}

QString CmbfheProcess::imgInput() const
{
  return mImgInput;
}

void CmbfheProcess::setImgInput(const QString &imgInput)
{
  mImgInput = imgInput;
}

QString CmbfheProcess::imgOutput() const
{
  return mImgOutput;
}

void CmbfheProcess::setImgOutput(const QString &imgOutput)
{
  mImgOutput = imgOutput;
}

QSize CmbfheProcess::blockSize() const
{
  return mBlockSize;
}

void CmbfheProcess::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void CmbfheProcess::reset()
{
  mImgInput.clear();
  mImgOutput.clear();
  mBlockSize = QSize(11, 11);
}

void CmbfheProcess::run()
{
  QByteArray ba = mImgInput.toLocal8Bit();
  const char *input_img = ba.data();

  double scale = 1.;
  cv::Mat img;
  if (mMaxSize != -1) {
    QImageReader imageReader(input_img);
    QSize size = imageReader.size();

    int w = size.width();
    int h = size.height();
    if (w > h){
      scale = w / static_cast<double>(mMaxSize);
    } else {
      scale = h / static_cast<double>(mMaxSize);
    }

    if (scale > 1.) {
      size /= scale;
      imageReader.setScaledSize(size);
      QImage image_scaled = imageReader.read();
      img = qImageToCvMat(image_scaled);
    }
  }

  if (scale <= 1.) {
    img = cv::imread(input_img);
  }

  cv::Mat color_boost;
  if (img.channels() >= 3) {
    cv::decolor(img, img, color_boost);
    color_boost.release();
  }

  cv::Mat out;
  pixkit::enhancement::local::LambertiMontrucchioSanna2006(img, out, cv::Size(mBlockSize.width(), mBlockSize.height()), cv::Size(44,44));
  img.release();

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();
  cv::imwrite(output_img, out);
}

} // namespace fme
