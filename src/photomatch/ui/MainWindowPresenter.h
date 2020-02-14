/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


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
class ProjectController;
class Project;
class Settings;
class SettingsController;
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
class IMultiViewModel;
class IMultiViewPresenter;
class ProgressHandler;
class IProgressDialog;
class AboutDialog;
class HelpDialog;
class TabHandler;
class StartPageWidget;

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

  void openStartPage();
  void openSettings();
  void openGitHub();

  /* Menú View */

  void openViewSettings();

  /* Quality Control */

  void openKeypointsViewer();
  void openKeypointsViewer(const QString &session, const QString &image);
  void openMatchesViewer();
  void openMatchesViewer(const QString &session, const QString &imageLeft, const QString &imageRight = QString());
  void openMultiviewMatchingAssessment();
  void openMultiviewMatchingAssessment(const QString &session);
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
  void openOnlineHelp();
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
  void deleteSession(const QString &sessionName);
  void deletePreprocess();
  void deleteFeatures();
  void deleteMatches();
  void groundTruthAdded();

  void processFinish();
  void processRunning();

  void onLoadImages();

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

  void initStartPage();

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

  void initMultiviewMatchingAssessment();

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

  Project *mProject;
  ProjectController *mProjectIO;
  IProjectModel *mProjectModel;

  INewProjectPresenter *mNewProjectPresenter;

  INewSessionPresenter *mNewSessionPresenter;

  IExportFeaturesPresenter *mExportFeaturesPresenter;
  IExportFeaturesModel *mExportFeaturesModel;

  IExportMatchesPresenter *mExportMatchesPresenter;
  IExportMatchesModel *mExportMatchesModel;

  Settings *mSettings;
  SettingsController *mSettingsRW;
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

  IMultiViewModel *mMultiviewModel;
  IMultiViewPresenter *mMultiviewPresenter;

  AboutDialog *mAboutDialog;
  std::shared_ptr<HelpDialog> mHelpDialog;

  ProgressHandler *mProgressHandler;
  IProgressDialog *mProgressDialog;

  TabHandler *mTabHandler;
  StartPageWidget *mStartPageWidget;

};

} // namespace photomatch

#endif // MAINWINDOWPRESENTER_H
