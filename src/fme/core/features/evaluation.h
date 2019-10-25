#ifndef EVALUATION_H
#define EVALUATION_H

#include "fme/fme_global.h"

#include <opencv2/features2d.hpp>

#include <QPointF>

#include <map>

namespace fme
{

template<typename T>
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

  Curve(const std::vector<std::pair<T, int>> &data);

  /*!
   * \brief Confussion matrix for the specified threshold
   * \param[in] threshold
   * \return Confussion Matrix
   */
  std::map<Classification, size_t> confusionMatrix(T threshold) const;

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

  size_t truePositives(T threshold) const;
  size_t falsePositives(T threshold) const;
  size_t trueNegatives(T threshold) const;
  size_t falseNegatives(T threshold) const;

  /*!
   * \brief accuracy
   * \param[in] threshold
   * \return
   */
  double accuracy(T threshold) const;

  /*!
   * \brief Precision or Positive Predictive Value
   * \param[in] threshold
   * \return
   */
  double positivePredictiveValue(T threshold) const;

  /*!
   * \brief Negative Predictive Value
   * \param[in] threshold
   * \return
   */
  double negativePredictiveValue(T threshold) const;

  /*!
   * \brief True Positive Rate, Recall or Sensitivity
   * \param[in] threshold
   * \return
   */
  double truePositiveRate(T threshold) const;

  /*!
   * \brief False Positive Rate or Fall-out
   * \param[in] threshold
   * \return
   */
  double falsePositiveRate(T threshold) const;

  /*!
   * \brief True Negative Rate or Specificity
   * \param[in] threshold
   * \return
   */
  double trueNegativeRate(T threshold) const;

  double falseNegativeRate(T threshold) const;

  virtual void compute(size_t steeps) = 0;

  std::vector<QPointF> curve() const;

  double auc() const;

  static double truePositiveRate(size_t tp, size_t positives);
  static double falsePositiveRate(size_t fp, size_t negatives);
  static double trueNegativeRate(size_t tn, size_t negatives);
  static double falseNegativeRate(size_t fn, size_t positives);
  static double positivePredictiveValue(size_t tp, size_t fp);
  static double negativePredictiveValue(size_t fn, size_t tn);
  static double accuracy(size_t tp, size_t tn, size_t positives, size_t negatives);

protected:

  std::vector<std::pair<T, int>> mData;
  std::vector<QPointF> mCurve;
  size_t mPositives;
  size_t mNegatives;
  double mAuc;

};



/*------------------------------------------------------------------------------------*/



template<typename T>
class PRCurve
  : public Curve<T>
{

public:

  PRCurve(const std::vector<std::pair<T, int>> &data, size_t steeps = 100);

  void compute(size_t steeps = 100) override;
};



/*------------------------------------------------------------------------------------*/



template<typename T>
class ROCCurve
  : public Curve<T>
{

public:

  ROCCurve(const std::vector<std::pair<T, int>> &data, size_t steeps = 100);

  void compute(size_t steeps = 100) override;

};



/*------------------------------------------------------------------------------------*/



template<typename T>
class DETCurve
  : public Curve<T>
{

public:

  DETCurve(const std::vector<std::pair<T, int>> &data, size_t steeps = 100);

  void compute(size_t steeps = 100) override;

};



/*------------------------------------------------------------------------------------*/


/* Curve class implementation */

template<typename T> 
Curve<T>::Curve(const std::vector<std::pair<T, int>> &data)
  : mData(data),
    mCurve(0),
    mPositives(0),
    mNegatives(0),
    mAuc(0.0)
{
  std::sort(mData.begin(), mData.end(),
            [](const std::pair<T, int> &data1,
               const std::pair<T, int> &data2){
    return data1.first < data2.first;});

  for(size_t i = 0; i < mData.size(); i++) {
    if (mData[i].second == 1){
      mPositives++;
    } else {
      mNegatives++;
    }
  }

}

template<typename T> inline
std::map<typename Curve<T>::Classification,size_t> Curve<T>::confusionMatrix(T threshold) const
{

  size_t tp = 0, fp = 0, tn = 0, fn = 0;
  for(size_t j = 0; j < mData.size(); j++ ) {

    if (mData[j].first <= threshold){
      if (mData[j].second == 1)
        tp++;
      else
        fp++;
    } else {
      if (mData[j].second == 0)
        tn++;
      else
        fn++;
    }
  }
  std::map<Classification,size_t> confussionMatrix;
  confussionMatrix[Classification::tp] = tp;
  confussionMatrix[Classification::fp] = fp;
  confussionMatrix[Classification::tn] = tn;
  confussionMatrix[Classification::fn] = fn;

  return confussionMatrix;
}

