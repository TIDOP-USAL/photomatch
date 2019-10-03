#include "FeatureExtractorPresenter.h"

#include "fme/core/features/features.h"
#include "fme/core/features/agast.h"
#include "fme/core/features/akaze.h"
#include "fme/core/features/brief.h"
#include "fme/core/features/brisk.h"
#include "fme/core/features/daisy.h"
#include "fme/core/features/fast.h"
#include "fme/core/features/freak.h"
#include "fme/core/features/gftt.h"
#include "fme/core/features/hog.h"
#include "fme/core/features/latch.h"
#include "fme/core/features/lucid.h"
#include "fme/core/features/lss.h"
#include "fme/core/features/msd.h"
#include "fme/core/features/mser.h"
#include "fme/core/features/kaze.h"
#include "fme/core/features/orb.h"
#include "fme/core/features/sift.h"
#include "fme/core/features/star.h"
#include "fme/core/features/surf.h"

#include "fme/ui/FeatureExtractorModel.h"
#include "fme/ui/FeatureExtractorView.h"
#include "fme/ui/ProjectModel.h"
#include "fme/ui/SettingsModel.h"
#include "fme/ui/utils/Progress.h"

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
#include "fme/widgets/LssWidget.h"
#include "fme/widgets/MsdWidget.h"
#include "fme/widgets/MserWidget.h"
#include "fme/widgets/OrbWidget.h"
#include "fme/widgets/SiftWidget.h"
#include "fme/widgets/StarWidget.h"
#include "fme/widgets/SurfWidget.h"

#include "fme/process/MultiProcess.h"
#include "fme/process/features/FeatureExtractorProcess.h"

#include <tidop/core/messages.h>

#include <QFileInfo>
#include <QDir>


namespace fme
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
    mAgastDetector(new AgastWidget),
    mAkazeDetector(new AkazeWidget),
    mBriskDetector(new BriskWidget),
    mFastDetector(new FastWidget),
    mGfttDetector(new GfttWidget),
    mKazeDetector(new KazeWidget),
    mMsdDetector(new MsdWidget),
    mMserDetector(new MserWidget),
    mOrbDetector(new OrbWidget),
    mSiftDetector(new SiftWidget),
    mStarDetector(new StarWidget),
    mSurfDetector(new SurfWidget),
    mAkazeDescriptor(new AkazeWidget),
    mBriefDescriptor(new BriefWidget),
    mBriskDescriptor(new BriskWidget),
    mDaisyDescriptor(new DaisyWidget),
    mFreakDescriptor(new FreakWidget),
    mHogDescriptor(new HogWidget),
    mKazeDescriptor(new KazeWidget),
    mLatchDescriptor(new LatchWidget),
    mLucidDescriptor(new LucidWidget),
    mLssDescriptor(new LssWidget),
    mOrbDescriptor(new OrbWidget),
    mSiftDescriptor(new SiftWidget),
    mSurfDescriptor(new SurfWidget),
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

  if (mSiftDetector){
    delete mSiftDetector;
    mSiftDetector = nullptr;
  }

  if (mStarDetector){
    delete mStarDetector;
    mStarDetector = nullptr;
  }

  if (mSurfDetector){
    delete mSurfDetector;
    mSurfDetector = nullptr;
  }

  if (mAkazeDescriptor){
    delete mAkazeDescriptor;
    mAkazeDescriptor = nullptr;
  }

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

  if (mLucidDescriptor){
    delete mLucidDescriptor;
    mLucidDescriptor = nullptr;
  }

  if (mLssDescriptor){
    delete mLssDescriptor;
    mLssDescriptor = nullptr;
  }

  if (mOrbDescriptor){
    delete mOrbDescriptor;
    mOrbDescriptor = nullptr;
  }

  if (mSiftDescriptor){
    delete mSiftDescriptor;
    mSiftDescriptor = nullptr;
  }

  if (mSurfDescriptor){
    delete mSurfDescriptor;
    mSurfDescriptor = nullptr;
  }

  if (mMultiProcess){
    delete mMultiProcess;
    mMultiProcess = nullptr;
  }
}

void FeatureExtractorPresenter::help()
{
}

