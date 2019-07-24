#include "PreprocessPresenter.h"

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
#include "fme/process/ImagePreprocessing/AcebsfProcess.h"
#include "fme/process/ImagePreprocessing/FaheProcess.h"
#include "fme/process/ImagePreprocessing/CmbfheProcess.h"
#include "fme/process/ImagePreprocessing/ClaheProcess.h"
#include "fme/process/ImagePreprocessing/DheProcess.h"
#include "fme/process/ImagePreprocessing/HmclaheProcess.h"
#include "fme/process/ImagePreprocessing/LceBsescsProcess.h"
#include "fme/process/ImagePreprocessing/MsrcpProcess.h"
#include "fme/process/ImagePreprocessing/NoshpProcess.h"
#include "fme/process/ImagePreprocessing/PoheProcess.h"
#include "fme/process/ImagePreprocessing/RswheProcess.h"
#include "fme/process/ImagePreprocessing/WallisProcess.h"

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

  connect(mView, SIGNAL(run()), this, SLOT(run()));
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

  mMultiProcess->clearProcessList();  ///TODO: Creo que no se esta liberando memoria

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

    QString currentPreprocess = mView->currentPreprocess();
    if (currentPreprocess.compare("ACEBSF") == 0) {
      std::shared_ptr<AcebsfProcess> acebsf_process(new AcebsfProcess(file_in, file_out, mACEBSF->blockSize(), mACEBSF->l(), mACEBSF->k1(), mACEBSF->k2()));
      acebsf_process->setMaxImageSize(mView->fullImageSize() ? -1 : mView->maxImageSize());
      mMultiProcess->appendProcess(acebsf_process);
      mProjectModel->setPreprocess(acebsf_process);
    } else if (currentPreprocess.compare("CLAHE") == 0) {
      std::shared_ptr<ClaheProcess> clahe_process(new ClaheProcess(file_in, file_out, mCLAHE->clipLimit(), mCLAHE->tileGridSize()));
      clahe_process->setMaxImageSize(mView->fullImageSize() ? -1 : mView->maxImageSize());
      mMultiProcess->appendProcess(clahe_process);
      mProjectModel->setPreprocess(clahe_process);
    } else if (currentPreprocess.compare("CMBFHE") == 0) {
      std::shared_ptr<CmbfheProcess> cmbfhe_process(new CmbfheProcess(file_in, file_out, mCMBFHE->blockSize()));
      cmbfhe_process->setMaxImageSize(mView->fullImageSize() ? -1 : mView->maxImageSize());
      mMultiProcess->appendProcess(cmbfhe_process);
      mProjectModel->setPreprocess(cmbfhe_process);
    } else if (currentPreprocess.compare("DHE") == 0) {
      std::shared_ptr<DheProcess> dhe_process(new DheProcess(file_in, file_out, mDHE->x()));
      dhe_process->setMaxImageSize(mView->fullImageSize() ? -1 : mView->maxImageSize());
      mMultiProcess->appendProcess(dhe_process);
      mProjectModel->setPreprocess(dhe_process);
    } else if (currentPreprocess.compare("FAHE") == 0) {
      std::shared_ptr<FaheProcess> fahe_process(new FaheProcess(file_in, file_out, mFAHE->blockSize()));
      fahe_process->setMaxImageSize(mView->fullImageSize() ? -1 : mView->maxImageSize());
      mMultiProcess->appendProcess(fahe_process);
      mProjectModel->setPreprocess(fahe_process);
    } else if (currentPreprocess.compare("HMCLAHE") == 0) {
      std::shared_ptr<HmclaheProcess> hmclahe_process(new HmclaheProcess(file_in, file_out, mHMCLAHE->blockSize(), mHMCLAHE->l(), mHMCLAHE->phi()));
      hmclahe_process->setMaxImageSize(mView->fullImageSize() ? -1 : mView->maxImageSize());
      mMultiProcess->appendProcess(hmclahe_process);
      mProjectModel->setPreprocess(hmclahe_process);
    } else if (currentPreprocess.compare("LCE-BSESCS") == 0) {
      std::shared_ptr<LceBsescsProcess> lceBsescsProcess(new LceBsescsProcess(file_in, file_out, mLCEBSESCS->blockSize()));
      lceBsescsProcess->setMaxImageSize(mView->fullImageSize() ? -1 : mView->maxImageSize());
      mMultiProcess->appendProcess(lceBsescsProcess);
      mProjectModel->setPreprocess(lceBsescsProcess);
    } else if (currentPreprocess.compare("MSRCP") == 0) {
      std::shared_ptr<MsrcpProcess> msrcpProcess(new MsrcpProcess(file_in, file_out, mMSRCP->smallScale(), mMSRCP->midScale(), mMSRCP->largeScale()));
      msrcpProcess->setMaxImageSize(mView->fullImageSize() ? -1 : mView->maxImageSize());
      mMultiProcess->appendProcess(msrcpProcess);
      mProjectModel->setPreprocess(msrcpProcess);
    } else if (currentPreprocess.compare("NOSHP") == 0) {
      std::shared_ptr<NoshpProcess> noshpProcess(new NoshpProcess(file_in, file_out, mNOSHP->blockSize()));
      noshpProcess->setMaxImageSize(mView->fullImageSize() ? -1 : mView->maxImageSize());
      mMultiProcess->appendProcess(noshpProcess);
      mProjectModel->setPreprocess(noshpProcess);
    } else if (currentPreprocess.compare("POHE") == 0) {
      std::shared_ptr<PoheProcess> poheProcess(new PoheProcess(file_in, file_out, mPOHE->blockSize()));
      poheProcess->setMaxImageSize(mView->fullImageSize() ? -1 : mView->maxImageSize());
      mMultiProcess->appendProcess(poheProcess);
      mProjectModel->setPreprocess(poheProcess);
    } else if (currentPreprocess.compare("RSWHE") == 0) {
      std::shared_ptr<RswheProcess> rswheProcess(new RswheProcess(file_in, file_out, mRSWHE->histogramDivisions(), static_cast<RswheProcess::HistogramCut>(mRSWHE->histogramCut())));
      rswheProcess->setMaxImageSize(mView->fullImageSize() ? -1 : mView->maxImageSize());
      mMultiProcess->appendProcess(rswheProcess);
      mProjectModel->setPreprocess(rswheProcess);
    } else if (currentPreprocess.compare("Wallis Filter") == 0) {
      std::shared_ptr<WallisProcess> wallisProcess(new WallisProcess(file_in, file_out, mWallis->contrast(), mWallis->brightness(), mWallis->imposedAverage(), mWallis->imposedLocalStdDev(), mWallis->kernelSize()));
      wallisProcess->setMaxImageSize(mView->fullImageSize() ? -1 : mView->maxImageSize());
      mMultiProcess->appendProcess(wallisProcess);
      mProjectModel->setPreprocess(wallisProcess);
    }
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
