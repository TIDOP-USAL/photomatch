#ifndef CROSSGRAPHICITEM_H
#define CROSSGRAPHICITEM_H

#include <QGraphicsItem>

class CrossGraphicItem : public QGraphicsItem
{
public:
    enum { Type = UserType + 1 };

    CrossGraphicItem(QPointF center);
    int type() const;

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0 );
    QRectF boundingRect() const;
    QPainterPath shape () const;

private:
    QPointF mCenter;
};

#endif // CROSSGRAPHICITEM_H
