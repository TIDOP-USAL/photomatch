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


#include "GraphicViewer.h"

#include <QWheelEvent>
#include <QMessageBox>
#include <QGraphicsPixmapItem>

#include <QApplication>
#include <QMenu>

namespace photomatch
{

GraphicViewerImp::GraphicViewerImp(QWidget *parent)
  : QGraphicsView(parent),
    GraphicViewer(),
    mScene(new QGraphicsScene()),
    mPixmapItem(nullptr),
    mContextMenu(nullptr),
    mZoomFactor(DEFAULT_ZOOM_FACTOR),
    mZoomCtrlFactor(DEFAULT_ZOOM_CTRL_FACTOR)
{
  init();

  connect(mScene, SIGNAL(selectionChanged()), this, SIGNAL(selectionChanged()));

}

GraphicViewerImp::~GraphicViewerImp()
{
  if (mPixmapItem) {
    delete mPixmapItem;
    mPixmapItem = nullptr;
  }
  if (mScene) {
    delete mScene;
    mScene = nullptr;
  }
}

void GraphicViewerImp::init()
{
  // Permitir el seguimiento del mouse incluso si no se presiona ningún botón
  this->setMouseTracking(true);

  // Añade la escena al QGraphicsView
  this->setScene(mScene);

  this->setBackgroundBrush(QBrush(QColor(220,220,220), Qt::SolidPattern));

  // Actualiza toda la ventana de observación cuando sea necesario, de lo contrario, el drawInViewPort puede experimentar problemas
  this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

  // Al hacer zoom, la vista permanece centrada sobre el mouse
  this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

  this->setResizeAnchor(QGraphicsView::AnchorViewCenter);

  // Add the default pixmap at startup
  mPixmapItem = mScene->addPixmap(mPixmap);

}

void GraphicViewerImp::setImage(const QImage &image)
{
  // Update the pixmap in the scene
  if (image.isGrayscale()){
    mPixmap = QPixmap::fromImage(image.convertToFormat(QImage::Format::Format_RGB888));
  } else {
    mPixmap = QPixmap::fromImage(image);
  }

  mPixmapItem->setPixmap(mPixmap);

  mScene->setSceneRect(QRect(QPoint(0,0), image.size()));

  mImageSize = image.size();
}

void GraphicViewerImp::setImageFromRawData(const uchar *data, int width, int height)
{
  QImage image(data, width, height, width*3, QImage::Format_RGB888);
  setImage(image);
}

void GraphicViewerImp::setZoomFactor(const double factor)
{
  mZoomFactor = factor;
}

void GraphicViewerImp::setZoomCtrlFactor(const double factor)
{
  mZoomCtrlFactor = factor;
}

void GraphicViewerImp::setContextMenu(QMenu *contextMenu)
{
  mContextMenu = contextMenu;
  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
}

void GraphicViewerImp::drawOnImage(QPainter *painter, QSize imageSize)
{

}

void GraphicViewerImp::drawInViewPort(QPainter *painter, QSize portSize)
{

}

void GraphicViewerImp::drawForeground(QPainter *painter, const QRectF &rect)
{
//  // Call the function to draw over the image
//  drawOnImage(painter, mImageSize);

//  // Reset transformation and call the function draw in the view port
//  painter->resetTransform();

//  // Call the function to draw in the view port
//  drawInViewPort(painter, viewport()->size());
}

void GraphicViewerImp::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton)
    setDragMode(QGraphicsView::ScrollHandDrag);

  mPointOld = event->pos();

  QGraphicsView::mousePressEvent(event);
}

void GraphicViewerImp::mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton){

    if (this->dragMode() == QGraphicsView::ScrollHandDrag){
      setDragMode(QGraphicsView::NoDrag);
    }

    if (event->pos() == mPointOld){
      QPointF imagePoint = mapToScene(QPoint(event->x(), event->y()));
      emit mouseClicked(imagePoint);
    }

  }

  QGraphicsView::mouseReleaseEvent(event);
}

void GraphicViewerImp::mouseDoubleClickEvent(QMouseEvent *event)
{
  //QPoint pt(event->x(), event->y());
  //QGraphicsItem *item = this->itemAt(pt);
  //QGraphicsEllipseItem *ell = qgraphicsitem_cast<QGraphicsEllipseItem *>(item);
  //if (ell){
  //  QBrush br(Qt::SolidPattern);
  //  br.setColor(Qt::black);
  //  ell->setBrush(br);
  //  ell->update();
  //}

  QGraphicsView::mouseDoubleClickEvent(event);
}

#ifndef QT_NO_WHEELEVENT

void GraphicViewerImp::wheelEvent(QWheelEvent *event)
{
  setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

  double factor = (event->modifiers() & Qt::ControlModifier) ? mZoomCtrlFactor : mZoomFactor;
  if(event->delta() > 0)
    // Zoom +
    scale(factor, factor);
  else {
    // Zoom -
    factor = 1.0 / factor;
    scale(factor, factor);
  }

  event->accept();
}

#endif

void GraphicViewerImp::mouseMoveEvent(QMouseEvent *event)
{
  // es QPoint(event->x(), event->y()) == event->pos() ???
  //QPointF imagePoint = mapToScene(QPoint(event->x(), event->y()));

  if (event->pos() == mPointOld){

  }
  //setToolTip(setToolTipText(QPoint((int)imagePoint.x(),(int)imagePoint.y())));

//  if (event->button() == Qt::LeftButton){
//    setDragMode(QGraphicsView::ScrollHandDrag);
//  }

  QGraphicsView::mouseMoveEvent(event);
}

void GraphicViewerImp::resizeEvent(QResizeEvent *event)
{
  if(event->oldSize().width() == -1 || event->oldSize().height() == -1) return;

  // Get the previous rectangle of the scene in the viewport
  QPointF P1 = mapToScene(QPoint(0,0));
  QPointF P2 = mapToScene(QPoint(event->oldSize().width(), event->oldSize().height()));

  // Stretch the rectangle around the scene
  if (P1.x() < 0) P1.setX(0);
  if (P1.y() < 0) P1.setY(0);
  if (P2.x() > mScene->width()) P2.setX(mScene->width());
  if (P2.y() > mScene->height()) P2.setY(mScene->height());

  // Fit the previous area in the scene
  this->fitInView(QRect(P1.toPoint(), P2.toPoint()), Qt::KeepAspectRatio);
}

void GraphicViewerImp::zoomExtend()
{
  Qt::ScrollBarPolicy	currentHorizontalPolicy = horizontalScrollBarPolicy();
  Qt::ScrollBarPolicy	currentverticalPolicy = verticalScrollBarPolicy();

  // Disable scroll bar to avoid a margin around the image
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  
  fitInView(mScene->sceneRect(), Qt::KeepAspectRatio);

  // Restaure scroll bar policy
  setHorizontalScrollBarPolicy(currentHorizontalPolicy);
  setVerticalScrollBarPolicy(currentverticalPolicy);
}

void GraphicViewerImp::zoom11()
{
  double scale11 = 1. / transform().m11();
  scale(scale11, scale11);
}

void GraphicViewerImp::zoomIn()
{
  scale(mZoomFactor, mZoomFactor);
}

void GraphicViewerImp::zoomOut()
{
  double factor = 1.0 / mZoomFactor;
  scale(factor, factor);
}

void GraphicViewerImp::showContextMenu(const QPoint &position)
{
  // Get the mouse position in the scene
  QPoint globalPos = mapToGlobal(position);

  // Display the menu
  mContextMenu->exec(globalPos);
}

} // namespace photomatch
