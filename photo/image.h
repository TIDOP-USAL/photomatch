#ifndef IMAGE_H
#define IMAGE_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QtDebug>
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>

class Image : public QGraphicsView {

	Q_OBJECT

public:
	Image();

	// The timer checks at startup in short intervals if the graphicsscene is correctly set up, and whenever that's the case it's calling the drawImg() function (see mainwindow.cpp)
	QTimer *t;

protected:
	// This events are used for zooming and menu opening/closing
	void wheelEvent(QWheelEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);

//        void paintEvent(QPaintEvent *event);

signals:
	void zoom(int);
	void mousePos(QPoint);
};

#endif // IMAGE_H
