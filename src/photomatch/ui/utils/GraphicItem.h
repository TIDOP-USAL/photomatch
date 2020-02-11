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


#ifndef PHOTOMATCH_GRAPHIC_ITEM_H
#define PHOTOMATCH_GRAPHIC_ITEM_H

#include <QGraphicsItem>
#include <QPen>

namespace photomatch
{

class GraphicItem
  : public QGraphicsItem
{

public:

  GraphicItem(QGraphicsItem *parent = nullptr) : QGraphicsItem(parent){}
  virtual ~GraphicItem() override = default;

  virtual QPen pen() const = 0;
  virtual void setPen(const QPen &pen) = 0;

  virtual double size() = 0;
  virtual void setSize(double size) = 0;

  virtual QPen selectedPen() const = 0;
  virtual void setSelectedPen(const QPen &pen) = 0;
};


class CircleGraphicItem
  : public GraphicItem
{

public:

  CircleGraphicItem(QGraphicsItem *parent = nullptr);
  CircleGraphicItem(const QPointF &center, double size, QGraphicsItem *parent = nullptr);
  ~CircleGraphicItem() override;

// GraphicItem interface

public:

  QPen pen() const override;
  void setPen(const QPen &pen) override;
  double size() override;
  void setSize(double size) override;
  QPen selectedPen() const override;
  void setSelectedPen(const QPen &pen) override;

// QGraphicsItem interface

public:

  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:

  QPointF mCenter;
  QPen mPen;
  double mSize;
  QPen mSelectedPen;
};



class CrossGraphicItem
  : public GraphicItem
{

public:

  CrossGraphicItem(QGraphicsItem *parent = nullptr);
  CrossGraphicItem(const QPointF &center, double size, QGraphicsItem *parent = nullptr);
  ~CrossGraphicItem() override;

// GraphicItem interface

public:

  QPen pen() const override;
  void setPen(const QPen &pen) override;
  double size() override;
  void setSize(double size) override;
  QPen selectedPen() const override;
  void setSelectedPen(const QPen &pen) override;

// QGraphicsItem interface

public:

  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:

  QPointF mCenter;
  QPen mPen;
  double mSize;
  QPen mSelectedPen;

};




class KeyPointGraphicsItem
  : public GraphicItem
{

public:

  KeyPointGraphicsItem(QGraphicsItem *parent = nullptr);
  KeyPointGraphicsItem(QPointF center, double size, double angle, QGraphicsItem *parent = nullptr);
  ~KeyPointGraphicsItem() override;

  double angle();
  void setAngle(double angle);

// GraphicItem interface

public:

  QPen pen() const override;
  void setPen(const QPen &pen) override;
  double size() override;
  void setSize(double size) override;
  QPen selectedPen() const override;
  void setSelectedPen(const QPen &pen) override;

// QGraphicsItem interface

public:

  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:

  QPointF mCenter;
  QPen mPen;
  double mSize;
  double mAngle;
  QPen mSelectedPen;
};



class DiagonalCrossGraphicItem
  : public GraphicItem
{

public:

  DiagonalCrossGraphicItem(QGraphicsItem *parent = nullptr);
  DiagonalCrossGraphicItem(const QPointF &center, double size, QGraphicsItem *parent = nullptr);
  ~DiagonalCrossGraphicItem() override;

// GraphicItem interface

public:

  QPen pen() const override;
  void setPen(const QPen &pen) override;
  double size() override;
  void setSize(double size) override;
  QPen selectedPen() const override;
  void setSelectedPen(const QPen &pen) override;

// QGraphicsItem interface

public:

  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:

  QPointF mCenter;
  QPen mPen;
  double mSize;
  QPen mSelectedPen;
};


} // namespace photomatch

#endif // PHOTOMATCH_GRAPHIC_ITEM_H
