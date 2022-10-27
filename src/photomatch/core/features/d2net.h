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


#ifndef PHOTOMATCH_D2_NET_DETECTOR_DESCRIPTOR_H
#define PHOTOMATCH_D2_NET_DETECTOR_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT D2NetProperties
  : public D2Net
{

public:

  D2NetProperties();
  D2NetProperties(const D2NetProperties &d2netProperties);
  ~D2NetProperties() override = default;

// D2Net interface

public:

  bool multiscale() const override;
  void setMultiscale(bool multiscale) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  bool mMultiscale;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT D2NetDetectorDescriptor
  : public D2NetProperties,
    public FeatureExtractorPython
{

public:

  D2NetDetectorDescriptor();
  D2NetDetectorDescriptor(const D2NetDetectorDescriptor &d2NetDetectorDescriptor);
  D2NetDetectorDescriptor(bool multiscale);

  ~D2NetDetectorDescriptor() override = default;

// FeatureExtractorPython interface

public:

  void extract(const QString &imagePath,
               const QString &featuresPath) override;

// Feature interface

public:

  void reset() override;


};

} // namespace photomatch

#endif // PHOTOMATCH_D2_NET_DETECTOR_DESCRIPTOR_H
