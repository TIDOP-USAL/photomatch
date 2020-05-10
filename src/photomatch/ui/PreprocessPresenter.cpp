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

//#include "photomatch/ui/PreprocessModel.h"
#include "photomatch/ui/PreprocessView.h"
#include "photomatch/ui/ProjectModel.h"
#include "photomatch/ui/SettingsModel.h"
#include "photomatch/ui/utils/Progress.h"
#include "photomatch/ui/HelpDialog.h"

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

PreprocessPresenterImp::PreprocessPresenterImp(PreprocessView *view,
                                               ProjectModel *projectModel,
                                               SettingsModel *settingsModel)
  : PreprocessPresenter(),
    mView(view),
    mProjectModel(projectModel),
    mSettingsModel(settingsModel),
    mHelp(nullptr),
    mACEBSF(new AcebsfWidgetImp),
    mCLAHE(new ClaheWidgetImp),
    mCMBFHE(new CmbfheWidgetImp),
    mDecolor(new DecolorWidgetImp),
    mDHE(new DheWidgetImp),
    mFAHE(new FaheWidgetImp),
    mHMCLAHE(new HmclaheWidgetImp),
    mLCEBSESCS(new LceBsescsWidgetImp),
    mMSRCP(new MsrcpWidgetImp),
    mNOSHP(new NoshpWidgetImp),
    mPOHE(new PoheWidgetImp),
    mRSWHE(new RswheWidgetImp),
    mWallis(new WallisWidgetImp),
    mMultiProcess(new MultiProcess(true)),
    mProgressHandler(nullptr)
{
  this->init();
  this->initSignalAndSlots();
}

PreprocessPresenterImp::~PreprocessPresenterImp()
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

void PreprocessPresenterImp::help()
{
  if (mHelp){
    mHelp->setPage("preprocess.html");
    mHelp->show();
  }
}

void PreprocessPresenterImp::open()
{

  if (Session *current_session = mProjectModel->currentSession().get()) {
    if (Preprocess *preprocess = current_session->preprocess().get()) {
      this->setCurrentPreprocess(preprocess->name());
      this->setPreprocessProperties(preprocess);
    }

    mView->setSessionName(current_session->name());
    mView->exec();
  } else {
    msgError("No active session found");
    return;
  }
}

void PreprocessPresenterImp::setPreprocessProperties(Preprocess *preprocess)
{
  this->setAcebsfProperties(preprocess);
  this->setClaheProperties(preprocess);
  this->setCmbfheProperties(preprocess);
  this->setDheProperties(preprocess);
  this->setFaheProperties(preprocess);
  this->setHmClaheProperties(preprocess);
  this->setLcebsescsProperties(preprocess);
  this->setMsrcpProperties(preprocess);
  this->setNoshpProperties(preprocess);
  this->setPoheProperties(preprocess);
  this->setRswheProperties(preprocess);
  this->setWallisProperties(preprocess);
}

void PreprocessPresenterImp::setAcebsfProperties(Preprocess *preprocess)
{
  mACEBSF->setBlockSize(preprocess && preprocess->type() == Preprocess::Type::acebsf ?
                          dynamic_cast<Acebsf *>(preprocess)->blockSize() :
                          mSettingsModel->acebsfBlockSize());
  mACEBSF->setL(preprocess && preprocess->type() == Preprocess::Type::acebsf ?
                  dynamic_cast<Acebsf *>(preprocess)->l() :
                  mSettingsModel->acebsfL());
  mACEBSF->setK1(preprocess && preprocess->type() == Preprocess::Type::acebsf ?
                   dynamic_cast<Acebsf *>(preprocess)->k1() :
                   mSettingsModel->acebsfK1());
  mACEBSF->setK2(preprocess && preprocess->type() == Preprocess::Type::acebsf ?
                   dynamic_cast<Acebsf *>(preprocess)->k2() :
                   mSettingsModel->acebsfK2());
}

