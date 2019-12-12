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

/*----------------------------------------------------------------*/

} // namespace photomatch

#endif // PHOTOMATCH_UTILS_H
