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

#ifndef PHOTOMATCH_SETTINGS_INTERFACES_H
#define PHOTOMATCH_SETTINGS_INTERFACES_H

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class SettingsModel
  : public PhotoMatchModel
{

  Q_OBJECT

public:

  SettingsModel(QObject *parent = nullptr) : PhotoMatchModel(parent) {}
  virtual ~SettingsModel() override {}

  /*!
   * \brief List of available languages
   * \return
   */
  virtual QStringList languages() const = 0;

  /*!
   * \brief Current language
   * \return Current language
   */
  virtual QString language() const = 0;

  /*!
   * \brief Recent history projects
   * \return List of recent projects
   */
  virtual QStringList history() const = 0;

  /*!
   * \brief Maximum history size
   * \return Maximum history size
   */
  virtual int historyMaxSize() const = 0;

  /*!
   * \brief Image viewer Background color
   * \return Hex value
   */
  virtual QString imageViewerBGcolor() const = 0;

  /*!
   * \brief Keypoints format
   * \return "Binary", "XML" or "YML"
   */
  virtual QString keypointsFormat() const = 0;

  /*!
   * \brief Matches format
   * \return "Binary", "XML" or "YML"
   */
  virtual QString matchesFormat() const = 0;

  virtual bool useCuda() const = 0;

  virtual QSize acebsfBlockSize() const = 0;
  virtual double acebsfL() const = 0;
  virtual double acebsfK1() const = 0;
  virtual double acebsfK2() const = 0;

  virtual double claheClipLimit() const = 0;
  virtual QSize claheTilesGridSize() const = 0;

  virtual QSize cmbfheBlockSize() const = 0;

  virtual int dheX() const = 0;

  virtual QSize faheBlockSize() const = 0;

  virtual QSize hmclaheBlockSize() const = 0;
  virtual double hmclaheL() const = 0;
  virtual double hmclahePhi() const  = 0;

  virtual QSize lceBsescsBlockSize() const = 0;

  virtual double msrcpSmallScale() const = 0;
  virtual double msrcpMidScale() const  = 0;
  virtual double msrcpLargeScale() const = 0;

  virtual QSize noshpBlockSize() const = 0;

  virtual QSize poheBlockSize() const = 0;

  virtual int rswheHistogramDivisions() const = 0;
  virtual int rswheHistogramCut() const = 0;

  virtual double wallisContrast() const = 0;
  virtual double wallisBrightness() const = 0;
  virtual int wallisImposedAverage() const = 0;
  virtual int wallisImposedLocalStdDev() const = 0;
  virtual int wallisKernelSize() const = 0;

  virtual int agastThreshold() const = 0;
  virtual bool agastNonmaxSuppression() const = 0;
  virtual QString agastDetectorType() const = 0;

  virtual QString akazeDescriptorType() const = 0;
  virtual int akazeDescriptorSize() const = 0;
  virtual int akazeDescriptorChannels() const = 0;
  virtual double akazeThreshold() const = 0;
  virtual int akazeOctaves() const = 0;
  virtual int akazeOctaveLayers() const = 0;
  virtual QString akazeDiffusivity() const = 0;

  virtual QString boostDescriptorType() const = 0;
  virtual bool boostUseOrientation() const = 0;
  virtual double boostScaleFactor() const = 0;

  virtual QString briefBytes() const = 0;
  virtual bool briefUseOrientation() const = 0;

  virtual int briskThreshold() const = 0;
  virtual int briskOctaves() const = 0;
  virtual double briskPatternScale() const = 0;

  virtual double daisyRadius() const = 0;
  virtual int daisyQRadius() const = 0;
  virtual int daisyQTheta() const = 0;
  virtual int daisyQHist() const = 0;
  virtual QString daisyNorm() const = 0;
  virtual bool daisyInterpolation() const = 0;
  virtual bool daisyUseOrientation() const = 0;

  virtual int fastThreshold() const = 0;
  virtual bool fastNonmaxSuppression() const = 0;
  virtual QString fastdetectorType() const = 0;

  virtual bool freakOrientationNormalized() const = 0;
  virtual bool freakScaleNormalized() const = 0;
  virtual double freakPatternScale() const = 0;
  virtual int freakOctaves() const = 0;

  virtual int gfttMaxFeatures() const = 0;
  virtual double gfttQualityLevel() const = 0;
  virtual double gfttMinDistance() const = 0;
  virtual int gfttBlockSize() const = 0;
  virtual bool gfttHarrisDetector() const = 0;
  virtual double gfttK() const = 0;

  virtual QSize hogWinSize() const = 0;
  virtual QSize hogBlockSize() const = 0;
  virtual QSize hogBlockStride() const = 0;
  virtual QSize hogCellSize() const = 0;
  virtual int hogNbins() const = 0;
  virtual int hogDerivAperture() const = 0;

  virtual bool kazeExtendedDescriptor() const = 0;
  virtual bool kazeUpright() const = 0;
  virtual double kazeThreshold() const = 0;
  virtual int kazeOctaves() const = 0;
  virtual int kazeOctaveLayers() const = 0;
  virtual QString kazeDiffusivity() const = 0;

  virtual QString latchBytes() const = 0;
  virtual bool latchRotationInvariance() const = 0;
  virtual int latchHalfSsdSize() const = 0;

  virtual int lucidKernel() const = 0;
  virtual int lucidBlurKernel() const = 0;

  virtual double msdThresholdSaliency() const = 0;
  virtual int msdPathRadius() const = 0;
  virtual int msdKnn() const = 0;
  virtual int msdAreaRadius() const = 0;
  virtual double msdScaleFactor() const = 0;
  virtual int msdNMSRadius() const = 0;
  virtual int msdNScales() const = 0;
  virtual int msdNMSScaleR() const = 0;
  virtual bool msdComputeOrientations() const = 0;
  virtual bool msdAffineMSD() const = 0;
  virtual int msdTilts() const = 0;

  virtual int mserDelta() const = 0;
  virtual int mserMinArea() const = 0;
  virtual int mserMaxArea() const = 0;
  virtual double mserMaxVariation() const = 0;
  virtual double mserMinDiversity() const = 0;
  virtual int mserMaxEvolution() const = 0;
  virtual double mserAreaThreshold() const = 0;
  virtual double mserMinMargin() const = 0;
  virtual int mserEdgeBlurSize() const = 0;

  virtual int orbFeaturesNumber() const = 0;
  virtual double orbScaleFactor() const = 0;
  virtual int orbLevelsNumber() const = 0;
  virtual int orbEdgeThreshold() const = 0;
  virtual int orbWta_k() const = 0;
  virtual QString orbScoreType() const = 0;
  virtual int orbPatchSize() const = 0;
  virtual int orbFastThreshold() const = 0;

  virtual int siftFeaturesNumber() const = 0;
  virtual int siftOctaveLayers() const = 0;
  virtual double siftContrastThreshold() = 0;
  virtual double siftEdgeThreshold() = 0;
  virtual double siftSigma() = 0;

  virtual int starMaxSize() const  = 0;
  virtual int starResponseThreshold() const  = 0;
  virtual int starLineThresholdProjected() const  = 0;
  virtual int starLineThresholdBinarized() const  = 0;
  virtual int starSuppressNonmaxSize() const  = 0;

  virtual double surfHessianThreshold() const = 0;
  virtual int surfOctaves() const = 0;
  virtual int surfOctaveLayers() const = 0;
  virtual bool surfExtendedDescriptor() const = 0;
  virtual bool surfRotatedFeatures() const = 0;

  virtual QString vggDescriptorType() const = 0;
  virtual double vggScaleFactor() const = 0;
  virtual double vggSigma() const = 0;
  virtual bool vggUseNormalizeDescriptor() const = 0;
  virtual bool vggUseNormalizeImage() const = 0;
  virtual bool vggUseScaleOrientation() const = 0;

  virtual QString matchMethod() const = 0;
  virtual QString matchStrategy() const = 0;
  virtual QString matchNormType() const = 0;
  virtual double matchRatio() const = 0;
  virtual double matchDistance() const = 0;
  virtual double matchConfidence() const = 0;
  virtual bool matchCrossMatching() const = 0;
  virtual int matchMaxIters() const = 0;
  virtual QString matchGeometricTest() const = 0;
  virtual QString matchHomographyComputeMethod() const = 0;
  virtual QString matchFundamentalComputeMethod() const = 0;
  virtual QString matchEssentialComputeMethod() const = 0;

  virtual QString keypointsViewerBGColor() const = 0;
  virtual int keypointsViewerMarkerType() const = 0;
  virtual int keypointsViewerMarkerSize() const = 0;
  virtual int keypointsViewerMarkerWidth() const = 0;
  virtual QString keypointsViewerMarkerColor() const = 0;
  virtual int keypointsViewerSelectMarkerWidth() const = 0;
  virtual QString keypointsViewerSelectMarkerColor() const = 0;

  virtual QString matchesViewerBGColor() const = 0;
  virtual int matchesViewerMarkerType() const = 0;
  virtual int matchesViewerMarkerSize() const = 0;
  virtual int matchesViewerMarkerWidth() const = 0;
  virtual QString matchesViewerMarkerColor() const = 0;
  virtual int matchesViewerSelectMarkerWidth() const = 0;
  virtual QString matchesViewerSelectMarkerColor() const = 0;
  virtual QString matchesViewerLineColor() const = 0;
  virtual int matchesViewerLineWidth() const = 0;

  virtual QString groundTruthEditorBGColor() const = 0;
  virtual int groundTruthEditorMarkerSize() const = 0;
  virtual int groundTruthEditorMarkerWidth() const = 0;
  virtual QString groundTruthEditorMarkerColor() const = 0;
  virtual int groundTruthEditorSelectMarkerWidth() const = 0;
  virtual QString groundTruthEditorSelectMarkerColor() const = 0;
  virtual QString groundTruthEditorMatrixAdjust() const = 0;

  /*!
   * \brief read
   * \return
   */
  virtual void read() = 0;

  /*!
   * \brief write
   * \return
   */
  virtual void write() = 0;

  /*!
   * \brief Comprueba si hay cambios sin guardar en el proyecto
   * \return
   */
  //virtual bool checkUnsavedChanges() const = 0;

public slots:

  /*!
   * \brief Set the language
   * \param[in] language GUI language
   */
  virtual void setLanguage(const QString &language) = 0;

  /*!
   * \brief Add a project to the history
   * \param[in] project Project path
   */
  virtual void addToHistory(const QString &project) = 0;

  /*!
   * \brief Clear the history of recent projects
   */
  virtual void clearHistory() = 0;

  /*!
   * \brief Set the size number of history items
   * \param[in] maxSize History size
   */
  virtual void setHistoryMaxSize(int maxSize) = 0;

  /*!
   * \brief Set Image Viewer background color
   * \param bgColor Hex value
   */
  virtual void setImageViewerBGcolor(const QString &bgColor) = 0;

  /*!
   * \brief Set Keypoints format
   * \param[in] format Supported formats: "Binary", "XML" or "YML"
   */
  virtual void setKeypointsFormat(const QString &format) = 0;

  /*!
   * \brief Set Matches format
   * \param[in] format Supported formats: "Binary", "XML" or "YML"
   */
  virtual void setMatchesFormat(const QString &format) = 0;

  virtual void setUseCuda(bool active) = 0;

  virtual void setAcebsfBlockSize(const QSize &blockSize) = 0;
  virtual void setAcebsfL(double) = 0;
  virtual void setAcebsfK1(double) = 0;
  virtual void setAcebsfK2(double) = 0;

  virtual void setClaheClipLimit(double clipLimit) = 0;
  virtual void setClaheTilesGridSize (const QSize &tilesGridSize) = 0;

  virtual void setCmbfheBlockSize(const QSize &size) = 0;

  virtual void setDheX(int x) = 0;

  virtual void setFaheBlockSize(const QSize &size) = 0;

  virtual void setHmclaheBlockSize(const QSize &size) = 0;
  virtual void setHmclaheL(double l) = 0;
  virtual void setHmclahePhi(double phi) = 0;

  virtual void setLceBsescsBlockSize(const QSize &blockSize) = 0;

  virtual void setMsrcpSmallScale(double smallScale) = 0;
  virtual void setMsrcpMidScale(double midScale) = 0;
  virtual void setMsrcpLargeScale(double largeScale) = 0;

  virtual void setNoshpBlockSize(const QSize &blockSize) = 0;

  virtual void setPoheBlockSize(const QSize &blockSize) = 0;

  virtual void setRswheHistogramDivisions(int histogramDivisions) = 0;
  virtual void setRswheHistogramCut(int histogramCut) = 0;

  virtual void setWallisContrast(double contrast) = 0;
  virtual void setWallisBrightness(double brightness) = 0;
  virtual void setWallisImposedAverage(int imposedAverage) = 0;
  virtual void setWallisImposedLocalStdDev(int imposedLocalStdDev) = 0;
  virtual void setWallisKernelSize(int kernelSize) = 0;

  virtual void setAgastThreshold(int threshold) = 0;
  virtual void setAgastNonmaxSuppression(bool nonmaxSuppression) = 0;
  virtual void setAgastDetectorType(const QString &detectorType) = 0;

  virtual void setAkazeDescriptorType(const QString &descriptorType) = 0;
  virtual void setAkazeDescriptorSize(int descriptorSize) = 0;
  virtual void setAkazeDescriptorChannels(int channels) = 0;
  virtual void setAkazeThreshold(double threshold) = 0;
  virtual void setAkazeOctaves(int octaves) = 0;
  virtual void setAkazeOctaveLayers(int octaveLayers) = 0;
  virtual void setAkazeDiffusivity(const QString &diffusivity) = 0;

  virtual void setBoostDescriptorType(const QString &descriptorType) = 0;
  virtual void setBoostUseOrientation(bool useOrientation) = 0;
  virtual void setBoostScaleFactor(double scaleFactor) = 0;

  virtual void setBriefBytes(const QString &bytes) = 0;
  virtual void setBriefUseOrientation(bool useOrientation) = 0;

  virtual void setBriskThreshold(int threshold) = 0;
  virtual void setBriskOctaves(int octaves) = 0;
  virtual void setBriskPatternScale(double patternScale) = 0;

  virtual void setDaisyRadius(double radius) = 0;
  virtual void setDaisyQRadius(int qRadius) = 0;
  virtual void setDaisyQTheta(int qTheta) = 0;
  virtual void setDaisyQHist(int qHist) = 0;
  virtual void setDaisyNorm(const QString &norm) = 0;
  virtual void setDaisyInterpolation(bool interpolation) = 0;
  virtual void setDaisyUseOrientation(bool useOrientation) = 0;

  virtual void setFastThreshold(int threshold) = 0;
  virtual void setFastNonmaxSuppression(bool nonmaxSuppression) = 0;
  virtual void setFastDetectorType(QString detectorType) = 0;

  virtual void setFreakOrientationNormalized(bool orientationNormalized) = 0;
  virtual void setFreakScaleNormalized(bool scaleNormalized) = 0;
  virtual void setFreakPatternScale(double patternScale) = 0;
  virtual void setFreakOctaves(int octaves) = 0;

  virtual void setGfttMaxFeatures(int maxFeatures) = 0;
  virtual void setGfttQualityLevel(double qlevel) = 0;
  virtual void setGfttMinDistance(double minDistance) = 0;
  virtual void setGfttBlockSize(int blockSize) = 0;
  virtual void setGfttHarrisDetector(bool value) = 0;
  virtual void setGfttK(double k) = 0;

  virtual void setHogWinSize(const QSize &winSize) = 0;
  virtual void setHogBlockSize(const QSize &blockSize) = 0;
  virtual void setHogBlockStride(const QSize &blockStride) = 0;
  virtual void setHogCellSize(const QSize &cellSize) = 0;
  virtual void setHogNbins(int nbins) = 0;
  virtual void setHogDerivAperture(int derivAperture) = 0;

  virtual void setKazeExtendedDescriptor(bool extended) = 0;
  virtual void setKazeUpright(bool upright) = 0;
  virtual void setKazeThreshold(double threshold) = 0;
  virtual void setKazeOctaves(int octaves) = 0;
  virtual void setKazeOctaveLayers(int octaveLayers) = 0;
  virtual void setKazeDiffusivity(const QString &diffusivity) = 0;

  virtual void setLatchBytes(const QString &bytes) = 0;
  virtual void setLatchRotationInvariance(bool rotationInvariance) = 0;
  virtual void setLatchHalfSsdSize(int halfSsdSize) = 0;

  virtual void setLucidKernel(int lucidKernel) = 0;
  virtual void setLucidBlurKernel(int blurKernel) = 0;

  virtual void setMsdThresholdSaliency(double thresholdSaliency) = 0;
  virtual void setMsdPathRadius(int pathRadius) = 0;
  virtual void setMsdKNN(int knn) = 0;
  virtual void setMsdAreaRadius(int areaRadius) = 0;
  virtual void setMsdScaleFactor(double scaleFactor) = 0;
  virtual void setMsdNMSRadius(int NMSRadius) = 0;
  virtual void setMsdNScales(int nScales) = 0;
  virtual void setMsdNMSScaleR(int NMSScaleR) = 0;
  virtual void setMsdComputeOrientations(bool computeOrientations) = 0;
  virtual void setMsdAffineMSD(bool affineMSD) = 0;
  virtual void setMsdTilts(int tilts) = 0;

  virtual void setMserDelta(int delta) = 0;
  virtual void setMserMinArea(int minArea) = 0;
  virtual void setMserMaxArea(int maxArea) = 0;
  virtual void setMserMaxVariation(double maxVariation) = 0;
  virtual void setMserMinDiversity(double minDiversity) = 0;
  virtual void setMserMaxEvolution(int maxEvolution) = 0;
  virtual void setMserAreaThreshold(double areaThreshold) = 0;
  virtual void setMserMinMargin(double minMargin) = 0;
  virtual void setMserEdgeBlurSize(int edgeBlurSize) = 0;

  virtual void setOrbScaleFactor(double scaleFactor) = 0;
  virtual void setOrbFeaturesNumber(int featuresNumber) = 0;
  virtual void setOrbLevelsNumber(int levelsNumber) = 0;
  virtual void setOrbEdgeThreshold(int edgeThreshold) = 0;
  virtual void setOrbWTA_K(int WTA_K) = 0;
  virtual void setOrbScoreType(const QString &scoreType) = 0;
  virtual void setOrbPatchSize(int patchSize) = 0;
  virtual void setOrbFastThreshold(int fastThreshold) = 0;

  virtual void setSiftFeaturesNumber(int featuresNumber) = 0;
  virtual void setSiftOctaveLayers(int octaveLayers) = 0;
  virtual void setSiftContrastThreshold(double contrastThreshold) = 0;
  virtual void setSiftEdgeThreshold(double edgeThreshold) = 0;
  virtual void setSiftSigma(double sigma) = 0;

  virtual void setStarMaxSize(int maxSize) = 0;
  virtual void setStarResponseThreshold(int responseThreshold) = 0;
  virtual void setStarLineThresholdProjected(int lineThresholdProjected) = 0;
  virtual void setStarLineThresholdBinarized(int lineThresholdBinarized) = 0;
  virtual void setStarSuppressNonmaxSize(int suppressNonmaxSize) = 0;

  virtual void setSurfHessianThreshold(double hessianThreshold) = 0;
  virtual void setSurfOctaves(int octaves) = 0;
  virtual void setSurfOctaveLayers(int octaveLayers) = 0;
  virtual void setSurfExtendedDescriptor(bool extendedDescriptor) = 0;
  virtual void setSurfRotatedFeatures(bool rotatedFeatures) = 0;

  virtual void setVggDescriptorType(const QString &descriptorType) = 0;
  virtual void setVggScaleFactor(double scaleFactor) = 0;
  virtual void setVggSigma(double sigma) = 0;
  virtual void setVggUseNormalizeDescriptor(bool useNormalizeDescriptor) = 0;
  virtual void setVggUseNormalizeImage(bool useNormalizeImage) = 0;
  virtual void setVggUseScaleOrientation(bool useScaleOrientation) = 0;

  virtual void setMatchMethod(const QString &matchingMethod) = 0;
  virtual void setMatchStrategy(const QString &matchingMethod) = 0;
  virtual void setMatchNormType(const QString &normType) = 0;
  virtual void setMatchRatio(double ratio) = 0;
  virtual void setMatchDistance(double distance) = 0;
  virtual void setMatchConfidence(double confidence) = 0;
  virtual void setMatchCrossMatching(bool crossMatching) = 0;
  virtual void setMatchMaxIters(int maxIters) = 0;
  virtual void setMatchGeometricTest(const QString &geometricTest) = 0;
  virtual void setMatchHomographyComputeMethod(const QString &computeMethod) = 0;
  virtual void setMatchFundamentalComputeMethod(const QString &computeMethod) = 0;
  virtual void setMatchEssentialComputeMethod(const QString &computeMethod) = 0;

  virtual void setKeypointsViewerBGColor(const QString &color) = 0;
  virtual void setKeypointsViewerMarkerType(int type) = 0;
  virtual void setKeypointsViewerMarkerSize(int size) = 0;
  virtual void setKeypointsViewerMarkerWidth(int width) = 0;
  virtual void setKeypointsViewerMarkerColor(const QString &color) = 0;
  virtual void setKeypointsViewerSelectMarkerWidth(int width) = 0;
  virtual void setKeypointsViewerSelectMarkerColor(const QString &color) = 0;

  virtual void setMatchesViewerBGColor(const QString &color) = 0;
  virtual void setMatchesViewerMarkerType(int type) = 0;
  virtual void setMatchesViewerMarkerSize(int size) = 0;
  virtual void setMatchesViewerMarkerWidth(int width) = 0;
  virtual void setMatchesViewerMarkerColor(const QString &color) = 0;
  virtual void setMatchesViewerSelectMarkerWidth(int width) = 0;
  virtual void setMatchesViewerSelectMarkerColor(const QString &color) = 0;
  virtual void setMatchesViewerLineColor(const QString &color) = 0;
  virtual void setMatchesViewerLineWidth(int width) = 0;

  virtual void setGroundTruthEditorBGColor(const QString &bgColor) = 0;
  virtual void setGroundTruthEditorMarkerSize(int size) = 0;
  virtual void setGroundTruthEditorMarkerWidth(int width) = 0;
  virtual void setGroundTruthEditorMarkerColor(const QString &color) = 0;
  virtual void setGroundTruthEditorSelectMarkerWidth(int width) = 0;
  virtual void setGroundTruthEditorSelectMarkerColor(const QString &color) = 0;
  virtual void setGroundTruthEditorMatrixAdjust(const QString &adjust) = 0;

  virtual void reset() = 0;

signals:

  void unsavedChanges(bool);
};


