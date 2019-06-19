#include "MainWindowPresenter.h"

#include "MainWindowView.h"
#include "MainWindowModel.h"

#include "NewProjectInterfaces.h"
#include "NewProjectPresenter.h"
#include "NewProjectModel.h"
#include "NewProjectView.h"

/* Qt */
#include <QFileDialog>
#include <QMessageBox>

namespace fme
{

MainWindowPresenter::MainWindowPresenter(MainWindowView *view, MainWindowModel *model)
  : IPresenter(),
    mView(view),
    mModel(model),
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

void MainWindowPresenter::help()
{
}

void fme::MainWindowPresenter::open()
{
  mView->showMaximized();
}

void MainWindowPresenter::init()
{
}

void MainWindowPresenter::initNewProjectDialog()
{
  if (mNewProjectPresenter == nullptr){
    mNewProjectModel = new NewProjectModel;
    INewProjectView *newProjectView = new NewProjectView(mView);
    mNewProjectPresenter = new NewProjectPresenter(newProjectView, mNewProjectModel);
    //mNewProjectPresenter->setHelp(mHelp);

    connect(mNewProjectPresenter, SIGNAL(projectCreate()), this, SLOT(loadProject()));
  }
}

} // namespace fme



