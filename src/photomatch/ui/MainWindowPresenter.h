#ifndef MAINWINDOWPRESENTER_H
#define MAINWINDOWPRESENTER_H

#include "mvp.h"

class QTextEdit;

namespace photomatch
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
class IHomographyViewerPresenter;
class IHomographyViewerModel;
class ICurvesViewerPresenter;
class ICurvesViewerModel;
class IGroundTruthModel;
class IGroundTruthPresenter;
class IRepeatabilityModel;
class IRepeatabilityPresenter;
class IFeaturesViewerModel;
class IFeaturesViewerPresenter;
class IExportFeaturesModel;
class IExportFeaturesPresenter;
class IExportMatchesModel;
class IExportMatchesPresenter;
//class IBatchModel;
//class IBatchPresenter;
class ProgressHandler;
class IProgressDialog;
class AboutDialog;
class HelpDialog;

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
  void exportFeatures();
  void exportMatches();

  void closeProject();
  void exit();

  void openSettings();

  /* Menú View */

  void openViewSettings();

  /* Quality Control */

  void openKeypointsViewer();
  void openKeypointsViewer(const QString &session, const QString &image);
  void openMatchesViewer();
  void openMatchesViewer(const QString &session, const QString &imageLeft, const QString &imageRight = QString());
  void groundTruthEditor();
  void openHomographyViewer();
  void openRepeatability();
  void openPRCurvesViewer();
  void openROCCurvesViewer();
  void openDETCurvesViewer();
  void openQualityControlSettings();

  /* Menú herramientas */

  void loadImages();
  void newSession();
  void openPreprocess();
  void openFeatureExtraction();
  void openFeatureMatching();
  //void openBatch();
  void openToolSettings();

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
  void deleteSession(const QString &sessionName);
  void deletePreprocess();
  void deleteFeatures();
  void deleteMatches();
  void groundTruthAdded();

  void processFinish();
  void processRunning();

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(std::shared_ptr<HelpDialog> &help) override;

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

  void initExportFeaturesDialog();
  void initExportMatchesDialog();

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

  /*!
   * \brief Inicializa la herramienta de matching
   */
  void initFeatureMatching();

  //void initBatch();

  void initProgress();

  /*!
   * \brief Inicializa el visor de puntos de interés
   */
  void initFeaturesViewer();

  /*!
   * \brief Inicializa el visor de matches
   */
  void initMatchesViewer();

  void initGroundTruthEditor();

  /*!
   * \brief Inicializa el visor de homografía
   */
  void initHomographyViewer();
  void initRepeatability();
  void initPRCurvesViewer();
  void initROCCurvesViewer();
  void initDETCurvesViewer();

  void initAboutDialog();
  void initHelpDialog();

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

  IExportFeaturesPresenter *mExportFeaturesPresenter;
  IExportFeaturesModel *mExportFeaturesModel;

  IExportMatchesPresenter *mExportMatchesPresenter;
  IExportMatchesModel *mExportMatchesModel;

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

  //IBatchModel *mBatchmodel;
  //IBatchPresenter *mBatchPresenter;

  IFeaturesViewerPresenter *mFeaturesViewerPresenter;
  IFeaturesViewerModel *mFeaturesViewerModel;

  IMatchViewerPresenter *mMatchesViewerPresenter;
  IMatchViewerModel *mMatchesViewerModel;

  IGroundTruthPresenter *mGroundTruthPresenter;
  IGroundTruthModel *mGroundTruthModel;

  IHomographyViewerPresenter *mHomographyViewerPresenter;
  IHomographyViewerModel *mHomographyViewerModel;

  ICurvesViewerPresenter *mCurvesPRViewerPresenter;
  ICurvesViewerModel *mCurvesPRViewerModel;
  ICurvesViewerPresenter *mCurvesROCViewerPresenter;
  ICurvesViewerModel *mCurvesROCViewerModel;
  ICurvesViewerPresenter *mCurvesDETViewerPresenter;
  ICurvesViewerModel *mCurvesDETViewerModel;

  IRepeatabilityPresenter *mRepeatabilityPresenter;
  IRepeatabilityModel *mRepeatabilityModel;

  AboutDialog *mAboutDialog;
  std::shared_ptr<HelpDialog> mHelpDialog;

  ProgressHandler *mProgressHandler;
  IProgressDialog *mProgressDialog;
  //QTextEdit *mConsole;
};

} // namespace photomatch

#endif // MAINWINDOWPRESENTER_H
