#include "ModulesManager.h"

#include "MainWindowView.h"
#include "MainWindowModel.h"
#include "MainWindowPresenter.h"

#include "ProjectModel.h"
#include "NewProjectModule.h"

namespace photomatch
{

ModulesManager::ModulesManager()
  : mView(nullptr),
    mModel(nullptr),
    mPresenter(nullptr),
    mProject(new ProjectImp),
    mProjectIO(new ProjectControllerImp),
    mProjectModel(nullptr),
    mNewProjectModule(nullptr)
{
  init();
}

ModulesManager::~ModulesManager()
{
  if (mView){
    delete mView;
    mView = nullptr;
  }

  if (mModel){
    delete mModel;
    mModel = nullptr;
  }

  if (mPresenter){
    delete mPresenter;
    mPresenter = nullptr;
  }
}

MainWindowView *ModulesManager::view()
{
  if (mView == nullptr){
    mView = new MainWindowView;
  }
  return mView;
}

MainWindowModel *ModulesManager::model()
{
  if (mModel == nullptr){
    mModel = new MainWindowModel;
  }
  return mModel;
}

MainWindowPresenter *ModulesManager::presenter()
{
  if (mPresenter == nullptr){
    mPresenter = new MainWindowPresenter(this->view(), this->model(), this->projectModel());
    connect(mPresenter, SIGNAL(openNewProjectModule()), this, SLOT(createNewProjectModule()));
  }
  return mPresenter;
}

NewProjectModule &ModulesManager::newProject()
{
  return NewProjectModule::instance(this->view(), this->projectModel());
}

void ModulesManager::createNewProjectModule()
{
  mNewProjectModule = &newProject();
  disconnect(mPresenter, SIGNAL(openNewProjectModule()), this, SLOT(createNewProjectModule()));
  connect(mPresenter, SIGNAL(openNewProjectModule()), mNewProjectModule, SLOT(show()));
  connect(mNewProjectModule, SIGNAL(projectCreate()), mPresenter, SLOT(loadProject()));
  mNewProjectModule->show();
}

void ModulesManager::init()
{

}



IProjectModel *ModulesManager::projectModel()
{
  if (mProjectModel == nullptr){
    mProjectModel = new ProjectModel(mProjectIO, mProject);
  }
  return mProjectModel;
}


} // namespace photomatch
