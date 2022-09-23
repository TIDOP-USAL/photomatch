/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#include "SettingsModel.h"

#include "photomatch/core/features/agast.h"
#include "photomatch/core/features/akaze.h"
#include "photomatch/core/features/boost.h"
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
#include "photomatch/core/features/vgg.h"
#include "photomatch/core/features/flann.h"
#include "photomatch/core/features/bfmatch.h"
#include "photomatch/core/features/robustmatch.h"
#include "photomatch/core/features/gsm.h"
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

SettingsModelImp::SettingsModelImp(Settings *settings,
                                   SettingsController *settingsRW,
                                   QObject *parent)
  : SettingsModel(parent),
    mSettings(settings),
    mSettingsRW(settingsRW)
{
  init();
}

SettingsModelImp::~SettingsModelImp()
{
}

QString SettingsModelImp::language() const
{
  return mSettings->language();
}

QStringList SettingsModelImp::history() const
{
  return mSettings->history();
}

int SettingsModelImp::historyMaxSize() const
{
  return mSettings->historyMaxSize();
}

QString SettingsModelImp::imageViewerBGcolor() const
{
  return mSettings->imageViewerBGcolor();
}

QString SettingsModelImp::keypointsFormat() const
{
  return mSettings->keypointsFormat();
}

QString SettingsModelImp::matchesFormat() const
{
  return mSettings->matchesFormat();
}

bool SettingsModelImp::useCuda() const
{
  return mSettings->useCuda();
}

QSize SettingsModelImp::acebsfBlockSize() const
{
  return mSettings->acebsf()->blockSize();
}

double SettingsModelImp::acebsfL() const
{
  return mSettings->acebsf()->l();
}

double SettingsModelImp::acebsfK1() const
{
  return mSettings->acebsf()->k1();
}

double SettingsModelImp::acebsfK2() const
{
  return mSettings->acebsf()->k2();
}

double SettingsModelImp::claheClipLimit() const
{
  return mSettings->clahe()->clipLimit();
}

QSize SettingsModelImp::claheTilesGridSize() const
{
  return mSettings->clahe()->tilesGridSize();
}

QSize SettingsModelImp::cmbfheBlockSize() const
{
  return mSettings->cmbfhe()->blockSize();
}

int SettingsModelImp::dheX() const
{
  return mSettings->dhe()->x();
}

QSize SettingsModelImp::faheBlockSize() const
{
  return mSettings->fahe()->blockSize();
}

QSize SettingsModelImp::hmclaheBlockSize() const
{
  return mSettings->hmclahe()->blockSize();
}

double SettingsModelImp::hmclaheL() const
{
  return mSettings->hmclahe()->l();
}

double SettingsModelImp::hmclahePhi() const
{
  return mSettings->hmclahe()->phi();
}

QSize SettingsModelImp::lceBsescsBlockSize() const
{
  return mSettings->lceBsescs()->blockSize();
}

double SettingsModelImp::msrcpSmallScale() const
{
  return mSettings->msrcp()->smallScale();
}

double SettingsModelImp::msrcpMidScale() const
{
  return mSettings->msrcp()->midScale();
}

double SettingsModelImp::msrcpLargeScale() const
{
  return mSettings->msrcp()->largeScale();
}

QSize SettingsModelImp::noshpBlockSize() const
{
  return mSettings->noshp()->blockSize();
}

QSize SettingsModelImp::poheBlockSize() const
{
  return mSettings->pohe()->blockSize();
}

int SettingsModelImp::rswheHistogramDivisions() const
{
  return mSettings->rswhe()->histogramDivisions();
}

int SettingsModelImp::rswheHistogramCut() const
{
  return static_cast<int>(mSettings->rswhe()->histogramCut());
}

double SettingsModelImp::wallisContrast() const
{
  return mSettings->wallis()->contrast();
}

double SettingsModelImp::wallisBrightness() const
{
  return mSettings->wallis()->brightness();
}

int SettingsModelImp::wallisImposedAverage() const
{
  return mSettings->wallis()->imposedAverage();
}

int SettingsModelImp::wallisImposedLocalStdDev() const
{
  return mSettings->wallis()->imposedLocalStdDev();
}

int SettingsModelImp::wallisKernelSize() const
{
  return mSettings->wallis()->kernelSize();
}

int SettingsModelImp::agastThreshold() const
{
  return mSettings->agast()->threshold();
}

bool SettingsModelImp::agastNonmaxSuppression() const
{
  return mSettings->agast()->nonmaxSuppression();
}

QString SettingsModelImp::agastDetectorType() const
{
  return mSettings->agast()->detectorType();
}

QString SettingsModelImp::akazeDescriptorType() const
{
  return mSettings->akaze()->descriptorType();
}

int SettingsModelImp::akazeDescriptorSize() const
{
  return mSettings->akaze()->descriptorSize();
}

int SettingsModelImp::akazeDescriptorChannels() const
{
  return mSettings->akaze()->descriptorChannels();
}

double SettingsModelImp::akazeThreshold() const
{
  return mSettings->akaze()->threshold();
}

int SettingsModelImp::akazeOctaves() const
{
  return mSettings->akaze()->octaves();
}

int SettingsModelImp::akazeOctaveLayers() const
{
  return mSettings->akaze()->octaveLayers();
}

QString SettingsModelImp::akazeDiffusivity() const
{
  return mSettings->akaze()->diffusivity();
}

int SettingsModelImp::asiftFeaturesNumber() const
{
  return mSettings->asift()->featuresNumber();
}

int SettingsModelImp::asiftOctaveLayers() const
{
  return mSettings->asift()->octaveLayers();
}

double SettingsModelImp::asiftContrastThreshold() const
{
  return mSettings->asift()->contrastThreshold();
}

double SettingsModelImp::asiftEdgeThreshold() const
{
  return mSettings->asift()->edgeThreshold();
}

double SettingsModelImp::asiftSigma() const
{
  return mSettings->asift()->sigma();
}

int SettingsModelImp::asiftMinTilt() const
{
  return mSettings->asift()->minTilt();
}

int SettingsModelImp::asiftMaxTilt() const
{
  return mSettings->asift()->maxTilt();
}

QString SettingsModelImp::boostDescriptorType() const
{
  return mSettings->boost()->descriptorType();
}

bool SettingsModelImp::boostUseOrientation() const
{
  return mSettings->boost()->useOrientation();
}

double SettingsModelImp::boostScaleFactor() const
{
  return mSettings->boost()->scaleFactor();
}

QString SettingsModelImp::briefBytes() const
{
  return mSettings->brief()->bytes();
}

bool SettingsModelImp::briefUseOrientation() const
{
  return mSettings->brief()->useOrientation();
}

