#include "settings.h"

#include <QSettings>
#include <QLocale>

namespace fme
{

Surf::Surf()
  : ISurf(),
    mHessianThreshold(100),
    mOctaves(4),
    mOctaveLayers(3),
    mExtendedDescriptor(false),
    mRotatedFeatures(false)
{
}

Surf::~Surf()
{
}

double Surf::hessianThreshold() const
{
  return mHessianThreshold;
}

void Surf::setHessianThreshold(double hessianThreshold)
{
  mHessianThreshold = hessianThreshold;
}

int Surf::octaves() const
{
  return mOctaves;
}

void Surf::setOctaves(int octaves)
{
  mOctaves = octaves;
}

int Surf::octaveLayers() const
{
  return mOctaveLayers;
}

void Surf::setOctaveLayers(int octaveLayers)
{
  mOctaveLayers = octaveLayers;
}

bool Surf::extendedDescriptor() const
{
  return mExtendedDescriptor;
}

void Surf::setExtendedDescriptor(bool extendedDescriptor)
{
  mExtendedDescriptor = extendedDescriptor;
}

bool Surf::rotatedFeatures() const
{
  return mRotatedFeatures;
}

void Surf::setRotatedFeatures(bool rotatedFeatures)
{
  mRotatedFeatures = rotatedFeatures;
}




Sift::Sift()
  : ISift(),
    mFeaturesNumber(5000),
    mOctaveLayers(3),
    mContrastThreshold(0.04),
    mEdgeThreshold(10.),
    mSigma(1.6)
{}

Sift::~Sift() {}

int Sift::featuresNumber() const
{
  return mFeaturesNumber;
}

int Sift::octaveLayers() const
{
  return mOctaveLayers;
}

double Sift::contrastThreshold() const
{
  return mContrastThreshold;
}

double Sift::edgeThreshold() const
{
  return mEdgeThreshold;
}

double Sift::sigma() const
{
  return mSigma;
}

void Sift::setFeaturesNumber(int featuresNumber)
{
  mFeaturesNumber = featuresNumber;
}

void Sift::setOctaveLayers(int octaveLayers)
{
  mOctaveLayers = octaveLayers;
}

void Sift::setContrastThreshold(double contrastThreshold)
{
  mContrastThreshold = contrastThreshold;
}

void Sift::setEdgeThreshold(double edgeThreshold)
{
  mEdgeThreshold = edgeThreshold;
}

void Sift::setSigma(double sigma)
{
  mSigma = sigma;
}




Settings::Settings()
  : ISettings(),
    mSift(new Sift),
    mSurf(new Surf)
{
  reset();
}

Settings::~Settings()
{
  if (mSift){
    delete mSift;
    mSift = nullptr;
  }

  if (mSurf){
    delete mSurf;
    mSurf = nullptr;
  }
}

QString Settings::language() const
{
  return mLanguage;
}

void Settings::setLanguage(const QString &language)
{
  mLanguage = language;
}

ISift *Settings::sift()
{
  return mSift;
}

const ISift *Settings::sift() const
{
  return mSift;
}

ISurf *fme::Settings::surf()
{
  return mSurf;
}

const ISurf *Settings::surf() const
{
  return mSurf;
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

  /* SIFT */
  settings.sift()->setSigma(mSettingsRW->value("SIFT/Sigma", settings.sift()->sigma()).toDouble());
  settings.sift()->setOctaveLayers(mSettingsRW->value("SIFT/OctaveLayers", settings.sift()->octaveLayers()).toInt());
  settings.sift()->setEdgeThreshold(mSettingsRW->value("SIFT/EdgeThreshold", settings.sift()->edgeThreshold()).toDouble());
  settings.sift()->setFeaturesNumber(mSettingsRW->value("SIFT/FeaturesNumber", settings.sift()->featuresNumber()).toInt());
  settings.sift()->setContrastThreshold(mSettingsRW->value("SIFT/ContrastThreshold", settings.sift()->contrastThreshold()).toDouble());

  /* SURF */
  settings.surf()->setOctaves(mSettingsRW->value("SURF/Octaves", settings.surf()->octaves()).toInt());
  settings.surf()->setOctaveLayers(mSettingsRW->value("SURF/OctaveLayers", settings.surf()->octaveLayers()).toInt());
  settings.surf()->setRotatedFeatures(mSettingsRW->value("SURF/RotatedFeatures", settings.surf()->rotatedFeatures()).toBool());
  settings.surf()->setHessianThreshold(mSettingsRW->value("SURF/HessianThreshold", settings.surf()->hessianThreshold()).toDouble());
  settings.surf()->setExtendedDescriptor(mSettingsRW->value("SURF/ExtendedDescriptor", settings.surf()->extendedDescriptor()).toBool());
}

void SettingsRW::write(const ISettings &settings)
{
  mSettingsRW->setValue("lang", settings.language());

  /* SIFT */
  mSettingsRW->setValue("SIFT/Sigma", settings.sift()->sigma());
  mSettingsRW->setValue("SIFT/OctaveLayers", settings.sift()->octaveLayers());
  mSettingsRW->setValue("SIFT/EdgeThreshold", settings.sift()->edgeThreshold());
  mSettingsRW->setValue("SIFT/FeaturesNumber", settings.sift()->featuresNumber());
  mSettingsRW->setValue("SIFT/ContrastThreshold", settings.sift()->contrastThreshold());

  /* SURF */
  mSettingsRW->setValue("SURF/Octaves", settings.surf()->octaves());
  mSettingsRW->setValue("SURF/OctaveLayers", settings.surf()->octaveLayers());
  mSettingsRW->setValue("SURF/RotatedFeatures", settings.surf()->rotatedFeatures());
  mSettingsRW->setValue("SURF/HessianThreshold", settings.surf()->hessianThreshold());
  mSettingsRW->setValue("SURF/ExtendedDescriptor", settings.surf()->extendedDescriptor());
}

} // namespace fme
