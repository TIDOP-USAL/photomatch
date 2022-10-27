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


#include "GraphicItem.h"

#include <tidop/core/defs.h>
#include <tidop/math/math.h>

#include <QPainter>
#include <QStyleOptionGraphicsItem>

namespace photomatch
{

CircleGraphicItem::CircleGraphicItem(QGraphicsItem *parent)
  : GraphicItem(parent),
    mCenter(),
    mPen(),
    mSize(10.)
{
  mSelectedPen.setColor(QColor(QString("#FF0000")));
  mSelectedPen.setWidth(2);
  mSelectedPen.setCosmetic(true);
}

CircleGraphicItem::CircleGraphicItem(const QPointF &center, double size, QGraphicsItem *parent)
  : GraphicItem(parent),
    mCenter(center),
    mPen(),
    mSize(size)
{
  mSelectedPen.setColor(QColor(QString("#FF0000")));
  mSelectedPen.setWidth(2);
  mSelectedPen.setCosmetic(true);
}

CircleGraphicItem::~CircleGraphicItem()
{

}

QPen CircleGraphicItem::pen() const
{
  return mPen;
}

void CircleGraphicItem::setPen(const QPen &pen)
{
  mPen = pen;
}

double CircleGraphicItem::size()
{
  return mSize;
}

void CircleGraphicItem::setSize(double size)
{
  mSize = size;
}

QPen CircleGraphicItem::selectedPen() const
{
  return mSelectedPen;
}

void CircleGraphicItem::setSelectedPen(const QPen &pen)
{
  mSelectedPen = pen;
}

QRectF CircleGraphicItem::boundingRect() const
{
  double r = mSize / 2.;
  return QRectF(mCenter.x() - r, mCenter.y() - r, mSize, mSize);
}

QPainterPath CircleGraphicItem::shape() const
{
  QPainterPath path;
  double r = mSize / 2.;
  path.addRect(mCenter.x() - r, mCenter.y() - r, mSize, mSize);
  return path;
}

void CircleGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  if (this->isSelected()) {
    painter->setPen(mSelectedPen);
  } else {
    painter->setPen(mPen);
  }
  double halfSize = mSize / 2.;
  painter->drawEllipse(mCenter, halfSize, halfSize);
}




CrossGraphicItem::CrossGraphicItem(QGraphicsItem *parent)
  : GraphicItem(parent),
    mCenter(),
    mPen(),
    mSize(10.)
{
  mSelectedPen.setColor(QColor(QString("#FF0000")));
  mSelectedPen.setWidth(2);
  mSelectedPen.setCosmetic(true);
}


CrossGraphicItem::CrossGraphicItem(const QPointF &center, double size, QGraphicsItem *parent)
  : GraphicItem(parent),
    mCenter(center),
    mPen(),
    mSize(size)
{
  mSelectedPen.setColor(QColor(QString("#FF0000")));
  mSelectedPen.setWidth(2);
  mSelectedPen.setCosmetic(true);
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

QPen CrossGraphicItem::selectedPen() const
{
  return mSelectedPen;
}

void CrossGraphicItem::setSelectedPen(const QPen &pen)
{
  mSelectedPen = pen;
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
    painter->setPen(mSelectedPen);
  } else {
    painter->setPen(mPen);
  }
  double halfSize = mSize / 2.;
  double x = mCenter.x();
  double y = mCenter.y();
  painter->drawLine(QPointF(x - halfSize, y), QPointF(x + halfSize, y));
  painter->drawLine(QPointF(x, y - halfSize), QPointF(x, y + halfSize));
}





KeyPointGraphicsItem::KeyPointGraphicsItem(QGraphicsItem *parent)
  : GraphicItem(parent),
    mCenter(),
    mPen(),
    mSize(10.),
    mAngle(0.)
{
  mSelectedPen.setColor(QColor(QString("#FF0000")));
  mSelectedPen.setWidth(2);
  mSelectedPen.setCosmetic(true);
}

KeyPointGraphicsItem::KeyPointGraphicsItem(QPointF center, double size, double angle, QGraphicsItem *parent)
  : GraphicItem(parent),
    mCenter(center),
    mPen(),
    mSize(size),
    mAngle(angle)
{
  mSelectedPen.setColor(QColor(QString("#FF0000")));
  mSelectedPen.setWidth(2);
  mSelectedPen.setCosmetic(true);
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

QPen KeyPointGraphicsItem::selectedPen() const
{
  return mSelectedPen;
}

void KeyPointGraphicsItem::setSelectedPen(const QPen &pen)
{
  mSelectedPen = pen;
}

QRectF KeyPointGraphicsItem::boundingRect() const
{
  double r = mSize / 2.;
  return QRectF(mCenter.x() - r, mCenter.y() - r, mSize, mSize);
}

QPainterPath KeyPointGraphicsItem::shape() const
{
  QPainterPath path;
  double r = 5/*mSize*/ / 2.;
  path.addRect(mCenter.x() - r, mCenter.y() - r, mSize, mSize);
  return path;
}

void KeyPointGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  if (this->isSelected()) {
    painter->setPen(mSelectedPen);
  } else {
    painter->setPen(mPen);
  }
  double r = mSize / 2.;
  painter->drawEllipse(mCenter, r, r);
  QPointF pt2(mCenter.x() + r * cos(mAngle * tl::math::consts::deg_to_rad<float>), mCenter.y() + r * sin(mAngle * tl::math::consts::deg_to_rad<float>));
  painter->drawLine(mCenter, pt2);
}




DiagonalCrossGraphicItem::DiagonalCrossGraphicItem(QGraphicsItem *parent)
  : GraphicItem(parent),
    mCenter(),
    mPen(),
    mSize(10.)
{
  mSelectedPen.setColor(QColor(QString("#FF0000")));
  mSelectedPen.setWidth(2);
  mSelectedPen.setCosmetic(true);
}


DiagonalCrossGraphicItem::DiagonalCrossGraphicItem(const QPointF &center, double size, QGraphicsItem *parent)
  : GraphicItem(parent),
    mCenter(center),
    mPen(),
    mSize(size),
    mSelectedPen(QColor(QString("#FF0000")))
{
  mSelectedPen.setColor(QColor(QString("#FF0000")));
  mSelectedPen.setWidth(2);
  mSelectedPen.setCosmetic(true);
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

QPen DiagonalCrossGraphicItem::selectedPen() const
{
  return mSelectedPen;
}

void DiagonalCrossGraphicItem::setSelectedPen(const QPen &pen)
{
  mSelectedPen = pen;
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
    painter->setPen(mSelectedPen);
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


