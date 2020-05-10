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


#ifndef PHOTOMATCH_GRAPHIC_VIEWER_H
#define PHOTOMATCH_GRAPHIC_VIEWER_H

#include <memory>

#include <QGraphicsView>
#include <QMenu>
#include <QGraphicsEllipseItem>

// Default zoom factors
#define DEFAULT_ZOOM_FACTOR 1.15
#define DEFAULT_ZOOM_CTRL_FACTOR 1.01

namespace photomatch
{

/*!
 * \brief The GraphicViewer class
 */
class GraphicViewer
{

public:

  /*!
   * \brief IGraphicViewer
   */
  GraphicViewer() {}
  virtual ~GraphicViewer() = default;

  /*!
   * \brief Establece la imagen
   * \param[in] image QImage que se muestra
   */
  virtual void setImage(const QImage &image) = 0;

  /*!
   * \brief Establecer la imagen a partir de datos en bruto
   * \param[in] data Datos de la imagen en bruto (data format is RGBRGBRGBRGB ...)
   * \param[in] width Ancho de la imagen
   * \param[in] height Alto de la imagen
   */
  virtual void setImageFromRawData(const uchar *data, int width, int height) = 0;

  /*!
   * \brief Establecer el factor de zoom cuando la tecla CTRL no se presiona
   * \param factor zoom factor (>1)
   */
  virtual void setZoomFactor(const double factor) = 0;


  /*!
   * \brief Establezca el factor de zoom cuando se presiona la tecla CTRL
   * \param factor zoom factor (>1)
   */
  virtual void setZoomCtrlFactor(const double factor) = 0;

  /*!
   * \brief Zoom extensión
   */
  virtual void zoomExtend() = 0;

  /*!
   * \brief Zoom a resolución 1:1
   */
  virtual void zoom11() = 0;

  /*!
   * \brief zoom +
   * \param point
   */
  virtual void zoomIn(QPoint point = QPoint()) = 0;

  /*!
   * \brief zoom -
   * \param point
   */
  virtual void zoomOut(QPoint point = QPoint()) = 0;

  virtual void setContextMenu(QMenu *contextMenu) = 0;

protected:

  /*!
   * \brief Mostrar el menú contextual (al hacer clic con el botón derecho)
   * \param[in] pos Posición del mouse en el widget
   */
  virtual void showContextMenu(const QPoint &pos) = 0;

};


class GraphicViewerImp
  : public QGraphicsView,
    public GraphicViewer
{
  Q_OBJECT

public:
    
  GraphicViewerImp(QWidget *parent = nullptr);
    
  ~GraphicViewerImp() override;

  /*!
   * \brief Establece la imagen
   * \param[in] image QImage que se muestra
   */
  virtual void setImage(const QImage &image) override;

  /*!
   * \brief Establecer la imagen a partir de datos en bruto
   * \param[in] data Datos de la imagen en bruto (data format is RGBRGBRGBRGB ...)
   * \param[in] width Ancho de la imagen
   * \param[in] height Alto de la imagen
   */
  virtual void setImageFromRawData(const uchar *data, int width, int height) override;

  /*!
   * \brief Establecer el factor de zoom cuando la tecla CTRL no se presiona
   * \param factor zoom factor (>1)
   */
  virtual void setZoomFactor(const double factor) override;


  /*!
   * \brief Establezca el factor de zoom cuando se presiona la tecla CTRL
   * \param factor zoom factor (>1)
   */
  virtual void setZoomCtrlFactor(const double factor) override;
  
  void setContextMenu(QMenu *contextMenu) override;

protected:

  virtual void drawOnImage(QPainter *painter, QSize imageSize);
  virtual void drawInViewPort(QPainter *painter, QSize portSize);
  virtual void drawForeground(QPainter *painter, const QRectF &rect) override;

  /*!
   * \brief mousePressEvent
   * \param event Evento del ratón
   */
  virtual void mousePressEvent(QMouseEvent *event) override;

  /*!
   * \brief mouseReleaseEvent
   * \param event Evento del ratón
   */
  virtual void mouseReleaseEvent(QMouseEvent *event) override;

  virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

#ifndef QT_NO_WHEELEVENT

  /*!
   * \brief wheelEvent Evento movimiento rueda del ratón
   * \param event Evento rueda ratón
   */
  virtual void wheelEvent(QWheelEvent *event) override;

#endif

  /*!
   * \brief Evento de movimiento del ratón
   * \param event Evento del ratón
   */
  virtual void mouseMoveEvent(QMouseEvent *event) override;

  /*!
   * \brief Evento redimensión
   * \param event Evento resize
   */
  virtual void resizeEvent(QResizeEvent *event) override;

public slots:

  virtual void zoomExtend() override;
  virtual void zoom11() override;
  virtual void zoomIn(QPoint point = QPoint()) override;
  virtual void zoomOut(QPoint point = QPoint()) override;

protected slots:

  /*!
   * \brief showContextMenu       Display the contextual menu (on right click)
   * \param pos                   Position of the mouse in the widget
   */
  virtual void showContextMenu(const QPoint &position) override;

private:
 
  void init();

signals:

  void mousePosition(QPoint);
  void mouseClicked(QPoint);
  void mouseClicked(QPointF);
  void selectionChanged();

protected:

  // Scene where the image is drawn
  QGraphicsScene *mScene;

  // Pixmap item containing the image
  QGraphicsPixmapItem *mPixmapItem;

  /*!
   * \brief Tamaño de la imagen
   */
  QSize mImageSize;

  QMenu *mContextMenu;

  /*!
   * \brief Factor de zoom
   */
  double mZoomFactor;

  /*!
   * \brief Factor de zoom cuando la tecla ctrl esta presionada
   */
  double mZoomCtrlFactor;

  QPixmap mPixmap;

  QPoint mPointOld;
};


} // namespace photomatch

#endif // PHOTOMATCH_GRAPHIC_VIEWER_H
