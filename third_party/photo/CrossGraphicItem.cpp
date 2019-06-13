#include <QPainter>
#include "CrossGraphicItem.h"

CrossGraphicItem::CrossGraphicItem(QPointF center):
    mCenter(center)
{
}

void CrossGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::blue);
    painter->drawLine(mCenter.x()-10, mCenter.y(), mCenter.x()+10, mCenter.y());
    painter->drawLine(mCenter.x(), mCenter.y()-10, mCenter.x(), mCenter.y()+10);
}

QRectF CrossGraphicItem::boundingRect() const
{
    return QRectF(mCenter.x()-10, mCenter.y()-10, 22, 22);
}

int CrossGraphicItem::type() const
{
//    return Type;
    return 9999;
}

QPainterPath CrossGraphicItem::shape() const
{
    QPainterPath path;
    path.addRect(mCenter.x()-10, mCenter.y()-10, 22, 22);
    return path;
}
