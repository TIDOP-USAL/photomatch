#ifndef EVALUATION_H
#define EVALUATION_H

#include "fme/fme_global.h"

#include <opencv2/features2d.hpp>

#include <QPointF>

namespace fme
{

/*!
 * \brief computePRCurve
 * \param[in] matches1to2
 * \param[in] correctMatches1to2Mask
 * \param[out] recallPrecisionCurve
 */
FME_EXPORT void computePRCurve(const std::vector<std::vector<cv::DMatch>> &matches1to2,
                               const std::vector<std::vector<uchar>> &correctMatches1to2Mask,
                               std::vector<QPointF> &recallPrecisionCurve);
/*!
 * \brief computePRCurve
 * \param[in] matches1to2
 * \param[in] correctMatches1to2Mask
 * \param[out] recallPrecisionCurve
 */
FME_EXPORT void computePRCurve(const std::vector<cv::DMatch> &matches1to2,
                               const std::vector<uchar> &correctMatches1to2Mask,
                               std::vector<QPointF> &recallPrecisionCurve);
/*!
 * \brief computeROCCurve
 * \param[in] matches1to2
 * \param[in] correctMatches1to2Mask
 * \param[out] rocCurve
 */
FME_EXPORT void computeROCCurve(const std::vector<std::vector<cv::DMatch>> &matches1to2,
                                const std::vector<std::vector<uchar>> &correctMatches1to2Mask,
                                std::vector<QPointF> &rocCurve);

/*!
 * \brief computeROCCurve
 * \param[in] matches1to2
 * \param[in] correctMatches1to2Mask
 * \param[out] rocCurve
 */
FME_EXPORT void computeROCCurve(const std::vector<cv::DMatch> &matches1to2,
                                const std::vector<uchar> &correctMatches1to2Mask,
                                std::vector<QPointF> &rocCurve);

} // namespace fme


#endif // EVALUATION_H