class SettingsView
  : public PhotoMatchDialogView
{

  Q_OBJECT

public:

  SettingsView(QWidget *parent = nullptr) : PhotoMatchDialogView(parent) {}
  virtual ~SettingsView(){}

  /*!
   * \brief Active language
   */
  virtual QString activeLanguage() const = 0;

  /*!
   * \brief History size
   */
  virtual int historyMaxSize() const = 0;

  virtual QString imageViewerBGColor() const = 0;

  virtual QString keypointsFormat() const = 0;
  virtual QString matchesFormat() const = 0;
  virtual bool useCuda() const = 0;

  virtual QString keypointsViewerBGColor() const = 0;
  virtual int keypointsViewerMarkerType() const = 0;
  virtual int keypointsViewerMarkerSize() const = 0;
  virtual int keypointsViewerMarkerWidth() const = 0;
  virtual QString keypointsViewerMarkerColor() const = 0;
  virtual int selectKeypointsViewerMarkerWidth() const = 0;
  virtual QString selectKeypointsViewerMarkerColor() const = 0;

  virtual QString matchesViewerBGColor() const = 0;
  virtual int matchesViewerMarkerType() const = 0;
  virtual int matchesViewerMarkerSize() const = 0;
  virtual int matchesViewerMarkerWidth() const = 0;
  virtual QString matchesViewerMarkerColor() const = 0;
  virtual int selectMatchesViewerMarkerWidth() const = 0;
  virtual QString selectMatchesViewerMarkerColor() const = 0;
  virtual QString matchesViewerLineColor() const = 0;
  virtual int matchesViewerLineWidth() const = 0;

  virtual QString groundTruthEditorBGColor() const = 0;
  virtual int groundTruthEditorMarkerSize() const = 0;
  virtual int groundTruthEditorMarkerWidth() const = 0;
  virtual QString groundTruthEditorMarkerColor() const = 0;
  virtual int selectGroundTruthEditorMarkerWidth() const = 0;
  virtual QString selectGroundTruthEditorMarkerColor() const = 0;
  virtual QString groundTruthEditorMatrixAdjust() const = 0;

public slots:

  /*!
   * \brief Set active page
   * \param[in] page Active page
   */
  virtual void setPage(int page) = 0;

  /*!
   * \brief Set available languages
   * \param[in] languages Available languages
   */
  virtual void setLanguages(const QStringList &languages) = 0;

  /*!
   * \brief Set active language
   * \param[in] language Active language
   */
  virtual void setActiveLanguage(const QString &language) = 0;

  /*!
   * \brief Set history size
   * \param[in] size History size
   */
  virtual void setHistoryMaxSize(int size) = 0;

  virtual void setImageViewerBGcolor(const QString &color) = 0;

  virtual void setKeypointsFormat(const QString &format) = 0;
  virtual void setMatchesFormat(const QString &format) = 0;
  virtual void setUseCuda(bool active) = 0;
  virtual void setCudaEnabled(bool enabled) = 0;

  virtual void addPreprocess(QWidget *preprocess) = 0;
  virtual void addFeatureDetectorMethod(QWidget *detector) = 0;
  virtual void addDescriptorMatcher(QWidget *detector) = 0;

  virtual void setKeypointsViewerBGColor(const QString &color) = 0;
  virtual void setKeypointsViewerMarkerType(int type) = 0;
  virtual void setKeypointsViewerMarkerSize(int size) = 0;
  virtual void setKeypointsViewerMarkerWidth(int width) = 0;
  virtual void setKeypointsViewerMarkerColor(const QString &color) = 0;
  virtual void setSelectKeypointsViewerMarkerWidth(int width) = 0;
  virtual void setSelectKeypointsViewerMarkerColor(const QString &color) = 0;

  virtual void setMatchesViewerBGColor(const QString &color) = 0;
  virtual void setMatchesViewerMarkerType(int type) = 0;
  virtual void setMatchesViewerMarkerSize(int size) = 0;
  virtual void setMatchesViewerMarkerWidth(int width) = 0;
  virtual void setMatchesViewerMarkerColor(const QString &color) = 0;
  virtual void setSelectMatchesViewerMarkerWidth(int width) = 0;
  virtual void setSelectMatchesViewerMarkerColor(const QString &color) = 0;
  virtual void setMatchesViewerLineColor(const QString &color) = 0;
  virtual void setMatchesViewerLineWidth(int width) = 0;

  virtual void setGroundTruthEditorBGColor(const QString &bgColor) = 0;
  virtual void setGroundTruthEditorMarkerSize(int size) = 0;
  virtual void setGroundTruthEditorMarkerWidth(int width) = 0;
  virtual void setGroundTruthEditorMarkerColor(const QString &color) = 0;
  virtual void setSelectGroundTruthEditorMarkerWidth(int width) = 0;
  virtual void setSelectGroundTruthEditorMarkerColor(const QString &color) = 0;
  virtual void setGroundTruthEditorMatrixAdjust(const QString &matrix) = 0;

  virtual void setUnsavedChanges(bool unsaveChanges) = 0;

signals:

  void languageChange(QString);
  void historyMaxSizeChange(int);
  void imageViewerBGColorChange(QString);
  void keypointsFormatChange(QString);
  void matchesFormatChange(QString);
  void useCudaChange(bool);
  void applyChanges();

  void keypointsViewerBGColorChange(QString);
  void keypointsViewerMarkerTypeChange(int);
  void keypointsViewerMarkerSizeChange(int);
  void keypointsViewerMarkerWidthChange(int);
  void keypointsViewerMarkerColorChange(QString);
  void selectKeypointsViewerMarkerWidthChange(int);
  void selectKeypointsViewerMarkerColorChange(QString);

  void matchesViewerBGColorChange(QString);
  void matchesViewerMarkerTypeChange(int);
  void matchesViewerMarkerSizeChange(int);
  void matchesViewerMarkerWidthChange(int);
  void matchesViewerMarkerColorChange(QString);
  void matchesViewerLineWidthChange(int);
  void matchesViewerLineColorChange(QString);
  void selectMatchesViewerMarkerWidthChange(int);
  void selectMatchesViewerMarkerColorChange(QString);

  void groundTruthEditorBGColorChange(QString);
  void groundTruthEditorMarkerSizeChange(int);
  void groundTruthEditorMarkerWidthChange(int);
  void groundTruthEditorMarkerColorChange(QString);
  void selectGroundTruthEditorMarkerWidthChange(int);
  void selectGroundTruthEditorMarkerColorChange(QString);
  void groundTruthEditorMatrixAdjustChange(QString);
};


class SettingsPresenter
  : public PhotoMatchPresenter
{
  Q_OBJECT

public:

  SettingsPresenter() {}
  virtual ~SettingsPresenter(){}

public slots:

  virtual void openViewSettings() = 0;
  virtual void openQualityControlSettings() = 0;
  virtual void openToolSettings() = 0;

signals:

private slots:

  /*!
   * \brief Establece el idioma de la aplicación
   * \param[in] language
   */
  virtual void setLanguage(const QString &language) = 0;

  /*!
   * \brief save
   */
  virtual void save() = 0;

  /*!
   * \brief discart
   */
  virtual void discart() = 0;
};


} // namespace photomatch

#endif // SETTINGS_H
