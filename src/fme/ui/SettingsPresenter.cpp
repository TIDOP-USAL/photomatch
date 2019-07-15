#include "SettingsPresenter.h"

#include "SettingsModel.h"
#include "SettingsView.h"

/* Image preprocess */
//#include "fme/widgets/AcebsfWidget.h"
#include "fme/widgets/ClaheWidget.h"
#include "fme/widgets/CmbfheWidget.h"
#include "fme/widgets/DheWidget.h"
#include "fme/widgets/FaheWidget.h"
//#include "fme/widgets/HmclaheWidget.h"
//#include "fme/widgets/LceBsescsWidget.h"
//#include "fme/widgets/MsrcpWidget.h"
//#include "fme/widgets/NoshpWidget.h"
//#include "fme/widgets/PoheWidget.h"
//#include "fme/widgets/RswheWidget.h"
//#include "fme/widgets/WallisWidget.h"

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

#include <QLocale>

namespace fme
{

SettingsPresenter::SettingsPresenter(ISettingsView *view, ISettingsModel *model)
  : ISettingsPresenter(),
    mView(view),
    mModel(model),
    /*mHelp(nullptr),*/
    //mACEBS(new AcebsfWidget),
    mCLAHE(new ClaheWidget),
    mCMBFHE(new CmbfheWidget),
    mDHE(new DheWidget),
    mFAHE(new FaheWidget),
    //mHMCLAHE(new HmclaheWidget),
    //mLCEBSESCS(new LceBsescsWidget),
    //mMSRCP(new MsrcpWidget),
    //mNOSHP(new NoshpWidget),
    //mPOHE(new PoheWidget),
    //mRSWHE(new RswheWidget),
    //mWallis(new WallisWidget),
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
    mSurf(new SurfWidget)
{
  init();

  connect(mView, SIGNAL(languageChange(QString)), this, SLOT(setLanguage(QString)));

  connect(mView, SIGNAL(accepted()), this, SLOT(save()));
  connect(mView, SIGNAL(applyChanges()), this, SLOT(save()));
  connect(mView, SIGNAL(rejected()), this, SLOT(discart()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));

  connect(mModel, SIGNAL(unsavedChanges(bool)), mView, SLOT(setUnsavedChanges(bool)));

  /* CLAHE */
  connect(mCLAHE, SIGNAL(clipLimitChange(double)),         mModel, SLOT(setClaheClipLimit(double)));
  connect(mCLAHE, SIGNAL(tileGridSizeChange(QSize)),       mModel, SLOT(setClaheTilesGridSize(QSize)));

  /* CMBFHE */
  connect(mCMBFHE, SIGNAL(blockSizeChange(QSize)),         mModel, SLOT(setCmbfheBlockSize(QSize)));

  /* DHE */
  connect(mDHE, SIGNAL(xChange(int)),                      mModel, SLOT(setDheX(int)));

  /* FAHE */
  connect(mFAHE,  SIGNAL(blockSizeChange(QSize)),          mModel, SLOT(setFaheBlockSize(QSize)));

  /* AGAST */
  connect(mAgast, SIGNAL(thresholdChange(int)),            mModel, SLOT(setAgastThreshold(int)));
  connect(mAgast, SIGNAL(nonmaxSuppressionChange(bool)),   mModel, SLOT(setAgastNonmaxSuppression(bool)));
  connect(mAgast, SIGNAL(detectorTypeChange(QString)),     mModel, SLOT(setAgastDetectorType(QString)));

  /* AKAZE */
  connect(mAkaze, SIGNAL(descriptorTypeChange(QString)),   mModel, SLOT(setAkazeDescriptorType(QString)));
  connect(mAkaze, SIGNAL(descriptorSizeChange(int)),       mModel, SLOT(setAkazeDescriptorSize(int)));
  connect(mAkaze, SIGNAL(descriptorChannelsChange(int)),   mModel, SLOT(setAkazeDescriptorChannels(int)));
  connect(mAkaze, SIGNAL(thresholdChange(double)),         mModel, SLOT(setAkazeThreshold(double)));
  connect(mAkaze, SIGNAL(octavesChange(int)),              mModel, SLOT(setAkazeOctaves(int)));
  connect(mAkaze, SIGNAL(octaveLayersChange(int)),         mModel, SLOT(setAkazeOctaveLayers(int)));
  connect(mAkaze, SIGNAL(diffusivityChange(QString)),      mModel, SLOT(setAkazeDiffusivity(QString)));

  /* SIFT */
  connect(mSift, SIGNAL(featuresNumberChange(int)),        mModel, SLOT(setSiftFeaturesNumber(int)));
  connect(mSift, SIGNAL(octaveLayersChange(int)),          mModel, SLOT(setSiftOctaveLayers(int)));
  connect(mSift, SIGNAL(contrastThresholdChange(double)),  mModel, SLOT(setSiftContrastThreshold(double)));
  connect(mSift, SIGNAL(edgeThresholdChange(double)),      mModel, SLOT(setSiftEdgeThreshold(double)));
  connect(mSift, SIGNAL(sigmaChange(double)),              mModel, SLOT(setSiftSigma(double)));

  /* SURF */
  connect(mSurf, SIGNAL(hessianThresholdChange(double)),   mModel, SLOT(setSurfHessianThreshold(double)));
  connect(mSurf, SIGNAL(octavesChange(int)),               mModel, SLOT(setSurfOctaves(int)));
  connect(mSurf, SIGNAL(octaveLayersChange(int)),          mModel, SLOT(setSurfOctaveLayers(int)));
  connect(mSurf, SIGNAL(extendedDescriptorChange(bool)),   mModel, SLOT(setSurfExtendedDescriptor(bool)));
  connect(mSurf, SIGNAL(rotatedFeaturesChange(bool)),      mModel, SLOT(setSurfRotatedFeatures(bool)));
}

SettingsPresenter::~SettingsPresenter()
{
//  if (mACEBS){
//    delete mACEBS;
//    mACEBS = nullptr;
//  }

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

//  if (mHMCLAHE){
//    delete mHMCLAHE;
//    mHMCLAHE = nullptr;
//  }
//  if (mLCEBSESCS){
//    delete mLCEBSESCS;
//    mLCEBSESCS = nullptr;
//  }
//  if (mMSRCP){
//    delete mMSRCP;
//    mMSRCP = nullptr;
//  }
//  if (mNOSHP){
//    delete mNOSHP;
//    mNOSHP = nullptr;
//  }
//  if (mPOHE){
//    delete mPOHE;
//    mPOHE = nullptr;
//  }
//  if (mRSWHE){
//    delete mRSWHE;
//    mRSWHE = nullptr;
//  }
//  if (mWallis){
//    delete mWallis;
//    mWallis = nullptr;
//  }

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

  ///TODO: completar....
  mCLAHE->setClipLimit(mModel->claheClipLimit());
  mCLAHE->setTilesGridSize(mModel->claheTilesGridSize());

  mCMBFHE->setBlockSize(mModel->faheBlockSize());

  mDHE->setX(mModel->dheX());

  mFAHE->setBlockSize(mModel->faheBlockSize());

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

  mSift->setSigma(mModel->siftSigma());
  mSift->setOctaveLayers(mModel->siftOctaveLayers());
  mSift->setEdgeThreshold(mModel->siftEdgeThreshold());
  mSift->setFeaturesNumber(mModel->siftFeaturesNumber());
  mSift->setContrastThreshold(mModel->siftContrastThreshold());

  mSurf->setOctaves(mModel->surfOctaves());
  mSurf->setOctaveLayers(mModel->surfOctaveLayers());
  mSurf->setRotatedFeatures(mModel->surfRotatedFeatures());
  mSurf->setHessianThreshold(mModel->surfHessianThreshold());
  mSurf->setExtendedDescriptor(mModel->surfExtendedDescriptor());

  mView->exec();
}

void SettingsPresenter::init()
{
  mView->addPreprocess(mCLAHE);
  mView->addPreprocess(mCMBFHE);
  mView->addPreprocess(mDHE);
  mView->addPreprocess(mFAHE);

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
