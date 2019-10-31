#ifndef PHOTOMATCH_NEW_PROJECT_MODEL_H
#define PHOTOMATCH_NEW_PROJECT_MODEL_H

#include "NewProjectInterfaces.h"



namespace photomatch
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

} // namespace photomatch


#endif // PHOTOMATCH_NEW_PROJECT_MODEL_H
