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

void Session::clear()
{
  mName.clear();
  mDescription.clear();
}

} // namespace fme
