#include "DheProcess.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
{

DheProcess::DheProcess()
  : ProcessConcurrent(),
    IDhe(),
    mImgInput(""),
    mImgOutput(""),
    mX(1)
{

}

DheProcess::DheProcess(const QString &imgInput, const QString &imgOutput, int x)
  : ProcessConcurrent(),
    IDhe(),
    mImgInput(imgInput),
    mImgOutput(imgOutput),
    mX(x)
{

}

DheProcess::~DheProcess()
{

}

int DheProcess::x() const
{
  return mX;
}

void DheProcess::setX(int x)
{
  mX = x;
}

void DheProcess::reset()
{
  mX = 1;
}

void DheProcess::run()
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

  cv::Mat out;
  pixkit::enhancement::global::WadudKabirDewanChae2007(img, out, mX);

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();
  cv::imwrite(output_img, out);

}

} // namespace fme
