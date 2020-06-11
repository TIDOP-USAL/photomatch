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


#include "SettingsPresenter.h"

#include "SettingsModel.h"
#include "SettingsView.h"
#include "photomatch/ui/HelpDialog.h"

/* Image preprocess */
#include "photomatch/widgets/AcebsfWidget.h"
#include "photomatch/widgets/ClaheWidget.h"
#include "photomatch/widgets/CmbfheWidget.h"
#include "photomatch/widgets/DheWidget.h"
#include "photomatch/widgets/FaheWidget.h"
#include "photomatch/widgets/HmclaheWidget.h"
#include "photomatch/widgets/LceBsescsWidget.h"
#include "photomatch/widgets/MsrcpWidget.h"
#include "photomatch/widgets/NoshpWidget.h"
#include "photomatch/widgets/PoheWidget.h"
#include "photomatch/widgets/RswheWidget.h"
#include "photomatch/widgets/WallisWidget.h"

/* Feature detector/extractor */
#include "photomatch/widgets/AgastWidget.h"
#include "photomatch/widgets/AkazeWidget.h"
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
#include "photomatch/widgets/BoostWidget.h"
#endif
#include "photomatch/widgets/BriefWidget.h"
#include "photomatch/widgets/BriskWidget.h"
#include "photomatch/widgets/DaisyWidget.h"
#include "photomatch/widgets/FastWidget.h"
#include "photomatch/widgets/FreakWidget.h"
#include "photomatch/widgets/GfttWidget.h"
#include "photomatch/widgets/HogWidget.h"
#include "photomatch/widgets/KazeWidget.h"
#include "photomatch/widgets/LatchWidget.h"
//#include "photomatch/widgets/LucidWidget.h"
#include "photomatch/widgets/MsdWidget.h"
#include "photomatch/widgets/MserWidget.h"
#include "photomatch/widgets/OrbWidget.h"
#ifdef OPENCV_ENABLE_NONFREE
#include "photomatch/widgets/SiftWidget.h"
#endif
#include "photomatch/widgets/StarWidget.h"
#ifdef OPENCV_ENABLE_NONFREE
#include "photomatch/widgets/SurfWidget.h"
#endif
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
#include "photomatch/widgets/VggWidget.h"
#endif

/* Descriptor Matcher */
#include "photomatch/widgets/DescriptorMatcherWidget.h"

#include <QLocale>

namespace photomatch
{

SettingsPresenterImp::SettingsPresenterImp(SettingsView *view,
                                           SettingsModel *model)
  : SettingsPresenter(),
    mView(view),
    mModel(model),
    mHelp(nullptr),
    mACEBSF(new AcebsfWidgetImp),
    mCLAHE(new ClaheWidgetImp),
    mCMBFHE(new CmbfheWidgetImp),
    mDHE(new DheWidgetImp),
    mFAHE(new FaheWidgetImp),
    mHMCLAHE(new HmclaheWidgetImp),
    mLCEBSESCS(new LceBsescsWidgetImp),
    mMSRCP(new MsrcpWidgetImp),
    mNOSHP(new NoshpWidgetImp),
    mPOHE(new PoheWidgetImp),
    mRSWHE(new RswheWidgetImp),
    mWallis(new WallisWidgetImp),
    mAgast(new AgastWidgetImp),
    mAkaze(new AkazeWidgetImp),
    #if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
    mBoost(new BoostWidgetImp),
    #endif
    mBrief(new BriefWidgetImp),
    mBrisk(new BriskWidgetImp),
    mDaisy(new DaisyWidgetImp),
    mFast(new FastWidgetImp),
    mFreak(new FreakWidgetImp),
    mGftt(new GfttWidgetImp),
    mHog(new HogWidgetImp),
    mKaze(new KazeWidgetImp),
    mLatch(new LatchWidgetImp),
    mMsd(new MsdWidgetImp),
    mMser(new MserWidgetImp),
    mOrb(new OrbWidgetImp),
#ifdef OPENCV_ENABLE_NONFREE
    mSift(new SiftWidgetImp),
#endif
    mStar(new StarWidgetImp),
#ifdef OPENCV_ENABLE_NONFREE
    mSurf(new SurfWidgetImp),
#endif
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
    mVgg(new VggWidgetImp),
#endif
    mMatcher(new DescriptorMatcherWidgetImp)
{
  this->init();
  this->initSignalAndSlots();
}

SettingsPresenterImp::~SettingsPresenterImp()
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

#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  if (mBoost){
    delete mBoost;
    mBoost = nullptr;
  }
