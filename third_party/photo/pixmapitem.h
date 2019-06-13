#ifndef PIXMAPITEM_H
#define PIXMAPITEM_H

#include <QGraphicsPixmapItem>

class PixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    PixmapItem();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

signals:
    void mousePressed(QPoint point);
    void mouseMoved(QPoint point);
    void mouseRightClick(QPoint point);
};

#endif // PIXMAPITEM_H
