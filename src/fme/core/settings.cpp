#include "settings.h"

#include "fme/core/features/agast.h"
#include "fme/core/features/akaze.h"
#include "fme/core/features/brief.h"
#include "fme/core/features/brisk.h"
#include "fme/core/features/daisy.h"
#include "fme/core/features/fast.h"
#include "fme/core/features/freak.h"
#include "fme/core/features/gftt.h"
#include "fme/core/features/hog.h"
#include "fme/core/features/latch.h"
#include "fme/core/features/lucid.h"
#include "fme/core/features/msd.h"
#include "fme/core/features/mser.h"
#include "fme/core/features/kaze.h"
#include "fme/core/features/orb.h"
#include "fme/core/features/sift.h"
#include "fme/core/features/star.h"
#include "fme/core/features/surf.h"
#include "fme/core/features/matcher.h"

#include "fme/core/preprocess/acebsf.h"
#include "fme/core/preprocess/clahe.h"
#include "fme/core/preprocess/cmbfhe.h"
#include "fme/core/preprocess/dhe.h"
#include "fme/core/preprocess/fahe.h"
#include "fme/core/preprocess/hmclahe.h"
#include "fme/core/preprocess/lce_bsescs.h"
#include "fme/core/preprocess/msrcp.h"
#include "fme/core/preprocess/noshp.h"
#include "fme/core/preprocess/pohe.h"
#include "fme/core/preprocess/rswhe.h"
#include "fme/core/preprocess/wallis.h"

#include <QSettings>
#include <QLocale>

#include <memory>

