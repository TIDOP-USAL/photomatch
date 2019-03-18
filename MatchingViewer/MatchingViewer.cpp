#include "MatchingViewer.h"
#include "photo/CrosshairGraphicsItem.h"

#include <QImageReader>
#include <QLayout>
#include <QtAlgorithms>
#include <opencv/cv.h>
MatchingViewer::MatchingViewer(QWidget *parentWidget, QObject *parent) :
    QObject(parent),
    mParentWidget(parentWidget),
    mPixmap(0),
    mPixmapItem(0),
    mPainter(0),
    mLastScaleFactor(0.0),
    mAccumulatedScaleFactor(1)
{
    mView = new MatchigGraphicsView();
    mView->setScene(&mScene);
    mView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mView->setDragMode(QGraphicsView::ScrollHandDrag);
    mView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(mView, SIGNAL(scaleChanged(float)),this, SLOT(onScaleChanged(float)));
}

void MatchingViewer::loadImagesPair(PWImage *leftImage, PWImage *rightImage)
{
    QImageReader reader(leftImage->getFullPath());
    QImage image1 = reader.read();
    reader.setFileName(rightImage->getFullPath());
    QImage image2 = reader.read();

    if(mPainter)
        delete mPainter;
    if(mPixmap)
        delete mPixmap;

    if (image1.height()>image2.height()) {
        mPixmap = new QPixmap(image1.width()+image2.width(), image1.height());
    }else {
        mPixmap = new QPixmap(image1.width()+image2.width(), image2.height());
    }    mPixmap->fill(Qt::transparent);
    mPainter = new QPainter(mPixmap);
    mPainter->drawImage(0,0,image1,0,0);
    mPainter->drawImage(image1.width(),0,image2,0,0);
    mPixmapItem->setPixmap(*mPixmap);

    mView->invalidateScene();
}

