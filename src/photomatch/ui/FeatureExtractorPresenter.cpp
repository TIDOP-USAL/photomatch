#include "FeatureExtractorPresenter.h"

#include "photomatch/core/features/features.h"
#include "photomatch/core/features/agast.h"
#include "photomatch/core/features/akaze.h"
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
#include "photomatch/core/features/boost.h"
#endif
#include "photomatch/core/features/brief.h"
#include "photomatch/core/features/brisk.h"
#include "photomatch/core/features/daisy.h"
#include "photomatch/core/features/fast.h"
#include "photomatch/core/features/freak.h"
#include "photomatch/core/features/gftt.h"
#include "photomatch/core/features/hog.h"
#include "photomatch/core/features/latch.h"
#include "photomatch/core/features/lucid.h"
#include "photomatch/core/features/lss.h"
#include "photomatch/core/features/msd.h"
#include "photomatch/core/features/mser.h"
#include "photomatch/core/features/kaze.h"
#include "photomatch/core/features/orb.h"
#include "photomatch/core/features/sift.h"
#include "photomatch/core/features/star.h"
#include "photomatch/core/features/surf.h"
#include "photomatch/core/features/vgg.h"
#include "photomatch/core/preprocess/decolor.h"

#include "photomatch/ui/FeatureExtractorModel.h"
#include "photomatch/ui/FeatureExtractorView.h"
#include "photomatch/ui/ProjectModel.h"
#include "photomatch/ui/SettingsModel.h"
#include "photomatch/ui/HelpDialog.h"
#include "photomatch/ui/utils/Progress.h"

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
#include "photomatch/widgets/LssWidget.h"
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
#include "photomatch/widgets/KeypointsFilterWidget.h"

#include "photomatch/process/MultiProcess.h"
#include "photomatch/process/features/FeatureExtractorProcess.h"
#include "photomatch/process/preprocess/ImagePreprocess.h"

#include <tidop/core/messages.h>

#include <QFileInfo>
#include <QDir>
#include <QImageReader>
#include <QMessageBox>

namespace photomatch
{

FeatureExtractorPresenter::FeatureExtractorPresenter(IFeatureExtractorView *view,
                                                     IFeatureExtractorModel *model,
                                                     IProjectModel *projectModel,
                                                     ISettingsModel *settingsModel)
  : IFeatureExtractorPresenter(),
    mView(view),
    mModel(model),
    mProjectModel(projectModel),
    mSettingsModel(settingsModel),
    mHelp(nullptr),
    mAgastDetector(new AgastWidget),
    mAkazeDetector(new AkazeWidget),
    mBriskDetector(new BriskWidget),
    mFastDetector(new FastWidget),
    mGfttDetector(new GfttWidget),
    mKazeDetector(new KazeWidget),
    mMsdDetector(new MsdWidget),
    mMserDetector(new MserWidget),
    mOrbDetector(new OrbWidget),
#ifdef OPENCV_ENABLE_NONFREE
    mSiftDetector(new SiftWidget),
#endif
    mStarDetector(new StarWidget),
#ifdef OPENCV_ENABLE_NONFREE
    mSurfDetector(new SurfWidget),
#endif
    mAkazeDescriptor(new AkazeWidget),
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
    mBoostDescriptor(new BoostWidget),
#endif
    mBriefDescriptor(new BriefWidget),
    mBriskDescriptor(new BriskWidget),
    mDaisyDescriptor(new DaisyWidget),
    mFreakDescriptor(new FreakWidget),
    mHogDescriptor(new HogWidget),
    mKazeDescriptor(new KazeWidget),
    mLatchDescriptor(new LatchWidget),
    //mLucidDescriptor(new LucidWidget),
    mLssDescriptor(new LssWidget),
    mOrbDescriptor(new OrbWidget),
#ifdef OPENCV_ENABLE_NONFREE
    mSiftDescriptor(new SiftWidget),
    mSurfDescriptor(new SurfWidget),
#endif
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
    mVggDescriptor(new VggWidget),
#endif
    mKeypointsFilterWidget(new KeypointsFilterWidget),
    mMultiProcess(new MultiProcess(true)),
    mProgressHandler(nullptr)
{
  init();

  connect(mView, SIGNAL(keypointDetectorChange(QString)),      this, SLOT(setCurrentkeypointDetector(QString)));
  connect(mView, SIGNAL(descriptorExtractorChange(QString)),   this, SLOT(setCurrentDescriptorExtractor(QString)));

  connect(mView, SIGNAL(run()),                                this, SLOT(run()));
  connect(mView, SIGNAL(help()),                               this, SLOT(help()));

}

FeatureExtractorPresenter::~FeatureExtractorPresenter()
{
  if (mAgastDetector){
    delete mAgastDetector;
    mAgastDetector = nullptr;
  }

  if (mAkazeDetector){
    delete mAkazeDetector;
    mAkazeDetector = nullptr;
  }

  if (mBriskDetector){
    delete mBriskDetector;
    mBriskDetector = nullptr;
  }

  if (mFastDetector){
    delete mFastDetector;
    mFastDetector = nullptr;
  }

  if (mGfttDetector){
    delete mGfttDetector;
    mGfttDetector = nullptr;
  }

  if (mKazeDetector){
    delete mKazeDetector;
    mKazeDetector = nullptr;
  }

  if (mMsdDetector){
    delete mMsdDetector;
    mMsdDetector = nullptr;
  }

  if (mMserDetector){
    delete mMserDetector;
    mMserDetector = nullptr;
  }

  if (mOrbDetector){
    delete mOrbDetector;
    mOrbDetector = nullptr;
  }

#ifdef OPENCV_ENABLE_NONFREE
  if (mSiftDetector){
    delete mSiftDetector;
    mSiftDetector = nullptr;
  }
#endif

  if (mStarDetector){
    delete mStarDetector;
    mStarDetector = nullptr;
  }

#ifdef OPENCV_ENABLE_NONFREE
  if (mSurfDetector){
    delete mSurfDetector;
    mSurfDetector = nullptr;
  }
#endif

  if (mAkazeDescriptor){
    delete mAkazeDescriptor;
    mAkazeDescriptor = nullptr;
  }

#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  if (mBoostDescriptor){
    delete mBoostDescriptor;
    mBoostDescriptor = nullptr;
  }
#endif

  if (mBriefDescriptor){
    delete mBriefDescriptor;
    mBriefDescriptor = nullptr;
  }

  if (mBriskDescriptor){
    delete mBriskDescriptor;
    mBriskDescriptor = nullptr;
  }

  if (mDaisyDescriptor){
    delete mDaisyDescriptor;
    mDaisyDescriptor = nullptr;
  }

  if (mFreakDescriptor){
    delete mFreakDescriptor;
    mFreakDescriptor = nullptr;
  }

  if (mHogDescriptor){
    delete mHogDescriptor;
    mHogDescriptor = nullptr;
  }

  if (mKazeDescriptor){
    delete mKazeDescriptor;
    mKazeDescriptor = nullptr;
  }

  if (mLatchDescriptor){
    delete mLatchDescriptor;
    mLatchDescriptor = nullptr;
  }

//  if (mLucidDescriptor){
//    delete mLucidDescriptor;
//    mLucidDescriptor = nullptr;
//  }

  if (mLssDescriptor){
    delete mLssDescriptor;
    mLssDescriptor = nullptr;
  }

  if (mOrbDescriptor){
    delete mOrbDescriptor;
    mOrbDescriptor = nullptr;
  }

#ifdef OPENCV_ENABLE_NONFREE
  if (mSiftDescriptor){
    delete mSiftDescriptor;
    mSiftDescriptor = nullptr;
  }

  if (mSurfDescriptor){
    delete mSurfDescriptor;
    mSurfDescriptor = nullptr;
  }
#endif

#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  if (mVggDescriptor){
    delete mVggDescriptor;
    mVggDescriptor = nullptr;
  }
#endif

  if (mKeypointsFilterWidget){
    delete mKeypointsFilterWidget;
    mKeypointsFilterWidget = nullptr;
  }

  if (mMultiProcess){
    delete mMultiProcess;
    mMultiProcess = nullptr;
  }
}

void FeatureExtractorPresenter::help()
{
  if (mHelp){
    mHelp->setPage("feature_extraction.html");
    mHelp->show();
  }
}

