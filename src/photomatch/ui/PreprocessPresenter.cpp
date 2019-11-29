#include "PreprocessPresenter.h"

#include "photomatch/core/preprocess/acebsf.h"
#include "photomatch/core/preprocess/clahe.h"
#include "photomatch/core/preprocess/cmbfhe.h"
#include "photomatch/core/preprocess/decolor.h"
#include "photomatch/core/preprocess/dhe.h"
#include "photomatch/core/preprocess/fahe.h"
#include "photomatch/core/preprocess/hmclahe.h"
#include "photomatch/core/preprocess/lce_bsescs.h"
#include "photomatch/core/preprocess/msrcp.h"
#include "photomatch/core/preprocess/noshp.h"
#include "photomatch/core/preprocess/pohe.h"
#include "photomatch/core/preprocess/rswhe.h"
#include "photomatch/core/preprocess/wallis.h"

#include "photomatch/ui/PreprocessModel.h"
#include "photomatch/ui/PreprocessView.h"
#include "photomatch/ui/ProjectModel.h"
#include "photomatch/ui/SettingsModel.h"
#include "photomatch/ui/utils/Progress.h"

#include "photomatch/widgets/AcebsfWidget.h"
#include "photomatch/widgets/ClaheWidget.h"
#include "photomatch/widgets/CmbfheWidget.h"
#include "photomatch/widgets/CmbfheWidget.h"
#include "photomatch/widgets/DecolorWidget.h"
#include "photomatch/widgets/DheWidget.h"
#include "photomatch/widgets/FaheWidget.h"
#include "photomatch/widgets/HmclaheWidget.h"
#include "photomatch/widgets/LceBsescsWidget.h"
#include "photomatch/widgets/MsrcpWidget.h"
#include "photomatch/widgets/NoshpWidget.h"
#include "photomatch/widgets/PoheWidget.h"
#include "photomatch/widgets/RswheWidget.h"
#include "photomatch/widgets/WallisWidget.h"

#include "photomatch/process/MultiProcess.h"
#include "photomatch/process/preprocess/ImagePreprocess.h"

#include <tidop/core/messages.h>

#include <QFileInfo>
#include <QDir>
#include <QMessageBox>

