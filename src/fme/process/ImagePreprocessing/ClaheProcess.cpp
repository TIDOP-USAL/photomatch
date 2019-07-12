#include "ClaheProcess.h"

//#include <opencv2/core.hpp>
#include <opencv2/photo.hpp>
//#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

namespace fme
{

ClaheProcess::ClaheProcess()
  : ProcessConcurrent(),
    IClahe(),
    mImgInput(""),
    mImgOutput(""),
    mClipLimit(40.0),
    mTilesGridSize(8, 8)
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
    mClipLimit(clipLimit),
    mTilesGridSize(tilesGridSize)
{

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
  return mClipLimit;
}

void ClaheProcess::setClipLimit(double clipLimit)
{
  mClipLimit = clipLimit;
}

QSize ClaheProcess::tilesGridSize() const
{
  return mTilesGridSize;
}

void ClaheProcess::setTilesGridSize(const QSize &tilesGridSize)
{
  mTilesGridSize = tilesGridSize;
}

void ClaheProcess::reset()
{
  mImgInput = "";
  mImgOutput = "";
  mClipLimit = 40.0;
  mTilesGridSize = QSize(8, 8);
}

void ClaheProcess::run()
{
  ///TODO: No hay que leer la imagen a resolución completa si se hace el calculo con un escalado de la imagen
  ///TODO: Chequeo de los parámetros
  QByteArray ba = mImgInput.toLocal8Bit();
  const char *input_img = ba.data();
  cv::Mat img = cv::imread(input_img);

  cv::Mat color_boost;
  if (img.channels() >= 3) {
    cv::decolor(img, img, color_boost);
  }

  cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
  clahe->setClipLimit(mClipLimit);
  clahe->setTilesGridSize(cv::Size(mTilesGridSize.width(), mTilesGridSize.height()));
  clahe->apply(img, img);

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();
  cv::imwrite(output_img, img);
}

} // namespace fme