int SettingsModelImp::briskThreshold() const
{
  return mSettings->brisk()->threshold();
}

int SettingsModelImp::briskOctaves() const
{
  return mSettings->brisk()->octaves();
}

double SettingsModelImp::briskPatternScale() const
{
  return mSettings->brisk()->patternScale();
}

double SettingsModelImp::daisyRadius() const
{
  return mSettings->daisy()->radius();
}

int SettingsModelImp::daisyQRadius() const
{
  return mSettings->daisy()->qRadius();
}

int SettingsModelImp::daisyQTheta() const
{
  return mSettings->daisy()->qTheta();
}

int SettingsModelImp::daisyQHist() const
{
  return mSettings->daisy()->qHist();
}

QString SettingsModelImp::daisyNorm() const
{
  return mSettings->daisy()->norm();
}

bool SettingsModelImp::daisyInterpolation() const
{
  return mSettings->daisy()->interpolation();
}

bool SettingsModelImp::daisyUseOrientation() const
{
  return mSettings->daisy()->useOrientation();
}

int SettingsModelImp::fastThreshold() const
{
  return mSettings->fast()->threshold();
}

bool SettingsModelImp::fastNonmaxSuppression() const
{
  return mSettings->fast()->nonmaxSuppression();
}

QString SettingsModelImp::fastdetectorType() const
{
  return mSettings->fast()->detectorType();
}

bool SettingsModelImp::freakOrientationNormalized() const
{
  return mSettings->freak()->orientationNormalized();
}

bool SettingsModelImp::freakScaleNormalized() const
{
  return mSettings->freak()->scaleNormalized();
}

double SettingsModelImp::freakPatternScale() const
{
  return mSettings->freak()->patternScale();
}

int SettingsModelImp::freakOctaves() const
{
  return mSettings->freak()->octaves();
}

int SettingsModelImp::gfttMaxFeatures() const
{
  return mSettings->gftt()->maxFeatures();
}

double SettingsModelImp::gfttQualityLevel() const
{
  return mSettings->gftt()->qualityLevel();
}

double SettingsModelImp::gfttMinDistance() const
{
  return mSettings->gftt()->minDistance();
}

int SettingsModelImp::gfttBlockSize() const
{
  return mSettings->gftt()->blockSize();
}

bool SettingsModelImp::gfttHarrisDetector() const
{
  return mSettings->gftt()->harrisDetector();
}

double SettingsModelImp::gfttK() const
{
  return mSettings->gftt()->k();
}

QSize SettingsModelImp::hogWinSize() const
{
  return mSettings->hog()->winSize();
}

QSize SettingsModelImp::hogBlockSize() const
{
  return mSettings->hog()->blockSize();
}

QSize SettingsModelImp::hogBlockStride() const
{
  return mSettings->hog()->blockStride();
}

QSize SettingsModelImp::hogCellSize() const
{
  return mSettings->hog()->cellSize();
}

int SettingsModelImp::hogNbins() const
{
  return mSettings->hog()->nbins();
}

int SettingsModelImp::hogDerivAperture() const
{
  return mSettings->hog()->derivAperture();
}

bool SettingsModelImp::kazeExtendedDescriptor() const
{
  return mSettings->kaze()->extendedDescriptor();
}

bool SettingsModelImp::kazeUpright() const
{
  return mSettings->kaze()->uprightDescriptor();
}

double SettingsModelImp::kazeThreshold() const
{
  return mSettings->kaze()->threshold();
}

int SettingsModelImp::kazeOctaves() const
{
  return mSettings->kaze()->octaves();
}

int SettingsModelImp::kazeOctaveLayers() const
{
  return mSettings->kaze()->octaveLayers();
}

QString SettingsModelImp::kazeDiffusivity() const
{
  return mSettings->kaze()->diffusivity();
}

QString SettingsModelImp::latchBytes() const
{
  return mSettings->latch()->bytes();
}

bool SettingsModelImp::latchRotationInvariance() const
{
  return mSettings->latch()->rotationInvariance();
}

int SettingsModelImp::latchHalfSsdSize() const
{
  return mSettings->latch()->halfSsdSize();
}

int SettingsModelImp::lucidKernel() const
{
  return mSettings->lucid()->lucidKernel();
}

int SettingsModelImp::lucidBlurKernel() const
{
  return mSettings->lucid()->blurKernel();
}

double SettingsModelImp::msdThresholdSaliency() const
{
  return mSettings->msd()->thresholdSaliency();
}

int SettingsModelImp::msdPathRadius() const
{
  return mSettings->msd()->patchRadius();
}

int SettingsModelImp::msdKnn() const
{
  return mSettings->msd()->knn();
}

int SettingsModelImp::msdAreaRadius() const
{
  return mSettings->msd()->searchAreaRadius();
}

double SettingsModelImp::msdScaleFactor() const
{
  return mSettings->msd()->scaleFactor();
}

int SettingsModelImp::msdNMSRadius() const
{
  return mSettings->msd()->NMSRadius();
}

int SettingsModelImp::msdNScales() const
{
  return mSettings->msd()->nScales();
}

int SettingsModelImp::msdNMSScaleR() const
{
  return mSettings->msd()->NMSScaleRadius();
}

bool SettingsModelImp::msdComputeOrientations() const
{
  return mSettings->msd()->computeOrientation();
}

bool SettingsModelImp::msdAffineMSD() const
{
  return mSettings->msd()->affineMSD();
}

int SettingsModelImp::msdTilts() const
{
  return mSettings->msd()->affineTilts();
}

int SettingsModelImp::mserDelta() const
{
  return mSettings->mser()->delta();
}

int SettingsModelImp::mserMinArea() const
{
  return mSettings->mser()->minArea();
}

int SettingsModelImp::mserMaxArea() const
{
  return mSettings->mser()->maxArea();
}

double SettingsModelImp::mserMaxVariation() const
{
  return mSettings->mser()->maxVariation();
}

double SettingsModelImp::mserMinDiversity() const
{
  return mSettings->mser()->minDiversity();
}

int SettingsModelImp::mserMaxEvolution() const
{
  return mSettings->mser()->maxEvolution();
}

double SettingsModelImp::mserAreaThreshold() const
{
  return mSettings->mser()->areaThreshold();
}

double SettingsModelImp::mserMinMargin() const
{
  return mSettings->mser()->minMargin();
}

int SettingsModelImp::mserEdgeBlurSize() const
{
  return mSettings->mser()->edgeBlurSize();
}

int SettingsModelImp::orbFeaturesNumber() const
{
  return mSettings->orb()->featuresNumber();
}

double SettingsModelImp::orbScaleFactor() const
{
  return mSettings->orb()->scaleFactor();
}

