#include "MainWindowView.h"
#include "ui_MainWindowView.h"

#include <QTreeWidgetItem>
#include <QFileInfo>
#include <QSettings>

namespace fme
{

MainWindowView::MainWindowView(QWidget *parent) :
  QMainWindow(parent),
  mActionNewProject(new QAction(this)),
  mActionOpenProject(new QAction(this)),
  mActionSaveProject(new QAction(this)),
  mActionSaveProjectAs(new QAction(this)),
  mActionCloseProject(new QAction(this)),
  mActionExit(new QAction(this)),
  mActionLoadImages(new QAction(this)),
  mActionNewProcessing(new QAction(this)),
  mActionAssistant(new QAction(this)),
  mActionPreprocess(new QAction(this)),
  mActionFeatureExtraction(new QAction(this)),
  mActionFeatureMatching(new QAction(this)),
  mActionSettings(new QAction(this)),
  mActionHelp(new QAction(this)),
  mActionAbout(new QAction(this)),
  mActionExportTiePoints(new QAction(this)),
  mActionMatchesViewer(new QAction(this)),
  mActionHomography(new QAction(this)),
  mActionRepeteability(new QAction(this)),
  mActionRecall(new QAction(this)),
  mActionNotRecentProjects(new QAction(this)),
  mActionClearHistory(new QAction(this)),
  ui(new Ui::MainWindowView)
{
  ui->setupUi(this);

  init();

  /* Menú Archivo */

  connect(mActionNewProject,       SIGNAL(triggered(bool)),   this,   SIGNAL(openNew()));
  connect(mActionOpenProject,      SIGNAL(triggered(bool)),   this,   SIGNAL(openProject()));
  connect(mActionClearHistory,     SIGNAL(triggered(bool)),   this,   SIGNAL(clearHistory()));
  connect(mActionSaveProject,      SIGNAL(triggered(bool)),   this,   SIGNAL(saveProject()));
  connect(mActionSaveProjectAs,    SIGNAL(triggered(bool)),   this,   SIGNAL(saveProjectAs()));
  connect(mActionCloseProject,     SIGNAL(triggered(bool)),   this,   SIGNAL(closeProject()));
  connect(mActionExit,             SIGNAL(triggered(bool)),   this,   SIGNAL(exit()));

  /* Menú View */

  //TODO: connect(ui->actionStartPage,    SIGNAL(triggered(bool)), this, SLOT(openStartPage()));

  /* Menú herramientas */
  connect(mActionLoadImages,         SIGNAL(triggered(bool)),   this,   SIGNAL(loadImages()));
  connect(mActionNewProcessing,      SIGNAL(triggered(bool)),   this,   SIGNAL(newProcessing()));
  connect(mActionAssistant,          SIGNAL(triggered(bool)),   this,   SIGNAL(openAssistant()));
  connect(mActionPreprocess,         SIGNAL(triggered(bool)),   this,   SIGNAL(openPreprocess()));
  connect(mActionFeatureExtraction,  SIGNAL(triggered(bool)),   this,   SIGNAL(openFeatureExtraction()));
  connect(mActionFeatureMatching,    SIGNAL(triggered(bool)),   this,   SIGNAL(openFeatureMatching()));
  connect(mActionSettings,           SIGNAL(triggered(bool)),   this,   SIGNAL(openSettings()));

  /* Menú Ayuda */
  connect(mActionHelp,  SIGNAL(triggered(bool)), this, SIGNAL(openHelpDialog()));
  connect(mActionAbout, SIGNAL(triggered(bool)), this, SIGNAL(openAboutDialog()));
}

MainWindowView::~MainWindowView()
{
  delete ui;
}

void MainWindowView::clear()
{
  setWindowTitle(QString("FME"));
  mTreeWidgetProject->clear();

  mFlags.clear();

  update();
}

void MainWindowView::setProjectTitle(const QString &title)
{
  this->setWindowTitle(QString("FME - ").append(title));

  QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0);
  if (itemProject == nullptr) {
    itemProject = new QTreeWidgetItem();
    //itemProject->setIcon(0, QIcon(":/ico/img/48x48/project.png"));
    mTreeWidgetProject->addTopLevelItem(itemProject);
    itemProject->setExpanded(true);
  }

  itemProject->setText(0, tr("Project: ").append(title));
}

