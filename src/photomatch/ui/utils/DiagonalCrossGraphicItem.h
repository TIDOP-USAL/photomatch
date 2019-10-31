#ifndef PHOTOMATCH_DIAGONAL_CROSS_GRAPHIC_ITEM_H
#define PHOTOMATCH_DIAGONAL_CROSS_GRAPHIC_ITEM_H

#include <QGraphicsItem>
#include <QPen>

namespace photomatch
{

class DiagonalCrossGraphicItem
  : public QGraphicsItem
{

public:

  DiagonalCrossGraphicItem(QGraphicsItem *parent = nullptr);
  DiagonalCrossGraphicItem(QPointF center, QGraphicsItem *parent = nullptr);
  ~DiagonalCrossGraphicItem() override;

  QPen pen() const;
  void setPen(const QPen &pen);

  double size();
  void setSize(double size);

// QGraphicsItem interface

public:

  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:

  QPointF mCenter;
  QPen mPen;
  double mSize;

};

} // namespace photomatch

#endif // PHOTOMATCH_DIAGONAL_CROSS_GRAPHIC_ITEM_H
