#include "TabHandler.h"

#include <QTabBar>
#include <QMenu>
#include <QFileInfo>

#include "photomatch/ui/utils/GraphicViewer.h"
#include "photomatch/ui/utils/GraphicItem.h"

namespace photomatch
{

TabHandler::TabHandler(QWidget *parent)
  : QTabWidget(parent),
    mGraphicViewer(nullptr),
    mActionZoomIn(new QAction(this)),
    mActionZoomOut(new QAction(this)),
    mActionZoomExtend(new QAction(this)),
    mActionZoom11(new QAction(this))
{
  init();

  connect(this, SIGNAL(tabCloseRequested(int)),                     this, SLOT(hideTab(int)));
  connect(this, SIGNAL(currentChanged(int)),                        this, SLOT(onTabChanged(int)));
  connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onTabWidgetContextMenu(const QPoint &)));

}

void TabHandler::hideTab(int tabId)
{
  if (tabId != -1) {
    GraphicViewer *graphicViewer = dynamic_cast<GraphicViewer *>(this->widget(tabId));
    this->removeTab(tabId);
    if (graphicViewer){
      delete graphicViewer;
      graphicViewer = nullptr;
      mGraphicViewer = nullptr;
    }
  }

  update();
}

void TabHandler::setCurrentTab(int tabId)
{
  this->setCurrentIndex(tabId);
  if (GraphicViewer *graphicViewer = dynamic_cast<GraphicViewer *>(this->widget(tabId)))
    mGraphicViewer = graphicViewer;
}

void TabHandler::clear()
{
  int n = this->count();
  for (int i = 0; i < n; i++){
    hideTab(0);
  }

  update();
}

void TabHandler::setImage(const QString &image)
{
  const QSignalBlocker blocker(this);

  QFileInfo fileInfo(image);

  if (mGraphicViewer != nullptr){
    disconnect(mActionZoomIn,      SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomIn()));
    disconnect(mActionZoomOut,     SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomOut()));
    disconnect(mActionZoomExtend,  SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomExtend()));
    disconnect(mActionZoom11,      SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoom11()));

    for (auto &item : mGraphicViewer->scene()->items()) {
      KeyPointGraphicsItem *keyPoints = dynamic_cast<KeyPointGraphicsItem *>(item);
      if (keyPoints){
        mGraphicViewer->scene()->removeItem(item);
      }
    }
  }

  // Carga en nueva pestaña
  int id = -1;
  for (int i = 0; i < this->count(); i++){

    if (this->tabToolTip(i) == image){
      id = i;
      this->setCurrentTab(i);
      break;
    }
  }

  if (id == -1) {
    GraphicViewer *graphicViewer = new GraphicViewer(this);
    mGraphicViewer = graphicViewer;
    mGraphicViewer->setImage(QImage(image));
    id = this->addTab(mGraphicViewer, fileInfo.fileName());
    this->setCurrentIndex(id);
    this->setTabToolTip(id, image);
    mGraphicViewer->zoomExtend();

    QMenu *contextMenu = new QMenu(graphicViewer);
    contextMenu->addAction(mActionZoomIn);
    contextMenu->addAction(mActionZoomOut);
    contextMenu->addAction(mActionZoomExtend);
    contextMenu->addAction(mActionZoom11);
    mGraphicViewer->setContextMenu(contextMenu);
  }

  connect(mActionZoomIn,      SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomIn()));
  connect(mActionZoomOut,     SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomOut()));
  connect(mActionZoomExtend,  SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomExtend()));
  connect(mActionZoom11,      SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoom11()));

  update();
}

GraphicViewer *TabHandler::graphicViewer(int tabId)
{
  return dynamic_cast<GraphicViewer *>(this->widget(tabId));
}

int TabHandler::graphicViewerId(const QString &name)
{
  int id = -1;
  for (int i = 0; i < this->count(); i++){
    if (this->tabToolTip(i) == name){
      id = i;
    }
  }
  return id;
}

