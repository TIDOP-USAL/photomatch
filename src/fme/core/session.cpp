#include "session.h"

namespace fme
{

Session::Session()
  : ISession(),
    mName(""),
    mDescription(""),
    mMaxImageSize(2000)
{

}

Session::Session(const QString &name, const QString &description)
  : ISession(),
    mName(name),
    mDescription(description),
    mMaxImageSize(2000)
{

}

QString Session::name() const
{
  return mName;
}

void Session::setName(const QString &name)
{
  mName = name;
}

QString Session::description() const
{
  return mDescription;
}

void Session::setDescription(const QString &description)
{
  mDescription = description;
}

int Session::maxImageSize() const
{
  return mMaxImageSize;
}

void Session::setMaxImageSize(int size)
{
  mMaxImageSize = size;
}

void Session::setFullImageSize(bool fullImageSize)
{
  mMaxImageSize = fullImageSize ? -1 : 2000;
}

bool Session::fullImageSize() const
{
  return (mMaxImageSize == -1);
}

std::shared_ptr<Preprocess> Session::preprocess()
{
  return mPreprocess;
}

void Session::setPreprocess(const std::shared_ptr<Preprocess> &preprocess)
{
  mPreprocess = preprocess;
}

std::shared_ptr<Feature> Session::detector()
{
  return mFeatureDetector;
}

void Session::setDetector(const std::shared_ptr<Feature> &detector)
{
  mFeatureDetector = detector;
}

std::shared_ptr<Feature> Session::descriptor()
{
  return mFeatureDescriptor;
}

void Session::setDescriptor(const std::shared_ptr<Feature> &descriptor)
{
  mFeatureDescriptor = descriptor;
}

void Session::clear()
{
  mName.clear();
  mDescription.clear();
  mMaxImageSize = 2000;
}

} // namespace fme