void MainWindowView::setFlag(MainWindowView::Flag flag, bool value)
{
  mFlags.activeFlag(flag, value);
  update();
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
  //ui->listWidgetRecentProjects->clear();
  //ui->listWidgetRecentProjects->addItems(history);
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

  mActionSaveProject->setEnabled(bProjectExists && bProjectModified);
  mActionSaveProjectAs->setEnabled(bProjectExists);
  mActionCloseProject->setEnabled(bProjectExists);

  mActionLoadImages->setEnabled(bProjectExists);
  mActionNewProcessing->setEnabled(mFlags.isActive(Flag::images_added));
  mActionAssistant->setEnabled(mFlags.isActive(Flag::processing));
  mActionPreprocess->setEnabled(mFlags.isActive(Flag::processing));
  mActionFeatureExtraction->setEnabled(mFlags.isActive(Flag::preprocess));
  mActionFeatureMatching->setEnabled(mFlags.isActive(Flag::feature_extraction));
  mActionExportTiePoints->setEnabled(mFlags.isActive(Flag::feature_extraction));
  mActionMatchesViewer->setEnabled(mFlags.isActive(Flag::feature_matching));
  mActionHomography->setEnabled(mFlags.isActive(Flag::feature_matching));
  mActionRepeteability->setEnabled(mFlags.isActive(Flag::feature_matching));
  mActionRecall->setEnabled(mFlags.isActive(Flag::feature_matching));

  mActionNotRecentProjects->setVisible(mHistory.size() == 0);
  mActionClearHistory->setEnabled(mHistory.size() > 0);

}

void MainWindowView::openFromHistory()
{
  QAction *action = qobject_cast<QAction *>(sender());
  if (action)
    emit openProjectFromHistory(action->data().toString());
}

