#ifndef MAINWINDOWPRESENTER_H
#define MAINWINDOWPRESENTER_H

#include "mvp.h"

namespace fme
{

class MainWindowView;
class MainWindowModel;
class INewProjectPresenter;
class IProjectModel;
class IProjectRW;
class IProject;
class ISettings;
class ISettingsRW;
class ISettingsModel;
class ISettingsPresenter;

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

  /* Menú View */


  /* Menú herramientas */

  void loadImages();
  void newProcessing();
  void openAssistant();
  void openPreprocess();
  void openFeatureExtraction();
  void openFeatureMatching();
  void openSettings();

  /* Menú Ayuda */
  void openAboutDialog();

  /*!
   * \brief Carga del proyecto
   */
  void loadProject();

  void updateProject();

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

  /*!
   * \brief Inicializa la herramienta de configuración de la aplicación
   */
  void initSettingsDialog();

protected:

  MainWindowView *mView;
  MainWindowModel *mModel;

  IProject *mProject;
  IProjectRW *mProjectIO;
  IProjectModel *mProjectModel;

  INewProjectPresenter *mNewProjectPresenter;

  ISettings *mSettings;
  ISettingsRW *mSettingsRW;
  ISettingsModel *mSettingsModel;
  ISettingsPresenter *mSettingsPresenter;

};

} // namespace fme

#endif // MAINWINDOWPRESENTER_H
