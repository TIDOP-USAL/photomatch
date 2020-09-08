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


#ifndef PHOTOMATCH_UTILS_H
#define PHOTOMATCH_UTILS_H

#include "photomatch/photomatch_global.h"

#include <opencv2/photo.hpp>

#include <QImageReader>

namespace photomatch
{

/*----------------------------------------------------------------*/

/*!
 * \brief Convert QImage to cv::Mat
 * \param[in] image QImage
 * \return cv::Mat
 */
PHOTOMATCH_EXPORT cv::Mat qImageToCvMat(const QImage &image);

/*!
 * \brief Convert cv::Mat to QImage
 * \param[in] image cv::Mat
 * \return QImage
 */
PHOTOMATCH_EXPORT QImage cvMatToQImage(const cv::Mat &image);


PHOTOMATCH_EXPORT cv::Mat convertToGray(const cv::Mat &image);

PHOTOMATCH_EXPORT QSize cvSizeToQSize(const cv::Size &size);
PHOTOMATCH_EXPORT cv::Size qSizeToCvSize(const QSize &size);

/*----------------------------------------------------------------*/

template <typename T>
static float distancePointLine(const cv::Point_<T> point, const cv::Vec3f &line)
{
  return std::fabsf(line(0)*point.x + line(1)*point.y + line(2))
      / std::sqrt(line(0)*line(0)+line(1)*line(1));
}


/*----------------------------------------------------------------*/


PHOTOMATCH_EXPORT bool cudaEnabled();
PHOTOMATCH_EXPORT bool cudaEnabled(double minDriver, double minCapability);


} // namespace photomatch

#endif // PHOTOMATCH_UTILS_H
