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
#include "fme/process/ImagePreprocessing/FaheProcess.h"
#include "fme/process/ImagePreprocessing/CmbfheProcess.h"
#include "fme/process/ImagePreprocessing/ClaheProcess.h"
#include "fme/process/ImagePreprocessing/DheProcess.h"

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
    mACEBS(new AcebsfWidget),
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
}

PreprocessPresenter::~PreprocessPresenter()
{
  if (mACEBS){
    delete mACEBS;
    mACEBS = nullptr;
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
  ///TODO: establecer valores de las herramientas según los almacenados en el fichero de configuración
  mCLAHE->setClipLimit(mSettingsModel->claheClipLimit());
  mCLAHE->setTilesGridSize(mSettingsModel->claheTilesGridSize());
  mCMBFHE->setBlockSize(mSettingsModel->faheBlockSize());
  mDHE->setX(mSettingsModel->dheX());
  mFAHE->setBlockSize(mSettingsModel->faheBlockSize());

  mView->exec();
}

void PreprocessPresenter::init()
{
  mView->addPreprocess(mACEBS);
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
  mView->setCurrentPreprocess(mACEBS->windowTitle());
}

void PreprocessPresenter::run()
{
  ///TODO: se crean los procesos
  /// - Se recorren todas las imagenes y se añaden los procesos

  ///

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

    if (mView->currentPreprocess().compare("ACEBS") == 0) {

    } else if (mView->currentPreprocess().compare("CLAHE") == 0) {
      ClaheProcess *clahe_process = new ClaheProcess(file_in, file_out, mCLAHE->clipLimit(), mCLAHE->tileGridSize());
      mMultiProcess->appendProcess(clahe_process);
    } else if (mView->currentPreprocess().compare("CMBFHE") == 0) {
      CmbfheProcess *cmbfhe_process = new CmbfheProcess(file_in, file_out, mCMBFHE->blockSize());
      mMultiProcess->appendProcess(cmbfhe_process);
    } else if (mView->currentPreprocess().compare("DHE") == 0) {
      DheProcess *dhe_process = new DheProcess(file_in, file_out, mDHE->x());
      mMultiProcess->appendProcess(dhe_process);
    } else if (mView->currentPreprocess().compare("FAHE") == 0) {
      FaheProcess *fahe_process = new FaheProcess(file_in, file_out, mFAHE->blockSize());
      mMultiProcess->appendProcess(fahe_process);
    } else if (mView->currentPreprocess().compare("HMCLAHE") == 0) {
    } else if (mView->currentPreprocess().compare("LCEBSESCS") == 0) {
    } else if (mView->currentPreprocess().compare("MSRCP") == 0) {

    } else if (mView->currentPreprocess().compare("NOSHP") == 0) {

    } else if (mView->currentPreprocess().compare("POHE") == 0) {

    } else if (mView->currentPreprocess().compare("RSWHE") == 0) {

    } else if (mView->currentPreprocess().compare("Wallis") == 0) {

    }
  }

  mMultiProcess->start();
}

void PreprocessPresenter::setCurrentPreprocess(const QString &preprocess)
{
//  ///TODO: - Se recuperan los valores del fichero de configuración
//  ///      - Se desactivan las señales del preproceso previo
//  ///      - Se activan las señales del preproceso actual

//  if (mView->currentPreprocess().compare("ACEBS") == 0) {
////    disconnect(mACEBS, SIGNAL(blockSizeChange(QSize)), mProcesACEBS, SLOT(setBlockSize(QSize)));
////    disconnect(mACEBS, SIGNAL(lChange(double)),        mProcesACEBS, SLOT(setL(double)));
////    disconnect(mACEBS, SIGNAL(k1Change(double)),       mProcesACEBS, SLOT(setK1(double)));
////    disconnect(mACEBS, SIGNAL(k2Change(double)),       mProcesACEBS, SLOT(setK2(double)));
//  } else if (preprocess.compare("CLAHE") == 0) {

//  } else if (preprocess.compare("CMBFHE") == 0) {

//  } else if (preprocess.compare("DHE") == 0) {

//  } else if (preprocess.compare("FAHE") == 0) {

//  } else if (preprocess.compare("HMCLAHE") == 0) {

//  } else if (preprocess.compare("LCEBSESCS") == 0) {

//  } else if (preprocess.compare("MSRCP") == 0) {

//  } else if (preprocess.compare("NOSHP") == 0) {

//  } else if (preprocess.compare("POHE") == 0) {

//  } else if (preprocess.compare("RSWHE") == 0) {

//  } else if (preprocess.compare("Wallis") == 0) {

//  }

  mView->setCurrentPreprocess(preprocess);

//  if (preprocess.compare("ACEBS") == 0) {
////    connect(mACEBS, SIGNAL(blockSizeChange(QSize)), mProcesACEBS, SLOT(setBlockSize(QSize)));
////    connect(mACEBS, SIGNAL(lChange(double)),        mProcesACEBS, SLOT(setL(double)));
////    connect(mACEBS, SIGNAL(k1Change(double)),       mProcesACEBS, SLOT(setK1(double)));
////    connect(mACEBS, SIGNAL(k2Change(double)),       mProcesACEBS, SLOT(setK2(double)));
//  } else if (preprocess.compare("CLAHE") == 0) {

//  } else if (preprocess.compare("CMBFHE") == 0) {

//  } else if (preprocess.compare("DHE") == 0) {

//  } else if (preprocess.compare("FAHE") == 0) {

//  } else if (preprocess.compare("HMCLAHE") == 0) {

//  } else if (preprocess.compare("LCEBSESCS") == 0) {

//  } else if (preprocess.compare("MSRCP") == 0) {

//  } else if (preprocess.compare("NOSHP") == 0) {

//  } else if (preprocess.compare("POHE") == 0) {

//  } else if (preprocess.compare("RSWHE") == 0) {

//  } else if (preprocess.compare("Wallis") == 0) {

//  }

  //mModel->setCurrentPreprocess();
}

} // namespace fme
