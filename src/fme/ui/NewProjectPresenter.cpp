#include "NewProjectPresenter.h"

#include "ProjectModel.h"
#include "NewProjectView.h"
//#include "ui/help.h"

#include <QStandardPaths>
#include <QDir>


namespace fme
{

NewProjectPresenter::NewProjectPresenter(INewProjectView *view, IProjectModel *model)
  : INewProjectPresenter(),
    mView(view),
    mProjectModel(model)/*,
    mHelp(nullptr)*/
{
  init();

  connect(mView, SIGNAL(accepted()), this, SLOT(saveProject()));
  connect(mView, SIGNAL(rejected()), this, SLOT(discartProject()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));
}

/* public slots */

void NewProjectPresenter::help()
{
//  if (mHelp){
//    mHelp->setPage("menus.html#new");
//    mHelp->setModal(true);
//    mHelp->showMaximized();
//  }
}

NewProjectPresenter::~NewProjectPresenter()
{
}

// INewProjectPresenter interface

// protected slots

void NewProjectPresenter::saveProject()
{
  ///TODO: Hay que comprobar que el nombre y la ruta sean correctos.
  /// sin que incluyan caracteres no permitidos
  ///   QRegExp re("(^(PRN|AUX|NUL|CON|COM[1-9]|LPT[1-9]|(\\.+)$)(\\..*)?$)|(([\\x00-\\x1f\\\\?*:\";|/<>])+)|(([\\. ]+)");
  /// https://www.boost.org/doc/libs/1_43_0/libs/filesystem/doc/portability_guide.htm

  QDir dir(mProjectModel->projectFolder());
  if (!dir.exists()) {
    dir.mkpath(".");
  }

  QString prj_path = mView->projectPath();
  if (mView->createProjectFolder())
    prj_path.append("/").append(mView->projectName());
  mProjectModel->setName(mView->projectName());
  mProjectModel->setProjectFolder(prj_path);
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

//void NewProjectPresenter::setHelp(std::shared_ptr<Help>& help)
//{
//  mHelp = help;
//}

// private

void NewProjectPresenter::init()
{
  mProjectsDefaultPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
  mProjectsDefaultPath.append("/fme/Projects");

  QDir dir(mProjectsDefaultPath);
  if (!dir.exists()) {
    dir.mkpath(".");
  }
}

} // namespace fme