#endif

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

//  if (mLucid){
//    delete mLucid;
//    mLucid = nullptr;
//  }

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

#ifdef OPENCV_ENABLE_NONFREE
  if (mSift){
    delete mSift;
    mSift = nullptr;
  }
#endif

  if (mStar){
    delete mStar;
    mStar = nullptr;
  }

#ifdef OPENCV_ENABLE_NONFREE
  if (mSurf){
    delete mSurf;
    mSurf = nullptr;
  }
#endif

#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  if (mVgg){
    delete mVgg;
    mVgg = nullptr;
  }
#endif

  if (mMatcher){
    delete mMatcher;
    mMatcher = nullptr;
  }
}

//void SettingsPresenter::openPage(int page)
//{
//  mView->setPage(page);
//  this->open();
//}

void SettingsPresenterImp::openViewSettings()
{
  mView->setPage(1);
  this->open();
}

void SettingsPresenterImp::openQualityControlSettings()
{
  mView->setPage(3);
  this->open();
}

void SettingsPresenterImp::openToolSettings()
{
  mView->setPage(2);
  this->open();
}

void SettingsPresenterImp::help()
{
  if (mHelp){
    mHelp->setPage("settings.html");
    mHelp->show();
  }
}

void SettingsPresenterImp::open()
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
  mView->setUseCuda(mModel->useCuda());
  mView->setCudaEnabled(false);
#ifdef HAVE_CUDA
  mView->setCudaEnabled(true);
#else
  mView->setCudaEnabled(false);
#endif //HAVE_CUDA

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

  mRSWHE->setHistogramCut(static_cast<RswheWidget::HistogramCut>(mModel->rswheHistogramCut()));
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

#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  mBoost->setDescriptorType(mModel->boostDescriptorType());
  mBoost->setUseOrientation(mModel->boostUseOrientation());
  mBoost->setScaleFactor(mModel->boostScaleFactor());
#endif

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
  mKaze->setUprightDescriptor(mModel->kazeUpright());
  mKaze->setThreshold(mModel->kazeUpright());
  mKaze->setOctaves(mModel->kazeOctaves());
  mKaze->setOctaveLayers(mModel->kazeOctaveLayers());
  mKaze->setDiffusivity(mModel->kazeDiffusivity());

  mLatch->setBytes(mModel->latchBytes());
  mLatch->setRotationInvariance(mModel->latchRotationInvariance());
  mLatch->setHalfSsdSize(mModel->latchHalfSsdSize());

//  mLucid->setLucidKernel(mModel->lucidKernel());
//  mLucid->setBlurKernel(mModel->lucidBlurKernel());

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

#ifdef OPENCV_ENABLE_NONFREE
  mSift->setSigma(mModel->siftSigma());
  mSift->setOctaveLayers(mModel->siftOctaveLayers());
  mSift->setEdgeThreshold(mModel->siftEdgeThreshold());
  mSift->setFeaturesNumber(mModel->siftFeaturesNumber());
  mSift->setContrastThreshold(mModel->siftContrastThreshold());
#endif

  mStar->setMaxSize(mModel->starMaxSize());
  mStar->setResponseThreshold(mModel->starResponseThreshold());
  mStar->setLineThresholdProjected(mModel->starLineThresholdProjected());
  mStar->setLineThresholdBinarized(mModel->starLineThresholdBinarized());
  mStar->setSuppressNonmaxSize(mModel->starSuppressNonmaxSize());

