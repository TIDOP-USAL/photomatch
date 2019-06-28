#ifndef FME_NEW_PROJECT_PRESENTER_H
#define FME_NEW_PROJECT_PRESENTER_H

#include <memory>

#include <QObject>

#include "NewProjectInterfaces.h"


namespace fme
{

class INewProjectView;
class IProjectModel;
class Help;

class NewProjectPresenter
  : public INewProjectPresenter
{
  Q_OBJECT

private:

  INewProjectView *mView;
  IProjectModel *mProjectModel;
  QString mProjectsDefaultPath;
  std::shared_ptr<Help> mHelp;

public:

  NewProjectPresenter(INewProjectView *view, IProjectModel *mModel);
  ~NewProjectPresenter() override;

// INewProjectPresenter interface

protected slots:

  void saveProject() override;
  void discartProject() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
//  void setHelp(std::shared_ptr<Help> &help) override;

private:

  void init() override;

};

} // namespace fme


#endif // FME_NEW_PROJECT_PRESENTER_H
