#include "BatchPresenter.h"

#include "photomatch/ui/BatchView.h"
#include "photomatch/ui/BatchModel.h"
#include "photomatch/ui/ProjectModel.h"
#include "photomatch/ui/SettingsModel.h"

namespace photomatch
{

BatchPresenter::BatchPresenter(IBatchView *view,
                               IBatchModel *model,
                               IProjectModel *projectModel,
                               ISettingsModel *settingsModel)
  : IBatchPresenter(),
    mView(view),
    mModel(model),
    mProjectModel(projectModel),
    mSettingsModel(settingsModel)
{
  init();

  connect(mView, SIGNAL(sessionChange(QString)),   this, SLOT(sessionChange(QString)));
  connect(mView, SIGNAL(accepted()),               this, SLOT(save()));

  //connect(mView, SIGNAL(rejected()),        this, SLOT(discart()));
  connect(mView, SIGNAL(help()),            this, SLOT(help()));
}

BatchPresenter::~BatchPresenter()
{

}

void BatchPresenter::help()
{
}

void BatchPresenter::open()
{
  mView->clear();

  //mView->setSessions(mModel->sessions());
  //mView->setActiveSession(mModel->sessionName());

  mView->open();
}

void BatchPresenter::init()
{
}

void BatchPresenter::sessionChange(const QString &session)
{
  //mModel->setSessionName(session);
  mView->setActiveSession(session);
}

} // namespace photomatch


