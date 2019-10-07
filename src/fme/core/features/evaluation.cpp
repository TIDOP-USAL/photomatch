#include "evaluation.h"


namespace fme
{

void computePRCurve(const std::vector<std::vector<cv::DMatch>> &matches1to2,
                    const std::vector<std::vector<uchar>> &correctMatches1to2Mask,
                    std::vector<QPointF> &recallPrecisionCurve)
{
  std::vector<cv::Point2f> rpc;
  cv::computeRecallPrecisionCurve(matches1to2, correctMatches1to2Mask, rpc);

  for (auto &point : rpc){
    recallPrecisionCurve.push_back(QPointF(static_cast<double>(point.y),
                                           1.-static_cast<double>(point.x)));
  }
}

void computePRCurve(const std::vector<cv::DMatch> &matches1to2,
                    const std::vector<uchar> &correctMatches1to2Mask,
                    std::vector<QPointF> &recallPrecisionCurve)
{
  std::vector<cv::Point2f> rpc;
  std::vector<std::vector<cv::DMatch>> m1to2;
  m1to2.push_back(matches1to2);
  std::vector<std::vector<uchar>> cm1to2;
  cm1to2.push_back(correctMatches1to2Mask);
  cv::computeRecallPrecisionCurve(m1to2, cm1to2, rpc);

  for (auto &point : rpc){
    recallPrecisionCurve.push_back(QPointF(static_cast<double>(point.y),
                                           1.-static_cast<double>(point.x)));
  }
}


/// Es privada en OpenCV así que se copia aquí
struct DMatchForEvaluation : public cv::DMatch
{
    uchar isCorrect;
    DMatchForEvaluation( const DMatch &dm ) : DMatch( dm ), isCorrect(0) {}
};

void computeROCCurve(const std::vector<std::vector<cv::DMatch>> &matches1to2,
                     const std::vector<std::vector<uchar>> &correctMatches1to2Mask,
                     std::vector<QPointF> &rocCurve)
{

//  if (matches1to2.size() == correctMatches1to2Mask.size()) {

//    std::vector<DMatchForEvaluation> allMatches;
//    int correspondenceCount = 0;
//    for(size_t i = 0; i < matches1to2.size(); i++) {
//      for(size_t j = 0; j < matches1to2[i].size(); j++) {
//        DMatchForEvaluation match = matches1to2[i][j];
//        match.isCorrect = correctMatches1to2Mask[i][j];
//        allMatches.push_back( match );
//        correspondenceCount += match.isCorrect != 0 ? 1 : 0;
//      }
//    }

//    std::sort(allMatches.begin(), allMatches.end());

//    int correctMatchCount = 0, falseMatchCount = 0;
//    rocCurve.resize(allMatches.size());
//    for(size_t i = 0; i < allMatches.size(); i++ ) {
//      if( allMatches[i].isCorrect )
//        correctMatchCount++;
//      else
//        falseMatchCount++;

//      //float r = recall( correctMatchCount, correspondenceCount );
//      //Recall o True Positive Rate
//      float recall = correspondenceCount ? static_cast<float>(correctMatchCount) / static_cast<float>(correspondenceCount) : -1;
//      // False Positive Rate
//      float p =  precision( correctMatchCount, falseMatchCount );
//      rocCurve[i] = Point2f(1-p, recall);
//    }

//  }

}

void computeROCCurve(const std::vector<cv::DMatch> &matches1to2,
                     const std::vector<uchar> &correctMatches1to2Mask,
                     std::vector<QPointF> &rocCurve)
{
  std::vector<std::vector<cv::DMatch>> m1to2;
  m1to2.push_back(matches1to2);
  std::vector<std::vector<uchar>> cm1to2;
  cm1to2.push_back(correctMatches1to2Mask);
  //cv::computeRecallPrecisionCurve(m1to2, cm1to2, rpc);
  computeROCCurve(m1to2, cm1to2, rocCurve);

//  for (auto &point : rpc){
//    recallPrecisionCurve.push_back(QPointF(static_cast<double>(point.y),
//                                           1.-static_cast<double>(point.x)));
//  }
}


} // namespace fme
