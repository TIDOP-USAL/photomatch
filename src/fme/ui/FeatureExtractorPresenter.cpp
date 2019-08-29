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

#include "fme/process/MultiProcess.h"
#include "fme/process/features/FeatureExtractorProcess.h"

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
    mOrbDescriptor(new OrbWidget),
    mSiftDescriptor(new SiftWidget),
    mSurfDescriptor(new SurfWidget),
    mMultiProcess(new MultiProcess(true))
{
  init();

  connect(mView, SIGNAL(keypointDetectorChange(QString)),      this, SLOT(setCurrentkeypointDetector(QString)));
  connect(mView, SIGNAL(descriptorExtractorChange(QString)),   this, SLOT(setCurrentDescriptorExtractor(QString)));
  connect(mView, SIGNAL(run()), this, SLOT(run()));
  connect(mView, SIGNAL(rejected()), this, SLOT(discart()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));

  connect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError()));
  connect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));
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
  mAgastDetector->setThreshold(mSettingsModel->agastThreshold());
  mAgastDetector->setDetectorType(mSettingsModel->agastDetectorType());
  mAgastDetector->setNonmaxSuppression(mSettingsModel->agastNonmaxSuppression());

  mAkazeDetector->setOctaves(mSettingsModel->akazeOctaves());
  mAkazeDetector->setThreshold(mSettingsModel->akazeThreshold());
  mAkazeDetector->setDiffusivity(mSettingsModel->akazeDiffusivity());
  mAkazeDetector->setOctaveLayers(mSettingsModel->akazeOctaveLayers());
  mAkazeDetector->setDescriptorSize(mSettingsModel->akazeDescriptorSize());
  mAkazeDetector->setDescriptorType(mSettingsModel->akazeDescriptorType());
  mAkazeDetector->setDescriptorChannels(mSettingsModel->akazeDescriptorChannels());
  mAkazeDescriptor->setOctaves(mSettingsModel->akazeOctaves());
  mAkazeDescriptor->setThreshold(mSettingsModel->akazeThreshold());
  mAkazeDescriptor->setDiffusivity(mSettingsModel->akazeDiffusivity());
  mAkazeDescriptor->setOctaveLayers(mSettingsModel->akazeOctaveLayers());
  mAkazeDescriptor->setDescriptorSize(mSettingsModel->akazeDescriptorSize());
  mAkazeDescriptor->setDescriptorType(mSettingsModel->akazeDescriptorType());
  mAkazeDescriptor->setDescriptorChannels(mSettingsModel->akazeDescriptorChannels());

  mBriefDescriptor->setBytes(mSettingsModel->briefBytes());
  mBriefDescriptor->setUseOrientation(mSettingsModel->briefUseOrientation());

  mBriskDetector->setThreshold(mSettingsModel->briskThreshold());
  mBriskDetector->setOctaves(mSettingsModel->briskOctaves());
  mBriskDetector->setPatternScale(mSettingsModel->briskPatternScale());
  mBriskDescriptor->setThreshold(mSettingsModel->briskThreshold());
  mBriskDescriptor->setOctaves(mSettingsModel->briskOctaves());
  mBriskDescriptor->setPatternScale(mSettingsModel->briskPatternScale());

  mDaisyDescriptor->setNorm(mSettingsModel->daisyNorm());
  mDaisyDescriptor->setQRadius(mSettingsModel->daisyQRadius());
  mDaisyDescriptor->setQTheta(mSettingsModel->daisyQTheta());
  mDaisyDescriptor->setQHist(mSettingsModel->daisyQHist());
  mDaisyDescriptor->setNorm(mSettingsModel->daisyNorm());
  mDaisyDescriptor->setInterpolation(mSettingsModel->daisyInterpolation());
  mDaisyDescriptor->setUseOrientation(mSettingsModel->daisyUseOrientation());

  mFastDetector->setThreshold(mSettingsModel->fastThreshold());
  mFastDetector->setNonmaxSuppression(mSettingsModel->fastNonmaxSuppression());
  mFastDetector->setDetectorType(mSettingsModel->fastdetectorType());

  mFreakDescriptor->setOrientationNormalized(mSettingsModel->freakOrientationNormalized());
  mFreakDescriptor->setScaleNormalized(mSettingsModel->freakScaleNormalized());
  mFreakDescriptor->setPatternScale(mSettingsModel->freakPatternScale());
  mFreakDescriptor->setOctaves(mSettingsModel->freakOctaves());

  mGfttDetector->setMaxFeatures(mSettingsModel->gfttMaxFeatures());
  mGfttDetector->setQualityLevel(mSettingsModel->gfttQualityLevel());
  mGfttDetector->setMinDistance(mSettingsModel->gfttMinDistance());
  mGfttDetector->setBlockSize(mSettingsModel->gfttBlockSize());
  mGfttDetector->setHarrisDetector(mSettingsModel->gfttHarrisDetector());
  mGfttDetector->setK(mSettingsModel->gfttK());

  mHogDescriptor->setWinSize(mSettingsModel->hogWinSize());
  mHogDescriptor->setBlockSize(mSettingsModel->hogBlockSize());
  mHogDescriptor->setBlockStride(mSettingsModel->hogBlockStride());
  mHogDescriptor->setCellSize(mSettingsModel->hogCellSize());
  mHogDescriptor->setNbins(mSettingsModel->hogNbins());
  mHogDescriptor->setDerivAperture(mSettingsModel->hogDerivAperture());

  mKazeDetector->setExtendedDescriptor(mSettingsModel->kazeExtendedDescriptor());
  mKazeDetector->setUpright(mSettingsModel->kazeUpright());
  mKazeDetector->setThreshold(mSettingsModel->kazeUpright());
  mKazeDetector->setOctaves(mSettingsModel->kazeOctaves());
  mKazeDetector->setOctaveLayers(mSettingsModel->kazeOctaveLayers());
  mKazeDetector->setDiffusivity(mSettingsModel->kazeDiffusivity());
  mKazeDescriptor->setExtendedDescriptor(mSettingsModel->kazeExtendedDescriptor());
  mKazeDescriptor->setUpright(mSettingsModel->kazeUpright());
  mKazeDescriptor->setThreshold(mSettingsModel->kazeUpright());
  mKazeDescriptor->setOctaves(mSettingsModel->kazeOctaves());
  mKazeDescriptor->setOctaveLayers(mSettingsModel->kazeOctaveLayers());
  mKazeDescriptor->setDiffusivity(mSettingsModel->kazeDiffusivity());

  mLatchDescriptor->setBytes(mSettingsModel->latchBytes());
  mLatchDescriptor->setRotationInvariance(mSettingsModel->latchRotationInvariance());
  mLatchDescriptor->setHalfSsdSize(mSettingsModel->latchHalfSsdSize());

  mLucidDescriptor->setLucidKernel(mSettingsModel->lucidKernel());
  mLucidDescriptor->setBlurKernel(mSettingsModel->lucidBlurKernel());

  mMsdDetector->setThresholdSaliency(mSettingsModel->msdThresholdSaliency());
  mMsdDetector->setPathRadius(mSettingsModel->msdPathRadius());
  mMsdDetector->setKNN(mSettingsModel->msdKnn());
  mMsdDetector->setAreaRadius(mSettingsModel->msdAreaRadius());
  mMsdDetector->setScaleFactor(mSettingsModel->msdScaleFactor());
  mMsdDetector->setNMSRadius(mSettingsModel->msdNMSRadius());
  mMsdDetector->setNScales(mSettingsModel->msdNScales());
  mMsdDetector->setNMSScaleR(mSettingsModel->msdNMSScaleR());
  mMsdDetector->setComputeOrientations(mSettingsModel->msdComputeOrientations());
  mMsdDetector->setAffineMSD(mSettingsModel->msdAffineMSD());
  mMsdDetector->setTilts(mSettingsModel->msdTilts());

  mMserDetector->setDelta(mSettingsModel->mserDelta());
  mMserDetector->setMaxArea(mSettingsModel->mserMaxArea());
  mMserDetector->setMinArea(mSettingsModel->mserMinArea());
  mMserDetector->setMaxVariation(mSettingsModel->mserMaxVariation());
  mMserDetector->setMinDiversity(mSettingsModel->mserMinDiversity());
  mMserDetector->setMaxEvolution(mSettingsModel->mserMaxEvolution());
  mMserDetector->setAreaThreshold(mSettingsModel->mserAreaThreshold());
  mMserDetector->setMinMargin(mSettingsModel->mserMinMargin());
  mMserDetector->setEdgeBlurSize(mSettingsModel->mserEdgeBlurSize());

  mOrbDetector->setScaleFactor(mSettingsModel->orbScaleFactor());
  mOrbDetector->setFeaturesNumber(mSettingsModel->orbFeaturesNumber());
  mOrbDetector->setLevelsNumber(mSettingsModel->orbLevelsNumber());
  mOrbDetector->setEdgeThreshold(mSettingsModel->orbEdgeThreshold());
  mOrbDetector->setWTA_K(mSettingsModel->orbWta_k());
  mOrbDetector->setScoreType(mSettingsModel->orbScoreType());
  mOrbDetector->setPatchSize(mSettingsModel->orbPatchSize());
  mOrbDetector->setFastThreshold(mSettingsModel->orbFastThreshold());
  mOrbDescriptor->setScaleFactor(mSettingsModel->orbScaleFactor());
  mOrbDescriptor->setFeaturesNumber(mSettingsModel->orbFeaturesNumber());
  mOrbDescriptor->setLevelsNumber(mSettingsModel->orbLevelsNumber());
  mOrbDescriptor->setEdgeThreshold(mSettingsModel->orbEdgeThreshold());
  mOrbDescriptor->setWTA_K(mSettingsModel->orbWta_k());
  mOrbDescriptor->setScoreType(mSettingsModel->orbScoreType());
  mOrbDescriptor->setPatchSize(mSettingsModel->orbPatchSize());
  mOrbDescriptor->setFastThreshold(mSettingsModel->orbFastThreshold());

  mSiftDetector->setSigma(mSettingsModel->siftSigma());
  mSiftDetector->setOctaveLayers(mSettingsModel->siftOctaveLayers());
  mSiftDetector->setEdgeThreshold(mSettingsModel->siftEdgeThreshold());
  mSiftDetector->setFeaturesNumber(mSettingsModel->siftFeaturesNumber());
  mSiftDetector->setContrastThreshold(mSettingsModel->siftContrastThreshold());
  mSiftDescriptor->setSigma(mSettingsModel->siftSigma());
  mSiftDescriptor->setOctaveLayers(mSettingsModel->siftOctaveLayers());
  mSiftDescriptor->setEdgeThreshold(mSettingsModel->siftEdgeThreshold());
  mSiftDescriptor->setFeaturesNumber(mSettingsModel->siftFeaturesNumber());
  mSiftDescriptor->setContrastThreshold(mSettingsModel->siftContrastThreshold());

  mStarDetector->setMaxSize(mSettingsModel->starMaxSize());
  mStarDetector->setResponseThreshold(mSettingsModel->starResponseThreshold());
  mStarDetector->setLineThresholdProjected(mSettingsModel->starLineThresholdProjected());
  mStarDetector->setLineThresholdBinarized(mSettingsModel->starLineThresholdBinarized());
  mStarDetector->setSuppressNonmaxSize(mSettingsModel->starSuppressNonmaxSize());

  mSurfDetector->setOctaves(mSettingsModel->surfOctaves());
  mSurfDetector->setOctaveLayers(mSettingsModel->surfOctaveLayers());
  mSurfDetector->setRotatedFeatures(mSettingsModel->surfRotatedFeatures());
  mSurfDetector->setHessianThreshold(mSettingsModel->surfHessianThreshold());
  mSurfDetector->setExtendedDescriptor(mSettingsModel->surfExtendedDescriptor());
  mSurfDescriptor->setOctaves(mSettingsModel->surfOctaves());
  mSurfDescriptor->setOctaveLayers(mSettingsModel->surfOctaveLayers());
  mSurfDescriptor->setRotatedFeatures(mSettingsModel->surfRotatedFeatures());
  mSurfDescriptor->setHessianThreshold(mSettingsModel->surfHessianThreshold());
  mSurfDescriptor->setExtendedDescriptor(mSettingsModel->surfExtendedDescriptor());

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
  mView->addKeypointDetector(mBriskDescriptor);
  mView->addDescriptorExtractor(mDaisyDescriptor);
  mView->addDescriptorExtractor(mFreakDescriptor);
  mView->addDescriptorExtractor(mHogDescriptor);
  mView->addDescriptorExtractor(mKazeDescriptor);
  mView->addDescriptorExtractor(mLatchDescriptor);
  mView->addDescriptorExtractor(mLucidDescriptor);
  mView->addDescriptorExtractor(mOrbDescriptor);
  mView->addDescriptorExtractor(mSiftDescriptor);
  mView->addDescriptorExtractor(mSurfDescriptor);

  setCurrentkeypointDetector(mSiftDescriptor->windowTitle());
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
    if (currentKeypointDetector.compare("SIFT") == 0){
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
    mMultiProcess->appendProcess(feat_extract);
  }

  mMultiProcess->start();
}

