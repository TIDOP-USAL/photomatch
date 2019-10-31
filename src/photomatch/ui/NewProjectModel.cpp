#include "NewProjectModel.h"

#include "fme/core/project.h"

#include <QDir>


namespace fme
{

NewProjectModel::NewProjectModel(IProject *project)
  : mProject(project)
{
  init();
}

NewProjectModel::~NewProjectModel()
{
}

// INewProjectModel interface

void NewProjectModel::newProject()
{
  mProject->clear();
}

void NewProjectModel::save(const QString &file)
{
  QDir dir(mProject->projectFolder());
  if (!dir.exists()) {
    dir.mkpath(".");
  }
  //mProject->saveAs(file);
}

void NewProjectModel::setProjectName(const QString &name)
{
  mProject->setName(name);
}

void NewProjectModel::setProjectFolder(const QString &dir)
{
  mProject->setProjectFolder(dir);
}

void NewProjectModel::setProjectDescription(const QString &description)
{
  mProject->setDescription(description);
}

// IModel interface

// private

void NewProjectModel::init()
{
}

} // namespace fme