void PreprocessPresenterImp::setClaheProperties(Preprocess *preprocess)
{
  mCLAHE->setClipLimit(preprocess && preprocess->type() == Preprocess::Type::clahe ?
                         dynamic_cast<Clahe *>(preprocess)->clipLimit() :
                         mSettingsModel->claheClipLimit());
  mCLAHE->setTilesGridSize(preprocess && preprocess->type() == Preprocess::Type::clahe ?
                             dynamic_cast<Clahe *>(preprocess)->tilesGridSize() :
                             mSettingsModel->claheTilesGridSize());
}

void PreprocessPresenterImp::setCmbfheProperties(Preprocess *preprocess)
{
  mCMBFHE->setBlockSize(preprocess && preprocess->type() == Preprocess::Type::cmbfhe ?
                          dynamic_cast<Cmbfhe *>(preprocess)->blockSize() :
                          mSettingsModel->faheBlockSize());
}

void PreprocessPresenterImp::setDheProperties(Preprocess *preprocess)
{
  mDHE->setX(preprocess && preprocess->type() == Preprocess::Type::dhe ?
               dynamic_cast<Dhe *>(preprocess)->x() :
               mSettingsModel->dheX());
}

void PreprocessPresenterImp::setFaheProperties(Preprocess *preprocess)
{
  mFAHE->setBlockSize(preprocess && preprocess->type() == Preprocess::Type::fahe ?
                        dynamic_cast<Fahe *>(preprocess)->blockSize() :
                        mSettingsModel->faheBlockSize());
}

void PreprocessPresenterImp::setHmClaheProperties(Preprocess *preprocess)
{
  mHMCLAHE->setBlockSize(preprocess && preprocess->type() == Preprocess::Type::hmclahe ?
                           dynamic_cast<Hmclahe *>(preprocess)->blockSize() :
                           mSettingsModel->hmclaheBlockSize());
  mHMCLAHE->setL(preprocess && preprocess->type() == Preprocess::Type::hmclahe ?
                   dynamic_cast<Hmclahe *>(preprocess)->l() :
                   mSettingsModel->hmclaheL());
  mHMCLAHE->setPhi(preprocess && preprocess->type() == Preprocess::Type::hmclahe ?
                     dynamic_cast<Hmclahe *>(preprocess)->phi() :
                     mSettingsModel->hmclahePhi());
}

void PreprocessPresenterImp::setLcebsescsProperties(Preprocess *preprocess)
{
  mLCEBSESCS->setBlockSize(preprocess && preprocess->type() == Preprocess::Type::lce_bsescs ?
                             dynamic_cast<LceBsescs *>(preprocess)->blockSize() :
                             mSettingsModel->lceBsescsBlockSize());
}

void PreprocessPresenterImp::setMsrcpProperties(Preprocess *preprocess)
{
  mMSRCP->setMidScale(preprocess && preprocess->type() == Preprocess::Type::msrcp ?
                        dynamic_cast<Msrcp *>(preprocess)->midScale() :
                        mSettingsModel->msrcpMidScale());
  mMSRCP->setLargeScale(preprocess && preprocess->type() == Preprocess::Type::msrcp ?
                          dynamic_cast<Msrcp *>(preprocess)->largeScale() :
                          mSettingsModel->msrcpLargeScale());
  mMSRCP->setSmallScale(preprocess && preprocess->type() == Preprocess::Type::msrcp ?
                          dynamic_cast<Msrcp *>(preprocess)->smallScale() :
                          mSettingsModel->msrcpSmallScale());
}

void PreprocessPresenterImp::setNoshpProperties(Preprocess *preprocess)
{
  mNOSHP->setBlockSize(preprocess && preprocess->type() == Preprocess::Type::noshp ?
                         dynamic_cast<Noshp *>(preprocess)->blockSize() :
                         mSettingsModel->noshpBlockSize());
}

void PreprocessPresenterImp::setPoheProperties(Preprocess *preprocess)
{
  mPOHE->setBlockSize(preprocess && preprocess->type() == Preprocess::Type::pohe ?
                        dynamic_cast<Pohe *>(preprocess)->blockSize() :
                        mSettingsModel->poheBlockSize());
}

