#include "FaheProcess.h"

#include "fme/core/utils.h"

#include <pixkit-image.hpp>

#include <opencv2/core.hpp>
#include <opencv2/photo.hpp>

namespace fme
{

FaheProcess::FaheProcess()
  : ProcessConcurrent(),
    IFahe(),
    mImgInput(""),
    mImgOutput(""),
    mBlockSize(11, 11)
{

}

FaheProcess::FaheProcess(const QString &imgInput,
                         const QString &imgOutput,
                         const QSize &blockSize)
  : ProcessConcurrent(),
    IFahe(),
    mImgInput(imgInput),
    mImgOutput(imgOutput),
    mBlockSize(blockSize)
{

}

QString FaheProcess::imgInput() const
{
  return mImgInput;
}

void FaheProcess::setImgInput(const QString &imgInput)
{
  mImgInput = imgInput;
}

QString FaheProcess::imgOutput() const
{
  return mImgOutput;
}

void FaheProcess::setImgOutput(const QString &imgOutput)
{
  mImgOutput = imgOutput;
}

void FaheProcess::run()
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

  cv::Mat img_out;
  pixkit::enhancement::local::FAHE2006(img, img_out, cv::Size(mBlockSize.width(), mBlockSize.height()));
  img.release();

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();
  cv::imwrite(output_img, img_out);

}

QSize FaheProcess::blockSize() const
{
  return mBlockSize;
}

void FaheProcess::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void FaheProcess::reset()
{
  mImgInput = "";
  mImgOutput = "";
  mBlockSize = QSize(11, 11);
}

} // namespace fme
