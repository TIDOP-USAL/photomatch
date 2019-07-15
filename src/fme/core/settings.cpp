#include "settings.h"

#include <QSettings>
#include <QLocale>

namespace fme
{

/*----------------------------------------------------------------*/
/* Feature Detectors/descriptors                                  */
/*----------------------------------------------------------------*/

Agast::Agast()
  : IAgast(),
    mThreshold(10),
    mNonmaxSuppression(true),
    mDetectorType("OAST_9_16")
{}

Agast::~Agast()
{
}

int Agast::threshold() const
{
  return mThreshold;
}

bool Agast::nonmaxSuppression() const
{
  return mNonmaxSuppression;
}

QString Agast::detectorType() const
{
  return mDetectorType;
}

void Agast::setThreshold(int threshold)
{
  mThreshold = threshold;
}

void Agast::setNonmaxSuppression(bool nonmaxSuppression)
{
  mNonmaxSuppression = nonmaxSuppression;
}

void Agast::setDetectorType(const QString &detectorType)
{
  if (detectorType.compare("AGAST_5_8") == 0 ||
      detectorType.compare("AGAST_7_12d") == 0 ||
      detectorType.compare("AGAST_7_12s") == 0 ||
      detectorType.compare("OAST_9_16") == 0) {
    mDetectorType = detectorType;
  }
}

void Agast::reset()
{
  mThreshold = 10;
  mNonmaxSuppression = true;
  mDetectorType = "OAST_9_16";
}


/*----------------------------------------------------------------*/


Akaze::Akaze()
  : IAkaze(),
    mDescriptorType("MLDB"),
    mDescriptorSize(0),
    mDescriptorChannels(3),
    mThreshold(0.001),
    mOctaves(4),
    mOctaveLayers(4),
    mDiffusivity("DIFF_PM_G2")
{
}

Akaze::~Akaze()
{
}

QString Akaze::descriptorType() const
{
  return mDescriptorType;
}

int Akaze::descriptorSize() const
{
  return mDescriptorSize;
}

int Akaze::descriptorChannels() const
{
  return mDescriptorChannels;
}

double Akaze::threshold() const
{
  return mThreshold;
}

int Akaze::octaves() const
{
  return mOctaves;
}

int Akaze::octaveLayers() const
{
  return mOctaveLayers;
}

QString Akaze::diffusivity() const
{
  return mDiffusivity;
}

void Akaze::setDescriptorType(const QString &descriptorType)
{
  if (descriptorType.compare("KAZE") == 0 ||
      descriptorType.compare("KAZE_UPRIGHT") == 0 ||
      descriptorType.compare("MLDB") == 0 ||
      descriptorType.compare("MLDB_UPRIGHT") == 0){
    mDescriptorType = descriptorType;
  }
}

void Akaze::setDescriptorSize(int descriptorSize)
{
  mDescriptorSize = descriptorSize;
}

void Akaze::setDescriptorChannels(int channels)
{
  mDescriptorChannels = channels;
}

void Akaze::setThreshold(double threshold)
{
  mThreshold = threshold;
}

void Akaze::setOctaves(int octaves)
{
  mOctaves = octaves;
}

void Akaze::setOctaveLayers(int octaveLayers)
{
  mOctaveLayers = octaveLayers;
}

void Akaze::setDiffusivity(const QString &diffusivity)
{
  if (diffusivity.compare("DIFF_PM_G1") == 0 ||
      diffusivity.compare("DIFF_PM_G2") == 0 ||
      diffusivity.compare("DIFF_WEICKERT") == 0 ||
      diffusivity.compare("DIFF_CHARBONNIER") == 0){
    mDiffusivity = diffusivity;
  }
}

void Akaze::reset()
{
  mDescriptorType = "MLDB";
  mDescriptorSize = 0;
  mDescriptorChannels = 3;
  mThreshold = 0.001;
  mOctaves = 4;
  mOctaveLayers = 4;
  mDiffusivity = "DIFF_PM_G2";
}


/*----------------------------------------------------------------*/


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

void Surf::reset()
{
  mHessianThreshold = 100;
  mOctaves = 4;
  mOctaveLayers = 3;
  mExtendedDescriptor = false;
  mRotatedFeatures = false;
}


/*----------------------------------------------------------------*/


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

void Sift::reset()
{
  mFeaturesNumber = 5000;
  mOctaveLayers = 3;
  mContrastThreshold = 0.04;
  mEdgeThreshold = 10.;
  mSigma = 1.6;
}



/*----------------------------------------------------------------*/
/* Image preprocessing                                            */
/*----------------------------------------------------------------*/


Clahe::Clahe()
  : IClahe(),
    mClipLimit(40.),
    mTilesGridSize(QSize(8, 8))
{
}

double Clahe::clipLimit() const
{
  return mClipLimit;
}

void Clahe::setClipLimit(double clipLimit)
{
  mClipLimit = clipLimit;
}

QSize Clahe::tilesGridSize() const
{
  return mTilesGridSize;
}

void Clahe::setTilesGridSize(const QSize &tilesGridSize)
{
  mTilesGridSize = tilesGridSize;
}

void Clahe::reset()
{
  mClipLimit = 40.0;
  mTilesGridSize = QSize(8, 8);
}


/*----------------------------------------------------------------*/


Cmbfhe::Cmbfhe()
  : ICmbfhe(),
    mBlockSize(11,11)
{}

QSize Cmbfhe::blockSize() const
{
  return mBlockSize;
}

void Cmbfhe::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void Cmbfhe::reset()
{
  mBlockSize = QSize(11,11);
}


/*----------------------------------------------------------------*/


Dhe::Dhe()
  : IDhe(),
    mX(1)
{
}

int Dhe::x() const
{
  return mX;
}

void Dhe::setX(int x)
{
  mX = x;
}

void Dhe::reset()
{
  mX = 1;
}


/*----------------------------------------------------------------*/


Fahe::Fahe()
  : IFahe(),
    mBlockSize(QSize(11, 11))
{
}

QSize Fahe::blockSize() const
{
  return mBlockSize;
}

void Fahe::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void Fahe::reset()
{
  mBlockSize = QSize(11, 11);
}


/*----------------------------------------------------------------*/

Hmclahe::Hmclahe()
  : IHmclahe(),
    mBlockSize(17,17),
    mL(0.03),
    mPhi(0.5)
{
}

Hmclahe::~Hmclahe()
{}

QSize Hmclahe::blockSize() const
{
  return mBlockSize;
}

void Hmclahe::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

double Hmclahe::l() const
{
  return mL;
}

void Hmclahe::setL(double l)
{
  mL = l;
}

double Hmclahe::phi() const
{
  return mPhi;
}

void Hmclahe::setPhi(double phi)
{
  mPhi = phi;
}

void Hmclahe::reset()
{
  mBlockSize = QSize(17, 17);
  mL = 0.03;
  mPhi = 0.5;
}


/*----------------------------------------------------------------*/


Settings::Settings()
  : ISettings(),
    mHistoyMaxSize(10),
    mClahe(new Clahe),
    mCmbfhe(new Cmbfhe),
    mDhe(new Dhe),
    mFahe(new Fahe),
    mHmclahe(new Hmclahe),
    mAgast(new Agast),
    mAkaze(new Akaze),
    mSift(new Sift),
    mSurf(new Surf)
{
  reset();
}

Settings::~Settings()
{
  if (mAgast){
    delete mAgast;
    mAgast = nullptr;
  }

  if (mAkaze){
    delete mAkaze;
    mAkaze = nullptr;
  }

  if (mSift){
    delete mSift;
    mSift = nullptr;
  }

  if (mSurf){
    delete mSurf;
    mSurf = nullptr;
  }

  if (mClahe){
    delete mClahe;
    mClahe = nullptr;
  }

  if (mCmbfhe){
    delete mCmbfhe;
    mCmbfhe = nullptr;
  }

  if (mDhe){
    delete mDhe;
    mDhe = nullptr;
  }

  if (mFahe){
    delete mFahe;
    mFahe = nullptr;
  }

  if (mHmclahe){
    delete mHmclahe;
    mHmclahe = nullptr;
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

QStringList Settings::history() const
{
  return mHistory;
}

void Settings::addToHistory(const QString &project)
{
  mHistory.removeAll(project);
  mHistory.prepend(project);

  while (mHistory.size() > mHistoyMaxSize)
    mHistory.removeLast();
}

void Settings::clearHistory()
{
  mHistory.clear();
}

int Settings::historyMaxSize() const
{
  return mHistoyMaxSize;
}

void Settings::setHistoryMaxSize(int maxSize)
{
  mHistoyMaxSize = maxSize;
}

IClahe *Settings::clahe()
{
  return mClahe;
}

const IClahe *Settings::clahe() const
{
  return mClahe;
}

ICmbfhe *Settings::cmbfhe()
{
  return mCmbfhe;
}

const ICmbfhe *Settings::cmbfhe() const
{
  return mCmbfhe;
}

IDhe *Settings::dhe()
{
  return mDhe;
}

const IDhe *Settings::dhe() const
{
  return mDhe;
}

IFahe *Settings::fahe()
{
  return mFahe;
}

const IFahe *Settings::fahe() const
{
  return mFahe;
}

IHmclahe *Settings::hmclahe()
{
  return mHmclahe;
}

const IHmclahe *Settings::hmclahe() const
{
  return mHmclahe;
}

IAgast *Settings::agast()
{
  return mAgast;
}

const IAgast *Settings::agast() const
{
  return mAgast;
}

IAkaze *Settings::akaze()
{
  return mAkaze;
}

const IAkaze *Settings::akaze() const
{
  return mAkaze;
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

  mHistoyMaxSize = 10;
  mHistory.clear();

  mClahe->reset();
  mCmbfhe->reset();
  mFahe->reset();
  mHmclahe->reset();

  mAgast->reset();
  mAkaze->reset();
  mSift->reset();
  mSurf->reset();
}


/*----------------------------------------------------------------*/


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

  settings.setHistoryMaxSize(mSettingsRW->value("HISTORY/MaxSize", settings.historyMaxSize()).toInt());
  QStringList history = mSettingsRW->value("HISTORY/RecentProjects", settings.history()).toStringList();
  settings.clearHistory();
  for(auto &prj : history){
    settings.addToHistory(prj);
  }

  /* CLAHE */
  settings.clahe()->setClipLimit(mSettingsRW->value("CLAHE/ClipLimit", settings.clahe()->clipLimit()).toDouble());
  settings.clahe()->setTilesGridSize(mSettingsRW->value("CLAHE/TilesGridSize", settings.clahe()->tilesGridSize()).toSize());

  /* CMBFHE */
  settings.cmbfhe()->setBlockSize(mSettingsRW->value("CMBFHE/BlockSize", settings.cmbfhe()->blockSize()).toSize());

  /* DHE */
  settings.dhe()->setX(mSettingsRW->value("DHE/x", settings.dhe()->x()).toInt());

  /* FAHE */
  settings.fahe()->setBlockSize(mSettingsRW->value("FAHE/BlockSize", settings.fahe()->blockSize()).toSize());

  //....

  /* AGAST */
  settings.agast()->setThreshold(mSettingsRW->value("AGAST/Threshold", settings.agast()->threshold()).toInt());
  settings.agast()->setNonmaxSuppression(mSettingsRW->value("AGAST/NonmaxSuppression", settings.agast()->nonmaxSuppression()).toBool());
  settings.agast()->setDetectorType(mSettingsRW->value("AGAST/DetectorType", settings.agast()->detectorType()).toString());

  /* AKAZE */
  settings.akaze()->setOctaves(mSettingsRW->value("AKAZE/Octaves", settings.akaze()->octaves()).toInt());
  settings.akaze()->setThreshold(mSettingsRW->value("AKAZE/Threshold", settings.akaze()->threshold()).toDouble());
  settings.akaze()->setDiffusivity(mSettingsRW->value("AKAZE/Diffusivity", settings.akaze()->diffusivity()).toString());
  settings.akaze()->setOctaveLayers(mSettingsRW->value("AKAZE/OctaveLayers", settings.akaze()->octaveLayers()).toInt());
  settings.akaze()->setDescriptorSize(mSettingsRW->value("AKAZE/DescriptorSize", settings.akaze()->descriptorSize()).toInt());
  settings.akaze()->setDescriptorType(mSettingsRW->value("AKAZE/DescriptorType", settings.akaze()->descriptorType()).toString());
  settings.akaze()->setDescriptorChannels(mSettingsRW->value("AKAZE/DescriptorChannels", settings.akaze()->descriptorChannels()).toInt());

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

  mSettingsRW->setValue("HISTORY/MaxSize", settings.historyMaxSize());
  mSettingsRW->setValue("HISTORY/RecentProjects", settings.history());

  /* CLAHE */
  mSettingsRW->setValue("CLAHE/ClipLimit", settings.clahe()->clipLimit());
  mSettingsRW->setValue("CLAHE/TilesGridSize", settings.clahe()->tilesGridSize());

  /* CMBFHE */
  mSettingsRW->setValue("CMBFHE/BlockSize", settings.cmbfhe()->blockSize());

  /* DHE */
  mSettingsRW->setValue("DHE/x", settings.dhe()->x());

  /* FAHE */
  mSettingsRW->setValue("FAHE/BlockSize", settings.fahe()->blockSize());

  //....

  /* AGAST */
  mSettingsRW->setValue("AGAST/Threshold", settings.agast()->threshold());
  mSettingsRW->setValue("AGAST/NonmaxSuppression", settings.agast()->nonmaxSuppression());
  mSettingsRW->setValue("AGAST/DetectorType", settings.agast()->detectorType());

  /* AKAZE */
  mSettingsRW->setValue("AKAZE/Octaves", settings.akaze()->octaves());
  mSettingsRW->setValue("AKAZE/Threshold", settings.akaze()->threshold());
  mSettingsRW->setValue("AKAZE/Diffusivity", settings.akaze()->diffusivity());
  mSettingsRW->setValue("AKAZE/OctaveLayers", settings.akaze()->octaveLayers());
  mSettingsRW->setValue("AKAZE/DescriptorSize", settings.akaze()->descriptorSize());
  mSettingsRW->setValue("AKAZE/DescriptorType", settings.akaze()->descriptorType());
  mSettingsRW->setValue("AKAZE/DescriptorChannels", settings.akaze()->descriptorChannels());

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

void SettingsRW::writeHistory(const ISettings &settings)
{
  mSettingsRW->setValue("HISTORY/RecentProjects", settings.history());
}

} // namespace fme