void FeatureExtractorPresenter::open()
{
  std::shared_ptr<Session> current_session = mProjectModel->currentSession();
  if (current_session == nullptr) {
    msgError("No active session found");
    return;
  }

  Feature *detector = current_session->detector().get();
  Feature *descriptor = current_session->descriptor().get();
  if (detector) setCurrentkeypointDetector(detector->name());
  if (descriptor) setCurrentDescriptorExtractor(descriptor->name());

  /* AGAST */

  mAgastDetector->setThreshold(detector && detector->type() == Feature::Type::agast ?
                                 dynamic_cast<IAgast *>(detector)->threshold() :
                                 mSettingsModel->agastThreshold());
  mAgastDetector->setDetectorType(detector && detector->type() == Feature::Type::agast ?
                                    dynamic_cast<IAgast *>(detector)->detectorType() :
                                    mSettingsModel->agastDetectorType());
  mAgastDetector->setNonmaxSuppression(detector && detector->type() == Feature::Type::agast ?
                                         dynamic_cast<IAgast *>(detector)->nonmaxSuppression() :
                                         mSettingsModel->agastNonmaxSuppression());

  /* AKAZE */

  mAkazeDetector->setOctaves(detector && detector->type() == Feature::Type::akaze ?
                               dynamic_cast<IAkaze *>(detector)->octaves() :
                               mSettingsModel->akazeOctaves());
  mAkazeDetector->setThreshold(detector && detector->type() == Feature::Type::akaze ?
                               dynamic_cast<IAkaze *>(detector)->threshold() :
                               mSettingsModel->akazeThreshold());
  mAkazeDetector->setDiffusivity(detector && detector->type() == Feature::Type::akaze ?
                                 dynamic_cast<IAkaze *>(detector)->diffusivity() :
                                 mSettingsModel->akazeDiffusivity());
  mAkazeDetector->setOctaveLayers(detector && detector->type() == Feature::Type::akaze ?
                                  dynamic_cast<IAkaze *>(detector)->octaveLayers() :
                                  mSettingsModel->akazeOctaveLayers());
  mAkazeDetector->setDescriptorSize(detector && detector->type() == Feature::Type::akaze ?
                                    dynamic_cast<IAkaze *>(detector)->descriptorSize() :
                                    mSettingsModel->akazeDescriptorSize());
  mAkazeDetector->setDescriptorType(detector && detector->type() == Feature::Type::akaze ?
                                    dynamic_cast<IAkaze *>(detector)->descriptorType() :
                                    mSettingsModel->akazeDescriptorType());
  mAkazeDetector->setDescriptorChannels(detector && detector->type() == Feature::Type::akaze ?
                                        dynamic_cast<IAkaze *>(detector)->descriptorChannels() :
                                        mSettingsModel->akazeDescriptorChannels());
  mAkazeDescriptor->setOctaves(descriptor && descriptor->type() == Feature::Type::akaze ?
                               dynamic_cast<IAkaze *>(descriptor)->octaves() :
                               mSettingsModel->akazeOctaves());
  mAkazeDescriptor->setThreshold(descriptor && descriptor->type() == Feature::Type::akaze ?
                                 dynamic_cast<IAkaze *>(descriptor)->threshold() :
                                 mSettingsModel->akazeThreshold());
  mAkazeDescriptor->setDiffusivity(descriptor && descriptor->type() == Feature::Type::akaze ?
                                   dynamic_cast<IAkaze *>(descriptor)->diffusivity() :
                                   mSettingsModel->akazeDiffusivity());
  mAkazeDescriptor->setOctaveLayers(descriptor && descriptor->type() == Feature::Type::akaze ?
                                    dynamic_cast<IAkaze *>(descriptor)->octaveLayers() :
                                    mSettingsModel->akazeOctaveLayers());
  mAkazeDescriptor->setDescriptorSize(descriptor && descriptor->type() == Feature::Type::akaze ?
                                      dynamic_cast<IAkaze *>(descriptor)->descriptorSize() :
                                      mSettingsModel->akazeDescriptorSize());
  mAkazeDescriptor->setDescriptorType(descriptor && descriptor->type() == Feature::Type::akaze ?
                                      dynamic_cast<IAkaze *>(descriptor)->descriptorType() :
                                      mSettingsModel->akazeDescriptorType());
  mAkazeDescriptor->setDescriptorChannels(descriptor && descriptor->type() == Feature::Type::akaze ?
                                          dynamic_cast<IAkaze *>(descriptor)->descriptorChannels() :
                                          mSettingsModel->akazeDescriptorChannels());

  /* Boost */

#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  mBoostDescriptor->setDescriptorType(descriptor && descriptor->type() == Feature::Type::boost ?
                                        dynamic_cast<IBoost *>(descriptor)->descriptorType() :
                                        mSettingsModel->boostDescriptorType());
  mBoostDescriptor->setUseOrientation(descriptor && descriptor->type() == Feature::Type::boost ?
                                        dynamic_cast<IBoost *>(descriptor)->useOrientation() :
                                        mSettingsModel->boostUseOrientation());

  mBoostDescriptor->setScaleFactor(descriptor && descriptor->type() == Feature::Type::boost ?
                                     dynamic_cast<IBoost *>(descriptor)->scaleFactor() :
                                     mSettingsModel->boostScaleFactor());
