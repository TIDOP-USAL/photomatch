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
   ~MserProperties() override;

// IMser interface

public:

  virtual int delta() const override;
  virtual int minArea() const override;
  virtual int maxArea() const override;
  virtual double maxVariation() const override;
  virtual double minDiversity() const override;
  virtual int maxEvolution() const override;
  virtual double areaThreshold() const override;
  virtual double minMargin() const override;
  virtual int edgeBlurSize() const override;
  virtual void setDelta(int delta) override;
  virtual void setMinArea(int minArea) override;
  virtual void setMaxArea(int maxArea) override;
  virtual void setMaxVariation(double maxVariation) override;
  virtual void setMinDiversity(double minDiversity) override;
  virtual void setMaxEvolution(int maxEvolution) override;
  virtual void setAreaThreshold(double areaThreshold) override;
  virtual void setMinMargin(double minMargin) override;
  virtual void setEdgeBlurSize(int edgeBlurSize) override;

// Feature interface

public:

  virtual void reset() override;
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


class MserDetector
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
  ~MserDetector() override;

private:

  void update();

// KeypointDetector interface

public:

  bool detect(const cv::Mat &img,
              std::vector<cv::KeyPoint> &keyPoints,
              cv::InputArray &mask = cv::noArray()) override;

// IFast interface

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