namespace photomatch
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
    mDecolor(new DecolorWidget),
    mDHE(new DheWidget),
    mFAHE(new FaheWidget),
    mHMCLAHE(new HmclaheWidget),
    mLCEBSESCS(new LceBsescsWidget),
    mMSRCP(new MsrcpWidget),
    mNOSHP(new NoshpWidget),
    mPOHE(new PoheWidget),
    mRSWHE(new RswheWidget),
    mWallis(new WallisWidget),
    mMultiProcess(new MultiProcess(true)),
    mProgressHandler(nullptr)
{
  init();

  connect(mView, SIGNAL(preprocessChange(QString)), this, SLOT(setCurrentPreprocess(QString)));

  connect(mView, SIGNAL(run()),      this, SLOT(run()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));

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

  if (mDecolor){
    delete mDecolor;
    mDecolor = nullptr;
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
  Preprocess *preprocess = mProjectModel->currentSession()->preprocess().get();
  if (preprocess) setCurrentPreprocess(preprocess->name());

  mACEBSF->setBlockSize(preprocess && preprocess->type() == Preprocess::Type::acebsf ?
                          dynamic_cast<IAcebsf *>(preprocess)->blockSize() :
                          mSettingsModel->acebsfBlockSize());
  mACEBSF->setL(preprocess && preprocess->type() == Preprocess::Type::acebsf ?
                  dynamic_cast<IAcebsf *>(preprocess)->l() :
                  mSettingsModel->acebsfL());
  mACEBSF->setK1(preprocess && preprocess->type() == Preprocess::Type::acebsf ?
                   dynamic_cast<IAcebsf *>(preprocess)->k1() :
                   mSettingsModel->acebsfK1());
  mACEBSF->setK2(preprocess && preprocess->type() == Preprocess::Type::acebsf ?
                   dynamic_cast<IAcebsf *>(preprocess)->k2() :
                   mSettingsModel->acebsfK2());

  mCLAHE->setClipLimit(preprocess && preprocess->type() == Preprocess::Type::clahe ?
                         dynamic_cast<IClahe *>(preprocess)->clipLimit() :
                         mSettingsModel->claheClipLimit());
  mCLAHE->setTilesGridSize(preprocess && preprocess->type() == Preprocess::Type::clahe ?
                             dynamic_cast<IClahe *>(preprocess)->tilesGridSize() :
                             mSettingsModel->claheTilesGridSize());

  mCMBFHE->setBlockSize(preprocess && preprocess->type() == Preprocess::Type::cmbfhe ?
                          dynamic_cast<ICmbfhe *>(preprocess)->blockSize() :
                          mSettingsModel->faheBlockSize());

  mDHE->setX(preprocess && preprocess->type() == Preprocess::Type::dhe ?
               dynamic_cast<IDhe *>(preprocess)->x() :
               mSettingsModel->dheX());

  mFAHE->setBlockSize(preprocess && preprocess->type() == Preprocess::Type::fahe ?
                        dynamic_cast<IFahe *>(preprocess)->blockSize() :
                        mSettingsModel->faheBlockSize());

  mHMCLAHE->setBlockSize(preprocess && preprocess->type() == Preprocess::Type::hmclahe ?
                           dynamic_cast<IHmclahe *>(preprocess)->blockSize() :
                           mSettingsModel->hmclaheBlockSize());
  mHMCLAHE->setL(preprocess && preprocess->type() == Preprocess::Type::hmclahe ?
                   dynamic_cast<IHmclahe *>(preprocess)->l() :
                   mSettingsModel->hmclaheL());
  mHMCLAHE->setPhi(preprocess && preprocess->type() == Preprocess::Type::hmclahe ?
                     dynamic_cast<IHmclahe *>(preprocess)->phi() :
                     mSettingsModel->hmclahePhi());

  mLCEBSESCS->setBlockSize(preprocess && preprocess->type() == Preprocess::Type::lce_bsescs ?
                             dynamic_cast<ILceBsescs *>(preprocess)->blockSize() :
                             mSettingsModel->lceBsescsBlockSize());

  mMSRCP->setMidScale(preprocess && preprocess->type() == Preprocess::Type::msrcp ?
                        dynamic_cast<IMsrcp *>(preprocess)->midScale() :
                        mSettingsModel->msrcpMidScale());
  mMSRCP->setLargeScale(preprocess && preprocess->type() == Preprocess::Type::msrcp ?
                          dynamic_cast<IMsrcp *>(preprocess)->largeScale() :
                          mSettingsModel->msrcpLargeScale());
  mMSRCP->setSmallScale(preprocess && preprocess->type() == Preprocess::Type::msrcp ?
                          dynamic_cast<IMsrcp *>(preprocess)->smallScale() :
                          mSettingsModel->msrcpSmallScale());

  mNOSHP->setBlockSize(preprocess && preprocess->type() == Preprocess::Type::noshp ?
                         dynamic_cast<INoshp *>(preprocess)->blockSize() :
                         mSettingsModel->noshpBlockSize());

  mPOHE->setBlockSize(preprocess && preprocess->type() == Preprocess::Type::pohe ?
                        dynamic_cast<IPohe *>(preprocess)->blockSize() :
                        mSettingsModel->poheBlockSize());

  mRSWHE->setHistogramCut(preprocess && preprocess->type() == Preprocess::Type::rswhe ?
                            static_cast<IRswheWidget::HistogramCut>(dynamic_cast<IRswhe *>(preprocess)->histogramCut()) :
                            static_cast<IRswheWidget::HistogramCut>(mSettingsModel->rswheHistogramCut()));
  mRSWHE->setHistogramDivisions(preprocess && preprocess->type() == Preprocess::Type::rswhe ?
                                  dynamic_cast<IRswhe *>(preprocess)->histogramDivisions() :
                                  mSettingsModel->rswheHistogramDivisions());

  mWallis->setContrast(preprocess && preprocess->type() == Preprocess::Type::wallis ?
                         dynamic_cast<IWallis *>(preprocess)->contrast() :
                         mSettingsModel->wallisContrast());
  mWallis->setBrightness(preprocess && preprocess->type() == Preprocess::Type::wallis ?
                           dynamic_cast<IWallis *>(preprocess)->brightness() :
                           mSettingsModel->wallisBrightness());
  mWallis->setKernelSize(preprocess && preprocess->type() == Preprocess::Type::wallis ?
                           dynamic_cast<IWallis *>(preprocess)->kernelSize() :
                           mSettingsModel->wallisKernelSize());
  mWallis->setImposedAverage(preprocess && preprocess->type() == Preprocess::Type::wallis ?
                               dynamic_cast<IWallis *>(preprocess)->imposedAverage() :
                               mSettingsModel->wallisImposedAverage());
  mWallis->setImposedLocalStdDev(preprocess && preprocess->type() == Preprocess::Type::wallis ?
                                   dynamic_cast<IWallis *>(preprocess)->imposedLocalStdDev() :
                                   mSettingsModel->wallisImposedLocalStdDev());

  mView->setSessionName(mProjectModel->currentSession()->name());
  mView->exec();
}

void PreprocessPresenter::init()
{
  mView->addPreprocess(mDecolor);
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

  mView->setCurrentPreprocess(mDecolor->windowTitle());
}

void PreprocessPresenter::setProgressHandler(ProgressHandler *progressHandler)
{
  mProgressHandler = progressHandler;
}

void PreprocessPresenter::cancel()
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

  msgWarning("Processing has been canceled by the user");
}