template<typename T> inline
size_t Curve<T>::positives() const
{
  return mPositives;
}

template<typename T> inline
size_t Curve<T>::negatives() const
{
  return mNegatives;
}

template<typename T> inline
size_t Curve<T>::truePositives(T threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  return confussionMatrix[Classification::tp];
}

template<typename T> inline
size_t Curve<T>::falsePositives(T threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  return confussionMatrix[Classification::fp];
}

template<typename T> inline
size_t Curve<T>::trueNegatives(T threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  return confussionMatrix[Classification::tn];
}

template<typename T> inline
size_t Curve<T>::falseNegatives(T threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  return confussionMatrix[Classification::fn];
}

template<typename T> inline
double Curve<T>::accuracy(T threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);

  return (mPositives + mNegatives) ?
    static_cast<double>(confussionMatrix[Classification::tp]+confussionMatrix[Classification::tn])
      / static_cast<double>(mPositives + mNegatives) : -1;
}

template<typename T> inline
double Curve<T>::positivePredictiveValue(T threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  double tp = confussionMatrix[Classification::tp];
  double fp = confussionMatrix[Classification::fp];
  return ( (tp + fp) > 0.) ? tp / (tp + fp) : -1;
}

template<typename T> inline
double Curve<T>::negativePredictiveValue(T threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  double fn = confussionMatrix[Classification::fn];
  double tn = confussionMatrix[Classification::tn];
  return (fn + tn > 0.) ? tn / (fn + tn) : -1;
}

template<typename T> inline
double Curve<T>::truePositiveRate(T threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  double tp = confussionMatrix[Classification::tp];
  return mPositives ? tp / static_cast<double>(mPositives) : -1;
}

template<typename T> inline
double Curve<T>::falsePositiveRate(T threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  double fp = confussionMatrix[Classification::fp];
  return mNegatives ? static_cast<double>(fp) / static_cast<double>(mNegatives) : -1;
}

template<typename T> inline
double Curve<T>::trueNegativeRate(T threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  double tn = confussionMatrix[Classification::tn];
  return mNegatives ? static_cast<double>(tn) / static_cast<double>(mNegatives) : -1;
}

template<typename T> inline
double Curve<T>::falseNegativeRate(T threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  double fn = confussionMatrix[Classification::fn];
  return mPositives ? static_cast<double>(fn) / static_cast<double>(mPositives) : -1;
}

template<typename T>
std::vector<QPointF> Curve<T>::curve() const
{
  return mCurve;
}

template<typename T>
double Curve<T>::auc() const
{
  return mAuc;
}

template<typename T> inline
double Curve<T>::truePositiveRate(size_t tp, size_t positives)
{
  return positives ? static_cast<double>(tp) / static_cast<double>(positives) : -1;
}

template<typename T> inline
double Curve<T>::falsePositiveRate(size_t fp, size_t negatives)
{
  return negatives ? static_cast<double>(fp) / static_cast<double>(negatives) : -1;
}

template<typename T> inline
double Curve<T>::trueNegativeRate(size_t tn, size_t negatives)
{
  return negatives ? static_cast<double>(tn) / static_cast<double>(negatives) : -1;
}

template<typename T> inline
double Curve<T>::falseNegativeRate(size_t fn, size_t positives)
{
  return positives ? static_cast<double>(fn) / static_cast<double>(positives) : -1;
}

template<typename T> inline
double Curve<T>::positivePredictiveValue(size_t tp, size_t fp)
{
  return ( (tp + fp) > 0.) ? tp / (tp + fp) : -1;
}

template<typename T> inline
double Curve<T>::negativePredictiveValue(size_t fn, size_t tn)
{
  return (fn + tn > 0.) ? tn / (fn + tn) : -1;
}

template<typename T> inline
double Curve<T>::accuracy(size_t tp, size_t tn, size_t positives, size_t negatives)
{

  return (positives + negatives) ?
    static_cast<double>(tp+tn)
      / static_cast<double>(positives + negatives) : -1;
}



/*------------------------------------------------------------------------------------*/


/* PR Curve class implementation */

