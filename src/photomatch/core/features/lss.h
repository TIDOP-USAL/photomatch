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


#ifndef PHOTOMATCH_LSS_DESCRIPTOR_H
#define PHOTOMATCH_LSS_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include <memory>

#include <opencv2/xfeatures2d.hpp>

#include <QString>

#include "photomatch/core/features/features.h"
#include "lss/lss.h"

namespace photomatch
{



class PHOTOMATCH_EXPORT LssProperties
  : public Lss
{
public:

  LssProperties();
  ~LssProperties() override = default;

// Feature interface

public:

  void reset() override;
  QString name() const final;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT LssDescriptor
    : public LssProperties,
      public DescriptorExtractor
{

public:

  LssDescriptor();
  ~LssDescriptor() override = default;

private:

  void update();

// DescriptorExtractor interface

public:

  cv::Mat extract(const cv::Mat &img,
                  std::vector<cv::KeyPoint> &keyPoints) override;

// Feature interface

public:

  void reset() override;

protected:

  std::shared_ptr<LSS> mLSS;
};


} // namespace photomatch

#endif // PHOTOMATCH_LSS_DESCRIPTOR_H
