#include "evaluation.h"


namespace fme
{

Curve::Curve(const std::vector<std::pair<double, int>> &data)
  : mData(data),
    mPositives(0),
    mNegatives(0)
{
  std::sort(mData.begin(), mData.end(),
            [](const std::pair<double, int> &data1,
               const std::pair<double, int> &data2){
    return data1.first < data2.first;});

  for(size_t i = 0; i < mData.size(); i++) {

    if (mData[i].second == 1){
      mPositives++;
    } else {
      mNegatives++;
    }

  }
}

std::map<Curve::Classification,size_t> Curve::confusionMatrix(double threshold) const
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

size_t Curve::positives() const
{
  return mPositives;
}

size_t Curve::negatives() const
{
  return mNegatives;
}

size_t Curve::truePositives(double threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  return confussionMatrix[Classification::tp];
}

size_t Curve::falsePositives(double threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  return confussionMatrix[Classification::fp];
}

size_t Curve::trueNegatives(double threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  return confussionMatrix[Classification::tn];
}

size_t Curve::falseNegatives(double threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  return confussionMatrix[Classification::fn];
}

double Curve::accuracy(double threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);

  return (mPositives + mNegatives) ?
    static_cast<double>(confussionMatrix[Classification::tp]+confussionMatrix[Classification::tn])
      / static_cast<double>(mPositives + mNegatives) : -1;
}

double Curve::positivePredictiveValue(double threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  double tp = confussionMatrix[Classification::tp];
  double fp = confussionMatrix[Classification::fp];
  return ( (tp + fp) > 0.) ? tp / (tp + fp) : -1;
}

double Curve::negativePredictiveValue(double threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  double fn = confussionMatrix[Classification::fn];
  double tn = confussionMatrix[Classification::tn];
  return (fn + tn > 0.) ? tn / (fn + tn) : -1;
}

double Curve::truePositiveRate(double threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  double tp = confussionMatrix[Classification::tp];
  return mPositives ? tp / static_cast<double>(mPositives) : -1;
}

double Curve::falsePositiveRate(double threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  double fp = confussionMatrix[Classification::fp];
  return mNegatives ? static_cast<double>(fp) / static_cast<double>(mNegatives) : -1;
}

double Curve::trueNegativeRate(double threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  double tn = confussionMatrix[Classification::tn];
  return mNegatives ? static_cast<double>(tn) / static_cast<double>(mNegatives) : -1;
}

double Curve::falseNegativeRate(double threshold) const
{
  std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
  double fn = confussionMatrix[Classification::fn];
  return mPositives ? static_cast<double>(fn) / static_cast<double>(mPositives) : -1;
}

double Curve::truePositiveRate(size_t tp, size_t positives)
{
  return positives ? static_cast<double>(tp) / static_cast<double>(positives) : -1;
}

double Curve::falsePositiveRate(size_t fp, size_t negatives)
{
  return negatives ? static_cast<double>(fp) / static_cast<double>(negatives) : -1;
}

double Curve::trueNegativeRate(size_t tn, size_t negatives)
{
  return negatives ? static_cast<double>(tn) / static_cast<double>(negatives) : -1;
}

double Curve::falseNegativeRate(size_t fn, size_t positives)
{
  return positives ? static_cast<double>(fn) / static_cast<double>(positives) : -1;
}

double Curve::positivePredictiveValue(size_t tp, size_t fp)
{
  return ( (tp + fp) > 0.) ? tp / (tp + fp) : -1;
}

double Curve::negativePredictiveValue(size_t fn, size_t tn)
{
  return (fn + tn > 0.) ? tn / (fn + tn) : -1;
}

double Curve::accuracy(size_t tp, size_t tn, size_t positives, size_t negatives)
{

  return (positives + negatives) ?
    static_cast<double>(tp+tn)
      / static_cast<double>(positives + negatives) : -1;
}

PRCurve::PRCurve(const std::vector<std::pair<double, int>> &data)
  : Curve(data)
{
}

std::vector<QPointF> PRCurve::compute()
{
  std::vector<QPointF> precisionRecallCurve(mData.size());

  double min = mData.front().first;
  double max = mData.back().first;

  double step = (max - min) / 100.;

  double threshold = min;

  for (int i = 0; i < 100; i++) {

    std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);

    double recall = truePositiveRate(confussionMatrix[Classification::tp], mPositives);
    double precision = positivePredictiveValue(confussionMatrix[Classification::tp], confussionMatrix[Classification::fp]);
    precisionRecallCurve.push_back(QPointF(recall, precision));
    threshold += step;
  }

  return precisionRecallCurve;
}



