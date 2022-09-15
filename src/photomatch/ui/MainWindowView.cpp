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


#include "MainWindowView.h"
#include "ui_MainWindowView.h"

#include "photomatch/widgets/ThumbnailsWidget.h"
#include "photomatch/widgets/LogWidget.h"
#include "photomatch/ui/utils/TabHandler.h"

#include <QTreeWidgetItem>
#include <QFileInfo>
#include <QSettings>
#include <QGraphicsEllipseItem>
#include <QDesktopServices>
#include <QUrl>
#include <QComboBox>
#include <QProgressBar>
#include <QLabel>

namespace photomatch
{

enum
{
  project,
  images,
  image,
  sessions,
  session,
  preprocess,
  preprocess_images,
  preprocess_image,
  features,
  features_images,
  features_image,
  detector,
  descriptor,
  matches,
  descriptor_matcher,
  matches_pairs,
  pair_left,
  pair_right
};

MainWindowView::MainWindowView(QWidget *parent)
  : QMainWindow(parent),
    mLabelActiveSession(new QLabel(this)),
    mComboBoxActiveSession(new QComboBox(this)),
    ui(new Ui::MainWindowView)
{
  this->initActions();
  this->initUI();
  this->connectSignalAndSlots();
}

void MainWindowView::initActions()
{
  this->initActionNewProject();
  this->initActionOpenProject();
  this->initActionSaveProject();
  this->initActionSaveProjectAs();
  this->initActionCloseProject();
  this->initActionExit();
  this->initActionStartPage();
  this->initActionViewSettings();
  this->initActionLoadImages();
  this->initActionNewSession();
  this->initActionPreprocess();
  this->initActionFeatureExtraction();
  this->initActionFeatureMatching();
  this->initActionBatch();
  this->initActionToolsSettings();
  this->initActionHelp();
  this->initActionOnlineHelp();
  this->initActionAbout();
  this->initActionRepeatability();
  this->initActionExportTiePoints();
  this->initActionExportMatches();
  this->initActionFeaturesViewer();
  this->initActionMatchesViewer();
  this->initActionPassPointsViewer();
  this->initActionGroundTruthEditor();
  this->initActionHomography();
  this->initActionPRCurves();
  this->initActionROCCurves();
  this->initActionDETCurves();
  this->initActionQualityControlSettings();
  this->initActionNotRecentProjects();
  this->initActionClearHistory();
  this->initActionsetSession();
  this->initActionDeleteSession();
}

void MainWindowView::initActionNewProject()
{
  mActionNewProject = new QAction(this);
  QIcon iconNewProject;
  iconNewProject.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_file_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionNewProject->setIcon(iconNewProject);
}

void MainWindowView::initActionOpenProject()
{
  mActionOpenProject = new QAction(this);
  QIcon iconOpenProject;
  iconOpenProject.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_opened_folder_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionOpenProject->setIcon(iconOpenProject);
}

void MainWindowView::initActionSaveProject()
{
  mActionSaveProject = new QAction(this);
  QIcon iconSaveProject;
  iconSaveProject.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_save_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionSaveProject->setIcon(iconSaveProject);
}

void MainWindowView::initActionSaveProjectAs()
{
  mActionSaveProjectAs = new QAction(this);
  QIcon iconSaveProjectAs;
  iconSaveProjectAs.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_save_as_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionSaveProjectAs->setIcon(iconSaveProjectAs);
}

void MainWindowView::initActionCloseProject()
{
  mActionCloseProject = new QAction(this);
  QIcon icon4;
  icon4.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_delete_sign_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionCloseProject->setIcon(icon4);
}

void MainWindowView::initActionExit()
{
  mActionExit = new QAction(this);
  QIcon iconExit;
  iconExit.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_shutdown_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionExit->setIcon(iconExit);
}

void MainWindowView::initActionStartPage()
{
  mActionStartPage = new QAction(this);
  QIcon iconStartPage;
  iconStartPage.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_home_page_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionStartPage->setIcon(iconStartPage);
}

void MainWindowView::initActionViewSettings()
{
  mActionViewSettings = new QAction(this);
  QIcon iconSettingsView;
  iconSettingsView.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_automatic_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionViewSettings->setIcon(iconSettingsView);
}

void MainWindowView::initActionLoadImages()
{
  mActionLoadImages = new QAction(this);
  QIcon iconLoadImages;
  iconLoadImages.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_images_folder_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionLoadImages->setIcon(iconLoadImages);
}

void MainWindowView::initActionNewSession()
{
  mActionNewSession = new QAction(this);
  QIcon iconNewSession;
  iconNewSession.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_add_list_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionNewSession->setIcon(iconNewSession);
}

void MainWindowView::initActionPreprocess()
{
  mActionPreprocess = new QAction(this);
  QIcon iconPreprocess;
  iconPreprocess.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_services_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionPreprocess->setIcon(iconPreprocess);
}

void MainWindowView::initActionFeatureExtraction()
{
  mActionFeatureExtraction = new QAction(this);
  QIcon iconFeatureExtraction;
  iconFeatureExtraction.addFile(QStringLiteral(":/ico/24/img/material/24/features.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionFeatureExtraction->setIcon(iconFeatureExtraction);
}

void MainWindowView::initActionFeatureMatching()
{
  mActionFeatureMatching = new QAction(this);
  QIcon iconFeatureMatching;
  iconFeatureMatching.addFile(QStringLiteral(":/ico/24/img/material/24/match_view.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionFeatureMatching->setIcon(iconFeatureMatching);
}

void MainWindowView::initActionBatch()
{
  //mActionBatch = new QAction(this);
  //mActionBatch->setText(QApplication::translate("MainWindowView", "Batch", nullptr));
}

void MainWindowView::initActionToolsSettings()
{
  mActionToolSettings = new QAction(this);
  QIcon iconSettings;
  iconSettings.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_automatic_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionToolSettings->setIcon(iconSettings);
}

void MainWindowView::initActionHelp()
{
  mActionHelp = new QAction(this);
  QIcon iconHelp;
  iconHelp.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_help_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionHelp->setIcon(iconHelp);
}

void MainWindowView::initActionOnlineHelp()
{
  mActionOnlineHelp = new QAction(this);
  QIcon iconOnlineHelp;
  iconOnlineHelp.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_help_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionOnlineHelp->setIcon(iconOnlineHelp);
}

void MainWindowView::initActionAbout()
{
  mActionAbout = new QAction(this);
  QIcon iconAbout;
  iconAbout.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_about_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionAbout->setIcon(iconAbout);
}

void MainWindowView::initActionRepeatability()
{
  //mActionRepeatability = new QAction(this);
  //mActionRepeatability->setText(QApplication::translate("MainWindowView", "Repeatability", nullptr));
}

void MainWindowView::initActionExportTiePoints()
{
  mActionExportTiePoints = new QAction(this);
}

void MainWindowView::initActionExportMatches()
{
  mActionExportMatches = new QAction(this);
}

void MainWindowView::initActionFeaturesViewer()
{
  mActionFeaturesViewer = new QAction(this);
  QIcon iconFeaturesViewer;
  iconFeaturesViewer.addFile(QStringLiteral(":/ico/24/img/material/24/points_viewer.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionFeaturesViewer->setIcon(iconFeaturesViewer);
}

void MainWindowView::initActionMatchesViewer()
{
  mActionMatchesViewer = new QAction(this);
  QIcon iconMatchesViewer;
  iconMatchesViewer.addFile(QStringLiteral(":/ico/24/img/material/24/match_viewer.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionMatchesViewer->setIcon(iconMatchesViewer);
}

void MainWindowView::initActionPassPointsViewer()
{
  mActionPassPointsViewer = new QAction(this);
}

void MainWindowView::initActionGroundTruthEditor()
{
  mActionGroundTruthEditor = new QAction(this);
}

void MainWindowView::initActionHomography()
{
  mActionHomography = new QAction(this);
}

void MainWindowView::initActionPRCurves()
{
  mActionPRCurves = new QAction(this);
  QIcon iconPRCurves;
  iconPRCurves.addFile(QStringLiteral(":/ico/24/img/material/24/pr_curve_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionPRCurves->setIcon(iconPRCurves);
}

void MainWindowView::initActionROCCurves()
{
  mActionROCCurves = new QAction(this);
  QIcon iconROCCurves;
  iconROCCurves.addFile(QStringLiteral(":/ico/24/img/material/24/roc_curve_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionROCCurves->setIcon(iconROCCurves);
}

void MainWindowView::initActionDETCurves()
{
  mActionDETCurves = new QAction(this);
  QIcon iconDETCurves;
  iconDETCurves.addFile(QStringLiteral(":/ico/24/img/material/24/det_curve_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionDETCurves->setIcon(iconDETCurves);
}

void MainWindowView::initActionQualityControlSettings()
{
  mActionQualityControlSettings = new QAction(this);
  QIcon iconQualityControlSettings;
  iconQualityControlSettings.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_automatic_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionQualityControlSettings->setIcon(iconQualityControlSettings);
}

void MainWindowView::initActionNotRecentProjects()
{
  mActionNotRecentProjects = new QAction(this);
  mActionNotRecentProjects->setEnabled(false);
}

void MainWindowView::initActionClearHistory()
{
  mActionClearHistory = new QAction(this);
  QIcon icon_delete_trash;
  icon_delete_trash.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_delete_trash_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionClearHistory->setIcon(icon_delete_trash);
}

void MainWindowView::initActionsetSession()
{
  mActionSetSession = new QAction(this);
}

void MainWindowView::initActionDeleteSession()
{
  mActionDeleteSession = new QAction(this);
  QIcon iconDeleteSession;
  iconDeleteSession.addFile(QStringLiteral(":/ico/24/img/material/24/delete_list_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionDeleteSession->setIcon(iconDeleteSession);
}

void MainWindowView::initUI()
{
  ui->setupUi(this);

  setWindowTitle(QString("PhotoMatch"));

  mLayoutCentral = new QGridLayout(this->centralWidget());
  mLayoutCentral->setSpacing(6);
  mLayoutCentral->setContentsMargins(0, 0, 0, 0);

  this->initTabHandler();
  this->initThumbnailsTool();
  this->initConsole();
  this->initToolbars();
  this->initTreeWidget();
  this->initMenus();
  this->initProgressBar();

  // Configuración de mensajes
  tl::MessageManager &msg_h = tl::MessageManager::instance();
  msg_h.addListener(mLogWidget);

  this->retranslate();
  this->update();
}

void MainWindowView::initTabHandler()
{
  mTabHandler = new TabHandler(this->centralWidget());
  mLayoutCentral->addWidget(mTabHandler);
}

void MainWindowView::initThumbnailsTool()
{
  QGridLayout* gridLayoutThumb = new QGridLayout(ui->dockWidgetThumbContents);
  gridLayoutThumb->setSpacing(6);
  gridLayoutThumb->setContentsMargins(11, 11, 11, 11);
  gridLayoutThumb->setContentsMargins(0, 0, 0, 0);
  mThumbnailsWidget = new ThumbnailsWidget(ui->dockWidgetThumbContents);
  gridLayoutThumb->addWidget(mThumbnailsWidget, 0, 0, 1, 1);
}

void MainWindowView::initConsole()
{
  QGridLayout* gridLayoutConsole = new QGridLayout(ui->dockWidgetContentsConsole);
  gridLayoutConsole->setSpacing(6);
  gridLayoutConsole->setContentsMargins(11, 11, 11, 11);
  gridLayoutConsole->setContentsMargins(0, 0, 0, 0);
  mLogWidget = new LogWidget(ui->dockWidgetThumbContents);
  gridLayoutConsole->addWidget(mLogWidget, 0, 0, 1, 1);
}

void MainWindowView::initToolbars()
{
  this->initToolbarFile();
  this->initToolbarTools();
  this->initToolbarView();
  this->initQualityControl();
}

void MainWindowView::initToolbarFile()
{
  ui->mainToolBar->addAction(mActionNewProject);
  ui->mainToolBar->addAction(mActionOpenProject);
  ui->mainToolBar->addAction(mActionSaveProject);
  ui->mainToolBar->addAction(mActionSaveProjectAs);
}

void MainWindowView::initToolbarTools()
{
  ui->toolBarTools->addAction(mActionLoadImages);
  ui->toolBarTools->addSeparator();
  ui->toolBarTools->addAction(mActionNewSession);
  ui->toolBarTools->addSeparator();
  ui->toolBarTools->addWidget(mLabelActiveSession);
  mComboBoxActiveSession->setMinimumWidth(100);
  mComboBoxActiveSession->setContentsMargins(8, 0, 0, 0);
  ui->toolBarTools->addWidget(mComboBoxActiveSession);
  ui->toolBarTools->addSeparator();
  ui->toolBarTools->addAction(mActionPreprocess);
  ui->toolBarTools->addAction(mActionFeatureExtraction);
  ui->toolBarTools->addAction(mActionFeatureMatching);
  //  ui->toolBarTools->addSeparator();
  //  ui->toolBarTools->addAction(mActionBatch);
}

void MainWindowView::initToolbarView()
{
  ui->toolBarView->addAction(mTabHandler->actionZoomIn());
  ui->toolBarView->addAction(mTabHandler->actionZoomOut());
  ui->toolBarView->addAction(mTabHandler->actionZoom11());
  ui->toolBarView->addAction(mTabHandler->actionZoomExtend());
}

void MainWindowView::initQualityControl()
{
  ui->toolBarQualityControl->addAction(mActionFeaturesViewer);
  ui->toolBarQualityControl->addAction(mActionMatchesViewer);
  ui->toolBarQualityControl->addSeparator();
  //ui->toolBarQualityControl->addAction(mActionPRCurves);
  ui->toolBarQualityControl->addAction(mActionROCCurves);
  ui->toolBarQualityControl->addAction(mActionDETCurves);
}

void MainWindowView::initTreeWidget()
{
  mTreeWidgetProject = new QTreeWidget(ui->dockWidgetContentsProject);
  mTreeWidgetProject->setContextMenuPolicy(Qt::CustomContextMenu);
  mTreeWidgetProject->header()->close();
  mTreeWidgetProject->setColumnCount(1);
  mTreeWidgetProject->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
  mTreeWidgetProject->header()->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
  mTreeWidgetProject->header()->setStretchLastSection(false);
  ui->gridLayout->addWidget(mTreeWidgetProject, 0, 0, 1, 1);
}

void MainWindowView::initMenus()
{
  this->initMenuFile();
  this->initMenuView();
  this->initMenuTools();
  this->initMenuQualityControl();
  this->initMenuHelp();
}

void MainWindowView::initMenuFile()
{
  ui->menuFile->addAction(mActionNewProject);
  ui->menuFile->addAction(mActionOpenProject);
  mMenuRecentProjects = new QMenu(this);
  mMenuRecentProjects->addAction(mActionNotRecentProjects);
  mMenuRecentProjects->addSeparator();
  mMenuRecentProjects->addAction(mActionClearHistory);
  ui->menuFile->addMenu(mMenuRecentProjects);
  ui->menuFile->addSeparator();
  ui->menuFile->addAction(mActionSaveProject);
  ui->menuFile->addAction(mActionSaveProjectAs);
  ui->menuFile->addSeparator();
  mMenuExport = new QMenu(this);
  mMenuExport->addAction(mActionExportTiePoints);
  mMenuExport->addAction(mActionExportMatches);
  ui->menuFile->addMenu(mMenuExport);
  ui->menuFile->addSeparator();
  ui->menuFile->addAction(mActionCloseProject);
  ui->menuFile->addSeparator();
  ui->menuFile->addAction(mActionExit);
}

void MainWindowView::initMenuView()
{
  ui->menuView->addAction(mActionStartPage);
  ui->menuView->addSeparator();
  mMenuPanels = new QMenu(this);
  mMenuPanels->setIcon(QIcon(":/ico/24/img/material/24/icons8_navigation_toolbar_left_24px.png"));
  mMenuPanels->addAction(ui->dockWidgetProject->toggleViewAction());
  mMenuPanels->addAction(ui->dockWidgetProperties->toggleViewAction());
  mMenuPanels->addAction(ui->dockWidgetConsole->toggleViewAction());
  mMenuPanels->addAction(ui->dockWidgetThumb->toggleViewAction());
  ui->menuView->addMenu(mMenuPanels);

  ui->menuView->addSeparator();

  mMenuToolBar = new QMenu(this);
  mMenuToolBar->setIcon(QIcon(":/ico/24/img/material/24/icons8_navigation_toolbar_top_24px.png"));
  mMenuToolBar->addAction(ui->mainToolBar->toggleViewAction());
  mMenuToolBar->addAction(ui->toolBarTools->toggleViewAction());
  mMenuToolBar->addAction(ui->toolBarView->toggleViewAction());
  mMenuToolBar->addAction(ui->toolBarQualityControl->toggleViewAction());
  ui->menuView->addMenu(mMenuToolBar);

  ui->menuView->addSeparator();

  ui->menuView->addAction(mActionViewSettings);
}

void MainWindowView::initMenuTools()
{
  ui->menuTools->addAction(mActionLoadImages);
  ui->menuTools->addSeparator();
  ui->menuTools->addAction(mActionNewSession);
  ui->menuTools->addSeparator();
  ui->menuTools->addAction(mActionPreprocess);
  ui->menuTools->addAction(mActionFeatureExtraction);
  ui->menuTools->addAction(mActionFeatureMatching);
  ui->menuTools->addSeparator();
  //ui->menuTools->addAction(mActionBatch);
  //ui->menuTools->addSeparator();
  ui->menuTools->addAction(mActionToolSettings);
}

void MainWindowView::initMenuQualityControl()
{
  ui->menuQualityControl->addAction(mActionFeaturesViewer);
  ui->menuQualityControl->addAction(mActionMatchesViewer);
  ui->menuQualityControl->addAction(mActionPassPointsViewer);
  ui->menuQualityControl->addSeparator();
  ui->menuQualityControl->addAction(mActionGroundTruthEditor);
  ui->menuQualityControl->addSeparator();
  ui->menuQualityControl->addAction(mActionHomography);
  //ui->menuQualityControl->addAction(mActionRepeatability);
  //ui->menuQualityControl->addAction(mActionPRCurves);
  ui->menuQualityControl->addAction(mActionROCCurves);
  ui->menuQualityControl->addAction(mActionDETCurves);
  ui->menuQualityControl->addSeparator();
  ui->menuQualityControl->addAction(mActionQualityControlSettings);
}

void MainWindowView::initMenuHelp()
{
  ui->menuHelp->addAction(mActionHelp);
  ui->menuHelp->addAction(mActionOnlineHelp);
  ui->menuHelp->addSeparator();
  ui->menuHelp->addAction(mActionAbout);
}

void MainWindowView::initProgressBar()
{
  mProgressBar = new QProgressBar(this);
  mProgressBar->setVisible(false);
  mProgressBar->setMaximumSize(150, 20);
  ui->statusBar->addPermanentWidget(mProgressBar);
}

void MainWindowView::connectSignalAndSlots()
{
  /* Menú Archivo */

  connect(mActionNewProject, SIGNAL(triggered(bool)), this, SIGNAL(openNew()));
  connect(mActionOpenProject, SIGNAL(triggered(bool)), this, SIGNAL(openProject()));
  connect(mActionClearHistory, SIGNAL(triggered(bool)), this, SIGNAL(clearHistory()));
  connect(mActionSaveProject, SIGNAL(triggered(bool)), this, SIGNAL(saveProject()));
  connect(mActionSaveProjectAs, SIGNAL(triggered(bool)), this, SIGNAL(saveProjectAs()));
  connect(mActionExportTiePoints, SIGNAL(triggered(bool)), this, SIGNAL(openExportFeatures()));
  connect(mActionExportMatches, SIGNAL(triggered(bool)), this, SIGNAL(openExportMatches()));
  connect(mActionCloseProject, SIGNAL(triggered(bool)), this, SIGNAL(closeProject()));
  connect(mActionExit, SIGNAL(triggered(bool)), this, SIGNAL(exit()));

  /* Menú View */

  connect(mActionStartPage, SIGNAL(triggered(bool)), this, SIGNAL(openStartPage()));
  connect(mActionViewSettings, SIGNAL(triggered(bool)), this, SIGNAL(openViewSettings()));

  /* Menú herramientas */

  connect(mActionLoadImages, SIGNAL(triggered(bool)), this, SIGNAL(loadImages()));
  connect(mActionNewSession, SIGNAL(triggered(bool)), this, SIGNAL(newSession()));
  connect(mActionPreprocess, SIGNAL(triggered(bool)), this, SIGNAL(openPreprocess()));
  connect(mActionFeatureExtraction, SIGNAL(triggered(bool)), this, SIGNAL(openFeatureExtraction()));
  connect(mActionFeatureMatching, SIGNAL(triggered(bool)), this, SIGNAL(openFeatureMatching()));
  //connect(mActionBatch,              SIGNAL(triggered(bool)),   this,   SIGNAL(openBatch()));
  connect(mActionToolSettings, SIGNAL(triggered(bool)), this, SIGNAL(openToolSettings()));

  /* Quality Control */

  connect(mActionFeaturesViewer, SIGNAL(triggered(bool)), this, SIGNAL(openKeypointsViewer()));
  connect(mActionMatchesViewer, SIGNAL(triggered(bool)), this, SIGNAL(openMatchesViewer()));
  connect(mActionPassPointsViewer, SIGNAL(triggered(bool)), this, SIGNAL(openMultiviewMatchingAssessment()));
  connect(mActionGroundTruthEditor, SIGNAL(triggered(bool)), this, SIGNAL(groundTruthEditor()));
  connect(mActionHomography, SIGNAL(triggered(bool)), this, SIGNAL(homography()));
  //connect(mActionRepeatability,      SIGNAL(triggered(bool)),   this,   SIGNAL(repeatability()));
  connect(mActionPRCurves, SIGNAL(triggered(bool)), this, SIGNAL(prCurves()));
  connect(mActionROCCurves, SIGNAL(triggered(bool)), this, SIGNAL(rocCurves()));
  connect(mActionDETCurves, SIGNAL(triggered(bool)), this, SIGNAL(detCurves()));
  connect(mActionQualityControlSettings, SIGNAL(triggered(bool)), this, SIGNAL(openQualityControlSettings()));


  /* Menú Ayuda */

  connect(mActionHelp, SIGNAL(triggered(bool)), this, SIGNAL(openHelpDialog()));
  connect(mActionOnlineHelp, SIGNAL(triggered(bool)), this, SIGNAL(openOnlineHelp()));
  connect(mActionAbout, SIGNAL(triggered(bool)), this, SIGNAL(openAboutDialog()));

  /* Panel de vistas en miniatura */

  connect(mThumbnailsWidget, SIGNAL(openImage(QString)), this, SIGNAL(openImage(QString)));
  connect(mThumbnailsWidget, SIGNAL(selectImage(QString)), this, SIGNAL(selectImage(QString)));
  connect(mThumbnailsWidget, SIGNAL(selectImages(QStringList)), this, SIGNAL(selectImages(QStringList)));
  connect(mThumbnailsWidget, SIGNAL(deleteImages(QStringList)), this, SIGNAL(deleteImages(QStringList)));
  connect(mThumbnailsWidget, SIGNAL(imagesLoaded()), this, SIGNAL(imagesLoaded()));

  connect(mTreeWidgetProject, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onTreeContextMenu(const QPoint &)));
  connect(mTreeWidgetProject, SIGNAL(itemSelectionChanged()), this, SLOT(onSelectionChanged()));
  connect(mTreeWidgetProject, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(onItemDoubleClicked(QTreeWidgetItem *, int)));

  connect(mComboBoxActiveSession, SIGNAL(currentTextChanged(QString)), this, SIGNAL(activeSessionChange(QString)));

}

MainWindowView::~MainWindowView()
{
  delete ui;
}

void MainWindowView::clear()
{
  setWindowTitle(QString("PhotoMatch"));
  const QSignalBlocker blockerTreeWidgetProject(mTreeWidgetProject);
  mTreeWidgetProject->clear();
  const QSignalBlocker blockerThumbnailsWidget(mThumbnailsWidget);
  mThumbnailsWidget->clear();
  ui->treeWidgetProperties->clear();
  mFlags.clear();
  const QSignalBlocker blockerComboBoxActiveSession(mComboBoxActiveSession);
  mComboBoxActiveSession->clear();

  if (mTabHandler) mTabHandler->clear();

  update();
}

void MainWindowView::setProjectTitle(const QString &title)
{
  this->setWindowTitle(QString("PhotoMatch - ").append(title));

  QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0);
  if (itemProject == nullptr) {
    itemProject = new QTreeWidgetItem();
    //itemProject->setIcon(0, QIcon(":/ico/img/48x48/icons8_file_48px.png"));
    mTreeWidgetProject->addTopLevelItem(itemProject);
    itemProject->setExpanded(true);
    itemProject->setData(0, Qt::UserRole, photomatch::project);
  }

  itemProject->setText(0, tr("Project: ").append(title));
}

void MainWindowView::setFlag(MainWindowView::Flag flag, bool value)
{
  mFlags.activeFlag(flag, value);
  update();
}

void MainWindowView::addImages(const QStringList &images)
{
  if (images.empty() == false) {
    for (auto &image : images) {
      if (QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0)) {

        /* Fotogramas */

        QTreeWidgetItem *itemImages = nullptr;
        for (int i = 0; i < itemProject->childCount(); i++) {
          QTreeWidgetItem *temp = itemProject->child(i);
          if (temp->text(0).compare(tr("Images")) == 0) {
            itemImages = itemProject->child(i);
            break;
          }
        }

        if (itemImages == nullptr) {
          itemImages = new QTreeWidgetItem();
          itemImages->setText(0, tr("Images"));
          itemImages->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_documents_folder_48px.png"));
          itemImages->setFlags(itemImages->flags() | Qt::ItemIsTristate);
          itemImages->setData(0, Qt::UserRole, photomatch::images);
          itemProject->addChild(itemImages);
          itemImages->setExpanded(true);
        }

        /* Se añade el fotograma al árbol del proyecto */
        QTreeWidgetItem *itemPhotogram = new QTreeWidgetItem();
        itemPhotogram->setText(0, QFileInfo(image).baseName());
        itemPhotogram->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_image_48px.png"));
        itemPhotogram->setToolTip(0, image);
        itemPhotogram->setData(0, Qt::UserRole, photomatch::image);
        itemImages->addChild(itemPhotogram);

        update();
      }
    }

    mThumbnailsWidget->addThumbnails(images);

  }
}

void MainWindowView::setActiveImage(const QString &image)
{
  const QSignalBlocker blocker1(mTreeWidgetProject);
  const QSignalBlocker blocker2(mThumbnailsWidget);

  if (QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0)) {

    QTreeWidgetItem *itemImages = nullptr;
    for (int i = 0; i < itemProject->childCount(); i++) {
      QTreeWidgetItem *temp = itemProject->child(i);
      if (temp->text(0).compare(tr("Images")) == 0) {
        itemImages = itemProject->child(i);
        break;
      }
    }

    if (itemImages) {
      // Se busca la imagen en el árbol
      for (int i = 0; i < itemImages->childCount(); i++) {
        QTreeWidgetItem *temp = itemImages->child(i);
        itemImages->child(i)->setSelected(temp->text(0).compare(image) == 0);
      }
    }
  }

  mThumbnailsWidget->setActiveImage(image);

}

void MainWindowView::setActiveImages(const QStringList &images)
{
  const QSignalBlocker blocker1(mTreeWidgetProject);
  const QSignalBlocker blocker2(mThumbnailsWidget);

  if (QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0)) {

    QTreeWidgetItem *itemImages = nullptr;
    for (int i = 0; i < itemProject->childCount(); i++) {
      QTreeWidgetItem *temp = itemProject->child(i);
      if (temp->text(0).compare(tr("Images")) == 0) {
        itemImages = itemProject->child(i);
        break;
      }
    }

    if (itemImages) {
      // Se busca la imagen en el árbol
      for (int i = 0; i < itemImages->childCount(); i++) {
        QTreeWidgetItem *temp = itemImages->child(i);
        temp->setSelected(false);
        for (auto &image : images){
          if (temp->text(0).compare(image) == 0){
            temp->setSelected(true);
            break;
          }
        }
      }
    }
  }

  mThumbnailsWidget->setActiveImages(images);
}

void MainWindowView::addSession(const QString &sessionName, const QString &sessionDescription)
{
  const QSignalBlocker blocker(mComboBoxActiveSession);

  int id = mComboBoxActiveSession->findText(sessionName);
  if (id == -1){
    mComboBoxActiveSession->addItem(sessionName);
  }

  if (QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0)) {

    /* Sessions */

    QTreeWidgetItem *itemSessions = nullptr;
    for (int i = 0; i < itemProject->childCount(); i++) {
      QTreeWidgetItem *temp = itemProject->child(i);
      if (temp->text(0).compare(tr("Sessions")) == 0) {
        itemSessions = itemProject->child(i);
        break;
      }
    }

    if (itemSessions == nullptr) {
      itemSessions = new QTreeWidgetItem();
      itemSessions->setText(0, tr("Sessions"));
      itemSessions->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_list_view_48px.png"));
      itemSessions->setFlags(itemSessions->flags() | Qt::ItemIsTristate);
      itemProject->addChild(itemSessions);
      itemSessions->setExpanded(true);
      itemSessions->setData(0, Qt::UserRole, photomatch::sessions);
    }

    QTreeWidgetItem *itemSession = new QTreeWidgetItem();
    itemSession->setData(0, Qt::UserRole, photomatch::session);
    itemSession->setText(0, sessionName);
    itemSession->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_list_48px.png"));
    itemSession->setToolTip(0, sessionDescription);
    itemSessions->addChild(itemSession);

    update();
  }
}

void MainWindowView::addPreprocess(const QString &sessionName,
                                   const QString &preprocess,
                                   const std::vector<QString> &preprocessImages)
{
  if (QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0)) {

    /* Sessions */

    QTreeWidgetItem *itemSessions = nullptr;
    for (int i = 0; i < itemProject->childCount(); i++) {
      if (QTreeWidgetItem *temp = itemProject->child(i)){
        if (temp->text(0).compare(tr("Sessions")) == 0) {
          itemSessions = itemProject->child(i);
          break;
        }
      }
    }

    if (itemSessions != nullptr) {

      QTreeWidgetItem *itemPreprocess = nullptr;
      for (int i = 0; i < itemSessions->childCount(); i++) {
        if (QTreeWidgetItem *itemSession = itemSessions->child(i)){
          if (itemSession->text(0).compare(sessionName) == 0){

            for (int j = 0; j < itemSession->childCount(); j++) {
              if (QTreeWidgetItem *temp = itemSession->child(j)) {
                if (temp->text(0).compare(tr("Preprocess")) == 0) {
                  itemPreprocess = itemSession->child(j);
                  break;
                }
              }
            }

            if (itemPreprocess == nullptr) {
              itemPreprocess = new QTreeWidgetItem();
              itemPreprocess->setText(0, QString("Preprocess"));
              itemPreprocess->setData(0, Qt::UserRole, photomatch::preprocess);
              itemSession->addChild(itemPreprocess);
            }

            update();
            break;
          }
        }
      }

      if (itemPreprocess != nullptr){

        QTreeWidgetItem *itemImages = nullptr;
        for (int i = 0; i < itemPreprocess->childCount(); i++) {
          if (QTreeWidgetItem *temp = itemPreprocess->child(i)){
            if (temp->text(0).compare(tr("Images")) == 0) {
              itemImages = itemPreprocess->child(i);
              break;
            }
          }
        }

        if (itemImages == nullptr) {
          itemImages = new QTreeWidgetItem();
          itemImages->setText(0, tr("Images"));
          itemImages->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_documents_folder_48px.png"));
          itemImages->setFlags(itemImages->flags() | Qt::ItemIsTristate);
          itemImages->setData(0, Qt::UserRole, photomatch::preprocess_images);
          itemPreprocess->addChild(itemImages);
          itemImages->setExpanded(true);
        }

        for (auto image : preprocessImages){

          QTreeWidgetItem *itemPhotogram = nullptr;
          for (int i = 0; i < itemImages->childCount(); i++) {
            if (QTreeWidgetItem *temp = itemImages->child(i)){
              if (temp && temp->toolTip(0).compare(image) == 0) {
                itemPhotogram = itemImages->child(i);
                break;
              }
            }
          }

          if (itemPhotogram == nullptr) {
            itemPhotogram = new QTreeWidgetItem();
            itemPhotogram->setText(0, QFileInfo(image).baseName());
            itemPhotogram->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_image_48px.png"));
            itemPhotogram->setToolTip(0, image);
            itemPhotogram->setFlags(itemPhotogram->flags() | Qt::ItemIsTristate);
            itemPhotogram->setData(0, Qt::UserRole, photomatch::preprocess_image);
            itemImages->addChild(itemPhotogram);
            itemPhotogram->setExpanded(true);
          }
        }

      }

    }
  }
}

void MainWindowView::addFeatures(const QString &sessionName, const QString &detector, const QString &descriptor, const std::vector<QString> &features)
{
  if (QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0)) {

    /* Sessions */

    QTreeWidgetItem *itemSessions = nullptr;
    for (int i = 0; i < itemProject->childCount(); i++) {
      if (QTreeWidgetItem *temp = itemProject->child(i)){
        if (temp->text(0).compare(tr("Sessions")) == 0) {
          itemSessions = itemProject->child(i);
          break;
        }
      }
    }

    if (itemSessions != nullptr) {

      QTreeWidgetItem *itemFeatures = nullptr;
      for (int i = 0; i < itemSessions->childCount(); i++) {
        if (QTreeWidgetItem *itemSession = itemSessions->child(i)){
          if (itemSession->text(0).compare(sessionName) == 0){

            for (int j = 0; j < itemSession->childCount(); j++) {
              if (QTreeWidgetItem *temp = itemSession->child(j)){
                if (temp->text(0).compare(tr("Features")) == 0) {
                  itemFeatures = itemSession->child(j);
                  break;
                }
              }
            }

            if (itemFeatures == nullptr) {
              itemFeatures = new QTreeWidgetItem();
              itemFeatures->setText(0, QString("Features"));
              itemFeatures->setData(0, Qt::UserRole, photomatch::features);
              itemSession->addChild(itemFeatures);
            }

            update();
            break;

          }
        }
      }

      if (itemFeatures != nullptr){

        /// Detector
        QTreeWidgetItem *itemDetector = nullptr;
        for (int i = 0; i < itemFeatures->childCount(); i++) {
          if (QTreeWidgetItem *temp = itemFeatures->child(i)){
            QStringList l = temp->text(0).split(":");
            if (l.size() == 2){
              if (l.at(0).compare(tr("Detector")) == 0) {
                itemDetector = itemFeatures->child(i);
                break;
              }
            }
          }

        }

        if (itemDetector == nullptr) {
          itemDetector = new QTreeWidgetItem();
          itemDetector->setData(0, Qt::UserRole, photomatch::detector);
          itemFeatures->addChild(itemDetector);
        }

        itemDetector->setText(0, QString("Detector: ").append(detector));


        /// Descriptor
        QTreeWidgetItem *itemDescriptor = nullptr;
        for (int i = 0; i < itemFeatures->childCount(); i++) {
          if (QTreeWidgetItem *temp = itemFeatures->child(i)){
            QStringList l = temp->text(0).split(":");
            if (l.size() == 2){
              if (l.at(0).compare(tr("Descriptor")) == 0) {
                itemDescriptor = itemFeatures->child(i);
                break;
              }
            }
          }
        }

        if (itemDescriptor == nullptr) {
          itemDescriptor = new QTreeWidgetItem();
          itemDescriptor->setData(0, Qt::UserRole, photomatch::descriptor);
          itemFeatures->addChild(itemDescriptor);
        }

        itemDescriptor->setText(0, QString("Descriptor: ").append(descriptor));

        QTreeWidgetItem *itemImagesFeatures = nullptr;
        for (int i = 0; i < itemFeatures->childCount(); i++) {
          QTreeWidgetItem *temp = itemFeatures->child(i);
          if (temp && temp->text(0).compare(tr("Keypoints")) == 0) {
            itemImagesFeatures = itemFeatures->child(i);
            break;
          }
        }

        if (itemImagesFeatures == nullptr) {
          itemImagesFeatures = new QTreeWidgetItem();
          itemImagesFeatures->setText(0, tr("Keypoints"));
          itemImagesFeatures->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_documents_folder_48px.png"));
          itemImagesFeatures->setFlags(itemImagesFeatures->flags() | Qt::ItemIsTristate);
          itemImagesFeatures->setData(0, Qt::UserRole, photomatch::features_images);
          itemFeatures->addChild(itemImagesFeatures);
        }

        for (auto &image_features : features) {

          QTreeWidgetItem *itemImageFeatures = nullptr;
          for (int i = 0; i < itemImagesFeatures->childCount(); i++) {
            QTreeWidgetItem *temp = itemImagesFeatures->child(i);
            if (temp && temp->toolTip(0).compare(image_features) == 0) {
              itemImageFeatures = itemImagesFeatures->child(i);
              break;
            }
          }

          if (itemImageFeatures == nullptr) {
            itemImageFeatures = new QTreeWidgetItem();
            itemImageFeatures->setText(0, QFileInfo(image_features).baseName());
            itemImageFeatures->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_xml_48px.png"));
            itemImageFeatures->setToolTip(0, image_features);
            itemImageFeatures->setFlags(itemImageFeatures->flags() | Qt::ItemIsTristate);
            itemImageFeatures->setData(0, Qt::UserRole, photomatch::features_image);
            itemImagesFeatures->addChild(itemImageFeatures);
          }

        }

      }

    }
  }
}

void MainWindowView::addMatches(const QString &sessionName, const QString &matcher, const QString &left, const QString &right, const QString &file)
{
  if (QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0)) {

    /* Sessions */

    QTreeWidgetItem *itemSessions = nullptr;
    for (int i = 0; i < itemProject->childCount(); i++) {
      if (QTreeWidgetItem *temp = itemProject->child(i)){
        if (temp->text(0).compare(tr("Sessions")) == 0) {
          itemSessions = itemProject->child(i);
          break;
        }
      }
    }

    if (itemSessions != nullptr) {

      QTreeWidgetItem *itemMatches = nullptr;
      for (int i = 0; i < itemSessions->childCount(); i++) {
        if (QTreeWidgetItem *itemSession = itemSessions->child(i)){
          if (itemSession->text(0).compare(sessionName) == 0){

            for (int j = 0; j < itemSession->childCount(); j++) {
              if (QTreeWidgetItem *temp = itemSession->child(j)){
                if (temp->text(0).compare(tr("Matches")) == 0) {
                  itemMatches = itemSession->child(j);
                  break;
                }
              }
            }

            if (itemMatches == nullptr) {
              itemMatches = new QTreeWidgetItem();
              itemMatches->setText(0, QString("Matches"));
              itemMatches->setData(0, Qt::UserRole, photomatch::matches);
              itemSession->addChild(itemMatches);
            }

            update();
            break;

          }
        }
      }

      if (itemMatches != nullptr){

        /// Detector
        QTreeWidgetItem *itemMatcher = nullptr;
        for (int i = 0; i < itemMatches->childCount(); i++) {
          if (QTreeWidgetItem *temp = itemMatches->child(i)){
            QStringList l = temp->text(0).split(":");
            if (l.size() == 2){
              if (l.at(0).compare(tr("Descriptor Matcher")) == 0) {
                itemMatcher = itemMatches->child(i);
                break;
              }
            }
          }

        }

        if (itemMatcher == nullptr) {
          itemMatcher = new QTreeWidgetItem();
          itemMatcher->setData(0, Qt::UserRole, photomatch::descriptor_matcher);
          itemMatches->addChild(itemMatcher);
        }

        itemMatcher->setText(0, QString("Descriptor Matcher: ").append(matcher));


        /* Image pairs */

        QTreeWidgetItem *itemImagePairs = nullptr;
        for (int i = 0; i < itemMatches->childCount(); i++) {
          QTreeWidgetItem *temp = itemMatches->child(i);
          if (temp && temp->text(0).compare(tr("Image Pairs")) == 0) {
            itemImagePairs = itemMatches->child(i);
            break;
          }
        }

        if (itemImagePairs == nullptr) {
          itemImagePairs = new QTreeWidgetItem();
          itemImagePairs->setText(0, tr("Image Pairs"));
          itemImagePairs->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_documents_folder_48px.png"));
          itemImagePairs->setFlags(itemImagePairs->flags() | Qt::ItemIsTristate);
          itemImagePairs->setData(0, Qt::UserRole, photomatch::matches_pairs);
          itemMatches->addChild(itemImagePairs);
          itemImagePairs->setExpanded(true);
        }

        QTreeWidgetItem *itemLeftImage = nullptr;
        for (int i = 0; i < itemImagePairs->childCount(); i++) {
          QTreeWidgetItem *temp = itemImagePairs->child(i);
          if (temp && temp->text(0).compare(left) == 0) {
            itemLeftImage = itemImagePairs->child(i);
            break;
          }
        }

        if (itemLeftImage == nullptr) {
          itemLeftImage = new QTreeWidgetItem();
          itemLeftImage->setText(0, left);
          itemLeftImage->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_stack_of_photos_48px.png"));
          itemLeftImage->setFlags(itemLeftImage->flags() | Qt::ItemIsTristate);
          itemLeftImage->setData(0, Qt::UserRole, photomatch::pair_left);
          itemImagePairs->addChild(itemLeftImage);
        }

        QTreeWidgetItem *itemRightImage = nullptr;
        for (int i = 0; i < itemLeftImage->childCount(); i++) {
          QTreeWidgetItem *temp = itemLeftImage->child(i);
          if (temp && temp->text(0).compare(right) == 0) {
            itemRightImage = itemLeftImage->child(i);
            break;
          }
        }

        if (itemRightImage == nullptr) {
          itemRightImage = new QTreeWidgetItem();
          itemRightImage->setText(0, right);
          itemRightImage->setToolTip(0, file);
          itemRightImage->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_image_48px.png"));
          itemRightImage->setFlags(itemRightImage->flags() | Qt::ItemIsTristate);
          itemRightImage->setData(0, Qt::UserRole, photomatch::pair_right);
          itemLeftImage->addChild(itemRightImage);
        }

      }

    }
  }
}

void MainWindowView::setStatusBarMsg(const QString &msg)
{
  ui->statusBar->showMessage(msg, 2000);
}

void MainWindowView::setProperties(const std::list<std::pair<QString, QString>> &properties)
{
  ui->treeWidgetProperties->clear();
  ui->treeWidgetProperties->setAlternatingRowColors(true);

  for (auto it = properties.begin(); it != properties.end(); it++){
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, it->first);
    item->setText(1, it->second);
    ui->treeWidgetProperties->addTopLevelItem(item);
  }

}

QProgressBar *MainWindowView::progressBar()
{
  return mProgressBar;
}

TabHandler *MainWindowView::tabHandler()
{
  return mTabHandler;
}

void MainWindowView::updateHistory(const QStringList &history)
{
  int n = history.size();
  for (int r = 0; r < n; r++) {
    QString prjFileName = tr("&%1 %2").arg(r + 1).arg(QFileInfo(history[r]).fileName());
    if (mHistory.size() == static_cast<size_t>(r)) {
      // Se añade un nuevo elemento
      QAction *action = new QAction(prjFileName, this);
      action->setData(history[r]);
      action->setToolTip(history[r]);
      mHistory.push_back(action);
      connect(mHistory[static_cast<size_t>(r)], SIGNAL(triggered()), this, SLOT(openFromHistory()));
      mMenuRecentProjects->insertAction(mActionNotRecentProjects, mHistory[static_cast<size_t>(r)]);
      mMenuRecentProjects->setToolTipsVisible(true);
    } else {
      mHistory[static_cast<size_t>(r)]->setText(prjFileName);
      mHistory[static_cast<size_t>(r)]->setData(history[r]);
      mHistory[static_cast<size_t>(r)]->setToolTip(history[r]);
    }
  }

  update();
}

void MainWindowView::deleteHistory()
{
  while (mHistory.size() > 0) {
    disconnect(mHistory[0], SIGNAL(triggered()), this, SLOT(openFromHistory()));
    mMenuRecentProjects->removeAction(mHistory[0]);
    mHistory.erase(mHistory.begin());
  }

  update();
}

void MainWindowView::deleteImage(const QString &file)
{
  if (QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0)) {

    QTreeWidgetItem *itemImages = nullptr;
    for (int i = 0; i < itemProject->childCount(); i++) {
      QTreeWidgetItem *temp = itemProject->child(i);
      if (temp->text(0).compare(tr("Images")) == 0) {
        itemImages = itemProject->child(i);
        break;
      }
    }

    if (itemImages) {

      // Se busca la imagen en el árbol
      QTreeWidgetItem *itemImage = nullptr;
      for (int i = 0; i < itemImages->childCount(); i++) {
        QTreeWidgetItem *temp = itemImages->child(i);
        if (temp->text(0).compare(file) == 0) {
          itemImage = itemImages->child(i);
          delete itemImage;
          itemImage = nullptr;
          break;
        }
      }
    }

    setFlag(MainWindowView::Flag::images_added, itemProject->childCount() > 0);
  }

  mThumbnailsWidget->deleteThumbnail(file);
}

void MainWindowView::deleteSession(const QString &session)
{

  int id = mComboBoxActiveSession->findText(session);
  if (id != -1){
    mComboBoxActiveSession->removeItem(id);
  }

  if (QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0)) {

    QTreeWidgetItem *itemSessions = nullptr;
    for (int i = 0; i < itemProject->childCount(); i++) {
      if (QTreeWidgetItem *temp = itemProject->child(i)){
        if (temp->text(0).compare(tr("Sessions")) == 0) {
          itemSessions = itemProject->child(i);
          break;
        }
      }
    }

    if (itemSessions != nullptr) {
      for (int i = 0; i < itemSessions->childCount(); i++) {
        if (QTreeWidgetItem *itemSession = itemSessions->child(i)){
          if (itemSession->text(0).compare(session) == 0){
            delete itemSession;
            itemSession = nullptr;
            break;
          }
        }
      }
    }
  }
}

void MainWindowView::deletePreprocess(const QString &session, const QString &preprocess)
{

  if (QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0)) {

    QTreeWidgetItem *itemSessions = nullptr;
    for (int i = 0; i < itemProject->childCount(); i++) {
      if (QTreeWidgetItem *temp = itemProject->child(i)){
        if (temp->text(0).compare(tr("Sessions")) == 0) {
          itemSessions = itemProject->child(i);
          break;
        }
      }
    }

    if (itemSessions != nullptr) {

      QTreeWidgetItem *itemPreprocess = nullptr;
      for (int i = 0; i < itemSessions->childCount(); i++) {
        if (QTreeWidgetItem *itemSession = itemSessions->child(i)){
          if (itemSession->text(0).compare(session) == 0){

            for (int j = 0; j < itemSession->childCount(); j++) {
              if (QTreeWidgetItem *temp = itemSession->child(j)) {
                if (temp->text(0).compare(tr("Preprocess")) == 0) {
                  itemPreprocess = itemSession->child(j);
                  break;
                }
              }
            }

            break;
          }
        }
      }

      if (itemPreprocess != nullptr){

        QTreeWidgetItem *itemImages = nullptr;
        for (int i = 0; i < itemPreprocess->childCount(); i++) {
          if (QTreeWidgetItem *temp = itemPreprocess->child(i)){
            if (temp->text(0).compare(tr("Images")) == 0) {
              itemImages = itemPreprocess->child(i);
              break;
            }
          }
        }

        if (itemImages != nullptr) {

          QTreeWidgetItem *itemPhotogram = nullptr;
          for (int i = 0; i < itemImages->childCount(); i++) {
            if (QTreeWidgetItem *temp = itemImages->child(i)){
              if (temp->toolTip(0).compare(preprocess) == 0) {
                itemPhotogram = itemImages->child(i);
                break;
              }
            }
          }

          if (itemPhotogram != nullptr) {
            delete itemPhotogram;
            itemPhotogram = nullptr;
            if (itemImages->childCount() == 0){
              delete itemImages;
              itemImages = nullptr;
            }
          }

        }

      }

    }

  }
}

void MainWindowView::deleteFeatures(const QString &session, const QString &feat)
{

  if (QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0)) {

    QTreeWidgetItem *itemSessions = nullptr;
    for (int i = 0; i < itemProject->childCount(); i++) {
      if (QTreeWidgetItem *temp = itemProject->child(i)){
        if (temp->text(0).compare(tr("Sessions")) == 0) {
          itemSessions = itemProject->child(i);
          break;
        }
      }
    }

    if (itemSessions != nullptr) {

      QTreeWidgetItem *itemFeatures = nullptr;
      for (int i = 0; i < itemSessions->childCount(); i++) {
        if (QTreeWidgetItem *itemSession = itemSessions->child(i)){
          if (itemSession->text(0).compare(session) == 0){

            for (int j = 0; j < itemSession->childCount(); j++) {
              if (QTreeWidgetItem *temp = itemSession->child(j)){
                if (temp->text(0).compare(tr("Features")) == 0) {
                  itemFeatures = itemSession->child(j);
                  break;
                }
              }
            }

            break;

          }
        }
      }

      if (itemFeatures != nullptr) {

        
        QTreeWidgetItem *itemImagesFeatures = nullptr;
        for (int i = 0; i < itemFeatures->childCount(); i++) {
          QTreeWidgetItem *temp = itemFeatures->child(i);
          if (temp && temp->text(0).compare(tr("Keypoints")) == 0) {
            itemImagesFeatures = itemFeatures->child(i);
            break;
          }
        }

        if (itemImagesFeatures != nullptr) {

          QTreeWidgetItem *itemImageFeatures = nullptr;
          for (int i = 0; i < itemImagesFeatures->childCount(); i++) {
            QTreeWidgetItem *temp = itemImagesFeatures->child(i);
            if (temp->toolTip(0).compare(feat) == 0) {
              itemImageFeatures = itemImagesFeatures->child(i);
              delete itemImageFeatures;
              itemImageFeatures = nullptr;
              break;
            }
          }

        }

      }
    
    }

  }
}

void MainWindowView::deleteMatches(const QString &session, const QString &matches)
{

  if (QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0)) {

    QTreeWidgetItem *itemSessions = nullptr;
    for (int i = 0; i < itemProject->childCount(); i++) {
      if (QTreeWidgetItem *temp = itemProject->child(i)){
        if (temp->text(0).compare(tr("Sessions")) == 0) {
          itemSessions = itemProject->child(i);
          break;
        }
      }
    }

    if (itemSessions != nullptr) {

      QTreeWidgetItem *itemMatches = nullptr;
      for (int i = 0; i < itemSessions->childCount(); i++) {
        if (QTreeWidgetItem *itemSession = itemSessions->child(i)){
          if (itemSession->text(0).compare(session) == 0){

            for (int j = 0; j < itemSession->childCount(); j++) {
              if (QTreeWidgetItem *temp = itemSession->child(j)){
                if (temp->text(0).compare(tr("Matches")) == 0) {
                  itemMatches = itemSession->child(j);
                  break;
                }
              }
            }

            break;

          }
        }
      }

      if (itemMatches != nullptr) {


        /* Image pairs */

        QTreeWidgetItem *itemImagePairs = nullptr;
        for (int i = 0; i < itemMatches->childCount(); i++) {
          QTreeWidgetItem *temp = itemMatches->child(i);
          if (temp && temp->text(0).compare(tr("Image Pairs")) == 0) {
            itemImagePairs = itemMatches->child(i);
            break;
          }
        }

        if (itemImagePairs != nullptr) {
          QTreeWidgetItem *itemLeftImage = nullptr;
          for (int i = 0; i < itemImagePairs->childCount(); i++) {
            itemLeftImage = itemImagePairs->child(i);
            if (itemLeftImage != nullptr) {

              QTreeWidgetItem *itemRightImage = nullptr;
              for (int j = 0; j < itemLeftImage->childCount(); j++) {
                QTreeWidgetItem *temp = itemLeftImage->child(j);
                if (temp && temp->toolTip(0).compare(matches) == 0) {
                  itemRightImage = itemLeftImage->child(j);
                  break;
                }
              }

              if (itemRightImage != nullptr) {
                delete itemRightImage;
                itemRightImage = nullptr;
                if (itemLeftImage->childCount() == 0){
                  delete itemLeftImage;
                  itemLeftImage = nullptr;
                }
                break;
              }
            }

          }

        }

      }

    }

  }
}

void MainWindowView::setActiveSession(const QString &session)
{
  const QSignalBlocker blocker(mComboBoxActiveSession);
  mComboBoxActiveSession->setCurrentText(session);

  if (QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0)) {

    /* Sessions */

    QTreeWidgetItem *itemSessions = nullptr;
    for (int i = 0; i < itemProject->childCount(); i++) {
      QTreeWidgetItem *temp = itemProject->child(i);
      if (temp->text(0).compare(tr("Sessions")) == 0) {
        itemSessions = itemProject->child(i);
        break;
      }
    }

    if (itemSessions != nullptr) {
      for (int i = 0; i < itemSessions->childCount(); i++) {
        if (QTreeWidgetItem *itemSession = itemSessions->child(i)){
          QFont font;
          font.setBold(itemSession->text(0).compare(session) == 0);
          itemSession->setFont(0, font);
        }
      }

//  //    QFont font;
//  //    font.setBold(activeSession);
//  //    itemSession->setFont(0, font);
//      itemSession->setData(0, Qt::UserRole, photomatch::session);
//      itemSession->setText(0, sessionName);
//      itemSession->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_list_48px.png"));
//      itemSession->setToolTip(0, sessionDescription);
//      itemSessions->addChild(itemSession);

    }


    update();
    }
}

void MainWindowView::changeEvent(QEvent *e)
{
  QMainWindow::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

void MainWindowView::update()
{
  bool bProjectExists = mFlags.isActive(Flag::project_exists);
  bool bProjectModified = mFlags.isActive(Flag::project_modified);
  bool bImageOpen = mFlags.isActive(Flag::image_open);
  bool bProcessing = mFlags.isActive(Flag::processing);
  bool bLoadingImages = mFlags.isActive(Flag::loading_images);

  mActionNewProject->setEnabled(!bProcessing);
  mActionOpenProject->setEnabled(!bProcessing);
  mMenuRecentProjects->setEnabled(!bProcessing);
  mActionSaveProject->setEnabled(bProjectExists && bProjectModified && !bProcessing);
  mActionSaveProjectAs->setEnabled(bProjectExists && !bProcessing);
  mActionCloseProject->setEnabled(bProjectExists && !bProcessing);
  mActionExit->setEnabled(!bProcessing);


  mActionLoadImages->setEnabled(bProjectExists && !bProcessing && !bLoadingImages);
  mActionGroundTruthEditor->setEnabled(mFlags.isActive(Flag::images_added));
  mActionNewSession->setEnabled(mFlags.isActive(Flag::images_added) && !bProcessing);
  mActionPreprocess->setEnabled(mFlags.isActive(Flag::session_created) && !bProcessing);
  mActionFeatureExtraction->setEnabled(mFlags.isActive(Flag::session_created) && !bProcessing);
  mActionFeatureMatching->setEnabled(mFlags.isActive(Flag::feature_extraction) && !bProcessing);
  //mActionBatch->setEnabled(mFlags.isActive(Flag::session_created) && !bProcessing);
  mActionExportTiePoints->setEnabled(mFlags.isActive(Flag::session_created) && !bProcessing);
  mActionExportMatches->setEnabled(mFlags.isActive(Flag::session_created) && !bProcessing);
  mActionFeaturesViewer->setEnabled(mFlags.isActive(Flag::feature_extraction));
  mActionMatchesViewer->setEnabled(mFlags.isActive(Flag::feature_matching));
  mActionPassPointsViewer->setEnabled(mFlags.isActive(Flag::feature_matching));
  mActionHomography->setEnabled(mFlags.isActive(Flag::feature_matching));
  //mActionRepeatability->setEnabled(mFlags.isActive(Flag::feature_matching) && mFlags.isActive(Flag::ground_truth));
  mActionPRCurves->setEnabled(mFlags.isActive(Flag::feature_matching) && mFlags.isActive(Flag::ground_truth));
  mActionROCCurves->setEnabled(mFlags.isActive(Flag::feature_matching) && mFlags.isActive(Flag::ground_truth));
  mActionDETCurves->setEnabled(mFlags.isActive(Flag::feature_matching) && mFlags.isActive(Flag::ground_truth));

  mActionNotRecentProjects->setVisible(mHistory.size() == 0);
  mActionClearHistory->setEnabled(mHistory.size() > 0);

  mComboBoxActiveSession->setDisabled(bProcessing);
  mActionSetSession->setDisabled(bProcessing);
  mActionDeleteSession->setDisabled(bProcessing);
}

void MainWindowView::retranslate()
{
  mActionNewProject->setText(QApplication::translate("MainWindowView", "New Project", nullptr));
#ifndef QT_NO_SHORTCUT
  mActionNewProject->setShortcut(QApplication::translate("MainWindowView", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
  mActionOpenProject->setText(QApplication::translate("MainWindowView", "Open Project", nullptr));
#ifndef QT_NO_SHORTCUT
  mActionOpenProject->setShortcut(QApplication::translate("MainWindowView", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
  mActionSaveProject->setText(QApplication::translate("MainWindowView", "Save Project", nullptr));
#ifndef QT_NO_SHORTCUT
  mActionSaveProject->setShortcut(QApplication::translate("MainWindowView", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
  mActionSaveProjectAs->setText(QApplication::translate("MainWindowView", "Save Project As...", nullptr));
#ifndef QT_NO_SHORTCUT
  mActionSaveProjectAs->setShortcut(QApplication::translate("MainWindowView", "Ctrl+Shift+S", nullptr));
#endif // QT_NO_SHORTCUT
  mActionExportTiePoints->setText(QApplication::translate("MainWindowView", "Export tie points", nullptr));
  mActionExportMatches->setText(QApplication::translate("MainWindowView", "Export Matches", nullptr));
  mActionCloseProject->setText(QApplication::translate("MainWindowView", "Close Project", nullptr));
  mActionExit->setText(QApplication::translate("MainWindowView", "Exit", nullptr));
#ifndef QT_NO_SHORTCUT
  mActionExit->setShortcut(QApplication::translate("MainWindowView", "Ctrl+F4", nullptr));
#endif // QT_NO_SHORTCUT
  mActionStartPage->setText(QApplication::translate("MainWindowView", "Start Page", nullptr));
  mActionViewSettings->setText(QApplication::translate("MainWindowView", "View Settings", nullptr));
  mActionLoadImages->setText(QApplication::translate("MainWindowView", "Load Images", nullptr));
  mActionNewSession->setText(QApplication::translate("MainWindowView", "New Session", nullptr));
  mActionPreprocess->setText(QApplication::translate("MainWindowView", "Preprocess", nullptr));
  mActionFeatureExtraction->setText(QApplication::translate("MainWindowView", "Feature Extraction", nullptr));
  mActionFeatureMatching->setText(QApplication::translate("MainWindowView", "Feature Matching", nullptr));
  mActionToolSettings->setText(QApplication::translate("MainWindowView", "Tools Settings", nullptr));
  mActionHelp->setText(QApplication::translate("MainWindowView", "Help", nullptr));
#ifndef QT_NO_SHORTCUT
  mActionHelp->setShortcut(QApplication::translate("MainWindowView", "F1", nullptr));
#endif // QT_NO_SHORTCUT
  mActionOnlineHelp->setText(QApplication::translate("MainWindowView", "Online Help", nullptr));
  mActionAbout->setText(QApplication::translate("MainWindowView", "About", nullptr));
  mActionFeaturesViewer->setText(QApplication::translate("MainWindowView", "Keypoints Viewer", nullptr));
  mActionMatchesViewer->setText(QApplication::translate("MainWindowView", "Matches Viewer", nullptr));
  mActionPassPointsViewer->setText(QApplication::translate("MainWindowView", "Multiview Matching Assessment", nullptr));
  mActionGroundTruthEditor->setText(QApplication::translate("MainWindowView", "Ground Truth Editor", nullptr));
  mActionHomography->setText(QApplication::translate("MainWindowView", "Homography", nullptr));
  mActionPRCurves->setText(QApplication::translate("MainWindowView", "Precision-Recall Curves", nullptr));
  mActionROCCurves->setText(QApplication::translate("MainWindowView", "ROC Curves", nullptr));
  mActionDETCurves->setText(QApplication::translate("MainWindowView", "DET Curves", nullptr));
  mActionQualityControlSettings->setText(QApplication::translate("MainWindowView", "Quality Control Settings", nullptr));
  mActionNotRecentProjects->setText(QApplication::translate("MainWindowView", "Not recent projects", nullptr));
  mActionClearHistory->setText(QApplication::translate("MainWindowView", "Clear History", nullptr));
  mActionSetSession->setText(QApplication::translate("MainWindowView", "Set as current session", nullptr));
  mActionDeleteSession->setText(QApplication::translate("MainWindowView", "Delete session", nullptr));

  mMenuRecentProjects->setTitle(QApplication::translate("MainWindowView", "Recent Projects", nullptr));
  mMenuExport->setTitle(QApplication::translate("MainWindowView", "Export", nullptr));
  mMenuPanels->setTitle(QApplication::translate("MainWindowView", "Dockable panels", nullptr));
  mMenuToolBar->setTitle(QApplication::translate("MainWindowView", "Toolbars", nullptr));

  mLabelActiveSession->setText(QApplication::translate("MainWindowView", "Active Session: ", nullptr));
}

void MainWindowView::openFromHistory()
{
  QAction *action = qobject_cast<QAction *>(sender());
  if (action)
    emit openProjectFromHistory(action->data().toString());
}

void MainWindowView::onSelectionChanged()
{
  QList<QTreeWidgetItem*> item = mTreeWidgetProject->selectedItems();
  if (item.isEmpty()) return;
  if (item[0]->data(0, Qt::UserRole) == photomatch::project){

  } else if (item[0]->data(0, Qt::UserRole) == photomatch::images){
  } else if (item[0]->data(0, Qt::UserRole) == photomatch::image){
    int size = item.size();
    if(size > 0){
      if (size == 1) {
        emit selectImage(item[0]->text(0));
      } else {
        QStringList selected_images;
        for (int i = 0; i < size; i++){
          selected_images.push_back(item[i]->text(0));
        }
        emit selectImages(selected_images);
      }
    }
  } else if (item[0]->data(0, Qt::UserRole) == photomatch::preprocess_image){
    ui->treeWidgetProperties->clear();
  } else if (item[0]->data(0, Qt::UserRole) == photomatch::sessions){
    ui->treeWidgetProperties->clear();
  } else if (item[0]->data(0, Qt::UserRole) == photomatch::session){
    int size = item.size();
    if(size > 0){
      if (size == 1) {
        emit selectSession(item[0]->text(0));
      }
    }
  } else if (item[0]->data(0, Qt::UserRole) == photomatch::preprocess){
    int size = item.size();
    if(size > 0){
      if (size == 1) {
        QString session = item[0]->parent()->text(0);
        emit selectPreprocess(session);
      }
    }
  } else if (item[0]->data(0, Qt::UserRole) == photomatch::features){
    ui->treeWidgetProperties->clear();
    QString session = item[0]->parent()->text(0);
    emit selectFeatures(session);
  } else if (item[0]->data(0, Qt::UserRole) == photomatch::features_images){
    ui->treeWidgetProperties->clear();
  } else if (item[0]->data(0, Qt::UserRole) == photomatch::features_image){
    ui->treeWidgetProperties->clear();
    emit selectImageFeatures(item[0]->toolTip(0));
  } else if (item[0]->data(0, Qt::UserRole) == photomatch::detector){
    int size = item.size();
    if(size > 0){
      if (size == 1) {
        QString session = item[0]->parent()->parent()->text(0);
        emit selectDetector(session);
      }
    }
  } else if (item[0]->data(0, Qt::UserRole) == photomatch::descriptor){
    int size = item.size();
    if(size > 0){
      if (size == 1) {
        QString session = item[0]->parent()->parent()->text(0);
        emit selectDescriptor(session);
      }
    }
  }

//  if (item[0]->parent()->text(0).compare(tr("Images")) == 0){
//    int size = item.size();
//    if(size > 0){
//      if (size == 1) {
//        emit selectImage(item[0]->toolTip(0));
//      } else {
//        QStringList selected_images;
//        for (int i = 0; i < size; i++){
//          selected_images.push_back(item[i]->toolTip(0));
//        }
//        emit selectImages(selected_images);
//      }
//    }
//  } else if (item[0]->parent()->text(0).compare(tr("Sessions")) == 0){
//    int size = item.size();
//    if(size > 0){
//      if (size == 1) {
//        emit selectSession(item[0]->text(0));
//      } /*else {
//        QStringList selected_images;
//        for (int i = 0; i < size; i++){
//          selected_images.push_back(item[i]->toolTip(0));
//        }
//        emit selectImages(selected_images);
//      }*/
//    }
  //  }
}

void MainWindowView::onItemDoubleClicked(QTreeWidgetItem *item, int column)
{
  if (item){
    if (item->data(0, Qt::UserRole) == photomatch::image ||
      item->data(0, Qt::UserRole) == photomatch::preprocess_image){
     emit openImage(item->toolTip(column));
   } else if (item->data(0, Qt::UserRole) == photomatch::pair_right){
     QString session = item->parent()->parent()->parent()->parent()->text(0);
     emit openImageMatches(session, item->parent()->text(0), item->text(column));
   } else if (item->data(0, Qt::UserRole) == photomatch::features_image){
     QString session = item->parent()->parent()->parent()->text(0);
     emit openKeypointsViewer(session, QFileInfo(item->text(column)).baseName());
   }
  }
}

void MainWindowView::onTreeContextMenu(const QPoint &point)
{
  QPoint globalPos = mTreeWidgetProject->mapToGlobal(point);

  QTreeWidgetItem *item = nullptr;
  item = mTreeWidgetProject->itemAt(point);

  if (item == nullptr)
    return;

  if (item->data(0, Qt::UserRole) == photomatch::project){
    QMenu menu;
    menu.addAction(mActionLoadImages);

    QAction *selectedItem = menu.exec(globalPos);
  } else if (item->data(0, Qt::UserRole) == photomatch::images){
  } else if (item->data(0, Qt::UserRole) == photomatch::image){
    QMenu menu;
    QAction *open_image = new QAction(QIcon(QStringLiteral(":/ico/24/img/material/24/icons8_image_file_24px.png")),
                                       tr("Open Image"), this);
    menu.addAction(open_image);
    QAction *delete_image = new QAction(QIcon(QStringLiteral(":/ico/24/img/material/24/icons8_remove_image_24px.png")),
                                       tr("Delete Image"), this);
    menu.addAction(delete_image);
    if (QAction *selectedItem = menu.exec(globalPos)) {
      if (selectedItem->text() == tr("Open Image")) {
        emit openImage(item->toolTip(0));
      } else if (selectedItem->text() == tr("Delete Image")) {
        emit deleteImages(QStringList(item->text(0)));
      }
    }
  } else if (item->data(0, Qt::UserRole) == photomatch::preprocess_image){
    QMenu menu;
    QAction *open_image = new QAction(QIcon(QStringLiteral(":/ico/24/img/material/24/icons8_image_file_24px.png")),
                                       tr("Open Image"), this);
    menu.addAction(open_image);
//    QAction *delete_image = new QAction(QIcon(QStringLiteral(":/ico/24/img/material/24/icons8_remove_image_24px.png")),
//                                       tr("Delete Image"), this);
//    menu.addAction(delete_image);
    if (QAction *selectedItem = menu.exec(globalPos)) {
      if (selectedItem->text() == tr("Open Image")) {
        emit openImage(item->toolTip(0));
      } /*else if (selectedItem->text() == tr("Delete Image")) {
        emit deleteImages(QStringList(item->toolTip(0)));
      }*/
    }
  } else if (item->data(0, Qt::UserRole) == photomatch::sessions){
    QMenu menu;
    menu.addAction(mActionNewSession);

    QAction *selectedItem = menu.exec(globalPos);
  } else if (item->data(0, Qt::UserRole) == photomatch::session){
    QMenu menu;
    menu.addAction(mActionSetSession);
    menu.addAction(mActionDeleteSession);
//    menu.addSeparator();
//    menu.addAction(mActionPreprocess);
//    menu.addAction(mActionFeatureExtraction);
//    menu.addAction(mActionFeatureMatching);

    if (QAction *selectedItem = menu.exec(globalPos)) {
      if (selectedItem->text() == tr("Set as current session")) {
        emit activeSessionChange(item->text(0));
      } else if (selectedItem->text() == tr("Delete session")) {
        emit delete_session(item->text(0));
      }
    }
  } else if (item->data(0, Qt::UserRole) == photomatch::preprocess){

  } else if (item->data(0, Qt::UserRole) == photomatch::features){

  } else if (item->data(0, Qt::UserRole) == photomatch::features_images){

  } else if (item->data(0, Qt::UserRole) == photomatch::features_image){
    QMenu menu;
    menu.addAction(tr("View keypoints"));
    if (QAction *selectedItem = menu.exec(globalPos)) {
      if (selectedItem->text() == tr("View keypoints")) {
        QString session = item->parent()->parent()->parent()->text(0);
        emit openKeypointsViewer(session, QFileInfo(item->text(0)).baseName());
      }
    }

  } else if (item->data(0, Qt::UserRole) == photomatch::detector){

  } else if (item->data(0, Qt::UserRole) == photomatch::descriptor){

  } else if (item->data(0, Qt::UserRole) == photomatch::pair_left){
    QMenu menu;
    menu.addAction(tr("View Matches"));
    if (QAction *selectedItem = menu.exec(globalPos)) {
      if (selectedItem->text() == tr("View Matches")) {
        QString session = item->parent()->parent()->parent()->text(0);
        emit openMatchesViewer(session, QFileInfo(item->text(0)).baseName(), QString());
      }
    }
  } else if (item->data(0, Qt::UserRole) == photomatch::pair_right){
    QMenu menu;
    menu.addAction(tr("View Matches"));
    if (QAction *selectedItem = menu.exec(globalPos)) {
      if (selectedItem->text() == tr("View Matches")) {
        QString session = item->parent()->parent()->parent()->parent()->text(0);
        emit openMatchesViewer(session, QFileInfo(item->parent()->text(0)).baseName(), QFileInfo(item->text(0)).baseName());
      }
    }
  }

}

void MainWindowView::closeEvent(QCloseEvent *event)
{
  QSettings settings(QSettings::IniFormat, QSettings::UserScope, "TIDOP", "PhotoMatch");
  settings.setValue("geometry", saveGeometry());
  settings.setValue("windowState", saveState());
  QMainWindow::closeEvent(event);
}

} // namespace photomatch
