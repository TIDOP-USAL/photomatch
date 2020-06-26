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
  this->setGeneralSettings();
  this->setToolsSettings();
  this->setQualityControlSettings();

  mView->exec();
}

void SettingsPresenterImp::setGeneralSettings()
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
#ifdef HAVE_CUDA
  mView->setCudaEnabled(true);
#else
  mView->setCudaEnabled(false);
#endif //HAVE_CUDA

}

void SettingsPresenterImp::setToolsSettings()
{
  this->setKeypointsFormat();
  this->setMatchesFormat();
  this->setPreprocessSettings();
  this->setFeatureDetectorExtractorSettings();
  this->setMatchingSettings();
}

void SettingsPresenterImp::setKeypointsFormat()
{
  mView->setKeypointsFormat(mModel->keypointsFormat());
}

void SettingsPresenterImp::setMatchesFormat()
{
  mView->setMatchesFormat(mModel->matchesFormat());
}

void SettingsPresenterImp::setPreprocessSettings()
{
  this->setAcebsfSettings();
  this->setClaheSettings();
  this->setCmbfhe();
  this->setDheSettings();
  this->setFahe();
  this->setHmclaheSettings();
  this->setLceBsescsSettings();
  this->setMsrcpSettings();
  this->setNoshpSettings();
  this->setPoheSettings();
  this->setRswheSettings();
  this->setWallisSettings();
}

void SettingsPresenterImp::setAcebsfSettings()
{
  mACEBSF->setBlockSize(mModel->acebsfBlockSize());
  mACEBSF->setL(mModel->acebsfL());
  mACEBSF->setK1(mModel->acebsfK1());
  mACEBSF->setK2(mModel->acebsfK2());
}

void SettingsPresenterImp::setClaheSettings()
{
  mCLAHE->setClipLimit(mModel->claheClipLimit());
  mCLAHE->setTilesGridSize(mModel->claheTilesGridSize());
}


void SettingsPresenterImp::setCmbfhe()
{
  mCMBFHE->setBlockSize(mModel->cmbfheBlockSize());
}

void SettingsPresenterImp::setDheSettings()
{
  mDHE->setX(mModel->dheX());
}

void SettingsPresenterImp::setFahe()
{
  mFAHE->setBlockSize(mModel->faheBlockSize());
}

void SettingsPresenterImp::setHmclaheSettings()
{
  mHMCLAHE->setBlockSize(mModel->hmclaheBlockSize());
  mHMCLAHE->setL(mModel->hmclaheL());
  mHMCLAHE->setPhi(mModel->hmclahePhi());
}

void SettingsPresenterImp::setLceBsescsSettings()
{
  mLCEBSESCS->setBlockSize(mModel->lceBsescsBlockSize());
}

void SettingsPresenterImp::setMsrcpSettings()
{
  mMSRCP->setMidScale(mModel->msrcpMidScale());
  mMSRCP->setLargeScale(mModel->msrcpLargeScale());
  mMSRCP->setSmallScale(mModel->msrcpSmallScale());
}

void SettingsPresenterImp::setNoshpSettings()
{
  mNOSHP->setBlockSize(mModel->noshpBlockSize());
}

void SettingsPresenterImp::setPoheSettings()
{
  mPOHE->setBlockSize(mModel->poheBlockSize());
}

void SettingsPresenterImp::setRswheSettings()
{
  mRSWHE->setHistogramCut(static_cast<RswheWidget::HistogramCut>(mModel->rswheHistogramCut()));
  mRSWHE->setHistogramDivisions(mModel->rswheHistogramDivisions());
}

void SettingsPresenterImp::setWallisSettings()
{
  mWallis->setContrast(mModel->wallisContrast());
  mWallis->setBrightness(mModel->wallisBrightness());
  mWallis->setKernelSize(mModel->wallisKernelSize());
  mWallis->setImposedAverage(mModel->wallisImposedAverage());
  mWallis->setImposedLocalStdDev(mModel->wallisImposedLocalStdDev());
}

void SettingsPresenterImp::setFeatureDetectorExtractorSettings()
{
  this->setAgastSettings();
  this->setAkazeSettings();
  this->setBoostSettings();
  this->setBriefSettings();
  this->setBriskSettings();
  this->setDaisySettings();
  this->setFastSettings();
  this->setFreakSettings();
  this->setGfttSettings();
  this->setHogSettings();
  this->setKazeSettings();
  this->setLatchSettings();
  this->setMsdSettings();
  this->setMserSettings();
  this->setOrbSettings();
  this->setSiftSettings();
  this->setStarSettings();
  this->setSurfSettings();
  this->setVggSettings();
}

