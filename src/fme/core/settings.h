#ifndef FME_SETTINGS_H
#define FME_SETTINGS_H

#include "fme/fme_global.h"

#include <QString>
#include <QStringList>
#include <QSize>

#include "fme/core/features.h"
#include "fme/core/preprocess.h"


class QSettings;

namespace fme
{

/*----------------------------------------------------------------*/

/*!
 * \brief Settings interface
 */
class FME_EXPORT ISettings
{

public:

  ISettings() {}
  virtual ~ISettings() = default;

  /*!
   * \brief Idioma actual
   * \return
   */
  virtual QString language() const = 0;

  /*!
   * \brief Establece el idioma del programa
   * \param[in] language Idioma
   */
  virtual void setLanguage(const QString &language) = 0;

  /*!
   * \brief Historial del proyectos recientes
   * \return Listado con los proyectos recientes
   */
  virtual QStringList history() const = 0;

  /*!
   * \brief Añade un proyecto al historial
   * \param[in] project Fichero de proyecto
   */
  virtual void addToHistory(const QString &project) = 0;

  /*!
   * \brief Borra el historial de proyectos recientes
   */
  virtual void clearHistory() = 0;

  /*!
   * \brief Tamaño máximo del historial
   * \return
   */
  virtual int historyMaxSize() const = 0;

  /*!
   * \brief Establece el tamaño máximo de elementos del historial
   * \param[in] maxSize Tamaño máximo del historial
   */
  virtual void setHistoryMaxSize(int maxSize) = 0;

  virtual IClahe *clahe() = 0;
  virtual const IClahe *clahe() const = 0;
  virtual ICmbfhe *cmbfhe() = 0;
  virtual const ICmbfhe *cmbfhe() const = 0;
  virtual IDhe *dhe() = 0;
  virtual const IDhe *dhe() const = 0;
  virtual IFahe *fahe() = 0;
  virtual const IFahe *fahe() const = 0;
  virtual IHmclahe *hmclahe() = 0;
  virtual const IHmclahe *hmclahe() const = 0;
  virtual ILceBsescs *lceBsescs() = 0;
  virtual const ILceBsescs *lceBsescs() const = 0;
  virtual IMsrcp *msrcp() = 0;
  virtual const IMsrcp *msrcp() const = 0;
  virtual INoshp *noshp() = 0;
  virtual const INoshp *noshp() const = 0;
  virtual IPohe *pohe() = 0;
  virtual const IPohe *pohe() const = 0;
  virtual IRswhe *rswhe() = 0;
  virtual const IRswhe *rswhe() const = 0;
  virtual IWallis *wallis() = 0;
  virtual const IWallis *wallis() const = 0;


  virtual IAgast *agast() = 0;
  virtual const IAgast *agast() const = 0;
  virtual IAkaze *akaze() = 0;
  virtual const IAkaze *akaze() const = 0;
  virtual IBrief *brief() = 0;
  virtual const IBrief *brief() const = 0;
  virtual IBrisk *brisk() = 0;
  virtual const IBrisk *brisk() const = 0;
  virtual IDaisy *daisy() = 0;
  virtual const IDaisy *daisy() const = 0;
  virtual IFast *fast() = 0;
  virtual const IFast *fast() const = 0;
  virtual IFreak *freak() = 0;
  virtual const IFreak *freak() const = 0;
  virtual IGftt *gftt() = 0;
  virtual const IGftt *gftt() const = 0;
  virtual IHog *hog() = 0;
  virtual const IHog *hog() const = 0;
  virtual IKaze *kaze() = 0;
  virtual const IKaze *kaze() const = 0;
  virtual ILatch *latch() = 0;
  virtual const ILatch *latch() const = 0;
  virtual ILucid *lucid() = 0;
  virtual const ILucid *lucid() const = 0;
  virtual IMsd *msd() = 0;
  virtual const IMsd *msd() const = 0;
  virtual IMser *mser() = 0;
  virtual const IMser *mser() const = 0;
  virtual IOrb *orb() = 0;
  virtual const IOrb *orb() const = 0;
  virtual ISift *sift() = 0;
  virtual const ISift *sift() const = 0;
  virtual IStar *star() = 0;
  virtual const IStar *star() const = 0;
  virtual ISurf *surf() = 0;
  virtual const ISurf *surf() const = 0;

