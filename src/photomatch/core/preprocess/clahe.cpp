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


#include "clahe.h"

#include "photomatch/core/utils.h"

#include <tidop/core/messages.h>

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


ClaheProperties::ClaheProperties()
  : Clahe(),
    mClipLimit(40.),
    mTilesGridSize(QSize(8, 8))
{
}

ClaheProperties::ClaheProperties(const ClaheProperties &claheProperties)
  : Clahe(),
    mClipLimit(claheProperties.mClipLimit),
    mTilesGridSize(claheProperties.mTilesGridSize)
{
}

double ClaheProperties::clipLimit() const
{
  return mClipLimit;
}

void ClaheProperties::setClipLimit(double clipLimit)
{
  mClipLimit = clipLimit;
}

QSize ClaheProperties::tilesGridSize() const
{
  return mTilesGridSize;
}

void ClaheProperties::setTilesGridSize(const QSize &tilesGridSize)
{
  mTilesGridSize = tilesGridSize;
}

void ClaheProperties::reset()
{
  mClipLimit = 40.0;
  mTilesGridSize = QSize(8, 8);
}

QString ClaheProperties::name() const
{
  return QString("CLAHE");
}


/*----------------------------------------------------------------*/


ClahePreprocess::ClahePreprocess()
  : ClaheProperties(),
    ImageProcess()
{
  cv::Size size(ClaheProperties::tilesGridSize().width(),
                ClaheProperties::tilesGridSize().height());
  mCvClahe = cv::createCLAHE(ClaheProperties::clipLimit(), size);
}

ClahePreprocess::ClahePreprocess(const ClahePreprocess &clahePreprocess)
  : ClaheProperties(clahePreprocess),
    ImageProcess()
{
  cv::Size size(ClaheProperties::tilesGridSize().width(),
                ClaheProperties::tilesGridSize().height());
  mCvClahe = cv::createCLAHE(ClaheProperties::clipLimit(), size);
}

ClahePreprocess::ClahePreprocess(double clipLimit,
                                 const QSize &tilesGridSize)
  : ClaheProperties(),
    ImageProcess(),
    mCvClahe(cv::createCLAHE())
{
  setClipLimit(clipLimit);
  setTilesGridSize(tilesGridSize);
}

ClahePreprocess::~ClahePreprocess()
{

}

void ClahePreprocess::reset()
{
  ClaheProperties::reset();
  cv::Size size(ClaheProperties::tilesGridSize().width(),
                ClaheProperties::tilesGridSize().height());
  mCvClahe->setClipLimit(ClaheProperties::clipLimit());
  mCvClahe->setTilesGridSize(size);
}

void ClahePreprocess::setClipLimit(double clipLimit)
{
  ClaheProperties::setClipLimit(clipLimit);
  mCvClahe->setClipLimit(clipLimit);
}

void ClahePreprocess::setTilesGridSize(const QSize &tilesGridSize)
{
  ClaheProperties::setTilesGridSize(tilesGridSize);
  mCvClahe->setTilesGridSize(cv::Size(tilesGridSize.width(), tilesGridSize.height()));
}

bool ClahePreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{
  try {

    mCvClahe->apply(convertToGray(imgIn), imgOut);

  } catch (cv::Exception &e) {
    msgError("CLAHE image preprocess error: %s", e.what());
    return true;
  }

  return false;
}


/*----------------------------------------------------------------*/


#ifdef HAVE_CUDA

ClahePreprocessCuda::ClahePreprocessCuda()
  : ClaheProperties(),
    ImageProcess()
{
  cv::Size size(ClaheProperties::tilesGridSize().width(),
                ClaheProperties::tilesGridSize().height());
  mCvClahe = cv::cuda::createCLAHE(ClaheProperties::clipLimit(), size);
}

ClahePreprocessCuda::ClahePreprocessCuda(const ClahePreprocessCuda &clahePreprocessCuda)
  : ClaheProperties(clahePreprocessCuda),
    ImageProcess()
{
  cv::Size size(ClaheProperties::tilesGridSize().width(),
                ClaheProperties::tilesGridSize().height());
  mCvClahe = cv::cuda::createCLAHE(ClaheProperties::clipLimit(), size);
}

ClahePreprocessCuda::ClahePreprocessCuda(double clipLimit, const QSize &tilesGridSize)
  : ClaheProperties(),
    ImageProcess(),
    mCvClahe(cv::cuda::createCLAHE())
{
  setClipLimit(clipLimit);
  setTilesGridSize(tilesGridSize);
}

ClahePreprocessCuda::~ClahePreprocessCuda()
{

}

void ClahePreprocessCuda::reset()
{
  ClaheProperties::reset();
  cv::Size size(ClaheProperties::tilesGridSize().width(),
                ClaheProperties::tilesGridSize().height());
  mCvClahe->setClipLimit(ClaheProperties::clipLimit());
  mCvClahe->setTilesGridSize(size);
}

void ClahePreprocessCuda::setClipLimit(double clipLimit)
{
  ClaheProperties::setClipLimit(clipLimit);
  mCvClahe->setClipLimit(clipLimit);
}

void ClahePreprocessCuda::setTilesGridSize(const QSize &tilesGridSize)
{
  ClaheProperties::setTilesGridSize(tilesGridSize);
  mCvClahe->setTilesGridSize(cv::Size(tilesGridSize.width(), tilesGridSize.height()));
}

bool ClahePreprocessCuda::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{
  try {

    if (imgIn.channels() >= 3) {
      cv::Mat color_boost;
      cv::decolor(imgIn, imgOut, color_boost);
      color_boost.release();
    } else {
      imgIn.copyTo(imgOut);
    }

    cv::cuda::GpuMat gImgOut(imgOut);
    mCvClahe->apply(gImgOut, gImgOut);
    gImgOut.download(imgOut);
  } catch (cv::Exception &e) {
    msgError("CLAHE image preprocess error: %s", e.what());
    return true;
  }

  return false;
}

#endif // HAVE_CUDA


} // namespace photomatch