void SettingsPresenterImp::setAgastSettings()
{
  mAgast->setThreshold(mModel->agastThreshold());
  mAgast->setDetectorType(mModel->agastDetectorType());
  mAgast->setNonmaxSuppression(mModel->agastNonmaxSuppression());
}

void SettingsPresenterImp::setAkazeSettings()
{
  mAkaze->setOctaves(mModel->akazeOctaves());
  mAkaze->setThreshold(mModel->akazeThreshold());
  mAkaze->setDiffusivity(mModel->akazeDiffusivity());
  mAkaze->setOctaveLayers(mModel->akazeOctaveLayers());
  mAkaze->setDescriptorSize(mModel->akazeDescriptorSize());
  mAkaze->setDescriptorType(mModel->akazeDescriptorType());
  mAkaze->setDescriptorChannels(mModel->akazeDescriptorChannels());
}

void SettingsPresenterImp::setBoostSettings()
{
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  mBoost->setDescriptorType(mModel->boostDescriptorType());
  mBoost->setUseOrientation(mModel->boostUseOrientation());
  mBoost->setScaleFactor(mModel->boostScaleFactor());
#endif
}

void SettingsPresenterImp::setBriefSettings()
{
  mBrief->setBytes(mModel->briefBytes());
  mBrief->setUseOrientation(mModel->briefUseOrientation());
}

void SettingsPresenterImp::setBriskSettings()
{
  mBrisk->setThreshold(mModel->briskThreshold());
  mBrisk->setOctaves(mModel->briskOctaves());
  mBrisk->setPatternScale(mModel->briskPatternScale());
}

void SettingsPresenterImp::setDaisySettings()
{
  mDaisy->setNorm(mModel->daisyNorm());
  mDaisy->setQRadius(mModel->daisyQRadius());
  mDaisy->setQTheta(mModel->daisyQTheta());
  mDaisy->setQHist(mModel->daisyQHist());
  mDaisy->setNorm(mModel->daisyNorm());
  mDaisy->setInterpolation(mModel->daisyInterpolation());
  mDaisy->setUseOrientation(mModel->daisyUseOrientation());
}

void SettingsPresenterImp::setFastSettings()
{
  mFast->setThreshold(mModel->fastThreshold());
  mFast->setNonmaxSuppression(mModel->fastNonmaxSuppression());
  mFast->setDetectorType(mModel->fastdetectorType());
}

void SettingsPresenterImp::setFreakSettings()
{
  mFreak->setOrientationNormalized(mModel->freakOrientationNormalized());
  mFreak->setScaleNormalized(mModel->freakScaleNormalized());
  mFreak->setPatternScale(mModel->freakPatternScale());
  mFreak->setOctaves(mModel->freakOctaves());
}

void SettingsPresenterImp::setGfttSettings()
{
  mGftt->setMaxFeatures(mModel->gfttMaxFeatures());
  mGftt->setQualityLevel(mModel->gfttQualityLevel());
  mGftt->setMinDistance(mModel->gfttMinDistance());
  mGftt->setBlockSize(mModel->gfttBlockSize());
  mGftt->setHarrisDetector(mModel->gfttHarrisDetector());
  mGftt->setK(mModel->gfttK());
}

void SettingsPresenterImp::setHogSettings()
{
  mHog->setWinSize(mModel->hogWinSize());
  mHog->setBlockSize(mModel->hogBlockSize());
  mHog->setBlockStride(mModel->hogBlockStride());
  mHog->setCellSize(mModel->hogCellSize());
  mHog->setNbins(mModel->hogNbins());
  mHog->setDerivAperture(mModel->hogDerivAperture());
}

void SettingsPresenterImp::setKazeSettings()
{
  mKaze->setExtendedDescriptor(mModel->kazeExtendedDescriptor());
  mKaze->setUprightDescriptor(mModel->kazeUpright());
  mKaze->setThreshold(mModel->kazeUpright());
  mKaze->setOctaves(mModel->kazeOctaves());
  mKaze->setOctaveLayers(mModel->kazeOctaveLayers());
  mKaze->setDiffusivity(mModel->kazeDiffusivity());
}

void SettingsPresenterImp::setLatchSettings()
{
  mLatch->setBytes(mModel->latchBytes());
  mLatch->setRotationInvariance(mModel->latchRotationInvariance());
  mLatch->setHalfSsdSize(mModel->latchHalfSsdSize());
}

void SettingsPresenterImp::setMsdSettings()
{
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
}

