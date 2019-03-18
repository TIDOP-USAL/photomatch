#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "pixmapitem.h"

PixmapItem::PixmapItem()
{
}

void PixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button()==2){
        emit mouseRightClick(QPoint(event->pos().x(),event->pos().y()));
    }
    else{
        emit mousePressed(QPoint(event->pos().x(),event->pos().y()));
    }

    QGraphicsPixmapItem::mousePressEvent(event);
}

void PixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit mouseMoved(QPoint(event->pos().x(),event->pos().y()));
    QGraphicsPixmapItem::mouseMoveEvent(event);
    qDebug() << "Moving*********************************";
}

void PixmapItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit mouseRightClick(QPoint(event->pos().x(),event->pos().y()));
}
