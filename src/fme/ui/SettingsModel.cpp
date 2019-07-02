#include "SettingsModel.h"

#include <QDir>
#include <QSettings>
#include <QLocale>

namespace fme
{

SettingsModel::SettingsModel(ISettings *settings,
                             ISettingsRW *settingsRW,
                             QObject *parent)
  : ISettingsModel(parent),
    mSettings(settings),
    mSettingsRW(settingsRW),
    bUnsavedChanges(false)
{
  init();
}

SettingsModel::~SettingsModel()
{
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

void SettingsModel::reset()
{
  mSettings->reset();
  bUnsavedChanges = false;
}

void SettingsModel::init()
{
}

void SettingsModel::read()
{
  mSettingsRW->read(*mSettings);
}

void SettingsModel::write()
{
  mSettingsRW->write(*mSettings);
  bUnsavedChanges = false;
}

bool SettingsModel::checkUnsavedChanges() const
{
  return bUnsavedChanges;
}

} // namespace fme

