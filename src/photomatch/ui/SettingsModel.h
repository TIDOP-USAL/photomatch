#ifndef PHOTOMATCH_SETTINGS_MODEL_H
#define PHOTOMATCH_SETTINGS_MODEL_H

#include <QObject>

#include "photomatch/core/settings.h"
#include "photomatch/ui/mvp.h"

namespace photomatch
{

class ISettingsModel
  : public IModel
{

  Q_OBJECT

public:

  ISettingsModel(QObject *parent = nullptr) : IModel(parent) {}
  virtual ~ISettingsModel() override {}

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

  virtual void reset() = 0;

signals:

  void unsavedChanges(bool);
};




class SettingsModel
  : public ISettingsModel
{

  Q_OBJECT

public:

  explicit SettingsModel(Settings *settings,
                         SettingsController *settingsRW,
                         QObject *parent = nullptr);
  ~SettingsModel() override;

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