void FeatureExtractorPresenter::open()
{

  Feature *detector = mProjectModel->currentSession()->detector().get();
  Feature *descriptor = mProjectModel->currentSession()->descriptor().get();
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

  /* LUCID */

  mLucidDescriptor->setLucidKernel(descriptor && descriptor->type() == Feature::Type::lucid ?
                                     dynamic_cast<ILucid *>(descriptor)->lucidKernel() :
                                     mSettingsModel->lucidKernel());
  mLucidDescriptor->setBlurKernel(descriptor && descriptor->type() == Feature::Type::lucid ?
                                    dynamic_cast<ILucid *>(descriptor)->blurKernel() :
                                    mSettingsModel->lucidBlurKernel());

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

  mSurfDetector->setOctaves(detector && detector->type() == Feature::Type::surf ?
                            dynamic_cast<ISurf *>(detector)->octaves() :
                            mSettingsModel->surfOctaves());
  mSurfDetector->setOctaveLayers(detector && detector->type() == Feature::Type::surf ?
                                 dynamic_cast<ISurf *>(detector)->octaveLayers() :
                                 mSettingsModel->surfOctaveLayers());
  mSurfDetector->setRotatedFeatures(detector && detector->type() == Feature::Type::surf ?
                                    dynamic_cast<ISurf *>(detector)->rotatedFeatures() :
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
  mSurfDescriptor->setRotatedFeatures(descriptor && descriptor->type() == Feature::Type::surf ?
                                      dynamic_cast<ISurf *>(descriptor)->rotatedFeatures() :
                                      mSettingsModel->surfRotatedFeatures());
  mSurfDescriptor->setHessianThreshold(descriptor && descriptor->type() == Feature::Type::surf ?
                                       dynamic_cast<ISurf *>(descriptor)->hessianThreshold() :
                                       mSettingsModel->surfHessianThreshold());
  mSurfDescriptor->setExtendedDescriptor(descriptor && descriptor->type() == Feature::Type::surf ?
                                         dynamic_cast<ISurf *>(descriptor)->extendedDescriptor() :
                                         mSettingsModel->surfExtendedDescriptor());


  mView->exec();
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
  mView->addKeypointDetector(mSiftDetector);
  mView->addKeypointDetector(mStarDetector);
  mView->addKeypointDetector(mSurfDetector);

  mView->addDescriptorExtractor(mAkazeDescriptor);
  mView->addDescriptorExtractor(mBriefDescriptor);
  mView->addDescriptorExtractor(mBriskDescriptor);
  mView->addDescriptorExtractor(mDaisyDescriptor);
  mView->addDescriptorExtractor(mFreakDescriptor);
  mView->addDescriptorExtractor(mHogDescriptor);
  mView->addDescriptorExtractor(mKazeDescriptor);
  mView->addDescriptorExtractor(mLatchDescriptor);
  mView->addDescriptorExtractor(mLucidDescriptor);
  mView->addDescriptorExtractor(mLssDescriptor);
  mView->addDescriptorExtractor(mOrbDescriptor);
  mView->addDescriptorExtractor(mSiftDescriptor);
  mView->addDescriptorExtractor(mSurfDescriptor);

  setCurrentkeypointDetector(mSiftDescriptor->windowTitle());
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

  msgInfo("Processing has been canceled by the user");
}

void FeatureExtractorPresenter::run()
{

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
    keypointDetector = std::make_shared<OrbDetectorDescriptor>(mOrbDetector->featuresNumber(),
                                                               mOrbDetector->scaleFactor(),
                                                               mOrbDetector->levelsNumber(),
                                                               mOrbDetector->edgeThreshold(),
                                                               mOrbDetector->wta_k(),
                                                               mOrbDetector->scoreType(),
                                                               mOrbDetector->patchSize(),
                                                               mOrbDetector->fastThreshold());
  } else if (currentKeypointDetector.compare("SIFT") == 0){
    keypointDetector = std::make_shared<SiftDetectorDescriptor>(mSiftDetector->featuresNumber(),
                                                                mSiftDetector->octaveLayers(),
                                                                mSiftDetector->contrastThreshold(),
                                                                mSiftDetector->edgeThreshold(),
                                                                mSiftDetector->sigma());
  } else if (currentKeypointDetector.compare("STAR") == 0){
    keypointDetector = std::make_shared<StarDetector>(mStarDetector->maxSize(),
                                                      mStarDetector->responseThreshold(),
                                                      mStarDetector->lineThresholdProjected(),
                                                      mStarDetector->lineThresholdBinarized(),
                                                      mStarDetector->suppressNonmaxSize());
  } else if (currentKeypointDetector.compare("SURF") == 0){
    keypointDetector = std::make_shared<SurfDetectorDescriptor>(mSurfDetector->hessianThreshold(),
                                                                mSurfDetector->octaves(),
                                                                mSurfDetector->octaveLayers(),
                                                                mSurfDetector->extendedDescriptor(),
                                                                mSurfDetector->rotatedFeatures());
  } else {
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
  } else if (currentDescriptorExtractor.compare("BRIEF") == 0){
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
  } else if (currentDescriptorExtractor.compare("LUCID") == 0){
    descriptorExtractor = std::make_shared<LucidDescriptor>(mLucidDescriptor->lucidKernel(),
                                                            mLucidDescriptor->blurKernel());
  } else if (currentDescriptorExtractor.compare("LSS") == 0){
    descriptorExtractor = std::make_shared<LssDescriptor>();
  } else if (currentDescriptorExtractor.compare("ORB") == 0){
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
  } else if (currentDescriptorExtractor.compare("SIFT") == 0){
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
    if (currentKeypointDetector.compare("SURF") == 0){
      descriptorExtractor = std::make_shared<SurfDetectorDescriptor>(mSurfDetector->hessianThreshold(),
                                                                     mSurfDetector->octaves(),
                                                                     mSurfDetector->octaveLayers(),
                                                                     mSurfDetector->extendedDescriptor(),
                                                                     mSurfDetector->rotatedFeatures());
    } else {
      descriptorExtractor = std::make_shared<SurfDetectorDescriptor>(mSurfDescriptor->hessianThreshold(),
                                                                     mSurfDescriptor->octaves(),
                                                                     mSurfDescriptor->octaveLayers(),
                                                                     mSurfDescriptor->extendedDescriptor(),
                                                                     mSurfDescriptor->rotatedFeatures());
    }
  } else {
    ///TODO: error
    return;
  }

  mProjectModel->setDetector(std::dynamic_pointer_cast<Feature>(keypointDetector));
  mProjectModel->setDescriptor(std::dynamic_pointer_cast<Feature>(descriptorExtractor));

  /// Hay que recuperar las imagenes de la carpeta de preprocesos
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    QString file_in = (*it)->path();
    QFileInfo fileInfo(file_in);
    QString preprocessed_image = fileInfo.path();
    preprocessed_image.append("\\").append(mProjectModel->currentSession()->name());
    preprocessed_image.append("\\preprocess\\");
    preprocessed_image.append(fileInfo.fileName());
    QString features = fileInfo.path();
    features.append("\\").append(mProjectModel->currentSession()->name());
    features.append("\\features\\");
    QDir dir_out(features);
    if (!dir_out.exists()) {
      dir_out.mkpath(".");
    }
    features.append(fileInfo.fileName()).append(".xml");

    std::shared_ptr<FeatureExtractor> feat_extract(new FeatureExtractor(preprocessed_image,
                                                                        features,
                                                                        keypointDetector,
                                                                        descriptorExtractor));
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

void FeatureExtractorPresenter::setCurrentkeypointDetector(const QString &featureExtractor)
{
  mView->setCurrentKeypointDetector(featureExtractor);

  mView->disableDescriptorExtractor("AKAZE");
  mView->disableDescriptorExtractor("KAZE");
  mView->enableDescriptorExtractor("ORB");
  mView->enableDescriptorExtractor("HOG");

  if (featureExtractor.compare("AGAST") == 0){
    mView->setCurrentDescriptorExtractor("SIFT");
  } else if (featureExtractor.compare("AKAZE") == 0){
    mView->setCurrentDescriptorExtractor("AKAZE");
    mView->enableDescriptorExtractor("AKAZE");
    mView->enableDescriptorExtractor("KAZE");
  } else if (featureExtractor.compare("BRISK") == 0){
    mView->setCurrentDescriptorExtractor("BRISK");
    mView->disableDescriptorExtractor("HOG");
  } else if (featureExtractor.compare("FAST") == 0){
    mView->setCurrentDescriptorExtractor("SIFT");
  } else if (featureExtractor.compare("GFTT") == 0){
    mView->setCurrentDescriptorExtractor("SIFT");
  } else if (featureExtractor.compare("KAZE") == 0){
    mView->setCurrentDescriptorExtractor("KAZE");
    mView->enableDescriptorExtractor("AKAZE");
    mView->enableDescriptorExtractor("KAZE");
  } else if (featureExtractor.compare("MSD") == 0){
    mView->setCurrentDescriptorExtractor("SIFT");
  } else if (featureExtractor.compare("MSER") == 0){
    mView->setCurrentDescriptorExtractor("SIFT");
  } else if (featureExtractor.compare("ORB") == 0){
    mView->setCurrentDescriptorExtractor("ORB");
  } else if (featureExtractor.compare("SIFT") == 0){
    mView->setCurrentDescriptorExtractor("SIFT");
    mView->disableDescriptorExtractor("ORB");
  } else if (featureExtractor.compare("STAR") == 0){
    mView->setCurrentDescriptorExtractor("SIFT");
  } else if (featureExtractor.compare("SURF") == 0){
    mView->setCurrentDescriptorExtractor("SURF");
  }

}

void FeatureExtractorPresenter::setCurrentDescriptorExtractor(const QString &descriptorExtractor)
{
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

  //  QByteArray ba = msg.toLocal8Bit();
  //  msgError("(%i) %s", code, ba.constData());
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

void FeatureExtractorPresenter::onFeaturesExtracted(const QString &features)
{
  mProjectModel->addFeatures(features);
  emit featuresExtracted(features);
}

} // namespace fme
