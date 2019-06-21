#ifndef MAINWINDOWPRESENTER_H
#define MAINWINDOWPRESENTER_H

#include "mvp.h"

namespace fme
{

class MainWindowView;
class MainWindowModel;
class INewProjectPresenter;
class INewProjectModel;
class IProjectIO;
class IProject;

class MainWindowPresenter
  : public IPresenter
{
  Q_OBJECT

public:

  explicit MainWindowPresenter(MainWindowView *view, MainWindowModel *model);
  ~MainWindowPresenter() override;

signals:

public slots:

protected slots:

  /* Menú Archivo */

  void openNew();
  void openProject();
  void openFromHistory(const QString &file);
  void deleteHistory();
  void saveProject();
  void saveProjectAs();
  void closeProject();
  void exit();

  /*!
   * \brief Carga del proyecto
   */
  void loadProject();

// IPresenter interface

public slots:

  void help() override;
  void open() override;

private:

  void init() override;

  /*!
   * \brief Inicializa el dialogo de creación de un nuevo proyecto
   */
  void initNewProjectDialog();

protected:

  MainWindowView *mView;
  MainWindowModel *mModel;

  IProjectIO *mProjectIO;
  IProject *mProjectModel;

  /* Dialogo de creación de un nuevo proyecto */

  INewProjectPresenter *mNewProjectPresenter;
  INewProjectModel *mNewProjectModel;

};

} // namespace fme

#endif // MAINWINDOWPRESENTER_H
