#ifndef THUMBNAIL_H
#define THUMBNAIL_H

#include "thbthread.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QtDebug>
#include <QMouseEvent>

#include <QTextItem>
#include <QTextDocument>

#include <QRadialGradient>

class Thumbnails : public QGraphicsView {

	Q_OBJECT

public:
	Thumbnails();
	~Thumbnails();

	// Scene for the thumbnails
	QGraphicsScene scene;

	// Thread creating the thumbnails in the background
	ThumbThread *thread;

	// Diffferent variables
	int counttot;
	int height;
	int previousHover;
	int currentHover;
	bool cacheEnabled;

	// The path of the current file
	QString currentfile;

	// Storring info about images in current directory
	QFileInfoList allimgs;
	QStringList allThumbs;

	// Initialising the QLists for the QPixmaps(item)
	QList<QGraphicsPixmapItem*> allPixItem;
	QList<QPixmap> allPixImg;
	QList<QPixmap> allPixSel;
	QList<QPixmap> allPixHov;

	// Gathering information about all images in current directory
	void allImgs();
        void allImgs(QStringList imageURLs);

public slots:
	// Add a thumbnail to the scene
	void addThumbnail(QImage,QString,int);

	// Hide/Show thumbnail view
	void toggle();

	// Stop the thumbnail creation
	void stopThread();

	// Update the hovered/selected thumbnail items
	void updImgMark(int oldpos, int newpos);
	void updImgHov();

	// (Re-)Loading the thumbnails
	void loadThumbs();

	// Enable/disable the menu item "Interrupt Thumbnail creation"
	void enableMenuInterrupt();

signals:
	// Emitted at click on thumbnail
	void loadImg(QString, int);

	// Enable/disable the menu item "Interrupt Thumbnail creation"
	void disEnableMenuInterrupt(bool);

protected:
	// Detecting mouse clicks
	void mouseReleaseEvent(QMouseEvent*);
	// Detecting mouse moves
    void mouseMoveEvent(QMouseEvent *event);

};

#endif // THUMBNAIL_H
