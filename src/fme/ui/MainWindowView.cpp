#include "MainWindowView.h"
#include "ui_MainWindowView.h"

#include "fme/widgets/ThumbnailsWidget.h"
#include "fme/widgets/LogWidget.h"
#include "fme/ui/utils/GraphicViewer.h"

#include <QTreeWidgetItem>
#include <QFileInfo>
#include <QSettings>
#include <QGraphicsEllipseItem>
#include <QDesktopServices>
#include <QUrl>

namespace fme
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
  descriptor
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
    mActionZoomIn(new QAction(this)),
    mActionZoomOut(new QAction(this)),
    mActionZoomExtend(new QAction(this)),
    mActionZoom11(new QAction(this)),
    mActionShowKeyPoints(new QAction(this)),
    mGraphicViewer(nullptr),
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

  connect(mActionStartPage,    SIGNAL(triggered(bool)), this, SLOT(openStartPage()));

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
  connect(mTreeWidgetProject, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(onItemDoubleClicked(QTreeWidgetItem *, int)));

  connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(hideTab(int)));
  connect(ui->tabWidget, SIGNAL(currentChanged(int)),    this, SLOT(tabChanged(int)));

  connect(mActionShowKeyPoints, SIGNAL(toggled(bool)), this, SLOT(onShowKeyPoints(bool)));

  /* Start Page */
  connect(ui->commandLinkButtonNewProject,   SIGNAL(clicked()),  this, SIGNAL(openNew()));
  connect(ui->commandLinkButtonOpenProject,  SIGNAL(clicked()),  this, SIGNAL(openProject()));
  connect(ui->commandLinkButtonSettings,     SIGNAL(clicked()),  this, SIGNAL(openSettings()));
  connect(ui->commandLinkButtonGitHub,       SIGNAL(clicked()),  this, SLOT(onCommandLinkButtonGitHubClicked()));
  connect(ui->commandLinkButtonClearHistory, SIGNAL(clicked()),  this, SIGNAL(clearHistory()));

  connect(ui->listWidgetRecentProjects,      SIGNAL(currentTextChanged(QString)), this, SIGNAL(openProjectFromHistory(QString)));

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
  ui->treeWidgetProperties->clear();
  mFlags.clear();

  const QSignalBlocker blocker(ui->tabWidget);
  int n = ui->tabWidget->count();
  for (int i = 0; i < n; i++){
    hideTab(0);
  }

  update();
}

void MainWindowView::setProjectTitle(const QString &title)
{
  this->setWindowTitle(QString("FME - ").append(title));

  QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0);
  if (itemProject == nullptr) {
    itemProject = new QTreeWidgetItem();
    //itemProject->setIcon(0, QIcon(":/ico/img/48x48/icons8_file_48px.png"));
    mTreeWidgetProject->addTopLevelItem(itemProject);
    itemProject->setExpanded(true);
    itemProject->setData(0, Qt::UserRole, fme::project);
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
          itemImages->setData(0, Qt::UserRole, fme::images);
          itemProject->addChild(itemImages);
          itemImages->setExpanded(true);
        }

        /* Se añade el fotograma al árbol del proyecto */
        QTreeWidgetItem *itemPhotogram = new QTreeWidgetItem();
        //itemPhotogram->setExpanded(true);
        //itemPhotogram->setCheckState(0, Qt::CheckState::Checked);
        itemPhotogram->setText(0, QFileInfo(image).baseName());
        itemPhotogram->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_image_48px.png"));
        itemPhotogram->setToolTip(0, image);
        itemPhotogram->setData(0, Qt::UserRole, fme::image);
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

