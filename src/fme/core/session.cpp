#include "session.h"

namespace fme
{

Session::Session()
  : ISession(),
    mName(""),
    mDescription("")
{

}

Session::Session(const QString &name, const QString &description)
  : ISession(),
    mName(name),
    mDescription(description)
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
}

} // namespace fme