int SettingsModelImp::orbLevelsNumber() const
{
  return mSettings->orb()->levelsNumber();
}

int SettingsModelImp::orbEdgeThreshold() const
{
  return mSettings->orb()->edgeThreshold();
}

int SettingsModelImp::orbWta_k() const
{
  return mSettings->orb()->wta_k();
}

QString SettingsModelImp::orbScoreType() const
{
  return mSettings->orb()->scoreType();
}

int SettingsModelImp::orbPatchSize() const
{
  return mSettings->orb()->patchSize();
}

int SettingsModelImp::orbFastThreshold() const
{
  return mSettings->orb()->fastThreshold();
}

int SettingsModelImp::siftFeaturesNumber() const
{
  return mSettings->sift()->featuresNumber();
}

int SettingsModelImp::siftOctaveLayers() const
{
  return mSettings->sift()->octaveLayers();
}

double SettingsModelImp::siftContrastThreshold() const
{
  return mSettings->sift()->contrastThreshold();
}

double SettingsModelImp::siftEdgeThreshold() const
{
  return mSettings->sift()->edgeThreshold();
}

double SettingsModelImp::siftSigma() const
{
  return mSettings->sift()->sigma();
}

int SettingsModelImp::starMaxSize() const
{
  return mSettings->star()->maxSize();
}

int SettingsModelImp::starResponseThreshold() const
{
  return mSettings->star()->responseThreshold();
}

int SettingsModelImp::starLineThresholdProjected() const
{
  return mSettings->star()->lineThresholdProjected();
}

int SettingsModelImp::starLineThresholdBinarized() const
{
  return mSettings->star()->lineThresholdBinarized();
}

int SettingsModelImp::starSuppressNonmaxSize() const
{
  return mSettings->star()->suppressNonmaxSize();
}

double SettingsModelImp::surfHessianThreshold() const
{
  return mSettings->surf()->hessianThreshold();
}

int SettingsModelImp::surfOctaves() const
{
  return mSettings->surf()->octaves();
}

int SettingsModelImp::surfOctaveLayers() const
{
  return mSettings->surf()->octaveLayers();
}

bool SettingsModelImp::surfExtendedDescriptor() const
{
  return mSettings->surf()->extendedDescriptor();
}

bool SettingsModelImp::surfRotatedFeatures() const
{
  return mSettings->surf()->upright();
}

QString SettingsModelImp::vggDescriptorType() const
{
  return mSettings->vgg()->descriptorType();
}

double SettingsModelImp::vggScaleFactor() const
{
  return mSettings->vgg()->scaleFactor();
}

double SettingsModelImp::vggSigma() const
{
  return mSettings->vgg()->sigma();
}

bool SettingsModelImp::vggUseNormalizeDescriptor() const
{
  return mSettings->vgg()->useNormalizeDescriptor();
}

bool SettingsModelImp::vggUseNormalizeImage() const
{
  return mSettings->vgg()->useNormalizeImage();
}

bool SettingsModelImp::vggUseScaleOrientation() const
{
  return mSettings->vgg()->useScaleOrientation();
}

QString SettingsModelImp::matchMethod() const
{
  return mSettings->matchMethod();
}

QString SettingsModelImp::matchStrategy() const
{
  return mSettings->matchStrategy();
}

