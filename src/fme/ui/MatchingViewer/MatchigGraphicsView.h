#ifndef MATCHIGGRAPHICSVIEW_H
#define MATCHIGGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

class MatchigGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MatchigGraphicsView();

protected:
    void wheelEvent(QWheelEvent *event);

private:
    int                         mZoomSteps;

signals:
    void scaleChanged(float scaleFactor);

public slots:

};

#endif // MATCHIGGRAPHICSVIEW_H
