#ifndef MAINWINDOWPRESENTER_H
#define MAINWINDOWPRESENTER_H

#include "mvp.h"

class QTextEdit;

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
class IFeatureExtractorModel;
class IFeatureExtractorPresenter;
class IDescriptorMatcherModel;
class IDescriptorMatcherPresenter;
class IMatchViewerPresenter;
class IMatchViewerModel;
class ProgressHandler;
class IProgressDialog;


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
  void exportTiePointsCvXml();
  void exportTiePointsCvYml();
  void exportMatchesCvYml();
  void exportMatchesCvXml();
  void exportMatchesTxt();

  void closeProject();
  void exit();

  /* Menú View */

  /* Quality Control */

  void openMatchesViewer();

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
  void selectSession(const QString &session);
  void activeSession(const QString &session);
  void selectPreprocess(const QString &session);
  void selectFeatures(const QString &session);
  void selectDetector(const QString &session);
  void selectDescriptor(const QString &session);
  void selectImageFeatures(const QString &imageFeatures);
  void openImageMatches(const QString &sessionName, const QString &imgName1, const QString &imgName2);

  void updatePreprocess();
  void updateFeatures();
  void updateMatches();
  void loadKeyPoints(const QString &image);

  void processFinish();
  void processRunning();

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

  /*!
   * \brief Inicializa la herramienta de extracción de caracteristicas
   */
  void initFeatureExtractionDialog();

  void initFeatureMatching();

  void initProgress();

  void initMatchesViewer();

  bool loadPreprocess(const QString &session);
  bool loadFeatures(const QString &session);
  bool loadMatches(const QString &session);

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

  IFeatureExtractorModel *mFeatureExtractorModel;
  IFeatureExtractorPresenter *mFeatureExtractorPresenter;

  IDescriptorMatcherModel *mDescriptorMatcherModel;
  IDescriptorMatcherPresenter *mDescriptorMatcherPresenter;

  IMatchViewerPresenter *mMatchesViewerPresenter;
  IMatchViewerModel *mMatchesViewerModel;

  ProgressHandler *mProgressHandler;
  IProgressDialog *mProgressDialog;
  //QTextEdit *mConsole;
};

} // namespace fme

#endif // MAINWINDOWPRESENTER_H
