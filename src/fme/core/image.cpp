#include "image.h"

#include <QFileInfo>

namespace fme
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
    mLongitudeExif(std::move(image.mLongitudeExif)),
    mLatitudeExif(std::move(image.mLatitudeExif)),
    mAltitudeExif(std::move(image.mAltitudeExif))
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
    this->mLongitudeExif = std::move(image.mLongitudeExif);
    this->mLatitudeExif = std::move(image.mLatitudeExif);
    this->mAltitudeExif = std::move(image.mAltitudeExif);
  }
  return *this;
}

void Image::update()
{
  QFileInfo file_info(mFilePath);
  mName = file_info.baseName();
}

} // namespace fme
