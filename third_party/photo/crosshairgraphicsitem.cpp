#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

#include "crosshairgraphicsitem.h"

CrosshairGraphicsItem::CrosshairGraphicsItem(PW2dPoint *point):
    QGraphicsEllipseItem(point->getCoord(0)-10,point->getCoord(1)-10,20, 20),
    mPoint(point),
    mCrossColor(Qt::blue)
{
    setFlag(ItemSendsGeometryChanges, true);
    setFlag(ItemSendsScenePositionChanges, true);
    setFlag(ItemIgnoresTransformations, true);
}

void CrosshairGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(mCrossColor);
    painter->drawLine(mPoint->getCoord(0)-10, mPoint->getCoord(1), mPoint->getCoord(0)+10, mPoint->getCoord(1));
    painter->drawLine(mPoint->getCoord(0), mPoint->getCoord(1)-10, mPoint->getCoord(0), mPoint->getCoord(1)+10);

    painter->setPen(Qt::red);
    painter->drawText(QRect(mPoint->getCoord(0)+12,mPoint->getCoord(1)-12,100, 100),mPoint->getName());

    QGraphicsEllipseItem::paint(painter,option,widget);
}

QRectF CrosshairGraphicsItem::boundingRect() const
{
    QRectF ellipseBounding = QGraphicsEllipseItem::boundingRect();
    return QRectF(ellipseBounding.topLeft().x(), ellipseBounding.topLeft().y(),
                  ellipseBounding.width()+100, ellipseBounding.height()+22);
}

void CrosshairGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsEllipseItem::mouseReleaseEvent(event);
    emit pointChanged(mPoint, this->scenePos());
}

QVariant CrosshairGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    return QGraphicsEllipseItem::itemChange(change,value);
}

int CrosshairGraphicsItem::type() const
{
    int type = QGraphicsEllipseItem::type();
    return type;
}

void CrosshairGraphicsItem::setCrossColor(QColor color)
{
    mCrossColor = color;
}


