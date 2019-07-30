#include "settings.h"

#include "fme/core/features/agast.h"
#include "fme/core/features/akaze.h"
#include "fme/core/features/brief.h"
#include "fme/core/features/brisk.h"
#include "fme/core/features/fast.h"
#include "fme/core/features/kaze.h"

#include <QSettings>
#include <QLocale>

namespace fme
{

/*----------------------------------------------------------------*/
/* Feature Detectors/descriptors properties                       */
/*----------------------------------------------------------------*/

DaisyProperties::DaisyProperties()
  : IDaisy(),
    mRadius(15.),
    mQRadius(3),
    mQTheta(8),
    mQHist(8),
    mNorm("NRM_NONE"),
    mInterpolation(true),
    mUseOrientation(false)
{}

DaisyProperties::~DaisyProperties()
{

}

double DaisyProperties::radius() const
{
  return mRadius;
}

int DaisyProperties::qRadius() const
{
  return mQRadius;
}

int DaisyProperties::qTheta() const
{
  return mQTheta;
}

int DaisyProperties::qHist() const
{
  return mQHist;
}

QString DaisyProperties::norm() const
{
  return mNorm;
}

bool DaisyProperties::interpolation() const
{
  return mInterpolation;
}

bool DaisyProperties::useOrientation() const
{
  return mUseOrientation;
}

void DaisyProperties::setRadius(double radius)
{
  mRadius = radius;
}

void DaisyProperties::setQRadius(int qRadius)
{
  mQRadius = qRadius;
}

void DaisyProperties::setQTheta(int qTheta)
{
  mQTheta = qTheta;
}

void DaisyProperties::setQHist(int qHist)
{
  mQHist = qHist;
}

void DaisyProperties::setNorm(const QString &norm)
{
  mNorm = norm;
}

void DaisyProperties::setInterpolation(bool interpolation)
{
  mInterpolation = interpolation;
}

void DaisyProperties::setUseOrientation(bool useOrientation)
{
  mUseOrientation = useOrientation;
}

void DaisyProperties::reset()
{
  mRadius = 15.;
  mQRadius = 3;
  mQTheta = 8;
  mQHist = 8;
  mNorm = "NRM_NONE";
  mInterpolation = true;
  mUseOrientation = false;
}

/*----------------------------------------------------------------*/

FreakProperties::FreakProperties()
  : IFreak(),
    mOrientationNormalized(true),
    mScaleNormalized(true),
    mPatternScale(22.),
    mOctaves(4)
{}

FreakProperties::~FreakProperties()
{

}

bool FreakProperties::orientationNormalized() const
{
  return mOrientationNormalized;
}

bool FreakProperties::scaleNormalized() const
{
  return mScaleNormalized;
}

double FreakProperties::patternScale() const
{
  return mPatternScale;
}

int FreakProperties::octaves() const
{
  return mOctaves;
}

void FreakProperties::setOrientationNormalized(bool orientationNormalized)
{
  mOrientationNormalized = orientationNormalized;
}

void FreakProperties::setScaleNormalized(bool scaleNormalized)
{
  mScaleNormalized = scaleNormalized;
}

void FreakProperties::setPatternScale(double patternScale)
{
  mPatternScale = patternScale;
}

void FreakProperties::setOctaves(int octaves)
{
  mOctaves = octaves;
}

void FreakProperties::reset()
{
  mOrientationNormalized = true;
  mScaleNormalized = true;
  mPatternScale = 22.;
  mOctaves = 4;
}


/*----------------------------------------------------------------*/


GfttProperties::GfttProperties()
  : IGftt(),
    mMaxFeatures(1000),
    mQualityLevel(0.01),
    mMinDistance(1),
    mBlockSize(3),
    mHarrisDetector(false),
    mK(0.04)
{

}

GfttProperties::~GfttProperties()
{

}

int GfttProperties::maxFeatures() const
{
  return mMaxFeatures;
}

double GfttProperties::qualityLevel() const
{
  return mQualityLevel;
}

double GfttProperties::minDistance() const
{
  return mMinDistance;
}

int GfttProperties::blockSize() const
{
  return mBlockSize;
}

bool GfttProperties::harrisDetector() const
{
  return mHarrisDetector;
}

double GfttProperties::k() const
{
  return mK;
}

void GfttProperties::setMaxFeatures(int maxFeatures)
{
  mMaxFeatures = maxFeatures;
}

void GfttProperties::setQualityLevel(double qlevel)
{
  mQualityLevel = qlevel;
}

void GfttProperties::setMinDistance(double minDistance)
{
  mMinDistance = minDistance;
}

void GfttProperties::setBlockSize(int blockSize)
{
  mBlockSize = blockSize;
}

void GfttProperties::setHarrisDetector(bool value)
{
  mHarrisDetector = value;
}

void GfttProperties::setK(double k)
{
  mK = k;
}

void GfttProperties::reset()
{
  mMaxFeatures = 1000;
  mQualityLevel = 0.01;
  mMinDistance = 1;
  mBlockSize = 3;
  mHarrisDetector = false;
  mK = 0.04;
}

/*----------------------------------------------------------------*/


HogProperties::HogProperties()
  : IHog(),
    mWinSize(128,64),
    mBlockSize(16,16),
    mBlockStride(8,8),
    mCellSize(8,8),
    mNbins(9),
    mDerivAperture(1)
{}

HogProperties::~HogProperties()
{

}

QSize HogProperties::winSize() const
{
  return mWinSize;
}

QSize HogProperties::blockSize() const
{
  return mBlockSize;
}

QSize HogProperties::blockStride() const
{
  return mBlockStride;
}

QSize HogProperties::cellSize() const
{
  return mCellSize;
}

int HogProperties::nbins() const
{
  return mNbins;
}

int HogProperties::derivAperture() const
{
  return mDerivAperture;
}

void HogProperties::setWinSize(const QSize &winSize)
{
  mWinSize = winSize;
}

void HogProperties::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void HogProperties::setBlockStride(const QSize &blockStride)
{
  mBlockStride = blockStride;
}

void HogProperties::setCellSize(const QSize &cellSize)
{
  mCellSize = cellSize;
}

void HogProperties::setNbins(int nbins)
{
  mNbins = nbins;
}

void HogProperties::setDerivAperture(int derivAperture)
{
  mDerivAperture = derivAperture;
}

void HogProperties::reset()
{
  mWinSize = QSize(128,64);
  mBlockSize = QSize(16,16);
  mBlockStride = QSize(8,8);
  mCellSize = QSize(8,8);
  mNbins = 9;
  mDerivAperture = 1;
}


LatchProperties::LatchProperties()
  : ILatch(),
    mBytes("32"),
    mRotationInvariance(true),
    mHalfSsdSize(3)
{}

LatchProperties::~LatchProperties()
{

}

QString LatchProperties::bytes() const
{
  return mBytes;
}

bool LatchProperties::rotationInvariance() const
{
  return mRotationInvariance;
}

int LatchProperties::halfSsdSize() const
{
  return mHalfSsdSize;
}

void LatchProperties::setBytes(const QString &bytes)
{
  mBytes = bytes;
}

void LatchProperties::setRotationInvariance(bool rotationInvariance)
{
  mRotationInvariance = rotationInvariance;
}

void LatchProperties::setHalfSsdSize(int halfSsdSize)
{
  mHalfSsdSize = halfSsdSize;
}

void LatchProperties::reset()
{
  mBytes = "32";
  mRotationInvariance = true;
  mHalfSsdSize = 3;
}

/*----------------------------------------------------------------*/


LucidProperties::LucidProperties()
  : ILucid(),
    mLucidKernel(1),
    mBlurKernel(2)
{}

LucidProperties::~LucidProperties()
{

}

int LucidProperties::lucidKernel() const
{
  return mLucidKernel;
}

int LucidProperties::blurKernel() const
{
  return mBlurKernel;
}

void LucidProperties::setLucidKernel(int lucidKernel)
{
  mLucidKernel = lucidKernel;
}

void LucidProperties::setBlurKernel(int blurKernel)
{
  mBlurKernel = blurKernel;
}

void LucidProperties::reset()
{
  mLucidKernel = 1;
  mBlurKernel = 2;
}

/*----------------------------------------------------------------*/


MsdProperties::MsdProperties()
  : IMsd(),
    mThresholdSaliency(250),
    mPathRadius(3),
    mKNN(4),
    mAreaRadius(5),
    mScaleFactor(1.25),
    mNMSRadius(5),
    mNScales(-1),
    mNMSScaleR(0),
    mComputeOrientations(false),
    mAffineMSD(false),
    mTilts(3)
{}

MsdProperties::~MsdProperties()
{

}

double MsdProperties::thresholdSaliency() const
{
  return mThresholdSaliency;
}

int MsdProperties::pathRadius() const
{
  return mPathRadius;
}

int MsdProperties::knn() const
{
  return mKNN;
}

int MsdProperties::areaRadius() const
{
  return mAreaRadius;
}

double MsdProperties::scaleFactor() const
{
  return mScaleFactor;
}

int MsdProperties::NMSRadius() const
{
  return mNMSRadius;
}

int MsdProperties::nScales() const
{
  return mNScales;
}

int MsdProperties::NMSScaleR() const
{
  return mNMSScaleR;
}

bool MsdProperties::computeOrientations() const
{
  return mComputeOrientations;
}

bool MsdProperties::affineMSD() const
{
  return mAffineMSD;
}

int MsdProperties::tilts() const
{
  return mTilts;
}

void MsdProperties::setThresholdSaliency(double thresholdSaliency)
{
  mThresholdSaliency = thresholdSaliency;
}

void MsdProperties::setPathRadius(int pathRadius)
{
  mPathRadius = pathRadius;
}

void MsdProperties::setKNN(int knn)
{
  mKNN = knn;
}

void MsdProperties::setAreaRadius(int areaRadius)
{
  mAreaRadius = areaRadius;
}

void MsdProperties::setScaleFactor(double scaleFactor)
{
  mScaleFactor = scaleFactor;
}

void MsdProperties::setNMSRadius(int NMSRadius)
{
  mNMSRadius = NMSRadius;
}

void MsdProperties::setNScales(int nScales)
{
  mNScales = nScales;
}

void MsdProperties::setNMSScaleR(int NMSScaleR)
{
  mNMSScaleR = NMSScaleR;
}

void MsdProperties::setComputeOrientations(bool computeOrientations)
{
  mComputeOrientations = computeOrientations;
}

void MsdProperties::setAffineMSD(bool affineMSD)
{
  mAffineMSD = affineMSD;
}

void MsdProperties::setTilts(int tilts)
{
  mTilts = tilts;
}

void MsdProperties::reset()
{
  mThresholdSaliency = 250;
  mPathRadius = 3;
  mKNN = 4;
  mAreaRadius = 5;
  mScaleFactor = 1.25;
  mNMSRadius = 5;
  mNScales = -1;
  mNMSScaleR = 0;
  mComputeOrientations = false;
  mAffineMSD = false;
  mTilts = 3;
}

/*----------------------------------------------------------------*/

MserProperties::MserProperties()
  : IMser(),
    mDelta(5),
    mMinArea(60),
    mMaxArea(14400),
    mMaxVariation(0.25),
    mMinDiversity(0.2),
    mMaxEvolution(200),
    mAreaThreshold(1.01),
    mMinMargin(0.003),
    mEdgeBlurSize(5)
{}

MserProperties::~MserProperties()
{

}

int MserProperties::delta() const
{
  return mDelta;
}

int MserProperties::minArea() const
{
  return mMinArea;
}

int MserProperties::maxArea() const
{
  return mMaxArea;
}

double MserProperties::maxVariation() const
{
  return mMaxVariation;
}

double MserProperties::minDiversity() const
{
  return mMinDiversity;
}

int MserProperties::maxEvolution() const
{
  return mMaxEvolution;
}

double MserProperties::areaThreshold() const
{
  return mAreaThreshold;
}

double MserProperties::minMargin() const
{
  return mMinMargin;
}

int MserProperties::edgeBlurSize() const
{
  return mEdgeBlurSize;
}

void MserProperties::setDelta(int delta)
{
  mDelta = delta;
}

void MserProperties::setMinArea(int minArea)
{
  mMinArea = minArea;
}

void MserProperties::setMaxArea(int maxArea)
{
  mMaxArea = maxArea;
}

void MserProperties::setMaxVariation(double maxVariation)
{
  mMaxVariation = maxVariation;
}

void MserProperties::setMinDiversity(double minDiversity)
{
  mMinDiversity = minDiversity;
}

void MserProperties::setMaxEvolution(int maxEvolution)
{
  mMaxEvolution = maxEvolution;
}

void MserProperties::setAreaThreshold(double areaThreshold)
{
  mAreaThreshold = areaThreshold;
}

void MserProperties::setMinMargin(double minMargin)
{
  mMinMargin = minMargin;
}

void MserProperties::setEdgeBlurSize(int edgeBlurSize)
{
  mEdgeBlurSize = edgeBlurSize;
}

void MserProperties::reset()
{
  mDelta = 5;
  mMinArea = 60;
  mMaxArea = 14400;
  mMaxVariation = 0.25;
  mMinDiversity = .2;
  mMaxEvolution = 200;
  mAreaThreshold = 1.01;
  mMinMargin = 0.003;
  mEdgeBlurSize = 5;
}


/*----------------------------------------------------------------*/


OrbProperties::OrbProperties()
  : IOrb(),
    mFeaturesNumber(5000),
    mScaleFactor(1.2),
    mLevelsNumber(8),
    mEdgeThreshold(31),
    mWTA_K(2),
    mScoreType("Harris"),
    mPatchSize(31),
    mFastThreshold(20)
{}

OrbProperties::~OrbProperties()
{

}

int OrbProperties::featuresNumber() const
{
  return mFeaturesNumber;
}

double OrbProperties::scaleFactor() const
{
  return mScaleFactor;
}

int OrbProperties::levelsNumber() const
{
  return mLevelsNumber;
}

int OrbProperties::edgeThreshold() const
{
  return mEdgeThreshold;
}

int OrbProperties::wta_k() const
{
  return mWTA_K;
}

QString OrbProperties::scoreType() const
{
  return mScoreType;
}

int OrbProperties::patchSize() const
{
  return mPatchSize;
}

int OrbProperties::fastThreshold() const
{
  return mFastThreshold;
}

void OrbProperties::setScaleFactor(double scaleFactor)
{
  mScaleFactor = scaleFactor;
}

void OrbProperties::setFeaturesNumber(int featuresNumber)
{
  mFeaturesNumber = featuresNumber;
}

void OrbProperties::setLevelsNumber(int levelsNumber)
{
  mLevelsNumber = levelsNumber;
}

void OrbProperties::setEdgeThreshold(int edgeThreshold)
{
  mEdgeThreshold = edgeThreshold;
}

void OrbProperties::setWTA_K(int WTA_K)
{
  mWTA_K = WTA_K;
}

void OrbProperties::setScoreType(const QString &scoreType)
{
  mScoreType = scoreType;
}

void OrbProperties::setPatchSize(int patchSize)
{
  mPatchSize = patchSize;
}

void OrbProperties::setFastThreshold(int fastThreshold)
{
  mFastThreshold = fastThreshold;
}

void OrbProperties::reset()
{
  mFeaturesNumber = 5000;
  mScaleFactor = 1.2;
  mLevelsNumber = 8;
  mEdgeThreshold = 31;
  mWTA_K = 2;
  mScoreType = "Harris";
  mPatchSize = 31;
  mFastThreshold = 20;
}

/*----------------------------------------------------------------*/


StarProperties::StarProperties()
  : IStar(),
    mMaxSize(45),
    mResponseThreshold(30),
    mLineThresholdProjected(10),
    mLineThresholdBinarized(8),
    mSuppressNonmaxSize(5)
{}

StarProperties::~StarProperties()
{

}

int StarProperties::maxSize() const
{
  return mMaxSize;
}

int StarProperties::responseThreshold() const
{
  return mResponseThreshold;
}

int StarProperties::lineThresholdProjected() const
{
  return mLineThresholdProjected;
}

int StarProperties::lineThresholdBinarized() const
{
  return mLineThresholdBinarized;
}

int StarProperties::suppressNonmaxSize() const
{
  return mSuppressNonmaxSize;
}

void StarProperties::setMaxSize(int maxSize)
{
  mMaxSize = maxSize;
}

void StarProperties::setResponseThreshold(int responseThreshold)
{
  mResponseThreshold = responseThreshold;
}

void StarProperties::setLineThresholdProjected(int lineThresholdProjected)
{
  mLineThresholdProjected = lineThresholdProjected;
}

void StarProperties::setLineThresholdBinarized(int lineThresholdBinarized)
{
  mLineThresholdBinarized = lineThresholdBinarized;
}

void StarProperties::setSuppressNonmaxSize(int suppressNonmaxSize)
{
  mSuppressNonmaxSize = suppressNonmaxSize;
}

void StarProperties::reset()
{
  mMaxSize = 45;
  mResponseThreshold = 30;
  mLineThresholdProjected = 10;
  mLineThresholdBinarized = 8;
  mSuppressNonmaxSize = 5;
}

/*----------------------------------------------------------------*/

SurfProperties::SurfProperties()
  : ISurf(),
    mHessianThreshold(100),
    mOctaves(4),
    mOctaveLayers(3),
    mExtendedDescriptor(false),
    mRotatedFeatures(false)
{
}

SurfProperties::~SurfProperties()
{
}

double SurfProperties::hessianThreshold() const
{
  return mHessianThreshold;
}

void SurfProperties::setHessianThreshold(double hessianThreshold)
{
  mHessianThreshold = hessianThreshold;
}

int SurfProperties::octaves() const
{
  return mOctaves;
}

void SurfProperties::setOctaves(int octaves)
{
  mOctaves = octaves;
}

int SurfProperties::octaveLayers() const
{
  return mOctaveLayers;
}

void SurfProperties::setOctaveLayers(int octaveLayers)
{
  mOctaveLayers = octaveLayers;
}

bool SurfProperties::extendedDescriptor() const
{
  return mExtendedDescriptor;
}

void SurfProperties::setExtendedDescriptor(bool extendedDescriptor)
{
  mExtendedDescriptor = extendedDescriptor;
}

bool SurfProperties::rotatedFeatures() const
{
  return mRotatedFeatures;
}

void SurfProperties::setRotatedFeatures(bool rotatedFeatures)
{
  mRotatedFeatures = rotatedFeatures;
}

void SurfProperties::reset()
{
  mHessianThreshold = 100;
  mOctaves = 4;
  mOctaveLayers = 3;
  mExtendedDescriptor = false;
  mRotatedFeatures = false;
}


/*----------------------------------------------------------------*/


SiftProperties::SiftProperties()
  : ISift(),
    mFeaturesNumber(5000),
    mOctaveLayers(3),
    mContrastThreshold(0.04),
    mEdgeThreshold(10.),
    mSigma(1.6)
{}

SiftProperties::~SiftProperties() {}

int SiftProperties::featuresNumber() const
{
  return mFeaturesNumber;
}

int SiftProperties::octaveLayers() const
{
  return mOctaveLayers;
}

double SiftProperties::contrastThreshold() const
{
  return mContrastThreshold;
}

double SiftProperties::edgeThreshold() const
{
  return mEdgeThreshold;
}

double SiftProperties::sigma() const
{
  return mSigma;
}

void SiftProperties::setFeaturesNumber(int featuresNumber)
{
  mFeaturesNumber = featuresNumber;
}

void SiftProperties::setOctaveLayers(int octaveLayers)
{
  mOctaveLayers = octaveLayers;
}

void SiftProperties::setContrastThreshold(double contrastThreshold)
{
  mContrastThreshold = contrastThreshold;
}

void SiftProperties::setEdgeThreshold(double edgeThreshold)
{
  mEdgeThreshold = edgeThreshold;
}

void SiftProperties::setSigma(double sigma)
{
  mSigma = sigma;
}

void SiftProperties::reset()
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

Acebsf::Acebsf()
  : IAcebsf(),
    mBlockSize(8, 8),
    mL(0.03),
    mK1(10.),
    mK2(0.5)
{

}

QSize Acebsf::blockSize() const
{
  return mBlockSize;
}

void Acebsf::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

double Acebsf::l() const
{
  return mL;
}

void Acebsf::setL(double l)
{
  mL = l;
}

double Acebsf::k1() const
{
  return mK1;
}

void Acebsf::setK1(double k1)
{
  mK1 = k1;
}

double Acebsf::k2() const
{
  return mK2;
}

void Acebsf::setK2(double k2)
{
  mK2 = k2;
}

void Acebsf::reset()
{
  mBlockSize = QSize(8, 8);
  mL = 0.03;
  mK1 = 10.;
  mK2 = 0.5;
}


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


LceBsescs::LceBsescs()
  : ILceBsescs(),
    mBlockSize(17,17)
{}

LceBsescs::~LceBsescs()
{
}

QSize LceBsescs::blockSize() const
{
  return mBlockSize;
}

void LceBsescs::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void LceBsescs::reset()
{
  mBlockSize = QSize(33, 33);
}


/*----------------------------------------------------------------*/


Msrcp::Msrcp()
  : IMsrcp(),
    mSmallScale(10.),
    mMidScale(100.),
    mLargeScale(220.)
{
}

Msrcp::~Msrcp()
{
}

double Msrcp::smallScale() const
{
  return mSmallScale;
}

void Msrcp::setSmallScale(double smallScale)
{
  mSmallScale = smallScale;
}

double Msrcp::midScale() const
{
  return mMidScale;
}

void Msrcp::setMidScale(double midScale)
{
  mMidScale = midScale;
}

double Msrcp::largeScale() const
{
  return mLargeScale;
}

void Msrcp::setLargeScale(double largeScale)
{
  mLargeScale = largeScale;
}

void Msrcp::reset()
{
  mSmallScale = 10.;
  mMidScale = 100.;
  mLargeScale = 220.;
}


/*----------------------------------------------------------------*/


Noshp::Noshp()
  : INoshp(),
    mBlockSize(127, 127)
{
}

Noshp::~Noshp()
{

}

QSize Noshp::blockSize() const
{
  return mBlockSize;
}

void Noshp::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void Noshp::reset()
{
  mBlockSize = QSize(127, 127);
}

/*----------------------------------------------------------------*/

Pohe::Pohe()
  : IPohe(),
    mBlockSize(127, 127)
{
}

Pohe::~Pohe()
{

}

QSize Pohe::blockSize() const
{
  return mBlockSize;
}

void Pohe::setBlockSize(const QSize &blockSize)
{
  mBlockSize = blockSize;
}

void Pohe::reset()
{
  mBlockSize = QSize(127, 127);
}

/*----------------------------------------------------------------*/


Rswhe::Rswhe()
  : IRswhe(),
    mHistogramCut(HistogramCut::by_mean),
    mHistogramDivisions(2)
{
}

Rswhe::~Rswhe()
{

}

int Rswhe::histogramDivisions() const
{
  return mHistogramDivisions;
}

void Rswhe::setHistogramDivisions(int histogramDivisions)
{
  mHistogramDivisions = histogramDivisions;
}

IRswhe::HistogramCut Rswhe::histogramCut() const
{
  return mHistogramCut;
}

void Rswhe::setHistogramCut(fme::IRswhe::HistogramCut histogramCut)
{
  mHistogramCut = histogramCut;
}

void Rswhe::reset()
{
  mHistogramDivisions = 2;
  mHistogramCut = HistogramCut::by_mean;
}


/*----------------------------------------------------------------*/


Wallis::Wallis()
  : IWallis(),
    mContrast(1.0),
    mBrightness(0.2),
    mImposedAverage(41),
    mImposedLocalStdDev(127),
    mKernelSize(50)
{

}

Wallis::~Wallis()
{
}

double Wallis::contrast() const
{
  return mContrast;
}

void Wallis::setContrast(double contrast)
{
  mContrast = contrast;
}

double Wallis::brightness() const
{
  return mBrightness;
}

void Wallis::setBrightness(double brightness)
{
  mBrightness = brightness;
}

int Wallis::imposedAverage() const
{
  return mImposedAverage;
}

void Wallis::setImposedAverage(int imposedAverage)
{
  mImposedAverage = imposedAverage;
}

int Wallis::imposedLocalStdDev() const
{
  return mImposedLocalStdDev;
}

void Wallis::setImposedLocalStdDev(int imposedLocalStdDev)
{
  mImposedLocalStdDev = imposedLocalStdDev;
}

int Wallis::kernelSize() const
{
  return mKernelSize;
}

void Wallis::setKernelSize(int kernelSize)
{
  mKernelSize = kernelSize;
}

void Wallis::reset()
{
  mContrast = 1.0;
  mBrightness = 0.2;
  mImposedAverage = 41;
  mImposedLocalStdDev = 127;
  mKernelSize = 50;
}



/*----------------------------------------------------------------*/



Settings::Settings()
  : ISettings(),
    mHistoyMaxSize(10),
    mAcebsf(new Acebsf),
    mClahe(new Clahe),
    mCmbfhe(new Cmbfhe),
    mDhe(new Dhe),
    mFahe(new Fahe),
    mHmclahe(new Hmclahe),
    mLceBsescs(new LceBsescs),
    mMsrcp(new Msrcp),
    mNoshp(new Noshp),
    mPohe(new Pohe),
    mRswhe(new Rswhe),
    mWallis(new Wallis),
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
    mSurf(new SurfProperties)
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

void Settings::reset()
{
  mLanguage = "en";

  mHistoyMaxSize = 10;
  mHistory.clear();

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
  settings.msd()->setTilts(mSettingsRW->value("MSD/Tilts", settings.msd()->tilts()).toInt());
  settings.msd()->setNScales(mSettingsRW->value("MSD/NScales", settings.msd()->nScales()).toInt());
  settings.msd()->setAffineMSD(mSettingsRW->value("MSD/AffineMSD", settings.msd()->affineMSD()).toBool());
  settings.msd()->setNMSRadius(mSettingsRW->value("MSD/NMSRadius", settings.msd()->NMSRadius()).toInt());
  settings.msd()->setNMSScaleR(mSettingsRW->value("MSD/NMSScaleR", settings.msd()->NMSScaleR()).toInt());
  settings.msd()->setAreaRadius(mSettingsRW->value("MSD/AreaRadius", settings.msd()->areaRadius()).toInt());
  settings.msd()->setPathRadius(mSettingsRW->value("MSD/PathRadius", settings.msd()->pathRadius()).toInt());
  settings.msd()->setScaleFactor(mSettingsRW->value("MSD/ScaleFactor", settings.msd()->scaleFactor()).toDouble());
  settings.msd()->setThresholdSaliency(mSettingsRW->value("MSD/ThresholdSaliency", settings.msd()->thresholdSaliency()).toDouble());
  settings.msd()->setComputeOrientations(mSettingsRW->value("MSD/ComputeOrientations", settings.msd()->computeOrientations()).toBool());

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
  mSettingsRW->setValue("MSD/Tilts", settings.msd()->tilts());
  mSettingsRW->setValue("MSD/NScales", settings.msd()->nScales());
  mSettingsRW->setValue("MSD/AffineMSD", settings.msd()->affineMSD());
  mSettingsRW->setValue("MSD/NMSRadius", settings.msd()->NMSRadius());
  mSettingsRW->setValue("MSD/NMSScaleR", settings.msd()->NMSScaleR());
  mSettingsRW->setValue("MSD/AreaRadius", settings.msd()->areaRadius());
  mSettingsRW->setValue("MSD/PathRadius", settings.msd()->pathRadius());
  mSettingsRW->setValue("MSD/ScaleFactor", settings.msd()->scaleFactor());
  mSettingsRW->setValue("MSD/ThresholdSaliency", settings.msd()->thresholdSaliency());
  mSettingsRW->setValue("MSD/ComputeOrientations", settings.msd()->computeOrientations());

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
}

void SettingsRW::writeHistory(const ISettings &settings)
{
  mSettingsRW->setValue("HISTORY/RecentProjects", settings.history());
}




} // namespace fme
