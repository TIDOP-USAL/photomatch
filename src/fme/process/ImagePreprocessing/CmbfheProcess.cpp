#include "CmbfheProcess.h"

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
  mBlockSize = QSize(11, 11);
}

void CmbfheProcess::run()
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
  pixkit::enhancement::local::LambertiMontrucchioSanna2006(img, out, cv::Size(mBlockSize.width(), mBlockSize.height()), cv::Size(44,44));

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();
  cv::imwrite(output_img, out);
}

} // namespace fme
