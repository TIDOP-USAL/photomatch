#ifndef FME_NEW_PROJECT_MODEL_H
#define FME_NEW_PROJECT_MODEL_H

#include "NewProjectInterfaces.h"



namespace fme
{

class IProject;

class NewProjectModel
  : public INewProjectModel
{

public:

  NewProjectModel(IProject *project);
  ~NewProjectModel() override;

// INewProjectModel interface

  void newProject() override;
  void save(const QString &file) override;
  void setProjectName(const QString &name) override;
  void setProjectFolder(const QString &dir) override;
  void setProjectDescription(const QString &description) override;

// IModel interface

private:

  void init() override;

protected:

  IProject *mProject;
};

} // namespace fme


#endif // FME_NEW_PROJECT_MODEL_H
