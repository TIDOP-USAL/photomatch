#include "image.h"

Image::Image() : QGraphicsView() {

	// Start a timer that calls the drawImg() function on startup whenever the scene is correctly set up
	t = new QTimer;
//	t->start(50);

        setMouseTracking(true);
        setContextMenuPolicy(Qt::CustomContextMenu);
}

// Zooming the image on ctrl+mouse wheel
void Image::wheelEvent(QWheelEvent *event) {

	// Check if ctrl is pressed
	int ctrlPressed = 0;

	switch(event->modifiers()) {
	case(Qt::ControlModifier):
		ctrlPressed = 1;
		break;
	}

	// if ctrl is pressed, zoom in/out
	if(ctrlPressed) {

		if(event->delta() > 0)
			emit zoom(1);
		else
			emit zoom(2);

	} else
		QGraphicsView::wheelEvent(event);

}

// ctrl+mouse wheel click resets the zooming position
void Image::mouseReleaseEvent(QMouseEvent *event) {

	int ctrlPressed = 0;

	switch(event->modifiers()) {
	case(Qt::ControlModifier):
		ctrlPressed = 1;
		break;
	}

	if(ctrlPressed) {

		if(event->type() == 3)
			emit zoom(0);

	} else
		QGraphicsView::mouseReleaseEvent(event);

}

// Get the current mouse position
void Image::mouseMoveEvent(QMouseEvent *event) {

        emit mousePos(event->pos());
        QGraphicsView::mouseMoveEvent(event);
}

void Image::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}