#endif

  /* BRIEF */

  mBriefDescriptor->setBytes(descriptor && descriptor->type() == Feature::Type::brief ?
                               dynamic_cast<IBrief *>(descriptor)->bytes() :
                               mSettingsModel->briefBytes());
  mBriefDescriptor->setUseOrientation(descriptor && descriptor->type() == Feature::Type::brief ?
                                        dynamic_cast<IBrief *>(descriptor)->useOrientation() :
                                        mSettingsModel->briefUseOrientation());

  /* BRISK */

  mBriskDetector->setThreshold(detector && detector->type() == Feature::Type::brisk ?
                                 dynamic_cast<IBrisk *>(detector)->threshold() :
                                 mSettingsModel->briskThreshold());
  mBriskDetector->setOctaves(detector && detector->type() == Feature::Type::brisk ?
                               dynamic_cast<IBrisk *>(detector)->octaves() :
                               mSettingsModel->briskOctaves());
  mBriskDetector->setPatternScale(detector && detector->type() == Feature::Type::brisk ?
                                    dynamic_cast<IBrisk *>(detector)->patternScale() :
                                    mSettingsModel->briskPatternScale());

  mBriskDescriptor->setThreshold(descriptor && descriptor->type() == Feature::Type::brisk ?
                                   dynamic_cast<IBrisk *>(descriptor)->threshold() :
                                   mSettingsModel->briskThreshold());
  mBriskDescriptor->setOctaves(descriptor && descriptor->type() == Feature::Type::brisk ?
                                 dynamic_cast<IBrisk *>(descriptor)->threshold() :
                                 mSettingsModel->briskOctaves());
  mBriskDescriptor->setPatternScale(descriptor && descriptor->type() == Feature::Type::brisk ?
                                      dynamic_cast<IBrisk *>(descriptor)->patternScale() :
                                      mSettingsModel->briskPatternScale());

  /* DAISY */

  mDaisyDescriptor->setRadius(descriptor && descriptor->type() == Feature::Type::daisy ?
                                dynamic_cast<IDaisy *>(descriptor)->radius() :
                                mSettingsModel->daisyRadius());
  mDaisyDescriptor->setQRadius(descriptor && descriptor->type() == Feature::Type::daisy ?
                                 dynamic_cast<IDaisy *>(descriptor)->qRadius() :
                                 mSettingsModel->daisyQRadius());
  mDaisyDescriptor->setQTheta(descriptor && descriptor->type() == Feature::Type::daisy ?
                                dynamic_cast<IDaisy *>(descriptor)->qTheta() :
                                mSettingsModel->daisyQTheta());
  mDaisyDescriptor->setQHist(descriptor && descriptor->type() == Feature::Type::daisy ?
                               dynamic_cast<IDaisy *>(descriptor)->qHist() :
                               mSettingsModel->daisyQHist());
  mDaisyDescriptor->setNorm(descriptor && descriptor->type() == Feature::Type::daisy ?
                              dynamic_cast<IDaisy *>(descriptor)->norm() :
                              mSettingsModel->daisyNorm());
  mDaisyDescriptor->setInterpolation(descriptor && descriptor->type() == Feature::Type::daisy ?
                                       dynamic_cast<IDaisy *>(descriptor)->interpolation() :
                                       mSettingsModel->daisyInterpolation());
  mDaisyDescriptor->setUseOrientation(descriptor && descriptor->type() == Feature::Type::daisy ?
                                        dynamic_cast<IDaisy *>(descriptor)->useOrientation() :
                                        mSettingsModel->daisyUseOrientation());

  /* FAST */

  mFastDetector->setThreshold(detector && detector->type() == Feature::Type::fast ?
                                dynamic_cast<IFast *>(detector)->threshold() :
                                mSettingsModel->fastThreshold());
  mFastDetector->setNonmaxSuppression(detector && detector->type() == Feature::Type::fast ?
                                        dynamic_cast<IFast *>(detector)->nonmaxSuppression() :
                                        mSettingsModel->fastNonmaxSuppression());
  mFastDetector->setDetectorType(detector && detector->type() == Feature::Type::fast ?
                                   dynamic_cast<IFast *>(detector)->detectorType() :
                                   mSettingsModel->fastdetectorType());

  /* FREAK */

  mFreakDescriptor->setOrientationNormalized(descriptor && descriptor->type() == Feature::Type::freak ?
                                               dynamic_cast<IFreak *>(descriptor)->orientationNormalized() :
                                               mSettingsModel->freakOrientationNormalized());
  mFreakDescriptor->setScaleNormalized(descriptor && descriptor->type() == Feature::Type::freak ?
                                         dynamic_cast<IFreak *>(descriptor)->scaleNormalized() :
                                         mSettingsModel->freakScaleNormalized());
  mFreakDescriptor->setPatternScale(descriptor && descriptor->type() == Feature::Type::freak ?
                                      dynamic_cast<IFreak *>(descriptor)->patternScale() :
                                      mSettingsModel->freakPatternScale());
  mFreakDescriptor->setOctaves(descriptor && descriptor->type() == Feature::Type::freak ?
                                 dynamic_cast<IFreak *>(descriptor)->octaves() :
                                 mSettingsModel->freakOctaves());

  /* GFTT */

  mGfttDetector->setMaxFeatures(detector && detector->type() == Feature::Type::gftt ?
                                  dynamic_cast<IGftt *>(detector)->maxFeatures() :
                                  mSettingsModel->gfttMaxFeatures());
  mGfttDetector->setQualityLevel(detector && detector->type() == Feature::Type::gftt ?
                                   dynamic_cast<IGftt *>(detector)->qualityLevel() :
                                   mSettingsModel->gfttQualityLevel());
  mGfttDetector->setMinDistance(detector && detector->type() == Feature::Type::gftt ?
                                  dynamic_cast<IGftt *>(detector)->minDistance() :
                                  mSettingsModel->gfttMinDistance());
  mGfttDetector->setBlockSize(detector && detector->type() == Feature::Type::gftt ?
                                dynamic_cast<IGftt *>(detector)->blockSize() :
                                mSettingsModel->gfttBlockSize());
  mGfttDetector->setHarrisDetector(detector && detector->type() == Feature::Type::gftt ?
                                     dynamic_cast<IGftt *>(detector)->harrisDetector() :
                                     mSettingsModel->gfttHarrisDetector());
  mGfttDetector->setK(detector && detector->type() == Feature::Type::gftt ?
                        dynamic_cast<IGftt *>(detector)->k() :
                        mSettingsModel->gfttK());

  /* HOG */

  mHogDescriptor->setWinSize(descriptor && descriptor->type() == Feature::Type::hog ?
                               dynamic_cast<IHog *>(descriptor)->winSize() :
                               mSettingsModel->hogWinSize());
  mHogDescriptor->setBlockSize(descriptor && descriptor->type() == Feature::Type::hog ?
                                 dynamic_cast<IHog *>(descriptor)->blockSize() :
                                 mSettingsModel->hogBlockSize());
  mHogDescriptor->setBlockStride(descriptor && descriptor->type() == Feature::Type::hog ?
                                   dynamic_cast<IHog *>(descriptor)->blockStride() :
                                   mSettingsModel->hogBlockStride());
  mHogDescriptor->setCellSize(descriptor && descriptor->type() == Feature::Type::hog ?
                                dynamic_cast<IHog *>(descriptor)->cellSize() :
                                mSettingsModel->hogCellSize());
  mHogDescriptor->setNbins(descriptor && descriptor->type() == Feature::Type::hog ?
                             dynamic_cast<IHog *>(descriptor)->nbins() :
                             mSettingsModel->hogNbins());
  mHogDescriptor->setDerivAperture(descriptor && descriptor->type() == Feature::Type::hog ?
                                     dynamic_cast<IHog *>(descriptor)->derivAperture() :
                                     mSettingsModel->hogDerivAperture());

  /* KAZE */

  mKazeDetector->setExtendedDescriptor(detector && detector->type() == Feature::Type::kaze ?
                                         dynamic_cast<IKaze *>(detector)->extendedDescriptor() :
                                         mSettingsModel->kazeExtendedDescriptor());
  mKazeDetector->setUpright(detector && detector->type() == Feature::Type::kaze ?
                              dynamic_cast<IKaze *>(detector)->upright() :
                              mSettingsModel->kazeUpright());
  mKazeDetector->setThreshold(detector && detector->type() == Feature::Type::kaze ?
                                dynamic_cast<IKaze *>(detector)->threshold() :
                                mSettingsModel->kazeThreshold());
  mKazeDetector->setOctaves(detector && detector->type() == Feature::Type::kaze ?
                              dynamic_cast<IKaze *>(detector)->octaves() :
                              mSettingsModel->kazeOctaves());
  mKazeDetector->setOctaveLayers(detector && detector->type() == Feature::Type::kaze ?
                                   dynamic_cast<IKaze *>(detector)->octaveLayers() :
                                   mSettingsModel->kazeOctaveLayers());
  mKazeDetector->setDiffusivity(detector && detector->type() == Feature::Type::kaze ?
                                  dynamic_cast<IKaze *>(detector)->diffusivity() :
                                  mSettingsModel->kazeDiffusivity());

  mKazeDescriptor->setExtendedDescriptor(descriptor && descriptor->type() == Feature::Type::kaze ?
                                           dynamic_cast<IKaze *>(descriptor)->extendedDescriptor() :
                                           mSettingsModel->kazeExtendedDescriptor());
  mKazeDescriptor->setUpright(descriptor && descriptor->type() == Feature::Type::kaze ?
                                dynamic_cast<IKaze *>(descriptor)->upright() :
                                mSettingsModel->kazeUpright());
  mKazeDescriptor->setThreshold(descriptor && descriptor->type() == Feature::Type::kaze ?
                                  dynamic_cast<IKaze *>(descriptor)->threshold() :
                                  mSettingsModel->kazeThreshold());
  mKazeDescriptor->setOctaves(descriptor && descriptor->type() == Feature::Type::kaze ?
                                dynamic_cast<IKaze *>(descriptor)->octaves() :
                                mSettingsModel->kazeOctaves());
  mKazeDescriptor->setOctaveLayers(descriptor && descriptor->type() == Feature::Type::kaze ?
                                     dynamic_cast<IKaze *>(descriptor)->octaveLayers() :
                                     mSettingsModel->kazeOctaveLayers());
  mKazeDescriptor->setDiffusivity(descriptor && descriptor->type() == Feature::Type::kaze ?
                                    dynamic_cast<IKaze *>(descriptor)->diffusivity() :
                                    mSettingsModel->kazeDiffusivity());

  /* LATCH */

  mLatchDescriptor->setBytes(descriptor && descriptor->type() == Feature::Type::latch ?
                               dynamic_cast<ILatch *>(descriptor)->bytes() :
                               mSettingsModel->latchBytes());
  mLatchDescriptor->setRotationInvariance(descriptor && descriptor->type() == Feature::Type::latch ?
                                            dynamic_cast<ILatch *>(descriptor)->rotationInvariance() :
                                            mSettingsModel->latchRotationInvariance());
  mLatchDescriptor->setHalfSsdSize(descriptor && descriptor->type() == Feature::Type::latch ?
                                     dynamic_cast<ILatch *>(descriptor)->halfSsdSize() :
                                     mSettingsModel->latchHalfSsdSize());

//  /* LUCID */

