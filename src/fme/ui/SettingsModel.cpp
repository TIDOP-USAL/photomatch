#include "SettingsModel.h"

#include <QDir>
#include <QSettings>
#include <QLocale>

namespace fme
{

SettingsModel::SettingsModel(ISettings *settings, QObject *parent)
  : ISettingsModel(parent),
    mSettings(settings),
    mSettingsRW(nullptr),
    bUnsavedChanges(false)
{
  init();
}

SettingsModel::~SettingsModel()
{
  if (mSettingsRW){
    delete mSettingsRW;
    mSettingsRW = nullptr;
  }
}

QString SettingsModel::language() const
{
  return mSettings->language();
}

void SettingsModel::setLanguage(const QString &language)
{
  mSettings->setLanguage(language);
  bUnsavedChanges = true;
}

void SettingsModel::init()
{
  mSettingsRW = new QSettings(QSettings::IniFormat, QSettings::UserScope, "TIDOP", "FME");

  read();
}

void SettingsModel::read()
{
  QString lang = QLocale::system().name();
  lang.truncate(lang.lastIndexOf('_'));
  mSettings->setLanguage(mSettingsRW->value("lang", lang).toString());
}

void SettingsModel::write()
{
  mSettingsRW->setValue("lang", mSettings->language());

  bUnsavedChanges = false;
}

} // namespace fme

