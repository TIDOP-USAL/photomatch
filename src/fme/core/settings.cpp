#include "settings.h"

namespace fme
{

Settings::Settings()
  : ISettings(),
    mLanguage("")
{

}

QString Settings::language() const
{
  return mLanguage;
}

void Settings::setLanguage(const QString &language)
{
  mLanguage = language;
}

} // namespace fme