void SettingsPresenterImp::setMserSettings()
{
  mMser->setDelta(mModel->mserDelta());
  mMser->setMaxArea(mModel->mserMaxArea());
  mMser->setMinArea(mModel->mserMinArea());
  mMser->setMaxVariation(mModel->mserMaxVariation());
  mMser->setMinDiversity(mModel->mserMinDiversity());
  mMser->setMaxEvolution(mModel->mserMaxEvolution());
  mMser->setAreaThreshold(mModel->mserAreaThreshold());
  mMser->setMinMargin(mModel->mserMinMargin());
  mMser->setEdgeBlurSize(mModel->mserEdgeBlurSize());
}

void SettingsPresenterImp::setOrbSettings()
{
  mOrb->setScaleFactor(mModel->orbScaleFactor());
  mOrb->setFeaturesNumber(mModel->orbFeaturesNumber());
  mOrb->setLevelsNumber(mModel->orbLevelsNumber());
  mOrb->setEdgeThreshold(mModel->orbEdgeThreshold());
  mOrb->setWTA_K(mModel->orbWta_k());
  mOrb->setScoreType(mModel->orbScoreType());
  mOrb->setPatchSize(mModel->orbPatchSize());
  mOrb->setFastThreshold(mModel->orbFastThreshold());
}

void SettingsPresenterImp::setSiftSettings()
{
#ifdef OPENCV_ENABLE_NONFREE
  mSift->setSigma(mModel->siftSigma());
  mSift->setOctaveLayers(mModel->siftOctaveLayers());
  mSift->setEdgeThreshold(mModel->siftEdgeThreshold());
  mSift->setFeaturesNumber(mModel->siftFeaturesNumber());
  mSift->setContrastThreshold(mModel->siftContrastThreshold());
#endif
}

void SettingsPresenterImp::setStarSettings()
{
  mStar->setMaxSize(mModel->starMaxSize());
  mStar->setResponseThreshold(mModel->starResponseThreshold());
  mStar->setLineThresholdProjected(mModel->starLineThresholdProjected());
  mStar->setLineThresholdBinarized(mModel->starLineThresholdBinarized());
  mStar->setSuppressNonmaxSize(mModel->starSuppressNonmaxSize());
}

void SettingsPresenterImp::setSurfSettings()
{
#ifdef OPENCV_ENABLE_NONFREE
  mSurf->setOctaves(mModel->surfOctaves());
  mSurf->setOctaveLayers(mModel->surfOctaveLayers());
  mSurf->seUpright(mModel->surfRotatedFeatures());
  mSurf->setHessianThreshold(mModel->surfHessianThreshold());
  mSurf->setExtendedDescriptor(mModel->surfExtendedDescriptor());
#endif
}

void SettingsPresenterImp::setVggSettings()
{
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  mVgg->setDescriptorType(mModel->boostDescriptorType());
  mVgg->setScaleFactor(mModel->boostScaleFactor());
  mVgg->setSigma(mModel->vggSigma());
  mVgg->setUseNormalizeDescriptor(mModel->vggUseNormalizeDescriptor());
  mVgg->setUseNormalizeImage(mModel->vggUseNormalizeImage());
  mVgg->setUseScaleOrientation(mModel->vggUseScaleOrientation());
#endif
}

void SettingsPresenterImp::setMatchingSettings()
{
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
}

void SettingsPresenterImp::setQualityControlSettings()
{
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
}

void SettingsPresenterImp::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void SettingsPresenterImp::init()
{
  this->addPreprocesses();
  this->addFeatureDetectorMethods();
  this->addDescriptorMatcher();
}

void SettingsPresenterImp::addPreprocesses()
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
}

void SettingsPresenterImp::addFeatureDetectorMethods()
{
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
  mView->addFeatureDetectorMethod(mMsd);
  mView->addFeatureDetectorMethod(mMser);
  mView->addFeatureDetectorMethod(mStar);
  mView->addFeatureDetectorMethod(mHog);
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  mView->addFeatureDetectorMethod(mVgg);
#endif
}

void SettingsPresenterImp::addDescriptorMatcher()
{
  mView->addDescriptorMatcher(mMatcher);
}

