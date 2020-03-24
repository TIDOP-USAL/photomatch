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


#ifndef PHOTOMATCH_SETTINGS_MODEL_H
#define PHOTOMATCH_SETTINGS_MODEL_H

#include <QObject>

#include "photomatch/core/settings.h"
#include "photomatch/ui/Settings.h"

namespace photomatch
{


class SettingsModelImp
  : public SettingsModel
{

  Q_OBJECT

public:

  explicit SettingsModelImp(Settings *settings,
                         SettingsController *settingsRW,
                         QObject *parent = nullptr);
  ~SettingsModelImp() override;

// IModel interface
public:

  QString language() const override;
  QStringList history() const override;
  int historyMaxSize() const override;

  QString imageViewerBGcolor() const override;

  QString keypointsFormat() const override;
  QString matchesFormat() const override;

  bool useCuda() const override;

  QSize acebsfBlockSize() const override;
  double acebsfL() const override;
  double acebsfK1() const override;
  double acebsfK2() const override;

  double claheClipLimit() const override;
  QSize claheTilesGridSize() const override;

  QSize cmbfheBlockSize() const override;

  int dheX() const override;

  QSize faheBlockSize() const override;

  QSize hmclaheBlockSize() const override;
  double hmclaheL() const override;
  double hmclahePhi() const  override;

  QSize lceBsescsBlockSize() const override;

  double msrcpSmallScale() const override;
  double msrcpMidScale() const  override;
  double msrcpLargeScale() const override;

  QSize noshpBlockSize() const override;

  QSize poheBlockSize() const override;

  int rswheHistogramDivisions() const override;
  int rswheHistogramCut() const override;

  double wallisContrast() const override;
  double wallisBrightness() const override;
  int wallisImposedAverage() const override;
  int wallisImposedLocalStdDev() const override;
  int wallisKernelSize() const override;

  int agastThreshold() const override;
  bool agastNonmaxSuppression() const override;
  QString agastDetectorType() const override;

  QString akazeDescriptorType() const override;
  int akazeDescriptorSize() const override;
  int akazeDescriptorChannels() const override;
  double akazeThreshold() const override;
  int akazeOctaves() const override;
  int akazeOctaveLayers() const override;
  QString akazeDiffusivity() const override;

  QString boostDescriptorType() const override;
  bool boostUseOrientation() const override;
  double boostScaleFactor() const override;

  QString briefBytes() const override;
  bool briefUseOrientation() const override;

  int briskThreshold() const override;
  int briskOctaves() const override;
  double briskPatternScale() const override;

  double daisyRadius() const override;
  int daisyQRadius() const override;
  int daisyQTheta() const override;
  int daisyQHist() const override;
  QString daisyNorm() const override;
  bool daisyInterpolation() const override;
  bool daisyUseOrientation() const override;

  int fastThreshold() const override;
  bool fastNonmaxSuppression() const override;
  QString fastdetectorType() const override;

  bool freakOrientationNormalized() const override;
  bool freakScaleNormalized() const override;
  double freakPatternScale() const override;
  int freakOctaves() const override;

  int gfttMaxFeatures() const override;
  double gfttQualityLevel() const override;
  double gfttMinDistance() const override;
  int gfttBlockSize() const override;
  bool gfttHarrisDetector() const override;
  double gfttK() const override;

  QSize hogWinSize() const override;
  QSize hogBlockSize() const override;
  QSize hogBlockStride() const override;
  QSize hogCellSize() const override;
  int hogNbins() const override;
  int hogDerivAperture() const override;

  bool kazeExtendedDescriptor() const override;
  bool kazeUpright() const override;
  double kazeThreshold() const override;
  int kazeOctaves() const override;
  int kazeOctaveLayers() const override;
  QString kazeDiffusivity() const override;

  QString latchBytes() const override;
  bool latchRotationInvariance() const override;
  int latchHalfSsdSize() const override;

  int lucidKernel() const override;
  int lucidBlurKernel() const override;

  double msdThresholdSaliency() const override;
  int msdPathRadius() const override;
  int msdKnn() const override;
  int msdAreaRadius() const override;
  double msdScaleFactor() const override;
  int msdNMSRadius() const override;
  int msdNScales() const override;
  int msdNMSScaleR() const override;
  bool msdComputeOrientations() const override;
  bool msdAffineMSD() const override;
  int msdTilts() const override;

  int mserDelta() const override;
  int mserMinArea() const override;
  int mserMaxArea() const override;
  double mserMaxVariation() const override;
  double mserMinDiversity() const override;
  int mserMaxEvolution() const override;
  double mserAreaThreshold() const override;
  double mserMinMargin() const override;
  int mserEdgeBlurSize() const override;

  int orbFeaturesNumber() const override;
  double orbScaleFactor() const override;
  int orbLevelsNumber() const override;
  int orbEdgeThreshold() const override;
  int orbWta_k() const override;
  QString orbScoreType() const override;
  int orbPatchSize() const override;
  int orbFastThreshold() const override;

  int siftFeaturesNumber() const override;
  int siftOctaveLayers() const override;
  double siftContrastThreshold() override;
  double siftEdgeThreshold() override;
  double siftSigma() override;

  int starMaxSize() const override;
  int starResponseThreshold() const override;
  int starLineThresholdProjected() const override;
  int starLineThresholdBinarized() const override;
  int starSuppressNonmaxSize() const override;

  double surfHessianThreshold() const override;
  int surfOctaves() const override;
  int surfOctaveLayers() const override;
  bool surfExtendedDescriptor() const override;
  bool surfRotatedFeatures() const override;

  QString vggDescriptorType() const override;
  double vggScaleFactor() const override;
  double vggSigma() const override;
  bool vggUseNormalizeDescriptor() const override;
  bool vggUseNormalizeImage() const override;
  bool vggUseScaleOrientation() const override;

  QString matchMethod() const override;
  QString matchStrategy() const override;
  QString matchNormType() const override;
  double matchRatio() const override;
  double matchDistance() const override;
  double matchConfidence() const override;
  bool matchCrossMatching() const override;
  int matchMaxIters() const override;
  QString matchGeometricTest() const override;
  QString matchHomographyComputeMethod() const override;
  QString matchFundamentalComputeMethod() const override;
  QString matchEssentialComputeMethod() const override;

  QString keypointsViewerBGColor() const override;
  int keypointsViewerMarkerType() const override;
  int keypointsViewerMarkerSize() const override;
  int keypointsViewerMarkerWidth() const override;
  QString keypointsViewerMarkerColor() const override;
  int keypointsViewerSelectMarkerWidth() const override;
  QString keypointsViewerSelectMarkerColor() const override;

  QString matchesViewerBGColor() const override;
  int matchesViewerMarkerType() const override;
  int matchesViewerMarkerSize() const override;
  int matchesViewerMarkerWidth() const override;
  QString matchesViewerMarkerColor() const override;
  int matchesViewerSelectMarkerWidth() const override;
  QString matchesViewerSelectMarkerColor() const override;
  QString matchesViewerLineColor() const override;
  int matchesViewerLineWidth() const override;

  QString groundTruthEditorBGColor() const override;
  int groundTruthEditorMarkerSize() const override;
  int groundTruthEditorMarkerWidth() const override;
  QString groundTruthEditorMarkerColor() const override;
  int groundTruthEditorSelectMarkerWidth() const override;
  QString groundTruthEditorSelectMarkerColor() const override;

  QStringList languages() const override;
  void read() override;
  void write() override;


public slots:

  void setLanguage(const QString &language) override;
  void addToHistory(const QString &project) override;
  void clearHistory() override;
  void setHistoryMaxSize(int maxSize) override;

  void setImageViewerBGcolor(const QString &bgColor) override;

  void setKeypointsFormat(const QString &format) override;
  void setMatchesFormat(const QString &format) override;

  void setClaheClipLimit(double clipLimit) override;
  void setClaheTilesGridSize(const QSize &tilesGridSize) override;

  void setCmbfheBlockSize(const QSize &size) override;

  void setDheX(int x) override;

  void setFaheBlockSize(const QSize &size) override;

  void setUseCuda(bool active) override;

  void setAcebsfBlockSize(const QSize &blockSize) override;
  void setAcebsfL(double l) override;
  void setAcebsfK1(double k1) override;
  void setAcebsfK2(double k2) override;

  void setHmclaheBlockSize(const QSize &size) override;
  void setHmclaheL(double l) override;
  void setHmclahePhi(double phi) override;

  void setLceBsescsBlockSize(const QSize &blockSize) override;

  void setMsrcpSmallScale(double smallScale) override;
  void setMsrcpMidScale(double midScale) override;
  void setMsrcpLargeScale(double largeScale) override;

  void setNoshpBlockSize(const QSize &blockSize) override;

  void setPoheBlockSize(const QSize &blockSize) override;

  void setRswheHistogramDivisions(int histogramDivisions) override;
  void setRswheHistogramCut(int histogramCut) override;

  void setWallisContrast(double contrast) override;
  void setWallisBrightness(double brightness) override;
  void setWallisImposedAverage(int imposedAverage) override;
  void setWallisImposedLocalStdDev(int imposedLocalStdDev) override;
  void setWallisKernelSize(int kernelSize) override;

  void setAgastThreshold(int threshold) override;
  void setAgastNonmaxSuppression(bool nonmaxSuppression) override;
  void setAgastDetectorType(const QString &detectorType) override;

  void setAkazeDescriptorType(const QString &descriptorType) override;
  void setAkazeDescriptorSize(int descriptorSize) override;
  void setAkazeDescriptorChannels(int channels) override;
  void setAkazeThreshold(double threshold) override;
  void setAkazeOctaves(int octaves) override;
  void setAkazeOctaveLayers(int octaveLayers) override;
  void setAkazeDiffusivity(const QString &diffusivity) override;

  void setBoostDescriptorType(const QString &descriptorType) override;
  void setBoostUseOrientation(bool useOrientation) override;
  void setBoostScaleFactor(double scaleFactor) override;

  void setBriefBytes(const QString &bytes) override;
  void setBriefUseOrientation(bool useOrientation) override;

  void setBriskThreshold(int threshold) override;
  void setBriskOctaves(int octaves) override;
  void setBriskPatternScale(double patternScale) override;

  void setDaisyRadius(double radius) override;
  void setDaisyQRadius(int qRadius) override;
  void setDaisyQTheta(int qTheta) override;
  void setDaisyQHist(int qHist) override;
  void setDaisyNorm(const QString &norm) override;
  void setDaisyInterpolation(bool interpolation) override;
  void setDaisyUseOrientation(bool useOrientation) override;

  void setFastThreshold(int threshold) override;
  void setFastNonmaxSuppression(bool nonmaxSuppression) override;
  void setFastDetectorType(QString detectorType) override;

  void setFreakOrientationNormalized(bool orientationNormalized) override;
  void setFreakScaleNormalized(bool scaleNormalized) override;
  void setFreakPatternScale(double patternScale) override;
  void setFreakOctaves(int octaves) override;

  void setGfttMaxFeatures(int maxFeatures) override;
  void setGfttQualityLevel(double qlevel) override;
  void setGfttMinDistance(double minDistance) override;
  void setGfttBlockSize(int blockSize) override;
  void setGfttHarrisDetector(bool value) override;
  void setGfttK(double k) override;

  void setHogWinSize(const QSize &winSize) override;
  void setHogBlockSize(const QSize &blockSize) override;
  void setHogBlockStride(const QSize &blockStride) override;
  void setHogCellSize(const QSize &cellSize) override;
  void setHogNbins(int nbins) override;
  void setHogDerivAperture(int derivAperture) override;

  void setKazeExtendedDescriptor(bool extended) override;
  void setKazeUpright(bool upright) override;
  void setKazeThreshold(double threshold) override;
  void setKazeOctaves(int octaves) override;
  void setKazeOctaveLayers(int octaveLayers) override;
  void setKazeDiffusivity(const QString &diffusivity) override;

  void setLatchBytes(const QString &bytes) override;
  void setLatchRotationInvariance(bool rotationInvariance) override;
  void setLatchHalfSsdSize(int halfSsdSize) override;

  void setLucidKernel(int lucidKernel) override;
  void setLucidBlurKernel(int blurKernel) override;

  void setMsdThresholdSaliency(double thresholdSaliency) override;
  void setMsdPathRadius(int pathRadius) override;
  void setMsdKNN(int knn) override;
  void setMsdAreaRadius(int areaRadius) override;
  void setMsdScaleFactor(double scaleFactor) override;
  void setMsdNMSRadius(int NMSRadius) override;
  void setMsdNScales(int nScales) override;
  void setMsdNMSScaleR(int NMSScaleR) override;
  void setMsdComputeOrientations(bool computeOrientations) override;
  void setMsdAffineMSD(bool affineMSD) override;
  void setMsdTilts(int tilts) override;

  void setMserDelta(int delta) override;
  void setMserMinArea(int minArea) override;
  void setMserMaxArea(int maxArea) override;
  void setMserMaxVariation(double maxVariation) override;
  void setMserMinDiversity(double minDiversity) override;
  void setMserMaxEvolution(int maxEvolution) override;
  void setMserAreaThreshold(double areaThreshold) override;
  void setMserMinMargin(double minMargin) override;
  void setMserEdgeBlurSize(int edgeBlurSize) override;

  void setOrbScaleFactor(double scaleFactor) override;
  void setOrbFeaturesNumber(int featuresNumber) override;
  void setOrbLevelsNumber(int levelsNumber) override;
  void setOrbEdgeThreshold(int edgeThreshold) override;
  void setOrbWTA_K(int WTA_K) override;
  void setOrbScoreType(const QString &scoreType) override;
  void setOrbPatchSize(int patchSize) override;
  void setOrbFastThreshold(int fastThreshold) override;

  void setSiftFeaturesNumber(int featuresNumber) override;
  void setSiftOctaveLayers(int octaveLayers) override;
  void setSiftContrastThreshold(double contrastThreshold) override;
  void setSiftEdgeThreshold(double edgeThreshold) override;
  void setSiftSigma(double sigma) override;

  void setStarMaxSize(int maxSize) override;
  void setStarResponseThreshold(int responseThreshold) override;
  void setStarLineThresholdProjected(int lineThresholdProjected) override;
  void setStarLineThresholdBinarized(int lineThresholdBinarized) override;
  void setStarSuppressNonmaxSize(int suppressNonmaxSize) override;

  void setSurfHessianThreshold(double hessianThreshold) override;
  void setSurfOctaves(int octaves) override;
  void setSurfOctaveLayers(int octaveLayers) override;
  void setSurfExtendedDescriptor(bool extendedDescriptor) override;
  void setSurfRotatedFeatures(bool rotatedFeatures) override;

  void setVggDescriptorType(const QString &descriptorType) override;
  void setVggScaleFactor(double scaleFactor) override;
  void setVggSigma(double sigma) override;
  void setVggUseNormalizeDescriptor(bool useNormalizeDescriptor) override;
  void setVggUseNormalizeImage(bool useNormalizeImage) override;
  void setVggUseScaleOrientation(bool useScaleOrientation) override;

  void setMatchMethod(const QString &matchingMethod) override;
  void setMatchStrategy(const QString &matchingStrategy) override;
  void setMatchNormType(const QString &normType) override;
  void setMatchRatio(double ratio) override;
  void setMatchDistance(double distance) override;
  void setMatchConfidence(double confidence) override;
  void setMatchCrossMatching(bool crossMatching) override;
  void setMatchMaxIters(int maxIters) override;
  void setMatchGeometricTest(const QString &geometricTest) override;
  void setMatchHomographyComputeMethod(const QString &computeMethod) override;
  void setMatchFundamentalComputeMethod(const QString &computeMethod) override;
  void setMatchEssentialComputeMethod(const QString &computeMethod) override;

  void setKeypointsViewerBGColor(const QString &color) override;
  void setKeypointsViewerMarkerType(int type) override;
  void setKeypointsViewerMarkerSize(int size) override;
  void setKeypointsViewerMarkerWidth(int width) override;
  void setKeypointsViewerMarkerColor(const QString &color) override;
  void setKeypointsViewerSelectMarkerWidth(int width) override;
  void setKeypointsViewerSelectMarkerColor(const QString &color) override;

  void setMatchesViewerBGColor(const QString &color) override;
  void setMatchesViewerMarkerType(int type) override;
  void setMatchesViewerMarkerSize(int size) override;
  void setMatchesViewerMarkerWidth(int width) override;
  void setMatchesViewerMarkerColor(const QString &color) override;
  void setMatchesViewerSelectMarkerWidth(int width) override;
  void setMatchesViewerSelectMarkerColor(const QString &color) override;
  void setMatchesViewerLineColor(const QString &color) override;
  void setMatchesViewerLineWidth(int width) override;

  void setGroundTruthEditorBGColor(const QString &bgColor) override;
  void setGroundTruthEditorMarkerSize(int size) override;
  void setGroundTruthEditorMarkerWidth(int width) override;
  void setGroundTruthEditorMarkerColor(const QString &color) override;
  void setGroundTruthEditorSelectMarkerWidth(int width) override;
  void setGroundTruthEditorSelectMarkerColor(const QString &color) override;

  void reset() override;

private:

  void init() override;

protected:

  Settings *mSettings;
  SettingsController *mSettingsRW;

};


} // namespace photomatch

#endif // PHOTOMATCH_SETTINGS_MODEL_H
