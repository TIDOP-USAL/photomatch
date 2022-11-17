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


#ifndef PHOTOMATCH_MAINWINDOW_H
#define PHOTOMATCH_MAINWINDOW_H

#include <QMainWindow>

#include <tidop/core/flags.h>

namespace Ui {
class MainWindowView;
}

class QTreeWidget;
class QTreeWidgetItem;
class QComboBox;
class QProgressBar;
class QGridLayout;
class QLabel;

namespace photomatch
{

class ThumbnailsWidget;
class LogWidget;
class TabHandler;

class MainWindowView
  : public QMainWindow
{
  Q_OBJECT

public:

  enum class Flag
  {
    project_exists        = (1 << 0),  // Existe un proyecto
    project_modified      = (1 << 1),  // Se ha modificado el proyecto
    images_added          = (1 << 2),  // Se han añadido fotogramas
    image_open            = (1 << 3),  // Hay una imagen abierta
    session_created       = (1 << 4),
    preprocess            = (1 << 5),
    feature_extraction    = (1 << 6),
    feature_matching      = (1 << 7),
    processing            = (1 << 20),
    loading_images        = (1 << 21),
    ground_truth          = (1 << 30),
  };

public:

  explicit MainWindowView(QWidget *parent = nullptr);
  ~MainWindowView() override;

  void clear();

  /*!
   * \brief Establece el nombre del proyecto
   * \param[in] title Titulo del proyecto
   */
  void setProjectTitle(const QString &title);

  void setFlag(Flag flag, bool value);
  void addImages(const QStringList &images);
  void setActiveImage(const QString &image);
  void setActiveImages(const QStringList &images);
  void addSession(const QString &sessionName,
                  const QString &sessionDescription);
  void addPreprocess(const QString &sessionName,
                     const QString &preprocess,
                     const std::vector<QString> &preprocessImages);
  void addFeatures(const QString &sessionName,
                   const QString &detector,
                   const QString &descriptor,
                   const std::vector<QString> &features);
  void addMatches(const QString &sessionName,
                  const QString &matcher,
                  const QString &left,
                  const QString &right,
                  const QString &file);

  /*!
   * \brief Añade un mensaje temporal en la barra de herramientas
   * \param msg Mensaje
   */
  void setStatusBarMsg(const QString &msg);

  /*!
   * \brief Establece las propiedades del elemento seleccionado en el árbol de proyecto
   */
  void setProperties(const std::list<std::pair<QString, QString> > &properties);

  QProgressBar *progressBar();

  /*!
   * \brief Tab handler
   * \return
   */
  TabHandler *tabHandler();

public slots:

  /*!
   * \brief Actualiza el historial de proyectos recientes
   * \param[in] history Listado con las rutas de los últimos proyectos
   */
  void updateHistory(const QStringList &history);

  /*!
   * \brief Borra el historial de proyectos recientes
   */
  void deleteHistory();

  void deleteSession(const QString &session);

  /*!
   * \brief Elimina una imagen
   * \param[in] file
   */
  void deleteImage(const QString &file);
  void deletePreprocess(const QString &session,
                        const QString &preprocess);
  void deleteFeatures(const QString &session,
                      const QString &feat);
  void deleteMatches(const QString &session,
                     const QString &matches);
  void setActiveSession(const QString &session);

signals:

  /* Menu File */

  void openNew();
  void openProject();
  void openProjectFromHistory(QString);
  void clearHistory();
  void saveProject();
  void saveProjectAs();
  void openExportFeatures();
  void openExportMatches();
  void closeProject();
  void exit();
  void openSettings();

  /* Menu View */

  void openStartPage();
  void openViewSettings();

  /* Menú herramientas */

  void loadImages();
  void newSession();
  void openPreprocess();
  void openFeatureExtraction();
  void openFeatureMatching();
  void openBatch();
  void openToolSettings();

  /* Quality Control */

  void openKeypointsViewer();
  void openMatchesViewer();
  void openMultiviewMatchingAssessment();
  void groundTruthEditor();
  void homography();
  void evaluation();
  void repeatability();
  void prCurves();
  void rocCurves();
  void detCurves();
  void openQualityControlSettings();

  /* Menú Ayuda */

  void openHelpDialog();
  void openOnlineHelp();
  void openAboutDialog();

  /* Panel de vistas en miniatura */

  ///TODO: asegurarse que se utiliza siempre el mismo criterio como id de la imagen
  ///      O nombre de la imagen o ruta completa
  void openImage(QString);
  void selectImage(QString);
  void selectImages(QStringList);
  void deleteImages(QStringList);
  void selectSession(QString);
  void selectPreprocess(QString);
  void selectFeatures(QString);
  void selectDetector(QString);
  void selectDescriptor(QString);
  void selectImageFeatures(QString);
  void imagesLoaded();

  void openImageMatches(QString, QString, QString);

  void activeSessionChange(QString);
  void delete_session(QString);

  void openKeypointsViewer(QString, QString);
  void openMatchesViewer(QString, QString, QString);
  void openMultiView(QString);

protected:

  void changeEvent(QEvent *e) override;

private slots:

  void update();
  void retranslate();

  void openFromHistory();
  void onSelectionChanged();
  void onItemDoubleClicked(QTreeWidgetItem *item, int column);
  void onTreeContextMenu(const QPoint &point);

private:

  void initActions();
  void initActionNewProject();
  void initActionOpenProject();
  void initActionSaveProject();
  void initActionSaveProjectAs();
  void initActionCloseProject();
  void initActionExit();
  void initActionStartPage();
  void initActionViewSettings();
  void initActionLoadImages();
  void initActionNewSession();
  void initActionPreprocess();
  void initActionFeatureExtraction();
  void initActionFeatureMatching();
  void initActionBatch();
  void initActionToolsSettings();
  void initActionHelp();
  void initActionOnlineHelp();
  void initActionAbout();
  void initActionRepeatability();
  void initActionExportTiePoints();
  void initActionExportMatches();
  void initActionFeaturesViewer();
  void initActionMatchesViewer();
  void initActionPassPointsViewer();
  void initActionGroundTruthEditor();
  void initActionHomography();
  void initActionEvaluation();
  void initActionPRCurves();
  void initActionROCCurves();
  void initActionDETCurves();
  void initActionQualityControlSettings();
  void initActionNotRecentProjects();
  void initActionClearHistory();
  void initActionsetSession();
  void initActionDeleteSession();
  void initUI();
  void initTabHandler();
  void initThumbnailsTool();
  void initConsole();
  void initToolbars();
  void initToolbarFile();
  void initToolbarTools();
  void initToolbarView();
  void initQualityControl();
  void initTreeWidget();
  void initMenus();
  void initMenuFile();
  void initMenuView();
  void initMenuTools();
  void initMenuQualityControl();
  void initMenuHelp();
  void initProgressBar();
  void connectSignalAndSlots();

// QWidget interface

public:

  void closeEvent(QCloseEvent *event) override;

protected:

  QTreeWidget *mTreeWidgetProject;
  QAction *mActionNewProject;
  QAction *mActionOpenProject;
  QAction *mActionSaveProject;
  QAction *mActionSaveProjectAs;
  QAction *mActionCloseProject;
  QAction *mActionExit;
  QAction *mActionStartPage;
  QAction *mActionLoadImages;
  QAction *mActionNewSession;
  QAction *mActionPreprocess;
  QAction *mActionFeatureExtraction;
  QAction *mActionFeatureMatching;
  QAction *mActionBatch;
  QAction *mActionViewSettings;
  QAction *mActionToolSettings;
  QAction *mActionHelp;
  QAction *mActionOnlineHelp;
  QAction *mActionAbout;
  QAction *mActionExportTiePoints;
  QAction *mActionExportMatches;
  QAction *mActionFeaturesViewer;
  QAction *mActionMatchesViewer;
  QAction *mActionPassPointsViewer;
  QAction *mActionGroundTruthEditor;
  QAction *mActionHomography;
  QAction *mActionEvaluation;
  //QAction *mActionRepeatability;
  QAction *mActionPRCurves;
  QAction *mActionROCCurves;
  QAction *mActionDETCurves;
  QAction *mActionQualityControlSettings;
  QAction *mActionNotRecentProjects;
  QAction *mActionClearHistory;
  QAction *mActionSetSession;
  QAction *mActionDeleteSession;
  QMenu *mMenuRecentProjects;
  QMenu *mMenuExport;
  QMenu* mMenuPanels;
  QMenu* mMenuToolBar;
  ThumbnailsWidget *mThumbnailsWidget;
  LogWidget *mLogWidget;
  QWidget *mStartPageWidget;
  QLabel *mLabelActiveSession;
  QComboBox *mComboBoxActiveSession;
  QProgressBar *mProgressBar;

  tl::EnumFlags<Flag> mFlags;
  std::vector<QAction*> mHistory;
  QGridLayout *mLayoutCentral;
  TabHandler *mTabHandler;

private:

  Ui::MainWindowView *ui;
};

ALLOW_BITWISE_FLAG_OPERATIONS(MainWindowView::Flag)

} // namespace photomatch

#endif // PHOTOMATCH_MAINWINDOW_H
