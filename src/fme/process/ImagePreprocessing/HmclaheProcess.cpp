#include "HmclaheProcess.h"

#include "fme/core/utils.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
{

HmclaheProcess::HmclaheProcess()
  : ProcessConcurrent(),
    IHmclahe(),
    mImgInput(""),
    mImgOutput(""),
    mBlockSize(17,17),
    mL(0.03),
    mPhi(0.5)
{

}

HmclaheProcess::HmclaheProcess(const QString &imgInput,
                               const QString &imgOutput,
                               const QSize &blockSize,
                               double l,
                               double phi)
  : ProcessConcurrent(),
    IHmclahe(),mImgInput(imgInput),
    mImgOutput(imgOutput),
    mBlockSize(blockSize),
    mL(l),
    mPhi(phi)
{

}

HmclaheProcess::~HmclaheProcess()
{

}

QString HmclaheProcess::imgInput() const
{
  return mImgInput;
}

void HmclaheProcess::setImgInput(const QString &imgInput)
{
  mImgInput = imgInput;
}

QString HmclaheProcess::imgOutput() const
{
  return mImgOutput;
}

void HmclaheProcess::setImgOutput(const QString &imgOutput)
{
  mImgOutput = imgOutput;
}

QSize HmclaheProcess::blockSize() const
{
  return mBlockSize;
}

void HmclaheProcess::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

double HmclaheProcess::l() const
{
  return mL;
}

void HmclaheProcess::setL(double l)
{
  mL = l;
}

double HmclaheProcess::phi() const
{
  return mPhi;
}

void HmclaheProcess::setPhi(double phi)
{
  mPhi = phi;
}

void HmclaheProcess::reset()
{
  mImgInput.clear();
  mImgOutput.clear();
  mBlockSize = QSize(17,17);
  mL = 0.03;
  mPhi = 0.5;
}

void HmclaheProcess::run()
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
  pixkit::enhancement::local::Sundarami2011(img, img_out, cv::Size(mBlockSize.width(), mBlockSize.height()), static_cast<float>(mL), static_cast<float>(mPhi));
  img.release();

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();
  cv::imwrite(output_img, img_out);
}

} // namespace fme