#ifdef OPENCV_ENABLE_NONFREE
  mSurf->setOctaves(mModel->surfOctaves());
  mSurf->setOctaveLayers(mModel->surfOctaveLayers());
  mSurf->seUpright(mModel->surfRotatedFeatures());
  mSurf->setHessianThreshold(mModel->surfHessianThreshold());
  mSurf->setExtendedDescriptor(mModel->surfExtendedDescriptor());
#endif

#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  mVgg->setDescriptorType(mModel->boostDescriptorType());
  mVgg->setScaleFactor(mModel->boostScaleFactor());
  mVgg->setSigma(mModel->vggSigma());
  mVgg->setUseNormalizeDescriptor(mModel->vggUseNormalizeDescriptor());
  mVgg->setUseNormalizeImage(mModel->vggUseNormalizeImage());
  mVgg->setUseScaleOrientation(mModel->vggUseScaleOrientation());
#endif

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

  mView->setKeypointsViewerBGColor(mModel->keypointsViewerBGColor());
  mView->setKeypointsViewerMarkerType(mModel->keypointsViewerMarkerType());
  mView->setKeypointsViewerMarkerSize(mModel->keypointsViewerMarkerSize());
  mView->setKeypointsViewerMarkerWidth(mModel->keypointsViewerMarkerWidth());
  mView->setKeypointsViewerMarkerColor(mModel->keypointsViewerMarkerColor());
  mView->setSelectKeypointsViewerMarkerColor(mModel->keypointsViewerSelectMarkerColor());
  mView->setSelectKeypointsViewerMarkerWidth(mModel->keypointsViewerSelectMarkerWidth());

  mView->setMatchesViewerBGColor(mModel->matchesViewerBGColor());
  mView->setMatchesViewerMarkerType(mModel->matchesViewerMarkerType());
  mView->setMatchesViewerMarkerSize(mModel->matchesViewerMarkerSize());
  mView->setMatchesViewerMarkerWidth(mModel->matchesViewerMarkerWidth());
  mView->setMatchesViewerMarkerColor(mModel->matchesViewerMarkerColor());
  mView->setSelectMatchesViewerMarkerWidth(mModel->matchesViewerSelectMarkerWidth());
  mView->setSelectMatchesViewerMarkerColor(mModel->matchesViewerSelectMarkerColor());
  mView->setMatchesViewerLineColor(mModel->matchesViewerLineColor());
  mView->setMatchesViewerLineWidth(mModel->matchesViewerLineWidth());

  mView->setGroundTruthEditorBGColor(mModel->groundTruthEditorBGColor());
  mView->setGroundTruthEditorMarkerSize(mModel->groundTruthEditorMarkerSize());
  mView->setGroundTruthEditorMarkerColor(mModel->groundTruthEditorMarkerColor());
  mView->setGroundTruthEditorMarkerWidth(mModel->groundTruthEditorMarkerWidth());
  mView->setSelectGroundTruthEditorMarkerWidth(mModel->groundTruthEditorSelectMarkerWidth());
  mView->setSelectGroundTruthEditorMarkerColor(mModel->groundTruthEditorSelectMarkerColor());
  mView->setGroundTruthEditorMatrixAdjust(mModel->groundTruthEditorMatrixAdjust());

  mView->exec();
}

void SettingsPresenterImp::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void SettingsPresenterImp::init()
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

#ifdef OPENCV_ENABLE_NONFREE
  mView->addFeatureDetectorMethod(mSift);
  mView->addFeatureDetectorMethod(mSurf);
