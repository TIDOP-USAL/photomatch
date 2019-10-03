#include "DiagonalCrossGraphicItem.h"

#include <QPainter>

namespace fme
{

DiagonalCrossGraphicItem::DiagonalCrossGraphicItem(QGraphicsItem *parent)
  : QGraphicsItem(parent),
    mCenter(),
    mPen(),
    mSize(10.)
{

}


DiagonalCrossGraphicItem::DiagonalCrossGraphicItem(QPointF center, QGraphicsItem *parent)
  : QGraphicsItem(parent),
    mCenter(center),
    mPen(),
    mSize(10.)
{

}

DiagonalCrossGraphicItem::~DiagonalCrossGraphicItem()
{

}

QPen DiagonalCrossGraphicItem::pen() const
{
  return mPen;
}

void DiagonalCrossGraphicItem::setPen(const QPen &pen)
{
  mPen = pen;
}

double DiagonalCrossGraphicItem::size()
{
  return mSize;
}

void DiagonalCrossGraphicItem::setSize(double size)
{
  mSize = size;
}


QRectF DiagonalCrossGraphicItem::boundingRect() const
{
  double r = mSize / 2.;
  return QRectF(mCenter.x() - r, mCenter.y() - r, mSize, mSize);
}

void DiagonalCrossGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->setPen(mPen);
  int halfSize = static_cast<int>(mSize / 2);
  int x = static_cast<int>(mCenter.x());
  int y = static_cast<int>(mCenter.y());
  painter->drawLine(x - halfSize, y, x + halfSize, y);
  painter->drawLine(x, y - halfSize, x, y + halfSize);

}

} // namespace fme
