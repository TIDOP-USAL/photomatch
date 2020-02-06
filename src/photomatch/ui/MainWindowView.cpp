#include "MainWindowView.h"
#include "ui_MainWindowView.h"

#include "photomatch/widgets/ThumbnailsWidget.h"
#include "photomatch/widgets/LogWidget.h"
#include "photomatch/ui/utils/GraphicViewer.h"
#include "photomatch/ui/utils/GraphicItem.h"

#include <QTreeWidgetItem>
#include <QFileInfo>
#include <QSettings>
#include <QGraphicsEllipseItem>
#include <QDesktopServices>
#include <QUrl>
#include <QComboBox>
#include <QProgressBar>

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
    mActionNewProject(new QAction(this)),
    mActionOpenProject(new QAction(this)),
    mActionSaveProject(new QAction(this)),
    mActionSaveProjectAs(new QAction(this)),
    mActionCloseProject(new QAction(this)),
    mActionExit(new QAction(this)),
    mActionStartPage(new QAction(this)),
    mActionLoadImages(new QAction(this)),
    mActionNewSession(new QAction(this)),
    mActionPreprocess(new QAction(this)),
    mActionFeatureExtraction(new QAction(this)),
    mActionFeatureMatching(new QAction(this)),
    //mActionBatch(new QAction(this)),
    mActionViewSettings(new QAction(this)),
    mActionToolSettings(new QAction(this)),
    mActionHelp(new QAction(this)),
    mActionOnlineHelp(new QAction(this)),
    mActionAbout(new QAction(this)),
    mActionExportTiePoints(new QAction(this)),
    mActionExportMatches(new QAction(this)),
    mActionFeaturesViewer(new QAction(this)),
    mActionMatchesViewer(new QAction(this)),
    mActionPassPointsViewer(new QAction(this)),
    mActionGroundTruthEditor(new QAction(this)),
    mActionHomography(new QAction(this)),
    //mActionRepeatability(new QAction(this)),
    mActionPRCurves(new QAction(this)),
    mActionROCCurves(new QAction(this)),
    mActionDETCurves(new QAction(this)),
    mActionQualityControlSettings(new QAction(this)),
    mActionNotRecentProjects(new QAction(this)),
    mActionClearHistory(new QAction(this)),
    mActionZoomIn(new QAction(this)),
    mActionZoomOut(new QAction(this)),
    mActionZoomExtend(new QAction(this)),
    mActionZoom11(new QAction(this)),
    mActionSetSession(new QAction(this)),
    mActionDeleteSession(new QAction(this)),
    mGraphicViewer(nullptr),
    mComboBoxActiveSession(new QComboBox(this)),
    ui(new Ui::MainWindowView)
{
  ui->setupUi(this);

  init();

  /* Menú Archivo */

  connect(mActionNewProject,           SIGNAL(triggered(bool)), this,   SIGNAL(openNew()));
  connect(mActionOpenProject,          SIGNAL(triggered(bool)), this,   SIGNAL(openProject()));
  connect(mActionClearHistory,         SIGNAL(triggered(bool)), this,   SIGNAL(clearHistory()));
  connect(mActionSaveProject,          SIGNAL(triggered(bool)), this,   SIGNAL(saveProject()));
  connect(mActionSaveProjectAs,        SIGNAL(triggered(bool)), this,   SIGNAL(saveProjectAs()));
  connect(mActionExportTiePoints,      SIGNAL(triggered(bool)), this,   SIGNAL(exportTiePoints()));
  connect(mActionExportMatches,        SIGNAL(triggered(bool)), this,   SIGNAL(exportMatches()));
  connect(mActionCloseProject,         SIGNAL(triggered(bool)), this,   SIGNAL(closeProject()));
  connect(mActionExit,                 SIGNAL(triggered(bool)), this,   SIGNAL(exit()));

  /* Menú View */

  connect(mActionStartPage,          SIGNAL(triggered(bool)),   this,   SLOT(openStartPage()));
  connect(mActionViewSettings,       SIGNAL(triggered(bool)),   this,   SIGNAL(openViewSettings()));

  /* Menú herramientas */

  connect(mActionLoadImages,         SIGNAL(triggered(bool)),   this,   SIGNAL(loadImages()));
  connect(mActionNewSession,         SIGNAL(triggered(bool)),   this,   SIGNAL(newSession()));
  connect(mActionPreprocess,         SIGNAL(triggered(bool)),   this,   SIGNAL(openPreprocess()));
  connect(mActionFeatureExtraction,  SIGNAL(triggered(bool)),   this,   SIGNAL(openFeatureExtraction()));
  connect(mActionFeatureMatching,    SIGNAL(triggered(bool)),   this,   SIGNAL(openFeatureMatching()));
  //connect(mActionBatch,              SIGNAL(triggered(bool)),   this,   SIGNAL(openBatch()));
  connect(mActionToolSettings,       SIGNAL(triggered(bool)),   this,   SIGNAL(openToolSettings()));

  /* Quality Control */

  connect(mActionFeaturesViewer,     SIGNAL(triggered(bool)),   this,   SIGNAL(featuresViewer()));
  connect(mActionMatchesViewer,      SIGNAL(triggered(bool)),   this,   SIGNAL(matchesViewer()));
  connect(mActionPassPointsViewer,   SIGNAL(triggered(bool)),   this,   SIGNAL(passPointsViewer()));
  connect(mActionGroundTruthEditor,  SIGNAL(triggered(bool)),   this,   SIGNAL(groundTruthEditor()));
  connect(mActionHomography,         SIGNAL(triggered(bool)),   this,   SIGNAL(homography()));
  //connect(mActionRepeatability,      SIGNAL(triggered(bool)),   this,   SIGNAL(repeatability()));
  connect(mActionPRCurves,           SIGNAL(triggered(bool)),   this,   SIGNAL(prCurves()));
  connect(mActionROCCurves,          SIGNAL(triggered(bool)),   this,   SIGNAL(rocCurves()));
  connect(mActionDETCurves,          SIGNAL(triggered(bool)),   this,   SIGNAL(detCurves()));
  connect(mActionQualityControlSettings,       SIGNAL(triggered(bool)),   this,   SIGNAL(openQualityControlSettings()));


  /* Menú Ayuda */

  connect(mActionHelp,               SIGNAL(triggered(bool)),   this,   SIGNAL(openHelpDialog()));
  connect(mActionOnlineHelp,         SIGNAL(triggered(bool)),   this,   SIGNAL(openOnlineHelp()));
  connect(mActionAbout,              SIGNAL(triggered(bool)),   this,   SIGNAL(openAboutDialog()));

  /* Panel de vistas en miniatura */

  connect(mThumbnailsWidget,  SIGNAL(openImage(QString)),        this, SIGNAL(openImage(QString)));
  connect(mThumbnailsWidget,  SIGNAL(selectImage(QString)),      this, SIGNAL(selectImage(QString)));
  connect(mThumbnailsWidget,  SIGNAL(selectImages(QStringList)), this, SIGNAL(selectImages(QStringList)));
  connect(mThumbnailsWidget,  SIGNAL(deleteImages(QStringList)), this, SIGNAL(deleteImages(QStringList)));

  connect(mTreeWidgetProject, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onTreeContextMenu(const QPoint &)));
  connect(mTreeWidgetProject, SIGNAL(itemSelectionChanged()),   this, SLOT(onSelectionChanged()));
  connect(mTreeWidgetProject, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(onItemDoubleClicked(QTreeWidgetItem *, int)));

  connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(hideTab(int)));
  connect(ui->tabWidget, SIGNAL(currentChanged(int)),    this, SLOT(tabChanged(int)));
  connect(ui->tabWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onTabWidgetContextMenu(const QPoint &)));

  /* Start Page */
  connect(ui->commandLinkButtonNewProject,   SIGNAL(clicked()),  this, SIGNAL(openNew()));
  connect(ui->commandLinkButtonOpenProject,  SIGNAL(clicked()),  this, SIGNAL(openProject()));
  connect(ui->commandLinkButtonSettings,     SIGNAL(clicked()),  this, SIGNAL(openSettings()));
  connect(ui->commandLinkButtonGitHub,       SIGNAL(clicked()),  this, SLOT(onCommandLinkButtonGitHubClicked()));
  connect(ui->commandLinkButtonClearHistory, SIGNAL(clicked()),  this, SIGNAL(clearHistory()));

  connect(ui->listWidgetRecentProjects,      SIGNAL(currentTextChanged(QString)), this, SIGNAL(openProjectFromHistory(QString)));

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

  const QSignalBlocker blocker(ui->tabWidget);
  int n = ui->tabWidget->count();
  for (int i = 0; i < n; i++){
    hideTab(0);
  }

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

            for (int i = 0; i < itemSession->childCount(); i++) {
              if (QTreeWidgetItem *temp = itemSession->child(i)) {
                if (temp->text(0).compare(tr("Preprocess")) == 0) {
                  itemPreprocess = itemSession->child(i);
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

            for (int i = 0; i < itemSession->childCount(); i++) {
              if (QTreeWidgetItem *temp = itemSession->child(i)){
                if (temp->text(0).compare(tr("Features")) == 0) {
                  itemFeatures = itemSession->child(i);
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

            for (int i = 0; i < itemSession->childCount(); i++) {
              if (QTreeWidgetItem *temp = itemSession->child(i)){
                if (temp->text(0).compare(tr("Matches")) == 0) {
                  itemMatches = itemSession->child(i);
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

QTabWidget *MainWindowView::tabWidget()
{
  return ui->tabWidget;
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
  const QSignalBlocker blocker(ui->listWidgetRecentProjects);
  ui->listWidgetRecentProjects->clear();
  ui->listWidgetRecentProjects->addItems(history);
  update();
}

void MainWindowView::deleteHistory()
{
  while (mHistory.size() > 0) {
    disconnect(mHistory[0], SIGNAL(triggered()), this, SLOT(openFromHistory()));
    mMenuRecentProjects->removeAction(mHistory[0]);
    mHistory.erase(mHistory.begin());
  }

  ui->listWidgetRecentProjects->clear();

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

void MainWindowView::deleteSession(const QString &session)
{

  int id = mComboBoxActiveSession->findText(session);
  if (id != -1){
    mComboBoxActiveSession->removeItem(id);
  }

  if (QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0)) {
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
              delete itemSession;
              itemSession = nullptr;
              break;
            }
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

            for (int i = 0; i < itemSession->childCount(); i++) {
              if (QTreeWidgetItem *temp = itemSession->child(i)) {
                if (temp->text(0).compare(tr("Preprocess")) == 0) {
                  itemPreprocess = itemSession->child(i);
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

            for (int i = 0; i < itemSession->childCount(); i++) {
              if (QTreeWidgetItem *temp = itemSession->child(i)){
                if (temp->text(0).compare(tr("Features")) == 0) {
                  itemFeatures = itemSession->child(i);
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

            for (int i = 0; i < itemSession->childCount(); i++) {
              if (QTreeWidgetItem *temp = itemSession->child(i)){
                if (temp->text(0).compare(tr("Matches")) == 0) {
                  itemMatches = itemSession->child(i);
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
              for (int i = 0; i < itemLeftImage->childCount(); i++) {
                QTreeWidgetItem *temp = itemLeftImage->child(i);
                if (temp && temp->toolTip(0).compare(matches) == 0) {
                  itemRightImage = itemLeftImage->child(i);
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

void MainWindowView::showImage(const QString &file)
{
  const QSignalBlocker blocker(ui->tabWidget);

  QFileInfo fileInfo(file);

  if (mGraphicViewer != nullptr){
    disconnect(mActionZoomIn,      SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomIn()));
    disconnect(mActionZoomOut,     SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomOut()));
    disconnect(mActionZoomExtend,  SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomExtend()));
    disconnect(mActionZoom11,      SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoom11()));
    //mGraphicViewer->deleteKeyPoints();
    for (auto &item : mGraphicViewer->scene()->items()) {
      KeyPointGraphicsItem *keyPoints = dynamic_cast<KeyPointGraphicsItem *>(item);
      if (keyPoints){
        mGraphicViewer->scene()->removeItem(item);
      }
    }
  }

  // Carga en nueva pestaña
  int id = -1;
  for (int i = 0; i < ui->tabWidget->count(); i++){

    if (ui->tabWidget->tabToolTip(i) == file){
      id = i;
      mGraphicViewer = static_cast<GraphicViewer *>(ui->tabWidget->widget(i));
      ui->tabWidget->setCurrentIndex(id);
      break;
    }
  }

  if (id == -1) {
    GraphicViewer *graphicViewer = new GraphicViewer(this);
    mGraphicViewer = graphicViewer;
    mGraphicViewer->setImage(QImage(file));
    id = ui->tabWidget->addTab(mGraphicViewer, fileInfo.fileName());
    ui->tabWidget->setCurrentIndex(id);
    ui->tabWidget->setTabToolTip(id, file);
    mGraphicViewer->zoomExtend();

    QMenu *contextMenu = new QMenu(graphicViewer);
    contextMenu->addAction(mActionZoomIn);
    contextMenu->addAction(mActionZoomOut);
    contextMenu->addAction(mActionZoomExtend);
    contextMenu->addAction(mActionZoom11);
    //contextMenu->addSeparator();
    //contextMenu->addAction(mActionShowKeyPoints);
    mGraphicViewer->setContextMenu(contextMenu);
  }

  connect(mActionZoomIn,      SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomIn()));
  connect(mActionZoomOut,     SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomOut()));
  connect(mActionZoomExtend,  SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomExtend()));
  connect(mActionZoom11,      SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoom11()));

  mFlags.activeFlag(Flag::image_open, true);

  emit selectImage(file);

  update();
}

//bool MainWindowView::showKeyPoints() const
//{
//  return mActionShowKeyPoints->isChecked();
//}

void MainWindowView::addKeyPoint(const QPointF &pt, double size, double angle)
{
  QColor color;
  color.setNamedColor(QString("#00FF00"));
  QPen pen(color, 2.);
  QBrush brush;
  brush = QBrush(Qt::NoBrush);

  KeyPointGraphicsItem *item = new KeyPointGraphicsItem(pt, size, angle);
  item->setPen(pen);
  item->setToolTip(QString("Size: ").append(QString::number(size)).append("\nAngle: ").append(QString::number(angle)));
  if (mGraphicViewer) 
    mGraphicViewer->scene()->addItem(item);
}

void MainWindowView::showMatches(const QString &pairLeft, const QString &pairRight,
                                 const std::vector<std::pair<QPointF, QPointF> > &matches)
{
  const QSignalBlocker blocker(ui->tabWidget);

  QFileInfo fileInfoLeft(pairLeft);
  QFileInfo fileInfoRight(pairRight);

  if (mGraphicViewer != nullptr){
    disconnect(mActionZoomIn, SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomIn()));
    disconnect(mActionZoomOut, SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomOut()));
    disconnect(mActionZoomExtend, SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomExtend()));
    disconnect(mActionZoom11, SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoom11()));
    for (auto &item : mGraphicViewer->scene()->items()) {
      QGraphicsEllipseItem *ellipse = dynamic_cast<QGraphicsEllipseItem *>(item);
      if (ellipse){
        mGraphicViewer->scene()->removeItem(item);
      }
    }
  }

  QString name(fileInfoLeft.baseName());
  name.append("-").append(fileInfoRight.baseName());

  // Carga en nueva pestaña
  int id = -1;
  for (int i = 0; i < ui->tabWidget->count(); i++){

    if (ui->tabWidget->tabToolTip(i) == name){
      id = i;
      mGraphicViewer = static_cast<GraphicViewer *>(ui->tabWidget->widget(i));
      ui->tabWidget->setCurrentIndex(id);
    }
  }

  if (id == -1) {
    GraphicViewer *graphicViewer = new GraphicViewer(this);
    mGraphicViewer = graphicViewer;
    QImage imageLeft(pairLeft);
    QImage imageRight(pairRight);
    int height = imageLeft.height() > imageRight.height() ? imageLeft.height() : imageRight.height();
    QImage pair(imageLeft.width() + imageRight.width(), height, imageLeft.format());

    QPainter painter;
    painter.begin(&pair);
    painter.drawImage(0, 0, imageLeft);
    painter.drawImage(imageLeft.width(), 0, imageRight);
    QPen point_pen(QColor(0, 0, 255), 2.);
    point_pen.setCosmetic(true);
    QPen line_pen(QColor(229, 9, 127), 2.);
    line_pen.setCosmetic(true);
    painter.end();

    mGraphicViewer->setImage(pair);

    for (size_t i = 0; i < matches.size(); i++){
      mGraphicViewer->scene()->addLine(matches[i].first.x(), matches[i].first.y(),
                                       imageLeft.width() + matches[i].second.x(),
                                       matches[i].second.y(), line_pen);
      mGraphicViewer->scene()->addEllipse(matches[i].first.x() - 5, matches[i].first.y() - 5, 10, 10, point_pen);
      mGraphicViewer->scene()->addEllipse(imageLeft.width() + matches[i].second.x() - 5, matches[i].second.y() - 5, 10, 10, point_pen);
    }

    id = ui->tabWidget->addTab(mGraphicViewer, name);
    ui->tabWidget->setCurrentIndex(id);
    ui->tabWidget->setTabToolTip(id, name);
    mGraphicViewer->zoomExtend();

    QMenu *contextMenu = new QMenu(graphicViewer);
    contextMenu->addAction(mActionZoomIn);
    contextMenu->addAction(mActionZoomOut);
    contextMenu->addAction(mActionZoomExtend);
    contextMenu->addAction(mActionZoom11);
    //contextMenu->addSeparator();
    //contextMenu->addAction(ui->actionShowKeyPoints);
    // Show all matches
    // Show inliers matches
    mGraphicViewer->setContextMenu(contextMenu);

    //emit loadMatches(pairLeft, pairRight);
  }

  connect(mActionZoomIn, SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomIn()));
  connect(mActionZoomOut, SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomOut()));
  connect(mActionZoomExtend, SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomExtend()));
  connect(mActionZoom11, SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoom11()));

  //mFlags.activeFlag(Flag::images_open, true);

  //emit selectImage(file);

  update();
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

  mActionNewProject->setEnabled(!bProcessing);
  mActionOpenProject->setEnabled(!bProcessing);
  mMenuRecentProjects->setEnabled(!bProcessing);
  mActionSaveProject->setEnabled(bProjectExists && bProjectModified && !bProcessing);
  mActionSaveProjectAs->setEnabled(bProjectExists && !bProcessing);
  mActionCloseProject->setEnabled(bProjectExists && !bProcessing);
  mActionExit->setEnabled(!bProcessing);


  mActionLoadImages->setEnabled(bProjectExists && !bProcessing);
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

  // toolbar viewer
  mActionZoomIn->setEnabled(bImageOpen);
  mActionZoomOut->setEnabled(bImageOpen);
  mActionZoomExtend->setEnabled(bImageOpen);
  mActionZoom11->setEnabled(bImageOpen);
  //mActionShowKeyPoints->setEnabled(bImageOpen && mFlags.isActive(Flag::feature_extraction));

  mComboBoxActiveSession->setDisabled(bProcessing);
  mActionSetSession->setDisabled(bProcessing);
  mActionDeleteSession->setDisabled(bProcessing);
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
  } else if (item[0]->data(0, Qt::UserRole) == photomatch::image ||
             item[0]->data(0, Qt::UserRole) == photomatch::preprocess_image){
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
  } else if (item[0]->data(0, Qt::UserRole) == photomatch::sessions){
    ui->treeWidgetProperties->clear();
  } else if (item[0]->data(0, Qt::UserRole) == photomatch::session){
    int size = item.size();
    if(size > 0){
      if (size == 1) {
        emit selectSession(item[0]->text(0));
      } /*else {
        QStringList selected_images;
        for (int i = 0; i < size; i++){
          selected_images.push_back(item[i]->toolTip(0));
        }
        emit selectImages(selected_images);
      }*/
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

void MainWindowView::hideTab(int id)
{
  if (id != -1) {
    GraphicViewer *graphicViewer = dynamic_cast<GraphicViewer *>(ui->tabWidget->widget(id));
    ui->tabWidget->removeTab(id);
    if (graphicViewer){
      delete graphicViewer;
      graphicViewer = nullptr;
      mGraphicViewer = nullptr;
    }
  }

  update();
}

void MainWindowView::tabChanged(int id)
{
  GraphicViewer *graphicViewer = dynamic_cast<GraphicViewer *>(ui->tabWidget->widget(id));

  if (graphicViewer){
    emit openImage(ui->tabWidget->tabToolTip(id));
  } else {
    mFlags.activeFlag(Flag::image_open, false);
  }

  update();
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
     emit openFeatures(session, QFileInfo(item->text(column)).baseName());
   }
  }
}

void MainWindowView::openStartPage()
{
  const QSignalBlocker blocker(ui->tabWidget);
  if (mStartPageWidget){
    int id = -1;
    for (int i = 0; i < ui->tabWidget->count(); i++){

      if (ui->tabWidget->tabText(i) == tr("Start Page")){
        id = i;
        ui->tabWidget->setCurrentIndex(id);
        break;
      }
    }

    if (id == -1) {
      id = ui->tabWidget->addTab(mStartPageWidget, tr("Start Page"));
      ui->tabWidget->setCurrentIndex(id);
      ui->tabWidget->setTabToolTip(id, tr("Start Page"));
    }
  }
}

void MainWindowView::onCommandLinkButtonGitHubClicked()
{
  QDesktopServices::openUrl(QUrl("https://github.com/Luisloez89/FME"));
}

//void MainWindowView::onShowKeyPoints(bool show)
//{
//  if (show){
//    // emitir señal con la imagen activa.
//    if (ui->tabWidget->count() > 0){
//      GraphicViewer *graphicViewer = dynamic_cast<GraphicViewer *>(ui->tabWidget->currentWidget());

//      if (graphicViewer){
//        QString file_name = ui->tabWidget->tabToolTip(ui->tabWidget->currentIndex());
//        emit loadKeyPoints(file_name);
//      }
//    }
//  } else {
//    for (auto &item : mGraphicViewer->scene()->items()) {
//      KeyPointGraphicsItem *kp = dynamic_cast<KeyPointGraphicsItem *>(item);
//      if (kp){
//        mGraphicViewer->scene()->removeItem(item);
//      }
//    }
//  }
//}

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
  } else if (item->data(0, Qt::UserRole) == photomatch::image ||
             item->data(0, Qt::UserRole) == photomatch::preprocess_image){
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
        emit deleteImages(QStringList(item->toolTip(0)));
      }
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
        emit openFeatures(session, QFileInfo(item->text(0)).baseName());
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
        emit openMatches(session, QFileInfo(item->text(0)).baseName(), QString());
      }
    }
  } else if (item->data(0, Qt::UserRole) == photomatch::pair_right){
    QMenu menu;
    menu.addAction(tr("View Matches"));
    if (QAction *selectedItem = menu.exec(globalPos)) {
      if (selectedItem->text() == tr("View Matches")) {
        QString session = item->parent()->parent()->parent()->parent()->text(0);
        emit openMatches(session, QFileInfo(item->parent()->text(0)).baseName(), QFileInfo(item->text(0)).baseName());
      }
    }
  }

}

