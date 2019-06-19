#include "NewProjectPresenter.h"

#include "NewProjectModel.h"
#include "NewProjectView.h"
//#include "ui/help.h"

#include <QStandardPaths>
#include <QDir>


namespace fme
{

NewProjectPresenter::NewProjectPresenter(INewProjectView *view, INewProjectModel *model)
  : INewProjectPresenter(),
    mView(view),
    mModel(model)/*,
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

  QString prj_path = mView->projectPath();
  if (mView->createProjectFolder())
    prj_path.append("/").append(mView->projectName());
  mModel->setProjectName(mView->projectName());
  mModel->setProjectPath(prj_path);
  mModel->setProjectDescription(mView->projectDescription());
  mModel->save(prj_path.append("/").append(mView->projectName()).append(".xml"));

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
  mModel->newProject();

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

