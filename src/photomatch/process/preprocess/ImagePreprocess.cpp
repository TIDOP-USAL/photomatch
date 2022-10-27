/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#include "ImagePreprocess.h"

#include "photomatch/core/utils.h"

#include <tidop/core/utils.h>
#include <tidop/core/messages.h>
#include <tidop/core/exception.h>
#include <tidop/core/chrono.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include <QFileInfo>

namespace photomatch
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

  try {

    QByteArray ba = mImgInput.toLocal8Bit();
    const char *input_img = ba.data();

    if (!QFileInfo::exists(mImgInput)) TL_THROW_EXCEPTION("Image doesn't exist: %s", input_img);

    msgInfo("Preprocessing image %s", input_img);

    QImageReader imageReader(input_img);
    QSize size = imageReader.size();
    double scale = 1.;
    int w = size.width();
    int h = size.height();
    if (w > h) {
      scale = w / static_cast<double>(mMaxSize);
    } else {
      scale = h / static_cast<double>(mMaxSize);
    }

    cv::Mat img;
    img = cv::imread(input_img, cv::IMREAD_IGNORE_ORIENTATION);
    if (scale > 1.) {
      size /= scale;
      cv::resize(img, img, cv::Size(size.width(), size.height()));
      msgInfo("Rescale image. New resolution: %ix%i px", size.width(), size.height());
    }

    if (img.empty()) TL_THROW_EXCEPTION("Could not load image: %s", input_img);

    tl::Chrono chrono;
    chrono.run();
    cv::Mat img_out = mPreprocess->process(img);

    double time = chrono.stop();
    msgInfo("Preprocessed image %s [Time: %f seconds]", input_img, time);

    ba = mImgOutput.toLocal8Bit();
    const char *output_img = ba.data();

    cv::imwrite(output_img, img_out);
    msgInfo("Write preprocessed image: %s", output_img);
    emit preprocessed(mImgOutput);
    emit statusChangedNext();

  } catch (const std::exception &e) {
    tl::MessageManager::release(e.what(), tl::MessageLevel::msg_error);
  } catch (...) {
    msgError("Preprocess image unknow exception");
  }

}

} // namespace photomatch