GraphicViewer *TabHandler::addGraphicViewer(const QString &name)
{

  if (mGraphicViewer != nullptr){
    disconnect(mActionZoomIn,     SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomIn()));
    disconnect(mActionZoomOut,    SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomOut()));
    disconnect(mActionZoomExtend, SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomExtend()));
    disconnect(mActionZoom11,     SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoom11()));
  }

  int id = this->graphicViewerId(name);

  if (id == -1 ) {
    GraphicViewer *graphicViewer = new GraphicViewer(this);

    QMenu *contextMenu = new QMenu(graphicViewer);
    contextMenu->addAction(mActionZoomIn);
    contextMenu->addAction(mActionZoomOut);
    contextMenu->addAction(mActionZoomExtend);
    contextMenu->addAction(mActionZoom11);
    graphicViewer->setContextMenu(contextMenu);

    id = this->addTab(graphicViewer, name);
    this->setTabToolTip(id, name);
  }

  this->setCurrentTab(id);

  connect(mActionZoomIn,     SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomIn()));
  connect(mActionZoomOut,    SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomOut()));
  connect(mActionZoomExtend, SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoomExtend()));
  connect(mActionZoom11,     SIGNAL(triggered(bool)), mGraphicViewer, SLOT(zoom11()));

  return mGraphicViewer;
}

void TabHandler::onTabChanged(int tabId)
{
  GraphicViewer *graphicViewer = dynamic_cast<GraphicViewer *>(this->widget(tabId));

  if (graphicViewer){
    setImage(this->tabToolTip(tabId));
  } else {
    mGraphicViewer = nullptr;
  }

  update();
}

void TabHandler::onTabWidgetContextMenu(const QPoint &pt)
{
  if (pt.isNull()) return;

  if (this->tabBar() == nullptr) return;

  int tabIndex = this->tabBar()->tabAt(pt);

  if (tabIndex == -1) return;

  QString tabText = this->tabBar()->tabText(tabIndex);

  QMenu menu;
  menu.addAction(tr("Close"));
  menu.addAction(tr("Close all tabs"));
  menu.addAction(tr("Close all tabs but current one"));

  if (QAction *selectedTab = menu.exec(this->tabBar()->mapToGlobal(pt))) {
    if (selectedTab->text() == tr("Close")) {
      hideTab(tabIndex);
    } else if (selectedTab->text() == tr("Close all tabs")) {
      const QSignalBlocker blocker(this);
      int n = this->count();
      for (int i = 0; i < n; i++){
        hideTab(0);
      }
    } else if (selectedTab->text() == tr("Close all tabs but current one")) {
      const QSignalBlocker blocker(this);
      int n = this->count();
      int tabToCloseId = 0;
      for (int i = 0; i < n; i++){
        if (this->tabBar()->tabText(tabToCloseId).compare(tabText) == 0){
          tabToCloseId = 1;
        } else {
          hideTab(tabToCloseId);
        }
      }
    }
    }
}

void TabHandler::update()
{
  bool bImageOpen = (mGraphicViewer != nullptr);
  mActionZoomIn->setEnabled(bImageOpen);
  mActionZoomOut->setEnabled(bImageOpen);
  mActionZoomExtend->setEnabled(bImageOpen);
  mActionZoom11->setEnabled(bImageOpen);
}

void TabHandler::init()
{
  this->setContextMenuPolicy(Qt::CustomContextMenu);
  this->setTabsClosable(true);

  mActionZoomIn->setText(tr("Zoom In"));
  QIcon iconZoomIn;
  iconZoomIn.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_zoom_in_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionZoomIn->setIcon(iconZoomIn);

  mActionZoomOut->setText(tr("Zoom Out"));
  QIcon iconZoomOut;
  iconZoomOut.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_zoom_out_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionZoomOut->setIcon(iconZoomOut);

  mActionZoomExtend->setText(tr("Zoom Extend"));
  QIcon iconZoomExtend;
  iconZoomExtend.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_zoom_to_extents_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionZoomExtend->setIcon(iconZoomExtend);

  mActionZoom11->setText(tr("Zoom 1:1"));
  QIcon iconZoom11;
  iconZoom11.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_zoom_to_actual_size_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mActionZoom11->setIcon(iconZoom11);

}

QAction *TabHandler::actionZoom11() const
{
  return mActionZoom11;
}

QAction *TabHandler::actionZoomExtend() const
{
  return mActionZoomExtend;
}

QAction *TabHandler::actionZoomOut() const
{
  return mActionZoomOut;
}

QAction *TabHandler::actionZoomIn() const
{
  return mActionZoomIn;
}


} // namespace photomatch
