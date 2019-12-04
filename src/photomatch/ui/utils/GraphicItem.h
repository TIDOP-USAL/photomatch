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
