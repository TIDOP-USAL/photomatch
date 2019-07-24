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

void Session::clear()
{
  mName.clear();
  mDescription.clear();
}

} // namespace fme
