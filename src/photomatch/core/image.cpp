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


#include "image.h"

#include <QFileInfo>

namespace photomatch
{

Image::Image()
  : mFilePath(""),
    mName(""),
    mLongitudeExif(0.0),
    mLatitudeExif(0.0),
    mAltitudeExif(0.0)
{
}

Image::Image(const QString &file)
  : mFilePath(file),
    mLongitudeExif(0.0),
    mLatitudeExif(0.0),
    mAltitudeExif(0.0)
{
  update();
}

Image::Image(const Image &image)
  : mFilePath(image.mFilePath),
    mName(image.mName),
    mLongitudeExif(image.mLongitudeExif),
    mLatitudeExif(image.mLatitudeExif),
    mAltitudeExif(image.mAltitudeExif)
{

}

Image::Image(Image &&image) noexcept
  : mFilePath(std::move(image.mFilePath)),
    mName(std::move(image.mName)),
    mLongitudeExif(image.mLongitudeExif),
    mLatitudeExif(image.mLatitudeExif),
    mAltitudeExif(image.mAltitudeExif)
{
  /// reset move object
  image.mFilePath = "";
  image.mName = "";
  image.mLongitudeExif = 0.;
  image.mLatitudeExif = 0.;
  image.mAltitudeExif = 0.;
}

QString Image::path() const
{
  return mFilePath;
}

void Image::setPath(const QString &file)
{
  mFilePath = file;
  update();
}

QString Image::name() const
{
  return mName;
}

double Image::longitudeExif() const
{
  return mLongitudeExif;
}

void Image::setLongitudeExif(double longitudeExif)
{
  mLongitudeExif = longitudeExif;
}

double Image::latitudeExif() const
{
  return mLatitudeExif;
}

void Image::setLatitudeExif(double latitudeExif)
{
  mLatitudeExif = latitudeExif;
}

double Image::altitudeExif() const
{
  return mAltitudeExif;
}

void Image::setAltitudeExif(double altitudeExif)
{
  mAltitudeExif = altitudeExif;
}

Image &Image::operator =(const Image &image)
{
  if (this != &image){
    this->mFilePath = image.mFilePath;
    this->mName = image.mName;
    this->mLongitudeExif = image.mLongitudeExif;
    this->mLatitudeExif = image.mLatitudeExif;
    this->mAltitudeExif = image.mAltitudeExif;
  }
  return *this;
}

Image &Image::operator =(Image &&image) noexcept
{
  if (this != &image){
    this->mFilePath = std::move(image.mFilePath);
    this->mName = std::move(image.mName);
    this->mLongitudeExif = image.mLongitudeExif;
    this->mLatitudeExif = image.mLatitudeExif;
    this->mAltitudeExif = image.mAltitudeExif;
  }
  return *this;
}

void Image::update()
{
  QFileInfo file_info(mFilePath);
  mName = file_info.baseName();
}

} // namespace photomatch
