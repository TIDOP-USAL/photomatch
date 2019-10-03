#include "CrossGraphicItem.h"

#include <QPainter>

namespace fme
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

void CrossGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->setPen(mPen);
  int halfSize = static_cast<int>(mSize / 2);
  int x = static_cast<int>(mCenter.x());
  int y = static_cast<int>(mCenter.y());
  painter->drawLine(x - halfSize, y - halfSize, x + halfSize, y + halfSize);
  painter->drawLine(x - halfSize, y + halfSize, x + halfSize, y - halfSize);
}

} // namespace fme
