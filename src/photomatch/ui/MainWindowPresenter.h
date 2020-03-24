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


#ifndef PHOTOMATCH_MAIN_WINDOW_PRESENTER_H
#define PHOTOMATCH_MAIN_WINDOW_PRESENTER_H

#include "mvp.h"

class QTextEdit;

namespace photomatch
{

class MainWindowView;
class MainWindowModel;
class ProjectModel;
class SettingsModel;
class HelpDialog;
class TabHandler;
class StartPageWidget;

class MainWindowPresenter
  : public IPresenter
{
  Q_OBJECT

public:

  explicit MainWindowPresenter(MainWindowView *view,
                               MainWindowModel *model,
                               ProjectModel *projectModel,
                               SettingsModel *settingsModel);
  ~MainWindowPresenter() override;

signals:

  void openNewProjectDialog();
  void openNewSessionDialog();
  void openPreprocessDialog();
  void openFeatureExtractionDialog();
  void openFeatureMatchingDialog();
  void openKeypointsViewerDialogFromSession(QString);
  void openKeypointsViewerDialogFromSessionAndImage(QString, QString);
  void openMatchesViewerDialogFromSession(QString);
  void openMatchesViewerDialogFromSessionAndImages(QString, QString, QString);
  void openExportFeaturesDialog();
  void openExportMatchesDialog();
  void openGroundTruthEditorDialog();
  void openHomographyViewerDialog();
  void openMultiviewMatchingAssessmentDialog();
  void openPRCurvesViewerDialog();
  void openROCCurvesViewerDialog();
  void openDETCurvesViewerDialog();
  void openAboutDialog();
  void openSettingsDialog();
  void openViewSettingsDialog();
  void openQualityControlSettingsDialog();
  void openToolSettingsDialog();

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

  void openStartPage();
  void openGitHub();

  /* Quality Control */

  void openKeypointsViewer();
  void openMatchesViewer();

  /* Menú herramientas */

  void loadImages();

  /* Menú Ayuda */

  void openOnlineHelp();

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
  void setHelp(HelpDialog *help) override;

private:

  void init() override;
  void initStartPage();

  bool loadPreprocess(const QString &session);
  bool loadFeatures(const QString &session);
  bool loadMatches(const QString &session);

protected:

  MainWindowView *mView;
  MainWindowModel *mModel;
  ProjectModel *mProjectModel;
  SettingsModel *mSettingsModel;
  HelpDialog *mHelpDialog;
  TabHandler *mTabHandler;
  StartPageWidget *mStartPageWidget;

};

} // namespace photomatch

#endif // PHOTOMATCH_MAIN_WINDOW_PRESENTER_H
