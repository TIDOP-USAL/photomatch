#ifndef MTM_H
#define MTM_H

#include <vector>
#include "opencv/cv.hpp"


class mtm
{
public:
    mtm();

  int PWCp2w (cv::Mat patern,cv::Mat window,std::vector<int> steps,cv::Mat &output );
  int PWCw2p (cv::Mat patern,cv::Mat window,std::vector<int> steps,cv::Mat &output );
  int PWCmax (cv::Mat patern,cv::Mat window,std::vector<int> steps,cv::Mat &output );
  int PWLp2w (cv::Mat patern,cv::Mat window,std::vector<int> steps,cv::Mat &output );
  int PWLw2p (cv::Mat patern,cv::Mat window,std::vector<int> steps,cv::Mat &output );
  int PWLmax (cv::Mat patern,cv::Mat window,std::vector<int> steps,cv::Mat &output );
  void TDMA  (std::vector<cv::Mat> phi,std::vector<cv::Mat> psi,std::vector<cv::Mat> rho,std::vector<cv::Mat> &betha);


  ~mtm();
};

#endif // MTM_H


