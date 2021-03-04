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


#include "mser.h"

#include <tidop/core/messages.h>


namespace photomatch
{


MserProperties::MserProperties()
  : mDelta(5),
    mMinArea(60),
    mMaxArea(14400),
    mMaxVariation(0.25),
    mMinDiversity(0.2),
    mMaxEvolution(200),
    mAreaThreshold(1.01),
    mMinMargin(0.003),
    mEdgeBlurSize(5)
{
}

MserProperties::MserProperties(const MserProperties &mserProperties)
  : Mser(mserProperties),
    mDelta(mserProperties.mDelta),
    mMinArea(mserProperties.minArea()),
    mMaxArea(mserProperties.mMaxArea),
    mMaxVariation(mserProperties.mMaxVariation),
    mMinDiversity(mserProperties.mMinDiversity),
    mMaxEvolution(mserProperties.mMaxEvolution),
    mAreaThreshold(mserProperties.mAreaThreshold),
    mMinMargin(mserProperties.mMinMargin),
    mEdgeBlurSize(mserProperties.mEdgeBlurSize)
{
}

int MserProperties::delta() const
{
  return mDelta;
}

int MserProperties::minArea() const
{
  return mMinArea;
}

int MserProperties::maxArea() const
{
  return mMaxArea;
}

double MserProperties::maxVariation() const
{
  return mMaxVariation;
}

double MserProperties::minDiversity() const
{
  return mMinDiversity;
}

int MserProperties::maxEvolution() const
{
  return mMaxEvolution;
}

double MserProperties::areaThreshold() const
{
  return mAreaThreshold;
}

double MserProperties::minMargin() const
{
  return mMinMargin;
}

int MserProperties::edgeBlurSize() const
{
  return mEdgeBlurSize;
}

void MserProperties::setDelta(int delta)
{
  mDelta = delta;
}

void MserProperties::setMinArea(int minArea)
{
  mMinArea = minArea;
}

void MserProperties::setMaxArea(int maxArea)
{
  mMaxArea = maxArea;
}

void MserProperties::setMaxVariation(double maxVariation)
{
  mMaxVariation = maxVariation;
}

void MserProperties::setMinDiversity(double minDiversity)
{
  mMinDiversity = minDiversity;
}

void MserProperties::setMaxEvolution(int maxEvolution)
{
  mMaxEvolution = maxEvolution;
}

void MserProperties::setAreaThreshold(double areaThreshold)
{
  mAreaThreshold = areaThreshold;
}

void MserProperties::setMinMargin(double minMargin)
{
  mMinMargin = minMargin;
}

void MserProperties::setEdgeBlurSize(int edgeBlurSize)
{
  mEdgeBlurSize = edgeBlurSize;
}

void MserProperties::reset()
{
  mDelta = 5;
  mMinArea = 60;
  mMaxArea = 14400;
  mMaxVariation = 0.25;
  mMinDiversity = .2;
  mMaxEvolution = 200;
  mAreaThreshold = 1.01;
  mMinMargin = 0.003;
  mEdgeBlurSize = 5;
}

QString MserProperties::name() const
{
  return QString("MSER");
}


/*----------------------------------------------------------------*/


MserDetector::MserDetector()
{
  update();
}

MserDetector::MserDetector(const MserDetector &mserDetector)
  : MserProperties(mserDetector),
    KeypointDetector(mserDetector)
{
  update();
}

MserDetector::MserDetector(int delta,
                           int minArea,
                           int maxArea,
                           double maxVariation,
                           double minDiversity,
                           int maxEvolution,
                           double areaThreshold,
                           double minMargin,
                           int edgeBlurSize)
{
  MserProperties::setDelta(delta);
  MserProperties::setMinArea(minArea);
  MserProperties::setMaxArea(maxArea);
  MserProperties::setMaxVariation(maxVariation);
  MserProperties::setMinDiversity(minDiversity);
  MserProperties::setMaxEvolution(maxEvolution);
  MserProperties::setAreaThreshold(areaThreshold);
  MserProperties::setMinMargin(minMargin);
  MserProperties::setEdgeBlurSize(edgeBlurSize);
  update();
}

void MserDetector::update()
{
  mMSER = cv::MSER::create(MserProperties::delta(),
                           MserProperties::minArea(),
                           MserProperties::maxArea(),
                           MserProperties::maxVariation(),
                           MserProperties::minDiversity(),
                           MserProperties::maxEvolution(),
                           MserProperties::areaThreshold(),
                           MserProperties::minMargin(),
                           MserProperties::edgeBlurSize());
}

std::vector<cv::KeyPoint> MserDetector::detect(const cv::Mat &img, 
                                               const cv::Mat &mask)
{
  std::vector<cv::KeyPoint> keyPoints;
  mMSER->detect(img, keyPoints, mask);
  return keyPoints;
}

void MserDetector::setDelta(int delta)
{
  MserProperties::setDelta(delta);
  mMSER->setDelta(delta);
}

void MserDetector::setMinArea(int minArea)
{
  MserProperties::setMinArea(minArea);
  mMSER->setMinArea(minArea);
}

void MserDetector::setMaxArea(int maxArea)
{
  MserProperties::setMaxArea(maxArea);
  mMSER->setMaxArea(maxArea);
}

void MserDetector::setMaxVariation(double maxVariation)
{
  MserProperties::setMaxVariation(maxVariation);
  update();
}

void MserDetector::setMinDiversity(double minDiversity)
{
  MserProperties::setMinDiversity(minDiversity);
  update();
}

void MserDetector::setMaxEvolution(int maxEvolution)
{
  MserProperties::setMaxEvolution(maxEvolution);
  update();
}

void MserDetector::setAreaThreshold(double areaThreshold)
{
  MserProperties::setAreaThreshold(areaThreshold);
  update();
}

void MserDetector::setMinMargin(double minMargin)
{
  MserProperties::setMinMargin(minMargin);
  update();
}

void MserDetector::setEdgeBlurSize(int edgeBlurSize)
{
  MserProperties::setEdgeBlurSize(edgeBlurSize);
  update();
}

void MserDetector::reset()
{
  MserProperties::reset();
  update();
}


} // namespace photomatch