void MainWindowView::init()
{
  setWindowTitle(QString("FME"));

  mActionNewProject->setText(QApplication::translate("MainWindowView", "New Project", nullptr));
#ifndef QT_NO_SHORTCUT
  mActionNewProject->setShortcut(QApplication::translate("MainWindowView", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
  mActionNewProject->setObjectName(QStringLiteral("actionNewProject"));
  QIcon icon;
  icon.addFile(QStringLiteral(":/ico/24/img/material/24/icons8-empty-document.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionNewProject->setIcon(icon);

  mActionOpenProject->setText(QApplication::translate("MainWindowView", "Open Project", nullptr));
#ifndef QT_NO_SHORTCUT
  mActionOpenProject->setShortcut(QApplication::translate("MainWindowView", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
  mActionOpenProject->setObjectName(QStringLiteral("actionOpenProject"));
  QIcon icon1;
  icon1.addFile(QStringLiteral(":/ico/24/img/material/24/icons8-open.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionOpenProject->setIcon(icon1);

  mActionSaveProject->setText(QApplication::translate("MainWindowView", "Save Project", nullptr));
  #ifndef QT_NO_SHORTCUT
    mActionSaveProject->setShortcut(QApplication::translate("MainWindowView", "Ctrl+S", nullptr));
  #endif // QT_NO_SHORTCUT
  mActionSaveProject->setObjectName(QStringLiteral("actionSaveProject"));
  QIcon icon2;
  icon2.addFile(QStringLiteral(":/ico/24/img/material/24/icons8-save.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionSaveProject->setIcon(icon2);

  mActionSaveProjectAs->setText(QApplication::translate("MainWindowView", "Save Project As...", nullptr));
  #ifndef QT_NO_SHORTCUT
    mActionSaveProjectAs->setShortcut(QApplication::translate("MainWindowView", "Ctrl+Shift+S", nullptr));
  #endif // QT_NO_SHORTCUT
  mActionSaveProjectAs->setObjectName(QStringLiteral("actionSaveProjectAs"));
  QIcon icon3;
  icon3.addFile(QStringLiteral(":/ico/24/img/material/24/icons8-save-as.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionSaveProjectAs->setIcon(icon3);

  mActionCloseProject->setText(QApplication::translate("MainWindowView", "Close Project", nullptr));
  mActionCloseProject->setObjectName(QStringLiteral("actionCloseProject"));
  QIcon icon4;
  icon4.addFile(QStringLiteral(":/ico/24/img/material/24/icons8-close-button.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionCloseProject->setIcon(icon4);

  mActionExit->setText(QApplication::translate("MainWindowView", "Exit", nullptr));
  #ifndef QT_NO_SHORTCUT
    mActionExit->setShortcut(QApplication::translate("MainWindowView", "Ctrl+F4", nullptr));
  #endif // QT_NO_SHORTCUT
  mActionExit->setObjectName(QStringLiteral("actionExit"));
  QIcon icon5;
  icon5.addFile(QStringLiteral(":/ico/24/img/material/24/icons8-switch-power-off.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionExit->setIcon(icon5);

  mActionLoadImages->setText(QApplication::translate("MainWindowView", "Load Images", nullptr));
  mActionLoadImages->setObjectName(QStringLiteral("actionLoadImages"));
  QIcon icon6;
  icon6.addFile(QStringLiteral(":/ico/24/img/material/24/icons8-pictures-folder.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionLoadImages->setIcon(icon6);

  mActionNewProcessing->setText(QApplication::translate("MainWindowView", "New Processing", nullptr));
  mActionNewProcessing->setObjectName(QStringLiteral("actionNewProcessing"));
  QIcon icon7;
  icon7.addFile(QStringLiteral(":/ico/24/img/material/24/icons8-add-list.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionNewProcessing->setIcon(icon7);

  mActionAssistant->setText(QApplication::translate("MainWindowView", "Assistant", nullptr));
  mActionAssistant->setObjectName(QStringLiteral("actionAssistant"));

  mActionPreprocess->setText(QApplication::translate("MainWindowView", "Preprocess", nullptr));
  mActionPreprocess->setObjectName(QStringLiteral("actionPreprocess"));
  QIcon icon8;
  icon8.addFile(QStringLiteral(":/ico/24/img/material/24/icons8-settings-button.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionPreprocess->setIcon(icon8);

  mActionFeatureExtraction->setText(QApplication::translate("MainWindowView", "Feature Extraction", nullptr));
  mActionFeatureExtraction->setObjectName(QStringLiteral("actionFeatureExtraction"));
  QIcon icon9;
  icon9.addFile(QStringLiteral(":/ico/24/img/material/24/features.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionFeatureExtraction->setIcon(icon9);

  mActionFeatureMatching->setText(QApplication::translate("MainWindowView", "Feature Matching", nullptr));
  mActionFeatureMatching->setObjectName(QStringLiteral("actionFeatureMatching"));
  QIcon icon10;
  icon10.addFile(QStringLiteral(":/ico/24/img/material/24/icons8-match_view.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionFeatureMatching->setIcon(icon10);

  mActionSettings->setText(QApplication::translate("MainWindowView", "Settings", nullptr));
  mActionSettings->setObjectName(QStringLiteral("actionSettings"));
  QIcon icon11;
  icon11.addFile(QStringLiteral(":/ico/24/img/material/24/icons8-settings.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionSettings->setIcon(icon11);

  mActionHelp->setText(QApplication::translate("MainWindowView", "Help", nullptr));
  mActionHelp->setObjectName(QStringLiteral("actionHelp"));
  QIcon icon12;
  icon12.addFile(QStringLiteral(":/ico/24/img/material/24/icons8-help.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionHelp->setIcon(icon12);

  mActionAbout->setText(QApplication::translate("MainWindowView", "About", nullptr));
  mActionAbout->setObjectName(QStringLiteral("actionAbout"));
  QIcon icon13;
  icon13.addFile(QStringLiteral(":/ico/24/img/material/24/icons8-about.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionAbout->setIcon(icon13);

  mActionExportTiePoints->setText(QApplication::translate("MainWindowView", "Export Tie Points", nullptr));
  mActionExportTiePoints->setObjectName(QStringLiteral("actionExportTiePoints"));

  mActionMatchesViewer->setText(QApplication::translate("MainWindowView", "Matches Viewer", nullptr));
  mActionMatchesViewer->setObjectName(QStringLiteral("actionMatchesViewer"));

  mActionHomography->setText(QApplication::translate("MainWindowView", "Homography", nullptr));
  mActionHomography->setObjectName(QStringLiteral("actionHomography"));

  mActionRepeteability->setText(QApplication::translate("MainWindowView", "Repeteability", nullptr));
  mActionRepeteability->setObjectName(QStringLiteral("actionRepeteability"));

  mActionRecall->setText(QApplication::translate("MainWindowView", "Recall", nullptr));
  mActionRecall->setObjectName(QStringLiteral("actionRecall"));

  mActionNotRecentProjects->setText(QApplication::translate("MainWindowView", "Not recent projects", nullptr));
  mActionNotRecentProjects->setObjectName(QStringLiteral("actionNotRecentProjects"));
  mActionNotRecentProjects->setEnabled(false);

  mActionClearHistory->setText(QApplication::translate("MainWindowView", "Clear History", nullptr));
  mActionClearHistory->setObjectName(QStringLiteral("actionClearHistory"));

  /* Árbol de proyecto */
  //ui->dockWidgetContentsProject->setContentsMargins(0, 0, 0, 0);
  mTreeWidgetProject = new QTreeWidget(ui->dockWidgetContentsProject);
  mTreeWidgetProject->header()->close();
  mTreeWidgetProject->setColumnCount(1);
  ui->gridLayout->addWidget(mTreeWidgetProject, 0, 0, 1, 1);

  /* Menu file */

  ui->menuFile->addAction(mActionNewProject);
  ui->menuFile->addAction(mActionOpenProject);
  mMenuRecentProjects = new QMenu(tr("Recent Projects"), this);
  mMenuRecentProjects->addAction(mActionNotRecentProjects);
  mMenuRecentProjects->addSeparator();
  mMenuRecentProjects->addAction(mActionClearHistory);
  ui->menuFile->addMenu(mMenuRecentProjects);
  ui->menuFile->addSeparator();
  ui->menuFile->addAction(mActionSaveProject);
  ui->menuFile->addAction(mActionSaveProjectAs);
  ui->menuFile->addSeparator();
  ui->menuFile->addAction(mActionCloseProject);
  ui->menuFile->addSeparator();
  ui->menuFile->addAction(mActionExit);

  /* Menu View */

  QMenu *menuPanels = new QMenu(tr("Dockable panels"), this);
  menuPanels->addAction(ui->dockWidgetProject->toggleViewAction());
  menuPanels->addAction(ui->dockWidgetProperties->toggleViewAction());
  menuPanels->addAction(ui->dockWidgetAssistant->toggleViewAction());
  menuPanels->addAction(ui->dockWidgetConsole->toggleViewAction());
  ui->menuView->addMenu(menuPanels);

  ui->menuView->addSeparator();

  QMenu *menuToolBar = new QMenu(tr("Toolbars"), this);
  menuToolBar->addAction(ui->mainToolBar->toggleViewAction());
//  menuToolBar->addAction(ui->toolBarView->toggleViewAction());
//  menuToolBar->addAction(ui->toolBarWorkflow->toggleViewAction());
//  menuToolBar->addAction(ui->toolBar3dModel->toggleViewAction());
  menuToolBar->addAction(ui->toolBarTools->toggleViewAction());
  ui->menuView->addMenu(menuToolBar);

  /* Menu Tools */

  ui->menuTools->addAction(mActionLoadImages);
  ui->menuTools->addSeparator();
  ui->menuTools->addAction(mActionNewProcessing);
  ui->menuTools->addSeparator();
  ui->menuTools->addAction(mActionAssistant);
  ui->menuTools->addSeparator();
  ui->menuTools->addAction(mActionPreprocess);
  ui->menuTools->addAction(mActionFeatureExtraction);
  ui->menuTools->addAction(mActionFeatureMatching);
  ui->menuTools->addSeparator();
  ui->menuTools->addAction(mActionSettings);

  /* Menu Quality Control */

  QMenu *menuPhotogrammetricQualityControl = new QMenu(tr("Photogrammetric Quality Control"), this);
  menuPhotogrammetricQualityControl->addAction(mActionExportTiePoints);
  menuPhotogrammetricQualityControl->addAction(mActionMatchesViewer);
  ui->menuQualityControl->addMenu(menuPhotogrammetricQualityControl);
  QMenu *menuComputerVisionQualityControl = new QMenu(tr("Computer Vision Quality Control"), this);
  menuComputerVisionQualityControl->addAction(mActionHomography);
  menuComputerVisionQualityControl->addAction(mActionRepeteability);
  menuComputerVisionQualityControl->addAction(mActionRecall);
  ui->menuQualityControl->addMenu(menuComputerVisionQualityControl);

  /* Menu Help */

  ui->menuHelp->addAction(mActionHelp);
  ui->menuHelp->addAction(mActionAbout);

  /* Toolbars */

  ui->mainToolBar->addAction(mActionNewProject);
  ui->mainToolBar->addAction(mActionOpenProject);
  ui->mainToolBar->addAction(mActionSaveProject);
  ui->mainToolBar->addAction(mActionSaveProjectAs);
  ui->toolBarTools->addAction(mActionNewProcessing);
  ui->toolBarTools->addSeparator();
  ui->toolBarTools->addAction(mActionPreprocess);
  ui->toolBarTools->addAction(mActionFeatureExtraction);
  ui->toolBarTools->addAction(mActionFeatureMatching);

  update();
}

void MainWindowView::closeEvent(QCloseEvent *event)
{
  QSettings settings(QSettings::IniFormat, QSettings::UserScope, "TIDOP", "FME");
  settings.setValue("geometry", saveGeometry());
  settings.setValue("windowState", saveState());
  QMainWindow::closeEvent(event);
}

} // namespace fme
