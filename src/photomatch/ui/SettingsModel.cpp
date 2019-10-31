#include "SettingsModel.h"

#include "photomatch/core/features/agast.h"
#include "photomatch/core/features/akaze.h"
#include "photomatch/core/features/brief.h"
#include "photomatch/core/features/brisk.h"
#include "photomatch/core/features/daisy.h"
#include "photomatch/core/features/fast.h"
#include "photomatch/core/features/freak.h"
#include "photomatch/core/features/gftt.h"
#include "photomatch/core/features/hog.h"
#include "photomatch/core/features/latch.h"
#include "photomatch/core/features/lucid.h"
#include "photomatch/core/features/msd.h"
#include "photomatch/core/features/mser.h"
#include "photomatch/core/features/kaze.h"
#include "photomatch/core/features/orb.h"
#include "photomatch/core/features/sift.h"
#include "photomatch/core/features/star.h"
#include "photomatch/core/features/surf.h"
#include "photomatch/core/features/matcher.h"

#include "photomatch/core/preprocess/acebsf.h"
#include "photomatch/core/preprocess/clahe.h"
#include "photomatch/core/preprocess/cmbfhe.h"
#include "photomatch/core/preprocess/dhe.h"
#include "photomatch/core/preprocess/fahe.h"
#include "photomatch/core/preprocess/hmclahe.h"
#include "photomatch/core/preprocess/lce_bsescs.h"
#include "photomatch/core/preprocess/msrcp.h"
#include "photomatch/core/preprocess/noshp.h"
#include "photomatch/core/preprocess/pohe.h"
#include "photomatch/core/preprocess/rswhe.h"
#include "photomatch/core/preprocess/wallis.h"

#include <QDir>
#include <QSettings>
#include <QLocale>
#include <QApplication>

namespace photomatch
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

QString SettingsModel::keypointsFormat() const
{
  return mSettings->keypointsFormat();
}

QString SettingsModel::matchesFormat() const
{
  return mSettings->matchesFormat();
}

QSize SettingsModel::acebsfBlockSize() const
{
  return mSettings->acebsf()->blockSize();
}

double SettingsModel::acebsfL() const
{
  return mSettings->acebsf()->l();
}

double SettingsModel::acebsfK1() const
{
  return mSettings->acebsf()->k1();
}

double SettingsModel::acebsfK2() const
{
  return mSettings->acebsf()->k2();
}

double SettingsModel::claheClipLimit() const
{
  return mSettings->clahe()->clipLimit();
}

QSize SettingsModel::claheTilesGridSize() const
{
  return mSettings->clahe()->tilesGridSize();
}

QSize SettingsModel::cmbfheBlockSize() const
{
  return mSettings->cmbfhe()->blockSize();
}

int SettingsModel::dheX() const
{
  return mSettings->dhe()->x();
}

QSize SettingsModel::faheBlockSize() const
{
  return mSettings->fahe()->blockSize();
}

QSize SettingsModel::hmclaheBlockSize() const
{
  return mSettings->hmclahe()->blockSize();
}

double SettingsModel::hmclaheL() const
{
  return mSettings->hmclahe()->l();
}

double SettingsModel::hmclahePhi() const
{
  return mSettings->hmclahe()->phi();
}

QSize SettingsModel::lceBsescsBlockSize() const
{
  return mSettings->lceBsescs()->blockSize();
}

double SettingsModel::msrcpSmallScale() const
{
  return mSettings->msrcp()->smallScale();
}

double SettingsModel::msrcpMidScale() const
{
  return mSettings->msrcp()->midScale();
}

double SettingsModel::msrcpLargeScale() const
{
  return mSettings->msrcp()->largeScale();
}

QSize SettingsModel::noshpBlockSize() const
{
  return mSettings->noshp()->blockSize();
}

QSize SettingsModel::poheBlockSize() const
{
  return mSettings->pohe()->blockSize();
}

int SettingsModel::rswheHistogramDivisions() const
{
  return mSettings->rswhe()->histogramDivisions();
}

int SettingsModel::rswheHistogramCut() const
{
  return static_cast<int>(mSettings->rswhe()->histogramCut());
}

double SettingsModel::wallisContrast() const
{
  return mSettings->wallis()->contrast();
}

double SettingsModel::wallisBrightness() const
{
  return mSettings->wallis()->brightness();
}

int SettingsModel::wallisImposedAverage() const
{
  return mSettings->wallis()->imposedAverage();
}

int SettingsModel::wallisImposedLocalStdDev() const
{
  return mSettings->wallis()->imposedLocalStdDev();
}

