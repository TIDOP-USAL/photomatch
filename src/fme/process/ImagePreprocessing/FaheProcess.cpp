#include "FaheProcess.h"

#include <pixkit-image.hpp>

#include <opencv2/core.hpp>
#include <opencv2/photo.hpp>

namespace fme
{

//FaheProcess::FaheProcess(cv::Mat &cvImgLeft, cv::Mat &cvImgRight, const cv::Size &blockSize, const QDir &outputDir)
//  : mCvImg_left(cvImgLeft),
//    mCvImg_right(cvImgRight),
//    mBlockSize(blockSize),
//    mOutputDir(outputDir)
//{

//}



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
  ///TODO: No hay que leer la imagen a resolución completa si se hace el calculo con un escalado de la imagen
  ///TODO: Chequeo de los parámetros
  QByteArray ba = mImgInput.toLocal8Bit();
  const char *input_img = ba.data();
  cv::Mat img_in = cv::imread(input_img);

  cv::Mat color_boost;
  if (img_in.channels() >= 3) {
    cv::decolor(img_in, img_in, color_boost);
  }

  cv::Mat img_out;
  pixkit::enhancement::local::FAHE2006(img_in, img_out, cv::Size(mBlockSize.width(), mBlockSize.height()));

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
  mBlockSize = QSize(11, 11);
}

} // namespace fme
