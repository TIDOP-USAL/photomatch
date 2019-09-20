#include "ImagePreprocess.h"

#include "fme/core/utils.h"

#include <tidop/core/messages.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

namespace fme
{

ImagePreprocess::ImagePreprocess(const QString &imgInput,
                                 const QString &imgOutput,
                                 const std::shared_ptr<ImageProcess> &preprocess,
                                 int maxSize)
  : ProcessConcurrent(),
    mImgInput(imgInput),
    mImgOutput(imgOutput),
    mPreprocess(preprocess),
    mMaxSize(maxSize)
{

}

QString ImagePreprocess::imgOutput() const
{
  return mImgOutput;
}

void ImagePreprocess::setImgOutput(const QString &imgOutput)
{
  mImgOutput = imgOutput;
}

void ImagePreprocess::setMaxImageSize(int size)
{
  mMaxSize = size;
}

QString ImagePreprocess::imgInput() const
{
  return mImgInput;
}

void ImagePreprocess::setImgInput(const QString &imgInput)
{
  mImgInput = imgInput;
}

std::shared_ptr<ImageProcess> ImagePreprocess::preprocess() const
{
  return mPreprocess;
}

void ImagePreprocess::run()
{
  QByteArray ba = mImgInput.toLocal8Bit();
  const char *input_img = ba.data();

  msgInfo("Preprocessing image %s", input_img);

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
    msgInfo("Rescale image. New resolution: %ix%i px", size.width(), size.height());
  } else {
    img = cv::imread(input_img);
    //msgWarning("Full image size. ");
  }

  cv::Mat img_out = mPreprocess->process(img);

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();

  try {
    cv::imwrite(output_img, img_out);
    msgInfo("Write preprocessed image: %s", output_img);
    emit preprocessed(mImgOutput);
    emit statusChangedNext();
  } catch (cv::Exception& e) {
    msgError("Write preprocessed image Exception: %s\n", e.what());
  }

}

} // namespace fme