ROCCurve::ROCCurve(const std::vector<std::pair<double, int>>& data)
  : Curve(data)
{
}

std::vector<QPointF> ROCCurve::compute()
{
  std::vector<QPointF> rocCurve;

  double min = mData.front().first;
  double max = mData.back().first;

  double step = (max - min) / 100.;

  double threshold = min;
  for (int i = 0; i < 100; i++) {

    std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
    double fpr = falsePositiveRate(confussionMatrix[Classification::fp], mNegatives);
    double tpr = truePositiveRate(confussionMatrix[Classification::tp], mPositives);
    rocCurve.push_back(QPointF(fpr, tpr));
    threshold += step;
  }

  return rocCurve;
}



DETCurve::DETCurve(const std::vector<std::pair<double, int>>& data)
  : Curve(data)
{
}

std::vector<QPointF> DETCurve::compute()
{
  std::vector<QPointF> detCurve;

  double min = mData.front().first;
  double max = mData.back().first;

  double step = (max - min) / 100.;

  double threshold = min;
  for (int i = 0; i < 100; i++) {

    std::map<Classification,size_t> confussionMatrix = this->confusionMatrix(threshold);
    double fpr = falsePositiveRate(confussionMatrix[Classification::fp], mNegatives);
    double fnr = falseNegativeRate(confussionMatrix[Classification::fn], mPositives);
    detCurve.push_back(QPointF(fpr, fnr));
    threshold += step;
  }

  return detCurve;
}



//PRCurve::PRCurve(const std::vector<std::pair<ConfusionMatrix::Classification, double> > &data)
//  : ConfusionMatrix(data)
//{}
//
//std::vector<QPointF> PRCurve::compute()
//{
//  std::vector<QPointF> precisionRecallCurve(mData.size());
//
//  int tp = 0, fp = 0, tn = 0, fn = 0;
//  for(size_t i = 0; i < mData.size(); i++ ) {
//    if (mData[i].first == Classification::tp)
//      tp++;
//    else if (mData[i].first == Classification::fp)
//      fp++;
//    else if (mData[i].first == Classification::tn)
//      tn++;
//    else if (mData[i].first == Classification::fn)
//      fn++;
//
//    double precision = (tp + fp) ? tp / (tp + fp) : -1;
//    double recall = this->truePositiveRate(tp);
//    precisionRecallCurve[i] = QPointF(precision, recall);
//  }
//
//  return precisionRecallCurve;
//}
//
//


//void computePRCurve(const std::vector<std::vector<cv::DMatch>> &matches1to2,
//                    const std::vector<std::vector<uchar>> &correctMatches1to2Mask,
//                    std::vector<QPointF> &recallPrecisionCurve)
//{
//  std::vector<cv::Point2f> rpc;
//  cv::computeRecallPrecisionCurve(matches1to2, correctMatches1to2Mask, rpc);
//
//  for (auto &point : rpc){
//    recallPrecisionCurve.push_back(QPointF(static_cast<double>(point.y),
//                                           1.-static_cast<double>(point.x)));
//  }
//}

//void computePRCurve(const std::vector<cv::DMatch> &matches1to2,
//                    const std::vector<uchar> &correctMatches1to2Mask,
//                    std::vector<QPointF> &recallPrecisionCurve)
//{
//  std::vector<cv::Point2f> rpc;
//  std::vector<std::vector<cv::DMatch>> m1to2;
//  m1to2.push_back(matches1to2);
//  std::vector<std::vector<uchar>> cm1to2;
//  cm1to2.push_back(correctMatches1to2Mask);
//  cv::computeRecallPrecisionCurve(m1to2, cm1to2, rpc);
//
//  for (auto &point : rpc){
//    recallPrecisionCurve.push_back(QPointF(static_cast<double>(point.y),
//                                           1.-static_cast<double>(point.x)));
//  }
//}

//
///// Es privada en OpenCV así que se copia aquí
//struct DMatchForEvaluation : public cv::DMatch
//{
//    MatchClass classification;
//    DMatchForEvaluation( const DMatch &dm ) : DMatch( dm ), classification(MatchClass::tp) {}
//};
//



} // namespace fme
