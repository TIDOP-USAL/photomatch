#include "DiagonalCrossGraphicItem.h"

#include <QPainter>

namespace photomatch
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

QPainterPath DiagonalCrossGraphicItem::shape() const
{
  QPainterPath path;
  double r = mSize / 2.;
  path.addRect(mCenter.x() - r, mCenter.y() - r, mSize, mSize);
  return path;
}

void DiagonalCrossGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  if (this->isSelected()) {
    QPen pen = mPen;
    pen.setWidth(mPen.width() * 2);
    painter->setPen(pen);
  } else {
    painter->setPen(mPen);
  }  
  double halfSize = mSize / 2.;
  double x = mCenter.x();
  double y = mCenter.y();
  painter->drawLine(QPointF(x - halfSize, y - halfSize), QPointF(x + halfSize, y + halfSize));
  painter->drawLine(QPointF(x - halfSize, y + halfSize), QPointF(x + halfSize, y - halfSize));
}

} // namespace photomatch