void PreprocessPresenter::run()
{

  if(std::shared_ptr<Preprocess> preprocess = mProjectModel->currentSession()->preprocess()){
    int i_ret = QMessageBox(QMessageBox::Warning,
                            tr("Previous results"),
                            tr("The previous results will be overwritten. Do you wish to continue?"),
                            QMessageBox::Yes|QMessageBox::No).exec();
    if (i_ret == QMessageBox::No) {
      return;
    }
  }

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
  } else if (currentPreprocess.compare("Decolorization") == 0) {
    imageProcess = std::make_shared<DecolorPreprocess>();
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

  mProjectModel->setMaxImageSize(mView->fullImageSize() ? -1 : mView->maxImageSize());
  mProjectModel->setPreprocess(std::dynamic_pointer_cast<Preprocess>(imageProcess));

  for(auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    QString file_in = (*it)->path();
    QFileInfo fileInfo(file_in);
    //QString file_out = fileInfo.path();
    QString file_out = mProjectModel->projectFolder();
    file_out.append("\\").append(mProjectModel->currentSession()->name());
    file_out.append("\\preprocess\\");
    QDir dir_out(file_out);
    if (!dir_out.exists()) {
      dir_out.mkpath(".");
    }
    file_out.append(fileInfo.fileName());

    std::shared_ptr<ImagePreprocess> preprocess(new ImagePreprocess((*it)->path(),
                                                                    file_out,
                                                                    imageProcess,
                                                                    mView->fullImageSize() ? -1 : mView->maxImageSize()));

    connect(preprocess.get(), SIGNAL(preprocessed(QString)), this, SLOT(onImagePreprocessed(QString)));
    mMultiProcess->appendProcess(preprocess);
  }

  connect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
  connect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));

  if (mProgressHandler) {
    connect(mMultiProcess, SIGNAL(finished()),             mProgressHandler,    SLOT(onFinish()));
    connect(mMultiProcess, SIGNAL(statusChangedNext()),    mProgressHandler,    SLOT(onNextPosition()));
    connect(mMultiProcess, SIGNAL(error(int, QString)),    mProgressHandler,    SLOT(onFinish()));

    mProgressHandler->setRange(0, mMultiProcess->count());
    mProgressHandler->setValue(0);
    mProgressHandler->setTitle("Image Preprocessing");
    mProgressHandler->setDescription("Preprocessing images...");
    mProgressHandler->onInit();
  }

  mView->hide();

  msgInfo("Preprocessing images");
  QByteArray ba = currentPreprocess.toLocal8Bit();
  const char *data = ba.constData();
  msgInfo("  Preprocessing method     :  %s", data);

  emit running();

  mMultiProcess->start();
}

void PreprocessPresenter::setCurrentPreprocess(const QString &preprocess)
{
  mView->setCurrentPreprocess(preprocess);
}

void PreprocessPresenter::onError(int code, const QString &msg)
{
  disconnect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
  disconnect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));

  if (mProgressHandler){
    mProgressHandler->setRange(0,1);
    mProgressHandler->setValue(1);
    mProgressHandler->onFinish();
    mProgressHandler->setDescription(tr("Image preprocessing error"));

    disconnect(mMultiProcess, SIGNAL(finished()),                 mProgressHandler,    SLOT(onFinish()));
    disconnect(mMultiProcess, SIGNAL(statusChangedNext()),        mProgressHandler,    SLOT(onNextPosition()));
    disconnect(mMultiProcess, SIGNAL(error(int, QString)),        mProgressHandler,    SLOT(onFinish()));
  }

  emit finished();
}

void PreprocessPresenter::onFinished()
{
  disconnect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
  disconnect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));

  if (mProgressHandler){
    mProgressHandler->setRange(0, 1);
    mProgressHandler->setValue(1);
    mProgressHandler->onFinish();
    mProgressHandler->setDescription(tr("Image preprocessing finished"));

    disconnect(mMultiProcess, SIGNAL(finished()),                 mProgressHandler,    SLOT(onFinish()));
    disconnect(mMultiProcess, SIGNAL(statusChangedNext()),        mProgressHandler,    SLOT(onNextPosition()));
    disconnect(mMultiProcess, SIGNAL(error(int, QString)),        mProgressHandler,    SLOT(onFinish()));
  }

  emit finished();

  msgInfo("Image preprocessing finished");
}

void PreprocessPresenter::onImagePreprocessed(const QString &image)
{
  mProjectModel->addPreprocessedImage(image);
  emit imagePreprocessed(image);
}

} // namespace photomatch