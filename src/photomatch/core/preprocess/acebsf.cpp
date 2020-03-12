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


#include "acebsf.h"

#include <tidop/core/messages.h>

#include "photomatch/core/utils.h"

#include <pixkit-image.hpp>

#include <opencv2/photo.hpp>

namespace photomatch
{


AcebsfProperties::AcebsfProperties()
  : Acebsf(),
    mBlockSize(8, 8),
    mL(0.03),
    mK1(10.),
    mK2(0.5)
{
}

AcebsfProperties::AcebsfProperties(const AcebsfProperties &acebsfProperties)
  : Acebsf(),
    mBlockSize(acebsfProperties.mBlockSize),
    mL(acebsfProperties.mL),
    mK1(acebsfProperties.mK1),
    mK2(acebsfProperties.mK2)
{
}

AcebsfProperties::AcebsfProperties(AcebsfProperties &&acebsfProperties) PHOTOMATCH_NOEXCEPT
  : Acebsf(),
    mBlockSize(std::move(acebsfProperties.mBlockSize)),
    mL(acebsfProperties.mL),
    mK1(acebsfProperties.mK1),
    mK2(acebsfProperties.mK2)
{
  acebsfProperties.mL = 0.;
  acebsfProperties.mK1 = 0.;
  acebsfProperties.mK2 = 0.;
}

AcebsfProperties &AcebsfProperties::operator=(const AcebsfProperties &acebsfProperties)
{
  if (this != &acebsfProperties) {  
    mBlockSize = acebsfProperties.mBlockSize;
    mL = acebsfProperties.mL;
    mK1 = acebsfProperties.mK1;
    mK2 = acebsfProperties.mK2;
  }
  return *this;
}

AcebsfProperties &AcebsfProperties::operator=(AcebsfProperties &&acebsfProperties) PHOTOMATCH_NOEXCEPT
{
  if (this != &acebsfProperties) {  
    mBlockSize = std::move(acebsfProperties.mBlockSize);
    mL = acebsfProperties.mL;
    mK1 = acebsfProperties.mK1;
    mK2 = acebsfProperties.mK2;
  }
  return *this;
}

QSize AcebsfProperties::blockSize() const
{
  return mBlockSize;
}

void AcebsfProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

double AcebsfProperties::l() const
{
  return mL;
}

void AcebsfProperties::setL(double l)
{
  mL = l;
}

double AcebsfProperties::k1() const
{
  return mK1;
}

void AcebsfProperties::setK1(double k1)
{
  mK1 = k1;
}

double AcebsfProperties::k2() const
{
  return mK2;
}

void AcebsfProperties::setK2(double k2)
{
  mK2 = k2;
}

void AcebsfProperties::reset()
{
  mBlockSize = QSize(8, 8);
  mL = 0.03;
  mK1 = 10.;
  mK2 = 0.5;
}


/*----------------------------------------------------------------*/


AcebsfPreprocess::AcebsfPreprocess()
  : AcebsfProperties(),
    ImageProcess()
{

}

AcebsfPreprocess::AcebsfPreprocess(const AcebsfPreprocess &acebsfPreprocess)
  : AcebsfProperties(acebsfPreprocess),
    ImageProcess()
{

}

AcebsfPreprocess::AcebsfPreprocess(AcebsfPreprocess &&acebsfPreprocess) PHOTOMATCH_NOEXCEPT
  : AcebsfProperties(std::forward<AcebsfProperties>(acebsfPreprocess)),
    ImageProcess()
{

}

AcebsfPreprocess::AcebsfPreprocess(const QSize &blockSize,
                                   double l, double k1, double k2)
  : AcebsfProperties(),
    ImageProcess()
{
  setBlockSize(blockSize);
  setL(l);
  setK1(k1);
  setK2(k2);
}

AcebsfPreprocess::~AcebsfPreprocess()
{

}

bool AcebsfPreprocess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{

  try {

    pixkit::enhancement::local::Lal2014(convertToGray(imgIn), imgOut,
                                        qSizeToCvSize(AcebsfProperties::blockSize()),
                                        static_cast<float>(AcebsfProperties::l()),
                                        static_cast<float>(AcebsfProperties::k1()),
                                        static_cast<float>(AcebsfProperties::k2()));

  } catch (cv::Exception &e) {
    msgError("ACEBSF Image preprocess error: %s", e.what());
    return true;
  }

  return false;
}

QString AcebsfProperties::name() const
{
  return QString("ACEBSF");
}

} // namespace photomatch



