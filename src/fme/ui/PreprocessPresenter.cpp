#include "PreprocessPresenter.h"

#include "fme/core/preprocess/acebsf.h"
#include "fme/core/preprocess/clahe.h"
#include "fme/core/preprocess/cmbfhe.h"
#include "fme/core/preprocess/dhe.h"
#include "fme/core/preprocess/fahe.h"
#include "fme/core/preprocess/hmclahe.h"
#include "fme/core/preprocess/lce_bsescs.h"
#include "fme/core/preprocess/msrcp.h"
#include "fme/core/preprocess/noshp.h"
#include "fme/core/preprocess/pohe.h"
#include "fme/core/preprocess/rswhe.h"
#include "fme/core/preprocess/wallis.h"

#include "fme/ui/PreprocessModel.h"
#include "fme/ui/PreprocessView.h"
#include "fme/ui/ProjectModel.h"
#include "fme/ui/SettingsModel.h"

#include "fme/widgets/AcebsfWidget.h"
#include "fme/widgets/ClaheWidget.h"
#include "fme/widgets/CmbfheWidget.h"
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

#include "fme/process/MultiProcess.h"
//#include "fme/process/ImagePreprocessing/AcebsfProcess.h"
//#include "fme/process/ImagePreprocessing/FaheProcess.h"
//#include "fme/process/ImagePreprocessing/CmbfheProcess.h"
//#include "fme/process/ImagePreprocessing/ClaheProcess.h"
//#include "fme/process/ImagePreprocessing/DheProcess.h"
//#include "fme/process/ImagePreprocessing/HmclaheProcess.h"
//#include "fme/process/ImagePreprocessing/LceBsescsProcess.h"
//#include "fme/process/ImagePreprocessing/MsrcpProcess.h"
//#include "fme/process/ImagePreprocessing/NoshpProcess.h"
//#include "fme/process/ImagePreprocessing/PoheProcess.h"
//#include "fme/process/ImagePreprocessing/RswheProcess.h"
//#include "fme/process/ImagePreprocessing/WallisProcess.h"
#include "fme/process/preprocess/imagePreprocess.h"

#include <QFileInfo>
#include <QDir>


namespace fme
{

PreprocessPresenter::PreprocessPresenter(IPreprocessView *view,
                                         IPreprocessModel *model,
                                         IProjectModel *projectModel,
                                         ISettingsModel *settingsModel)
  : IPreprocessPresenter(),
    mView(view),
    mModel(model),
    mProjectModel(projectModel),
    mSettingsModel(settingsModel),
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
    mMultiProcess(new MultiProcess(true))
{
  init();

  connect(mView, SIGNAL(preprocessChange(QString)), this, SLOT(setCurrentPreprocess(QString)));

  connect(mView, SIGNAL(run()),      this, SLOT(run()));
  connect(mView, SIGNAL(rejected()), this, SLOT(discart()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));

  connect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError()));
  connect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));
}

PreprocessPresenter::~PreprocessPresenter()
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

  if (mMultiProcess){
    delete mMultiProcess;
    mMultiProcess = nullptr;
  }
}

void PreprocessPresenter::help()
{
}

void PreprocessPresenter::open()
{
  mACEBSF->setBlockSize(mSettingsModel->acebsfBlockSize());
  mACEBSF->setL(mSettingsModel->acebsfL());
  mACEBSF->setK1(mSettingsModel->acebsfK1());
  mACEBSF->setK2(mSettingsModel->acebsfK2());

  mCLAHE->setClipLimit(mSettingsModel->claheClipLimit());
  mCLAHE->setTilesGridSize(mSettingsModel->claheTilesGridSize());

  mCMBFHE->setBlockSize(mSettingsModel->faheBlockSize());

  mDHE->setX(mSettingsModel->dheX());

  mFAHE->setBlockSize(mSettingsModel->faheBlockSize());

  mHMCLAHE->setBlockSize(mSettingsModel->hmclaheBlockSize());
  mHMCLAHE->setL(mSettingsModel->hmclaheL());
  mHMCLAHE->setPhi(mSettingsModel->hmclahePhi());

  mLCEBSESCS->setBlockSize(mSettingsModel->lceBsescsBlockSize());

  mMSRCP->setMidScale(mSettingsModel->msrcpMidScale());
  mMSRCP->setLargeScale(mSettingsModel->msrcpLargeScale());
  mMSRCP->setSmallScale(mSettingsModel->msrcpSmallScale());

  mNOSHP->setBlockSize(mSettingsModel->noshpBlockSize());

  mPOHE->setBlockSize(mSettingsModel->poheBlockSize());

  mRSWHE->setHistogramCut(static_cast<IRswheWidget::HistogramCut>(mSettingsModel->rswheHistogramCut()));
  mRSWHE->setHistogramDivisions(mSettingsModel->rswheHistogramDivisions());

  mWallis->setContrast(mSettingsModel->wallisContrast());
  mWallis->setBrightness(mSettingsModel->wallisBrightness());
  mWallis->setKernelSize(mSettingsModel->wallisKernelSize());
  mWallis->setImposedAverage(mSettingsModel->wallisImposedAverage());
  mWallis->setImposedLocalStdDev(mSettingsModel->wallisImposedLocalStdDev());

  mView->exec();
}

