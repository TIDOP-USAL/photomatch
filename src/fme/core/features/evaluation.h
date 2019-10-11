#ifndef EVALUATION_H
#define EVALUATION_H

#include "fme/fme_global.h"

#include <opencv2/features2d.hpp>

#include <QPointF>

#include <map>

namespace fme
{

///TODO: mejor que sea una template para poder utilizar varios tipos de datos
///TODO: área bajo la curva (AUC)
class Curve
{

public:

  enum class Classification
  {
    tp,
    fp,
    tn,
    fn
  };

public:

  Curve(const std::vector<std::pair<double, int>> &data);

  /*!
   * \brief Confussion matrix for the specified threshold
   * \param[in] threshold
   * \return Confussion Matrix
   */
  std::map<Classification, size_t> confusionMatrix(double threshold) const;

  /*!
   * \brief positives
   * positives = TP + FN
   * \return
   */
  size_t positives() const;

  /*!
   * \brief negatives
   * negatives = FP + TN
   * \return
   */
  size_t negatives() const;

  size_t truePositives(double threshold) const;
  size_t falsePositives(double threshold) const;
  size_t trueNegatives(double threshold) const;
  size_t falseNegatives(double threshold) const;

  /*!
   * \brief accuracy
   * \param[in] threshold
   * \return
   */
  double accuracy(double threshold) const;

  /*!
   * \brief Precision or Positive Predictive Value
   * \param[in] threshold
   * \return
   */
  double positivePredictiveValue(double threshold) const;

  /*!
   * \brief Negative Predictive Value
   * \param[in] threshold
   * \return
   */
  double negativePredictiveValue(double threshold) const;

  /*!
   * \brief True Positive Rate, Recall or Sensitivity
   * \param[in] threshold
   * \return
   */
  double truePositiveRate(double threshold) const;

  /*!
   * \brief False Positive Rate or Fall-out
   * \param[in] threshold
   * \return
   */
  double falsePositiveRate(double threshold) const;

  /*!
   * \brief True Negative Rate or Specificity
   * \param[in] threshold
   * \return
   */
  double trueNegativeRate(double threshold) const;

  double falseNegativeRate(double threshold) const;

  virtual std::vector<QPointF> compute() = 0;


  static double truePositiveRate(size_t tp, size_t positives);
  static double falsePositiveRate(size_t fp, size_t negatives);
  static double trueNegativeRate(size_t tn, size_t negatives);
  static double falseNegativeRate(size_t fn, size_t positives);
  static double positivePredictiveValue(size_t tp, size_t fp);
  static double negativePredictiveValue(size_t fn, size_t tn);
  static double accuracy(size_t tp, size_t tn, size_t positives, size_t negatives);

protected:

  std::vector<std::pair<double, int>> mData;
  size_t mPositives;
  size_t mNegatives;

};


class PRCurve
  : public Curve
{

public:

  PRCurve(const std::vector<std::pair<double, int>> &data);

  std::vector<QPointF> compute() override;
};

class ROCCurve
  : public Curve
{

public:

  ROCCurve(const std::vector<std::pair<double, int>> &data);

  std::vector<QPointF> compute() override;

};

class DETCurve
  : public Curve
{

public:

  DETCurve(const std::vector<std::pair<double, int>> &data);

  std::vector<QPointF> compute() override;

};




///*!
// * \brief computePRCurve
// * \param[in] matches1to2
// * \param[in] correctMatches1to2Mask
// * \param[out] recallPrecisionCurve
// */
//FME_EXPORT void computePRCurve(const std::vector<std::vector<cv::DMatch>> &matches1to2,
//                               const std::vector<std::vector<uchar>> &correctMatches1to2Mask,
//                               std::vector<QPointF> &recallPrecisionCurve);
///*!
// * \brief computePRCurve
// * \param[in] matches1to2
// * \param[in] correctMatches1to2Mask
// * \param[out] recallPrecisionCurve
// */
//FME_EXPORT void computePRCurve(const std::vector<cv::DMatch> &matches1to2,
//                               const std::vector<uchar> &correctMatches1to2Mask,
//                               std::vector<QPointF> &recallPrecisionCurve);

} // namespace fme


#endif // EVALUATION_H