void MainWindowView::addSession(const QString &sessionName, const QString &sessionDescription, bool activeSession)
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
      itemSessions->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_add_list_48px.png"));
      itemSessions->setFlags(itemSessions->flags() | Qt::ItemIsTristate);
      itemProject->addChild(itemSessions);
      itemSessions->setExpanded(true);
      itemSessions->setData(0, Qt::UserRole, fme::sessions);
    }

    QTreeWidgetItem *itemSession = new QTreeWidgetItem();
    itemSession->setText(0, sessionName);
    itemSession->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_list_48px.png"));
    itemSession->setToolTip(0, sessionDescription);
    itemSessions->addChild(itemSession);
    QFont font;
    font.setBold(activeSession);
    itemSession->setFont(0, font);
    itemSession->setData(0, Qt::UserRole, fme::session);

    update();
  }
}

void MainWindowView::addPreprocess(const QString &sessionName, const QString &preprocess, const QStringList &preprocessImages)
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

    if (itemSessions != nullptr) {

      QTreeWidgetItem *itemPreprocess = nullptr;
      for (int i = 0; i < itemSessions->childCount(); i++) {
        QTreeWidgetItem *itemSession = itemSessions->child(i);
        if (itemSession){
          if (itemSession->text(0).compare(sessionName) == 0){
            itemPreprocess = new QTreeWidgetItem();
            itemPreprocess->setText(0, QString("Preprocess: ").append(preprocess));
            itemPreprocess->setData(0, Qt::UserRole, fme::preprocess);
            itemSession->addChild(itemPreprocess);
            update();
            break;
          }
        }
      }

      if (itemPreprocess != nullptr){

        QTreeWidgetItem *itemImages = nullptr;
        for (int i = 0; i < itemPreprocess->childCount(); i++) {
          QTreeWidgetItem *temp = itemPreprocess->child(i);
          if (temp->text(0).compare(tr("Images")) == 0) {
            itemImages = itemPreprocess->child(i);
            break;
          }
        }

        if (itemImages == nullptr) {
          itemImages = new QTreeWidgetItem();
          itemImages->setText(0, tr("Images"));
          itemImages->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_documents_folder_48px.png"));
          itemImages->setFlags(itemImages->flags() | Qt::ItemIsTristate);
          itemImages->setData(0, Qt::UserRole, fme::preprocess_images);
          itemPreprocess->addChild(itemImages);
          itemImages->setExpanded(true);
        }

        for (auto image : preprocessImages){
          QTreeWidgetItem *itemPhotogram = new QTreeWidgetItem();
          itemPhotogram->setText(0, QFileInfo(image).baseName());
          itemPhotogram->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_image_48px.png"));
          itemPhotogram->setToolTip(0, image);
          itemPhotogram->setData(0, Qt::UserRole, fme::preprocess_image);
          itemImages->addChild(itemPhotogram);
        }

      }

    }
  }
}

//void MainWindowView::addDetector(const QString &sessionName, const QString &detector)
//{
//  if (QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0)) {

//    /* Sessions */

//    QTreeWidgetItem *itemSessions = nullptr;
//    for (int i = 0; i < itemProject->childCount(); i++) {
//      QTreeWidgetItem *temp = itemProject->child(i);
//      if (temp->text(0).compare(tr("Sessions")) == 0) {
//        itemSessions = itemProject->child(i);
//        break;
//      }
//    }

//    if (itemSessions != nullptr) {

//      for (int i = 0; i < itemSessions->childCount(); i++) {
//        QTreeWidgetItem *itemSession = itemSessions->child(i);
//        if (itemSession){
//          if (itemSession->text(0).compare(sessionName) == 0){
//            QTreeWidgetItem *itemDetector = new QTreeWidgetItem();
//            itemDetector->setText(0, QString("Detector: ").append(detector));
//            itemDetector->setData(0, Qt::UserRole, fme::detector);
//            itemSession->addChild(itemDetector);
//            update();
//            break;
//          }
//        }
//      }
//    }
//  }
//}

//void MainWindowView::addDescriptor(const QString &sessionName, const QString &descriptor)
//{
//  if (QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0)) {

//    /* Sessions */

