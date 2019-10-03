#ifndef FME_CROSS_GRAPHIC_ITEM_H
#define FME_CROSS_GRAPHIC_ITEM_H

#include <QGraphicsItem>
#include <QPen>

namespace fme
{

class CrossGraphicItem
  : public QGraphicsItem
{

public:

  CrossGraphicItem(QGraphicsItem *parent = nullptr);
  CrossGraphicItem(QPointF center, QGraphicsItem *parent = nullptr);
  ~CrossGraphicItem() override;

  QPen pen() const;
  void setPen(const QPen &pen);

  double size();
  void setSize(double size);

// QGraphicsItem interface

public:

  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:

  QPointF mCenter;
  QPen mPen;
  double mSize;

};

} // namespace fme

#endif // FME_CROSS_GRAPHIC_ITEM_H
