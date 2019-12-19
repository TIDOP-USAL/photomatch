#include "NewProjectPresenter.h"

#include "photomatch/ui/ProjectModel.h"
#include "photomatch/ui/NewProjectView.h"
#include "photomatch/ui/HelpDialog.h"

#include <QStandardPaths>
#include <QDir>


namespace photomatch
{

NewProjectPresenter::NewProjectPresenter(INewProjectView *view, IProjectModel *model)
  : INewProjectPresenter(),
    mView(view),
    mProjectModel(model),
    mHelp(nullptr)
{
  init();

  connect(mView, SIGNAL(accepted()), this, SLOT(saveProject()));
  connect(mView, SIGNAL(rejected()), this, SLOT(discartProject()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));
}

NewProjectPresenter::~NewProjectPresenter()
{
}

/* public slots */

void NewProjectPresenter::help()
{
  if (mHelp){
    mHelp->setPage("menus.html#new_project");
    mHelp->show();
  }
}

// INewProjectPresenter interface

// protected slots

void NewProjectPresenter::saveProject()
{
  ///TODO: Hay que comprobar que el nombre y la ruta sean correctos.
  /// sin que incluyan caracteres no permitidos
  ///   QRegExp re("(^(PRN|AUX|NUL|CON|COM[1-9]|LPT[1-9]|(\\.+)$)(\\..*)?$)|(([\\x00-\\x1f\\\\?*:\";|/<>])+)|(([\\. ]+)");
  /// https://www.boost.org/doc/libs/1_43_0/libs/filesystem/doc/portability_guide.htm


  QString prj_path = mView->projectPath();
  if (mView->createProjectFolder())
    prj_path.append("/").append(mView->projectName());
  mProjectModel->setName(mView->projectName());
  mProjectModel->setProjectFolder(prj_path);
  QDir dir(prj_path);
  if (!dir.exists()) {
    dir.mkpath(".");
  }
  mProjectModel->setDescription(mView->projectDescription());
  prj_path.append("/").append(mView->projectName()).append(".xml");
  mProjectModel->saveAs(prj_path);

  emit projectCreate();

  mView->clear();
}

void NewProjectPresenter::discartProject()
{
  mView->clear();
}

// IPresenter interface

// public slots:

void NewProjectPresenter::open()
{
  mProjectModel->clear();

  mView->setProjectPath(mProjectsDefaultPath);

  mView->exec();
}

void NewProjectPresenter::setHelp(std::shared_ptr<HelpDialog> &help)
{
  mHelp = help;
}

// private

void NewProjectPresenter::init()
{
  mProjectsDefaultPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
  mProjectsDefaultPath.append("/photomatch/Projects");

  QDir dir(mProjectsDefaultPath);
  if (!dir.exists()) {
    dir.mkpath(".");
  }
}

} // namespace photomatch

