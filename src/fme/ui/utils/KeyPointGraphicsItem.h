#ifndef FME_KEYPOINT_GRAPHICS_ITEM_H
#define FME_KEYPOINT_GRAPHICS_ITEM_H

#include <QGraphicsItem>
#include <QPen>
#include <QBrush>

namespace fme
{

class KeyPointGraphicsItem
  : public QGraphicsItem
{

public:

  KeyPointGraphicsItem(QGraphicsItem *parent = nullptr);
  KeyPointGraphicsItem(QPointF center, QGraphicsItem *parent = nullptr);
  ~KeyPointGraphicsItem() override;

  QPen pen() const;
  void setPen(const QPen &pen);

  QBrush brush() const;
  void setBrush(const QBrush &brush);

  double size();
  void setSize(double size);

  double angle();
  void setAngle(double angle);

// QGraphicsItem interface

public:

  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:

  QPointF mCenter;
  QPen mPen;
  QBrush mBrush;
  double mSize;
  double mAngle;

};

} // namespace fme

#endif // FME_KEYPOINT_GRAPHICS_ITEM_H
