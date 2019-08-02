#include "MainWindowView.h"
#include "ui_MainWindowView.h"

#include "fme/widgets/ThumbnailsWidget.h"
#include "fme/widgets/LogWidget.h"

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
  mActionNewSession(new QAction(this)),
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
  connect(mActionNewSession,         SIGNAL(triggered(bool)),   this,   SIGNAL(newSession()));
  connect(mActionAssistant,          SIGNAL(triggered(bool)),   this,   SIGNAL(openAssistant()));
  connect(mActionPreprocess,         SIGNAL(triggered(bool)),   this,   SIGNAL(openPreprocess()));
  connect(mActionFeatureExtraction,  SIGNAL(triggered(bool)),   this,   SIGNAL(openFeatureExtraction()));
  connect(mActionFeatureMatching,    SIGNAL(triggered(bool)),   this,   SIGNAL(openFeatureMatching()));
  connect(mActionSettings,           SIGNAL(triggered(bool)),   this,   SIGNAL(openSettings()));

  /* Menú Ayuda */
  connect(mActionHelp,  SIGNAL(triggered(bool)), this, SIGNAL(openHelpDialog()));
  connect(mActionAbout, SIGNAL(triggered(bool)), this, SIGNAL(openAboutDialog()));

  /* Panel de vistas en miniatura */
  connect(mThumbnailsWidget, SIGNAL(openImage(QString)),        this, SIGNAL(openImage(QString)));
  connect(mThumbnailsWidget, SIGNAL(selectImage(QString)),      this, SIGNAL(selectImage(QString)));
  connect(mThumbnailsWidget, SIGNAL(selectImages(QStringList)), this, SIGNAL(selectImages(QStringList)));
  connect(mThumbnailsWidget, SIGNAL(deleteImages(QStringList)), this, SIGNAL(deleteImages(QStringList)));

  connect(mTreeWidgetProject, SIGNAL(itemSelectionChanged()),   this, SLOT(onSelectionChanged()));
}

MainWindowView::~MainWindowView()
{
  delete ui;
}

void MainWindowView::clear()
{
  setWindowTitle(QString("FME"));
  mTreeWidgetProject->clear();
  mThumbnailsWidget->clear();
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
          itemImages->setIcon(0, QIcon(":/ico/48/img/material/48/icons8-pictures-folder.png"));
          itemImages->setFlags(itemImages->flags() | Qt::ItemIsTristate);
          itemProject->addChild(itemImages);
          itemImages->setExpanded(true);
        }

        /* Se añade el fotograma al árbol del proyecto */
        QTreeWidgetItem *itemPhotogram = new QTreeWidgetItem();
        //itemPhotogram->setExpanded(true);
        //itemPhotogram->setCheckState(0, Qt::CheckState::Checked);
        itemPhotogram->setText(0, QFileInfo(image).baseName());
        itemPhotogram->setIcon(0, QIcon(":/ico/48/img/material/48/icons8-image-file.png"));
        itemPhotogram->setToolTip(0, image);
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
        itemImages->child(i)->setSelected(temp->toolTip(0).compare(image) == 0);
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
          if (temp->toolTip(0).compare(image) == 0){
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
      itemSessions->setIcon(0, QIcon(":/ico/48/img/material/48/icons8-add-list.png"));
      itemSessions->setFlags(itemSessions->flags() | Qt::ItemIsTristate);
      itemProject->addChild(itemSessions);
      itemSessions->setExpanded(true);
    }

    QTreeWidgetItem *itemSession = new QTreeWidgetItem();
    itemSession->setText(0, sessionName);
    itemSession->setIcon(0, QIcon(":/ico/48/img/material/48/icons8-list.png"));
    itemSession->setToolTip(0, sessionDescription);
    itemSessions->addChild(itemSession);

    update();
  }
}

void MainWindowView::setStatusBarMsg(const QString &msg)
{
  ui->statusBar->showMessage(msg, 2000);
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
        if (temp->toolTip(0).compare(file) == 0) {
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
  mActionNewSession->setEnabled(mFlags.isActive(Flag::images_added));
  mActionAssistant->setEnabled(mFlags.isActive(Flag::session_created));
  mActionPreprocess->setEnabled(mFlags.isActive(Flag::session_created));
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

void MainWindowView::onSelectionChanged()
{
  QList<QTreeWidgetItem*> item = mTreeWidgetProject->selectedItems();
  int size = item.size();
  if(size > 0){
    if (size == 1) {
      emit selectImage(item[0]->toolTip(0));
    } else {
      QStringList selected_images;
      for (int i = 0; i < size; i++){
        selected_images.push_back(item[i]->toolTip(0));
      }
      emit selectImages(selected_images);
    }
  }
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

  mActionNewSession->setText(QApplication::translate("MainWindowView", "New Processing", nullptr));
  mActionNewSession->setObjectName(QStringLiteral("actionNewProcessing"));
  QIcon icon7;
  icon7.addFile(QStringLiteral(":/ico/24/img/material/24/icons8-add-list.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionNewSession->setIcon(icon7);

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

  /* Thumbnails */
  QGridLayout *gridLayoutThumb = new QGridLayout(ui->dockWidgetThumbContents);
  gridLayoutThumb->setSpacing(6);
  gridLayoutThumb->setContentsMargins(11, 11, 11, 11);
  gridLayoutThumb->setContentsMargins(0, 0, 0, 0);
  mThumbnailsWidget = new ThumbnailsWidget(ui->dockWidgetThumbContents);
  gridLayoutThumb->addWidget(mThumbnailsWidget, 0, 0, 1, 1);

  /* Log */
  QGridLayout *gridLayoutConsole = new QGridLayout(ui->dockWidgetContentsConsole);
  gridLayoutConsole->setSpacing(6);
  gridLayoutConsole->setContentsMargins(11, 11, 11, 11);
  gridLayoutConsole->setContentsMargins(0, 0, 0, 0);
  mLogWidget = new LogWidget(ui->dockWidgetThumbContents);
  gridLayoutConsole->addWidget(mLogWidget, 0, 0, 1, 1);

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
  ui->menuTools->addAction(mActionNewSession);
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
  ui->toolBarTools->addAction(mActionNewSession);
  ui->toolBarTools->addSeparator();
  ui->toolBarTools->addAction(mActionPreprocess);
  ui->toolBarTools->addAction(mActionFeatureExtraction);
  ui->toolBarTools->addAction(mActionFeatureMatching);

  // Configuración de mensajes
  tl::MessageManager &msg_h = tl::MessageManager::instance();
  msg_h.addListener(mLogWidget);

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
