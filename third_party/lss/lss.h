#ifndef FME_LSS_H
#define FME_LSS_H

#include <opencv2/core.hpp>

// ¿Es Local Self - Similarity????

class LSS
{
public:

  int compute(const cv::Point &p, const cv::Mat &input, cv::Mat_<float> &polar);

  float ssd(cv::Mat &a, cv::Mat &b);

  /// TODO: Ver si esto son parametros o constantes
  static const int idim = 5;
  static const int odim = 80;
  static const int radii_steps = 40;
  static const int angle_steps = 10;
  static const int varnoise = 1;

};

#endif // FME_LSS_H