//  mLucidDescriptor->setLucidKernel(descriptor && descriptor->type() == Feature::Type::lucid ?
//                                     dynamic_cast<ILucid *>(descriptor)->lucidKernel() :
//                                     mSettingsModel->lucidKernel());
//  mLucidDescriptor->setBlurKernel(descriptor && descriptor->type() == Feature::Type::lucid ?
//                                    dynamic_cast<ILucid *>(descriptor)->blurKernel() :
//                                    mSettingsModel->lucidBlurKernel());

  /* MSD */

  mMsdDetector->setThresholdSaliency(detector && detector->type() == Feature::Type::msd ?
                                       dynamic_cast<IMsd *>(detector)->thresholdSaliency() :
                                       mSettingsModel->msdThresholdSaliency());
  mMsdDetector->setPatchRadius(detector && detector->type() == Feature::Type::msd ?
                                dynamic_cast<IMsd *>(detector)->patchRadius() :
                                mSettingsModel->msdPathRadius());
  mMsdDetector->setKNN(detector && detector->type() == Feature::Type::msd ?
                         dynamic_cast<IMsd *>(detector)->knn() :
                         mSettingsModel->msdKnn());
  mMsdDetector->setAreaRadius(detector && detector->type() == Feature::Type::msd ?
                                dynamic_cast<IMsd *>(detector)->searchAreaRadius() :
                                mSettingsModel->msdAreaRadius());
  mMsdDetector->setScaleFactor(detector && detector->type() == Feature::Type::msd ?
                                 dynamic_cast<IMsd *>(detector)->scaleFactor() :
                                 mSettingsModel->msdScaleFactor());
  mMsdDetector->setNMSRadius(detector && detector->type() == Feature::Type::msd ?
                               dynamic_cast<IMsd *>(detector)->NMSRadius() :
                               mSettingsModel->msdNMSRadius());
  mMsdDetector->setNScales(detector && detector->type() == Feature::Type::msd ?
                             dynamic_cast<IMsd *>(detector)->nScales() :
                             mSettingsModel->msdNScales());
  mMsdDetector->setNMSScaleR(detector && detector->type() == Feature::Type::msd ?
                               dynamic_cast<IMsd *>(detector)->NMSScaleRadius() :
                               mSettingsModel->msdNMSScaleR());
  mMsdDetector->setComputeOrientations(detector && detector->type() == Feature::Type::msd ?
                                         dynamic_cast<IMsd *>(detector)->computeOrientation() :
                                         mSettingsModel->msdComputeOrientations());
  mMsdDetector->setAffineMSD(detector && detector->type() == Feature::Type::msd ?
                               dynamic_cast<IMsd *>(detector)->affineMSD() :
                               mSettingsModel->msdAffineMSD());
  mMsdDetector->setTilts(detector && detector->type() == Feature::Type::msd ?
                           dynamic_cast<IMsd *>(detector)->affineTilts() :
                           mSettingsModel->msdTilts());

  /* MSER */

  mMserDetector->setDelta(detector && detector->type() == Feature::Type::mser ?
                            dynamic_cast<IMser *>(detector)->delta() :
                            mSettingsModel->mserDelta());
  mMserDetector->setMaxArea(detector && detector->type() == Feature::Type::mser ?
                              dynamic_cast<IMser *>(detector)->maxArea() :
                              mSettingsModel->mserMaxArea());
  mMserDetector->setMinArea(detector && detector->type() == Feature::Type::mser ?
                              dynamic_cast<IMser *>(detector)->minArea() :
                              mSettingsModel->mserMinArea());
  mMserDetector->setMaxVariation(detector && detector->type() == Feature::Type::mser ?
                                   dynamic_cast<IMser *>(detector)->maxVariation() :
                                   mSettingsModel->mserMaxVariation());
  mMserDetector->setMinDiversity(detector && detector->type() == Feature::Type::mser ?
                                   dynamic_cast<IMser *>(detector)->minDiversity() :
                                   mSettingsModel->mserMinDiversity());
  mMserDetector->setMaxEvolution(detector && detector->type() == Feature::Type::mser ?
                                   dynamic_cast<IMser *>(detector)->maxEvolution() :
                                   mSettingsModel->mserMaxEvolution());
  mMserDetector->setAreaThreshold(detector && detector->type() == Feature::Type::mser ?
                                    dynamic_cast<IMser *>(detector)->areaThreshold() :
                                    mSettingsModel->mserAreaThreshold());
  mMserDetector->setMinMargin(detector && detector->type() == Feature::Type::mser ?
                                dynamic_cast<IMser *>(detector)->minMargin() :
                                mSettingsModel->mserMinMargin());
  mMserDetector->setEdgeBlurSize(detector && detector->type() == Feature::Type::mser ?
                                   dynamic_cast<IMser *>(detector)->edgeBlurSize() :
                                   mSettingsModel->mserEdgeBlurSize());

  /* ORB */

  mOrbDetector->setScaleFactor(detector && detector->type() == Feature::Type::orb ?
                                 dynamic_cast<IOrb *>(detector)->scaleFactor() :
                                 mSettingsModel->orbScaleFactor());
  mOrbDetector->setFeaturesNumber(detector && detector->type() == Feature::Type::orb ?
                                    dynamic_cast<IOrb *>(detector)->featuresNumber() :
                                    mSettingsModel->orbFeaturesNumber());
  mOrbDetector->setLevelsNumber(detector && detector->type() == Feature::Type::orb ?
                                  dynamic_cast<IOrb *>(detector)->levelsNumber() :
                                  mSettingsModel->orbLevelsNumber());
  mOrbDetector->setEdgeThreshold(detector && detector->type() == Feature::Type::orb ?
                                   dynamic_cast<IOrb *>(detector)->edgeThreshold() :
                                   mSettingsModel->orbEdgeThreshold());
  mOrbDetector->setWTA_K(detector && detector->type() == Feature::Type::orb ?
                           dynamic_cast<IOrb *>(detector)->wta_k() :
                           mSettingsModel->orbWta_k());
  mOrbDetector->setScoreType(detector && detector->type() == Feature::Type::orb ?
                               dynamic_cast<IOrb *>(detector)->scoreType() :
                               mSettingsModel->orbScoreType());
  mOrbDetector->setPatchSize(detector && detector->type() == Feature::Type::orb ?
                               dynamic_cast<IOrb *>(detector)->patchSize() :
                               mSettingsModel->orbPatchSize());
  mOrbDetector->setFastThreshold(detector && detector->type() == Feature::Type::orb ?
                                   dynamic_cast<IOrb *>(detector)->fastThreshold() :
                                   mSettingsModel->orbFastThreshold());

  mOrbDescriptor->setScaleFactor(descriptor && descriptor->type() == Feature::Type::orb ?
                                   dynamic_cast<IOrb *>(descriptor)->scaleFactor() :
                                   mSettingsModel->orbScaleFactor());
  mOrbDescriptor->setFeaturesNumber(descriptor && descriptor->type() == Feature::Type::orb ?
                                      dynamic_cast<IOrb *>(descriptor)->featuresNumber() :
                                      mSettingsModel->orbFeaturesNumber());
  mOrbDescriptor->setLevelsNumber(descriptor && descriptor->type() == Feature::Type::orb ?
                                    dynamic_cast<IOrb *>(descriptor)->levelsNumber() :
                                    mSettingsModel->orbLevelsNumber());
  mOrbDescriptor->setEdgeThreshold(descriptor && descriptor->type() == Feature::Type::orb ?
                                     dynamic_cast<IOrb *>(descriptor)->edgeThreshold() :
                                     mSettingsModel->orbEdgeThreshold());
  mOrbDescriptor->setWTA_K(descriptor && descriptor->type() == Feature::Type::orb ?
                             dynamic_cast<IOrb *>(descriptor)->wta_k() :
                             mSettingsModel->orbWta_k());
  mOrbDescriptor->setScoreType(descriptor && descriptor->type() == Feature::Type::orb ?
                                 dynamic_cast<IOrb *>(descriptor)->scoreType() :
                                 mSettingsModel->orbScoreType());
  mOrbDescriptor->setPatchSize(descriptor && descriptor->type() == Feature::Type::orb ?
                                 dynamic_cast<IOrb *>(descriptor)->patchSize() :
                                 mSettingsModel->orbPatchSize());
  mOrbDescriptor->setFastThreshold(descriptor && descriptor->type() == Feature::Type::orb ?
                                     dynamic_cast<IOrb *>(descriptor)->fastThreshold() :
                                     mSettingsModel->orbFastThreshold());

  /* SIFT */
#ifdef OPENCV_ENABLE_NONFREE
  mSiftDetector->setSigma(detector && detector->type() == Feature::Type::sift ?
                            dynamic_cast<ISift *>(detector)->sigma() :
                            mSettingsModel->siftSigma());
  mSiftDetector->setOctaveLayers(detector && detector->type() == Feature::Type::sift ?
                                   dynamic_cast<ISift *>(detector)->octaveLayers() :
                                   mSettingsModel->siftOctaveLayers());
  mSiftDetector->setEdgeThreshold(detector && detector->type() == Feature::Type::sift ?
                                    dynamic_cast<ISift *>(detector)->edgeThreshold() :
                                    mSettingsModel->siftEdgeThreshold());
  mSiftDetector->setFeaturesNumber(detector && detector->type() == Feature::Type::sift ?
                                     dynamic_cast<ISift *>(detector)->featuresNumber() :
                                     mSettingsModel->siftFeaturesNumber());
  mSiftDetector->setContrastThreshold(detector && detector->type() == Feature::Type::sift ?
                                        dynamic_cast<ISift *>(detector)->contrastThreshold() :
                                        mSettingsModel->siftContrastThreshold());

  mSiftDescriptor->setSigma(descriptor && descriptor->type() == Feature::Type::sift ?
                              dynamic_cast<ISift *>(descriptor)->sigma() :
                              mSettingsModel->siftSigma());
  mSiftDescriptor->setOctaveLayers(descriptor && descriptor->type() == Feature::Type::sift ?
                                     dynamic_cast<ISift *>(descriptor)->octaveLayers() :
                                     mSettingsModel->siftOctaveLayers());
  mSiftDescriptor->setEdgeThreshold(descriptor && descriptor->type() == Feature::Type::sift ?
                                      dynamic_cast<ISift *>(descriptor)->edgeThreshold() :
                                      mSettingsModel->siftEdgeThreshold());
  mSiftDescriptor->setFeaturesNumber(descriptor && descriptor->type() == Feature::Type::sift ?
                                       dynamic_cast<ISift *>(descriptor)->featuresNumber() :
                                       mSettingsModel->siftFeaturesNumber());
  mSiftDescriptor->setContrastThreshold(descriptor && descriptor->type() == Feature::Type::sift ?
                                          dynamic_cast<ISift *>(descriptor)->contrastThreshold() :
                                          mSettingsModel->siftContrastThreshold());
#endif

  /* STAR */

  mStarDetector->setMaxSize(detector && detector->type() == Feature::Type::star ?
                              dynamic_cast<IStar *>(descriptor)->maxSize() :
                              mSettingsModel->starMaxSize());
  mStarDetector->setResponseThreshold(detector && detector->type() == Feature::Type::star ?
                                        dynamic_cast<IStar *>(descriptor)->responseThreshold() :
                                        mSettingsModel->starResponseThreshold());
  mStarDetector->setLineThresholdProjected(detector && detector->type() == Feature::Type::star ?
                                             dynamic_cast<IStar *>(descriptor)->lineThresholdProjected() :
                                             mSettingsModel->starLineThresholdProjected());
  mStarDetector->setLineThresholdBinarized(detector && detector->type() == Feature::Type::star ?
                                             dynamic_cast<IStar *>(descriptor)->lineThresholdBinarized() :
                                             mSettingsModel->starLineThresholdBinarized());
  mStarDetector->setSuppressNonmaxSize(detector && detector->type() == Feature::Type::star ?
                                         dynamic_cast<IStar *>(descriptor)->suppressNonmaxSize() :
                                         mSettingsModel->starSuppressNonmaxSize());

  /* SURF */
