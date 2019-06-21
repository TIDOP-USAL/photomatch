#include "MainWindowPresenter.h"

#include "MainWindowView.h"
#include "MainWindowModel.h"

#include "NewProjectInterfaces.h"
#include "NewProjectPresenter.h"
#include "NewProjectModel.h"
#include "NewProjectView.h"

#include "fme/core/project.h"

/* Qt */
#include <QFileDialog>
#include <QMessageBox>

namespace fme
{

MainWindowPresenter::MainWindowPresenter(MainWindowView *view, MainWindowModel *model)
  : IPresenter(),
    mView(view),
    mModel(model),
    mProjectIO(nullptr),
    mProjectModel(nullptr),
    mNewProjectPresenter(nullptr),
    mNewProjectModel(nullptr)
{
  init();

  /* Menú Archivo */
  connect(mView, SIGNAL(openNew()),                this, SLOT(openNew()));
  connect(mView, SIGNAL(openProject()),            this, SLOT(openProject()));
  connect(mView, SIGNAL(openFromHistory(QString)), this, SLOT(openFromHistory(QString)));
  connect(mView, SIGNAL(clearHistory()),           this, SLOT(deleteHistory()));
  connect(mView, SIGNAL(saveProject()),            this, SLOT(saveProject()));
  connect(mView, SIGNAL(saveProjectAs()),          this, SLOT(saveProjectAs()));
  connect(mView, SIGNAL(closeProject()),           this, SLOT(closeProject()));
  connect(mView, SIGNAL(exit()),                   this, SLOT(exit()));
}

MainWindowPresenter::~MainWindowPresenter()
{
  if (mProjectIO) {
    delete mProjectIO;
    mProjectIO =nullptr;
  }

  if (mProjectModel){
    delete mProjectModel;
    mProjectModel = nullptr;
  }

  if (mNewProjectPresenter) {
    delete mNewProjectPresenter;
    mNewProjectPresenter = nullptr;
  }

  if (mNewProjectModel) {
    delete mNewProjectModel;
    mNewProjectModel = nullptr;
  }
}

void MainWindowPresenter::openNew()
{
  if(mModel->checkUnsavedChanges()) {
    int i_ret = QMessageBox(QMessageBox::Information,
                            tr("Save Changes"),
                            tr("There are unsaved changes. Do you want to save them?"),
                            QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel).exec();
    if (i_ret == QMessageBox::Yes) {
      saveProject();
    } else if (i_ret == QMessageBox::Cancel) {
      return;
    }
  }

  mView->clear();

  initNewProjectDialog();

  mNewProjectPresenter->open();
}

void MainWindowPresenter::openProject()
{

}

void MainWindowPresenter::openFromHistory(const QString &file)
{

}

void MainWindowPresenter::deleteHistory()
{

}

void MainWindowPresenter::saveProject()
{

}

void MainWindowPresenter::saveProjectAs()
{

}

void MainWindowPresenter::closeProject()
{

}

void MainWindowPresenter::exit()
{

}

void MainWindowPresenter::loadProject()
{
  QString prjFile = mProjectModel->path();

  mView->clear();
  mView->setProjectTitle(QString("FME - ").append(mProjectModel->name()));


}

void MainWindowPresenter::help()
{
}

void fme::MainWindowPresenter::open()
{
  mView->showMaximized();
}

void MainWindowPresenter::init()
{
  mProjectIO = new ProjectIO;
  mProjectModel = new Project(mProjectIO);
}

void MainWindowPresenter::initNewProjectDialog()
{
  if (mNewProjectPresenter == nullptr){
    ///TODO: NewProjectModel es un simple wrapper de Project.
    /// igual interesa utilizar Project directamente
    mNewProjectModel = new NewProjectModel(mProjectModel);
    INewProjectView *newProjectView = new NewProjectView(mView);
    mNewProjectPresenter = new NewProjectPresenter(newProjectView, mNewProjectModel);
    //mNewProjectPresenter->setHelp(mHelp);

    connect(mNewProjectPresenter, SIGNAL(projectCreate()), this, SLOT(loadProject()));
  }
}

} // namespace fme

