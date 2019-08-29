#include "DescriptorMatcherPresenter.h"

#include "fme/ui/DescriptorMatcherModel.h"
#include "fme/ui/DescriptorMatcherView.h"
#include "fme/ui/ProjectModel.h"
#include "fme/ui/SettingsModel.h"
#include "fme/process/MultiProcess.h"

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
    mMultiProcess(new MultiProcess(true))
{
  init();

  connect(mView, SIGNAL(run()),      this, SLOT(run()));
  connect(mView, SIGNAL(rejected()), this, SLOT(discart()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));

  connect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError()));
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

void DescriptorMatcherPresenter::run()
{
  mMultiProcess->clearProcessList();

  if (mView->matchingMethod().compare("Brute-Force") == 0){

  }
}

} // namespace fme