void MainWindowView::onTabWidgetContextMenu(const QPoint &point)
{
  if (point.isNull()) return;

  int tabIndex = ui->tabWidget->tabBar()->tabAt(point);

  if (tabIndex == -1) return;

  //ui->tabWidget->widget(tabIndex);
  QString tabText = ui->tabWidget->tabBar()->tabText(tabIndex);

  QMenu menu;
  menu.addAction(tr("Close"));
  menu.addAction(tr("Close all tabs"));
  menu.addAction(tr("Close all tabs but current one"));
  QAction* selectedTab = menu.exec(ui->tabWidget->tabBar()->mapToGlobal(point));
  if (selectedTab) {
    if (selectedTab->text() == tr("Close")) {
      hideTab(tabIndex);
    } else if (selectedTab->text() == tr("Close all tabs")) {
      const QSignalBlocker blocker(ui->tabWidget);
      int n = ui->tabWidget->count();
      for (int i = 0; i < n; i++){
        hideTab(0);
      }
    } else if (selectedTab->text() == tr("Close all tabs but current one")) {
      const QSignalBlocker blocker(ui->tabWidget);
      int n = ui->tabWidget->count();
      int tabToCloseId = 0;
      for (int i = 0; i < n; i++){
        if (ui->tabWidget->tabBar()->tabText(tabToCloseId).compare(tabText) == 0){
          tabToCloseId = 1;
        } else {
          hideTab(tabToCloseId);
        }
      }
    }
  }
}