void SettingsPresenterImp::initSignalAndSlots()
{
  connect(mView, &SettingsView::languageChange, this, &SettingsPresenterImp::setLanguage);
  connect(mView, &SettingsView::historyMaxSizeChange, mModel, &SettingsModel::setHistoryMaxSize);
  connect(mView, &SettingsView::keypointsFormatChange, mModel, &SettingsModel::setKeypointsFormat);
  connect(mView, &SettingsView::matchesFormatChange, mModel, &SettingsModel::setMatchesFormat);
  connect(mView, &SettingsView::useCudaChange, mModel, &SettingsModel::setUseCuda);

  connect(mView, &SettingsView::imageViewerBGColorChange, mModel, &SettingsModel::setImageViewerBGcolor);

  connect(mModel, &SettingsModel::unsavedChanges, mView, &SettingsView::setUnsavedChanges);

  /* ACEBSF */
  connect(mACEBSF, &AcebsfWidget::blockSizeChange, mModel, &SettingsModel::setAcebsfBlockSize);
  connect(mACEBSF, &AcebsfWidget::lChange, mModel, &SettingsModel::setAcebsfL);
  connect(mACEBSF, &AcebsfWidget::k1Change, mModel, &SettingsModel::setAcebsfK1);
  connect(mACEBSF, &AcebsfWidget::k2Change, mModel, &SettingsModel::setAcebsfK2);

  /* CLAHE */
  connect(mCLAHE, &ClaheWidget::clipLimitChange, mModel, &SettingsModel::setClaheClipLimit);
  connect(mCLAHE, &ClaheWidget::tileGridSizeChange, mModel, &SettingsModel::setClaheTilesGridSize);

  /* CMBFHE */
  connect(mCMBFHE, &CmbfheWidget::blockSizeChange, mModel, &SettingsModel::setCmbfheBlockSize);

  /* DHE */
  connect(mDHE, &DheWidget::xChange, mModel, &SettingsModel::setDheX);

  /* FAHE */
  connect(mFAHE, &FaheWidget::blockSizeChange, mModel, &SettingsModel::setFaheBlockSize);

  /* HMCLAHE */
  connect(mHMCLAHE, &HmclaheWidget::blockSizeChange, mModel, &SettingsModel::setHmclaheBlockSize);
  connect(mHMCLAHE, &HmclaheWidget::lChange, mModel, &SettingsModel::setHmclaheL);
  connect(mHMCLAHE, &HmclaheWidget::phiChange, mModel, &SettingsModel::setHmclahePhi);

  /* LCEBSESCS */
  connect(mLCEBSESCS, &LceBsescsWidget::blockSizeChange, mModel, &SettingsModel::setLceBsescsBlockSize);

  /* MSRCP */
  connect(mMSRCP, &MsrcpWidget::smallScaleChange, mModel, &SettingsModel::setMsrcpSmallScale);
  connect(mMSRCP, &MsrcpWidget::midScaleChange, mModel, &SettingsModel::setMsrcpMidScale);
  connect(mMSRCP, &MsrcpWidget::largeScaleChange, mModel, &SettingsModel::setMsrcpLargeScale);

  /* NOSHP */
  connect(mNOSHP, &NoshpWidget::blockSizeChange, mModel, &SettingsModel::setNoshpBlockSize);

  /* POHE */
  connect(mPOHE, &PoheWidget::blockSizeChange, mModel, &SettingsModel::setPoheBlockSize);

  /* RSWHE */
  connect(mRSWHE, &RswheWidget::histogramDivisionsChange, mModel, &SettingsModel::setRswheHistogramDivisions);
  connect(mRSWHE, &RswheWidget::histogramCutChange, mModel, &SettingsModel::setRswheHistogramCut);

  /* WALLIS */
  connect(mWallis, &WallisWidget::contrastChange, mModel, &SettingsModel::setWallisContrast);
  connect(mWallis, &WallisWidget::brightnessChange, mModel, &SettingsModel::setWallisBrightness);
  connect(mWallis, &WallisWidget::imposedAverageChange, mModel, &SettingsModel::setWallisImposedAverage);
  connect(mWallis, &WallisWidget::imposedLocalStdDevChange, mModel, &SettingsModel::setWallisImposedLocalStdDev);
  connect(mWallis, &WallisWidget::kernelSizeChange, mModel, &SettingsModel::setWallisKernelSize);

  /* AGAST */
  connect(mAgast, &AgastWidget::thresholdChange, mModel, &SettingsModel::setAgastThreshold);
  connect(mAgast, &AgastWidget::nonmaxSuppressionChange, mModel, &SettingsModel::setAgastNonmaxSuppression);
  connect(mAgast, &AgastWidget::detectorTypeChange, mModel, &SettingsModel::setAgastDetectorType);

  /* AKAZE */
  connect(mAkaze, &AkazeWidget::descriptorTypeChange, mModel, &SettingsModel::setAkazeDescriptorType);
  connect(mAkaze, &AkazeWidget::descriptorSizeChange, mModel, &SettingsModel::setAkazeDescriptorSize);
  connect(mAkaze, &AkazeWidget::descriptorChannelsChange, mModel, &SettingsModel::setAkazeDescriptorChannels);
  connect(mAkaze, &AkazeWidget::thresholdChange, mModel, &SettingsModel::setAkazeThreshold);
  connect(mAkaze, &AkazeWidget::octavesChange, mModel, &SettingsModel::setAkazeOctaves);
  connect(mAkaze, &AkazeWidget::octaveLayersChange, mModel, &SettingsModel::setAkazeOctaveLayers);
  connect(mAkaze, &AkazeWidget::diffusivityChange, mModel, &SettingsModel::setAkazeDiffusivity);

  /* BOOST */
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  connect(mBoost, &BoostWidget::descriptorTypeChange, mModel, &SettingsModel::setBoostDescriptorType);
  connect(mBoost, &BoostWidget::useOrientationChange, mModel, &SettingsModel::setBoostUseOrientation);
  connect(mBoost, &BoostWidget::scaleFactorChange, mModel, &SettingsModel::setBoostScaleFactor);
#endif

  /* BRIEF */
  connect(mBrief, &BriefWidget::bytesChange, mModel, &SettingsModel::setBriefBytes);
  connect(mBrief, &BriefWidget::useOrientationChange, mModel, &SettingsModel::setBriefUseOrientation);

  /* BRISK */
  connect(mBrisk, &BriskWidget::thresholdChange, mModel, &SettingsModel::setBriskThreshold);
  connect(mBrisk, &BriskWidget::octavesChange, mModel, &SettingsModel::setBriskOctaves);
  connect(mBrisk, &BriskWidget::patternScaleChange, mModel, &SettingsModel::setBriskPatternScale);

  /* DAISY */
  connect(mDaisy, &DaisyWidget::radiusChange, mModel, &SettingsModel::setDaisyRadius);
  connect(mDaisy, &DaisyWidget::qRadiusChange, mModel, &SettingsModel::setDaisyQRadius);
  connect(mDaisy, &DaisyWidget::qThetaChange, mModel, &SettingsModel::setDaisyQTheta);
  connect(mDaisy, &DaisyWidget::qHistChange, mModel, &SettingsModel::setDaisyQHist);
  connect(mDaisy, &DaisyWidget::normChange, mModel, &SettingsModel::setDaisyNorm);
  connect(mDaisy, &DaisyWidget::interpolationChange, mModel, &SettingsModel::setDaisyInterpolation);
  connect(mDaisy, &DaisyWidget::useOrientationChange, mModel, &SettingsModel::setDaisyUseOrientation);

  /* FAST */
  connect(mFast, &FastWidget::thresholdChange, mModel, &SettingsModel::setFastThreshold);
  connect(mFast, &FastWidget::nonmaxSuppressionChange, mModel, &SettingsModel::setFastNonmaxSuppression);
  connect(mFast, &FastWidget::detectorTypeChange, mModel, &SettingsModel::setFastDetectorType);

  /* FREAK */
  connect(mFreak, &FreakWidget::orientationNormalizedChange, mModel, &SettingsModel::setFreakOrientationNormalized);
  connect(mFreak, &FreakWidget::scaleNormalizedChange, mModel, &SettingsModel::setFreakScaleNormalized);
  connect(mFreak, &FreakWidget::patternScaleChange, mModel, &SettingsModel::setFreakPatternScale);
  connect(mFreak, &FreakWidget::octavesChange, mModel, &SettingsModel::setFreakOctaves);

  /* GFTT */
  connect(mGftt, &GfttWidget::maxFeaturesChange, mModel, &SettingsModel::setGfttMaxFeatures);
  connect(mGftt, &GfttWidget::qualityLevelChange, mModel, &SettingsModel::setGfttQualityLevel);
  connect(mGftt, &GfttWidget::minDistanceChange, mModel, &SettingsModel::setGfttMinDistance);
  connect(mGftt, &GfttWidget::blockSizeChange, mModel, &SettingsModel::setGfttBlockSize);
  connect(mGftt, &GfttWidget::harrisDetectorChange, mModel, &SettingsModel::setGfttHarrisDetector);
  connect(mGftt, &GfttWidget::kChange, mModel, &SettingsModel::setGfttK);

  /* HOG */
  connect(mHog, &HogWidget::winSizeChange, mModel, &SettingsModel::setHogWinSize);
  connect(mHog, &HogWidget::blockSizeChange, mModel, &SettingsModel::setHogBlockSize);
  connect(mHog, &HogWidget::blockStrideChange, mModel, &SettingsModel::setHogBlockStride);
  connect(mHog, &HogWidget::cellSizeChange, mModel, &SettingsModel::setHogCellSize);
  connect(mHog, &HogWidget::nbinsChange, mModel, &SettingsModel::setHogNbins);
  connect(mHog, &HogWidget::derivApertureChange, mModel, &SettingsModel::setHogDerivAperture);

  /* KAZE */
  connect(mKaze, &KazeWidget::extendedDescriptorChange, mModel, &SettingsModel::setKazeExtendedDescriptor);
  connect(mKaze, &KazeWidget::uprightDescriptorChange, mModel, &SettingsModel::setKazeUpright);
  connect(mKaze, &KazeWidget::thresholdChange, mModel, &SettingsModel::setKazeThreshold);
  connect(mKaze, &KazeWidget::octavesChange, mModel, &SettingsModel::setKazeOctaves);
  connect(mKaze, &KazeWidget::octaveLayersChange, mModel, &SettingsModel::setKazeOctaveLayers);
  connect(mKaze, &KazeWidget::diffusivityChange, mModel, &SettingsModel::setKazeDiffusivity);

  /* LATCH */
  connect(mLatch, &LatchWidget::bytesChange, mModel, &SettingsModel::setLatchBytes);
  connect(mLatch, &LatchWidget::rotationInvarianceChange, mModel, &SettingsModel::setLatchRotationInvariance);
  connect(mLatch, &LatchWidget::halfSsdSizeChange, mModel, &SettingsModel::setLatchHalfSsdSize);

  /* MSD */
  connect(mMsd, &MsdWidget::thresholdSaliencyChange, mModel, &SettingsModel::setMsdThresholdSaliency);
  connect(mMsd, &MsdWidget::pathRadiusChange, mModel, &SettingsModel::setMsdPathRadius);
  connect(mMsd, &MsdWidget::KNNChange, mModel, &SettingsModel::setMsdKNN);
  connect(mMsd, &MsdWidget::areaRadiusChange, mModel, &SettingsModel::setMsdAreaRadius);
  connect(mMsd, &MsdWidget::scaleFactorChange, mModel, &SettingsModel::setMsdScaleFactor);
  connect(mMsd, &MsdWidget::NMSRadiusChange, mModel, &SettingsModel::setMsdNMSRadius);
  connect(mMsd, &MsdWidget::nScalesChange, mModel, &SettingsModel::setMsdNScales);
  connect(mMsd, &MsdWidget::NMSScaleRChange, mModel, &SettingsModel::setMsdNMSScaleR);
  connect(mMsd, &MsdWidget::computeOrientationsChange, mModel, &SettingsModel::setMsdComputeOrientations);
  connect(mMsd, &MsdWidget::affineMSDChange, mModel, &SettingsModel::setMsdAffineMSD);
  connect(mMsd, &MsdWidget::tiltsChange, mModel, &SettingsModel::setMsdTilts);

  /* MSER */
  connect(mMser, &MserWidget::deltaChange, mModel, &SettingsModel::setMserDelta);
  connect(mMser, &MserWidget::minAreaChange, mModel, &SettingsModel::setMserMinArea);
  connect(mMser, &MserWidget::maxAreaChange, mModel, &SettingsModel::setMserMaxArea);
  connect(mMser, &MserWidget::maxVariationChange, mModel, &SettingsModel::setMserMaxVariation);
  connect(mMser, &MserWidget::minDiversityChange, mModel, &SettingsModel::setMserMinDiversity);
  connect(mMser, &MserWidget::maxEvolutionChange, mModel, &SettingsModel::setMserMaxEvolution);
  connect(mMser, &MserWidget::areaThresholdChange, mModel, &SettingsModel::setMserAreaThreshold);
  connect(mMser, &MserWidget::minMarginChange, mModel, &SettingsModel::setMserMinMargin);
  connect(mMser, &MserWidget::edgeBlurSizeChange, mModel, &SettingsModel::setMserEdgeBlurSize);

  /* ORB */
  connect(mOrb, &OrbWidget::scaleFactorChange, mModel, &SettingsModel::setOrbScaleFactor);
  connect(mOrb, &OrbWidget::featuresNumberChange, mModel, &SettingsModel::setOrbFeaturesNumber);
  connect(mOrb, &OrbWidget::levelsNumberChange, mModel, &SettingsModel::setOrbLevelsNumber);
  connect(mOrb, &OrbWidget::edgeThresholdChange, mModel, &SettingsModel::setOrbEdgeThreshold);
  connect(mOrb, &OrbWidget::wta_kChange, mModel, &SettingsModel::setOrbWTA_K);
  connect(mOrb, &OrbWidget::scoreTypeChange, mModel, &SettingsModel::setOrbScoreType);
  connect(mOrb, &OrbWidget::patchSizeChange, mModel, &SettingsModel::setOrbPatchSize);
  connect(mOrb, &OrbWidget::fastThresholdChange, mModel, &SettingsModel::setOrbFastThreshold);

  /* SIFT */
#ifdef OPENCV_ENABLE_NONFREE
  connect(mSift, &SiftWidget::featuresNumberChange, mModel, &SettingsModel::setSiftFeaturesNumber);
  connect(mSift, &SiftWidget::octaveLayersChange, mModel, &SettingsModel::setSiftOctaveLayers);
  connect(mSift, &SiftWidget::contrastThresholdChange, mModel, &SettingsModel::setSiftContrastThreshold);
  connect(mSift, &SiftWidget::edgeThresholdChange, mModel, &SettingsModel::setSiftEdgeThreshold);
  connect(mSift, &SiftWidget::sigmaChange, mModel, &SettingsModel::setSiftSigma);
#endif

  /* STAR */
  connect(mStar, &StarWidget::maxSizeChange, mModel, &SettingsModel::setStarMaxSize);
  connect(mStar, &StarWidget::responseThresholdChange, mModel, &SettingsModel::setStarResponseThreshold);
  connect(mStar, &StarWidget::lineThresholdProjectedChange, mModel, &SettingsModel::setStarLineThresholdProjected);
  connect(mStar, &StarWidget::lineThresholdBinarizedChange, mModel, &SettingsModel::setStarLineThresholdBinarized);
  connect(mStar, &StarWidget::suppressNonmaxSizeChange, mModel, &SettingsModel::setStarSuppressNonmaxSize);

  /* SURF */
#ifdef OPENCV_ENABLE_NONFREE
  connect(mSurf, &SurfWidget::hessianThresholdChange, mModel, &SettingsModel::setSurfHessianThreshold);
  connect(mSurf, &SurfWidget::octavesChange, mModel, &SettingsModel::setSurfOctaves);
  connect(mSurf, &SurfWidget::octaveLayersChange, mModel, &SettingsModel::setSurfOctaveLayers);
  connect(mSurf, &SurfWidget::extendedDescriptorChange, mModel, &SettingsModel::setSurfExtendedDescriptor);
  connect(mSurf, &SurfWidget::rotatedFeaturesChange, mModel, &SettingsModel::setSurfRotatedFeatures);
#endif

  /* VGG */
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  connect(mVgg, &VggWidget::descriptorTypeChange, mModel, &SettingsModel::setVggDescriptorType);
  connect(mVgg, &VggWidget::scaleFactorChange, mModel, &SettingsModel::setVggScaleFactor);
  connect(mVgg, &VggWidget::sigmaChange, mModel, &SettingsModel::setVggSigma);
  connect(mVgg, &VggWidget::useNormalizeDescriptorChange, mModel, &SettingsModel::setVggUseNormalizeDescriptor);
  connect(mVgg, &VggWidget::useNormalizeDescriptorChange, mModel, &SettingsModel::setVggUseNormalizeImage);
  connect(mVgg, &VggWidget::useNormalizeDescriptorChange, mModel, &SettingsModel::setVggUseScaleOrientation);
#endif

  /* Matching */
  connect(mMatcher, &DescriptorMatcherWidget::matchingMethodChange, mModel, &SettingsModel::setMatchMethod);
  connect(mMatcher, &DescriptorMatcherWidget::normTypeChange, mModel, &SettingsModel::setMatchNormType);
  connect(mMatcher, &DescriptorMatcherWidget::ratioChange, mModel, &SettingsModel::setMatchRatio);
  connect(mMatcher, &DescriptorMatcherWidget::distanceChange, mModel, &SettingsModel::setMatchDistance);
  connect(mMatcher, &DescriptorMatcherWidget::confidenceChange, mModel, &SettingsModel::setMatchConfidence);
  connect(mMatcher, &DescriptorMatcherWidget::crossMatchingChange, mModel, &SettingsModel::setMatchCrossMatching);
  connect(mMatcher, &DescriptorMatcherWidget::maxItersChange, mModel, &SettingsModel::setMatchMaxIters);
  connect(mMatcher, &DescriptorMatcherWidget::geometricTestChange, mModel, &SettingsModel::setMatchGeometricTest);
  connect(mMatcher, &DescriptorMatcherWidget::homographyComputeMethodChange, mModel, &SettingsModel::setMatchHomographyComputeMethod);
  connect(mMatcher, &DescriptorMatcherWidget::fundamentalComputeMethodChange, mModel, &SettingsModel::setMatchFundamentalComputeMethod);
  connect(mMatcher, &DescriptorMatcherWidget::essentialComputeMethodChange, mModel, &SettingsModel::setMatchEssentialComputeMethod);

  /* Keypoints Viewer */
  connect(mView, &SettingsView::keypointsViewerBGColorChange, mModel, &SettingsModel::setKeypointsViewerBGColor);
  connect(mView, &SettingsView::keypointsViewerMarkerTypeChange, mModel, &SettingsModel::setKeypointsViewerMarkerType);
  connect(mView, &SettingsView::keypointsViewerMarkerSizeChange, mModel, &SettingsModel::setKeypointsViewerMarkerSize);
  connect(mView, &SettingsView::keypointsViewerMarkerWidthChange, mModel, &SettingsModel::setKeypointsViewerMarkerWidth);
  connect(mView, &SettingsView::keypointsViewerMarkerColorChange, mModel, &SettingsModel::setKeypointsViewerMarkerColor);
  connect(mView, &SettingsView::selectKeypointsViewerMarkerWidthChange, mModel, &SettingsModel::setKeypointsViewerSelectMarkerWidth);
  connect(mView, &SettingsView::selectKeypointsViewerMarkerColorChange, mModel, &SettingsModel::setKeypointsViewerSelectMarkerColor);

  /* Matches Viewer */
  connect(mView, &SettingsView::matchesViewerBGColorChange, mModel, &SettingsModel::setMatchesViewerBGColor);
  connect(mView, &SettingsView::matchesViewerMarkerTypeChange, mModel, &SettingsModel::setMatchesViewerMarkerType);
  connect(mView, &SettingsView::matchesViewerMarkerSizeChange, mModel, &SettingsModel::setMatchesViewerMarkerSize);
  connect(mView, &SettingsView::matchesViewerMarkerWidthChange, mModel, &SettingsModel::setMatchesViewerMarkerWidth);
  connect(mView, &SettingsView::matchesViewerMarkerColorChange, mModel, &SettingsModel::setMatchesViewerMarkerColor);
  connect(mView, &SettingsView::selectMatchesViewerMarkerWidthChange, mModel, &SettingsModel::setMatchesViewerSelectMarkerWidth);
  connect(mView, &SettingsView::selectMatchesViewerMarkerColorChange, mModel, &SettingsModel::setMatchesViewerSelectMarkerColor);
  connect(mView, &SettingsView::matchesViewerLineWidthChange, mModel, &SettingsModel::setMatchesViewerLineWidth);
  connect(mView, &SettingsView::matchesViewerLineColorChange, mModel, &SettingsModel::setMatchesViewerLineColor);

  /* Ground Truth Editor */
  connect(mView, &SettingsView::groundTruthEditorBGColorChange, mModel, &SettingsModel::setGroundTruthEditorBGColor);
  connect(mView, &SettingsView::groundTruthEditorMarkerSizeChange, mModel, &SettingsModel::setGroundTruthEditorMarkerSize);
  connect(mView, &SettingsView::groundTruthEditorMarkerWidthChange, mModel, &SettingsModel::setGroundTruthEditorMarkerWidth);
  connect(mView, &SettingsView::groundTruthEditorMarkerColorChange, mModel, &SettingsModel::setGroundTruthEditorMarkerColor);
  connect(mView, &SettingsView::selectGroundTruthEditorMarkerWidthChange, mModel, &SettingsModel::setGroundTruthEditorSelectMarkerWidth);
  connect(mView, &SettingsView::selectGroundTruthEditorMarkerColorChange, mModel, &SettingsModel::setGroundTruthEditorSelectMarkerColor);
  connect(mView, &SettingsView::groundTruthEditorMatrixAdjustChange, mModel, &SettingsModel::setGroundTruthEditorMatrixAdjust);

  connect(mView, &QDialog::accepted,          this, &SettingsPresenterImp::save);
  connect(mView, &SettingsView::applyChanges, this, &SettingsPresenterImp::save);
  connect(mView, &QDialog::rejected,          this, &SettingsPresenterImp::discart);
  connect(mView, &PhotoMatchDialogView::help, this, &SettingsPresenterImp::help);

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
