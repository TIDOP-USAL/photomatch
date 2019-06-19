#ifndef FME_NEW_PROJECT_MODEL_H
#define FME_NEW_PROJECT_MODEL_H

#include "NewProjectInterfaces.h"

namespace fme
{

///TODO: Clase proyecto como inyección de dependencias para facilitar los test.
class NewProjectModel
  : public INewProjectModel
{

public:

  NewProjectModel();
  ~NewProjectModel() override;

// INewProjectModel interface

  void newProject() override;
  void save(const QString &file) override;
  void setProjectName(const QString &name) override;
  void setProjectPath(const QString &path) override;
  void setProjectDescription(const QString &description) override;

// IModel interface

private:

  void init() override;

};

} // namespace fme


#endif // FME_NEW_PROJECT_MODEL_H