void MainWindowView::init()
{
  setWindowTitle(QString("PhotoMatch"));

  mActionNewProject->setText(QApplication::translate("MainWindowView", "New Project", nullptr));
#ifndef QT_NO_SHORTCUT
  mActionNewProject->setShortcut(QApplication::translate("MainWindowView", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
  QIcon iconNewProject;
  iconNewProject.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_file_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionNewProject->setIcon(iconNewProject);

  mActionOpenProject->setText(QApplication::translate("MainWindowView", "Open Project", nullptr));
#ifndef QT_NO_SHORTCUT
  mActionOpenProject->setShortcut(QApplication::translate("MainWindowView", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
  QIcon iconOpenProject;
  iconOpenProject.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_opened_folder_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionOpenProject->setIcon(iconOpenProject);

  mActionSaveProject->setText(QApplication::translate("MainWindowView", "Save Project", nullptr));
  #ifndef QT_NO_SHORTCUT
    mActionSaveProject->setShortcut(QApplication::translate("MainWindowView", "Ctrl+S", nullptr));
  #endif // QT_NO_SHORTCUT
  QIcon iconSaveProject;
  iconSaveProject.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_save_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionSaveProject->setIcon(iconSaveProject);

  mActionSaveProjectAs->setText(QApplication::translate("MainWindowView", "Save Project As...", nullptr));
  #ifndef QT_NO_SHORTCUT
    mActionSaveProjectAs->setShortcut(QApplication::translate("MainWindowView", "Ctrl+Shift+S", nullptr));
  #endif // QT_NO_SHORTCUT
  QIcon iconSaveProjectAs;
  iconSaveProjectAs.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_save_as_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionSaveProjectAs->setIcon(iconSaveProjectAs);

  mActionExportTiePoints->setText(QApplication::translate("MainWindowView", "Export tie points", nullptr));
//  QIcon iconExportTiePointsCvXml;
//  iconExportTiePointsCvXml.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_xml_file_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
//  mActionExportTiePoints->setIcon(iconExportTiePointsCvXml);

  mActionExportMatches->setText(QApplication::translate("MainWindowView", "Export Matches", nullptr));


//  mActionExportTiePointsCvXml->setText(QApplication::translate("MainWindowView", "Export tie points to OpenCV XML", nullptr));
//  mActionExportTiePointsCvXml->setObjectName(QStringLiteral("actionExportTiePointsCvXml"));
//  QIcon iconExportTiePointsCvXml;
//  iconExportTiePointsCvXml.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_xml_file_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
//  mActionExportTiePointsCvXml->setIcon(iconExportTiePointsCvXml);

//  mActionExportTiePointsCvYml->setText(QApplication::translate("MainWindowView", "Export tie points to OpenCV YML", nullptr));
//  mActionExportTiePointsCvYml->setObjectName(QStringLiteral("actionExportTiePointsCvYml"));
//  QIcon iconExportTiePointsCvYml;
//  iconExportTiePointsCvYml.addFile(QStringLiteral(":/ico/24/img/material/24/yml_file_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
//  mActionExportTiePointsCvYml->setIcon(iconExportTiePointsCvYml);

//  mActionExportMatchesToCvXml->setText(QApplication::translate("MainWindowView", "Export matches to OpenCV XML", nullptr));
//  mActionExportMatchesToCvXml->setObjectName(QStringLiteral("actionExportMatchesToCvXml"));
//  QIcon iconExportMatchesToCvXml;
//  iconExportMatchesToCvXml.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_xml_file_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
//  mActionExportMatchesToCvXml->setIcon(iconExportMatchesToCvXml);

//  mActionExportMatchesToCvYml->setText(QApplication::translate("MainWindowView", "Export matches to OpenCV YML", nullptr));
//  mActionExportMatchesToCvYml->setObjectName(QStringLiteral("actionExportMatchesToCvYml"));
//  QIcon iconExportMatchesToCvYml;
//  iconExportMatchesToCvYml.addFile(QStringLiteral(":/ico/24/img/material/24/yml_file_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
//  mActionExportMatchesToCvYml->setIcon(iconExportMatchesToCvYml);

//  mActionExportMatchesToTxt->setText(QApplication::translate("MainWindowView", "Export matches to txt", nullptr));
//  mActionExportMatchesToTxt->setObjectName(QStringLiteral("actionExportMatchesToCvYml"));
//  QIcon iconExportMatchesToTxt;
//  iconExportMatchesToTxt.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_txt_24px"), QSize(), QIcon::Normal, QIcon::Off);
//  mActionExportMatchesToTxt->setIcon(iconExportMatchesToTxt);

  mActionCloseProject->setText(QApplication::translate("MainWindowView", "Close Project", nullptr));
  QIcon icon4;
  icon4.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_delete_sign_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionCloseProject->setIcon(icon4);

  mActionExit->setText(QApplication::translate("MainWindowView", "Exit", nullptr));
  #ifndef QT_NO_SHORTCUT
    mActionExit->setShortcut(QApplication::translate("MainWindowView", "Ctrl+F4", nullptr));
  #endif // QT_NO_SHORTCUT
  mActionExit->setObjectName(QStringLiteral("actionExit"));
  QIcon iconExit;
  iconExit.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_shutdown_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionExit->setIcon(iconExit);

  mActionStartPage->setText(QApplication::translate("MainWindowView", "Start Page", nullptr));
  QIcon iconStartPage;
  iconStartPage.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_home_page_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionStartPage->setIcon(iconStartPage);

  mActionViewSettings->setText(QApplication::translate("MainWindowView", "View Settings", nullptr));
  QIcon iconSettingsView;
  iconSettingsView.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_automatic_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionViewSettings->setIcon(iconSettingsView);

  mActionLoadImages->setText(QApplication::translate("MainWindowView", "Load Images", nullptr));
  QIcon iconLoadImages;
  iconLoadImages.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_images_folder_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionLoadImages->setIcon(iconLoadImages);

  mActionNewSession->setText(QApplication::translate("MainWindowView", "New Session", nullptr));
  QIcon iconNewSession;
  iconNewSession.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_add_list_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionNewSession->setIcon(iconNewSession);

//  mActionAssistant->setText(QApplication::translate("MainWindowView", "Assistant", nullptr));
//  mActionAssistant->setObjectName(QStringLiteral("actionAssistant"));

  mActionPreprocess->setText(QApplication::translate("MainWindowView", "Preprocess", nullptr));
  QIcon iconPreprocess;
  iconPreprocess.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_services_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionPreprocess->setIcon(iconPreprocess);

  mActionFeatureExtraction->setText(QApplication::translate("MainWindowView", "Feature Extraction", nullptr));
  QIcon iconFeatureExtraction;
  iconFeatureExtraction.addFile(QStringLiteral(":/ico/24/img/material/24/features.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionFeatureExtraction->setIcon(iconFeatureExtraction);

  mActionFeatureMatching->setText(QApplication::translate("MainWindowView", "Feature Matching", nullptr));
  QIcon iconFeatureMatching;
  iconFeatureMatching.addFile(QStringLiteral(":/ico/24/img/material/24/match_view.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionFeatureMatching->setIcon(iconFeatureMatching);

  //mActionBatch->setText(QApplication::translate("MainWindowView", "Batch", nullptr));

  mActionToolSettings->setText(QApplication::translate("MainWindowView", "Tools Settings", nullptr));
  QIcon iconSettings;
  iconSettings.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_automatic_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionToolSettings->setIcon(iconSettings);

  mActionHelp->setText(QApplication::translate("MainWindowView", "Help", nullptr));
#ifndef QT_NO_SHORTCUT
  mActionHelp->setShortcut(QApplication::translate("MainWindowView", "F1", nullptr));
#endif // QT_NO_SHORTCUT
  QIcon iconHelp;
  iconHelp.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_help_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionHelp->setIcon(iconHelp);

  mActionOnlineHelp->setText(QApplication::translate("MainWindowView", "Online Help", nullptr));
#ifndef QT_NO_SHORTCUT
#endif // QT_NO_SHORTCUT
  QIcon iconOnlineHelp;
  iconOnlineHelp.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_help_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionOnlineHelp->setIcon(iconOnlineHelp);

  mActionAbout->setText(QApplication::translate("MainWindowView", "About", nullptr));
  QIcon iconAbout;
  iconAbout.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_about_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionAbout->setIcon(iconAbout);

  //mActionExportTiePoints->setText(QApplication::translate("MainWindowView", "Export Tie Points", nullptr));
  //mActionExportTiePoints->setObjectName(QStringLiteral("actionExportTiePoints"));

  mActionFeaturesViewer->setText(QApplication::translate("MainWindowView", "Keypoints Viewer", nullptr));

  mActionMatchesViewer->setText(QApplication::translate("MainWindowView", "Matches Viewer", nullptr));

  mActionPassPointsViewer->setText(QApplication::translate("MainWindowView", "Pass Points Viewer", nullptr));

  mActionGroundTruthEditor->setText(QApplication::translate("MainWindowView", "Ground Truth Editor", nullptr));

  mActionHomography->setText(QApplication::translate("MainWindowView", "Homography", nullptr));

  //mActionRepeatability->setText(QApplication::translate("MainWindowView", "Repeatability", nullptr));

  mActionPRCurves->setText(QApplication::translate("MainWindowView", "Precision-Recall Curves", nullptr));
  QIcon iconPRCurves;
  iconPRCurves.addFile(QStringLiteral(":/ico/24/img/material/24/pr_curve_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionPRCurves->setIcon(iconPRCurves);

  mActionROCCurves->setText(QApplication::translate("MainWindowView", "ROC Curves", nullptr));
  QIcon iconROCCurves;
  iconROCCurves.addFile(QStringLiteral(":/ico/24/img/material/24/roc_curve_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionROCCurves->setIcon(iconROCCurves);

  mActionDETCurves->setText(QApplication::translate("MainWindowView", "DET Curves", nullptr));
  QIcon iconDETCurves;
  iconDETCurves.addFile(QStringLiteral(":/ico/24/img/material/24/det_curve_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionDETCurves->setIcon(iconDETCurves);

  mActionQualityControlSettings->setText(QApplication::translate("MainWindowView", "Quality Control Settings", nullptr));
  QIcon iconQualityControlSettings;
  iconQualityControlSettings.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_automatic_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionQualityControlSettings->setIcon(iconQualityControlSettings);

  mActionNotRecentProjects->setText(QApplication::translate("MainWindowView", "Not recent projects", nullptr));
  mActionNotRecentProjects->setEnabled(false);

  mActionClearHistory->setText(QApplication::translate("MainWindowView", "Clear History", nullptr));
  QIcon icon_delete_trash;
  icon_delete_trash.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_delete_trash_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionClearHistory->setIcon(icon_delete_trash);

  mActionZoomIn->setText(QApplication::translate("MainWindowView", "Zoom In", nullptr));
  QIcon iconZoomIn;
  iconZoomIn.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_zoom_in_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionZoomIn->setIcon(iconZoomIn);

  mActionZoomOut->setText(QApplication::translate("MainWindowView", "Zoom Out", nullptr));
  QIcon iconZoomOut;
  iconZoomOut.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_zoom_out_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionZoomOut->setIcon(iconZoomOut);

  mActionZoomExtend->setText(QApplication::translate("MainWindowView", "Zoom Extend", nullptr));
  QIcon iconZoomExtend;
  iconZoomExtend.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_zoom_to_extents_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionZoomExtend->setIcon(iconZoomExtend);

  mActionZoom11->setText(QApplication::translate("MainWindowView", "Zoom 1:1", nullptr));
  QIcon iconZoom11;
  iconZoom11.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_zoom_to_actual_size_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionZoom11->setIcon(iconZoom11);

//  mActionShowKeyPoints->setText(QApplication::translate("MainWindowView", "Show Keypoints", nullptr));
//  QIcon iconZoomShowKeyPoints;
//  iconZoomShowKeyPoints.addFile(QStringLiteral(":/ico/24/img/material/24/keypoints.png"), QSize(), QIcon::Normal, QIcon::Off);
//  mActionShowKeyPoints->setIcon(iconZoomShowKeyPoints);
//  mActionShowKeyPoints->setCheckable(true);

  mActionSetSession->setText(QApplication::translate("MainWindowView", "Set as current session", nullptr));

  mActionDeleteSession->setText(QApplication::translate("MainWindowView", "Delete session", nullptr));
  QIcon iconDeleteSession;
  iconDeleteSession.addFile(QStringLiteral(":/ico/24/img/material/24/delete_list_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionDeleteSession->setIcon(iconDeleteSession);

  /* Árbol de proyecto */
  //ui->dockWidgetContentsProject->setContentsMargins(0, 0, 0, 0);
  mTreeWidgetProject = new QTreeWidget(ui->dockWidgetContentsProject);
  mTreeWidgetProject->setContextMenuPolicy(Qt::CustomContextMenu);
  mTreeWidgetProject->header()->close();
  mTreeWidgetProject->setColumnCount(1);
  mTreeWidgetProject->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
  mTreeWidgetProject->header()->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
  mTreeWidgetProject->header()->setStretchLastSection(false);
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
  mMenuExport = new QMenu(tr("Export"), this);
  mMenuExport->addAction(mActionExportTiePoints);
  mMenuExport->addAction(mActionExportMatches);
  //mMenuExportTiePoints = new QMenu(tr("Tie Points"), this);
  //mMenuExportMatches = new QMenu(tr("Matches"), this);
  //mMenuExportTiePoints->addAction(mActionExportTiePointsCvXml);
  //mMenuExportTiePoints->addAction(mActionExportTiePointsCvYml);
  //mMenuExportMatches->addAction(mActionExportMatchesToCvXml);
  //mMenuExportMatches->addAction(mActionExportMatchesToCvYml);
  //mMenuExportMatches->addAction(mActionExportMatchesToTxt);
  //mMenuExport->addMenu(mMenuExportTiePoints);
  //mMenuExport->addMenu(mMenuExportMatches);
  ui->menuFile->addMenu(mMenuExport);
  ui->menuFile->addSeparator();
  ui->menuFile->addAction(mActionCloseProject);
  ui->menuFile->addSeparator();
  ui->menuFile->addAction(mActionExit);

  /* Menu View */

  ui->menuView->addAction(mActionStartPage);
  ui->menuView->addSeparator();
  QMenu *menuPanels = new QMenu(tr("Dockable panels"), this);
  menuPanels->addAction(ui->dockWidgetProject->toggleViewAction());
  menuPanels->addAction(ui->dockWidgetProperties->toggleViewAction());
  menuPanels->addAction(ui->dockWidgetConsole->toggleViewAction());
  menuPanels->addAction(ui->dockWidgetThumb->toggleViewAction());
  ui->menuView->addMenu(menuPanels);

  ui->menuView->addSeparator();

  QMenu *menuToolBar = new QMenu(tr("Toolbars"), this);
  menuToolBar->addAction(ui->mainToolBar->toggleViewAction());
  menuToolBar->addAction(ui->toolBarTools->toggleViewAction());
  menuToolBar->addAction(ui->toolBarView->toggleViewAction());
  menuToolBar->addAction(ui->toolBarQualityControl->toggleViewAction());
  ui->menuView->addMenu(menuToolBar);

  ui->menuView->addSeparator();

  ui->menuView->addAction(mActionViewSettings);

  /* Menu Tools */

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

  /* Menu Quality Control */

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

  /* Menu Help */

  ui->menuHelp->addAction(mActionHelp);
  ui->menuHelp->addAction(mActionOnlineHelp);
  ui->menuHelp->addSeparator();
  ui->menuHelp->addAction(mActionAbout);

  /* Toolbars */

  ui->mainToolBar->addAction(mActionNewProject);
  ui->mainToolBar->addAction(mActionOpenProject);
  ui->mainToolBar->addAction(mActionSaveProject);
  ui->mainToolBar->addAction(mActionSaveProjectAs);

  ui->toolBarTools->addAction(mActionLoadImages);
  ui->toolBarTools->addSeparator();
  ui->toolBarTools->addAction(mActionNewSession);
  ui->toolBarTools->addSeparator();
  ui->toolBarTools->addWidget(new QLabel(tr("Active Session: "), this));
  mComboBoxActiveSession->setMinimumWidth(100);
  mComboBoxActiveSession->setContentsMargins(8,0,0,0);
  ui->toolBarTools->addWidget(mComboBoxActiveSession);
  ui->toolBarTools->addSeparator();
  ui->toolBarTools->addAction(mActionPreprocess);
  ui->toolBarTools->addAction(mActionFeatureExtraction);
  ui->toolBarTools->addAction(mActionFeatureMatching);
//  ui->toolBarTools->addSeparator();
//  ui->toolBarTools->addAction(mActionBatch);

  ui->toolBarView->addAction(mActionZoomIn);
  ui->toolBarView->addAction(mActionZoomOut);
  ui->toolBarView->addAction(mActionZoom11);
  ui->toolBarView->addAction(mActionZoomExtend);
  //ui->toolBarView->addSeparator();
  //ui->toolBarView->addAction(mActionShowKeyPoints);

  //ui->toolBarQualityControl->addAction(mActionPRCurves);
  ui->toolBarQualityControl->addAction(mActionROCCurves);
  ui->toolBarQualityControl->addAction(mActionDETCurves);

  mStartPageWidget = ui->tabWidget->widget(0);

  mProgressBar = new QProgressBar(this);
  mProgressBar->setVisible(false);
  mProgressBar->setMaximumSize(150, 20);
  ui->statusBar->addPermanentWidget(mProgressBar);

  // Configuración de mensajes
  tl::MessageManager &msg_h = tl::MessageManager::instance();
  msg_h.addListener(mLogWidget);

  update();
}

void MainWindowView::closeEvent(QCloseEvent *event)
{
  QSettings settings(QSettings::IniFormat, QSettings::UserScope, "TIDOP", "PhotoMatch");
  settings.setValue("geometry", saveGeometry());
  settings.setValue("windowState", saveState());
  QMainWindow::closeEvent(event);
}

} // namespace photomatch
