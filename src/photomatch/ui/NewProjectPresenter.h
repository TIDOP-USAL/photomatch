#ifndef PHOTOMATCH_NEW_PROJECT_PRESENTER_H
#define PHOTOMATCH_NEW_PROJECT_PRESENTER_H

#include <memory>

#include <QObject>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class INewProjectView;
class IProjectModel;
class Help;

/*!
 * \brief The INewProjectPresenter class
 */
class INewProjectPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  INewProjectPresenter(){}

  virtual ~INewProjectPresenter() {}

signals:

  /*!
   * \brief Señal que se emite cuando se crea el proyecto
   */
  void projectCreate();

protected slots:

  /*!
   * \brief Guarda el proyecto
   */
  virtual void saveProject() = 0;

  /*!
   * \brief Descarta los cambios en el proyecto
   */
  virtual void discartProject() = 0;

};

class NewProjectPresenter
  : public INewProjectPresenter
{
  Q_OBJECT

public:

  NewProjectPresenter(INewProjectView *view, IProjectModel *model);
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

private:

  INewProjectView *mView;
  IProjectModel *mProjectModel;
  QString mProjectsDefaultPath;
  std::shared_ptr<Help> mHelp;

};

} // namespace photomatch


#endif // PHOTOMATCH_NEW_PROJECT_PRESENTER_H