void PreprocessPresenter::init()
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

  mView->setCurrentPreprocess(mACEBSF->windowTitle());
}

void PreprocessPresenter::run()
{
  ///TODO: se crean los procesos
  /// - Se recorren todas las imagenes y se añaden los procesos

  mMultiProcess->clearProcessList();

  QString currentPreprocess = mView->currentPreprocess();
  std::shared_ptr<ImageProcess> imageProcess;

  if (currentPreprocess.compare("ACEBSF") == 0) {
    imageProcess = std::make_shared<AcebsfPreprocess>(mACEBSF->blockSize(),
                                                      mACEBSF->l(),
                                                      mACEBSF->k1(),
                                                      mACEBSF->k2());
  } else if (currentPreprocess.compare("CLAHE") == 0) {
    imageProcess = std::make_shared<ClahePreprocess>(mCLAHE->clipLimit(),
                                                     mCLAHE->tileGridSize());
  } else if (currentPreprocess.compare("CMBFHE") == 0) {
    imageProcess = std::make_shared<CmbfhePreprocess>(mCMBFHE->blockSize());
  } else if (currentPreprocess.compare("DHE") == 0) {
    imageProcess = std::make_shared<DhePreprocess>(mDHE->x());
  } else if (currentPreprocess.compare("FAHE") == 0) {
    imageProcess = std::make_shared<FahePreprocess>(mFAHE->blockSize());
  } else if (currentPreprocess.compare("HMCLAHE") == 0) {
    imageProcess = std::make_shared<HmclahePreprocess>(mHMCLAHE->blockSize(),
                                                       mHMCLAHE->l(),
                                                       mHMCLAHE->phi());
  } else if (currentPreprocess.compare("LCE-BSESCS") == 0) {
    imageProcess = std::make_shared<LceBsescsPreprocess>(mLCEBSESCS->blockSize());
  } else if (currentPreprocess.compare("MSRCP") == 0) {
    imageProcess = std::make_shared<MsrcpPreprocess>(mMSRCP->smallScale(),
                                                     mMSRCP->midScale(),
                                                     mMSRCP->largeScale());
  } else if (currentPreprocess.compare("NOSHP") == 0) {
    imageProcess = std::make_shared<NoshpPreprocess>(mNOSHP->blockSize());
  } else if (currentPreprocess.compare("POHE") == 0) {
    imageProcess = std::make_shared<PohePreprocess>(mPOHE->blockSize());
  } else if (currentPreprocess.compare("RSWHE") == 0) {
    imageProcess = std::make_shared<RswhePreprocess>(mRSWHE->histogramDivisions(),
                                                     static_cast<RswhePreprocess::HistogramCut>(mRSWHE->histogramCut()));
  } else if (currentPreprocess.compare("Wallis Filter") == 0) {
    imageProcess = std::make_shared<WallisPreprocess>(mWallis->contrast(),
                                                      mWallis->brightness(),
                                                      mWallis->imposedAverage(),
                                                      mWallis->imposedLocalStdDev(),
                                                      mWallis->kernelSize());
  }

  mProjectModel->setPreprocess(std::dynamic_pointer_cast<Preprocess>(imageProcess));

  for(auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    QString file_in = (*it)->path();
    QFileInfo fileInfo(file_in);
    QString file_out = fileInfo.path();
    file_out.append("\\").append(mProjectModel->currentSession()->name());
    file_out.append("\\preprocess\\");
    QDir dir_out(file_out);
    if (!dir_out.exists()) {
      dir_out.mkpath(".");
    }
    file_out.append(fileInfo.fileName());

    std::shared_ptr<ImagePreprocess> preprocess(new ImagePreprocess(file_in,
                                                                    file_out,
                                                                    imageProcess,
                                                                    mView->fullImageSize() ? -1 : mView->maxImageSize()));
    mMultiProcess->appendProcess(preprocess);
  }

  mMultiProcess->start();
}

void PreprocessPresenter::setCurrentPreprocess(const QString &preprocess)
{
  mView->setCurrentPreprocess(preprocess);
}

void PreprocessPresenter::onError(int, QString)
{

}

void PreprocessPresenter::onFinished()
{
  emit preprocessFinished();
}

} // namespace fme
