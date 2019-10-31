#include "KeyPointGraphicsItem.h"

#include <tidop/core/defs.h>

#include <QPainter>

namespace photomatch
{

KeyPointGraphicsItem::KeyPointGraphicsItem(QGraphicsItem *parent)
  : QGraphicsItem(parent),
    mCenter(),
    mPen(),
    mBrush(),
    mSize(10.),
    mAngle(0.)
{

}

KeyPointGraphicsItem::KeyPointGraphicsItem(QPointF center, QGraphicsItem *parent)
  : QGraphicsItem(parent),
    mCenter(center),
    mPen(),
    mBrush(),
    mSize(10.),
    mAngle(0.)
{

}

KeyPointGraphicsItem::~KeyPointGraphicsItem()
{

}

QPen KeyPointGraphicsItem::pen() const
{
  return mPen;
}

void KeyPointGraphicsItem::setPen(const QPen &pen)
{
  mPen = pen;
}

QBrush KeyPointGraphicsItem::brush() const
{
  return mBrush;
}

void KeyPointGraphicsItem::setBrush(const QBrush &brush)
{
  mBrush = brush;
}

double KeyPointGraphicsItem::size()
{
  return mSize;
}

void KeyPointGraphicsItem::setSize(double size)
{
  mSize = size;
}

double KeyPointGraphicsItem::angle()
{
  return mAngle;
}

void KeyPointGraphicsItem::setAngle(double angle)
{
  mAngle = angle;
}

QRectF KeyPointGraphicsItem::boundingRect() const
{
  double r = mSize / 2.;
  return QRectF(mCenter.x() - r, mCenter.y() - r, mSize, mSize);
}

QPainterPath KeyPointGraphicsItem::shape() const
{
  QPainterPath path;
  double r = mSize / 2.;
  path.addRect(mCenter.x() - r, mCenter.y() - r, mSize, mSize);
  return path;
}

void KeyPointGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->setPen(mPen);
  painter->setBrush(mBrush);
  double r = mSize / 2.;
  painter->drawEllipse(mCenter, r, r);
  QPointF pt2(mCenter.x() + r * cos(mAngle * TL_DEG_TO_RAD), mCenter.y() + r * sin(mAngle * TL_DEG_TO_RAD));
  painter->drawLine(mCenter, pt2);
}

} // namespace photomatch