template<typename T>
PRCurve<T>::PRCurve(const std::vector<std::pair<T, int>> &data, size_t steeps)
  : Curve<T>(data)
{
  this->compute(steeps);
}


///TODO: para enteros habria que especializar la plantilla
template<typename T> inline
void PRCurve<T>::compute(size_t steeps)
{

  T min = this->mData.front().first;
  T max = this->mData.back().first;

  T step = (max - min) / static_cast<double>(steeps);

  T threshold = min;

  for (size_t i = 0; i < steeps; i++) {

    std::map<typename PRCurve<T>::Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);

    double recall = truePositiveRate(confussionMatrix[PRCurve<T>::Classification::tp], this->mPositives);
    double precision = positivePredictiveValue(confussionMatrix[PRCurve<T>::Classification::tp],
                                               confussionMatrix[PRCurve<T>::Classification::tp] + confussionMatrix[PRCurve<T>::Classification::fp]);
    this->mCurve.push_back(QPointF(recall, 1-precision));
    threshold += step;
  }

  /// AUC
  size_t size = this->mCurve.size();
  this->mAuc = 0.0;

  if (size > 2) {
    QPointF point1 = this->mCurve[0];
    QPointF point2;

    for(size_t i = 1; i < size; i++){
      point2 = this->mCurve[i];
      this->mAuc += sqrt(pow( (1-point1.x() + 1-point2.x()) / 2. * (point1.y() - point2.y()), 2));
      point1 = point2;
    }
  }

}



/*------------------------------------------------------------------------------------*/


/* ROC Curve class implementation */


template<typename T>
ROCCurve<T>::ROCCurve(const std::vector<std::pair<T, int>> &data, size_t steeps)
  : Curve<T>(data)
{
  this->compute(steeps);
}

///TODO: para enteros habria que especializar la plantilla
template<typename T> inline
void ROCCurve<T>::compute(size_t steeps)
{

  T min = this->mData.front().first;
  T max = this->mData.back().first;

  T step = (max - min) / static_cast<double>(steeps);

  T threshold = min;
  for (int i = 0; i < steeps; i++) {

    std::map<typename PRCurve<T>::Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
    double fpr = falsePositiveRate(confussionMatrix[PRCurve<T>::Classification::fp], this->mNegatives);
    double tpr = truePositiveRate(confussionMatrix[PRCurve<T>::Classification::tp], this->mPositives);
    this->mCurve.push_back(QPointF(fpr, tpr));
    threshold += step;
  }

  /// AUC
  size_t size = this->mCurve.size();
  this->mAuc = 0.0;

  if (size > 2) {
    QPointF point1 = this->mCurve[0];
    QPointF point2;

    for(size_t i = 1; i < size; i++){
      point2 = this->mCurve[i];
      this->mAuc += sqrt(pow( (1-point1.x() + 1-point2.x()) / 2. * (point1.y() - point2.y()), 2));
      point1 = point2;
    }
  }

}

/*------------------------------------------------------------------------------------*/


/* DET Curve class implementation */

template<typename T>
DETCurve<T>::DETCurve(const std::vector<std::pair<T, int>> &data, size_t steeps)
  : Curve<T>(data)
{
  this->compute(steeps);
}

///TODO: para enteros habria que especializar la plantilla
template<typename T> inline
void DETCurve<T>::compute(size_t steeps)
{

  T min = this->mData.front().first;
  T max = this->mData.back().first;

  T step = (max - min) / static_cast<double>(steeps);

  T threshold = min;
  for (int i = 0; i < steeps; i++) {

    std::map<typename DETCurve<T>::Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
    double fpr = falsePositiveRate(confussionMatrix[DETCurve<T>::Classification::fp], this->mNegatives);
    double fnr = falseNegativeRate(confussionMatrix[DETCurve<T>::Classification::fn], this->mPositives);
    this->mCurve.push_back(QPointF(fpr, fnr));
    threshold += step;
  }

  /// AUC
  size_t size = this->mCurve.size();
  this->mAuc = 0.0;

  if (size > 2) {
    QPointF point1 = this->mCurve[0];
    QPointF point2;

    for(size_t i = 1; i < size; i++){
      point2 = this->mCurve[i];
      this->mAuc += sqrt(pow( (1-point1.x() + 1-point2.x()) / 2. * (point1.y() - point2.y()), 2));
      point1 = point2;
    }
  }
}


} // namespace fme


#endif // EVALUATION_H
