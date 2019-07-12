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

QStringList SettingsModel::history() const
{
  return mSettings->history();
}

int SettingsModel::historyMaxSize() const
{
  return mSettings->historyMaxSize();
}

QSize SettingsModel::faheBlockSize() const
{
  return mSettings->fahe()->blockSize();
}

int SettingsModel::agastThreshold() const
{
  return mSettings->agast()->threshold();
}

bool SettingsModel::agastNonmaxSuppression() const
{
  return mSettings->agast()->nonmaxSuppression();
}

QString SettingsModel::agastDetectorType() const
{
  return mSettings->agast()->detectorType();
}

QString SettingsModel::akazeDescriptorType() const
{
  return mSettings->akaze()->descriptorType();
}

int SettingsModel::akazeDescriptorSize() const
{
  return mSettings->akaze()->descriptorSize();
}

int SettingsModel::akazeDescriptorChannels() const
{
  return mSettings->akaze()->descriptorChannels();
}

double SettingsModel::akazeThreshold() const
{
  return mSettings->akaze()->threshold();
}

int SettingsModel::akazeOctaves() const
{
  return mSettings->akaze()->octaves();
}

int SettingsModel::akazeOctaveLayers() const
{
  return mSettings->akaze()->octaveLayers();
}

QString SettingsModel::akazeDiffusivity() const
{
  return mSettings->akaze()->diffusivity();
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

void SettingsModel::setLanguage(const QString &language)
{
  mSettings->setLanguage(language);
  emit unsavedChanges(true);
}

void SettingsModel::addToHistory(const QString &project)
{
  mSettings->addToHistory(project);
  mSettingsRW->writeHistory(*mSettings);
}

void SettingsModel::clearHistory()
{
  mSettings->clearHistory();
  mSettingsRW->writeHistory(*mSettings);
}

void SettingsModel::setHistoryMaxSize(int maxSize)
{
  mSettings->setHistoryMaxSize(maxSize);
  emit unsavedChanges(true);
}

void SettingsModel::setFaheBlockSize(const QSize &size)
{
  mSettings->fahe()->setBlockSize(size);
  emit unsavedChanges(true);
}

void SettingsModel::setAgastThreshold(int threshold)
{
  mSettings->agast()->setThreshold(threshold);
  emit unsavedChanges(true);
}

void SettingsModel::setAgastNonmaxSuppression(bool nonmaxSuppression)
{
  mSettings->agast()->setNonmaxSuppression(nonmaxSuppression);
  emit unsavedChanges(true);
}

void SettingsModel::setAgastDetectorType(const QString &detectorType)
{
  mSettings->agast()->setDetectorType(detectorType);
  emit unsavedChanges(true);
}

void SettingsModel::setAkazeDescriptorType(const QString &descriptorType)
{
  mSettings->akaze()->setDescriptorType(descriptorType);
  emit unsavedChanges(true);
}

void SettingsModel::setAkazeDescriptorSize(int descriptorSize)
{
  mSettings->akaze()->setDescriptorSize(descriptorSize);
  emit unsavedChanges(true);
}

void SettingsModel::setAkazeDescriptorChannels(int channels)
{
  mSettings->akaze()->setDescriptorChannels(channels);
  emit unsavedChanges(true);
}

void SettingsModel::setAkazeThreshold(double threshold)
{
  mSettings->akaze()->setThreshold(threshold);
  emit unsavedChanges(true);
}

void SettingsModel::setAkazeOctaves(int octaves)
{
  mSettings->akaze()->setOctaves(octaves);
  emit unsavedChanges(true);
}

void SettingsModel::setAkazeOctaveLayers(int octaveLayers)
{
  mSettings->akaze()->setOctaveLayers(octaveLayers);
  emit unsavedChanges(true);
}

void SettingsModel::setAkazeDiffusivity(const QString &diffusivity)
{
  mSettings->akaze()->setDiffusivity(diffusivity);
  emit unsavedChanges(true);
}

void SettingsModel::setSiftFeaturesNumber(int featuresNumber)
{
  mSettings->sift()->setFeaturesNumber(featuresNumber);
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