int SettingsModel::wallisKernelSize() const
{
  return mSettings->wallis()->kernelSize();
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

QString SettingsModel::briefBytes() const
{
  return mSettings->brief()->bytes();
}

bool SettingsModel::briefUseOrientation() const
{
  return mSettings->brief()->useOrientation();
}

int SettingsModel::briskThreshold() const
{
  return mSettings->brisk()->threshold();
}

int SettingsModel::briskOctaves() const
{
  return mSettings->brisk()->octaves();
}

double SettingsModel::briskPatternScale() const
{
  return mSettings->brisk()->patternScale();
}

double SettingsModel::daisyRadius() const
{
  return mSettings->daisy()->radius();
}

int SettingsModel::daisyQRadius() const
{
  return mSettings->daisy()->qRadius();
}

int SettingsModel::daisyQTheta() const
{
  return mSettings->daisy()->qTheta();
}

int SettingsModel::daisyQHist() const
{
  return mSettings->daisy()->qHist();
}

QString SettingsModel::daisyNorm() const
{
  return mSettings->daisy()->norm();
}

bool SettingsModel::daisyInterpolation() const
{
  return mSettings->daisy()->interpolation();
}

bool SettingsModel::daisyUseOrientation() const
{
  return mSettings->daisy()->useOrientation();
}

int SettingsModel::fastThreshold() const
{
  return mSettings->fast()->threshold();
}

bool SettingsModel::fastNonmaxSuppression() const
{
  return mSettings->fast()->nonmaxSuppression();
}

QString SettingsModel::fastdetectorType() const
{
  return mSettings->fast()->detectorType();
}

bool SettingsModel::freakOrientationNormalized() const
{
  return mSettings->freak()->orientationNormalized();
}

bool SettingsModel::freakScaleNormalized() const
{
  return mSettings->freak()->scaleNormalized();
}

double SettingsModel::freakPatternScale() const
{
  return mSettings->freak()->patternScale();
}

int SettingsModel::freakOctaves() const
{
  return mSettings->freak()->octaves();
}

int SettingsModel::gfttMaxFeatures() const
{
  return mSettings->gftt()->maxFeatures();
}

double SettingsModel::gfttQualityLevel() const
{
  return mSettings->gftt()->qualityLevel();
}

double SettingsModel::gfttMinDistance() const
{
  return mSettings->gftt()->minDistance();
}

int SettingsModel::gfttBlockSize() const
{
  return mSettings->gftt()->blockSize();
}

bool SettingsModel::gfttHarrisDetector() const
{
  return mSettings->gftt()->harrisDetector();
}

double SettingsModel::gfttK() const
{
  return mSettings->gftt()->k();
}

QSize SettingsModel::hogWinSize() const
{
  return mSettings->hog()->winSize();
}

QSize SettingsModel::hogBlockSize() const
{
  return mSettings->hog()->blockSize();
}

QSize SettingsModel::hogBlockStride() const
{
  return mSettings->hog()->blockStride();
}

QSize SettingsModel::hogCellSize() const
{
  return mSettings->hog()->cellSize();
}

int SettingsModel::hogNbins() const
{
  return mSettings->hog()->nbins();
}

int SettingsModel::hogDerivAperture() const
{
  return mSettings->hog()->derivAperture();
}

bool SettingsModel::kazeExtendedDescriptor() const
{
  return mSettings->kaze()->extendedDescriptor();
}

bool SettingsModel::kazeUpright() const
{
  return mSettings->kaze()->upright();
}

double SettingsModel::kazeThreshold() const
{
  return mSettings->kaze()->threshold();
}

int SettingsModel::kazeOctaves() const
{
  return mSettings->kaze()->octaves();
}

int SettingsModel::kazeOctaveLayers() const
{
  return mSettings->kaze()->octaveLayers();
}

QString SettingsModel::kazeDiffusivity() const
{
  return mSettings->kaze()->diffusivity();
}

QString SettingsModel::latchBytes() const
{
  return mSettings->latch()->bytes();
}

bool SettingsModel::latchRotationInvariance() const
{
  return mSettings->latch()->rotationInvariance();
}

int SettingsModel::latchHalfSsdSize() const
{
  return mSettings->latch()->halfSsdSize();
}

int SettingsModel::lucidKernel() const
{
  return mSettings->lucid()->lucidKernel();
}

int SettingsModel::lucidBlurKernel() const
{
  return mSettings->lucid()->blurKernel();
}

double SettingsModel::msdThresholdSaliency() const
{
  return mSettings->msd()->thresholdSaliency();
}

int SettingsModel::msdPathRadius() const
{
  return mSettings->msd()->patchRadius();
}

int SettingsModel::msdKnn() const
{
  return mSettings->msd()->knn();
}

int SettingsModel::msdAreaRadius() const
{
  return mSettings->msd()->searchAreaRadius();
}

double SettingsModel::msdScaleFactor() const
{
  return mSettings->msd()->scaleFactor();
}

int SettingsModel::msdNMSRadius() const
{
  return mSettings->msd()->NMSRadius();
}

int SettingsModel::msdNScales() const
{
  return mSettings->msd()->nScales();
}

int SettingsModel::msdNMSScaleR() const
{
  return mSettings->msd()->NMSScaleRadius();
}

bool SettingsModel::msdComputeOrientations() const
{
  return mSettings->msd()->computeOrientation();
}

bool SettingsModel::msdAffineMSD() const
{
  return mSettings->msd()->affineMSD();
}

int SettingsModel::msdTilts() const
{
  return mSettings->msd()->affineTilts();
}

int SettingsModel::mserDelta() const
{
  return mSettings->mser()->delta();
}

int SettingsModel::mserMinArea() const
{
  return mSettings->mser()->minArea();
}

int SettingsModel::mserMaxArea() const
{
  return mSettings->mser()->maxArea();
}

double SettingsModel::mserMaxVariation() const
{
  return mSettings->mser()->maxVariation();
}

double SettingsModel::mserMinDiversity() const
{
  return mSettings->mser()->minDiversity();
}

int SettingsModel::mserMaxEvolution() const
{
  return mSettings->mser()->maxEvolution();
}

double SettingsModel::mserAreaThreshold() const
{
  return mSettings->mser()->areaThreshold();
}

double SettingsModel::mserMinMargin() const
{
  return mSettings->mser()->minMargin();
}

int SettingsModel::mserEdgeBlurSize() const
{
  return mSettings->mser()->edgeBlurSize();
}

int SettingsModel::orbFeaturesNumber() const
{
  return mSettings->orb()->featuresNumber();
}

double SettingsModel::orbScaleFactor() const
{
  return mSettings->orb()->scaleFactor();
}

int SettingsModel::orbLevelsNumber() const
{
  return mSettings->orb()->levelsNumber();
}

int SettingsModel::orbEdgeThreshold() const
{
  return mSettings->orb()->edgeThreshold();
}

int SettingsModel::orbWta_k() const
{
  return mSettings->orb()->wta_k();
}

QString SettingsModel::orbScoreType() const
{
  return mSettings->orb()->scoreType();
}

int SettingsModel::orbPatchSize() const
{
  return mSettings->orb()->patchSize();
}

int SettingsModel::orbFastThreshold() const
{
  return mSettings->orb()->fastThreshold();
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

int SettingsModel::starMaxSize() const
{
  return mSettings->star()->maxSize();
}

int SettingsModel::starResponseThreshold() const
{
  return mSettings->star()->responseThreshold();
}

int SettingsModel::starLineThresholdProjected() const
{
  return mSettings->star()->lineThresholdProjected();
}

int SettingsModel::starLineThresholdBinarized() const
{
  return mSettings->star()->lineThresholdBinarized();
}

int SettingsModel::starSuppressNonmaxSize() const
{
  return mSettings->star()->suppressNonmaxSize();
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

QString SettingsModel::matchMethod() const
{
  return mSettings->matchMethod();
}

QString SettingsModel::matchNormType() const
{
  BruteForceMatcher::Norm norm = mSettings->bruteForceMatcher()->normType();
  QString s_norm = "NORM_L2";
  if (norm == BruteForceMatcherProperties::Norm::l1) {
    s_norm = "NORM_L1";
  } else if (norm == BruteForceMatcherProperties::Norm::l2) {
    s_norm = "NORM_L2";
  } else if (norm == BruteForceMatcherProperties::Norm::hamming) {
    s_norm = "NORM_HAMMING";
  } else if (norm == BruteForceMatcherProperties::Norm::hamming2) {
    s_norm = "NORM_HAMMING2";
  }

  return s_norm;
}

double SettingsModel::matchRatio() const
{
  return mSettings->robustMatcherRefinement()->ratio();
}

double SettingsModel::matchDistance() const
{
  return mSettings->robustMatcherRefinement()->distance();
}

double SettingsModel::matchConfidence() const
{
  return mSettings->robustMatcherRefinement()->confidence();
}

bool SettingsModel::matchCrossMatching() const
{
  return mSettings->robustMatcherRefinement()->crossCheck();
}

int SettingsModel::matchMaxIters() const
{
  return mSettings->robustMatcherRefinement()->maxIter();
}

QString SettingsModel::matchGeometricTest() const
{
  IRobustMatcherRefinement::GeometricTest geometric_test = mSettings->robustMatcherRefinement()->geometricTest();
  QString geometricTest = "Homography Matrix";
  if (geometric_test == IRobustMatcherRefinement::GeometricTest::homography) {
    geometricTest = "Homography Matrix";
  } else if (geometric_test == IRobustMatcherRefinement::GeometricTest::fundamental) {
    geometricTest = "Fundamental Matrix";
  } else if (geometric_test == IRobustMatcherRefinement::GeometricTest::essential) {
    geometricTest = "Essential Matrix";
  }
  return geometricTest;
}

QString SettingsModel::matchHomographyComputeMethod() const
{
  IRobustMatcherRefinement::HomographyComputeMethod computeMethod = mSettings->robustMatcherRefinement()->homographyComputeMethod();
  QString homographyComputeMethod = "RANSAC";
  if (computeMethod == IRobustMatcherRefinement::HomographyComputeMethod::all_points) {
    homographyComputeMethod = "All Points";
  } else if (computeMethod == IRobustMatcherRefinement::HomographyComputeMethod::ransac) {
    homographyComputeMethod = "RANSAC";
  } else if (computeMethod == IRobustMatcherRefinement::HomographyComputeMethod::lmeds) {
    homographyComputeMethod = "LMedS";
  } else if (computeMethod == IRobustMatcherRefinement::HomographyComputeMethod::rho) {
    homographyComputeMethod = "RHO";
  }
  return homographyComputeMethod;
}

QString SettingsModel::matchFundamentalComputeMethod() const
{
  IRobustMatcherRefinement::FundamentalComputeMethod computeMethod = mSettings->robustMatcherRefinement()->fundamentalComputeMethod();
  QString fundamentalComputeMethod = "RANSAC";
  if (computeMethod == IRobustMatcherRefinement::FundamentalComputeMethod::algorithm_7_point) {
    fundamentalComputeMethod = "7-point algorithm";
  } else if (computeMethod == IRobustMatcherRefinement::FundamentalComputeMethod::algorithm_8_point) {
    fundamentalComputeMethod = "8-point algorithm";
  } else if (computeMethod == IRobustMatcherRefinement::FundamentalComputeMethod::ransac) {
    fundamentalComputeMethod = "RANSAC";
  } else if (computeMethod == IRobustMatcherRefinement::FundamentalComputeMethod::lmeds) {
    fundamentalComputeMethod = "LMedS";
  }
  return fundamentalComputeMethod;
}

QString SettingsModel::matchEssentialComputeMethod() const
{
  IRobustMatcherRefinement::EssentialComputeMethod computeMethod = mSettings->robustMatcherRefinement()->essentialComputeMethod();
  QString essentialComputeMethod = "RANSAC";
  if (computeMethod == IRobustMatcherRefinement::EssentialComputeMethod::ransac) {
    essentialComputeMethod = "RANSAC";
  } else if (computeMethod == IRobustMatcherRefinement::EssentialComputeMethod::lmeds) {
    essentialComputeMethod = "LMedS";
  }
  return essentialComputeMethod;
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

void SettingsModel::setKeypointsFormat(const QString &format)
{
  mSettings->setKeypointsFormat(format);
  emit unsavedChanges(true);
}

void SettingsModel::setMatchesFormat(const QString &format)
{
  mSettings->setMatchesFormat(format);
  emit unsavedChanges(true);
}

void SettingsModel::setClaheClipLimit(double clipLimit)
{
  mSettings->clahe()->setClipLimit(clipLimit);
  emit unsavedChanges(true);
}

void SettingsModel::setClaheTilesGridSize(const QSize &tilesGridSize)
{
  mSettings->clahe()->setTilesGridSize(tilesGridSize);
  emit unsavedChanges(true);
}

void SettingsModel::setCmbfheBlockSize(const QSize &size)
{
  mSettings->cmbfhe()->setBlockSize(size);
  emit unsavedChanges(true);
}

void SettingsModel::setDheX(int x)
{
  mSettings->dhe()->setX(x);
  emit unsavedChanges(true);
}

void SettingsModel::setFaheBlockSize(const QSize &size)
{
  mSettings->fahe()->setBlockSize(size);
  emit unsavedChanges(true);
}

void SettingsModel::setAcebsfBlockSize(const QSize &blockSize)
{
  mSettings->acebsf()->setBlockSize(blockSize);
  emit unsavedChanges(true);
}

void SettingsModel::setAcebsfL(double l)
{
  mSettings->acebsf()->setL(l);
  emit unsavedChanges(true);
}

void SettingsModel::setAcebsfK1(double k1)
{
  mSettings->acebsf()->setK1(k1);
  emit unsavedChanges(true);
}

void SettingsModel::setAcebsfK2(double k2)
{
  mSettings->acebsf()->setK2(k2);
  emit unsavedChanges(true);
}

void SettingsModel::setHmclaheBlockSize(const QSize &size)
{
  mSettings->hmclahe()->setBlockSize(size);
  emit unsavedChanges(true);
}

void SettingsModel::setHmclaheL(double l)
{
  mSettings->hmclahe()->setL(l);
  emit unsavedChanges(true);
}

void SettingsModel::setHmclahePhi(double phi)
{
  mSettings->hmclahe()->setPhi(phi);
  emit unsavedChanges(true);
}

void SettingsModel::setLceBsescsBlockSize(const QSize &blockSize)
{
  mSettings->lceBsescs()->setBlockSize(blockSize);
  emit unsavedChanges(true);
}

void SettingsModel::setMsrcpSmallScale(double smallScale)
{
  mSettings->msrcp()->setSmallScale(smallScale);
  emit unsavedChanges(true);
}

void SettingsModel::setMsrcpMidScale(double midScale)
{
  mSettings->msrcp()->setMidScale(midScale);
  emit unsavedChanges(true);
}

void SettingsModel::setMsrcpLargeScale(double largeScale)
{
  mSettings->msrcp()->setLargeScale(largeScale);
  emit unsavedChanges(true);
}

void SettingsModel::setNoshpBlockSize(const QSize &blockSize)
{
  mSettings->noshp()->setBlockSize(blockSize);
  emit unsavedChanges(true);
}

void SettingsModel::setPoheBlockSize(const QSize &blockSize)
{
  mSettings->pohe()->setBlockSize(blockSize);
  emit unsavedChanges(true);
}

void SettingsModel::setRswheHistogramDivisions(int histogramDivisions)
{
  mSettings->rswhe()->setHistogramDivisions(histogramDivisions);
  emit unsavedChanges(true);
}

void SettingsModel::setRswheHistogramCut(int histogramCut)
{
  mSettings->rswhe()->setHistogramCut(static_cast<IRswhe::HistogramCut>(histogramCut));
  emit unsavedChanges(true);
}

void SettingsModel::setWallisContrast(double contrast)
{
  mSettings->wallis()->setContrast(contrast);
  emit unsavedChanges(true);
}

void SettingsModel::setWallisBrightness(double brightness)
{
  mSettings->wallis()->setBrightness(brightness);
  emit unsavedChanges(true);
}

void SettingsModel::setWallisImposedAverage(int imposedAverage)
{
  mSettings->wallis()->setImposedAverage(imposedAverage);
  emit unsavedChanges(true);
}

void SettingsModel::setWallisImposedLocalStdDev(int imposedLocalStdDev)
{
  mSettings->wallis()->setImposedLocalStdDev(imposedLocalStdDev);
  emit unsavedChanges(true);
}

void SettingsModel::setWallisKernelSize(int kernelSize)
{
  mSettings->wallis()->setKernelSize(kernelSize);
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

void SettingsModel::setBriefBytes(const QString &bytes)
{
  mSettings->brief()->setBytes(bytes);
  emit unsavedChanges(true);
}

void SettingsModel::setBriefUseOrientation(bool useOrientation)
{
  mSettings->brief()->setUseOrientation(useOrientation);
  emit unsavedChanges(true);
}

void SettingsModel::setBriskThreshold(int threshold)
{
  mSettings->brisk()->setThreshold(threshold);
  emit unsavedChanges(true);
}

void SettingsModel::setBriskOctaves(int octaves)
{
  mSettings->brisk()->setOctaves(octaves);
  emit unsavedChanges(true);
}

void SettingsModel::setBriskPatternScale(double patternScale)
{
  mSettings->brisk()->setPatternScale(patternScale);
  emit unsavedChanges(true);
}

void SettingsModel::setDaisyRadius(double radius)
{
  mSettings->daisy()->setRadius(radius);
  emit unsavedChanges(true);
}

void SettingsModel::setDaisyQRadius(int qRadius)
{
  mSettings->daisy()->setQRadius(qRadius);
  emit unsavedChanges(true);
}

void SettingsModel::setDaisyQTheta(int qTheta)
{
  mSettings->daisy()->setQTheta(qTheta);
  emit unsavedChanges(true);
}

void SettingsModel::setDaisyQHist(int qHist)
{
  mSettings->daisy()->setQHist(qHist);
  emit unsavedChanges(true);
}

void SettingsModel::setDaisyNorm(const QString &norm)
{
  mSettings->daisy()->setNorm(norm);
  emit unsavedChanges(true);
}

void SettingsModel::setDaisyInterpolation(bool interpolation)
{
  mSettings->daisy()->setInterpolation(interpolation);
  emit unsavedChanges(true);
}

void SettingsModel::setDaisyUseOrientation(bool useOrientation)
{
  mSettings->daisy()->setUseOrientation(useOrientation);
  emit unsavedChanges(true);
}

void SettingsModel::setFastThreshold(int threshold)
{
  mSettings->fast()->setThreshold(threshold);
  emit unsavedChanges(true);
}

void SettingsModel::setFastNonmaxSuppression(bool nonmaxSuppression)
{
  mSettings->fast()->setNonmaxSuppression(nonmaxSuppression);
  emit unsavedChanges(true);
}

void SettingsModel::setFastDetectorType(QString detectorType)
{
  mSettings->fast()->setDetectorType(detectorType);
  emit unsavedChanges(true);
}

void SettingsModel::setFreakOrientationNormalized(bool orientationNormalized)
{
  mSettings->freak()->setOrientationNormalized(orientationNormalized);
  emit unsavedChanges(true);
}

void SettingsModel::setFreakScaleNormalized(bool scaleNormalized)
{
  mSettings->freak()->setScaleNormalized(scaleNormalized);
  emit unsavedChanges(true);
}

void SettingsModel::setFreakPatternScale(double patternScale)
{
  mSettings->freak()->setPatternScale(patternScale);
  emit unsavedChanges(true);
}

void SettingsModel::setFreakOctaves(int octaves)
{
  mSettings->freak()->setOctaves(octaves);
  emit unsavedChanges(true);
}

void SettingsModel::setGfttMaxFeatures(int maxFeatures)
{
  mSettings->gftt()->setMaxFeatures(maxFeatures);
  emit unsavedChanges(true);
}

void SettingsModel::setGfttQualityLevel(double qlevel)
{
  mSettings->gftt()->setQualityLevel(qlevel);
  emit unsavedChanges(true);
}

void SettingsModel::setGfttMinDistance(double minDistance)
{
  mSettings->gftt()->setMinDistance(minDistance);
  emit unsavedChanges(true);
}

void SettingsModel::setGfttBlockSize(int blockSize)
{
  mSettings->gftt()->setBlockSize(blockSize);
  emit unsavedChanges(true);
}

void SettingsModel::setGfttHarrisDetector(bool value)
{
  mSettings->gftt()->setHarrisDetector(value);
  emit unsavedChanges(true);
}

void SettingsModel::setGfttK(double k)
{
  mSettings->gftt()->setK(k);
  emit unsavedChanges(true);
}

void SettingsModel::setHogWinSize(const QSize &winSize)
{
  mSettings->hog()->setWinSize(winSize);
  emit unsavedChanges(true);
}

void SettingsModel::setHogBlockSize(const QSize &blockSize)
{
  mSettings->hog()->setBlockSize(blockSize);
  emit unsavedChanges(true);
}

void SettingsModel::setHogBlockStride(const QSize &blockStride)
{
  mSettings->hog()->setBlockStride(blockStride);
  emit unsavedChanges(true);
}

void SettingsModel::setHogCellSize(const QSize &cellSize)
{
  mSettings->hog()->setCellSize(cellSize);
  emit unsavedChanges(true);
}

void SettingsModel::setHogNbins(int nbins)
{
  mSettings->hog()->setNbins(nbins);
  emit unsavedChanges(true);
}

void SettingsModel::setHogDerivAperture(int derivAperture)
{
  mSettings->hog()->setDerivAperture(derivAperture);
  emit unsavedChanges(true);
}

void SettingsModel::setKazeExtendedDescriptor(bool extended)
{
  mSettings->kaze()->setExtendedDescriptor(extended);
  emit unsavedChanges(true);
}

void SettingsModel::setKazeUpright(bool upright)
{
  mSettings->kaze()->setUpright(upright);
  emit unsavedChanges(true);
}

void SettingsModel::setKazeThreshold(double threshold)
{
  mSettings->kaze()->setThreshold(threshold);
  emit unsavedChanges(true);
}

void SettingsModel::setKazeOctaves(int octaves)
{
  mSettings->kaze()->setOctaves(octaves);
  emit unsavedChanges(true);
}

void SettingsModel::setKazeOctaveLayers(int octaveLayers)
{
  mSettings->kaze()->setOctaveLayers(octaveLayers);
  emit unsavedChanges(true);
}

void SettingsModel::setKazeDiffusivity(const QString &diffusivity)
{
  mSettings->kaze()->setDiffusivity(diffusivity);
  emit unsavedChanges(true);
}

void SettingsModel::setLatchBytes(const QString &bytes)
{
  mSettings->latch()->setBytes(bytes);
  emit unsavedChanges(true);
}

void SettingsModel::setLatchRotationInvariance(bool rotationInvariance)
{
  mSettings->latch()->setRotationInvariance(rotationInvariance);
  emit unsavedChanges(true);
}

void SettingsModel::setLatchHalfSsdSize(int halfSsdSize)
{
  mSettings->latch()->setHalfSsdSize(halfSsdSize);
  emit unsavedChanges(true);
}

void SettingsModel::setLucidKernel(int lucidKernel)
{
  mSettings->lucid()->setLucidKernel(lucidKernel);
  emit unsavedChanges(true);
}

void SettingsModel::setLucidBlurKernel(int blurKernel)
{
  mSettings->lucid()->setBlurKernel(blurKernel);
  emit unsavedChanges(true);
}

void SettingsModel::setMsdThresholdSaliency(double thresholdSaliency)
{
  mSettings->msd()->setThresholdSaliency(thresholdSaliency);
  emit unsavedChanges(true);
}

void SettingsModel::setMsdPathRadius(int pathRadius)
{
  mSettings->msd()->setPatchRadius(pathRadius);
  emit unsavedChanges(true);
}

void SettingsModel::setMsdKNN(int knn)
{
  mSettings->msd()->setKNN(knn);
  emit unsavedChanges(true);
}

void SettingsModel::setMsdAreaRadius(int areaRadius)
{
  mSettings->msd()->setSearchAreaRadius(areaRadius);
  emit unsavedChanges(true);
}

void SettingsModel::setMsdScaleFactor(double scaleFactor)
{
  mSettings->msd()->setScaleFactor(scaleFactor);
  emit unsavedChanges(true);
}

void SettingsModel::setMsdNMSRadius(int NMSRadius)
{
  mSettings->msd()->setNMSRadius(NMSRadius);
  emit unsavedChanges(true);
}

void SettingsModel::setMsdNScales(int nScales)
{
  mSettings->msd()->setNScales(nScales);
  emit unsavedChanges(true);
}

void SettingsModel::setMsdNMSScaleR(int NMSScaleR)
{
  mSettings->msd()->setNMSScaleRadius(NMSScaleR);
  emit unsavedChanges(true);
}

void SettingsModel::setMsdComputeOrientations(bool computeOrientations)
{
  mSettings->msd()->setComputeOrientation(computeOrientations);
  emit unsavedChanges(true);
}

void SettingsModel::setMsdAffineMSD(bool affineMSD)
{
  mSettings->msd()->setAffineMSD(affineMSD);
  emit unsavedChanges(true);
}

void SettingsModel::setMsdTilts(int tilts)
{
  mSettings->msd()->setAffineTilts(tilts);
  emit unsavedChanges(true);
}

void SettingsModel::setMserDelta(int delta)
{
  mSettings->mser()->setDelta(delta);
  emit unsavedChanges(true);
}

void SettingsModel::setMserMinArea(int minArea)
{
  mSettings->mser()->setMinArea(minArea);
  emit unsavedChanges(true);
}

void SettingsModel::setMserMaxArea(int maxArea)
{
  mSettings->mser()->setMaxArea(maxArea);
  emit unsavedChanges(true);
}

void SettingsModel::setMserMaxVariation(double maxVariation)
{
  mSettings->mser()->setMaxVariation(maxVariation);
  emit unsavedChanges(true);
}

void SettingsModel::setMserMinDiversity(double minDiversity)
{
  mSettings->mser()->setMinDiversity(minDiversity);
  emit unsavedChanges(true);
}

void SettingsModel::setMserMaxEvolution(int maxEvolution)
{
  mSettings->mser()->setMaxEvolution(maxEvolution);
  emit unsavedChanges(true);
}

void SettingsModel::setMserAreaThreshold(double areaThreshold)
{
  mSettings->mser()->setAreaThreshold(areaThreshold);
  emit unsavedChanges(true);
}

void SettingsModel::setMserMinMargin(double minMargin)
{
  mSettings->mser()->setMinMargin(minMargin);
  emit unsavedChanges(true);
}

void SettingsModel::setMserEdgeBlurSize(int edgeBlurSize)
{
  mSettings->mser()->setEdgeBlurSize(edgeBlurSize);
  emit unsavedChanges(true);
}

void SettingsModel::setOrbScaleFactor(double scaleFactor)
{
  mSettings->orb()->setScaleFactor(scaleFactor);
  emit unsavedChanges(true);
}

void SettingsModel::setOrbFeaturesNumber(int featuresNumber)
{
  mSettings->orb()->setFeaturesNumber(featuresNumber);
  emit unsavedChanges(true);
}

void SettingsModel::setOrbLevelsNumber(int levelsNumber)
{
  mSettings->orb()->setLevelsNumber(levelsNumber);
  emit unsavedChanges(true);
}

void SettingsModel::setOrbEdgeThreshold(int edgeThreshold)
{
  mSettings->orb()->setEdgeThreshold(edgeThreshold);
  emit unsavedChanges(true);
}

void SettingsModel::setOrbWTA_K(int WTA_K)
{
  mSettings->orb()->setWTA_K(WTA_K);
  emit unsavedChanges(true);
}

void SettingsModel::setOrbScoreType(const QString &scoreType)
{
  mSettings->orb()->setScoreType(scoreType);
  emit unsavedChanges(true);
}

void SettingsModel::setOrbPatchSize(int patchSize)
{
  mSettings->orb()->setPatchSize(patchSize);
  emit unsavedChanges(true);
}

void SettingsModel::setOrbFastThreshold(int fastThreshold)
{
  mSettings->orb()->setFastThreshold(fastThreshold);
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

void SettingsModel::setStarMaxSize(int maxSize)
{
  mSettings->star()->setMaxSize(maxSize);
  emit unsavedChanges(true);
}

void SettingsModel::setStarResponseThreshold(int responseThreshold)
{
  mSettings->star()->setResponseThreshold(responseThreshold);
  emit unsavedChanges(true);
}

void SettingsModel::setStarLineThresholdProjected(int lineThresholdProjected)
{
  mSettings->star()->setLineThresholdProjected(lineThresholdProjected);
  emit unsavedChanges(true);
}

void SettingsModel::setStarLineThresholdBinarized(int lineThresholdBinarized)
{
  mSettings->star()->setLineThresholdBinarized(lineThresholdBinarized);
  emit unsavedChanges(true);
}

void SettingsModel::setStarSuppressNonmaxSize(int suppressNonmaxSize)
{
  mSettings->star()->setSuppressNonmaxSize(suppressNonmaxSize);
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

void SettingsModel::setMatchMethod(const QString &matchingMethod)
{
  mSettings->setMatchMethod(matchingMethod);
  emit unsavedChanges(true);
}

void SettingsModel::setMatchNormType(const QString &normType)
{
  BruteForceMatcher::Norm norm = BruteForceMatcherProperties::Norm::l2;
  if (normType.compare("NORM_L1") == 0) {
    norm = BruteForceMatcherProperties::Norm::l1;
  } else if (normType.compare("NORM_L2") == 0) {
    norm = BruteForceMatcherProperties::Norm::l2;
  } else if (normType.compare("NORM_HAMMING") == 0) {
    norm = BruteForceMatcherProperties::Norm::hamming;
  } else if (normType.compare("NORM_HAMMING2") == 0) {
    norm = BruteForceMatcherProperties::Norm::hamming2;
  }
  mSettings->bruteForceMatcher()->setNormType(norm);
  emit unsavedChanges(true);
}

void SettingsModel::setMatchRatio(double ratio)
{
  mSettings->robustMatcherRefinement()->setRatio(ratio);
  emit unsavedChanges(true);
}

void SettingsModel::setMatchDistance(double distance)
{
  mSettings->robustMatcherRefinement()->setDistance(distance);
  emit unsavedChanges(true);
}

void SettingsModel::setMatchConfidence(double confidence)
{
  mSettings->robustMatcherRefinement()->setConfidence(confidence);
  emit unsavedChanges(true);
}

void SettingsModel::setMatchCrossMatching(bool crossMatching)
{
  mSettings->robustMatcherRefinement()->setCrossCheck(crossMatching);
  emit unsavedChanges(true);
}

void SettingsModel::setMatchMaxIters(int maxIters)
{
  mSettings->robustMatcherRefinement()->setMaxIters(maxIters);
  emit unsavedChanges(true);
}

void SettingsModel::setMatchGeometricTest(const QString &geometricTest)
{
  IRobustMatcherRefinement::GeometricTest geometric_test = IRobustMatcherRefinement::GeometricTest::homography;
  if (geometricTest.compare("Homography Matrix") == 0) {
    geometric_test = IRobustMatcherRefinement::GeometricTest::homography;
  } else if (geometricTest.compare("Fundamental Matrix") == 0) {
    geometric_test = IRobustMatcherRefinement::GeometricTest::fundamental;
  } else if (geometricTest.compare("Essential Matrix") == 0) {
    geometric_test = IRobustMatcherRefinement::GeometricTest::essential;
  }
  mSettings->robustMatcherRefinement()->setGeometricTest(geometric_test);
  emit unsavedChanges(true);
}

void SettingsModel::setMatchHomographyComputeMethod(const QString &computeMethod)
{
  IRobustMatcherRefinement::HomographyComputeMethod homographyComputeMethod = IRobustMatcherRefinement::HomographyComputeMethod::ransac;
  if (computeMethod.compare("All Points") == 0) {
    homographyComputeMethod = IRobustMatcherRefinement::HomographyComputeMethod::all_points;
  } else if (computeMethod.compare("RANSAC") == 0) {
    homographyComputeMethod = IRobustMatcherRefinement::HomographyComputeMethod::ransac;
  } else if (computeMethod.compare("LMedS") == 0) {
    homographyComputeMethod = IRobustMatcherRefinement::HomographyComputeMethod::lmeds;
  } else if (computeMethod.compare("RHO") == 0) {
    homographyComputeMethod = IRobustMatcherRefinement::HomographyComputeMethod::rho;
  }
  mSettings->robustMatcherRefinement()->setHomographyComputeMethod(homographyComputeMethod);
  emit unsavedChanges(true);
}

void SettingsModel::setMatchFundamentalComputeMethod(const QString &computeMethod)
{
  IRobustMatcherRefinement::FundamentalComputeMethod fundamentalComputeMethod = IRobustMatcherRefinement::FundamentalComputeMethod::ransac;
  if (computeMethod.compare("7-point algorithm") == 0) {
    fundamentalComputeMethod = IRobustMatcherRefinement::FundamentalComputeMethod::algorithm_7_point;
  } else if (computeMethod.compare("8-point algorithm") == 0) {
    fundamentalComputeMethod = IRobustMatcherRefinement::FundamentalComputeMethod::algorithm_8_point;
  } else if (computeMethod.compare("RANSAC") == 0) {
    fundamentalComputeMethod = IRobustMatcherRefinement::FundamentalComputeMethod::ransac;
  } else if (computeMethod.compare("LMedS") == 0) {
    fundamentalComputeMethod = IRobustMatcherRefinement::FundamentalComputeMethod::lmeds;
  }
  mSettings->robustMatcherRefinement()->setFundamentalComputeMethod(fundamentalComputeMethod);
  emit unsavedChanges(true);
}

void SettingsModel::setMatchEssentialComputeMethod(const QString &computeMethod)
{
  IRobustMatcherRefinement::EssentialComputeMethod essentialComputeMethod = IRobustMatcherRefinement::EssentialComputeMethod::ransac;
  if (computeMethod.compare("RANSAC") == 0) {
    essentialComputeMethod = IRobustMatcherRefinement::EssentialComputeMethod::ransac;
  } else if (computeMethod.compare("LMedS") == 0) {
    essentialComputeMethod = IRobustMatcherRefinement::EssentialComputeMethod::lmeds;
  }
  mSettings->robustMatcherRefinement()->setEssentialComputeMethod(essentialComputeMethod);
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

  QStringList lang_list = QDir(langPath).entryList(QStringList("photomatch_*.qm"));
  if (lang_list.size() == 0)
    lang_list.push_back("photomatch_en.qm");
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

} // namespace photomatch