  /*!
   * \brief Recupera la configuración por defecto
   */
  virtual void reset() = 0;
};


/*----------------------------------------------------------------*/


/*!
 * \brief Settings read and write interface
 */
class FME_EXPORT ISettingsRW
{

public:

  ISettingsRW() {}
  virtual ~ISettingsRW() = default;

  /*!
   * \brief read
   * \return
   */
  virtual void read(ISettings &settings) = 0;

  /*!
   * \brief write
   * \return
   */
  virtual void write(const ISettings &settings) = 0;

  virtual void writeHistory(const ISettings &settings) = 0;
};



/*----------------------------------------------------------------*/
/* Feature Detectors/descriptors                                  */
/*----------------------------------------------------------------*/


/*!
 * \brief AGAST detector properties class
 */
class FME_EXPORT Agast
  : public IAgast
{

public:

  Agast();
  ~Agast() override;

// IAgast interface

public:

  int threshold() const override;
  bool nonmaxSuppression() const override;
  QString detectorType() const override;
  void setThreshold(int threshold) override;
  void setNonmaxSuppression(bool nonmaxSuppression) override;
  void setDetectorType(const QString &detectorType) override;
  void reset() override;

protected:

  int mThreshold;
  bool mNonmaxSuppression;
  QString mDetectorType;

};


/*----------------------------------------------------------------*/


/*!
 * \brief AKAZE detector/descriptor properties class
 */
class FME_EXPORT Akaze
  : public IAkaze
{

public:

  Akaze();
  ~Akaze() override;

// IAkaze interface

public:

  QString descriptorType() const override;
  int descriptorSize() const override;
  int descriptorChannels() const override;
  double threshold() const override;
  int octaves() const override;
  int octaveLayers() const override;
  QString diffusivity() const override;
  void setDescriptorType(const QString &descriptorType) override;
  void setDescriptorSize(int descriptorSize) override;
  void setDescriptorChannels(int channels) override;
  void setThreshold(double threshold) override;
  void setOctaves(int octaves) override;
  void setOctaveLayers(int octaveLayers) override;
  void setDiffusivity(const QString &diffusivity) override;
  void reset() override;

protected:

  QString mDescriptorType;
  int mDescriptorSize;
  int mDescriptorChannels;
  double mThreshold;
  int mOctaves;
  int mOctaveLayers;
  QString mDiffusivity;

};


/*----------------------------------------------------------------*/


class FME_EXPORT Brief
  : public IBrief
{
public:

  Brief();
  ~Brief() override;

// IBrief interface

public:

  QString bytes() const override;
  bool useOrientation() const override;
  void setBytes(const QString &bytes) override;
  void setUseOrientation(bool useOrientation) override;
  void reset() override;

protected:

  QString mBytes;
  bool mUseOrientation;
};


/*----------------------------------------------------------------*/

class FME_EXPORT Brisk
  : public IBrisk
{
public:

  Brisk();
  ~Brisk() override;

  // IBrisk interface
public:
  int threshold() const override;
  int octaves() const override;
  double patternScale() const override;
  void setThreshold(int threshold) override;
  void setOctaves(int octaves) override;
  void setPatternScale(double patternScale) override;
  void reset() override;

protected:

  int mThreshold;
  int mOctaves;
  double mPatternScale;
};

/*----------------------------------------------------------------*/

class FME_EXPORT Daisy
  : public IDaisy
{
public:

  Daisy();
  ~Daisy() override;

// IDaisy interface

public:

  double radius() const override;
  int qRadius() const override;
  int qTheta() const override;
  int qHist() const override;
  QString norm() const override;
  bool interpolation() const override;
  bool useOrientation() const override;
  void setRadius(double radius) override;
  void setQRadius(int qRadius) override;
  void setQTheta(int qTheta) override;
  void setQHist(int qHist) override;
  void setNorm(const QString &norm) override;
  void setInterpolation(bool interpolation) override;
  void setUseOrientation(bool useOrientation) override;
  void reset() override;

protected:

  double mRadius;
  int mQRadius;
  int mQTheta;
  int mQHist;
  QString mNorm;
  bool mInterpolation;
  bool mUseOrientation;
};

/*----------------------------------------------------------------*/

class FME_EXPORT Fast
  : public IFast
{
public:

  Fast();
  ~Fast() override;

// IFast interface

public:

  int threshold() const override;
  bool nonmaxSuppression() const override;
  QString detectorType() const override;
  void setThreshold(int threshold) override;
  void setNonmaxSuppression(bool nonmaxSuppression) override;
  void setDetectorType(QString detectorType) override;
  void reset() override;

protected:

  int mThreshold;
  bool mNonmaxSuppression;
  QString mDetectorType;
};

/*----------------------------------------------------------------*/

class FME_EXPORT Freak
  : public IFreak
{

public:

  Freak();
  ~Freak() override;

  // IFreak interface
public:
  bool orientationNormalized() const override;
  bool scaleNormalized() const override;
  double patternScale() const override;
  int octaves() const override;
  void setOrientationNormalized(bool orientationNormalized) override;
  void setScaleNormalized(bool scaleNormalized) override;
  void setPatternScale(double patternScale) override;
  void setOctaves(int octaves) override;
  void reset() override;

protected:

  bool mOrientationNormalized;
  bool mScaleNormalized;
  double mPatternScale;
  int mOctaves;
};

/*----------------------------------------------------------------*/

class FME_EXPORT Gftt
  : public IGftt
{
public:

  Gftt();
  ~Gftt() override;

  // IGftt interface
public:
  int maxFeatures() const override;
  double qualityLevel() const override;
  double minDistance() const override;
  int blockSize() const override;
  bool harrisDetector() const override;
  double k() const override;
  void setMaxFeatures(int maxFeatures) override;
  void setQualityLevel(double qlevel) override;
  void setMinDistance(double minDistance) override;
  void setBlockSize(int blockSize) override;
  void setHarrisDetector(bool value) override;
  void setK(double k) override;
  void reset() override;

protected:

  int mMaxFeatures;
  double mQualityLevel;
  double mMinDistance;
  int mBlockSize;
  bool mHarrisDetector;
  double mK;

};


/*----------------------------------------------------------------*/

class FME_EXPORT Hog
  : public IHog
{
public:

  Hog();
  ~Hog() override;

// IHog interface

public:

  QSize winSize() const override;
  QSize blockSize() const override;
  QSize blockStride() const override;
  QSize cellSize() const override;
  int nbins() const override;
  int derivAperture() const override;
  void setWinSize(const QSize &winSize) override;
  void setBlockSize(const QSize &blockSize) override;
  void setBlockStride(const QSize &blockStride) override;
  void setCellSize(const QSize &cellSize) override;
  void setNbins(int nbins) override;
  void setDerivAperture(int derivAperture) override;
  void reset() override;

protected:

  QSize mWinSize;
  QSize mBlockSize;
  QSize mBlockStride;
  QSize mCellSize;
  int mNbins;
  int mDerivAperture;
};

/*----------------------------------------------------------------*/

class FME_EXPORT Kaze
  : public IKaze
{
public:

  Kaze();
  ~Kaze() override;

// IKaze interface

public:

  bool extendedDescriptor() const override;
  bool upright() const override;
  double threshold() const override;
  int octaves() const override;
  int octaveLayers() const override;
  QString diffusivity() const override;
  void setExtendedDescriptor(bool extended) override;
  void setUpright(bool upright) override;
  void setThreshold(double threshold) override;
  void setOctaves(int octaves) override;
  void setOctaveLayers(int octaveLayers) override;
  void setDiffusivity(const QString &diffusivity) override;
  void reset() override;

protected:

  bool mExtended;
  bool mUpright;
  double mThreshold;
  int mOctaves;
  int mOctaveLayers;
  QString mDiffusivity;

};


/*----------------------------------------------------------------*/

class FME_EXPORT Latch
  : public ILatch
{
public:

  Latch();
  ~Latch() override;

// ILatch interface

public:

  QString bytes() const override;
  bool rotationInvariance() const override;
  int halfSsdSize() const override;
  void setBytes(const QString &bytes) override;
  void setRotationInvariance(bool rotationInvariance) override;
  void setHalfSsdSize(int halfSsdSize) override;
  void reset() override;

protected:

  QString mBytes;
  bool mRotationInvariance;
  int mHalfSsdSize;
};

/*----------------------------------------------------------------*/

class FME_EXPORT Lucid
  : public ILucid
{
public:

  Lucid();
  ~Lucid() override;

// ILucid interface

public:

  int lucidKernel() const override;
  int blurKernel() const override;
  void setLucidKernel(int lucidKernel) override;
  void setBlurKernel(int blurKernel) override;
  void reset() override;

protected:

  int mLucidKernel;
  int mBlurKernel;
};


/*----------------------------------------------------------------*/

class FME_EXPORT Msd
  : public IMsd
{
public:

  Msd();
  ~Msd() override;

// IMsd interface
public:

  double thresholdSaliency() const override;
  int pathRadius() const override;
  int knn() const override;
  int areaRadius() const override;
  double scaleFactor() const override;
  int NMSRadius() const override;
  int nScales() const override;
  int NMSScaleR() const override;
  bool computeOrientations() const override;
  bool affineMSD() const override;
  int tilts() const override;
  void setThresholdSaliency(double thresholdSaliency) override;
  void setPathRadius(int pathRadius) override;
  void setKNN(int knn) override;
  void setAreaRadius(int areaRadius) override;
  void setScaleFactor(double scaleFactor) override;
  void setNMSRadius(int NMSRadius) override;
  void setNScales(int nScales) override;
  void setNMSScaleR(int NMSScaleR) override;
  void setComputeOrientations(bool computeOrientations) override;
  void setAffineMSD(bool affineMSD) override;
  void setTilts(int tilts) override;
  void reset() override;

protected:

  double mThresholdSaliency;
  int mPathRadius;
  int mKNN;
  int mAreaRadius;
  double mScaleFactor;
  int mNMSRadius;
  int mNScales;
  int mNMSScaleR;
  bool mComputeOrientations;
  bool mAffineMSD;
  int mTilts;
};

/*----------------------------------------------------------------*/

class FME_EXPORT Mser
  : public IMser
{
public:

  Mser();
   ~Mser() override;

// IMser interface

public:

  int delta() const override;
  int minArea() const override;
  int maxArea() const override;
  double maxVariation() const override;
  double minDiversity() const override;
  int maxEvolution() const override;
  double areaThreshold() const override;
  double minMargin() const override;
  int edgeBlurSize() const override;
  void setDelta(int delta) override;
  void setMinArea(int minArea) override;
  void setMaxArea(int maxArea) override;
  void setMaxVariation(double maxVariation) override;
  void setMinDiversity(double minDiversity) override;
  void setMaxEvolution(int maxEvolution) override;
  void setAreaThreshold(double areaThreshold) override;
  void setMinMargin(double minMargin) override;
  void setEdgeBlurSize(int edgeBlurSize) override;
  void reset() override;

protected:

  int mDelta;
  int mMinArea;
  int mMaxArea;
  double mMaxVariation;
  double mMinDiversity;
  int mMaxEvolution;
  double mAreaThreshold;
  double mMinMargin;
  int mEdgeBlurSize;
};

/*----------------------------------------------------------------*/

class FME_EXPORT Orb
  : public IOrb
{
public:

  Orb();
   ~Orb() override;

// IOrb interface

public:

  int featuresNumber() const override;
  double scaleFactor() const override;
  int levelsNumber() const override;
  int edgeThreshold() const override;
  int wta_k() const override;
  QString scoreType() const override;
  int patchSize() const override;
  int fastThreshold() const override;
  void setScaleFactor(double scaleFactor) override;
  void setFeaturesNumber(int featuresNumber) override;
  void setLevelsNumber(int levelsNumber) override;
  void setEdgeThreshold(int edgeThreshold) override;
  void setWTA_K(int WTA_K) override;
  void setScoreType(const QString &scoreType) override;
  void setPatchSize(int patchSize) override;
  void setFastThreshold(int fastThreshold) override;
  void reset() override;

protected:

  int mFeaturesNumber;
  double mScaleFactor;
  int mLevelsNumber;
  int mEdgeThreshold;
  int mWTA_K;
  QString mScoreType;
  int mPatchSize;
  int mFastThreshold;
};


/*----------------------------------------------------------------*/


/*!
 * \brief SIFT detector/descriptor properties class
 */
class FME_EXPORT Sift
  : public ISift
{

public:

  Sift();
  ~Sift() override;

// ISift interface

public:

  int featuresNumber() const override;
  int octaveLayers() const override;
  double contrastThreshold() const override;
  double edgeThreshold() const override;
  double sigma() const override;
  void setFeaturesNumber(int featuresNumber) override;
  void setOctaveLayers(int octaveLayers) override;
  void setContrastThreshold(double contrastThreshold) override;
  void setEdgeThreshold(double edgeThreshold) override;
  void setSigma(double sigma) override;
  void reset() override;

protected:

  int mFeaturesNumber;
  int mOctaveLayers;
  double mContrastThreshold;
  double mEdgeThreshold;
  double mSigma;
};


/*----------------------------------------------------------------*/

class FME_EXPORT Star
  : public IStar
{
public:

  Star();
  ~Star() override;

// IStar interface

public:

  int maxSize() const override;
  int responseThreshold() const override;
  int lineThresholdProjected() const override;
  int lineThresholdBinarized() const override;
  int suppressNonmaxSize() const override;
  void setMaxSize(int maxSize) override;
  void setResponseThreshold(int responseThreshold) override;
  void setLineThresholdProjected(int lineThresholdProjected) override;
  void setLineThresholdBinarized(int lineThresholdBinarized) override;
  void setSuppressNonmaxSize(int suppressNonmaxSize) override;
  void reset() override;

protected:

  int mMaxSize;
  int mResponseThreshold;
  int mLineThresholdProjected;
  int mLineThresholdBinarized;
  int mSuppressNonmaxSize;
};

/*----------------------------------------------------------------*/


/*!
 * \brief SURF detector/descriptor properties class
 */
class FME_EXPORT Surf
  : public ISurf
{

public:

  Surf();
  ~Surf() override;

  // ISurf interface

public:

  double hessianThreshold() const override;
  void setHessianThreshold(double hessianThreshold) override;
  int octaves() const override;
  void setOctaves(int octaves) override;
  int octaveLayers() const override;
  void setOctaveLayers(int octaveLayers) override;
  bool extendedDescriptor() const override;
  void setExtendedDescriptor(bool extendedDescriptor) override;
  bool rotatedFeatures() const override;
  void setRotatedFeatures(bool rotatedFeatures) override;
  void reset() override;

protected:

  double mHessianThreshold;
  int mOctaves;
  int mOctaveLayers;
  bool mExtendedDescriptor;
  bool mRotatedFeatures;
};


/*----------------------------------------------------------------*/
/* Image preprocessing                                            */
/*----------------------------------------------------------------*/


/*!
 * \brief CLAHE image preprocess class
 */
class FME_EXPORT Clahe
  : public IClahe
{

public:

  Clahe();
  ~Clahe() override = default;

// IClahe interface

public:

  double clipLimit() const override;
  void setClipLimit(double clipLimit) override;
  QSize tilesGridSize() const override;
  void setTilesGridSize(const QSize &tilesGridSize) override;

  void reset() override;

protected:

  double mClipLimit;
  QSize mTilesGridSize;
};


/*----------------------------------------------------------------*/


/*!
 * \brief CMBFHE image preprocess class
 */
class FME_EXPORT Cmbfhe
  : public ICmbfhe
{
public:
  Cmbfhe();
  ~Cmbfhe() override {}

// ICmbfhe interface

public:

  QSize blockSize() const override;
  void setBlockSize(const QSize &blockSize) override;

  void reset() override;

protected:

  QSize mBlockSize;
};


/*----------------------------------------------------------------*/


class FME_EXPORT Dhe
  : public IDhe
{

public:

  Dhe();
  ~Dhe() override = default;

// IDhe interface

public:

  int x() const override;
  void setX(int x) override;

  void reset() override;

protected:

  int mX;
};


/*----------------------------------------------------------------*/


/*!
 * \brief Fahe image preprocess class
 */
class FME_EXPORT Fahe
  : public IFahe
{

public:

  Fahe();
  ~Fahe() override = default;

  QSize blockSize() const override;
  void setBlockSize(const QSize &blockSize) override;

  void reset() override;

protected:

  QSize mBlockSize;

};


/*----------------------------------------------------------------*/


class FME_EXPORT Hmclahe
  : public IHmclahe
{

public:

  Hmclahe();
  ~Hmclahe() override;

// IHmclahe interface

public:

  QSize blockSize() const override;
  void setBlockSize(const QSize &blockSize) override;
  double l() const override;
  void setL(double l) override;
  double phi() const override;
  void setPhi(double phi) override;

  void reset() override;

protected:

  QSize mBlockSize;
  double mL;
  double mPhi;
};


/*----------------------------------------------------------------*/


class FME_EXPORT LceBsescs
  : public ILceBsescs
{

public:

  LceBsescs();
  ~LceBsescs() override;

// ILceBsescs interface

public:

  QSize blockSize() const override;
  void setBlockSize(const QSize &blockSize) override;

  void reset() override;

protected:

  QSize mBlockSize;
};


/*----------------------------------------------------------------*/


class FME_EXPORT Msrcp
  : public IMsrcp
{

public:

  Msrcp();
  ~Msrcp() override;

// IMsrcp interface

public:

  double smallScale() const override;
  void setSmallScale(double smallScale) override;
  double midScale() const override;
  void setMidScale(double midScale) override;
  double largeScale() const override;
  void setLargeScale(double largeScale) override;

  void reset() override;

protected:

  double mSmallScale;
  double mMidScale;
  double mLargeScale;
};


/*----------------------------------------------------------------*/


class FME_EXPORT Noshp
  : public INoshp
{

public:

  Noshp();
  ~Noshp() override;

// INoshp interface

public:

  QSize blockSize() const override;
  void setBlockSize(const QSize &blockSize) override;

  void reset() override;

protected:

  QSize mBlockSize;

};


/*----------------------------------------------------------------*/


class FME_EXPORT Pohe
  : public IPohe
{

public:

  Pohe();
  ~Pohe() override;

// IPohe interface

public:

  QSize blockSize() const override;
  void setBlockSize(const QSize &blockSize) override;

  void reset() override;

protected:

  QSize mBlockSize;

};


/*----------------------------------------------------------------*/


class FME_EXPORT Rswhe
  : public IRswhe
{

public:

  Rswhe();
  ~Rswhe() override;

// IRswhe interface

public:

  int histogramDivisions() const override;
  void setHistogramDivisions(int histogramDivisions) override;
  HistogramCut histogramCut() const override;
  void setHistogramCut(HistogramCut histogramCut) override;

  void reset() override;

protected:

  HistogramCut mHistogramCut;
  int mHistogramDivisions;

};


/*----------------------------------------------------------------*/


class FME_EXPORT Wallis
  : public IWallis
{

public:

  Wallis();
  ~Wallis() override;

// IWallis interface

public:

  double contrast() const override;
  void setContrast(double contrast) override;
  double brightness() const override;
  void setBrightness(double brightness) override;
  int imposedAverage() const override;
  void setImposedAverage(int imposedAverage) override;
  int imposedLocalStdDev() const override;
  void setImposedLocalStdDev(int imposedLocalStdDev) override;
  int kernelSize() const override;
  void setKernelSize(int kernelSize) override;

  void reset() override;

protected:

  double mContrast;
  double mBrightness;
  int mImposedAverage;
  int mImposedLocalStdDev;
  int mKernelSize;
};

/*----------------------------------------------------------------*/


/*!
 * \brief The Settings class
 */
class FME_EXPORT Settings
  : public ISettings
{

public:

  Settings();
  ~Settings() override;

// ISettings interface

public:

  QString language() const override;
  void setLanguage(const QString &language) override;

  QStringList history() const override;
  void addToHistory(const QString &project) override;
  void clearHistory() override;
  int historyMaxSize() const override;
  void setHistoryMaxSize(int maxSize) override;

  IClahe *clahe() override;
  const IClahe *clahe() const override;
  ICmbfhe *cmbfhe() override;
  const ICmbfhe *cmbfhe() const override;
  IDhe *dhe() override;
  const IDhe *dhe() const override;
  IFahe *fahe() override;
  const IFahe *fahe() const override;
  IHmclahe *hmclahe() override;
  const IHmclahe *hmclahe() const override;
  ILceBsescs *lceBsescs() override;
  const ILceBsescs *lceBsescs() const override;
  IMsrcp *msrcp() override;
  const IMsrcp *msrcp() const override;
  INoshp *noshp() override;
  const INoshp *noshp() const override;
  IPohe *pohe() override;
  const IPohe *pohe() const override;
  IRswhe *rswhe() override;
  const IRswhe *rswhe() const override;
  IWallis *wallis() override;
  const IWallis *wallis() const override;

  IAgast *agast() override;
  const IAgast *agast() const override;
  IAkaze *akaze() override;
  const IAkaze *akaze() const override;
  IBrief *brief() override;
  const IBrief *brief() const override;
  IBrisk *brisk() override;
  const IBrisk *brisk() const override;
  IDaisy *daisy() override;
  const IDaisy *daisy() const override;
  IFast *fast() override;
  const IFast *fast() const override;
  IFreak *freak() override;
  const IFreak *freak() const override;
  IGftt *gftt() override;
  const IGftt *gftt() const override;
  IHog *hog() override;
  const IHog *hog() const override;
  IKaze *kaze() override;
  const IKaze *kaze() const override;
  ILatch *latch() override;
  const ILatch *latch() const override;
  ILucid *lucid() override;
  const ILucid *lucid() const override;
  IMsd *msd() override;
  const IMsd *msd() const override;
  IMser *mser() override;
  const IMser *mser() const override;
  IOrb *orb() override;
  const IOrb *orb() const override;
  ISift *sift() override;
  const ISift *sift() const override;
  IStar *star() override;
  const IStar *star() const override;
  ISurf *surf() override;
  const ISurf *surf() const override;

  void reset() override;

protected:

  QString mLanguage;
  int mHistoyMaxSize;
  QStringList mHistory;

  IClahe *mClahe;
  ICmbfhe *mCmbfhe;
  IDhe *mDhe;
  IFahe *mFahe;
  IHmclahe *mHmclahe;
  ILceBsescs *mLceBsescs;
  IMsrcp *mMsrcp;
  INoshp *mNoshp;
  IPohe *mPohe;
  IRswhe *mRswhe;
  IWallis *mWallis;

  IAgast *mAgast;
  IAkaze *mAkaze;
  IBrief *mBrief;
  IBrisk *mBrisk;
  IDaisy *mDaisy;
  IFast *mFast;
  IFreak *mFreak;
  IGftt *mGftt;
  IHog *mHog;
  IKaze *mKaze;
  ILatch *mLatch;
  ILucid *mLucid;
  IMsd *mMsd;
  IMser *mMser;
  IOrb *mOrb;
  ISift *mSift;
  IStar *mStar;
  ISurf *mSurf;
};


/*----------------------------------------------------------------*/


/*!
 * \brief The SettingsRW class
 */
class FME_EXPORT SettingsRW
  : public ISettingsRW
{

public:

  explicit SettingsRW();
  ~SettingsRW() override;

// ISettingsRW interface

public:

  void read(ISettings &settings) override;
  void write(const ISettings &settings) override;
  void writeHistory(const ISettings &settings) override;

protected:

  QSettings *mSettingsRW;

};

} // namespace fme

#endif // FME_SETTINGS_H
