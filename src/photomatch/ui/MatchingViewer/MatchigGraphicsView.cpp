#include "MatchigGraphicsView.h"

MatchigGraphicsView::MatchigGraphicsView() :
    QGraphicsView()
{
}

void MatchigGraphicsView::wheelEvent(QWheelEvent *event)
{
    // Check if ctrl is pressed
    int ctrlPressed = 0;

    switch(event->modifiers()) {
    case(Qt::ControlModifier):
        ctrlPressed = 1;
        break;
    }

    // if ctrl is pressed, zoom in/out
    if(ctrlPressed) {
        setTransformationAnchor(AnchorUnderMouse);
        if(event->delta() > 0)
            emit scaleChanged(1.25f);
//            scale(1.25,1.25);
        else
            emit scaleChanged(0.8f);
//            scale(0.8,0.8);

    } else
        QGraphicsView::wheelEvent(event);
}