void FeatureExtractorPresenter::setCurrentkeypointDetector(const QString &featureExtractor)
{
  mView->setCurrentKeypointDetector(featureExtractor);

  mView->disableDescriptorExtractor("AKAZE");

  if (featureExtractor.compare("AGAST") == 0){
    mView->setCurrentDescriptorExtractor("SIFT");
  } else if (featureExtractor.compare("AKAZE") == 0){
    mView->setCurrentDescriptorExtractor("AKAZE");
    mView->enableDescriptorExtractor("AKAZE");
  } else if (featureExtractor.compare("BRISK") == 0){
    mView->setCurrentDescriptorExtractor("BRISK");
  } else if (featureExtractor.compare("FAST") == 0){
    mView->setCurrentDescriptorExtractor("SIFT");
  } else if (featureExtractor.compare("GFTT") == 0){
    mView->setCurrentDescriptorExtractor("SIFT");
  } else if (featureExtractor.compare("KAZE") == 0){
    mView->setCurrentDescriptorExtractor("KAZE");
    mView->enableDescriptorExtractor("AKAZE");
  } else if (featureExtractor.compare("MSD") == 0){
    mView->setCurrentDescriptorExtractor("SIFT");
  } else if (featureExtractor.compare("MSER") == 0){
    mView->setCurrentDescriptorExtractor("SIFT");
  } else if (featureExtractor.compare("ORB") == 0){
    mView->setCurrentDescriptorExtractor("ORB");
  } else if (featureExtractor.compare("SIFT") == 0){
    mView->setCurrentDescriptorExtractor("SIFT");
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

void FeatureExtractorPresenter::onError(int, QString)
{

}

void FeatureExtractorPresenter::onFinished()
{
  emit featureExtractorFinished();
}

} // namespace fme
