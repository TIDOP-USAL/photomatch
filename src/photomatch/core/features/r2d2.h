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


#ifndef PHOTOMATCH_R2_D2_DETECTOR_DESCRIPTOR_H
#define PHOTOMATCH_R2_D2_DETECTOR_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT R2D2Properties
  : public R2D2
{

public:

  R2D2Properties();
  R2D2Properties(const R2D2Properties &r2D2Properties);
  ~R2D2Properties() override = default;

// R2D2 interface

public:

  double scaleF() const override;
  void setScaleF(double scaleF) override;
  int minSize() const override;
  void setMinSize(int size) override;
  int maxSize() const override;
  void setMaxSize(int size) override;
  double minScale() const override;
  void setMinScale(double minScale) override;
  double maxScale() const override;
  void setMaxScale(double maxScale) override;
  double reliabilityThreshold() const override;
  void setReliabilityThreshold(double reliabilityThreshold) override;
  double repeatabilityThreshold() const override;
  void setRepeatabilityThreshold(double repeatabilityThreshold) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  double mScaleF;
  int mMinSize{256};
  int mMaxSize{1024};
  double mMinScale{0};
  double mMaxScale{1};
  double mReliabilityThreshold{0.7};
  double mRepeatabilityThreshold{0.7};


};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT R2D2DetectorDescriptor
  : public R2D2Properties,
    public FeatureExtractorPython
{

public:

  R2D2DetectorDescriptor();
  R2D2DetectorDescriptor(const R2D2DetectorDescriptor &r2D2DetectorDescriptor);
  R2D2DetectorDescriptor(double scaleF,
                         int minSize,
                         int maxSize,
                         double minScale,
                         double maxScale,
                         double reliabilityThreshold,
                         double repeatabilityThreshold);

  ~R2D2DetectorDescriptor() override = default;

// FeatureExtractorPython interface

public:

  void extract(const QString &imagePath,
               const QString &featuresPath) override;

// Feature interface

public:

  void reset() override;


};

} // namespace photomatch

#endif // PHOTOMATCH_R2_D2_DETECTOR_DESCRIPTOR_H