#ifdef OPENCV_ENABLE_NONFREE
  mSurfDetector->setOctaves(detector && detector->type() == Feature::Type::surf ?
                            dynamic_cast<ISurf *>(detector)->octaves() :
                            mSettingsModel->surfOctaves());
  mSurfDetector->setOctaveLayers(detector && detector->type() == Feature::Type::surf ?
                                 dynamic_cast<ISurf *>(detector)->octaveLayers() :
                                 mSettingsModel->surfOctaveLayers());
  mSurfDetector->seUpright(detector && detector->type() == Feature::Type::surf ?
                                    dynamic_cast<ISurf *>(detector)->upright() :
                                    mSettingsModel->surfRotatedFeatures());
  mSurfDetector->setHessianThreshold(detector && detector->type() == Feature::Type::surf ?
                                     dynamic_cast<ISurf *>(detector)->hessianThreshold() :
                                     mSettingsModel->surfHessianThreshold());
  mSurfDetector->setExtendedDescriptor(detector && detector->type() == Feature::Type::surf ?
                                       dynamic_cast<ISurf *>(detector)->extendedDescriptor() :
                                       mSettingsModel->surfExtendedDescriptor());

  mSurfDescriptor->setOctaves(descriptor && descriptor->type() == Feature::Type::surf ?
                              dynamic_cast<ISurf *>(descriptor)->octaves() :
                              mSettingsModel->surfOctaves());
  mSurfDescriptor->setOctaveLayers(descriptor && descriptor->type() == Feature::Type::surf ?
                                   dynamic_cast<ISurf *>(descriptor)->octaveLayers() :
                                   mSettingsModel->surfOctaveLayers());
  mSurfDescriptor->seUpright(descriptor && descriptor->type() == Feature::Type::surf ?
                                      dynamic_cast<ISurf *>(descriptor)->upright() :
                                      mSettingsModel->surfRotatedFeatures());
  mSurfDescriptor->setHessianThreshold(descriptor && descriptor->type() == Feature::Type::surf ?
                                       dynamic_cast<ISurf *>(descriptor)->hessianThreshold() :
                                       mSettingsModel->surfHessianThreshold());
  mSurfDescriptor->setExtendedDescriptor(descriptor && descriptor->type() == Feature::Type::surf ?
                                         dynamic_cast<ISurf *>(descriptor)->extendedDescriptor() :
                                         mSettingsModel->surfExtendedDescriptor());

#endif

  /* Vgg */

#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  mVggDescriptor->setDescriptorType(descriptor && descriptor->type() == Feature::Type::vgg ?
                                        dynamic_cast<IVgg *>(descriptor)->descriptorType() :
                                        mSettingsModel->vggDescriptorType());
  mVggDescriptor->setScaleFactor(descriptor && descriptor->type() == Feature::Type::vgg ?
                                     dynamic_cast<IVgg *>(descriptor)->scaleFactor() :
                                     mSettingsModel->vggScaleFactor());
  mVggDescriptor->setSigma(descriptor && descriptor->type() == Feature::Type::vgg ?
                                        dynamic_cast<IVgg *>(descriptor)->sigma() :
                                        mSettingsModel->vggSigma());
  mVggDescriptor->setUseNormalizeDescriptor(descriptor && descriptor->type() == Feature::Type::vgg ?
                                        dynamic_cast<IVgg *>(descriptor)->useNormalizeDescriptor() :
                                        mSettingsModel->vggUseNormalizeDescriptor());
  mVggDescriptor->setUseNormalizeImage(descriptor && descriptor->type() == Feature::Type::vgg ?
                                        dynamic_cast<IVgg *>(descriptor)->useNormalizeImage() :
                                        mSettingsModel->vggUseNormalizeImage());
  mVggDescriptor->setUseScaleOrientation(descriptor && descriptor->type() == Feature::Type::vgg ?
                                     dynamic_cast<IVgg *>(descriptor)->useScaleOrientation() :
                                     mSettingsModel->vggUseScaleOrientation());
#endif

  ///TODO: guardar en proyecto y configuración y recuperarlo desde aqui
  //mKeypointsFilterWidget->setNPoints();
  //mKeypointsFilterWidget->setMinSize();
  //mKeypointsFilterWidget->setMaxSize();

  mView->setSessionName(current_session->name());
  mView->exec();
}

void FeatureExtractorPresenter::setHelp(std::shared_ptr<HelpDialog> &help)
{
  mHelp = help;
}

void FeatureExtractorPresenter::init()
{
  mView->addKeypointDetector(mAgastDetector);
  mView->addKeypointDetector(mAkazeDetector);
  mView->addKeypointDetector(mBriskDetector);
  mView->addKeypointDetector(mFastDetector);
  mView->addKeypointDetector(mGfttDetector);
  mView->addKeypointDetector(mKazeDetector);
  mView->addKeypointDetector(mMsdDetector);
  mView->addKeypointDetector(mMserDetector);
  mView->addKeypointDetector(mOrbDetector);
#ifdef OPENCV_ENABLE_NONFREE
  mView->addKeypointDetector(mSiftDetector);
#endif
  mView->addKeypointDetector(mStarDetector);
#ifdef OPENCV_ENABLE_NONFREE
  mView->addKeypointDetector(mSurfDetector);
#endif

  mView->addDescriptorExtractor(mAkazeDescriptor);
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  mView->addDescriptorExtractor(mBoostDescriptor);
#endif
  mView->addDescriptorExtractor(mBriefDescriptor);
  mView->addDescriptorExtractor(mBriskDescriptor);
  mView->addDescriptorExtractor(mDaisyDescriptor);
  mView->addDescriptorExtractor(mFreakDescriptor);
  mView->addDescriptorExtractor(mHogDescriptor);
  mView->addDescriptorExtractor(mKazeDescriptor);
  mView->addDescriptorExtractor(mLatchDescriptor);
//  mView->addDescriptorExtractor(mLucidDescriptor);
  mView->addDescriptorExtractor(mLssDescriptor);
  mView->addDescriptorExtractor(mOrbDescriptor);
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  mView->addDescriptorExtractor(mVggDescriptor);
#endif
#ifdef OPENCV_ENABLE_NONFREE
  mView->addDescriptorExtractor(mSiftDescriptor);
  mView->addDescriptorExtractor(mSurfDescriptor);

  setCurrentkeypointDetector(mSiftDescriptor->windowTitle());
#else
  setCurrentkeypointDetector(mOrbDescriptor->windowTitle());
#endif

  mView->addKeypointsFilter(mKeypointsFilterWidget);
  
}

void FeatureExtractorPresenter::setProgressHandler(ProgressHandler *progressHandler)
{
  mProgressHandler = progressHandler;
}

void FeatureExtractorPresenter::cancel()
{
  mMultiProcess->stop();

  disconnect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
  disconnect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));

  if (mProgressHandler){
    mProgressHandler->setRange(0,1);
    mProgressHandler->setValue(1);
    mProgressHandler->onFinish();
    mProgressHandler->setDescription(tr("Processing has been canceled by the user"));

    disconnect(mMultiProcess, SIGNAL(finished()),                 mProgressHandler,    SLOT(onFinish()));
    disconnect(mMultiProcess, SIGNAL(statusChangedNext()),        mProgressHandler,    SLOT(onNextPosition()));
    disconnect(mMultiProcess, SIGNAL(error(int, QString)),        mProgressHandler,    SLOT(onFinish()));
  }

  emit finished();

  msgWarning("Processing has been canceled by the user");
}

