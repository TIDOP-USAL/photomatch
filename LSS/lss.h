#ifndef LSS_H
#define LSS_H
#include "opencv/cv.hpp"

class LSS
{
public:

      int compute( const cv::Point& p, const cv::Mat& input,   cv::Mat_<float>& polar );

      float ssd(cv::Mat &a, cv::Mat &b );

      static const int idim = 5;
         static const int odim = 80;
         static const int radii_steps = 40;
         static const int angle_steps = 10;
         static const int varnoise = 1;

};

#endif // LSS_H
