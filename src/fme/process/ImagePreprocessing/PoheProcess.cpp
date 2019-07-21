#include "PoheProcess.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace fme
{

PoheProcess::PoheProcess()
  : ProcessConcurrent(),
    IPohe(),
    mImgInput(""),
    mImgOutput(""),
    mBlockSize(127, 127)
{

}

PoheProcess::PoheProcess(const QString &imgInput,
                         const QString &imgOutput,
                         const QSize &blockSize)
  : ProcessConcurrent(),
    IPohe(),
    mImgInput(imgInput),
    mImgOutput(imgOutput),
    mBlockSize(blockSize)
{

}

QString PoheProcess::imgInput() const
{
    return mImgInput;
}

void PoheProcess::setImgInput(const QString &imgInput)
{
    mImgInput = imgInput;
}

QString PoheProcess::imgOutput() const
{
    return mImgOutput;
}

void PoheProcess::setImgOutput(const QString &imgOutput)
{
    mImgOutput = imgOutput;
}


QSize PoheProcess::blockSize() const
{
  return mBlockSize;
}

void PoheProcess::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void PoheProcess::reset()
{
  mImgInput.clear();
  mImgOutput.clear();
  mBlockSize = QSize(127, 127);
}

void PoheProcess::run()
{
  QByteArray ba = mImgInput.toLocal8Bit();
  const char *input_img = ba.data();
  cv::Mat img = cv::imread(input_img);

  cv::Mat tmp;
  if (img.channels() == 1)  cv::cvtColor(img, tmp, cv::COLOR_GRAY2BGR);
  else img.copyTo(tmp);

  ;
  cv::Mat out;
  pixkit::enhancement::local::MSRCP2014(tmp, out);
  cv::Mat color_boost;
  if (img.channels() >= 3) {
    cv::decolor(out, out, color_boost);
  } else {
    cv::cvtColor(out, out, cv::COLOR_BGR2GRAY);
  }

  ba = mImgOutput.toLocal8Bit();
  const char *output_img = ba.data();
  cv::imwrite(output_img, out);
}

} // namespace fme