void FeatureExtractorPresenter::run()
{
  std::shared_ptr<Session> current_session = mProjectModel->currentSession();
  if (current_session == nullptr) {
    msgError("No active session found");
    return;
  }

  std::shared_ptr<Preprocess> preprocess = current_session->preprocess();
  std::shared_ptr<ImageProcess> imageProcess;
  if (preprocess == nullptr){
    imageProcess = std::make_shared<DecolorPreprocess>();
    mProjectModel->setMaxImageSize(2000);
    mProjectModel->setPreprocess(std::dynamic_pointer_cast<Preprocess>(imageProcess));
  }

  Feature *detector = current_session->detector().get();
  Feature *descriptor = current_session->descriptor().get();
  if (detector && descriptor){
    int i_ret = QMessageBox(QMessageBox::Warning,
                            tr("Previous results"),
                            tr("The previous results will be overwritten. Do you wish to continue?"),
                            QMessageBox::Yes|QMessageBox::No).exec();
    if (i_ret == QMessageBox::No) {
      return;
    }
  }

  mMultiProcess->clearProcessList();

  QString currentKeypointDetector = mView->currentKeypointDetector();
  QString currentDescriptorExtractor = mView->currentDescriptorExtractor();
  std::shared_ptr<KeypointDetector> keypointDetector;
  std::shared_ptr<DescriptorExtractor> descriptorExtractor;


  if (currentKeypointDetector.compare("AGAST") == 0) {
    keypointDetector = std::make_shared<AgastDetector>(mAgastDetector->threshold(),
                                                       mAgastDetector->nonmaxSuppression(),
                                                       mAgastDetector->detectorType());
  } else if (currentKeypointDetector.compare("AKAZE") == 0){
    keypointDetector = std::make_shared<AkazeDetectorDescriptor>(mAkazeDetector->descriptorType(),
                                                                 mAkazeDetector->descriptorSize(),
                                                                 mAkazeDetector->descriptorChannels(),
                                                                 mAkazeDetector->threshold(),
                                                                 mAkazeDetector->octaves(),
                                                                 mAkazeDetector->octaveLayers(),
                                                                 mAkazeDetector->diffusivity());
  } else if (currentKeypointDetector.compare("BRISK") == 0){
    keypointDetector = std::make_shared<BriskDetectorDescriptor>(mBriskDetector->threshold(),
                                                                 mBriskDetector->octaves(),
                                                                 mBriskDetector->patternScale());
  } else if (currentKeypointDetector.compare("FAST") == 0){
    keypointDetector = std::make_shared<FastDetector>(mFastDetector->threshold(),
                                                      mFastDetector->nonmaxSuppression(),
                                                      mFastDetector->detectorType());
  } else if (currentKeypointDetector.compare("GFTT") == 0){
    keypointDetector = std::make_shared<GfttDetector>(mGfttDetector->maxFeatures(),
                                                      mGfttDetector->qualityLevel(),
                                                      mGfttDetector->minDistance(),
                                                      mGfttDetector->blockSize(),
                                                      mGfttDetector->harrisDetector(),
                                                      mGfttDetector->k());
  } else if (currentKeypointDetector.compare("KAZE") == 0){
    keypointDetector = std::make_shared<KazeDetectorDescriptor>(mKazeDetector->extendedDescriptor(),
                                                                mKazeDetector->upright(),
                                                                mKazeDetector->threshold(),
                                                                mKazeDetector->octaves(),
                                                                mKazeDetector->octaveLayers(),
                                                                mKazeDetector->diffusivity());
  } else if (currentKeypointDetector.compare("MSD") == 0){
    keypointDetector = std::make_shared<MsdDetector>(mMsdDetector->thresholdSaliency(),
                                                     mMsdDetector->pathRadius(),
                                                     mMsdDetector->knn(),
                                                     mMsdDetector->areaRadius(),
                                                     mMsdDetector->scaleFactor(),
                                                     mMsdDetector->NMSRadius(),
                                                     mMsdDetector->nScales(),
                                                     mMsdDetector->NMSScaleR(),
                                                     mMsdDetector->computeOrientations(),
                                                     mMsdDetector->affineMSD(),
                                                     mMsdDetector->tilts());
  } else if (currentKeypointDetector.compare("MSER") == 0){
    keypointDetector = std::make_shared<MserDetector>(mMserDetector->delta(),
                                                      mMserDetector->minArea(),
                                                      mMserDetector->maxArea(),
                                                      mMserDetector->maxVariation(),
                                                      mMserDetector->minDiversity(),
                                                      mMserDetector->maxEvolution(),
                                                      mMserDetector->areaThreshold(),
                                                      mMserDetector->minMargin(),
                                                      mMserDetector->edgeBlurSize());
  } else if (currentKeypointDetector.compare("ORB") == 0){
#ifdef HAVE_CUDA
    if (mSettingsModel->useCuda()){
      keypointDetector = std::make_shared<OrbCudaDetectorDescriptor>(mOrbDetector->featuresNumber(),
                                                                     mOrbDetector->scaleFactor(),
                                                                     mOrbDetector->levelsNumber(),
                                                                     mOrbDetector->edgeThreshold(),
                                                                     mOrbDetector->wta_k(),
                                                                     mOrbDetector->scoreType(),
                                                                     mOrbDetector->patchSize(),
                                                                     mOrbDetector->fastThreshold());
    } else {
#endif // HAVE_CUDA
      keypointDetector = std::make_shared<OrbDetectorDescriptor>(mOrbDetector->featuresNumber(),
                                                                 mOrbDetector->scaleFactor(),
                                                                 mOrbDetector->levelsNumber(),
                                                                 mOrbDetector->edgeThreshold(),
                                                                 mOrbDetector->wta_k(),
                                                                 mOrbDetector->scoreType(),
                                                                 mOrbDetector->patchSize(),
                                                                 mOrbDetector->fastThreshold());

#ifdef HAVE_CUDA
    }
#endif // HAVE_CUDA
  } 
#ifdef OPENCV_ENABLE_NONFREE
  else if (currentKeypointDetector.compare("SIFT") == 0){
    keypointDetector = std::make_shared<SiftDetectorDescriptor>(mSiftDetector->featuresNumber(),
                                                                mSiftDetector->octaveLayers(),
                                                                mSiftDetector->contrastThreshold(),
                                                                mSiftDetector->edgeThreshold(),
                                                                mSiftDetector->sigma());
  }
#endif
  else if (currentKeypointDetector.compare("STAR") == 0){
    keypointDetector = std::make_shared<StarDetector>(mStarDetector->maxSize(),
                                                      mStarDetector->responseThreshold(),
                                                      mStarDetector->lineThresholdProjected(),
                                                      mStarDetector->lineThresholdBinarized(),
                                                      mStarDetector->suppressNonmaxSize());
  } 
#ifdef OPENCV_ENABLE_NONFREE
  else if (currentKeypointDetector.compare("SURF") == 0){
#ifdef HAVE_CUDA
    if (mSettingsModel->useCuda()){
      keypointDetector = std::make_shared<SurfCudaDetectorDescriptor>(mSurfDetector->hessianThreshold(),
                                                                      mSurfDetector->octaves(),
                                                                      mSurfDetector->octaveLayers(),
                                                                      mSurfDetector->extendedDescriptor(),
                                                                      mSurfDetector->upright());
    } else {
#endif // HAVE_CUDA

    keypointDetector = std::make_shared<SurfDetectorDescriptor>(mSurfDetector->hessianThreshold(),
                                                                mSurfDetector->octaves(),
                                                                mSurfDetector->octaveLayers(),
                                                                mSurfDetector->extendedDescriptor(),
                                                                mSurfDetector->upright());
#ifdef HAVE_CUDA
    }
#endif // HAVE_CUDA
  } 
#endif
  else {
    ///TODO: error
    return;
  }


  if (currentDescriptorExtractor.compare("AKAZE") == 0){
    if (currentKeypointDetector.compare("AKAZE") == 0){
      descriptorExtractor = std::make_shared<AkazeDetectorDescriptor>(mAkazeDetector->descriptorType(),
                                                                      mAkazeDetector->descriptorSize(),
                                                                      mAkazeDetector->descriptorChannels(),
                                                                      mAkazeDetector->threshold(),
                                                                      mAkazeDetector->octaves(),
                                                                      mAkazeDetector->octaveLayers(),
                                                                      mAkazeDetector->diffusivity());
    } else {
      descriptorExtractor = std::make_shared<AkazeDetectorDescriptor>(mAkazeDescriptor->descriptorType(),
                                                                      mAkazeDescriptor->descriptorSize(),
                                                                      mAkazeDescriptor->descriptorChannels(),
                                                                      mAkazeDescriptor->threshold(),
                                                                      mAkazeDescriptor->octaves(),
                                                                      mAkazeDescriptor->octaveLayers(),
                                                                      mAkazeDescriptor->diffusivity());
    }
  }
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  else if (currentDescriptorExtractor.compare("BOOST") == 0){
    descriptorExtractor = std::make_shared<BoostDescriptor>(mBoostDescriptor->descriptorType(),
                                                            mBoostDescriptor->useOrientation(),
                                                            mBoostDescriptor->scaleFactor());
  }
#endif
  else if (currentDescriptorExtractor.compare("BRIEF") == 0){
    descriptorExtractor = std::make_shared<BriefDescriptor>(mBriefDescriptor->bytes(),
                                                            mBriefDescriptor->useOrientation());
  } else if (currentDescriptorExtractor.compare("BRISK") == 0){
    descriptorExtractor = std::make_shared<BriskDetectorDescriptor>(mBriskDescriptor->threshold(),
                                                                    mBriskDescriptor->octaves(),
                                                                    mBriskDescriptor->patternScale());
  } else if (currentDescriptorExtractor.compare("DAISY") == 0){
    descriptorExtractor = std::make_shared<DaisyDescriptor>(mDaisyDescriptor->radius(),
                                                            mDaisyDescriptor->qRadius(),
                                                            mDaisyDescriptor->qTheta(),
                                                            mDaisyDescriptor->qHist(),
                                                            mDaisyDescriptor->norm(),
                                                            mDaisyDescriptor->interpolation(),
                                                            mDaisyDescriptor->useOrientation());
  } else if (currentDescriptorExtractor.compare("FREAK") == 0){
    descriptorExtractor = std::make_shared<FreakDescriptor>(mFreakDescriptor->orientationNormalized(),
                                                            mFreakDescriptor->scaleNormalized(),
                                                            mFreakDescriptor->patternScale(),
                                                            mFreakDescriptor->octaves());
  } else if (currentDescriptorExtractor.compare("HOG") == 0){
    descriptorExtractor = std::make_shared<HogDescriptor>(mHogDescriptor->winSize(),
                                                          mHogDescriptor->blockSize(),
                                                          mHogDescriptor->blockStride(),
                                                          mHogDescriptor->cellSize(),
                                                          mHogDescriptor->nbins(),
                                                          mHogDescriptor->derivAperture());
  } else if (currentDescriptorExtractor.compare("KAZE") == 0){
    if (currentKeypointDetector.compare("KAZE") == 0){
      descriptorExtractor = std::make_shared<KazeDetectorDescriptor>(mKazeDetector->extendedDescriptor(),
                                                                     mKazeDetector->upright(),
                                                                     mKazeDetector->threshold(),
                                                                     mKazeDetector->octaves(),
                                                                     mKazeDetector->octaveLayers(),
                                                                     mKazeDetector->diffusivity());
    } else {
      descriptorExtractor = std::make_shared<KazeDetectorDescriptor>(mKazeDescriptor->extendedDescriptor(),
                                                                     mKazeDescriptor->upright(),
                                                                     mKazeDescriptor->threshold(),
                                                                     mKazeDescriptor->octaves(),
                                                                     mKazeDescriptor->octaveLayers(),
                                                                     mKazeDescriptor->diffusivity());
    }
  } else if (currentDescriptorExtractor.compare("LATCH") == 0){
    descriptorExtractor = std::make_shared<LatchDescriptor>(mLatchDescriptor->bytes(),
                                                            mLatchDescriptor->rotationInvariance(),
                                                            mLatchDescriptor->halfSsdSize());
  } /* else if (currentDescriptorExtractor.compare("LUCID") == 0){
    descriptorExtractor = std::make_shared<LucidDescriptor>(mLucidDescriptor->lucidKernel(),
                                                            mLucidDescriptor->blurKernel());
  }*/ else if (currentDescriptorExtractor.compare("LSS") == 0){
    descriptorExtractor = std::make_shared<LssDescriptor>();
  } else if (currentDescriptorExtractor.compare("ORB") == 0){
#ifdef HAVE_CUDA
    if (mSettingsModel->useCuda()){
      if (currentKeypointDetector.compare("ORB") == 0){
        descriptorExtractor = std::make_shared<OrbCudaDetectorDescriptor>(mOrbDetector->featuresNumber(),
                                                                          mOrbDetector->scaleFactor(),
                                                                          mOrbDetector->levelsNumber(),
                                                                          mOrbDetector->edgeThreshold(),
                                                                          mOrbDetector->wta_k(),
                                                                          mOrbDetector->scoreType(),
                                                                          mOrbDetector->patchSize(),
                                                                          mOrbDetector->fastThreshold());
      } else {
        descriptorExtractor = std::make_shared<OrbCudaDetectorDescriptor>(mOrbDescriptor->featuresNumber(),
                                                                          mOrbDescriptor->scaleFactor(),
                                                                          mOrbDescriptor->levelsNumber(),
                                                                          mOrbDescriptor->edgeThreshold(),
                                                                          mOrbDescriptor->wta_k(),
                                                                          mOrbDescriptor->scoreType(),
                                                                          mOrbDescriptor->patchSize(),
                                                                          mOrbDescriptor->fastThreshold());
      }
    } else {
#endif // HAVE_CUDA
      if (currentKeypointDetector.compare("ORB") == 0){
        descriptorExtractor = std::make_shared<OrbDetectorDescriptor>(mOrbDetector->featuresNumber(),
                                                                      mOrbDetector->scaleFactor(),
                                                                      mOrbDetector->levelsNumber(),
                                                                      mOrbDetector->edgeThreshold(),
                                                                      mOrbDetector->wta_k(),
                                                                      mOrbDetector->scoreType(),
                                                                      mOrbDetector->patchSize(),
                                                                      mOrbDetector->fastThreshold());
      } else {
        descriptorExtractor = std::make_shared<OrbDetectorDescriptor>(mOrbDescriptor->featuresNumber(),
                                                                      mOrbDescriptor->scaleFactor(),
                                                                      mOrbDescriptor->levelsNumber(),
                                                                      mOrbDescriptor->edgeThreshold(),
                                                                      mOrbDescriptor->wta_k(),
                                                                      mOrbDescriptor->scoreType(),
                                                                      mOrbDescriptor->patchSize(),
                                                                      mOrbDescriptor->fastThreshold());
      }
#ifdef HAVE_CUDA
    }
#endif // HAVE_CUDA
  } 
#ifdef OPENCV_ENABLE_NONFREE
  else if (currentDescriptorExtractor.compare("SIFT") == 0){
    if (currentKeypointDetector.compare("SIFT") == 0){
      descriptorExtractor = std::make_shared<SiftDetectorDescriptor>(mSiftDetector->featuresNumber(),
                                                                  mSiftDetector->octaveLayers(),
                                                                  mSiftDetector->contrastThreshold(),
                                                                  mSiftDetector->edgeThreshold(),
                                                                  mSiftDetector->sigma());
    } else {
      descriptorExtractor = std::make_shared<SiftDetectorDescriptor>(mSiftDescriptor->featuresNumber(),
                                                                     mSiftDescriptor->octaveLayers(),
                                                                     mSiftDescriptor->contrastThreshold(),
                                                                     mSiftDescriptor->edgeThreshold(),
                                                                     mSiftDescriptor->sigma());
    }
  } else if (currentDescriptorExtractor.compare("SURF") == 0){
#ifdef HAVE_CUDA
    if (mSettingsModel->useCuda()){
      if (currentKeypointDetector.compare("SURF") == 0){
        descriptorExtractor = std::make_shared<SurfCudaDetectorDescriptor>(mSurfDetector->hessianThreshold(),
                                                                           mSurfDetector->octaves(),
                                                                           mSurfDetector->octaveLayers(),
                                                                           mSurfDetector->extendedDescriptor(),
                                                                           mSurfDetector->upright());
      } else {
        descriptorExtractor = std::make_shared<SurfCudaDetectorDescriptor>(mSurfDescriptor->hessianThreshold(),
                                                                           mSurfDescriptor->octaves(),
                                                                           mSurfDescriptor->octaveLayers(),
                                                                           mSurfDescriptor->extendedDescriptor(),
                                                                           mSurfDescriptor->upright());
      }
    } else {
#endif // HAVE_CUDA
      if (currentKeypointDetector.compare("SURF") == 0){
        descriptorExtractor = std::make_shared<SurfDetectorDescriptor>(mSurfDetector->hessianThreshold(),
                                                                       mSurfDetector->octaves(),
                                                                       mSurfDetector->octaveLayers(),
                                                                       mSurfDetector->extendedDescriptor(),
                                                                       mSurfDetector->upright());
      } else {
        descriptorExtractor = std::make_shared<SurfDetectorDescriptor>(mSurfDescriptor->hessianThreshold(),
                                                                       mSurfDescriptor->octaves(),
                                                                       mSurfDescriptor->octaveLayers(),
                                                                       mSurfDescriptor->extendedDescriptor(),
                                                                       mSurfDescriptor->upright());
      }
#ifdef HAVE_CUDA
    }
#endif // HAVE_CUDA
  } 
#endif
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  else if (currentDescriptorExtractor.compare("VGG") == 0){
    descriptorExtractor = std::make_shared<VggDescriptor>(mVggDescriptor->descriptorType(),
                                                          mVggDescriptor->scaleFactor(),
                                                          mVggDescriptor->sigma(),
                                                          mVggDescriptor->useNormalizeDescriptor(),
                                                          mVggDescriptor->useNormalizeImage(),
                                                          mVggDescriptor->useScaleOrientation());
  }
#endif
  else {
    ///TODO: error
    return;
  }

  mProjectModel->setDetector(std::dynamic_pointer_cast<Feature>(keypointDetector));
  mProjectModel->setDescriptor(std::dynamic_pointer_cast<Feature>(descriptorExtractor));


  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    QString fileName = (*it)->name();
    QString preprocessed_image;

    if (imageProcess){
      QString file_in = (*it)->path();
      QFileInfo fileInfo(file_in);
      preprocessed_image = mProjectModel->projectFolder();
      preprocessed_image.append("\\").append(mProjectModel->currentSession()->name());
      preprocessed_image.append("\\preprocess\\");
      QDir dir_out(preprocessed_image);
      if (!dir_out.exists()) {
        dir_out.mkpath(".");
      }
      preprocessed_image.append(fileInfo.fileName());
      std::shared_ptr<ImagePreprocess> preprocess(new ImagePreprocess((*it)->path(),
                                                                      preprocessed_image,
                                                                      imageProcess,
                                                                      2000));
      connect(preprocess.get(), SIGNAL(preprocessed(QString)), this, SLOT(onImagePreprocessed(QString)));
      mMultiProcess->appendProcess(preprocess);
    } else {
      preprocessed_image = mProjectModel->currentSession()->preprocessImage(fileName);
    }

    QString features = mProjectModel->projectFolder();
    features.append("\\").append(mProjectModel->currentSession()->name());
    features.append("\\features\\");
    QDir dir_out(features);
    if (!dir_out.exists()) {
      dir_out.mkpath(".");
    }
    features.append(fileName);
    QString keypointsFormat = mSettingsModel->keypointsFormat();
    if (keypointsFormat.compare("Binary") == 0){
      features.append(".bin");
    } else if (keypointsFormat.compare("YML") == 0){
      features.append(".yml");
    } else {
      features.append(".xml");
    }

    double scale = 1.;
    if (mProjectModel->fullImageSize() == false){
      int maxSize = mProjectModel->maxImageSize();
      QImageReader imageReader((*it)->path());
      QSize size = imageReader.size();
      int w = size.width();
      int h = size.height();
      if (w > h){
        scale = w / static_cast<double>(maxSize);
      } else {
        scale = h / static_cast<double>(maxSize);
      }
      if (scale < 1.) scale = 1.;
    }

    /// Se añade aqui porque se necesita la escala
    std::list<std::shared_ptr<KeyPointsFilterProcess>> keyPointsFiltersProcess;
    if (mKeypointsFilterWidget->isActiveFilterBest()){
      std::shared_ptr<KeyPointsFilterProcess> keyPointsFilterNBest = std::make_shared<KeyPointsFilterNBest>(mKeypointsFilterWidget->nPoints());
      keyPointsFiltersProcess.push_back(keyPointsFilterNBest);
    }
    if (mKeypointsFilterWidget->isActiveFilterSize()){
      std::shared_ptr<KeyPointsFilterProcess> keyPointsFilterBySize = std::make_shared<KeyPointsFilterBySize>(mKeypointsFilterWidget->minSize()/scale, 
                                                                                                              mKeypointsFilterWidget->maxSize()/scale);
      keyPointsFiltersProcess.push_back(keyPointsFilterBySize);
    }
    if (mKeypointsFilterWidget->isActiveRemoveDuplicated()){
      std::shared_ptr<KeyPointsFilterProcess> keyPointsFilterRemoveDuplicated = std::make_shared<KeyPointsFilterRemoveDuplicated>();
      keyPointsFiltersProcess.push_back(keyPointsFilterRemoveDuplicated);
    }

    std::shared_ptr<FeatureExtractor> feat_extract(new FeatureExtractor(preprocessed_image,
                                                                        features,
                                                                        scale,
                                                                        keypointDetector,
                                                                        descriptorExtractor,
                                                                        keyPointsFiltersProcess));
    connect(feat_extract.get(), SIGNAL(featuresExtracted(QString)), this, SLOT(onFeaturesExtracted(QString)));

    mMultiProcess->appendProcess(feat_extract);
  }

  connect(mMultiProcess, SIGNAL(error(int, QString)),          this, SLOT(onError(int, QString)));
  connect(mMultiProcess, SIGNAL(finished()),                   this, SLOT(onFinished()));

  if (mProgressHandler){
    connect(mMultiProcess, SIGNAL(finished()),             mProgressHandler,    SLOT(onFinish()));
    connect(mMultiProcess, SIGNAL(statusChangedNext()),    mProgressHandler,    SLOT(onNextPosition()));
    connect(mMultiProcess, SIGNAL(error(int, QString)),    mProgressHandler,    SLOT(onFinish()));

    mProgressHandler->setRange(0, mMultiProcess->count());
    mProgressHandler->setValue(0);
    mProgressHandler->setTitle("Computing Features...");
    mProgressHandler->setDescription("Computing Features...");
    mProgressHandler->onInit();
  }

  mView->hide();

  msgInfo("Starting Feature Extraction");
  QByteArray ba = currentKeypointDetector.toLocal8Bit();
  const char *keypoint_detector = ba.constData();
  msgInfo("  Feature Detector     :  %s", keypoint_detector);
  ba = currentDescriptorExtractor.toLocal8Bit();
  const char *descriptor_extractor = ba.constData();
  msgInfo("  DescriptorExtractor  :  %s", descriptor_extractor);

  emit running();

  mMultiProcess->start();
}

