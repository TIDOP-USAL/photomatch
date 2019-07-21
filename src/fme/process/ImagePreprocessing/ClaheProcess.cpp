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
  ///TODO: No hay que leer la imagen a resolución completa si se hace el calculo con un escalado de la imagen
  ///TODO: Chequeo de los parámetros
  QByteArray ba = mImgInput.toLocal8Bit();
  const char *input_img = ba.data();
  cv::Mat img = cv::imread(input_img);

  cv::Mat color_boost;
  if (img.channels() >= 3) {
    cv::decolor(img, img, color_boost);
  }

  mCvClahe->apply(img, img);

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();
  cv::imwrite(output_img, img);
}

} // namespace fme