void PreprocessPresenterImp::setRswheProperties(Preprocess *preprocess)
{
  mRSWHE->setHistogramCut(preprocess && preprocess->type() == Preprocess::Type::rswhe ?
                            static_cast<RswheWidget::HistogramCut>(dynamic_cast<Rswhe *>(preprocess)->histogramCut()) :
                            static_cast<RswheWidget::HistogramCut>(mSettingsModel->rswheHistogramCut()));
  mRSWHE->setHistogramDivisions(preprocess && preprocess->type() == Preprocess::Type::rswhe ?
                                  dynamic_cast<Rswhe *>(preprocess)->histogramDivisions() :
                                  mSettingsModel->rswheHistogramDivisions());
}

void PreprocessPresenterImp::setWallisProperties(Preprocess *preprocess)
{
  mWallis->setContrast(preprocess && preprocess->type() == Preprocess::Type::wallis ?
                         dynamic_cast<Wallis *>(preprocess)->contrast() :
                         mSettingsModel->wallisContrast());
  mWallis->setBrightness(preprocess && preprocess->type() == Preprocess::Type::wallis ?
                           dynamic_cast<Wallis *>(preprocess)->brightness() :
                           mSettingsModel->wallisBrightness());
  mWallis->setKernelSize(preprocess && preprocess->type() == Preprocess::Type::wallis ?
                           dynamic_cast<Wallis *>(preprocess)->kernelSize() :
                           mSettingsModel->wallisKernelSize());
  mWallis->setImposedAverage(preprocess && preprocess->type() == Preprocess::Type::wallis ?
                               dynamic_cast<Wallis *>(preprocess)->imposedAverage() :
                               mSettingsModel->wallisImposedAverage());
  mWallis->setImposedLocalStdDev(preprocess && preprocess->type() == Preprocess::Type::wallis ?
                                   dynamic_cast<Wallis *>(preprocess)->imposedLocalStdDev() :
                                   mSettingsModel->wallisImposedLocalStdDev());
}

void PreprocessPresenterImp::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void PreprocessPresenterImp::init()
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

void PreprocessPresenterImp::initSignalAndSlots()
{
  connect(mView, SIGNAL(preprocessChange(QString)), this, SLOT(setCurrentPreprocess(QString)));

  connect(mView, SIGNAL(run()),      this, SLOT(run()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));
}

void PreprocessPresenterImp::setProgressHandler(ProgressHandler *progressHandler)
{
  mProgressHandler = progressHandler;
}

void PreprocessPresenterImp::cancel()
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

