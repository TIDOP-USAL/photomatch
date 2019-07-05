#include "SettingsPresenter.h"

#include "SettingsModel.h"
#include "SettingsView.h"

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

  mSurf->setOctaves(mModel->surfOctaves());
  mSurf->setOctaveLayers(mModel->surfOctaveLayers());
  mSurf->setRotatedFeatures(mModel->surfRotatedFeatures());
  mSurf->setHessianThreshold(mModel->surfHessianThreshold());
  mSurf->setExtendedDescriptor(mModel->surfExtendedDescriptor());

  mView->exec();
}

void SettingsPresenter::init()
{
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
