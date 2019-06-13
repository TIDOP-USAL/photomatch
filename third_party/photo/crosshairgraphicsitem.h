#ifndef CROSSHAIRGRAPHICSITEM_H
#define CROSSHAIRGRAPHICSITEM_H

#include <QGraphicsEllipseItem>

#include "fme/ui/MatchingViewer/PW2dPoint.h"

class CrosshairGraphicsItem : public QObject, public QGraphicsEllipseItem
{

    Q_OBJECT

public:
    CrosshairGraphicsItem(PW2dPoint *point);
    int type () const;
    void setCrossColor(QColor color);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0 );
    QRectF boundingRect() const;
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );
    QVariant itemChange ( GraphicsItemChange change, const QVariant & value );

private:
    PW2dPoint *mPoint;
    QColor mCrossColor;

signals:
    void pointChanged(PW2dPoint *point, QPointF pos);
};

#endif // CROSSHAIRGRAPHICSITEM_H
