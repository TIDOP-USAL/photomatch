#include "NewSessionPresenter.h"

#include "fme/ui/ProjectModel.h"
#include "fme/ui/NewSessionView.h"

namespace fme
{

NewSessionPresenter::NewSessionPresenter(INewSessionView *view, IProjectModel *model)
  : INewSessionPresenter(),
    mView(view),
    mProjectModel(model)/*,
      mHelp(nullptr)*/
{
  init();

  connect(mView, SIGNAL(sessionNameChange(QString)), this, SLOT(checkSessionName(QString)));

  connect(mView, SIGNAL(accepted()), this, SLOT(saveProject()));
  connect(mView, SIGNAL(rejected()), this, SLOT(discartProject()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));
}

NewSessionPresenter::~NewSessionPresenter()
{

}

void NewSessionPresenter::help()
{
//  if (mHelp){
//    mHelp->setPage("menus.html#new");
//    mHelp->setModal(true);
//    mHelp->showMaximized();
//  }
}

void NewSessionPresenter::open()
{
  mView->exec();
}

void NewSessionPresenter::init()
{
}

void NewSessionPresenter::saveProject()
{
  mProjectModel->addSession(mView->sessionName(), mView->sessionDescription());

  emit sessionCreate(mView->sessionName());

  mView->clear();
}

void NewSessionPresenter::discartProject()
{
  mView->clear();
}

void NewSessionPresenter::checkSessionName(const QString &name)
{
  std::shared_ptr<Session> session = mProjectModel->findSession(name);
  if (session)
    mView->setExistingName(true);
  else
    mView->setExistingName(false);
}

} // namespace fme