void MatchingViewer::loadImagesPair(PWImage *leftImage, PWImage *rightImage,
                                    QList<QVector<float>> correctMatching_coords,QList<QVector<float>> wrongMatching_coords,
                                    double accuracyTolerance, bool drawOutlierMatches)
{
    QImageReader reader(leftImage->getFullPath());
    QImage image1 = reader.read();
    reader.setFileName(rightImage->getFullPath());
    QImage image2 = reader.read();

    if(mPainter){
        delete mPainter;
        mPainter = 0;
    }
    if(mPixmap){
        delete mPixmap;
        mPixmap = 0;
    }
    if(mPixmapItem){
        delete mPixmapItem;
    }
    mScene.clear();
    mPixmapItem = 0;
    mPixmapItem = new QGraphicsPixmapItem();
    mScene.addItem(mPixmapItem);

    if (image1.height()>image2.height()) {
        mPixmap = new QPixmap(image1.width()+image2.width(), image1.height());
    }else {
        mPixmap = new QPixmap(image1.width()+image2.width(), image2.height());
    }
    mPixmap->fill(Qt::transparent);
    mPainter = new QPainter(mPixmap);
    mPainter->drawImage(0,0,image1,0,0);
    mPainter->drawImage(image1.width(),0,image2,0,0);
    mPixmapItem->setPixmap(*mPixmap);

    if(mLastScaleFactor)
        mView->scale(1.0/mLastScaleFactor, 1.0/mLastScaleFactor);
    int prueba = mView->viewport()->width();
    int prueba2 = mView->width();
    float scaleFactor = ((float)mView->viewport()->width()) / mPixmap->width();
    mView->scale(scaleFactor,scaleFactor);
    mLastScaleFactor= scaleFactor;
    float prueba3 = qreal(mPixmap->width())/qreal(leftImage->getSize().width()+rightImage->getSize().width());
    float prueba4=qreal(mPixmap->height())/qreal(leftImage->getSize().height()+rightImage->getSize().height());
    QTransform trans;
    trans.translate(qreal(mPixmapItem->sceneBoundingRect().left()),qreal(mPixmapItem->sceneBoundingRect().top()));
    trans=trans.scale(qreal(mPixmap->width())/qreal(leftImage->getSize().width()+rightImage->getSize().width()),
                      qreal(mPixmap->height())/qreal(leftImage->getSize().height()+rightImage->getSize().height()));

    //DrawCorrectMatches
    for (int i=0; i<correctMatching_coords.size(); i++){
        if (correctMatching_coords.at(i)[4] <= accuracyTolerance || drawOutlierMatches){

            QPointF transPoint = trans.map(QPointF(0.0,0.0));
            PW2dPoint *point = new PW2dPoint(transPoint.x(),transPoint.y(),"");

            QGraphicsLineItem *lineItem = new QGraphicsLineItem(correctMatching_coords.at(i)[0],correctMatching_coords.at(i)[1],
                    correctMatching_coords.at(i)[2] + image1.width(),correctMatching_coords.at(i)[3]);
            int red = 50;
            int green = 50;
            int blue = 255;
            if (accuracyTolerance && correctMatching_coords.at(i)[4]>=0){
                red = correctMatching_coords.at(i)[4] * 255 / accuracyTolerance;
                green = 255 - red;
                blue = 0;
                if (red>255) red = green = blue = 0;
            }
            lineItem->setPen(QPen(QColor(119, 221 , 119),2));

            QGraphicsEllipseItem *leftEllipseItem = new QGraphicsEllipseItem(correctMatching_coords.at(i)[0]-10,
                    correctMatching_coords.at(i)[1]-10,
                    20,
                    20);
            leftEllipseItem->setPen(QPen(QColor(red, green , blue),2));
            QGraphicsEllipseItem *rightEllipseItem = new QGraphicsEllipseItem(correctMatching_coords.at(i)[2]+ image1.width()-10,
                    correctMatching_coords.at(i)[3]-10,
                    20,
                    20);
            rightEllipseItem->setPen(QPen(QColor(red, green , blue),2));

            mScene.addItem(lineItem);
            lineItem->moveBy(point->x(),point->y());

            mScene.addItem(rightEllipseItem);
            mScene.addItem(leftEllipseItem);
        }
    }

    //DrawWrongMatches
    for (int i=0; i<wrongMatching_coords.size(); i++){
        if (wrongMatching_coords.at(i)[4] <= accuracyTolerance || drawOutlierMatches){

            QPointF transPoint = trans.map(QPointF(0.0,0.0));
            PW2dPoint *point = new PW2dPoint(transPoint.x(),transPoint.y(),"");

            QGraphicsLineItem *lineItem = new QGraphicsLineItem(wrongMatching_coords.at(i)[0],wrongMatching_coords.at(i)[1],
                    wrongMatching_coords.at(i)[2] + image1.width(),wrongMatching_coords.at(i)[3]);
            int red = 50;
            int green = 50;
            int blue = 255;
            if (accuracyTolerance && wrongMatching_coords.at(i)[4]>=0){
                red = wrongMatching_coords.at(i)[4] * 255 / accuracyTolerance;
                green = 255 - red;
                blue = 0;
                if (red>255) red = green = blue = 0;
            }
            lineItem->setPen(QPen(QColor(255, 0 , 0),2));
            QGraphicsEllipseItem *leftEllipseItem = new QGraphicsEllipseItem(wrongMatching_coords.at(i)[0]-10,
                    wrongMatching_coords.at(i)[1]-10,
                    20,
                    20);
            leftEllipseItem->setPen(QPen(QColor(red, green , blue),2));
            QGraphicsEllipseItem *rightEllipseItem = new QGraphicsEllipseItem(wrongMatching_coords.at(i)[2]+ image1.width()-10,
                    wrongMatching_coords.at(i)[3]-10,
                    20,
                    20);
            rightEllipseItem->setPen(QPen(QColor(red, green , blue),2));

            mScene.addItem(lineItem);
            lineItem->moveBy(point->x(),point->y());

            mScene.addItem(rightEllipseItem);
            mScene.addItem(leftEllipseItem);
        }
    }

//    mView->scale(mAccumulatedScaleFactor, mAccumulatedScaleFactor);
    mScene.invalidate();
}