//    QTreeWidgetItem *itemSessions = nullptr;
//    for (int i = 0; i < itemProject->childCount(); i++) {
//      QTreeWidgetItem *temp = itemProject->child(i);
//      if (temp->text(0).compare(tr("Sessions")) == 0) {
//        itemSessions = itemProject->child(i);
//        break;
//      }
//    }

//    if (itemSessions != nullptr) {

//      for (int i = 0; i < itemSessions->childCount(); i++) {
//        QTreeWidgetItem *itemSession = itemSessions->child(i);
//        if (itemSession){
//          if (itemSession->text(0).compare(sessionName) == 0){
//            QTreeWidgetItem *itemDescriptor = new QTreeWidgetItem();
//            itemDescriptor->setText(0, QString("Descriptor: ").append(descriptor));
//            itemDescriptor->setData(0, Qt::UserRole, fme::descriptor);
//            itemSession->addChild(itemDescriptor);
//            update();
//            break;
//          }
//        }
//      }
//    }
//  }
//}

void MainWindowView::addFeatures(const QString &sessionName, const QString &detector, const QString &descriptor, const QStringList &features)
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

    if (itemSessions != nullptr) {

      QTreeWidgetItem *itemFeatures = nullptr;
      for (int i = 0; i < itemSessions->childCount(); i++) {
        QTreeWidgetItem *itemSession = itemSessions->child(i);
        if (itemSession){
          if (itemSession->text(0).compare(sessionName) == 0){
            itemFeatures = new QTreeWidgetItem();
            itemFeatures->setText(0, QString("Features"));
            itemFeatures->setData(0, Qt::UserRole, fme::features);
            itemSession->addChild(itemFeatures);
            update();
            break;
          }
        }
      }

      if (itemFeatures != nullptr){

        /// Detector
        QTreeWidgetItem *itemDetector = new QTreeWidgetItem();
        itemDetector->setText(0, QString("Detector: ").append(detector));
        itemDetector->setData(0, Qt::UserRole, fme::detector);
        itemFeatures->addChild(itemDetector);

        /// Descriptor
        QTreeWidgetItem *itemDescriptor = new QTreeWidgetItem();
        itemDescriptor->setText(0, QString("Descriptor: ").append(descriptor));
        itemDescriptor->setData(0, Qt::UserRole, fme::descriptor);
        itemFeatures->addChild(itemDescriptor);

        QTreeWidgetItem *itemImagesFeatures = nullptr;
        for (int i = 0; i < itemFeatures->childCount(); i++) {
          QTreeWidgetItem *temp = itemFeatures->child(i);
          if (temp->text(0).compare(tr("Features")) == 0) {
            itemImagesFeatures = itemFeatures->child(i);
            break;
          }
        }

        if (itemImagesFeatures == nullptr) {
          itemImagesFeatures = new QTreeWidgetItem();
          itemImagesFeatures->setText(0, tr("Features"));
          itemImagesFeatures->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_documents_folder_48px.png"));
          itemImagesFeatures->setFlags(itemImagesFeatures->flags() | Qt::ItemIsTristate);
          itemImagesFeatures->setData(0, Qt::UserRole, fme::features_images);
          itemFeatures->addChild(itemImagesFeatures);
          itemImagesFeatures->setExpanded(true);
        }

        for (auto image_features : features) {
          QTreeWidgetItem *itemPhotogram = new QTreeWidgetItem();
          itemPhotogram->setText(0, QFileInfo(image_features).baseName());
          itemPhotogram->setIcon(0, QIcon(":/ico/48/img/material/48/icons8_image_48px.png"));
          itemPhotogram->setToolTip(0, image_features);
          itemPhotogram->setData(0, Qt::UserRole, fme::features_image);
          itemImagesFeatures->addChild(itemPhotogram);
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
      QGraphicsEllipseItem *ellipse = dynamic_cast<QGraphicsEllipseItem *>(item);
      if (ellipse){
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
    contextMenu->addSeparator();
    contextMenu->addAction(mActionShowKeyPoints);
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

bool MainWindowView::showKeyPoints() const
{
  return mActionShowKeyPoints->isChecked();
}

void MainWindowView::setKeyPoints(const std::vector<QPointF> &keyPoints)
{
//  /////////////////////////////////////////////////////////////////////////
//  /// No esta bien aqui...
//  Settings &settings = Settings::instance();
//  QColor color;
//  color.setNamedColor(settings.keyPointsColor());
//  QPen pen(color, 1.);
//  QBrush brush;
//  if (settings.keyPointsBgColor().compare("-") == 0){
//    brush = QBrush(Qt::NoBrush);
//  } else {
//    brush.setColor(QColor(settings.keyPointsBgColor()));
//    brush.setStyle(Qt::SolidPattern);
//  }

//  int symbol = settings.symbol();
//  double symbol_size = settings.symbolSize();
//  double r = symbol_size / 2.;

//  /////////////////////////////////////////////////////////////////////////

  QColor color;
  color.setNamedColor(QString("#00FF00"));
  QPen pen(color, 1.);
  QBrush brush;
  brush = QBrush(Qt::NoBrush);
  double symbol_size = 10.;
  double r = symbol_size / 2.;

  for (size_t i = 0; i < keyPoints.size(); i++){
    QGraphicsEllipseItem *ellipse = mGraphicViewer->scene()->addEllipse(keyPoints[i].x() - r,
                                                                        keyPoints[i].y() - r,
                                                                        r * 2, r * 2, pen, brush);
    ///e->setToolTip("ID punto...");
    ellipse->setFlag(QGraphicsItem::ItemIsSelectable, true);
    //ellipse->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    //ellipse->setToolTip(QString::number(static_cast<int>(i)));
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

  // toolbar viewer
  mActionZoomIn->setEnabled(bImageOpen);
  mActionZoomOut->setEnabled(bImageOpen);
  mActionZoomExtend->setEnabled(bImageOpen);
  mActionZoom11->setEnabled(bImageOpen);
  mActionShowKeyPoints->setEnabled(bImageOpen && mFlags.isActive(Flag::feature_extraction));

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
  if (item[0]->data(0, Qt::UserRole) == fme::project){

  } else if (item[0]->data(0, Qt::UserRole) == fme::images){
  } else if (item[0]->data(0, Qt::UserRole) == fme::image ||
             item[0]->data(0, Qt::UserRole) == fme::preprocess_image){
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
  } else if (item[0]->data(0, Qt::UserRole) == fme::sessions){
    ui->treeWidgetProperties->clear();
  } else if (item[0]->data(0, Qt::UserRole) == fme::session){
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
  } else if (item[0]->data(0, Qt::UserRole) == fme::preprocess){
    int size = item.size();
    if(size > 0){
      if (size == 1) {
        QString session = item[0]->parent()->text(0);
        emit selectPreprocess(session);
      }
    }
  } else if (item[0]->data(0, Qt::UserRole) == fme::features){
    ui->treeWidgetProperties->clear();
    QString session = item[0]->parent()->text(0);
    emit selectFeatures(session);
  } else if (item[0]->data(0, Qt::UserRole) == fme::features_images){
    ui->treeWidgetProperties->clear();
  } else if (item[0]->data(0, Qt::UserRole) == fme::features_image){
    ui->treeWidgetProperties->clear();
  } else if (item[0]->data(0, Qt::UserRole) == fme::detector){
    int size = item.size();
    if(size > 0){
      if (size == 1) {
        QString session = item[0]->parent()->parent()->text(0);
        emit selectDetector(session);
      }
    }
  } else if (item[0]->data(0, Qt::UserRole) == fme::descriptor){
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
  if (item->data(0, Qt::UserRole) == fme::image ||
      item->data(0, Qt::UserRole) == fme::preprocess_image){
    emit openImage(item->toolTip(column));
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

void MainWindowView::onShowKeyPoints(bool show)
{
  if (show){
    // emitir señal con la imagen activa.
    if (ui->tabWidget->count() > 0){
      GraphicViewer *graphicViewer = dynamic_cast<GraphicViewer *>(ui->tabWidget->currentWidget());

      if (graphicViewer){
        QString file_name = ui->tabWidget->tabToolTip(ui->tabWidget->currentIndex());
        emit loadKeyPoints(file_name);
      }
    }
  } else {
    for (auto &item : mGraphicViewer->scene()->items()) {
      QGraphicsEllipseItem *ellipse = dynamic_cast<QGraphicsEllipseItem *>(item);
      if (ellipse){
        mGraphicViewer->scene()->removeItem(item);
      }
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

  mActionLoadImages->setText(QApplication::translate("MainWindowView", "Load Images", nullptr));
  QIcon iconLoadImages;
  iconLoadImages.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_images_folder_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionLoadImages->setIcon(iconLoadImages);

  mActionNewSession->setText(QApplication::translate("MainWindowView", "New Processing", nullptr));
  QIcon iconNewSession;
  iconNewSession.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_add_list_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionNewSession->setIcon(iconNewSession);

  mActionAssistant->setText(QApplication::translate("MainWindowView", "Assistant", nullptr));
  mActionAssistant->setObjectName(QStringLiteral("actionAssistant"));

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

  mActionSettings->setText(QApplication::translate("MainWindowView", "Settings", nullptr));
  QIcon iconSettings;
  iconSettings.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_automatic_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionSettings->setIcon(iconSettings);

  mActionHelp->setText(QApplication::translate("MainWindowView", "Help", nullptr));
  QIcon iconHelp;
  iconHelp.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_help_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionHelp->setIcon(iconHelp);

  mActionAbout->setText(QApplication::translate("MainWindowView", "About", nullptr));
  QIcon iconAbout;
  iconAbout.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_about_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionAbout->setIcon(iconAbout);

  mActionExportTiePoints->setText(QApplication::translate("MainWindowView", "Export Tie Points", nullptr));
  mActionExportTiePoints->setObjectName(QStringLiteral("actionExportTiePoints"));

  mActionMatchesViewer->setText(QApplication::translate("MainWindowView", "Matches Viewer", nullptr));

  mActionHomography->setText(QApplication::translate("MainWindowView", "Homography", nullptr));

  mActionRepeteability->setText(QApplication::translate("MainWindowView", "Repeteability", nullptr));

  mActionRecall->setText(QApplication::translate("MainWindowView", "Recall", nullptr));

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

  mActionShowKeyPoints->setText(QApplication::translate("MainWindowView", "Show Keypoints", nullptr));
  QIcon iconZoomShowKeyPoints;
  iconZoomShowKeyPoints.addFile(QStringLiteral(":/ico/24/img/material/24/keypoints.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionShowKeyPoints->setIcon(iconZoomShowKeyPoints);
  mActionShowKeyPoints->setCheckable(true);

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

  ui->menuView->addAction(mActionStartPage);
  ui->menuView->addSeparator();
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
  menuToolBar->addAction(ui->toolBarView->toggleViewAction());
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

  ui->toolBarTools->addAction(mActionLoadImages);
  ui->toolBarTools->addSeparator();
  ui->toolBarTools->addAction(mActionNewSession);
  ui->toolBarTools->addSeparator();
  ui->toolBarTools->addAction(mActionPreprocess);
  ui->toolBarTools->addAction(mActionFeatureExtraction);
  ui->toolBarTools->addAction(mActionFeatureMatching);

  ui->toolBarView->addAction(mActionZoomIn);
  ui->toolBarView->addAction(mActionZoomOut);
  ui->toolBarView->addAction(mActionZoom11);
  ui->toolBarView->addAction(mActionZoomExtend);
  ui->toolBarView->addSeparator();
  ui->toolBarView->addAction(mActionShowKeyPoints);

  mStartPageWidget = ui->tabWidget->widget(0);

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
