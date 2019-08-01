/*
Modificado para FME
*/


//This file is part of the MSD-Detector project (github.com/fedassa/msdDetector).
//
//The MSD-Detector is free software : you can redistribute it and / or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//The MSD-Detector is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with the MSD-Detector project.If not, see <http://www.gnu.org/licenses/>.
// 
// AUTHOR: Federico Tombari (fedassa@gmail.com)
// University of Bologna, Open Perception

#ifndef LSD_DETECTOR_H_
#define LSD_DETECTOR_H_

#include <vector>
#include "opencv/cv.hpp"

#include "MSDImgPyramid.h"


class MsdDetector
{
public:

  MsdDetector();

  std::vector<cv::KeyPoint> detect(cv::Mat &img);

  void setPatchRadius(int patchRadius);
  int getPatchRadius() const;

  void setSearchAreaRadius(int searchAreaRadius);
  int getSearchAreaRadius() const;

  void setNMSRadius(int nmsRadius);
  int getNMSRadius() const;

  void setNMSScaleRadius(int nmsScaleRadius);
  int getNMSScaleRadius() const;

  void setThSaliency(float thSaliency);
  float getThSaliency() const;

  void setKNN(int kNN);
  int getKNN() const;

  void setScaleFactor(float scaleFactor);
  float getScaleFactor() const;

  void setNScales(int nScales);
  int getNScales() const;

  void setComputeOrientation(bool computeOrientation);
  bool getComputeOrientation() const;

private:

  int m_patch_radius;
  int m_search_area_radius;

  int m_nms_radius;
  int m_nms_scale_radius;

  float m_th_saliency;
  int m_kNN;

  float m_scale_factor;
  int m_n_scales;
  int m_cur_n_scales;
  bool m_compute_orientation;

  std::vector<cv::Mat> m_scaleSpace;

  float computeAvgDistance(std::vector<int> &minVals, int den);

  void contextualSelfDissimilarity(const cv::Mat &img, int xmin, int xmax, float* saliency);

  float computeOrientation(const cv::Mat &img, int x, int y, const std::vector<cv::Point2f> &circle);

  void nonMaximaSuppression(std::vector<float *> & saliency, std::vector<cv::KeyPoint> & keypoints, std::vector<cv::Mat> &aux_des);

  void normalizepatch(int size, float angle, const cv::Mat &input, cv::Mat &output);
};





#endif
