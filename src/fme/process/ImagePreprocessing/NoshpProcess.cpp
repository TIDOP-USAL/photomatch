#include "NoshpProcess.h"

#include "fme/core/utils.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
{

NoshpProcess::NoshpProcess()
  : ProcessConcurrent(),
    INoshp(),
    mImgInput(""),
    mImgOutput(""),
    mBlockSize(127, 127)
{

}

NoshpProcess::NoshpProcess(const QString &imgInput,
                           const QString &imgOutput,
                           const QSize &blockSize)
  : ProcessConcurrent(),
    INoshp(),
    mImgInput(imgInput),
    mImgOutput(imgOutput),
    mBlockSize(blockSize)
{

}

QString NoshpProcess::imgOutput() const
{
  return mImgOutput;
}

void NoshpProcess::setImgOutput(const QString &imgOutput)
{
  mImgOutput = imgOutput;
}

QString NoshpProcess::imgInput() const
{
  return mImgInput;
}

void NoshpProcess::setImgInput(const QString &imgInput)
{
  mImgInput = imgInput;
}

QSize NoshpProcess::blockSize() const
{
  return mBlockSize;
}

void NoshpProcess::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void NoshpProcess::reset()
{
  mImgInput.clear();
  mImgOutput.clear();
  mBlockSize = QSize(127, 127);
}

void NoshpProcess::run()
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
  pixkit::enhancement::local::LiuJinChenLiuLi2011(img, out, cv::Size(mBlockSize.width(), mBlockSize.height()));

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();
  cv::imwrite(output_img, out);
}

} // namespace fme