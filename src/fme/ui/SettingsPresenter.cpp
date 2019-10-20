#include "SettingsPresenter.h"

#include "SettingsModel.h"
#include "SettingsView.h"

/* Image preprocess */
#include "fme/widgets/AcebsfWidget.h"
#include "fme/widgets/ClaheWidget.h"
#include "fme/widgets/CmbfheWidget.h"
#include "fme/widgets/DheWidget.h"
#include "fme/widgets/FaheWidget.h"
#include "fme/widgets/HmclaheWidget.h"
#include "fme/widgets/LceBsescsWidget.h"
#include "fme/widgets/MsrcpWidget.h"
#include "fme/widgets/NoshpWidget.h"
#include "fme/widgets/PoheWidget.h"
#include "fme/widgets/RswheWidget.h"
#include "fme/widgets/WallisWidget.h"

/* Feature detector/extractor */
#include "fme/widgets/AgastWidget.h"
#include "fme/widgets/AkazeWidget.h"
#include "fme/widgets/BriefWidget.h"
#include "fme/widgets/BriskWidget.h"
#include "fme/widgets/DaisyWidget.h"
#include "fme/widgets/FastWidget.h"
#include "fme/widgets/FreakWidget.h"
#include "fme/widgets/GfttWidget.h"
#include "fme/widgets/HogWidget.h"
#include "fme/widgets/KazeWidget.h"
#include "fme/widgets/LatchWidget.h"
#include "fme/widgets/LucidWidget.h"
#include "fme/widgets/MsdWidget.h"
#include "fme/widgets/MserWidget.h"
#include "fme/widgets/OrbWidget.h"
#include "fme/widgets/SiftWidget.h"
#include "fme/widgets/StarWidget.h"
#include "fme/widgets/SurfWidget.h"

/* Descriptor Matcher */
#include "fme/widgets/DescriptorMatcherWidget.h"

#include <QLocale>

