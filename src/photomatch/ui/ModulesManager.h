#ifndef PHOTOMATCH_MODULES_MANAGER_H
#define PHOTOMATCH_MODULES_MANAGER_H

#include <QObject>
namespace photomatch
{

class MainWindowView;
class MainWindowModel;
class MainWindowPresenter;
class Project;
class ProjectController;
class IProjectModel;
class NewProjectModule;

class ModulesManager
  : public QObject
{

  Q_OBJECT

public:

  ModulesManager();
  ~ModulesManager();

  MainWindowView *view();
  MainWindowModel *model();
  MainWindowPresenter *presenter();
  IProjectModel *projectModel();
  NewProjectModule &newProject();

protected slots:

  void createNewProjectModule();

private:

  void init();

protected:

  MainWindowView *mView;
  MainWindowModel *mModel;
  MainWindowPresenter *mPresenter;
  Project *mProject;
  ProjectController *mProjectIO;
  IProjectModel *mProjectModel;

  NewProjectModule *mNewProjectModule;

};

} // namespace photomatch

#endif // PHOTOMATCH_MODULES_MANAGER_H
