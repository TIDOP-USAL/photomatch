#include "NewProjectModel.h"

//#include "utils/project.h"

#include <QDir>


namespace fme
{

NewProjectModel::NewProjectModel()
{
  init();
}

NewProjectModel::~NewProjectModel()
{
}

// INewProjectModel interface

void NewProjectModel::newProject()
{
//  Project &prj = Project::getInstance();
//  prj.clear(); // Se establecen los valores por defecto
}

void NewProjectModel::save(const QString &file)
{
//  Project &prj = Project::getInstance();
//  QDir dir(prj.dir());
//  if (!dir.exists()) {
//    dir.mkpath(".");
//  }
//  prj.saveAs(file);
}

void NewProjectModel::setProjectName(const QString &name)
{
//  Project::getInstance().setName(name);
}

void NewProjectModel::setProjectPath(const QString &path)
{
//  Project::getInstance().setDir(path);
}

void NewProjectModel::setProjectDescription(const QString &description)
{
//  Project::getInstance().setDescription(description);
}

// IModel interface

// private

void NewProjectModel::init()
{
}

} // namespace fme
