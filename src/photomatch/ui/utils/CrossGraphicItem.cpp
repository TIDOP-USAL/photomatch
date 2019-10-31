#include "CrossGraphicItem.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
//#include <QGraphicsRectItem>

namespace photomatch
{

CrossGraphicItem::CrossGraphicItem(QGraphicsItem *parent)
  : QGraphicsItem(parent),
    mCenter(),
    mPen(),
    mSize(10.)
{

}


CrossGraphicItem::CrossGraphicItem(QPointF center, QGraphicsItem *parent)
  : QGraphicsItem(parent),
    mCenter(center),
    mPen(),
    mSize(10.)
{

}

CrossGraphicItem::~CrossGraphicItem()
{

}

QPen CrossGraphicItem::pen() const
{
  return mPen;
}

void CrossGraphicItem::setPen(const QPen &pen)
{
  mPen = pen;
}

double CrossGraphicItem::size()
{
  return mSize;
}

void CrossGraphicItem::setSize(double size)
{
  mSize = size;
}

QRectF CrossGraphicItem::boundingRect() const
{
  double r = mSize / 2.;
  return QRectF(mCenter.x() - r, mCenter.y() - r, mSize, mSize);
}

QPainterPath CrossGraphicItem::shape() const
{
  QPainterPath path;
  double r = mSize / 2.;
  path.addRect(mCenter.x() - r, mCenter.y() - r, mSize, mSize);
  return path;
}

void CrossGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  if (this->isSelected()) {
    QPen pen = mPen;
    pen.setWidth(mPen.width() * 2);
    painter->setPen(pen);
  } else {
    painter->setPen(mPen);
  }  
  int halfSize = static_cast<int>(mSize / 2);
  int x = static_cast<int>(mCenter.x());
  int y = static_cast<int>(mCenter.y());
  painter->drawLine(x - halfSize, y, x + halfSize, y);
  painter->drawLine(x, y - halfSize, x, y + halfSize);
}

} // namespace photomatch
