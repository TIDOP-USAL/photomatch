#include "DescriptorMatcherPresenter.h"

#include "fme/ui/DescriptorMatcherModel.h"
#include "fme/ui/DescriptorMatcherView.h"
#include "fme/ui/ProjectModel.h"
#include "fme/ui/SettingsModel.h"
#include "fme/ui/utils/ProgressDialog.h"
#include "fme/process/MultiProcess.h"

#include <tidop/core/messages.h>

namespace fme
{

DescriptorMatcherPresenter::DescriptorMatcherPresenter(IDescriptorMatcherView *view,
                                                       IDescriptorMatcherModel *model,
                                                       IProjectModel *projectModel,
                                                       ISettingsModel *settingsModel)
  : IDescriptorMatcherPresenter(),
    mView(view),
    mModel(model),
    mProjectModel(projectModel),
    mSettingsModel(settingsModel),
    mMultiProcess(new MultiProcess(true)),
    mProgressDialog(nullptr)
{
  init();

  connect(mView, SIGNAL(run()),      this, SLOT(run()));
  connect(mView, SIGNAL(rejected()), this, SLOT(discart()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));

  connect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
  connect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));

}

DescriptorMatcherPresenter::~DescriptorMatcherPresenter()
{
  if (mMultiProcess){
    delete mMultiProcess;
    mMultiProcess = nullptr;
  }
}

void DescriptorMatcherPresenter::help()
{
}

void DescriptorMatcherPresenter::open()
{
  mView->setRatio(mSettingsModel->matchRatio());
  mView->setDistance(mSettingsModel->matchDistance());
  mView->setNormType(mSettingsModel->matchNormType());
  mView->setConfidence(mSettingsModel->matchConfidence());
  mView->setCrossMatching(mSettingsModel->matchCrossMatching());
  mView->setMatchingMethod(mSettingsModel->matchMatchingMethod());

  mView->exec();
}

void DescriptorMatcherPresenter::init()
{
}

void DescriptorMatcherPresenter::setProgressDialog(IProgressDialog *progressDialog)
{
  mProgressDialog = progressDialog;
}

void DescriptorMatcherPresenter::run()
{
  mMultiProcess->clearProcessList();

  if (mView->matchingMethod().compare("Brute-Force") == 0){

  }

  mView->hide();

  if (mProgressDialog){
    connect(mProgressDialog, SIGNAL(cancel()), mMultiProcess, SLOT(stop()));
    mProgressDialog->setRange(0, 0);
    mProgressDialog->setWindowTitle("Matching Features...");
    mProgressDialog->setStatusText("Matching Features...");
    mProgressDialog->setFinished(false);
    mProgressDialog->show();
  }

  mMultiProcess->start();
}

void DescriptorMatcherPresenter::onError(int code, const QString &msg)
{
  QByteArray ba = msg.toLocal8Bit();
  msgError("(%i) %s", code, ba.constData());
}

void DescriptorMatcherPresenter::onFinished()
{

  if (mProgressDialog) {
    mProgressDialog->setRange(0,1);
    mProgressDialog->setValue(1);
    mProgressDialog->setFinished(true);
    mProgressDialog->setStatusText(tr("Feature matching finished."));
    disconnect(mProgressDialog, SIGNAL(cancel()), mMultiProcess, SLOT(stop()));
  }

  emit matchesFinished();
}

} // namespace fme

