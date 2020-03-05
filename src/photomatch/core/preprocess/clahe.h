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


#ifndef PHOTOMATCH_CLAHE_PREPROCESS_H
#define PHOTOMATCH_CLAHE_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>
#ifdef HAVE_CUDA
#include <opencv2/cudaimgproc.hpp>
#endif // HAVE_CUDA

#include <QString>

namespace photomatch
{


/*!
 * \brief CLAHE image preprocess class
 */
class PHOTOMATCH_EXPORT ClaheProperties
  : public Clahe
{

public:

  ClaheProperties();
  ClaheProperties(const ClaheProperties &claheProperties);
  ~ClaheProperties() override = default;

// IClahe interface

public:

  /*!
   * \brief Return threshold value for contrast limiting
   * \return
   */
  double clipLimit() const override;

  /*!
   * \brief Set threshold value for contrast limiting
   * \param clipLimit
   */
  void setClipLimit(double clipLimit) override;

  /*!
   * \brief Returns the number of tiles in row and column.
   * \return
   */
  QSize tilesGridSize() const override;

  /*!
   * \brief Sets size of grid for histogram equalization. Input image will be divided into equally sized rectangular tiles.
   * \param[in] tilesGridSize
   */
  void setTilesGridSize(const QSize &tilesGridSize) override;

// Preprocess interface

public:

  void reset() override;
  QString name() const final;

private:

  double mClipLimit;
  QSize mTilesGridSize;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT ClahePreprocess
  : public ClaheProperties,
    public ImageProcess
{

public:

  ClahePreprocess();
  ClahePreprocess(const ClahePreprocess &clahePreprocess);
  ClahePreprocess(double clipLimit, const QSize &tilesGridSize);
  ~ClahePreprocess() override;

// Preprocess interface

public:

  void reset() override;

// IClahe interface

public:

  void setClipLimit(double clipLimit) override;
  void setTilesGridSize(const QSize &tilesGridSize) override;

// ImageProcess interface

public:

  bool process(const cv::Mat &imgIn, cv::Mat &imgOut) override;

protected:

  cv::Ptr<cv::CLAHE> mCvClahe;

};

/*----------------------------------------------------------------*/

#ifdef HAVE_CUDA

class PHOTOMATCH_EXPORT ClahePreprocessCuda
  : public ClaheProperties,
    public ImageProcess
{

public:

  ClahePreprocessCuda();
  ClahePreprocessCuda(const ClahePreprocessCuda &clahePreprocessCuda);
  ClahePreprocessCuda(double clipLimit, const QSize &tilesGridSize);
  ~ClahePreprocessCuda() override;

// Preprocess interface

public:

  void reset() override;

// IClahe interface

public:

  void setClipLimit(double clipLimit) override;
  void setTilesGridSize(const QSize &tilesGridSize) override;

// ImageProcess interface

public:

  bool process(const cv::Mat &imgIn, cv::Mat &imgOut) override;

protected:

  cv::Ptr<cv::cuda::CLAHE> mCvClahe;

};

#endif // HAVE_CUDA

} // namespace photomatch

#endif // PHOTOMATCH_CLAHE_PREPROCESS_H
