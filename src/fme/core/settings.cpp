#include "settings.h"

#include <QSettings>
#include <QLocale>

namespace fme
{

Settings::Settings()
  : ISettings()
{
  reset();
}

QString Settings::language() const
{
  return mLanguage;
}

void Settings::setLanguage(const QString &language)
{
  mLanguage = language;
}

void Settings::reset()
{
  mLanguage = "en";
}



SettingsRW::SettingsRW()
  : ISettingsRW(),
    mSettingsRW(nullptr)
{
  mSettingsRW = new QSettings(QSettings::IniFormat, QSettings::UserScope, "TIDOP", "FME");
}

SettingsRW::~SettingsRW()
{
  if (mSettingsRW){
    delete mSettingsRW;
    mSettingsRW = nullptr;
  }
}

void SettingsRW::read(ISettings &settings)
{
  QString lang = QLocale::system().name();
  lang.truncate(lang.lastIndexOf('_'));
  settings.setLanguage(mSettingsRW->value("lang", lang).toString());
}

void SettingsRW::write(const ISettings &settings)
{
  mSettingsRW->setValue("lang", settings.language());
}

} // namespace fme
