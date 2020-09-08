/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#ifndef PHOTOMATCH_MSER_DETECTOR_H
#define PHOTOMATCH_MSER_DETECTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <QString>

namespace photomatch
{



class PHOTOMATCH_EXPORT MserProperties
  : public Mser
{
public:

  MserProperties();
  MserProperties(const MserProperties &mserProperties);
  ~MserProperties() override = default;

// Mser interface

public:

  int delta() const override;
  int minArea() const override;
  int maxArea() const override;
  double maxVariation() const override;
  double minDiversity() const override;
  int maxEvolution() const override;
  double areaThreshold() const override;
  double minMargin() const override;
  int edgeBlurSize() const override;
  void setDelta(int delta) override;
  void setMinArea(int minArea) override;
  void setMaxArea(int maxArea) override;
  void setMaxVariation(double maxVariation) override;
  void setMinDiversity(double minDiversity) override;
  void setMaxEvolution(int maxEvolution) override;
  void setAreaThreshold(double areaThreshold) override;
  void setMinMargin(double minMargin) override;
  void setEdgeBlurSize(int edgeBlurSize) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  int mDelta;
  int mMinArea;
  int mMaxArea;
  double mMaxVariation;
  double mMinDiversity;
  int mMaxEvolution;
  double mAreaThreshold;
  double mMinMargin;
  int mEdgeBlurSize;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT MserDetector
  : public MserProperties,
    public KeypointDetector
{

public:

  MserDetector();
  MserDetector(const MserDetector &mserDetector);
  MserDetector(int delta,
               int minArea,
               int maxArea,
               double maxVariation,
               double minDiversity,
               int maxEvolution,
               double areaThreshold,
               double minMargin,
               int edgeBlurSize);
  ~MserDetector() override = default;

private:

  void update();

// KeypointDetector interface

public:

  std::vector<cv::KeyPoint> detect(const cv::Mat &img,
                                   const cv::Mat &mask = cv::Mat()) override;

// Mser interface

public:

  void setDelta(int delta) override;
  void setMinArea(int minArea) override;
  void setMaxArea(int maxArea) override;
  void setMaxVariation(double maxVariation) override;
  void setMinDiversity(double minDiversity) override;
  void setMaxEvolution(int maxEvolution) override;
  void setAreaThreshold(double areaThreshold) override;
  void setMinMargin(double minMargin) override;
  void setEdgeBlurSize(int edgeBlurSize) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::MSER> mMSER;

};


} // namespace photomatch

#endif // PHOTOMATCH_MSER_DETECTOR_H