#endif
  mView->addFeatureDetectorMethod(mOrb);
  mView->addFeatureDetectorMethod(mAgast);
  mView->addFeatureDetectorMethod(mAkaze);
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  mView->addFeatureDetectorMethod(mBoost);
#endif
  mView->addFeatureDetectorMethod(mBrief);
  mView->addFeatureDetectorMethod(mBrisk);
  mView->addFeatureDetectorMethod(mDaisy);
  mView->addFeatureDetectorMethod(mFast);
  mView->addFeatureDetectorMethod(mFreak);
  mView->addFeatureDetectorMethod(mGftt);
  mView->addFeatureDetectorMethod(mHog);
  mView->addFeatureDetectorMethod(mKaze);
  mView->addFeatureDetectorMethod(mLatch);
  //mView->addFeatureDetectorMethod(mLucid);
  mView->addFeatureDetectorMethod(mMsd);
  mView->addFeatureDetectorMethod(mMser);
  mView->addFeatureDetectorMethod(mStar);
  mView->addFeatureDetectorMethod(mHog);
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  mView->addFeatureDetectorMethod(mVgg);
#endif

  mView->addDescriptorMatcher(mMatcher);
}

void SettingsPresenterImp::initSignalAndSlots()
{
  connect(mView, SIGNAL(languageChange(QString)),        this,   SLOT(setLanguage(QString)));
  connect(mView, SIGNAL(historyMaxSizeChange(int)),      mModel, SLOT(setHistoryMaxSize(int)));
  connect(mView, SIGNAL(keypointsFormatChange(QString)), mModel, SLOT(setKeypointsFormat(QString)));
  connect(mView, SIGNAL(matchesFormatChange(QString)),   mModel, SLOT(setMatchesFormat(QString)));
  connect(mView, SIGNAL(useCudaChange(bool)),            mModel, SLOT(setUseCuda(bool)));

  connect(mView, SIGNAL(imageViewerBGColorChange(QString)),  mModel, SLOT(setImageViewerBGcolor(QString)));

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

  /* BOOST */
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  connect(mBoost, SIGNAL(descriptorTypeChange(QString)),     mModel, SLOT(setBoostDescriptorType(QString)));
  connect(mBoost, SIGNAL(useOrientationChange(bool)),        mModel, SLOT(setBoostUseOrientation(bool)));
  connect(mBoost, SIGNAL(scaleFactorChange(double)),         mModel, SLOT(setBoostScaleFactor(double)));
#endif

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
  connect(mKaze, SIGNAL(uprightDescriptorChange(bool)),      mModel, SLOT(setKazeUpright(bool)));
  connect(mKaze, SIGNAL(thresholdChange(double)),            mModel, SLOT(setKazeThreshold(double)));
  connect(mKaze, SIGNAL(octavesChange(int)),                 mModel, SLOT(setKazeOctaves(int)));
  connect(mKaze, SIGNAL(octaveLayersChange(int)),            mModel, SLOT(setKazeOctaveLayers(int)));
  connect(mKaze, SIGNAL(diffusivityChange(QString)),         mModel, SLOT(setKazeDiffusivity(QString)));

  /* LATCH */
  connect(mLatch, SIGNAL(bytesChange(QString)),              mModel, SLOT(setLatchBytes(QString)));
  connect(mLatch, SIGNAL(rotationInvarianceChange(bool)),    mModel, SLOT(setLatchRotationInvariance(bool)));
  connect(mLatch, SIGNAL(halfSsdSizeChange(int)),            mModel, SLOT(setLatchHalfSsdSize(int)));

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
#ifdef OPENCV_ENABLE_NONFREE
  connect(mSift, SIGNAL(featuresNumberChange(int)),          mModel, SLOT(setSiftFeaturesNumber(int)));
  connect(mSift, SIGNAL(octaveLayersChange(int)),            mModel, SLOT(setSiftOctaveLayers(int)));
  connect(mSift, SIGNAL(contrastThresholdChange(double)),    mModel, SLOT(setSiftContrastThreshold(double)));
  connect(mSift, SIGNAL(edgeThresholdChange(double)),        mModel, SLOT(setSiftEdgeThreshold(double)));
  connect(mSift, SIGNAL(sigmaChange(double)),                mModel, SLOT(setSiftSigma(double)));
#endif

  /* STAR */
  connect(mStar, SIGNAL(maxSizeChange(int)),                 mModel, SLOT(setStarMaxSize(int)));
  connect(mStar, SIGNAL(responseThresholdChange(int)),       mModel, SLOT(setStarResponseThreshold(int)));
  connect(mStar, SIGNAL(lineThresholdProjectedChange(int)),  mModel, SLOT(setStarLineThresholdProjected(int)));
  connect(mStar, SIGNAL(lineThresholdBinarizedChange(int)),  mModel, SLOT(setStarLineThresholdBinarized(int)));
  connect(mStar, SIGNAL(suppressNonmaxSizeChange(int)),      mModel, SLOT(setStarSuppressNonmaxSize(int)));

  /* SURF */
#ifdef OPENCV_ENABLE_NONFREE
  connect(mSurf, SIGNAL(hessianThresholdChange(double)),     mModel, SLOT(setSurfHessianThreshold(double)));
  connect(mSurf, SIGNAL(octavesChange(int)),                 mModel, SLOT(setSurfOctaves(int)));
  connect(mSurf, SIGNAL(octaveLayersChange(int)),            mModel, SLOT(setSurfOctaveLayers(int)));
  connect(mSurf, SIGNAL(extendedDescriptorChange(bool)),     mModel, SLOT(setSurfExtendedDescriptor(bool)));
  connect(mSurf, SIGNAL(rotatedFeaturesChange(bool)),        mModel, SLOT(setSurfRotatedFeatures(bool)));
#endif

  /* VGG */
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  connect(mVgg, SIGNAL(descriptorTypeChange(QString)),        mModel, SLOT(setVggDescriptorType(QString)));
  connect(mVgg, SIGNAL(scaleFactorChange(double)),            mModel, SLOT(setVggScaleFactor(double)));
  connect(mVgg, SIGNAL(sigmaChange(double)),                  mModel, SLOT(setVggSigma(double)));
  connect(mVgg, SIGNAL(useNormalizeDescriptorChange(bool)),   mModel, SLOT(setVggUseNormalizeDescriptor(bool)));
  connect(mVgg, SIGNAL(useNormalizeDescriptorChange(bool)),   mModel, SLOT(setVggUseNormalizeImage(bool)));
  connect(mVgg, SIGNAL(useNormalizeDescriptorChange(bool)),   mModel, SLOT(setVggUseScaleOrientation(bool)));
#endif

  /* Matching */
  connect(mMatcher, SIGNAL(matchingMethodChange(QString)),                  mModel, SLOT(setMatchMethod(QString)));
  connect(mMatcher, SIGNAL(normTypeChange(QString)),                        mModel, SLOT(setMatchNormType(QString)));
  connect(mMatcher, SIGNAL(ratioChange(double)),                            mModel, SLOT(setMatchRatio(double)));
  connect(mMatcher, SIGNAL(distanceChange(double)),                         mModel, SLOT(setMatchDistance(double)));
  connect(mMatcher, SIGNAL(confidenceChange(double)),                       mModel, SLOT(setMatchConfidence(double)));
  connect(mMatcher, SIGNAL(crossMatchingChange(bool)),                      mModel, SLOT(setMatchCrossMatching(bool)));
  connect(mMatcher, SIGNAL(maxItersChange(int)),                            mModel, SLOT(setMatchMaxIters(int)));
  connect(mMatcher, SIGNAL(geometricTestChange(QString)),                   mModel, SLOT(setMatchGeometricTest(QString)));
  connect(mMatcher, SIGNAL(homographyComputeMethodChange(QString)),         mModel, SLOT(setMatchHomographyComputeMethod(QString)));
  connect(mMatcher, SIGNAL(fundamentalComputeMethodChange(QString)),        mModel, SLOT(setMatchFundamentalComputeMethod(QString)));
  connect(mMatcher, SIGNAL(essentialComputeMethodChange(QString)),          mModel, SLOT(setMatchEssentialComputeMethod(QString)));

  /* Keypoints Viewer */
  connect(mView, SIGNAL(keypointsViewerBGColorChange(QString)),             mModel, SLOT(setKeypointsViewerBGColor(QString)));
  connect(mView, SIGNAL(keypointsViewerMarkerTypeChange(int)),              mModel, SLOT(setKeypointsViewerMarkerType(int)));
  connect(mView, SIGNAL(keypointsViewerMarkerSizeChange(int)),              mModel, SLOT(setKeypointsViewerMarkerSize(int)));
  connect(mView, SIGNAL(keypointsViewerMarkerWidthChange(int)),             mModel, SLOT(setKeypointsViewerMarkerWidth(int)));
  connect(mView, SIGNAL(keypointsViewerMarkerColorChange(QString)),         mModel, SLOT(setKeypointsViewerMarkerColor(QString)));
  connect(mView, SIGNAL(selectKeypointsViewerMarkerWidthChange(int)),       mModel, SLOT(setKeypointsViewerSelectMarkerWidth(int)));
  connect(mView, SIGNAL(selectKeypointsViewerMarkerColorChange(QString)),   mModel, SLOT(setKeypointsViewerSelectMarkerColor(QString)));

  /* Matches Viewer */
  connect(mView, SIGNAL(matchesViewerBGColorChange(QString)),               mModel, SLOT(setMatchesViewerBGColor(QString)));
  connect(mView, SIGNAL(matchesViewerMarkerTypeChange(int)),                mModel, SLOT(setMatchesViewerMarkerType(int)));
  connect(mView, SIGNAL(matchesViewerMarkerSizeChange(int)),                mModel, SLOT(setMatchesViewerMarkerSize(int)));
  connect(mView, SIGNAL(matchesViewerMarkerWidthChange(int)),               mModel, SLOT(setMatchesViewerMarkerWidth(int)));
  connect(mView, SIGNAL(matchesViewerMarkerColorChange(QString)),           mModel, SLOT(setMatchesViewerMarkerColor(QString)));
  connect(mView, SIGNAL(selectMatchesViewerMarkerWidthChange(int)),         mModel, SLOT(setMatchesViewerSelectMarkerWidth(int)));
  connect(mView, SIGNAL(selectMatchesViewerMarkerColorChange(QString)),     mModel, SLOT(setMatchesViewerSelectMarkerColor(QString)));
  connect(mView, SIGNAL(matchesViewerLineWidthChange(int)),                 mModel, SLOT(setMatchesViewerLineWidth(int)));
  connect(mView, SIGNAL(matchesViewerLineColorChange(QString)),             mModel, SLOT(setMatchesViewerLineColor(QString)));

  /* Ground Truth Editor */
  connect(mView, SIGNAL(groundTruthEditorBGColorChange(QString)),           mModel, SLOT(setGroundTruthEditorBGColor(QString)));
  connect(mView, SIGNAL(groundTruthEditorMarkerSizeChange(int)),            mModel, SLOT(setGroundTruthEditorMarkerSize(int)));
  connect(mView, SIGNAL(groundTruthEditorMarkerWidthChange(int)),           mModel, SLOT(setGroundTruthEditorMarkerWidth(int)));
  connect(mView, SIGNAL(groundTruthEditorMarkerColorChange(QString)),       mModel, SLOT(setGroundTruthEditorMarkerColor(QString)));
  connect(mView, SIGNAL(selectGroundTruthEditorMarkerWidthChange(int)),     mModel, SLOT(setGroundTruthEditorSelectMarkerWidth(int)));
  connect(mView, SIGNAL(selectGroundTruthEditorMarkerColorChange(QString)), mModel, SLOT(setGroundTruthEditorSelectMarkerColor(QString)));
  connect(mView, SIGNAL(groundTruthEditorMatrixAdjustChange(QString)),      mModel, SLOT(setGroundTruthEditorMatrixAdjust(QString)));
}

void SettingsPresenterImp::setLanguage(const QString &language)
{
  QString lang_code = mLang[language];

  mModel->setLanguage(lang_code);
}

void SettingsPresenterImp::save()
{
  mModel->write();
}

void SettingsPresenterImp::discart()
{
  mModel->read();
}

} // End namespace photomatch
