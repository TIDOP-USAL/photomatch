#ifndef PHOTOMATCH_UTILS_H
#define PHOTOMATCH_UTILS_H

#include "photomatch/photomatch_global.h"

#include <opencv2/photo.hpp>

#include <QImageReader>

namespace photomatch
{

/*----------------------------------------------------------------*/

PHOTOMATCH_EXPORT cv::Mat qImageToCvMat(const QImage &image);
PHOTOMATCH_EXPORT QImage cvMatToQImage(const cv::Mat &image);

/*----------------------------------------------------------------*/

} // namespace photomatch

#endif // PHOTOMATCH_UTILS_H