namespace fme
{


Settings::Settings()
  : ISettings(),
    mHistoyMaxSize(10),
    mKeypointsFormat("Binary"),
    mMatchesFormat("Binary"),
    mAcebsf(new AcebsfProperties),
    mClahe(new ClaheProperties),
    mCmbfhe(new CmbfheProperties),
    mDhe(new DheProperties),
    mFahe(new FaheProperties),
    mHmclahe(new HmclaheProperties),
    mLceBsescs(new LceBsescsProperties),
    mMsrcp(new MsrcpProperties),
    mNoshp(new NoshpProperties),
    mPohe(new PoheProperties),
    mRswhe(new RswheProperties),
    mWallis(new WallisProperties),
    mAgast(new AgastProperties),
    mAkaze(new AkazeProperties),
    mBrief(new BriefProperties),
    mBrisk(new BriskProperties),
    mDaisy(new DaisyProperties),
    mFast(new FastProperties),
    mFreak(new FreakProperties),
    mGftt(new GfttProperties),
    mHog(new HogProperties),
    mKaze(new KazeProperties),
    mLatch(new LatchProperties),
    mLucid(new LucidProperties),
    mMsd(new MsdProperties),
    mMser(new MserProperties),
    mOrb(new OrbProperties),
    mSift(new SiftProperties),
    mStar(new StarProperties),
    mSurf(new SurfProperties),
    mMatchMethod("Flann Based Matching"),
    mFlannMatcher(new FlannMatcherProperties),
    mBruteForceMatcher(new BruteForceMatcherProperties),
    mRobustMatcherRefinement(new RobustMatcherProperties)
{

  reset();
}

Settings::~Settings()
{
  if (mAcebsf){
    delete mAcebsf;
    mAcebsf = nullptr;
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

  if (mLceBsescs){
    delete mLceBsescs;
    mLceBsescs = nullptr;
  }

  if (mMsrcp){
    delete mMsrcp;
    mMsrcp = nullptr;
  }

  if (mNoshp){
    delete mNoshp;
    mNoshp = nullptr;
  }

  if (mPohe){
    delete mPohe;
    mPohe = nullptr;
  }

  if (mRswhe){
    delete mRswhe;
    mRswhe = nullptr;
  }

  if (mWallis){
    delete mWallis;
    mWallis = nullptr;
  }

  if (mAgast){
    delete mAgast;
    mAgast = nullptr;
  }

  if (mAkaze){
    delete mAkaze;
    mAkaze = nullptr;
  }

  if (mBrief){
    delete mBrief;
    mBrief = nullptr;
  }

  if (mBrisk){
    delete mBrisk;
    mBrisk = nullptr;
  }

  if (mDaisy){
    delete mDaisy;
    mDaisy = nullptr;
  }

  if (mFast){
    delete mFast;
    mFast = nullptr;
  }

  if (mFreak){
    delete mFreak;
    mFreak = nullptr;
  }

  if (mGftt){
    delete mGftt;
    mGftt = nullptr;
  }

  if (mHog){
    delete mHog;
    mHog = nullptr;
  }

  if (mKaze){
    delete mKaze;
    mKaze = nullptr;
  }

  if (mLatch){
    delete mLatch;
    mLatch = nullptr;
  }

  if (mLucid){
    delete mLucid;
    mLucid = nullptr;
  }

  if (mMsd){
    delete mMsd;
    mMsd = nullptr;
  }

  if (mMser){
    delete mMser;
    mMser = nullptr;
  }

  if (mOrb){
    delete mOrb;
    mOrb = nullptr;
  }

  if (mSift){
    delete mSift;
    mSift = nullptr;
  }

  if (mStar){
    delete mStar;
    mStar = nullptr;
  }

  if (mSurf){
    delete mSurf;
    mSurf = nullptr;
  }

  if (mFlannMatcher){
    delete mFlannMatcher;
    mFlannMatcher = nullptr;
  }

  if (mBruteForceMatcher){
    delete mBruteForceMatcher;
    mBruteForceMatcher = nullptr;
  }

  if (mRobustMatcherRefinement){
    delete mRobustMatcherRefinement;
    mRobustMatcherRefinement = nullptr;
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

QString Settings::keypointsFormat() const
{
  return mKeypointsFormat;
}

void Settings::setKeypointsFormat(const QString &format)
{
  mKeypointsFormat = format;
}

QString Settings::matchesFormat() const
{
  return mMatchesFormat;
}

void Settings::setMatchesFormat(const QString &format)
{
  mMatchesFormat = format;
}

IAcebsf *Settings::acebsf()
{
  return mAcebsf;
}

const IAcebsf *Settings::acebsf() const
{
  return mAcebsf;
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

ILceBsescs *Settings::lceBsescs()
{
  return mLceBsescs;
}

const ILceBsescs *Settings::lceBsescs() const
{
  return mLceBsescs;
}

IMsrcp *Settings::msrcp()
{
  return mMsrcp;
}

const IMsrcp *Settings::msrcp() const
{
  return mMsrcp;
}

INoshp *Settings::noshp()
{
  return mNoshp;
}

const INoshp *Settings::noshp() const
{
  return mNoshp;
}

IPohe *Settings::pohe()
{
  return mPohe;
}

const IPohe *Settings::pohe() const
{
  return mPohe;
}

IRswhe *Settings::rswhe()
{
  return mRswhe;
}

const IRswhe *Settings::rswhe() const
{
  return mRswhe;
}

IWallis *Settings::wallis()
{
  return mWallis;
}

const IWallis *Settings::wallis() const
{
  return mWallis;
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

IBrief *Settings::brief()
{
  return mBrief;
}

const IBrief *Settings::brief() const
{
  return mBrief;
}

IBrisk *Settings::brisk()
{
  return mBrisk;
}

const IBrisk *Settings::brisk() const
{
  return mBrisk;
}

IDaisy *Settings::daisy()
{
  return mDaisy;
}

const IDaisy *Settings::daisy() const
{
  return mDaisy;
}

IFast *Settings::fast()
{
  return mFast;
}

const IFast *Settings::fast() const
{
  return mFast;
}

IFreak *Settings::freak()
{
  return mFreak;
}

const IFreak *Settings::freak() const
{
  return mFreak;
}

IGftt *Settings::gftt()
{
  return mGftt;
}

const IGftt *Settings::gftt() const
{
  return mGftt;
}

IHog *Settings::hog()
{
  return mHog;
}

const IHog *Settings::hog() const
{
  return mHog;
}

IKaze *Settings::kaze()
{
  return mKaze;
}

const IKaze *Settings::kaze() const
{
  return mKaze;
}

ILatch *Settings::latch()
{
  return mLatch;
}

const ILatch *Settings::latch() const
{
  return mLatch;
}

ILucid *Settings::lucid()
{
  return mLucid;
}

const ILucid *Settings::lucid() const
{
  return mLucid;
}

IMsd *Settings::msd()
{
  return mMsd;
}

const IMsd *Settings::msd() const
{
  return mMsd;
}

IMser *Settings::mser()
{
  return mMser;
}

const IMser *Settings::mser() const
{
  return mMser;
}

IOrb *Settings::orb()
{
  return mOrb;
}

const IOrb *Settings::orb() const
{
  return mOrb;
}

ISift *Settings::sift()
{
  return mSift;
}

const ISift *Settings::sift() const
{
  return mSift;
}

IStar *Settings::star()
{
  return mStar;
}

const IStar *Settings::star() const
{
  return mStar;
}

ISurf *fme::Settings::surf()
{
  return mSurf;
}

const ISurf *Settings::surf() const
{
  return mSurf;
}

QString Settings::matchMethod() const
{
  return mMatchMethod;
}

void Settings::setMatchMethod(const QString &matchingMethod)
{
  mMatchMethod = matchingMethod;
}

IFlannMatcher *Settings::flannMatcher()
{
  return mFlannMatcher;
}

const IFlannMatcher *Settings::flannMatcher() const
{
  return mFlannMatcher;
}

IBruteForceMatcher *Settings::bruteForceMatcher()
{
  return mBruteForceMatcher;
}

const IBruteForceMatcher *Settings::bruteForceMatcher() const
{
  return mBruteForceMatcher;
}

IRobustMatcherRefinement *Settings::robustMatcherRefinement()
{
  return mRobustMatcherRefinement;
}

const IRobustMatcherRefinement *Settings::robustMatcherRefinement() const
{
  return mRobustMatcherRefinement;
}


void Settings::reset()
{
  mLanguage = "en";

  mHistoyMaxSize = 10;
  mHistory.clear();
  mKeypointsFormat = "Binary";
  mMatchesFormat = "Binary";

  mAcebsf->reset();
  mClahe->reset();
  mCmbfhe->reset();
  mDhe->reset();
  mFahe->reset();
  mHmclahe->reset();
  mLceBsescs->reset();
  mMsrcp->reset();
  mNoshp->reset();
  mPohe->reset();
  mRswhe->reset();
  mWallis->reset();

  mAgast->reset();
  mAkaze->reset();
  mBrief->reset();
  mBrisk->reset();
  mDaisy->reset();
  mFast->reset();
  mFreak->reset();
  mGftt->reset();
  mHog->reset();
  mKaze->reset();
  mLatch->reset();
  mLucid->reset();
  mMsd->reset();
  mMser->reset();
  mOrb->reset();
  mSift->reset();
  mStar->reset();
  mSurf->reset();

  mMatchMethod = "Flann Based Matching";
  mFlannMatcher->reset();
  mBruteForceMatcher->reset();
  mRobustMatcherRefinement->reset();
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

  settings.setKeypointsFormat(mSettingsRW->value("MATCH/KeypointsFormat", settings.keypointsFormat()).toString());
  settings.setMatchMethod(mSettingsRW->value("MATCH/MatchMethod", settings.matchesFormat()).toString());

  /* CLAHE */
  settings.clahe()->setClipLimit(mSettingsRW->value("CLAHE/ClipLimit", settings.clahe()->clipLimit()).toDouble());
  settings.clahe()->setTilesGridSize(mSettingsRW->value("CLAHE/TilesGridSize", settings.clahe()->tilesGridSize()).toSize());

  /* CMBFHE */
  settings.cmbfhe()->setBlockSize(mSettingsRW->value("CMBFHE/BlockSize", settings.cmbfhe()->blockSize()).toSize());

  /* DHE */
  settings.dhe()->setX(mSettingsRW->value("DHE/x", settings.dhe()->x()).toInt());

  /* FAHE */
  settings.fahe()->setBlockSize(mSettingsRW->value("FAHE/BlockSize", settings.fahe()->blockSize()).toSize());

  /* HMCLAHE */
  settings.hmclahe()->setL(mSettingsRW->value("HMCLAHE/L", settings.hmclahe()->l()).toDouble());
  settings.hmclahe()->setPhi(mSettingsRW->value("HMCLAHE/Phi", settings.hmclahe()->phi()).toDouble());
  settings.hmclahe()->setBlockSize(mSettingsRW->value("HMCLAHE/BlockSize", settings.hmclahe()->blockSize()).toSize());

  /* LCE_BSESCS */
  settings.lceBsescs()->setBlockSize(mSettingsRW->value("LCE_BSESCS/BlockSize", settings.lceBsescs()->blockSize()).toSize());

  /* MSRCP */
  settings.msrcp()->setMidScale(mSettingsRW->value("MSRCP/MidScale", settings.msrcp()->midScale()).toDouble());
  settings.msrcp()->setLargeScale(mSettingsRW->value("MSRCP/LargeScale", settings.msrcp()->largeScale()).toDouble());
  settings.msrcp()->setSmallScale(mSettingsRW->value("MSRCP/SmallScale", settings.msrcp()->smallScale()).toDouble());

  /* NOSHP */
  settings.noshp()->setBlockSize(mSettingsRW->value("NOSHP/BlockSize", settings.noshp()->blockSize()).toSize());

  /* POHE */
  settings.pohe()->setBlockSize(mSettingsRW->value("POHE/BlockSize", settings.pohe()->blockSize()).toSize());

  /* RSWHE */
  int histogramCutDef = static_cast<int>(settings.rswhe()->histogramCut());
  IRswhe::HistogramCut value = static_cast<IRswhe::HistogramCut>(mSettingsRW->value("RSWHE/HistogramCut", histogramCutDef).toInt());
  settings.rswhe()->setHistogramCut(value);
  settings.rswhe()->setHistogramDivisions(mSettingsRW->value("RSWHE/HistogramDivisions", settings.rswhe()->histogramDivisions()).toInt());

  /* WALLIS */
  settings.wallis()->setContrast(mSettingsRW->value("WALLIS/Contrast", settings.wallis()->contrast()).toDouble());
  settings.wallis()->setBrightness(mSettingsRW->value("WALLIS/Brightness", settings.wallis()->brightness()).toDouble());
  settings.wallis()->setImposedAverage(mSettingsRW->value("WALLIS/ImposedAverage", settings.wallis()->imposedAverage()).toInt());
  settings.wallis()->setImposedLocalStdDev(mSettingsRW->value("WALLIS/ImposedLocalStdDev", settings.wallis()->imposedLocalStdDev()).toInt());
  settings.wallis()->setKernelSize(mSettingsRW->value("WALLIS/KernelSize", settings.wallis()->kernelSize()).toInt());

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

  /* BRIEF */
  settings.brief()->setBytes(mSettingsRW->value("BRIEF/Bytes", settings.brief()->bytes()).toString());
  settings.brief()->setUseOrientation(mSettingsRW->value("BRIEF/Orientation", settings.brief()->useOrientation()).toBool());

  /* BRISK */
  settings.brisk()->setOctaves(mSettingsRW->value("BRISK/Octaves", settings.brisk()->octaves()).toInt());
  settings.brisk()->setThreshold(mSettingsRW->value("BRISK/Threshold", settings.brisk()->threshold()).toInt());
  settings.brisk()->setPatternScale(mSettingsRW->value("BRISK/PatternScale", settings.brisk()->patternScale()).toDouble());

  /* DAISY */
  settings.daisy()->setNorm(mSettingsRW->value("DAISY/Norm", settings.daisy()->norm()).toString());
  settings.daisy()->setQHist(mSettingsRW->value("DAISY/QHist", settings.daisy()->qHist()).toInt());
  settings.daisy()->setQTheta(mSettingsRW->value("DAISY/QTheta", settings.daisy()->qTheta()).toInt());
  settings.daisy()->setRadius(mSettingsRW->value("DAISY/Radius", settings.daisy()->radius()).toInt());
  settings.daisy()->setQRadius(mSettingsRW->value("DAISY/QRadius", settings.daisy()->qRadius()).toInt());
  settings.daisy()->setInterpolation(mSettingsRW->value("DAISY/Interpolation", settings.daisy()->interpolation()).toBool());
  settings.daisy()->setUseOrientation(mSettingsRW->value("DAISY/UseOrientation", settings.daisy()->useOrientation()).toBool());

  /* FAST */
  settings.fast()->setThreshold(mSettingsRW->value("FAST/Threshold", settings.fast()->threshold()).toInt());
  settings.fast()->setDetectorType(mSettingsRW->value("FAST/DetectorType", settings.fast()->detectorType()).toString());
  settings.fast()->setNonmaxSuppression(mSettingsRW->value("FAST/NonmaxSuppression", settings.fast()->nonmaxSuppression()).toBool());

  /* FREAK */
  settings.freak()->setOctaves(mSettingsRW->value("FREAK/Octaves", settings.freak()->octaves()).toInt());
  settings.freak()->setPatternScale(mSettingsRW->value("FREAK/PatternScale", settings.freak()->patternScale()).toDouble());
  settings.freak()->setScaleNormalized(mSettingsRW->value("FREAK/ScaleNormalized", settings.freak()->scaleNormalized()).toBool());
  settings.freak()->setOrientationNormalized(mSettingsRW->value("FREAK/OrientationNormalized", settings.freak()->orientationNormalized()).toBool());

  /* GFTT */
  settings.gftt()->setK(mSettingsRW->value("GFTT/K", settings.gftt()->k()).toDouble());
  settings.gftt()->setBlockSize(mSettingsRW->value("GFTT/BlockSize", settings.gftt()->blockSize()).toInt());
  settings.gftt()->setMaxFeatures(mSettingsRW->value("GFTT/MaxFeatures", settings.gftt()->maxFeatures()).toInt());
  settings.gftt()->setMinDistance(mSettingsRW->value("GFTT/MinDistance", settings.gftt()->minDistance()).toDouble());
  settings.gftt()->setQualityLevel(mSettingsRW->value("GFTT/QualityLevel", settings.gftt()->qualityLevel()).toDouble());
  settings.gftt()->setHarrisDetector(mSettingsRW->value("GFTT/HarrisDetector", settings.gftt()->harrisDetector()).toBool());

  /* HOG */
  settings.hog()->setNbins(mSettingsRW->value("HOG/Nbins", settings.hog()->nbins()).toInt());
  settings.hog()->setWinSize(mSettingsRW->value("HOG/WinSize", settings.hog()->winSize()).toSize());
  settings.hog()->setCellSize(mSettingsRW->value("HOG/CellSize", settings.hog()->cellSize()).toSize());
  settings.hog()->setBlockSize(mSettingsRW->value("HOG/BlockSize", settings.hog()->blockSize()).toSize());
  settings.hog()->setBlockStride(mSettingsRW->value("HOG/BlockStride", settings.hog()->blockStride()).toSize());
  settings.hog()->setDerivAperture(mSettingsRW->value("HOG/DerivAperture", settings.hog()->derivAperture()).toInt());

  /* KAZE */
  settings.kaze()->setOctaves(mSettingsRW->value("KAZE/Octaves", settings.kaze()->octaves()).toInt());
  settings.kaze()->setUpright(mSettingsRW->value("KAZE/Upright", settings.kaze()->upright()).toBool());
  settings.kaze()->setThreshold(mSettingsRW->value("KAZE/Threshold", settings.kaze()->threshold()).toDouble());
  settings.kaze()->setDiffusivity(mSettingsRW->value("KAZE/Diffusivity", settings.kaze()->diffusivity()).toString());
  settings.kaze()->setOctaveLayers(mSettingsRW->value("KAZE/OctaveLayers", settings.kaze()->octaveLayers()).toInt());
  settings.kaze()->setExtendedDescriptor(mSettingsRW->value("KAZE/ExtendedDescriptor", settings.kaze()->extendedDescriptor()).toBool());

  /* LATCH */
  settings.latch()->setBytes(mSettingsRW->value("LATCH/Bytes", settings.latch()->bytes()).toString());
  settings.latch()->setHalfSsdSize(mSettingsRW->value("LATCH/HalfSsdSize", settings.latch()->halfSsdSize()).toInt());
  settings.latch()->setRotationInvariance(mSettingsRW->value("LATCH/RotationInvariance", settings.latch()->rotationInvariance()).toBool());

  /* LUCID */
  settings.lucid()->setBlurKernel(mSettingsRW->value("LUCID/BlurKernel", settings.lucid()->blurKernel()).toInt());
  settings.lucid()->setLucidKernel(mSettingsRW->value("LUCID/LucidKernel", settings.lucid()->lucidKernel()).toInt());

  /* MSD */
  settings.msd()->setKNN(mSettingsRW->value("MSD/KNN", settings.msd()->knn()).toInt());
  settings.msd()->setAffineTilts(mSettingsRW->value("MSD/AffineTilts", settings.msd()->affineTilts()).toInt());
  settings.msd()->setNScales(mSettingsRW->value("MSD/NScales", settings.msd()->nScales()).toInt());
  settings.msd()->setAffineMSD(mSettingsRW->value("MSD/AffineMSD", settings.msd()->affineMSD()).toBool());
  settings.msd()->setNMSRadius(mSettingsRW->value("MSD/NMSRadius", settings.msd()->NMSRadius()).toInt());
  settings.msd()->setNMSScaleRadius(mSettingsRW->value("MSD/NMSScaleRadius", settings.msd()->NMSScaleRadius()).toInt());
  settings.msd()->setSearchAreaRadius(mSettingsRW->value("MSD/AreaRadius", settings.msd()->searchAreaRadius()).toInt());
  settings.msd()->setPatchRadius(mSettingsRW->value("MSD/PathRadius", settings.msd()->patchRadius()).toInt());
  settings.msd()->setScaleFactor(mSettingsRW->value("MSD/ScaleFactor", settings.msd()->scaleFactor()).toDouble());
  settings.msd()->setThresholdSaliency(mSettingsRW->value("MSD/ThresholdSaliency", settings.msd()->thresholdSaliency()).toDouble());
  settings.msd()->setComputeOrientation(mSettingsRW->value("MSD/ComputeOrientations", settings.msd()->computeOrientation()).toBool());

  /* MSER */
  settings.mser()->setDelta(mSettingsRW->value("MSER/Delta", settings.mser()->delta()).toInt());
  settings.mser()->setMaxArea(mSettingsRW->value("MSER/MaxArea", settings.mser()->maxArea()).toInt());
  settings.mser()->setMinArea(mSettingsRW->value("MSER/MinArea", settings.mser()->minArea()).toInt());
  settings.mser()->setMinMargin(mSettingsRW->value("MSER/MinMargin", settings.mser()->minMargin()).toInt());
  settings.mser()->setEdgeBlurSize(mSettingsRW->value("MSER/EdgeBlurSize", settings.mser()->edgeBlurSize()).toInt());
  settings.mser()->setMaxEvolution(mSettingsRW->value("MSER/MaxEvolution", settings.mser()->maxEvolution()).toInt());
  settings.mser()->setMaxVariation(mSettingsRW->value("MSER/MaxVariation", settings.mser()->maxVariation()).toDouble());
  settings.mser()->setMinDiversity(mSettingsRW->value("MSER/MinDiversity", settings.mser()->minDiversity()).toDouble());
  settings.mser()->setAreaThreshold(mSettingsRW->value("MSER/AreaThreshold", settings.mser()->areaThreshold()).toDouble());

  /* ORB */
  settings.orb()->setWTA_K(mSettingsRW->value("ORB/WTA_K", settings.orb()->wta_k()).toInt());
  settings.orb()->setPatchSize(mSettingsRW->value("ORB/PatchSize", settings.orb()->patchSize()).toInt());
  settings.orb()->setScoreType(mSettingsRW->value("ORB/ScoreType", settings.orb()->scoreType()).toString());
  settings.orb()->setScaleFactor(mSettingsRW->value("ORB/ScaleFactor", settings.orb()->scaleFactor()).toDouble());
  settings.orb()->setLevelsNumber(mSettingsRW->value("ORB/LevelsNumber", settings.orb()->levelsNumber()).toInt());
  settings.orb()->setEdgeThreshold(mSettingsRW->value("ORB/EdgeThreshold", settings.orb()->edgeThreshold()).toInt());
  settings.orb()->setFastThreshold(mSettingsRW->value("ORB/FastThreshold", settings.orb()->fastThreshold()).toInt());
  settings.orb()->setFeaturesNumber(mSettingsRW->value("ORB/FeaturesNumber", settings.orb()->featuresNumber()).toInt());

  /* SIFT */
  settings.sift()->setSigma(mSettingsRW->value("SIFT/Sigma", settings.sift()->sigma()).toDouble());
  settings.sift()->setOctaveLayers(mSettingsRW->value("SIFT/OctaveLayers", settings.sift()->octaveLayers()).toInt());
  settings.sift()->setEdgeThreshold(mSettingsRW->value("SIFT/EdgeThreshold", settings.sift()->edgeThreshold()).toDouble());
  settings.sift()->setFeaturesNumber(mSettingsRW->value("SIFT/FeaturesNumber", settings.sift()->featuresNumber()).toInt());
  settings.sift()->setContrastThreshold(mSettingsRW->value("SIFT/ContrastThreshold", settings.sift()->contrastThreshold()).toDouble());

  /* STAR */
  settings.star()->setMaxSize(mSettingsRW->value("STAR/MaxSize", settings.star()->maxSize()).toInt());
  settings.star()->setResponseThreshold(mSettingsRW->value("STAR/ResponseThreshold", settings.star()->responseThreshold()).toInt());
  settings.star()->setSuppressNonmaxSize(mSettingsRW->value("STAR/SuppressNonmaxSize", settings.star()->suppressNonmaxSize()).toInt());
  settings.star()->setLineThresholdBinarized(mSettingsRW->value("STAR/LineThresholdBinarized", settings.star()->lineThresholdBinarized()).toInt());
  settings.star()->setLineThresholdProjected(mSettingsRW->value("STAR/LineThresholdProjected", settings.star()->lineThresholdProjected()).toInt());

  /* SURF */
  settings.surf()->setOctaves(mSettingsRW->value("SURF/Octaves", settings.surf()->octaves()).toInt());
  settings.surf()->setOctaveLayers(mSettingsRW->value("SURF/OctaveLayers", settings.surf()->octaveLayers()).toInt());
  settings.surf()->setRotatedFeatures(mSettingsRW->value("SURF/RotatedFeatures", settings.surf()->rotatedFeatures()).toBool());
  settings.surf()->setHessianThreshold(mSettingsRW->value("SURF/HessianThreshold", settings.surf()->hessianThreshold()).toDouble());
  settings.surf()->setExtendedDescriptor(mSettingsRW->value("SURF/ExtendedDescriptor", settings.surf()->extendedDescriptor()).toBool());

  /* Matching */
  settings.setMatchMethod(mSettingsRW->value("MATCH/MatchMethod", settings.matchMethod()).toString());
  int normType = mSettingsRW->value("MATCH/BFNormType", static_cast<int>(settings.bruteForceMatcher()->normType())).toInt();
  settings.bruteForceMatcher()->setNormType(static_cast<IBruteForceMatcher::Norm>(normType));
  settings.robustMatcherRefinement()->setRatio(mSettingsRW->value("MATCH/RefinementRatio", settings.robustMatcherRefinement()->ratio()).toDouble());
  settings.robustMatcherRefinement()->setDistance(mSettingsRW->value("MATCH/RefinementDistance", settings.robustMatcherRefinement()->distance()).toDouble());
  settings.robustMatcherRefinement()->setConfidence(mSettingsRW->value("MATCH/RefinementConfidence", settings.robustMatcherRefinement()->confidence()).toDouble());
  settings.robustMatcherRefinement()->setCrossCheck(mSettingsRW->value("MATCH/RefinementCrossCheck", settings.robustMatcherRefinement()->crossCheck()).toBool());
  settings.robustMatcherRefinement()->setMaxIters(mSettingsRW->value("MATCH/RefinementMaxIters", settings.robustMatcherRefinement()->maxIter()).toInt());
  int geometricTest = mSettingsRW->value("MATCH/RefinementGeometricTest", static_cast<int>(settings.robustMatcherRefinement()->geometricTest())).toInt();
  settings.robustMatcherRefinement()->setGeometricTest(static_cast<IRobustMatcherRefinement::GeometricTest>(geometricTest));
  int homographyComputeMethod = mSettingsRW->value("MATCH/RefinementHomographyComputeMethod", static_cast<int>(settings.robustMatcherRefinement()->homographyComputeMethod())).toInt();
  settings.robustMatcherRefinement()->setHomographyComputeMethod(static_cast<IRobustMatcherRefinement::HomographyComputeMethod>(homographyComputeMethod));
  int fundamentalComputeMethod = mSettingsRW->value("MATCH/RefinementFundamentalComputeMethod", static_cast<int>(settings.robustMatcherRefinement()->fundamentalComputeMethod())).toInt();
  settings.robustMatcherRefinement()->setFundamentalComputeMethod(static_cast<IRobustMatcherRefinement::FundamentalComputeMethod>(fundamentalComputeMethod));
  int essentialComputeMethod = mSettingsRW->value("MATCH/RefinementEssentialComputeMethod", static_cast<int>(settings.robustMatcherRefinement()->essentialComputeMethod())).toInt();
  settings.robustMatcherRefinement()->setEssentialComputeMethod(static_cast<IRobustMatcherRefinement::EssentialComputeMethod>(essentialComputeMethod));
}

void SettingsRW::write(const ISettings &settings)
{
  mSettingsRW->setValue("lang", settings.language());

  mSettingsRW->setValue("HISTORY/MaxSize", settings.historyMaxSize());
  mSettingsRW->setValue("HISTORY/RecentProjects", settings.history());

  mSettingsRW->setValue("MATCH/KeypointsFormat", settings.keypointsFormat());
  mSettingsRW->setValue("MATCH/MatchMethod", settings.matchesFormat());

  /* CLAHE */
  mSettingsRW->setValue("CLAHE/ClipLimit", settings.clahe()->clipLimit());
  mSettingsRW->setValue("CLAHE/TilesGridSize", settings.clahe()->tilesGridSize());

  /* CMBFHE */
  mSettingsRW->setValue("CMBFHE/BlockSize", settings.cmbfhe()->blockSize());

  /* DHE */
  mSettingsRW->setValue("DHE/x", settings.dhe()->x());

  /* FAHE */
  mSettingsRW->setValue("FAHE/BlockSize", settings.fahe()->blockSize());

  /* HMCLAHE */
  mSettingsRW->setValue("HMCLAHE/L", settings.hmclahe()->l());
  mSettingsRW->setValue("HMCLAHE/Phi", settings.hmclahe()->phi());
  mSettingsRW->setValue("HMCLAHE/BlockSize", settings.hmclahe()->blockSize());

  /* LCE_BSESCS */
  mSettingsRW->setValue("LCE_BSESCS/BlockSize", settings.lceBsescs()->blockSize());

  /* MSRCP */
  mSettingsRW->setValue("MSRCP/MidScale", settings.msrcp()->midScale());
  mSettingsRW->setValue("MSRCP/LargeScale", settings.msrcp()->largeScale());
  mSettingsRW->setValue("MSRCP/SmallScale", settings.msrcp()->smallScale());

  /* NOSHP */
  mSettingsRW->setValue("NOSHP/BlockSize", settings.noshp()->blockSize());

  /* POHE */
  mSettingsRW->setValue("POHE/BlockSize", settings.pohe()->blockSize());

  /* RSWHE */
  mSettingsRW->setValue("RSWHE/HistogramCut", static_cast<int>(settings.rswhe()->histogramCut()));
  mSettingsRW->setValue("RSWHE/HistogramDivisions", settings.rswhe()->histogramDivisions());

  /* WALLIS */
  mSettingsRW->setValue("WALLIS/Contrast", settings.wallis()->contrast());
  mSettingsRW->setValue("WALLIS/Brightness", settings.wallis()->brightness());
  mSettingsRW->setValue("WALLIS/ImposedAverage", settings.wallis()->imposedAverage());
  mSettingsRW->setValue("WALLIS/ImposedLocalStdDev", settings.wallis()->imposedLocalStdDev());
  mSettingsRW->setValue("WALLIS/KernelSize", settings.wallis()->kernelSize());


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

  /* BRIEF */
  mSettingsRW->setValue("BRIEF/Bytes", settings.brief()->bytes());
  mSettingsRW->setValue("BRIEF/Orientation", settings.brief()->useOrientation());

  /* BRISK */
  mSettingsRW->setValue("BRISK/Octaves", settings.brisk()->octaves());
  mSettingsRW->setValue("BRISK/Threshold", settings.brisk()->threshold());
  mSettingsRW->setValue("BRISK/PatternScale", settings.brisk()->patternScale());

  /* DAISY */
  mSettingsRW->setValue("DAISY/Norm", settings.daisy()->norm());
  mSettingsRW->setValue("DAISY/QHist", settings.daisy()->qHist());
  mSettingsRW->setValue("DAISY/QTheta", settings.daisy()->qTheta());
  mSettingsRW->setValue("DAISY/Radius", settings.daisy()->radius());
  mSettingsRW->setValue("DAISY/QRadius", settings.daisy()->qRadius());
  mSettingsRW->setValue("DAISY/Interpolation", settings.daisy()->interpolation());
  mSettingsRW->setValue("DAISY/UseOrientation", settings.daisy()->useOrientation());

  /* FAST */
  mSettingsRW->setValue("FAST/Threshold", settings.fast()->threshold());
  mSettingsRW->setValue("FAST/DetectorType", settings.fast()->detectorType());
  mSettingsRW->setValue("FAST/NonmaxSuppression", settings.fast()->nonmaxSuppression());

  /* FREAK */
  mSettingsRW->setValue("FREAK/Octaves", settings.freak()->octaves());
  mSettingsRW->setValue("FREAK/PatternScale", settings.freak()->patternScale());
  mSettingsRW->setValue("FREAK/ScaleNormalized", settings.freak()->scaleNormalized());
  mSettingsRW->setValue("FREAK/OrientationNormalized", settings.freak()->orientationNormalized());

  /* GFTT */
  mSettingsRW->setValue("GFTT/K", settings.gftt()->k());
  mSettingsRW->setValue("GFTT/BlockSize", settings.gftt()->blockSize());
  mSettingsRW->setValue("GFTT/MaxFeatures", settings.gftt()->maxFeatures());
  mSettingsRW->setValue("GFTT/MinDistance", settings.gftt()->minDistance());
  mSettingsRW->setValue("GFTT/QualityLevel", settings.gftt()->qualityLevel());
  mSettingsRW->setValue("GFTT/HarrisDetector", settings.gftt()->harrisDetector());

  /* HOG */
  mSettingsRW->setValue("HOG/Nbins", settings.hog()->nbins());
  mSettingsRW->setValue("HOG/WinSize", settings.hog()->winSize());
  mSettingsRW->setValue("HOG/CellSize", settings.hog()->cellSize());
  mSettingsRW->setValue("HOG/BlockSize", settings.hog()->blockSize());
  mSettingsRW->setValue("HOG/BlockStride", settings.hog()->blockStride());
  mSettingsRW->setValue("HOG/DerivAperture", settings.hog()->derivAperture());

  /* KAZE */
  mSettingsRW->setValue("KAZE/Octaves", settings.kaze()->octaves());
  mSettingsRW->setValue("KAZE/Upright", settings.kaze()->upright());
  mSettingsRW->setValue("KAZE/Threshold", settings.kaze()->threshold());
  mSettingsRW->setValue("KAZE/Diffusivity", settings.kaze()->diffusivity());
  mSettingsRW->setValue("KAZE/OctaveLayers", settings.kaze()->octaveLayers());
  mSettingsRW->setValue("KAZE/ExtendedDescriptor", settings.kaze()->extendedDescriptor());

  /* LATCH */
  mSettingsRW->setValue("LATCH/Bytes", settings.latch()->bytes());
  mSettingsRW->setValue("LATCH/HalfSsdSize", settings.latch()->halfSsdSize());
  mSettingsRW->setValue("LATCH/RotationInvariance", settings.latch()->rotationInvariance());

  /* LUCID */
  mSettingsRW->setValue("LUCID/BlurKernel", settings.lucid()->blurKernel());
  mSettingsRW->setValue("LUCID/LucidKernel", settings.lucid()->lucidKernel());

  /* MSD */
  mSettingsRW->setValue("MSD/KNN", settings.msd()->knn());
  mSettingsRW->setValue("MSD/AfineTilts", settings.msd()->affineTilts());
  mSettingsRW->setValue("MSD/NScales", settings.msd()->nScales());
  mSettingsRW->setValue("MSD/AffineMSD", settings.msd()->affineMSD());
  mSettingsRW->setValue("MSD/NMSRadius", settings.msd()->NMSRadius());
  mSettingsRW->setValue("MSD/NMSScaleRadius", settings.msd()->NMSScaleRadius());
  mSettingsRW->setValue("MSD/AreaRadius", settings.msd()->searchAreaRadius());
  mSettingsRW->setValue("MSD/PathRadius", settings.msd()->patchRadius());
  mSettingsRW->setValue("MSD/ScaleFactor", settings.msd()->scaleFactor());
  mSettingsRW->setValue("MSD/ThresholdSaliency", settings.msd()->thresholdSaliency());
  mSettingsRW->setValue("MSD/ComputeOrientations", settings.msd()->computeOrientation());

  /* MSER */
  mSettingsRW->setValue("MSER/Delta", settings.mser()->delta());
  mSettingsRW->setValue("MSER/MaxArea", settings.mser()->maxArea());
  mSettingsRW->setValue("MSER/MinArea", settings.mser()->minArea());
  mSettingsRW->setValue("MSER/MinMargin", settings.mser()->minMargin());
  mSettingsRW->setValue("MSER/EdgeBlurSize", settings.mser()->edgeBlurSize());
  mSettingsRW->setValue("MSER/MaxEvolution", settings.mser()->maxEvolution());
  mSettingsRW->setValue("MSER/MaxVariation", settings.mser()->maxVariation());
  mSettingsRW->setValue("MSER/MinDiversity", settings.mser()->minDiversity());
  mSettingsRW->setValue("MSER/AreaThreshold", settings.mser()->areaThreshold());

  /* ORB */
  mSettingsRW->setValue("ORB/WTA_K", settings.orb()->wta_k());
  mSettingsRW->setValue("ORB/PatchSize", settings.orb()->patchSize());
  mSettingsRW->setValue("ORB/ScoreType", settings.orb()->scoreType());
  mSettingsRW->setValue("ORB/ScaleFactor", settings.orb()->scaleFactor());
  mSettingsRW->setValue("ORB/LevelsNumber", settings.orb()->levelsNumber());
  mSettingsRW->setValue("ORB/EdgeThreshold", settings.orb()->edgeThreshold());
  mSettingsRW->setValue("ORB/FastThreshold", settings.orb()->fastThreshold());
  mSettingsRW->setValue("ORB/FeaturesNumber", settings.orb()->featuresNumber());

  /* SIFT */
  mSettingsRW->setValue("SIFT/Sigma", settings.sift()->sigma());
  mSettingsRW->setValue("SIFT/OctaveLayers", settings.sift()->octaveLayers());
  mSettingsRW->setValue("SIFT/EdgeThreshold", settings.sift()->edgeThreshold());
  mSettingsRW->setValue("SIFT/FeaturesNumber", settings.sift()->featuresNumber());
  mSettingsRW->setValue("SIFT/ContrastThreshold", settings.sift()->contrastThreshold());

  /* STAR */
  mSettingsRW->setValue("STAR/MaxSize", settings.star()->maxSize());
  mSettingsRW->setValue("STAR/ResponseThreshold", settings.star()->responseThreshold());
  mSettingsRW->setValue("STAR/SuppressNonmaxSize", settings.star()->suppressNonmaxSize());
  mSettingsRW->setValue("STAR/LineThresholdBinarized", settings.star()->lineThresholdBinarized());
  mSettingsRW->setValue("STAR/LineThresholdProjected", settings.star()->lineThresholdProjected());

  /* SURF */
  mSettingsRW->setValue("SURF/Octaves", settings.surf()->octaves());
  mSettingsRW->setValue("SURF/OctaveLayers", settings.surf()->octaveLayers());
  mSettingsRW->setValue("SURF/RotatedFeatures", settings.surf()->rotatedFeatures());
  mSettingsRW->setValue("SURF/HessianThreshold", settings.surf()->hessianThreshold());
  mSettingsRW->setValue("SURF/ExtendedDescriptor", settings.surf()->extendedDescriptor());

  /* Matching */
  mSettingsRW->setValue("MATCH/MatchMethod", settings.matchMethod());
  mSettingsRW->setValue("MATCH/BFNormType", static_cast<int>(settings.bruteForceMatcher()->normType()));
  mSettingsRW->setValue("MATCH/RefinementRatio", settings.robustMatcherRefinement()->ratio());
  mSettingsRW->setValue("MATCH/RefinementDistance", settings.robustMatcherRefinement()->distance());
  mSettingsRW->setValue("MATCH/RefinementConfidence", settings.robustMatcherRefinement()->confidence());
  mSettingsRW->setValue("MATCH/RefinementCrossCheck", settings.robustMatcherRefinement()->crossCheck());
  mSettingsRW->setValue("MATCH/RefinementMaxIters", settings.robustMatcherRefinement()->maxIter());
  mSettingsRW->setValue("MATCH/RefinementGeometricTest", static_cast<int>(settings.robustMatcherRefinement()->geometricTest()));
  mSettingsRW->setValue("MATCH/RefinementHomographyComputeMethod", static_cast<int>(settings.robustMatcherRefinement()->homographyComputeMethod()));
  mSettingsRW->setValue("MATCH/RefinementFundamentalComputeMethod", static_cast<int>(settings.robustMatcherRefinement()->fundamentalComputeMethod()));
  mSettingsRW->setValue("MATCH/RefinementEssentialComputeMethod", static_cast<int>(settings.robustMatcherRefinement()->essentialComputeMethod()));
}

void SettingsRW::writeHistory(const ISettings &settings)
{
  mSettingsRW->setValue("HISTORY/RecentProjects", settings.history());
}




} // namespace fme