void PreprocessPresenterImp::run()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()) {

    if(std::shared_ptr<Preprocess> preprocess = current_session->preprocess()){
      int i_ret = QMessageBox(QMessageBox::Warning,
                              tr("Previous results"),
                              tr("The previous results will be overwritten. Do you wish to continue?"),
                              QMessageBox::Yes|QMessageBox::No).exec();
      if (i_ret == QMessageBox::No) {
        return;
      }
    }

    mMultiProcess->clearProcessList();

    QString currentPreprocess = mView->currentPreprocess();
    std::shared_ptr<ImageProcess> image_process = this->preprocess(currentPreprocess);

    mProjectModel->setMaxImageSize(mView->fullImageSize() ? -1 : mView->maxImageSize());
    mProjectModel->setPreprocess(std::dynamic_pointer_cast<Preprocess>(image_process));

    for(auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
      QString file_in = (*it)->path();
      QString file_out = fileOut(file_in);

      std::shared_ptr<ImagePreprocess> preprocess(new ImagePreprocess(file_in,
                                                                      file_out,
                                                                      image_process,
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
  } else {
    msgError("No active session found");
    return;
  }
}

std::shared_ptr<ImageProcess> PreprocessPresenterImp::preprocess(const QString &currentPreprocess)
{
  std::shared_ptr<ImageProcess> image_process;
  if (currentPreprocess.compare("ACEBSF") == 0) {
    image_process = std::make_shared<AcebsfPreprocess>(mACEBSF->blockSize(),
                                                       mACEBSF->l(),
                                                       mACEBSF->k1(),
                                                       mACEBSF->k2());
  } else if (currentPreprocess.compare("CLAHE") == 0) {
#ifdef HAVE_CUDA
    if (mSettingsModel->useCuda()){
       image_process = std::make_shared<ClahePreprocessCuda>(mCLAHE->clipLimit(),
                                                             mCLAHE->tileGridSize());
    } else {
#endif // HAVE_CUDA
      image_process = std::make_shared<ClahePreprocess>(mCLAHE->clipLimit(),
                                                        mCLAHE->tileGridSize());
#ifdef HAVE_CUDA
    }
#endif // HAVE_CUDA
  } else if (currentPreprocess.compare("CMBFHE") == 0) {
    image_process = std::make_shared<CmbfhePreprocess>(mCMBFHE->blockSize());
  } else if (currentPreprocess.compare("Decolorization") == 0) {
    image_process = std::make_shared<DecolorPreprocess>();
  } else if (currentPreprocess.compare("DHE") == 0) {
    image_process = std::make_shared<DhePreprocess>(mDHE->x());
  } else if (currentPreprocess.compare("FAHE") == 0) {
    image_process = std::make_shared<FahePreprocess>(mFAHE->blockSize());
  } else if (currentPreprocess.compare("HMCLAHE") == 0) {
    image_process = std::make_shared<HmclahePreprocess>(mHMCLAHE->blockSize(),
                                                        mHMCLAHE->l(),
                                                        mHMCLAHE->phi());
  } else if (currentPreprocess.compare("LCE-BSESCS") == 0) {
    image_process = std::make_shared<LceBsescsPreprocess>(mLCEBSESCS->blockSize());
  } else if (currentPreprocess.compare("MSRCP") == 0) {
    image_process = std::make_shared<MsrcpPreprocess>(mMSRCP->smallScale(),
                                                      mMSRCP->midScale(),
                                                      mMSRCP->largeScale());
  } else if (currentPreprocess.compare("NOSHP") == 0) {
    image_process = std::make_shared<NoshpPreprocess>(mNOSHP->blockSize());
  } else if (currentPreprocess.compare("POHE") == 0) {
    image_process = std::make_shared<PohePreprocess>(mPOHE->blockSize());
  } else if (currentPreprocess.compare("RSWHE") == 0) {
    image_process = std::make_shared<RswhePreprocess>(mRSWHE->histogramDivisions(),
                                                      static_cast<RswhePreprocess::HistogramCut>(mRSWHE->histogramCut()));
  } else if (currentPreprocess.compare("Wallis Filter") == 0) {
    image_process = std::make_shared<WallisPreprocess>(mWallis->contrast(),
                                                       mWallis->brightness(),
                                                       mWallis->imposedAverage(),
                                                       mWallis->imposedLocalStdDev(),
                                                       mWallis->kernelSize());
  }
  return image_process;
}

QString PreprocessPresenterImp::fileOut(const QString &fileIn)
{
  QString file_out;
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){
    QFileInfo fileInfo(fileIn);
    file_out = mProjectModel->projectFolder();
    file_out.append("\\").append(current_session->name());
    file_out.append("\\preprocess\\");
    QDir dir_out(file_out);
    if (!dir_out.exists()) {
      dir_out.mkpath(".");
    }
    file_out.append(fileInfo.fileName());
  }
  return file_out;
}

void PreprocessPresenterImp::setCurrentPreprocess(const QString &preprocess)
{
  mView->setCurrentPreprocess(preprocess);
}

void PreprocessPresenterImp::onError(int code, const QString &msg)
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

void PreprocessPresenterImp::onFinished()
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

void PreprocessPresenterImp::onImagePreprocessed(const QString &image)
{
  mProjectModel->addPreprocessedImage(image);
  emit imagePreprocessed(image);
}

} // namespace photomatch
