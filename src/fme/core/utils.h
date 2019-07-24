#ifndef FME_UTILS_H
#define FME_UTILS_H

#include "fme/fme_global.h"

#include <opencv2/photo.hpp>

#include <QImageReader>

namespace fme
{

/*----------------------------------------------------------------*/

FME_EXPORT cv::Mat qImageToCvMat(const QImage &image);


/*----------------------------------------------------------------*/

} // namespace fme

#endif // FME_UTILS_H
