#include "AcebsfProcess.h"

#include "fme/core/utils.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
{

AcebsfProcess::AcebsfProcess()
  : ProcessConcurrent(),
    IAcebsf(),
    mImgInput(""),
    mImgOutput(""),
    mBlockSize(8, 8),
    mL(0.03),
    mK1(10.),
    mK2(0.5)
{

}

AcebsfProcess::AcebsfProcess(const QString &imgInput,
                             const QString &imgOutput,
                             const QSize &blockSize,
                             double l, double k1, double k2)
  : ProcessConcurrent(),
    IAcebsf(),
    mImgInput(imgInput),
    mImgOutput(imgOutput),
    mBlockSize(blockSize),
    mL(l),
    mK1(k1),
    mK2(k2)
{

}

AcebsfProcess::~AcebsfProcess()
{

}

QSize AcebsfProcess::blockSize() const
{
  return mBlockSize;
}

void AcebsfProcess::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

double AcebsfProcess::l() const
{
  return mL;
}

void AcebsfProcess::setL(double l)
{
  mL = l;
}

double AcebsfProcess::k1() const
{
  return mK1;
}

void AcebsfProcess::setK1(double k1)
{
  mK1 = k1;
}

double AcebsfProcess::k2() const
{
  return mK2;
}

void AcebsfProcess::setK2(double k2)
{
  mK2 = k2;
}

void fme::AcebsfProcess::reset()
{
  mImgInput.clear();
  mImgOutput.clear();
  mBlockSize = QSize(8, 8);
  mL = 0.03;
  mK1 = 10.;
  mK2 = 0.5;
}

void fme::AcebsfProcess::run()
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

  pixkit::enhancement::local::Lal2014(tmp, tmp, cv::Size(mBlockSize.width(), mBlockSize.height()),
                                      static_cast<float>(mL), static_cast<float>(mK1), static_cast<float>(mK2));
  cv::Mat color_boost;
  if (img.channels() >= 3) {
    cv::decolor(tmp, img, color_boost);
  } else {
    cv::cvtColor(tmp, img, cv::COLOR_BGR2GRAY);
  }
  color_boost.release();
  tmp.release();

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();
  cv::imwrite(output_img, img);
}

} // namespace fme
