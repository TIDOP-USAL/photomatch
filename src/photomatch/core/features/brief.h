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


#ifndef PHOTOMATCH_BRIEF_DESCRIPTOR_H
#define PHOTOMATCH_BRIEF_DESCRIPTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <opencv2/xfeatures2d.hpp>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT BriefProperties
  : public Brief
{
public:

  BriefProperties();
  BriefProperties(const BriefProperties &briefProperties);
  ~BriefProperties() override = default;

// Brief interface

public:

  QString bytes() const override;
  bool useOrientation() const override;
  void setBytes(const QString &bytes) override;
  void setUseOrientation(bool useOrientation) override;

// Feature interface

public:

  void reset() override;
  QString name() const final;

private:

  QString mBytes;
  bool mUseOrientation;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT BriefDescriptor
    : public BriefProperties,
      public DescriptorExtractor
{

public:

  BriefDescriptor();
  BriefDescriptor(const BriefDescriptor &briefDescriptor);
  BriefDescriptor(QString bytes,
                  bool useOrientation);
  ~BriefDescriptor() override = default;

private:

  void update();

// DescriptorExtractor interface

public:

  bool extract(const cv::Mat &img,
               std::vector<cv::KeyPoint> &keyPoints,
               cv::Mat &descriptors) override;


// Brief interface

public:

  void setBytes(const QString &bytes) override;
  void setUseOrientation(bool useOrientation) override;

// Feature interface

public:

  void reset() override;

protected:

  cv::Ptr<cv::xfeatures2d::BriefDescriptorExtractor> mBrief;
};


} // namespace photomatch

#endif // PHOTOMATCH_BRIEF_DESCRIPTOR_H
