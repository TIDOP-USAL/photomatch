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
class INewSessionPresenter;
class IPreprocessPresenter;
class IPreprocessModel;

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
  void newSession();
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

  void openImage(const QString &image);
  void activeImage(const QString &image);
  void activeImages(const QStringList &images);
  void deleteImages(const QStringList &images);

  void loadSession(const QString &session);

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
   * \brief Inicializa la herramienta de creación de una nueva sesión
   */
  void initNewSessionDialog();

  /*!
   * \brief Inicializa la herramienta de configuración de la aplicación
   */
  void initSettingsDialog();

  /*!
   * \brief Inicializa la herramienta de preprocesado
   */
  void initPreprocessDialog();

protected:

  MainWindowView *mView;
  MainWindowModel *mModel;

  IProject *mProject;
  IProjectRW *mProjectIO;
  IProjectModel *mProjectModel;

  INewProjectPresenter *mNewProjectPresenter;

  INewSessionPresenter *mNewSessionPresenter;

  ISettings *mSettings;
  ISettingsRW *mSettingsRW;
  ISettingsModel *mSettingsModel;
  ISettingsPresenter *mSettingsPresenter;

  IPreprocessModel *mPreprocessModel;
  IPreprocessPresenter *mPreprocessPresenter;

};

} // namespace fme

#endif // MAINWINDOWPRESENTER_H
