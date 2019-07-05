#include "SettingsModel.h"

#include <QDir>
#include <QSettings>
#include <QLocale>
#include <QApplication>

namespace fme
{

SettingsModel::SettingsModel(ISettings *settings,
                             ISettingsRW *settingsRW,
                             QObject *parent)
  : ISettingsModel(parent),
    mSettings(settings),
    mSettingsRW(settingsRW)
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
  emit unsavedChanges(true);
}

double SettingsModel::surfHessianThreshold() const
{
  return mSettings->surf()->hessianThreshold();
}

int SettingsModel::surfOctaves() const
{
  return mSettings->surf()->octaves();
}

int SettingsModel::surfOctaveLayers() const
{
  return mSettings->surf()->octaveLayers();
}

bool SettingsModel::surfExtendedDescriptor() const
{
  return mSettings->surf()->extendedDescriptor();
}

bool SettingsModel::surfRotatedFeatures() const
{
  return mSettings->surf()->rotatedFeatures();
}

int SettingsModel::siftFeaturesNumber() const
{
  return mSettings->sift()->featuresNumber();
}

int SettingsModel::siftOctaveLayers() const
{
  return mSettings->sift()->octaveLayers();
}

double SettingsModel::siftContrastThreshold()
{
  return mSettings->sift()->contrastThreshold();
}

double SettingsModel::siftEdgeThreshold()
{
  return mSettings->sift()->edgeThreshold();
}

double SettingsModel::siftSigma()
{
  return mSettings->sift()->sigma();
}

void SettingsModel::setSurfHessianThreshold(double hessianThreshold)
{
  mSettings->surf()->setHessianThreshold(hessianThreshold);
  emit unsavedChanges(true);
}

void SettingsModel::setSurfOctaves(int octaves)
{
  mSettings->surf()->setOctaves(octaves);
  emit unsavedChanges(true);
}

void SettingsModel::setSurfOctaveLayers(int octaveLayers)
{
  mSettings->surf()->setOctaveLayers(octaveLayers);
  emit unsavedChanges(true);
}

void SettingsModel::setSurfExtendedDescriptor(bool extendedDescriptor)
{
  mSettings->surf()->setExtendedDescriptor(extendedDescriptor);
  emit unsavedChanges(true);
}

void SettingsModel::setSurfRotatedFeatures(bool rotatedFeatures)
{
  mSettings->surf()->setRotatedFeatures(rotatedFeatures);
  emit unsavedChanges(true);
}

void SettingsModel::setSiftFeaturesNumber(int featuresNumber)
{
  mSettings->sift()->setSigma(featuresNumber);
  emit unsavedChanges(true);
}

void SettingsModel::setSiftOctaveLayers(int octaveLayers)
{
  mSettings->sift()->setOctaveLayers(octaveLayers);
  emit unsavedChanges(true);
}

void SettingsModel::setSiftContrastThreshold(double contrastThreshold)
{
  mSettings->sift()->setContrastThreshold(contrastThreshold);
  emit unsavedChanges(true);
}

void SettingsModel::setSiftEdgeThreshold(double edgeThreshold)
{
  mSettings->sift()->setEdgeThreshold(edgeThreshold);
  emit unsavedChanges(true);
}

void SettingsModel::setSiftSigma(double sigma)
{
  mSettings->sift()->setSigma(sigma);
  emit unsavedChanges(true);
}

void SettingsModel::reset()
{
  mSettings->reset();
  emit unsavedChanges(false);
}

void SettingsModel::init()
{
}

QStringList SettingsModel::languages() const
{
  QString langPath = QApplication::applicationDirPath();
  langPath.append("/translations");

  QStringList lang_list = QDir(langPath).entryList(QStringList("fme_*.qm"));
  if (lang_list.size() == 0)
    lang_list.push_back("fme_en.qm");
  return lang_list;
}

void SettingsModel::read()
{
  mSettingsRW->read(*mSettings);
}

void SettingsModel::write()
{
  mSettingsRW->write(*mSettings);
  emit unsavedChanges(false);
}

//bool SettingsModel::checkUnsavedChanges() const
//{
//  return bUnsavedChanges;
//}

} // namespace fme