QString SettingsModelImp::matchNormType() const
{
  BruteForceMatcherImp::Norm norm = mSettings->bruteForceMatcher()->normType();
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

double SettingsModelImp::matchRatio() const
{
  return mSettings->robustMatcher()->ratio();
}

double SettingsModelImp::matchDistance() const
{
  return mSettings->robustMatcher()->distance();
}

double SettingsModelImp::matchConfidence() const
{
  return mSettings->robustMatcher()->confidence();
}

bool SettingsModelImp::matchCrossMatching() const
{
  return mSettings->robustMatcher()->crossCheck();
}

int SettingsModelImp::matchMaxIters() const
{
  return mSettings->robustMatcher()->maxIter();
}

QString SettingsModelImp::matchGeometricTest() const
{
  RobustMatcher::GeometricTest geometric_test = mSettings->robustMatcher()->geometricTest();
  QString geometricTest = "Homography Matrix";
  if (geometric_test == RobustMatcher::GeometricTest::homography) {
    geometricTest = "Homography Matrix";
  } else if (geometric_test == RobustMatcher::GeometricTest::fundamental) {
    geometricTest = "Fundamental Matrix";
  } else if (geometric_test == RobustMatcher::GeometricTest::essential) {
    geometricTest = "Essential Matrix";
  }
  return geometricTest;
}

QString SettingsModelImp::matchHomographyComputeMethod() const
{
  RobustMatcher::HomographyComputeMethod computeMethod = mSettings->robustMatcher()->homographyComputeMethod();
  QString homographyComputeMethod = "RANSAC";
  if (computeMethod == RobustMatcher::HomographyComputeMethod::all_points) {
    homographyComputeMethod = "All Points";
  } else if (computeMethod == RobustMatcher::HomographyComputeMethod::ransac) {
    homographyComputeMethod = "RANSAC";
  } else if (computeMethod == RobustMatcher::HomographyComputeMethod::lmeds) {
    homographyComputeMethod = "LMedS";
  } else if (computeMethod == RobustMatcher::HomographyComputeMethod::rho) {
    homographyComputeMethod = "RHO";
  }
  return homographyComputeMethod;
}

QString SettingsModelImp::matchFundamentalComputeMethod() const
{
  RobustMatcher::FundamentalComputeMethod computeMethod = mSettings->robustMatcher()->fundamentalComputeMethod();
  QString fundamentalComputeMethod = "RANSAC";
  if (computeMethod == RobustMatcher::FundamentalComputeMethod::algorithm_7_point) {
    fundamentalComputeMethod = "7-point algorithm";
  } else if (computeMethod == RobustMatcher::FundamentalComputeMethod::algorithm_8_point) {
    fundamentalComputeMethod = "8-point algorithm";
  } else if (computeMethod == RobustMatcher::FundamentalComputeMethod::ransac) {
    fundamentalComputeMethod = "RANSAC";
  } else if (computeMethod == RobustMatcher::FundamentalComputeMethod::lmeds) {
    fundamentalComputeMethod = "LMedS";
  }
  return fundamentalComputeMethod;
}

QString SettingsModelImp::matchEssentialComputeMethod() const
{
  RobustMatcher::EssentialComputeMethod computeMethod = mSettings->robustMatcher()->essentialComputeMethod();
  QString essentialComputeMethod = "RANSAC";
  if (computeMethod == RobustMatcher::EssentialComputeMethod::ransac) {
    essentialComputeMethod = "RANSAC";
  } else if (computeMethod == RobustMatcher::EssentialComputeMethod::lmeds) {
    essentialComputeMethod = "LMedS";
  }
  return essentialComputeMethod;
}

QString SettingsModelImp::keypointsViewerBGColor() const
{
  return mSettings->keypointsViewerBGColor();
}

int SettingsModelImp::keypointsViewerMarkerType() const
{
  return mSettings->keypointsViewerMarkerType();
}

int SettingsModelImp::keypointsViewerMarkerSize() const
{
  return mSettings->keypointsViewerMarkerSize();
}

int SettingsModelImp::keypointsViewerMarkerWidth() const
{
  return mSettings->keypointsViewerMarkerWidth();
}

QString SettingsModelImp::keypointsViewerMarkerColor() const
{
  return mSettings->keypointsViewerMarkerColor();
}

int SettingsModelImp::keypointsViewerSelectMarkerWidth() const
{
  return mSettings->keypointsViewerSelectMarkerWidth();
}

QString SettingsModelImp::keypointsViewerSelectMarkerColor() const
{
  return mSettings->keypointsViewerSelectMarkerColor();
}

QString SettingsModelImp::matchesViewerBGColor() const
{
  return mSettings->matchesViewerBGColor();
}

int SettingsModelImp::matchesViewerMarkerType() const
{
  return mSettings->matchesViewerMarkerType();
}

int SettingsModelImp::matchesViewerMarkerSize() const
{
  return mSettings->matchesViewerMarkerSize();
}

int SettingsModelImp::matchesViewerMarkerWidth() const
{
  return mSettings->matchesViewerMarkerWidth();
}

QString SettingsModelImp::matchesViewerMarkerColor() const
{
  return mSettings->matchesViewerMarkerColor();
}

int SettingsModelImp::matchesViewerSelectMarkerWidth() const
{
  return mSettings->matchesViewerSelectMarkerWidth();
}

QString SettingsModelImp::matchesViewerSelectMarkerColor() const
{
  return mSettings->matchesViewerSelectMarkerColor();
}

QString SettingsModelImp::matchesViewerLineColor() const
{
  return mSettings->matchesViewerLineColor();
}

int SettingsModelImp::matchesViewerLineWidth() const
{
  return mSettings->matchesViewerLineWidth();
}

QString SettingsModelImp::groundTruthEditorBGColor() const
{
  return mSettings->groundTruthEditorBGColor();
}

int SettingsModelImp::groundTruthEditorMarkerSize() const
{
  return mSettings->groundTruthEditorMarkerSize();
}

int SettingsModelImp::groundTruthEditorMarkerWidth() const
{
  return mSettings->groundTruthEditorMarkerWidth();
}

QString SettingsModelImp::groundTruthEditorMarkerColor() const
{
  return mSettings->groundTruthEditorMarkerColor();
}

int SettingsModelImp::groundTruthEditorSelectMarkerWidth() const
{
  return mSettings->groundTruthEditorSelectMarkerWidth();
}

QString SettingsModelImp::groundTruthEditorSelectMarkerColor() const
{
  return mSettings->groundTruthEditorSelectMarkerColor();
}

QString SettingsModelImp::groundTruthEditorMatrixAdjust() const
{
  return mSettings->groundTruthEditorMatrixAdjust();
}

void SettingsModelImp::setLanguage(const QString &language)
{
  mSettings->setLanguage(language);
  emit unsavedChanges(true);
}

void SettingsModelImp::addToHistory(const QString &project)
{
  mSettings->addToHistory(project);
  mSettingsRW->writeHistory(*mSettings);
}

void SettingsModelImp::clearHistory()
{
  mSettings->clearHistory();
  mSettingsRW->writeHistory(*mSettings);
}

void SettingsModelImp::setHistoryMaxSize(int maxSize)
{
  mSettings->setHistoryMaxSize(maxSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setImageViewerBGcolor(const QString &bgColor)
{
  mSettings->setImageViewerBGcolor(bgColor);
  emit unsavedChanges(true);
}

void SettingsModelImp::setKeypointsFormat(const QString &format)
{
  mSettings->setKeypointsFormat(format);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchesFormat(const QString &format)
{
  mSettings->setMatchesFormat(format);
  emit unsavedChanges(true);
}

void SettingsModelImp::setClaheClipLimit(double clipLimit)
{
  mSettings->clahe()->setClipLimit(clipLimit);
  emit unsavedChanges(true);
}

void SettingsModelImp::setClaheTilesGridSize(const QSize &tilesGridSize)
{
  mSettings->clahe()->setTilesGridSize(tilesGridSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setCmbfheBlockSize(const QSize &size)
{
  mSettings->cmbfhe()->setBlockSize(size);
  emit unsavedChanges(true);
}

void SettingsModelImp::setDheX(int x)
{
  mSettings->dhe()->setX(x);
  emit unsavedChanges(true);
}

void SettingsModelImp::setFaheBlockSize(const QSize &size)
{
  mSettings->fahe()->setBlockSize(size);
  emit unsavedChanges(true);
}

void SettingsModelImp::setUseCuda(bool active)
{
  mSettings->setUseCuda(active);
  emit unsavedChanges(true);
}

void SettingsModelImp::setAcebsfBlockSize(const QSize &blockSize)
{
  mSettings->acebsf()->setBlockSize(blockSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setAcebsfL(double l)
{
  mSettings->acebsf()->setL(l);
  emit unsavedChanges(true);
}

void SettingsModelImp::setAcebsfK1(double k1)
{
  mSettings->acebsf()->setK1(k1);
  emit unsavedChanges(true);
}

void SettingsModelImp::setAcebsfK2(double k2)
{
  mSettings->acebsf()->setK2(k2);
  emit unsavedChanges(true);
}

void SettingsModelImp::setHmclaheBlockSize(const QSize &size)
{
  mSettings->hmclahe()->setBlockSize(size);
  emit unsavedChanges(true);
}

void SettingsModelImp::setHmclaheL(double l)
{
  mSettings->hmclahe()->setL(l);
  emit unsavedChanges(true);
}

void SettingsModelImp::setHmclahePhi(double phi)
{
  mSettings->hmclahe()->setPhi(phi);
  emit unsavedChanges(true);
}

void SettingsModelImp::setLceBsescsBlockSize(const QSize &blockSize)
{
  mSettings->lceBsescs()->setBlockSize(blockSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMsrcpSmallScale(double smallScale)
{
  mSettings->msrcp()->setSmallScale(smallScale);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMsrcpMidScale(double midScale)
{
  mSettings->msrcp()->setMidScale(midScale);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMsrcpLargeScale(double largeScale)
{
  mSettings->msrcp()->setLargeScale(largeScale);
  emit unsavedChanges(true);
}

void SettingsModelImp::setNoshpBlockSize(const QSize &blockSize)
{
  mSettings->noshp()->setBlockSize(blockSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setPoheBlockSize(const QSize &blockSize)
{
  mSettings->pohe()->setBlockSize(blockSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setRswheHistogramDivisions(int histogramDivisions)
{
  mSettings->rswhe()->setHistogramDivisions(histogramDivisions);
  emit unsavedChanges(true);
}

void SettingsModelImp::setRswheHistogramCut(int histogramCut)
{
  mSettings->rswhe()->setHistogramCut(static_cast<Rswhe::HistogramCut>(histogramCut));
  emit unsavedChanges(true);
}

void SettingsModelImp::setWallisContrast(double contrast)
{
  mSettings->wallis()->setContrast(contrast);
  emit unsavedChanges(true);
}

void SettingsModelImp::setWallisBrightness(double brightness)
{
  mSettings->wallis()->setBrightness(brightness);
  emit unsavedChanges(true);
}

void SettingsModelImp::setWallisImposedAverage(int imposedAverage)
{
  mSettings->wallis()->setImposedAverage(imposedAverage);
  emit unsavedChanges(true);
}

void SettingsModelImp::setWallisImposedLocalStdDev(int imposedLocalStdDev)
{
  mSettings->wallis()->setImposedLocalStdDev(imposedLocalStdDev);
  emit unsavedChanges(true);
}

void SettingsModelImp::setWallisKernelSize(int kernelSize)
{
  mSettings->wallis()->setKernelSize(kernelSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setAgastThreshold(int threshold)
{
  mSettings->agast()->setThreshold(threshold);
  emit unsavedChanges(true);
}

void SettingsModelImp::setAgastNonmaxSuppression(bool nonmaxSuppression)
{
  mSettings->agast()->setNonmaxSuppression(nonmaxSuppression);
  emit unsavedChanges(true);
}

void SettingsModelImp::setAgastDetectorType(const QString &detectorType)
{
  mSettings->agast()->setDetectorType(detectorType);
  emit unsavedChanges(true);
}

void SettingsModelImp::setAkazeDescriptorType(const QString &descriptorType)
{
  mSettings->akaze()->setDescriptorType(descriptorType);
  emit unsavedChanges(true);
}

void SettingsModelImp::setAkazeDescriptorSize(int descriptorSize)
{
  mSettings->akaze()->setDescriptorSize(descriptorSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setAkazeDescriptorChannels(int channels)
{
  mSettings->akaze()->setDescriptorChannels(channels);
  emit unsavedChanges(true);
}

void SettingsModelImp::setAkazeThreshold(double threshold)
{
  mSettings->akaze()->setThreshold(threshold);
  emit unsavedChanges(true);
}

void SettingsModelImp::setAkazeOctaves(int octaves)
{
  mSettings->akaze()->setOctaves(octaves);
  emit unsavedChanges(true);
}

void SettingsModelImp::setAkazeOctaveLayers(int octaveLayers)
{
  mSettings->akaze()->setOctaveLayers(octaveLayers);
  emit unsavedChanges(true);
}

void SettingsModelImp::setAkazeDiffusivity(const QString &diffusivity)
{
  mSettings->akaze()->setDiffusivity(diffusivity);
  emit unsavedChanges(true);
}

void SettingsModelImp::setBoostDescriptorType(const QString &descriptorType)
{
  mSettings->boost()->setDescriptorType(descriptorType);
  emit unsavedChanges(true);
}

void SettingsModelImp::setBoostUseOrientation(bool useOrientation)
{
  mSettings->boost()->setUseOrientation(useOrientation);
  emit unsavedChanges(true);
}

void SettingsModelImp::setBoostScaleFactor(double scaleFactor)
{
  mSettings->boost()->setScaleFactor(scaleFactor);
  emit unsavedChanges(true);
}

void SettingsModelImp::setBriefBytes(const QString &bytes)
{
  mSettings->brief()->setBytes(bytes);
  emit unsavedChanges(true);
}

void SettingsModelImp::setBriefUseOrientation(bool useOrientation)
{
  mSettings->brief()->setUseOrientation(useOrientation);
  emit unsavedChanges(true);
}

void SettingsModelImp::setBriskThreshold(int threshold)
{
  mSettings->brisk()->setThreshold(threshold);
  emit unsavedChanges(true);
}

void SettingsModelImp::setBriskOctaves(int octaves)
{
  mSettings->brisk()->setOctaves(octaves);
  emit unsavedChanges(true);
}

void SettingsModelImp::setBriskPatternScale(double patternScale)
{
  mSettings->brisk()->setPatternScale(patternScale);
  emit unsavedChanges(true);
}

void SettingsModelImp::setDaisyRadius(double radius)
{
  mSettings->daisy()->setRadius(radius);
  emit unsavedChanges(true);
}

void SettingsModelImp::setDaisyQRadius(int qRadius)
{
  mSettings->daisy()->setQRadius(qRadius);
  emit unsavedChanges(true);
}

void SettingsModelImp::setDaisyQTheta(int qTheta)
{
  mSettings->daisy()->setQTheta(qTheta);
  emit unsavedChanges(true);
}

void SettingsModelImp::setDaisyQHist(int qHist)
{
  mSettings->daisy()->setQHist(qHist);
  emit unsavedChanges(true);
}

void SettingsModelImp::setDaisyNorm(const QString &norm)
{
  mSettings->daisy()->setNorm(norm);
  emit unsavedChanges(true);
}

void SettingsModelImp::setDaisyInterpolation(bool interpolation)
{
  mSettings->daisy()->setInterpolation(interpolation);
  emit unsavedChanges(true);
}

void SettingsModelImp::setDaisyUseOrientation(bool useOrientation)
{
  mSettings->daisy()->setUseOrientation(useOrientation);
  emit unsavedChanges(true);
}

void SettingsModelImp::setFastThreshold(int threshold)
{
  mSettings->fast()->setThreshold(threshold);
  emit unsavedChanges(true);
}

void SettingsModelImp::setFastNonmaxSuppression(bool nonmaxSuppression)
{
  mSettings->fast()->setNonmaxSuppression(nonmaxSuppression);
  emit unsavedChanges(true);
}

void SettingsModelImp::setFastDetectorType(QString detectorType)
{
  mSettings->fast()->setDetectorType(detectorType);
  emit unsavedChanges(true);
}

void SettingsModelImp::setFreakOrientationNormalized(bool orientationNormalized)
{
  mSettings->freak()->setOrientationNormalized(orientationNormalized);
  emit unsavedChanges(true);
}

void SettingsModelImp::setFreakScaleNormalized(bool scaleNormalized)
{
  mSettings->freak()->setScaleNormalized(scaleNormalized);
  emit unsavedChanges(true);
}

void SettingsModelImp::setFreakPatternScale(double patternScale)
{
  mSettings->freak()->setPatternScale(patternScale);
  emit unsavedChanges(true);
}

void SettingsModelImp::setFreakOctaves(int octaves)
{
  mSettings->freak()->setOctaves(octaves);
  emit unsavedChanges(true);
}

void SettingsModelImp::setGfttMaxFeatures(int maxFeatures)
{
  mSettings->gftt()->setMaxFeatures(maxFeatures);
  emit unsavedChanges(true);
}

void SettingsModelImp::setGfttQualityLevel(double qlevel)
{
  mSettings->gftt()->setQualityLevel(qlevel);
  emit unsavedChanges(true);
}

void SettingsModelImp::setGfttMinDistance(double minDistance)
{
  mSettings->gftt()->setMinDistance(minDistance);
  emit unsavedChanges(true);
}

void SettingsModelImp::setGfttBlockSize(int blockSize)
{
  mSettings->gftt()->setBlockSize(blockSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setGfttHarrisDetector(bool value)
{
  mSettings->gftt()->setHarrisDetector(value);
  emit unsavedChanges(true);
}

void SettingsModelImp::setGfttK(double k)
{
  mSettings->gftt()->setK(k);
  emit unsavedChanges(true);
}

void SettingsModelImp::setHogWinSize(const QSize &winSize)
{
  mSettings->hog()->setWinSize(winSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setHogBlockSize(const QSize &blockSize)
{
  mSettings->hog()->setBlockSize(blockSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setHogBlockStride(const QSize &blockStride)
{
  mSettings->hog()->setBlockStride(blockStride);
  emit unsavedChanges(true);
}

void SettingsModelImp::setHogCellSize(const QSize &cellSize)
{
  mSettings->hog()->setCellSize(cellSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setHogNbins(int nbins)
{
  mSettings->hog()->setNbins(nbins);
  emit unsavedChanges(true);
}

void SettingsModelImp::setHogDerivAperture(int derivAperture)
{
  mSettings->hog()->setDerivAperture(derivAperture);
  emit unsavedChanges(true);
}

void SettingsModelImp::setKazeExtendedDescriptor(bool extended)
{
  mSettings->kaze()->setExtendedDescriptor(extended);
  emit unsavedChanges(true);
}

void SettingsModelImp::setKazeUpright(bool upright)
{
  mSettings->kaze()->setUprightDescriptor(upright);
  emit unsavedChanges(true);
}

void SettingsModelImp::setKazeThreshold(double threshold)
{
  mSettings->kaze()->setThreshold(threshold);
  emit unsavedChanges(true);
}

void SettingsModelImp::setKazeOctaves(int octaves)
{
  mSettings->kaze()->setOctaves(octaves);
  emit unsavedChanges(true);
}

void SettingsModelImp::setKazeOctaveLayers(int octaveLayers)
{
  mSettings->kaze()->setOctaveLayers(octaveLayers);
  emit unsavedChanges(true);
}

void SettingsModelImp::setKazeDiffusivity(const QString &diffusivity)
{
  mSettings->kaze()->setDiffusivity(diffusivity);
  emit unsavedChanges(true);
}

void SettingsModelImp::setLatchBytes(const QString &bytes)
{
  mSettings->latch()->setBytes(bytes);
  emit unsavedChanges(true);
}

void SettingsModelImp::setLatchRotationInvariance(bool rotationInvariance)
{
  mSettings->latch()->setRotationInvariance(rotationInvariance);
  emit unsavedChanges(true);
}

void SettingsModelImp::setLatchHalfSsdSize(int halfSsdSize)
{
  mSettings->latch()->setHalfSsdSize(halfSsdSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setLucidKernel(int lucidKernel)
{
  mSettings->lucid()->setLucidKernel(lucidKernel);
  emit unsavedChanges(true);
}

void SettingsModelImp::setLucidBlurKernel(int blurKernel)
{
  mSettings->lucid()->setBlurKernel(blurKernel);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMsdThresholdSaliency(double thresholdSaliency)
{
  mSettings->msd()->setThresholdSaliency(thresholdSaliency);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMsdPathRadius(int pathRadius)
{
  mSettings->msd()->setPatchRadius(pathRadius);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMsdKNN(int knn)
{
  mSettings->msd()->setKNN(knn);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMsdAreaRadius(int areaRadius)
{
  mSettings->msd()->setSearchAreaRadius(areaRadius);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMsdScaleFactor(double scaleFactor)
{
  mSettings->msd()->setScaleFactor(scaleFactor);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMsdNMSRadius(int NMSRadius)
{
  mSettings->msd()->setNMSRadius(NMSRadius);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMsdNScales(int nScales)
{
  mSettings->msd()->setNScales(nScales);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMsdNMSScaleR(int NMSScaleR)
{
  mSettings->msd()->setNMSScaleRadius(NMSScaleR);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMsdComputeOrientations(bool computeOrientations)
{
  mSettings->msd()->setComputeOrientation(computeOrientations);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMsdAffineMSD(bool affineMSD)
{
  mSettings->msd()->setAffineMSD(affineMSD);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMsdTilts(int tilts)
{
  mSettings->msd()->setAffineTilts(tilts);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMserDelta(int delta)
{
  mSettings->mser()->setDelta(delta);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMserMinArea(int minArea)
{
  mSettings->mser()->setMinArea(minArea);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMserMaxArea(int maxArea)
{
  mSettings->mser()->setMaxArea(maxArea);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMserMaxVariation(double maxVariation)
{
  mSettings->mser()->setMaxVariation(maxVariation);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMserMinDiversity(double minDiversity)
{
  mSettings->mser()->setMinDiversity(minDiversity);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMserMaxEvolution(int maxEvolution)
{
  mSettings->mser()->setMaxEvolution(maxEvolution);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMserAreaThreshold(double areaThreshold)
{
  mSettings->mser()->setAreaThreshold(areaThreshold);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMserMinMargin(double minMargin)
{
  mSettings->mser()->setMinMargin(minMargin);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMserEdgeBlurSize(int edgeBlurSize)
{
  mSettings->mser()->setEdgeBlurSize(edgeBlurSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setOrbScaleFactor(double scaleFactor)
{
  mSettings->orb()->setScaleFactor(scaleFactor);
  emit unsavedChanges(true);
}

void SettingsModelImp::setOrbFeaturesNumber(int featuresNumber)
{
  mSettings->orb()->setFeaturesNumber(featuresNumber);
  emit unsavedChanges(true);
}

void SettingsModelImp::setOrbLevelsNumber(int levelsNumber)
{
  mSettings->orb()->setLevelsNumber(levelsNumber);
  emit unsavedChanges(true);
}

void SettingsModelImp::setOrbEdgeThreshold(int edgeThreshold)
{
  mSettings->orb()->setEdgeThreshold(edgeThreshold);
  emit unsavedChanges(true);
}

void SettingsModelImp::setOrbWTA_K(int WTA_K)
{
  mSettings->orb()->setWTA_K(WTA_K);
  emit unsavedChanges(true);
}

void SettingsModelImp::setOrbScoreType(const QString &scoreType)
{
  mSettings->orb()->setScoreType(scoreType);
  emit unsavedChanges(true);
}

void SettingsModelImp::setOrbPatchSize(int patchSize)
{
  mSettings->orb()->setPatchSize(patchSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setOrbFastThreshold(int fastThreshold)
{
  mSettings->orb()->setFastThreshold(fastThreshold);
  emit unsavedChanges(true);
}

void SettingsModelImp::setSiftFeaturesNumber(int featuresNumber)
{
  mSettings->sift()->setFeaturesNumber(featuresNumber);
  emit unsavedChanges(true);
}

void SettingsModelImp::setSiftOctaveLayers(int octaveLayers)
{
  mSettings->sift()->setOctaveLayers(octaveLayers);
  emit unsavedChanges(true);
}

void SettingsModelImp::setSiftContrastThreshold(double contrastThreshold)
{
  mSettings->sift()->setContrastThreshold(contrastThreshold);
  emit unsavedChanges(true);
}

void SettingsModelImp::setSiftEdgeThreshold(double edgeThreshold)
{
  mSettings->sift()->setEdgeThreshold(edgeThreshold);
  emit unsavedChanges(true);
}

void SettingsModelImp::setSiftSigma(double sigma)
{
  mSettings->sift()->setSigma(sigma);
  emit unsavedChanges(true);
}

void SettingsModelImp::setStarMaxSize(int maxSize)
{
  mSettings->star()->setMaxSize(maxSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setStarResponseThreshold(int responseThreshold)
{
  mSettings->star()->setResponseThreshold(responseThreshold);
  emit unsavedChanges(true);
}

void SettingsModelImp::setStarLineThresholdProjected(int lineThresholdProjected)
{
  mSettings->star()->setLineThresholdProjected(lineThresholdProjected);
  emit unsavedChanges(true);
}

void SettingsModelImp::setStarLineThresholdBinarized(int lineThresholdBinarized)
{
  mSettings->star()->setLineThresholdBinarized(lineThresholdBinarized);
  emit unsavedChanges(true);
}

void SettingsModelImp::setStarSuppressNonmaxSize(int suppressNonmaxSize)
{
  mSettings->star()->setSuppressNonmaxSize(suppressNonmaxSize);
  emit unsavedChanges(true);
}

void SettingsModelImp::setSurfHessianThreshold(double hessianThreshold)
{
  mSettings->surf()->setHessianThreshold(hessianThreshold);
  emit unsavedChanges(true);
}

void SettingsModelImp::setSurfOctaves(int octaves)
{
  mSettings->surf()->setOctaves(octaves);
  emit unsavedChanges(true);
}

void SettingsModelImp::setSurfOctaveLayers(int octaveLayers)
{
  mSettings->surf()->setOctaveLayers(octaveLayers);
  emit unsavedChanges(true);
}

void SettingsModelImp::setSurfExtendedDescriptor(bool extendedDescriptor)
{
  mSettings->surf()->setExtendedDescriptor(extendedDescriptor);
  emit unsavedChanges(true);
}

void SettingsModelImp::setSurfRotatedFeatures(bool rotatedFeatures)
{
  mSettings->surf()->setUpright(rotatedFeatures);
  emit unsavedChanges(true);
}

void SettingsModelImp::setVggDescriptorType(const QString &descriptorType)
{
  mSettings->vgg()->setDescriptorType(descriptorType);
  emit unsavedChanges(true);
}

void SettingsModelImp::setVggScaleFactor(double scaleFactor)
{
  mSettings->vgg()->setScaleFactor(scaleFactor);
  emit unsavedChanges(true);
}

void SettingsModelImp::setVggSigma(double sigma)
{
  mSettings->vgg()->setSigma(sigma);
  emit unsavedChanges(true);
}

void SettingsModelImp::setVggUseNormalizeDescriptor(bool useNormalizeDescriptor)
{
  mSettings->vgg()->setUseNormalizeDescriptor(useNormalizeDescriptor);
  emit unsavedChanges(true);
}

void SettingsModelImp::setVggUseNormalizeImage(bool useNormalizeImage)
{
  mSettings->vgg()->setUseNormalizeImage(useNormalizeImage);
  emit unsavedChanges(true);
}

void SettingsModelImp::setVggUseScaleOrientation(bool useScaleOrientation)
{
  mSettings->vgg()->setUseScaleOrientation(useScaleOrientation);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchMethod(const QString &matchingMethod)
{
  mSettings->setMatchMethod(matchingMethod);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchStrategy(const QString &matchingStrategy)
{
  mSettings->setMatchStrategy(matchingStrategy);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchNormType(const QString &normType)
{
  BruteForceMatcherImp::Norm norm = BruteForceMatcherProperties::Norm::l2;
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

void SettingsModelImp::setMatchRatio(double ratio)
{
  mSettings->robustMatcher()->setRatio(ratio);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchDistance(double distance)
{
  mSettings->robustMatcher()->setDistance(distance);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchConfidence(double confidence)
{
  mSettings->robustMatcher()->setConfidence(confidence);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchCrossMatching(bool crossMatching)
{
  mSettings->robustMatcher()->setCrossCheck(crossMatching);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchMaxIters(int maxIters)
{
  mSettings->robustMatcher()->setMaxIters(maxIters);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchGeometricTest(const QString &geometricTest)
{
  RobustMatcher::GeometricTest geometric_test = RobustMatcher::GeometricTest::homography;
  if (geometricTest.compare("Homography Matrix") == 0) {
    geometric_test = RobustMatcher::GeometricTest::homography;
  } else if (geometricTest.compare("Fundamental Matrix") == 0) {
    geometric_test = RobustMatcher::GeometricTest::fundamental;
  } else if (geometricTest.compare("Essential Matrix") == 0) {
    geometric_test = RobustMatcher::GeometricTest::essential;
  }
  mSettings->robustMatcher()->setGeometricTest(geometric_test);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchHomographyComputeMethod(const QString &computeMethod)
{
  RobustMatcher::HomographyComputeMethod homographyComputeMethod = RobustMatcher::HomographyComputeMethod::ransac;
  if (computeMethod.compare("All Points") == 0) {
    homographyComputeMethod = RobustMatcher::HomographyComputeMethod::all_points;
  } else if (computeMethod.compare("RANSAC") == 0) {
    homographyComputeMethod = RobustMatcher::HomographyComputeMethod::ransac;
  } else if (computeMethod.compare("LMedS") == 0) {
    homographyComputeMethod = RobustMatcher::HomographyComputeMethod::lmeds;
  } else if (computeMethod.compare("RHO") == 0) {
    homographyComputeMethod = RobustMatcher::HomographyComputeMethod::rho;
  }
  mSettings->robustMatcher()->setHomographyComputeMethod(homographyComputeMethod);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchFundamentalComputeMethod(const QString &computeMethod)
{
  RobustMatcher::FundamentalComputeMethod fundamentalComputeMethod = RobustMatcher::FundamentalComputeMethod::ransac;
  if (computeMethod.compare("7-point algorithm") == 0) {
    fundamentalComputeMethod = RobustMatcher::FundamentalComputeMethod::algorithm_7_point;
  } else if (computeMethod.compare("8-point algorithm") == 0) {
    fundamentalComputeMethod = RobustMatcher::FundamentalComputeMethod::algorithm_8_point;
  } else if (computeMethod.compare("RANSAC") == 0) {
    fundamentalComputeMethod = RobustMatcher::FundamentalComputeMethod::ransac;
  } else if (computeMethod.compare("LMedS") == 0) {
    fundamentalComputeMethod = RobustMatcher::FundamentalComputeMethod::lmeds;
  }
  mSettings->robustMatcher()->setFundamentalComputeMethod(fundamentalComputeMethod);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchEssentialComputeMethod(const QString &computeMethod)
{
  RobustMatcher::EssentialComputeMethod essentialComputeMethod = RobustMatcher::EssentialComputeMethod::ransac;
  if (computeMethod.compare("RANSAC") == 0) {
    essentialComputeMethod = RobustMatcher::EssentialComputeMethod::ransac;
  } else if (computeMethod.compare("LMedS") == 0) {
    essentialComputeMethod = RobustMatcher::EssentialComputeMethod::lmeds;
  }
  mSettings->robustMatcher()->setEssentialComputeMethod(essentialComputeMethod);
  emit unsavedChanges(true);
}

void SettingsModelImp::setKeypointsViewerBGColor(const QString &color)
{
  mSettings->setKeypointsViewerBGColor(color);
  emit unsavedChanges(true);
}

void SettingsModelImp::setKeypointsViewerMarkerType(int type)
{
  mSettings->setKeypointsViewerMarkerType(type);
  emit unsavedChanges(true);
}

void SettingsModelImp::setKeypointsViewerMarkerSize(int size)
{
  mSettings->setKeypointsViewerMarkerSize(size);
  emit unsavedChanges(true);
}

void SettingsModelImp::setKeypointsViewerMarkerWidth(int width)
{
  mSettings->setKeypointsViewerMarkerWidth(width);
  emit unsavedChanges(true);
}

void SettingsModelImp::setKeypointsViewerMarkerColor(const QString &color)
{
  mSettings->setKeypointsViewerMarkerColor(color);
  emit unsavedChanges(true);
}

void SettingsModelImp::setKeypointsViewerSelectMarkerWidth(int width)
{
  mSettings->setKeypointsViewerSelectMarkerWidth(width);
  emit unsavedChanges(true);
}

void SettingsModelImp::setKeypointsViewerSelectMarkerColor(const QString &color)
{
  mSettings->setKeypointsViewerSelectMarkerColor(color);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchesViewerBGColor(const QString &color)
{
  mSettings->setMatchesViewerBGColor(color);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchesViewerMarkerType(int type)
{
  mSettings->setMatchesViewerMarkerType(type);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchesViewerMarkerSize(int size)
{
  mSettings->setMatchesViewerMarkerSize(size);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchesViewerMarkerWidth(int width)
{
  mSettings->setMatchesViewerMarkerWidth(width);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchesViewerMarkerColor(const QString &color)
{
  mSettings->setMatchesViewerMarkerColor(color);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchesViewerSelectMarkerWidth(int width)
{
  mSettings->setMatchesViewerSelectMarkerWidth(width);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchesViewerSelectMarkerColor(const QString &color)
{
  mSettings->setMatchesViewerSelectMarkerColor(color);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchesViewerLineColor(const QString &color)
{
  mSettings->setMatchesViewerLineColor(color);
  emit unsavedChanges(true);
}

void SettingsModelImp::setMatchesViewerLineWidth(int width)
{
  mSettings->setMatchesViewerLineWidth(width);
  emit unsavedChanges(true);
}

void SettingsModelImp::setGroundTruthEditorBGColor(const QString &bgColor)
{
  mSettings->setGroundTruthEditorBGColor(bgColor);
  emit unsavedChanges(true);
}

void SettingsModelImp::setGroundTruthEditorMarkerSize(int size)
{
  mSettings->setGroundTruthEditorMarkerSize(size);
  emit unsavedChanges(true);
}

void SettingsModelImp::setGroundTruthEditorMarkerWidth(int width)
{
  mSettings->setGroundTruthEditorMarkerWidth(width);
  emit unsavedChanges(true);
}

void SettingsModelImp::setGroundTruthEditorMarkerColor(const QString &color)
{
  mSettings->setGroundTruthEditorMarkerColor(color);
  emit unsavedChanges(true);
}

void SettingsModelImp::setGroundTruthEditorSelectMarkerWidth(int width)
{
  mSettings->setGroundTruthEditorSelectMarkerWidth(width);
  emit unsavedChanges(true);
}

void SettingsModelImp::setGroundTruthEditorSelectMarkerColor(const QString &color)
{
  mSettings->setGroundTruthEditorSelectMarkerColor(color);
  emit unsavedChanges(true);
}

void SettingsModelImp::setGroundTruthEditorMatrixAdjust(const QString &adjust)
{
  mSettings->setGroundTruthEditorMatrixAdjust(adjust);
  emit unsavedChanges(true);
}

void SettingsModelImp::reset()
{
  mSettings->reset();
  emit unsavedChanges(false);
}

void SettingsModelImp::init()
{
}

QStringList SettingsModelImp::languages() const
{
  QString langPath = QApplication::applicationDirPath();
  langPath.append("/translations");

  QStringList lang_list = QDir(langPath).entryList(QStringList("photomatch_*.qm"));
  if (lang_list.size() == 0)
    lang_list.push_back("photomatch_en.qm");
  return lang_list;
}

void SettingsModelImp::read()
{
  mSettingsRW->read(*mSettings);
}

void SettingsModelImp::write()
{
  mSettingsRW->write(*mSettings);
  emit unsavedChanges(false);
}

} // namespace photomatch