void FeatureExtractorPresenter::setCurrentkeypointDetector(const QString &keypointDetector)
{
  mView->setCurrentKeypointDetector(keypointDetector);

  mView->disableDescriptorExtractor("AKAZE");
  mView->disableDescriptorExtractor("KAZE");
  mView->enableDescriptorExtractor("ORB");
  mView->enableDescriptorExtractor("HOG");

  if (keypointDetector.compare("AGAST") == 0){
#ifdef OPENCV_ENABLE_NONFREE
    mView->setCurrentDescriptorExtractor("SIFT");
#else
    mView->setCurrentDescriptorExtractor("ORB");
#endif
  } else if (keypointDetector.compare("AKAZE") == 0){
    mView->setCurrentDescriptorExtractor("AKAZE");
    mView->enableDescriptorExtractor("AKAZE");
    mView->enableDescriptorExtractor("KAZE");
  } else if (keypointDetector.compare("BRISK") == 0){
    mView->setCurrentDescriptorExtractor("BRISK");
    mView->disableDescriptorExtractor("HOG");
  } else if (keypointDetector.compare("FAST") == 0){
#ifdef OPENCV_ENABLE_NONFREE
    mView->setCurrentDescriptorExtractor("SIFT");
#else
    mView->setCurrentDescriptorExtractor("ORB");
#endif
  } else if (keypointDetector.compare("GFTT") == 0){
#ifdef OPENCV_ENABLE_NONFREE
    mView->setCurrentDescriptorExtractor("SIFT");
#else
    mView->setCurrentDescriptorExtractor("ORB");
#endif
  } else if (keypointDetector.compare("KAZE") == 0){
    mView->setCurrentDescriptorExtractor("KAZE");
    mView->enableDescriptorExtractor("AKAZE");
    mView->enableDescriptorExtractor("KAZE");
  } else if (keypointDetector.compare("MSD") == 0){
#ifdef OPENCV_ENABLE_NONFREE
    mView->setCurrentDescriptorExtractor("SIFT");
#else
    mView->setCurrentDescriptorExtractor("ORB");
#endif
  } else if (keypointDetector.compare("MSER") == 0){
#ifdef OPENCV_ENABLE_NONFREE
    mView->setCurrentDescriptorExtractor("SIFT");
#else
    mView->setCurrentDescriptorExtractor("ORB");
#endif
  } else if (keypointDetector.compare("ORB") == 0){
    mView->setCurrentDescriptorExtractor("ORB");
  }
#ifdef OPENCV_ENABLE_NONFREE
  else if (keypointDetector.compare("SIFT") == 0){
    mView->setCurrentDescriptorExtractor("SIFT");
    mView->disableDescriptorExtractor("ORB");
  }
#endif
  else if (keypointDetector.compare("STAR") == 0){
#ifdef OPENCV_ENABLE_NONFREE
    mView->setCurrentDescriptorExtractor("SIFT");
#else
    mView->setCurrentDescriptorExtractor("ORB");
#endif
  }
#ifdef OPENCV_ENABLE_NONFREE
  else if (keypointDetector.compare("SURF") == 0){
    mView->setCurrentDescriptorExtractor("SURF");
  }
#endif
}