void MatchingViewer::loadImagesPair(PWImage *leftImage, PWImage *rightImage,std::vector<cv::KeyPoint> cvLeft_key,std::vector<cv::KeyPoint> cvRight_key)
{
    QImageReader reader(leftImage->getFullPath());
    QImage image1 = reader.read();
    reader.setFileName(rightImage->getFullPath());
    QImage image2 = reader.read();

    if(mPainter){
        delete mPainter;
        mPainter = 0;
    }
    if(mPixmap){
        delete mPixmap;
        mPixmap = 0;
    }
    if(mPixmapItem){
        delete mPixmapItem;
    }
    mScene.clear();
    mPixmapItem = 0;
    mPixmapItem = new QGraphicsPixmapItem();
    mScene.addItem(mPixmapItem);

    if (image1.height()>image2.height()) {
        mPixmap = new QPixmap(image1.width()+image2.width(), image1.height());
    }else {
        mPixmap = new QPixmap(image1.width()+image2.width(), image2.height());
    }    mPixmap->fill(Qt::transparent);
    mPainter = new QPainter(mPixmap);
    mPainter->drawImage(0,0,image1,0,0);
    mPainter->drawImage(image1.width(),0,image2,0,0);
    mPixmapItem->setPixmap(*mPixmap);

    if(mLastScaleFactor)
        mView->scale(1.0/mLastScaleFactor, 1.0/mLastScaleFactor);
    int prueba = mView->viewport()->width();
    int prueba2 = mView->width();
    float scaleFactor = ((float)mView->viewport()->width()) / mPixmap->width();
    mView->scale(scaleFactor,scaleFactor);
    mLastScaleFactor= scaleFactor;
    float prueba3 = qreal(mPixmap->width())/qreal(leftImage->getSize().width()+rightImage->getSize().width());
    float prueba4=qreal(mPixmap->height())/qreal(leftImage->getSize().height()+rightImage->getSize().height());
    QTransform trans;
    trans.translate(qreal(mPixmapItem->sceneBoundingRect().left()),qreal(mPixmapItem->sceneBoundingRect().top()));
    trans=trans.scale(qreal(mPixmap->width())/qreal(leftImage->getSize().width()+rightImage->getSize().width()),
                      qreal(mPixmap->height())/qreal(leftImage->getSize().height()+rightImage->getSize().height()));

    //DrawTiePoitsLeft
    for (int i=0; i<cvLeft_key.size(); i++){

            QPointF transPoint = trans.map(QPointF(0.0,0.0));
            PW2dPoint *point = new PW2dPoint(transPoint.x(),transPoint.y(),"");

            QGraphicsEllipseItem *leftEllipseItem = new QGraphicsEllipseItem(cvLeft_key.at(i).pt.x-10,
                    cvLeft_key.at(i).pt.y-10,
                    20,
                    20);
            leftEllipseItem->setPen(QPen(QColor(0, 0 , 255),2));
            mScene.addItem(leftEllipseItem);
    }
    //DrawTiePoitsRithg
    for (int i=0; i<cvRight_key.size(); i++){

            QPointF transPoint = trans.map(QPointF(0.0,0.0));
            PW2dPoint *point = new PW2dPoint(transPoint.x(),transPoint.y(),"");

            QGraphicsEllipseItem *rightEllipseItem = new QGraphicsEllipseItem(cvRight_key.at(i).pt.x+ image1.width()-10,
                    cvRight_key.at(i).pt.y-10,
                    20,
                    20);
            rightEllipseItem->setPen(QPen(QColor(0, 0 , 255),2));

            mScene.addItem(rightEllipseItem);
    }

//    mView->scale(mAccumulatedScaleFactor, mAccumulatedScaleFactor);
    mScene.invalidate();
}

QWidget *MatchingViewer::getView()
{
    return mView;
}

void MatchingViewer::clearAll()
{
    mScene.clear();
    mScene.invalidate();
    mPixmapItem = 0;
}

void MatchingViewer::onScaleChanged(float scaleFactor)
{
    mView->scale(scaleFactor, scaleFactor);
    mAccumulatedScaleFactor*=(1/scaleFactor);
}