namespace fme
{

SettingsPresenter::SettingsPresenter(ISettingsView *view, ISettingsModel *model)
  : ISettingsPresenter(),
    mView(view),
    mModel(model),
    /*mHelp(nullptr),*/
    mACEBSF(new AcebsfWidget),
    mCLAHE(new ClaheWidget),
    mCMBFHE(new CmbfheWidget),
    mDHE(new DheWidget),
    mFAHE(new FaheWidget),
    mHMCLAHE(new HmclaheWidget),
    mLCEBSESCS(new LceBsescsWidget),
    mMSRCP(new MsrcpWidget),
    mNOSHP(new NoshpWidget),
    mPOHE(new PoheWidget),
    mRSWHE(new RswheWidget),
    mWallis(new WallisWidget),
    mAgast(new AgastWidget),
    mAkaze(new AkazeWidget),
    mBrief(new BriefWidget),
    mBrisk(new BriskWidget),
    mDaisy(new DaisyWidget),
    mFast(new FastWidget),
    mFreak(new FreakWidget),
    mGftt(new GfttWidget),
    mHog(new HogWidget),
    mKaze(new KazeWidget),
    mLatch(new LatchWidget),
    mLucid(new LucidWidget),
    mMsd(new MsdWidget),
    mMser(new MserWidget),
    mOrb(new OrbWidget),
    mSift(new SiftWidget),
    mStar(new StarWidget),
    mSurf(new SurfWidget),
    mMatcher(new DescriptorMatcherWidget)
{
  init();

  connect(mView, SIGNAL(languageChange(QString)),        this,   SLOT(setLanguage(QString)));
  connect(mView, SIGNAL(keypointsFormatChange(QString)), mModel, SLOT(setKeypointsFormat(QString)));
  connect(mView, SIGNAL(matchesFormatChange(QString)),   mModel, SLOT(setMatchesFormat(QString)));

  connect(mView, SIGNAL(accepted()), this, SLOT(save()));
  connect(mView, SIGNAL(applyChanges()), this, SLOT(save()));
  connect(mView, SIGNAL(rejected()), this, SLOT(discart()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));

  connect(mModel, SIGNAL(unsavedChanges(bool)), mView, SLOT(setUnsavedChanges(bool)));

  /* ACEBSF */
  connect(mACEBSF, SIGNAL(blockSizeChange(QSize)),         mModel, SLOT(setAcebsfBlockSize(QSize)));
  connect(mACEBSF, SIGNAL(lChange(double)),                mModel, SLOT(setAcebsfL(double)));
  connect(mACEBSF, SIGNAL(k1Change(double)),               mModel, SLOT(setAcebsfK1(double)));
  connect(mACEBSF, SIGNAL(k2Change(double)),               mModel, SLOT(setAcebsfK2(double)));

  /* CLAHE */
  connect(mCLAHE, SIGNAL(clipLimitChange(double)),         mModel, SLOT(setClaheClipLimit(double)));
  connect(mCLAHE, SIGNAL(tileGridSizeChange(QSize)),       mModel, SLOT(setClaheTilesGridSize(QSize)));

  /* CMBFHE */
  connect(mCMBFHE, SIGNAL(blockSizeChange(QSize)),         mModel, SLOT(setCmbfheBlockSize(QSize)));

  /* DHE */
  connect(mDHE, SIGNAL(xChange(int)),                      mModel, SLOT(setDheX(int)));

  /* FAHE */
  connect(mFAHE,  SIGNAL(blockSizeChange(QSize)),          mModel, SLOT(setFaheBlockSize(QSize)));

  /* HMCLAHE */
  connect(mHMCLAHE,  SIGNAL(blockSizeChange(QSize)),       mModel, SLOT(setHmclaheBlockSize(QSize)));
  connect(mHMCLAHE,  SIGNAL(lChange(double)),              mModel, SLOT(setHmclaheL(double)));
  connect(mHMCLAHE,  SIGNAL(phiChange(double)),            mModel, SLOT(setHmclahePhi(double)));

  /* LCEBSESCS */
  connect(mLCEBSESCS, SIGNAL(blockSizeChange(QSize)),       mModel, SLOT(setLceBsescsBlockSize(QSize)));

  /* MSRCP */
  connect(mMSRCP, SIGNAL(smallScaleChange(double)),         mModel, SLOT(setMsrcpSmallScale(double)));
  connect(mMSRCP, SIGNAL(midScaleChange(double)),           mModel, SLOT(setMsrcpMidScale(double)));
  connect(mMSRCP, SIGNAL(largeScaleChange(double)),         mModel, SLOT(setMsrcpLargeScale(double)));

  /* NOSHP */
  connect(mNOSHP,  SIGNAL(blockSizeChange(QSize)),          mModel, SLOT(setNoshpBlockSize(QSize)));

  /* POHE */
  connect(mPOHE, SIGNAL(blockSizeChange(QSize)),            mModel, SLOT(setPoheBlockSize(QSize)));

  /* RSWHE */
  connect(mRSWHE, SIGNAL(histogramDivisionsChange(int)),    mModel, SLOT(setRswheHistogramDivisions(int)));
  connect(mRSWHE, SIGNAL(histogramCutChange(int)),          mModel, SLOT(setRswheHistogramCut(int)));

  /* WALLIS */
  connect(mWallis, SIGNAL(contrastChange(double)),           mModel, SLOT(setWallisContrast(double)));
  connect(mWallis, SIGNAL(brightnessChange(double)),         mModel, SLOT(setWallisBrightness(double)));
  connect(mWallis, SIGNAL(imposedAverageChange(int)),        mModel, SLOT(setWallisImposedAverage(int)));
  connect(mWallis, SIGNAL(imposedLocalStdDevChange(int)),    mModel, SLOT(setWallisImposedLocalStdDev(int)));
  connect(mWallis, SIGNAL(kernelSizeChange(int)),            mModel, SLOT(setWallisKernelSize(int)));

  /* AGAST */
  connect(mAgast, SIGNAL(thresholdChange(int)),              mModel, SLOT(setAgastThreshold(int)));
  connect(mAgast, SIGNAL(nonmaxSuppressionChange(bool)),     mModel, SLOT(setAgastNonmaxSuppression(bool)));
  connect(mAgast, SIGNAL(detectorTypeChange(QString)),       mModel, SLOT(setAgastDetectorType(QString)));

  /* AKAZE */
  connect(mAkaze, SIGNAL(descriptorTypeChange(QString)),     mModel, SLOT(setAkazeDescriptorType(QString)));
  connect(mAkaze, SIGNAL(descriptorSizeChange(int)),         mModel, SLOT(setAkazeDescriptorSize(int)));
  connect(mAkaze, SIGNAL(descriptorChannelsChange(int)),     mModel, SLOT(setAkazeDescriptorChannels(int)));
  connect(mAkaze, SIGNAL(thresholdChange(double)),           mModel, SLOT(setAkazeThreshold(double)));
  connect(mAkaze, SIGNAL(octavesChange(int)),                mModel, SLOT(setAkazeOctaves(int)));
  connect(mAkaze, SIGNAL(octaveLayersChange(int)),           mModel, SLOT(setAkazeOctaveLayers(int)));
  connect(mAkaze, SIGNAL(diffusivityChange(QString)),        mModel, SLOT(setAkazeDiffusivity(QString)));

  /* BRIEF */
  connect(mBrief, SIGNAL(bytesChange(QString)),              mModel, SLOT(setBriefBytes(QString)));
  connect(mBrief, SIGNAL(useOrientationChange(bool)),        mModel, SLOT(setBriefUseOrientation(bool)));

  /* BRISK */
  connect(mBrisk, SIGNAL(thresholdChange(int)),              mModel, SLOT(setBriskThreshold(int)));
  connect(mBrisk, SIGNAL(octavesChange(int)),                mModel, SLOT(setBriskOctaves(int)));
  connect(mBrisk, SIGNAL(patternScaleChange(double)),        mModel, SLOT(setBriskPatternScale(double)));

  /* DAISY */
  connect(mDaisy, SIGNAL(radiusChange(double)),              mModel, SLOT(setDaisyRadius(double)));
  connect(mDaisy, SIGNAL(qRadiusChange(int)),                mModel, SLOT(setDaisyQRadius(int)));
  connect(mDaisy, SIGNAL(qThetaChange(int)),                 mModel, SLOT(setDaisyQTheta(int)));
  connect(mDaisy, SIGNAL(qHistChange(int)),                  mModel, SLOT(setDaisyQHist(int)));
  connect(mDaisy, SIGNAL(normChange(QString)),               mModel, SLOT(setDaisyNorm(QString)));
  connect(mDaisy, SIGNAL(interpolationChange(bool)),         mModel, SLOT(setDaisyInterpolation(bool)));
  connect(mDaisy, SIGNAL(useOrientationChange(bool)),        mModel, SLOT(setDaisyUseOrientation(bool)));

  /* FAST */
  connect(mFast, SIGNAL(thresholdChange(int)),               mModel, SLOT(setFastThreshold(int)));
  connect(mFast, SIGNAL(nonmaxSuppressionChange(bool)),      mModel, SLOT(setFastNonmaxSuppression(bool)));
  connect(mFast, SIGNAL(detectorTypeChange(QString)),        mModel, SLOT(setFastDetectorType(QString)));

  /* FREAK */
  connect(mFreak, SIGNAL(orientationNormalizedChange(bool)), mModel, SLOT(setFreakOrientationNormalized(bool)));
  connect(mFreak, SIGNAL(scaleNormalizedChange(bool)),       mModel, SLOT(setFreakScaleNormalized(bool)));
  connect(mFreak, SIGNAL(patternScaleChange(double)),        mModel, SLOT(setFreakPatternScale(double)));
  connect(mFreak, SIGNAL(octavesChange(int)),                mModel, SLOT(setFreakOctaves(int)));

  /* GFTT */
  connect(mGftt, SIGNAL(maxFeaturesChange(int)),             mModel, SLOT(setGfttMaxFeatures(int)));
  connect(mGftt, SIGNAL(qualityLevelChange(double)),         mModel, SLOT(setGfttQualityLevel(double)));
  connect(mGftt, SIGNAL(minDistanceChange(double)),          mModel, SLOT(setGfttMinDistance(double)));
  connect(mGftt, SIGNAL(blockSizeChange(int)),               mModel, SLOT(setGfttBlockSize(int)));
  connect(mGftt, SIGNAL(harrisDetectorChange(bool)),         mModel, SLOT(setGfttHarrisDetector(bool)));
  connect(mGftt, SIGNAL(kChange(double)),                    mModel, SLOT(setGfttK(double)));

  /* HOG */
  connect(mHog, SIGNAL(winSizeChange(QSize)),                mModel, SLOT(setHogWinSize(QSize)));
  connect(mHog, SIGNAL(blockSizeChange(QSize)),              mModel, SLOT(setHogBlockSize(QSize)));
  connect(mHog, SIGNAL(blockStrideChange(QSize)),            mModel, SLOT(setHogBlockStride(QSize)));
  connect(mHog, SIGNAL(cellSizeChange(QSize)),               mModel, SLOT(setHogCellSize(QSize)));
  connect(mHog, SIGNAL(nbinsChange(int)),                    mModel, SLOT(setHogNbins(int)));
  connect(mHog, SIGNAL(derivApertureChange(int)),            mModel, SLOT(setHogDerivAperture(int)));

  /* KAZE */
  connect(mKaze, SIGNAL(extendedDescriptorChange(bool)),     mModel, SLOT(setKazeExtendedDescriptor(bool)));
  connect(mKaze, SIGNAL(uprightChange(bool)),                mModel, SLOT(setKazeUpright(bool)));
  connect(mKaze, SIGNAL(thresholdChange(double)),            mModel, SLOT(setKazeThreshold(double)));
  connect(mKaze, SIGNAL(octavesChange(int)),                 mModel, SLOT(setKazeOctaves(int)));
  connect(mKaze, SIGNAL(octaveLayersChange(int)),            mModel, SLOT(setKazeOctaveLayers(int)));
  connect(mKaze, SIGNAL(diffusivityChange(QString)),         mModel, SLOT(setKazeDiffusivity(QString)));

  /* LATCH */
  connect(mLatch, SIGNAL(bytesChange(QString)),              mModel, SLOT(setLatchBytes(QString)));
  connect(mLatch, SIGNAL(rotationInvarianceChange(bool)),    mModel, SLOT(setLatchRotationInvariance(bool)));
  connect(mLatch, SIGNAL(halfSsdSizeChange(int)),            mModel, SLOT(setLatchHalfSsdSize(int)));

  /* LUCID */
  connect(mLucid, SIGNAL(lucidKernelChange(int)),            mModel, SLOT(setLucidKernel(int)));
  connect(mLucid, SIGNAL(blurKernelChange(int)),             mModel, SLOT(setLucidBlurKernel(int)));

  /* MSD */
  connect(mMsd, SIGNAL(thresholdSaliencyChange(double)),     mModel, SLOT(setMsdThresholdSaliency(double)));
  connect(mMsd, SIGNAL(pathRadiusChange(int)),               mModel, SLOT(setMsdPathRadius(int)));
  connect(mMsd, SIGNAL(KNNChange(int)),                      mModel, SLOT(setMsdKNN(int)));
  connect(mMsd, SIGNAL(areaRadiusChange(int)),               mModel, SLOT(setMsdAreaRadius(int)));
  connect(mMsd, SIGNAL(scaleFactorChange(double)),           mModel, SLOT(setMsdScaleFactor(double)));
  connect(mMsd, SIGNAL(NMSRadiusChange(int)),                mModel, SLOT(setMsdNMSRadius(int)));
  connect(mMsd, SIGNAL(nScalesChange(int)),                  mModel, SLOT(setMsdNScales(int)));
  connect(mMsd, SIGNAL(NMSScaleRChange(int)),                mModel, SLOT(setMsdNMSScaleR(int)));
  connect(mMsd, SIGNAL(computeOrientationsChange(bool)),     mModel, SLOT(setMsdComputeOrientations(bool)));
  connect(mMsd, SIGNAL(affineMSDChange(bool)),               mModel, SLOT(setMsdAffineMSD(bool)));
  connect(mMsd, SIGNAL(tiltsChange(int)),                    mModel, SLOT(setMsdTilts(int)));

  /* MSER */
  connect(mMser, SIGNAL(deltaChange(int)),                   mModel, SLOT(setMserDelta(int)));
  connect(mMser, SIGNAL(minAreaChange(int)),                 mModel, SLOT(setMserMinArea(int)));
  connect(mMser, SIGNAL(maxAreaChange(int)),                 mModel, SLOT(setMserMaxArea(int)));
  connect(mMser, SIGNAL(maxVariationChange(double)),         mModel, SLOT(setMserMaxVariation(double)));
  connect(mMser, SIGNAL(minDiversityChange(double)),         mModel, SLOT(setMserMinDiversity(double)));
  connect(mMser, SIGNAL(maxEvolutionChange(int)),            mModel, SLOT(setMserMaxEvolution(int)));
  connect(mMser, SIGNAL(areaThresholdChange(double)),        mModel, SLOT(setMserAreaThreshold(double)));
  connect(mMser, SIGNAL(minMarginChange(double)),            mModel, SLOT(setMserMinMargin(double)));
  connect(mMser, SIGNAL(edgeBlurSizeChange(int)),            mModel, SLOT(setMserEdgeBlurSize(int)));

  /* ORB */
  connect(mOrb, SIGNAL(scaleFactorChange(double)),           mModel, SLOT(setOrbScaleFactor(double)));
  connect(mOrb, SIGNAL(featuresNumberChange(int)),           mModel, SLOT(setOrbFeaturesNumber(int)));
  connect(mOrb, SIGNAL(levelsNumberChange(int)),             mModel, SLOT(setOrbLevelsNumber(int)));
  connect(mOrb, SIGNAL(edgeThresholdChange(int)),            mModel, SLOT(setOrbEdgeThreshold(int)));
  connect(mOrb, SIGNAL(wta_kChange(int)),                    mModel, SLOT(setOrbWTA_K(int)));
  connect(mOrb, SIGNAL(scoreTypeChange(QString)),            mModel, SLOT(setOrbScoreType(QString)));
  connect(mOrb, SIGNAL(patchSizeChange(int)),                mModel, SLOT(setOrbPatchSize(int)));
  connect(mOrb, SIGNAL(fastThresholdChange(int)),            mModel, SLOT(setOrbFastThreshold(int)));

  /* SIFT */
  connect(mSift, SIGNAL(featuresNumberChange(int)),          mModel, SLOT(setSiftFeaturesNumber(int)));
  connect(mSift, SIGNAL(octaveLayersChange(int)),            mModel, SLOT(setSiftOctaveLayers(int)));
  connect(mSift, SIGNAL(contrastThresholdChange(double)),    mModel, SLOT(setSiftContrastThreshold(double)));
  connect(mSift, SIGNAL(edgeThresholdChange(double)),        mModel, SLOT(setSiftEdgeThreshold(double)));
  connect(mSift, SIGNAL(sigmaChange(double)),                mModel, SLOT(setSiftSigma(double)));

  /* STAR */
  connect(mStar, SIGNAL(maxSizeChange(int)),                 mModel, SLOT(setStarMaxSize(int)));
  connect(mStar, SIGNAL(responseThresholdChange(int)),       mModel, SLOT(setStarResponseThreshold(int)));
  connect(mStar, SIGNAL(lineThresholdProjectedChange(int)),  mModel, SLOT(setStarLineThresholdProjected(int)));
  connect(mStar, SIGNAL(lineThresholdBinarizedChange(int)),  mModel, SLOT(setStarLineThresholdBinarized(int)));
  connect(mStar, SIGNAL(suppressNonmaxSizeChange(int)),      mModel, SLOT(setStarSuppressNonmaxSize(int)));

  /* SURF */
  connect(mSurf, SIGNAL(hessianThresholdChange(double)),     mModel, SLOT(setSurfHessianThreshold(double)));
  connect(mSurf, SIGNAL(octavesChange(int)),                 mModel, SLOT(setSurfOctaves(int)));
  connect(mSurf, SIGNAL(octaveLayersChange(int)),            mModel, SLOT(setSurfOctaveLayers(int)));
  connect(mSurf, SIGNAL(extendedDescriptorChange(bool)),     mModel, SLOT(setSurfExtendedDescriptor(bool)));
  connect(mSurf, SIGNAL(rotatedFeaturesChange(bool)),        mModel, SLOT(setSurfRotatedFeatures(bool)));

  connect(mMatcher, SIGNAL(matchingMethodChange(QString)),   mModel, SLOT(setMatchMethod(QString)));
  connect(mMatcher, SIGNAL(normTypeChange(QString)),         mModel, SLOT(setMatchNormType(QString)));
  connect(mMatcher, SIGNAL(ratioChange(double)),             mModel, SLOT(setMatchRatio(double)));
  connect(mMatcher, SIGNAL(distanceChange(double)),          mModel, SLOT(setMatchDistance(double)));
  connect(mMatcher, SIGNAL(confidenceChange(double)),        mModel, SLOT(setMatchConfidence(double)));
  connect(mMatcher, SIGNAL(crossMatchingChange(bool)),       mModel, SLOT(setMatchCrossMatching(bool)));
  connect(mMatcher, SIGNAL(maxItersChange(int)),             mModel, SLOT(setMatchMaxIters(int)));
  connect(mMatcher, SIGNAL(geometricTestChange(QString)),    mModel, SLOT(setMatchGeometricTest(QString)));
  connect(mMatcher, SIGNAL(homographyComputeMethodChange(QString)),  mModel, SLOT(setMatchHomographyComputeMethod(QString)));
  connect(mMatcher, SIGNAL(fundamentalComputeMethodChange(QString)), mModel, SLOT(setMatchFundamentalComputeMethod(QString)));
  connect(mMatcher, SIGNAL(essentialComputeMethodChange(QString)),   mModel, SLOT(setMatchEssentialComputeMethod(QString)));

}

SettingsPresenter::~SettingsPresenter()
{
  if (mACEBSF){
    delete mACEBSF;
    mACEBSF = nullptr;
  }

  if (mCLAHE){
    delete mCLAHE;
    mCLAHE = nullptr;
  }

  if (mCMBFHE){
    delete mCMBFHE;
    mCMBFHE = nullptr;
  }

  if (mDHE){
    delete mDHE;
    mDHE = nullptr;
  }

  if (mFAHE){
    delete mFAHE;
    mFAHE = nullptr;
  }

  if (mHMCLAHE){
    delete mHMCLAHE;
    mHMCLAHE = nullptr;
  }

  if (mLCEBSESCS){
    delete mLCEBSESCS;
    mLCEBSESCS = nullptr;
  }
  if (mMSRCP){
    delete mMSRCP;
    mMSRCP = nullptr;
  }
  if (mNOSHP){
    delete mNOSHP;
    mNOSHP = nullptr;
  }
  if (mPOHE){
    delete mPOHE;
    mPOHE = nullptr;
  }
  if (mRSWHE){
    delete mRSWHE;
    mRSWHE = nullptr;
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
    mBrisk = nullptr;}

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

  if (mMatcher){
    delete mMatcher;
    mMatcher = nullptr;
  }
}

void SettingsPresenter::openPage(int page)
{
  mView->setPage(page);
  this->open();
}

void SettingsPresenter::help()
{
//  if (mHelp){
//    mHelp->setPage("settings.html");
//    mHelp->setModal(true);
//    mHelp->showMaximized();
//  }
}

void SettingsPresenter::open()
{
  QStringList languages = mModel->languages();
  QStringList langs;
  mLang.clear();

  for (int i = 0; i < languages.size(); ++i) {
    QString lang_code = languages[i];
    lang_code.truncate(lang_code.lastIndexOf('.'));
    lang_code.remove(0, lang_code.indexOf('_') + 1);
    QString lang_name = QLocale::languageToString(QLocale(lang_code).language());
    langs.push_back(lang_name);
    mLang[lang_name] = lang_code;
  }

  mView->setLanguages(langs);

  mView->setHistoryMaxSize(mModel->historyMaxSize());
  mView->setKeypointsFormat(mModel->keypointsFormat());
  mView->setMatchesFormat(mModel->matchesFormat());

  mACEBSF->setBlockSize(mModel->acebsfBlockSize());
  mACEBSF->setL(mModel->acebsfL());
  mACEBSF->setK1(mModel->acebsfK1());
  mACEBSF->setK2(mModel->acebsfK2());

  mCLAHE->setClipLimit(mModel->claheClipLimit());
  mCLAHE->setTilesGridSize(mModel->claheTilesGridSize());

  mCMBFHE->setBlockSize(mModel->faheBlockSize());

  mDHE->setX(mModel->dheX());

  mFAHE->setBlockSize(mModel->faheBlockSize());

  mHMCLAHE->setBlockSize(mModel->hmclaheBlockSize());
  mHMCLAHE->setL(mModel->hmclaheL());
  mHMCLAHE->setPhi(mModel->hmclahePhi());

  mLCEBSESCS->setBlockSize(mModel->lceBsescsBlockSize());

  mMSRCP->setMidScale(mModel->msrcpMidScale());
  mMSRCP->setLargeScale(mModel->msrcpLargeScale());
  mMSRCP->setSmallScale(mModel->msrcpSmallScale());

  mNOSHP->setBlockSize(mModel->noshpBlockSize());

  mPOHE->setBlockSize(mModel->poheBlockSize());

  mRSWHE->setHistogramCut(static_cast<IRswheWidget::HistogramCut>(mModel->rswheHistogramCut()));
  mRSWHE->setHistogramDivisions(mModel->rswheHistogramDivisions());

  mWallis->setContrast(mModel->wallisContrast());
  mWallis->setBrightness(mModel->wallisBrightness());
  mWallis->setKernelSize(mModel->wallisKernelSize());
  mWallis->setImposedAverage(mModel->wallisImposedAverage());
  mWallis->setImposedLocalStdDev(mModel->wallisImposedLocalStdDev());


  mAgast->setThreshold(mModel->agastThreshold());
  mAgast->setDetectorType(mModel->agastDetectorType());
  mAgast->setNonmaxSuppression(mModel->agastNonmaxSuppression());

  mAkaze->setOctaves(mModel->akazeOctaves());
  mAkaze->setThreshold(mModel->akazeThreshold());
  mAkaze->setDiffusivity(mModel->akazeDiffusivity());
  mAkaze->setOctaveLayers(mModel->akazeOctaveLayers());
  mAkaze->setDescriptorSize(mModel->akazeDescriptorSize());
  mAkaze->setDescriptorType(mModel->akazeDescriptorType());
  mAkaze->setDescriptorChannels(mModel->akazeDescriptorChannels());

  mBrief->setBytes(mModel->briefBytes());
  mBrief->setUseOrientation(mModel->briefUseOrientation());

  mBrisk->setThreshold(mModel->briskThreshold());
  mBrisk->setOctaves(mModel->briskOctaves());
  mBrisk->setPatternScale(mModel->briskPatternScale());

  mDaisy->setNorm(mModel->daisyNorm());
  mDaisy->setQRadius(mModel->daisyQRadius());
  mDaisy->setQTheta(mModel->daisyQTheta());
  mDaisy->setQHist(mModel->daisyQHist());
  mDaisy->setNorm(mModel->daisyNorm());
  mDaisy->setInterpolation(mModel->daisyInterpolation());
  mDaisy->setUseOrientation(mModel->daisyUseOrientation());

  mFast->setThreshold(mModel->fastThreshold());
  mFast->setNonmaxSuppression(mModel->fastNonmaxSuppression());
  mFast->setDetectorType(mModel->fastdetectorType());

  mFreak->setOrientationNormalized(mModel->freakOrientationNormalized());
  mFreak->setScaleNormalized(mModel->freakScaleNormalized());
  mFreak->setPatternScale(mModel->freakPatternScale());
  mFreak->setOctaves(mModel->freakOctaves());

  mGftt->setMaxFeatures(mModel->gfttMaxFeatures());
  mGftt->setQualityLevel(mModel->gfttQualityLevel());
  mGftt->setMinDistance(mModel->gfttMinDistance());
  mGftt->setBlockSize(mModel->gfttBlockSize());
  mGftt->setHarrisDetector(mModel->gfttHarrisDetector());
  mGftt->setK(mModel->gfttK());

  mHog->setWinSize(mModel->hogWinSize());
  mHog->setBlockSize(mModel->hogBlockSize());
  mHog->setBlockStride(mModel->hogBlockStride());
  mHog->setCellSize(mModel->hogCellSize());
  mHog->setNbins(mModel->hogNbins());
  mHog->setDerivAperture(mModel->hogDerivAperture());

  mKaze->setExtendedDescriptor(mModel->kazeExtendedDescriptor());
  mKaze->setUpright(mModel->kazeUpright());
  mKaze->setThreshold(mModel->kazeUpright());
  mKaze->setOctaves(mModel->kazeOctaves());
  mKaze->setOctaveLayers(mModel->kazeOctaveLayers());
  mKaze->setDiffusivity(mModel->kazeDiffusivity());

  mLatch->setBytes(mModel->latchBytes());
  mLatch->setRotationInvariance(mModel->latchRotationInvariance());
  mLatch->setHalfSsdSize(mModel->latchHalfSsdSize());

  mLucid->setLucidKernel(mModel->lucidKernel());
  mLucid->setBlurKernel(mModel->lucidBlurKernel());

  mMsd->setThresholdSaliency(mModel->msdThresholdSaliency());
  mMsd->setPatchRadius(mModel->msdPathRadius());
  mMsd->setKNN(mModel->msdKnn());
  mMsd->setAreaRadius(mModel->msdAreaRadius());
  mMsd->setScaleFactor(mModel->msdScaleFactor());
  mMsd->setNMSRadius(mModel->msdNMSRadius());
  mMsd->setNScales(mModel->msdNScales());
  mMsd->setNMSScaleR(mModel->msdNMSScaleR());
  mMsd->setComputeOrientations(mModel->msdComputeOrientations());
  mMsd->setAffineMSD(mModel->msdAffineMSD());
  mMsd->setTilts(mModel->msdTilts());

  mMser->setDelta(mModel->mserDelta());
  mMser->setMaxArea(mModel->mserMaxArea());
  mMser->setMinArea(mModel->mserMinArea());
  mMser->setMaxVariation(mModel->mserMaxVariation());
  mMser->setMinDiversity(mModel->mserMinDiversity());
  mMser->setMaxEvolution(mModel->mserMaxEvolution());
  mMser->setAreaThreshold(mModel->mserAreaThreshold());
  mMser->setMinMargin(mModel->mserMinMargin());
  mMser->setEdgeBlurSize(mModel->mserEdgeBlurSize());

  mOrb->setScaleFactor(mModel->orbScaleFactor());
  mOrb->setFeaturesNumber(mModel->orbFeaturesNumber());
  mOrb->setLevelsNumber(mModel->orbLevelsNumber());
  mOrb->setEdgeThreshold(mModel->orbEdgeThreshold());
  mOrb->setWTA_K(mModel->orbWta_k());
  mOrb->setScoreType(mModel->orbScoreType());
  mOrb->setPatchSize(mModel->orbPatchSize());
  mOrb->setFastThreshold(mModel->orbFastThreshold());

  mSift->setSigma(mModel->siftSigma());
  mSift->setOctaveLayers(mModel->siftOctaveLayers());
  mSift->setEdgeThreshold(mModel->siftEdgeThreshold());
  mSift->setFeaturesNumber(mModel->siftFeaturesNumber());
  mSift->setContrastThreshold(mModel->siftContrastThreshold());

  mStar->setMaxSize(mModel->starMaxSize());
  mStar->setResponseThreshold(mModel->starResponseThreshold());
  mStar->setLineThresholdProjected(mModel->starLineThresholdProjected());
  mStar->setLineThresholdBinarized(mModel->starLineThresholdBinarized());
  mStar->setSuppressNonmaxSize(mModel->starSuppressNonmaxSize());

  mSurf->setOctaves(mModel->surfOctaves());
  mSurf->setOctaveLayers(mModel->surfOctaveLayers());
  mSurf->setRotatedFeatures(mModel->surfRotatedFeatures());
  mSurf->setHessianThreshold(mModel->surfHessianThreshold());
  mSurf->setExtendedDescriptor(mModel->surfExtendedDescriptor());

  mMatcher->setMatchingMethod(mModel->matchMethod());
  mMatcher->setNormType(mModel->matchNormType());
  mMatcher->setRatio(mModel->matchRatio());
  mMatcher->setDistance(mModel->matchDistance());
  mMatcher->setConfidence(mModel->matchConfidence());
  mMatcher->setCrossMatching(mModel->matchCrossMatching());
  mMatcher->setMaxIters(mModel->matchMaxIters());
  mMatcher->setGeometricTest(mModel->matchGeometricTest());
  mMatcher->setHomographyComputeMethod(mModel->matchHomographyComputeMethod());
  mMatcher->setFundamentalComputeMethod(mModel->matchFundamentalComputeMethod());
  mMatcher->setEssentialComputeMethod(mModel->matchEssentialComputeMethod());

  mView->exec();
}

void SettingsPresenter::init()
{
  mView->addPreprocess(mACEBSF);
  mView->addPreprocess(mCLAHE);
  mView->addPreprocess(mCMBFHE);
  mView->addPreprocess(mDHE);
  mView->addPreprocess(mFAHE);
  mView->addPreprocess(mHMCLAHE);
  mView->addPreprocess(mLCEBSESCS);
  mView->addPreprocess(mMSRCP);
  mView->addPreprocess(mNOSHP);
  mView->addPreprocess(mPOHE);
  mView->addPreprocess(mRSWHE);
  mView->addPreprocess(mWallis);

  mView->addFeatureDetectorMethod(mSift);
  mView->addFeatureDetectorMethod(mSurf);
  mView->addFeatureDetectorMethod(mOrb);
  mView->addFeatureDetectorMethod(mAgast);
  mView->addFeatureDetectorMethod(mAkaze);
  mView->addFeatureDetectorMethod(mBrief);
  mView->addFeatureDetectorMethod(mBrisk);
  mView->addFeatureDetectorMethod(mDaisy);
  mView->addFeatureDetectorMethod(mFast);
  mView->addFeatureDetectorMethod(mFreak);
  mView->addFeatureDetectorMethod(mGftt);
  mView->addFeatureDetectorMethod(mHog);
  mView->addFeatureDetectorMethod(mKaze);
  mView->addFeatureDetectorMethod(mLatch);
  mView->addFeatureDetectorMethod(mLucid);
  mView->addFeatureDetectorMethod(mMsd);
  mView->addFeatureDetectorMethod(mMser);
  mView->addFeatureDetectorMethod(mStar);
  mView->addFeatureDetectorMethod(mHog);

  mView->addDescriptorMatcher(mMatcher);
}

void SettingsPresenter::setLanguage(const QString &language)
{
  QString lang_code = mLang[language];

  mModel->setLanguage(lang_code);
}

void SettingsPresenter::save()
{
  mModel->write();
}

void SettingsPresenter::discart()
{
  mModel->read();
}

} // End namespace fme