void FeatureExtractorPresenter::setCurrentDescriptorExtractor(const QString &descriptorExtractor)
{
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  if (descriptorExtractor.compare("BOOST") == 0 ||
      descriptorExtractor.compare("VGG") == 0){
    QString keypointDetector = mView->currentKeypointDetector();
    if (keypointDetector.compare("AGAST") == 0 ||
        keypointDetector.compare("AKAZE") == 0 ||
        keypointDetector.compare("BRISK") == 0 ||
        keypointDetector.compare("FAST") == 0 ||
        keypointDetector.compare("MSD") == 0){
      mBoostDescriptor->setScaleFactor(5.0);
    } else if (keypointDetector.compare("KAZE") == 0 ||
               keypointDetector.compare("SURF") == 0) {
      mBoostDescriptor->setScaleFactor(6.25);
    } else if (keypointDetector.compare("SIFT") == 0) {
     mBoostDescriptor->setScaleFactor(6.75);
   } else if (keypointDetector.compare("ORB") == 0) {
      mBoostDescriptor->setScaleFactor(1.50);
   }
  }
#endif
  mView->setCurrentDescriptorExtractor(descriptorExtractor);
}

void FeatureExtractorPresenter::onError(int code, const QString &msg)
{
  disconnect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
  disconnect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));

  if (mProgressHandler){
    mProgressHandler->setRange(0,1);
    mProgressHandler->setValue(1);
    mProgressHandler->onFinish();
    mProgressHandler->setDescription(tr("Feature detection and description error"));

    disconnect(mMultiProcess, SIGNAL(finished()),                 mProgressHandler,    SLOT(onFinish()));
    disconnect(mMultiProcess, SIGNAL(statusChangedNext()),        mProgressHandler,    SLOT(onNextPosition()));
    disconnect(mMultiProcess, SIGNAL(error(int, QString)),        mProgressHandler,    SLOT(onFinish()));
  }

  emit finished();
}

void FeatureExtractorPresenter::onFinished()
{
  disconnect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
  disconnect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));

  if (mProgressHandler){
    mProgressHandler->setRange(0,1);
    mProgressHandler->setValue(1);
    mProgressHandler->onFinish();
    mProgressHandler->setDescription(tr("Feature detection and description finished"));

    disconnect(mMultiProcess, SIGNAL(finished()),                 mProgressHandler,    SLOT(onFinish()));
    disconnect(mMultiProcess, SIGNAL(statusChangedNext()),        mProgressHandler,    SLOT(onNextPosition()));
    disconnect(mMultiProcess, SIGNAL(error(int, QString)),        mProgressHandler,    SLOT(onFinish()));
  }

  emit finished();

  msgInfo("Feature detection and description finished.");
}

void FeatureExtractorPresenter::onImagePreprocessed(const QString &image)
{
  mProjectModel->addPreprocessedImage(image);
  emit imagePreprocessed(image);
}

void FeatureExtractorPresenter::onFeaturesExtracted(const QString &features)
{
  mProjectModel->addFeatures(features);
  emit featuresExtracted(features);
}

} // namespace photomatch
