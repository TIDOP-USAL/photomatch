#ifndef MATCHINGVIEWER_H
#define MATCHINGVIEWER_H

#include <QObject>
#include <QMainWindow>
#include <qgraphicsscene.h>
#include <QGraphicsPixmapItem>
#include "MatchigGraphicsView.h"
#include "PWImage.h"
#include <opencv/cv.h>

class MatchingViewer : public QObject
{
    Q_OBJECT
public:
    explicit MatchingViewer(QWidget * parentWidget, QObject *parent = 0);

    void loadImagesPair(PWImage *leftImage, PWImage *rightImage);
    void MatchingViewer::loadImagesPair(PWImage *leftImage, PWImage *rightImage,std::vector<cv::KeyPoint> cvLeft_key,std::vector<cv::KeyPoint> cvRight_key);
    void loadImagesPair(PWImage *leftImage, PWImage *rightImage,
                        QList<QVector<float>> correctMatching_coords,QList<QVector<float>> wrongMatching_coords,
                        double accuracyTolerance = 0, bool drawOutlierMatches = false);
    QWidget *getView();
    void clearAll();

signals:

public slots:
    void onScaleChanged(float scaleFactor);

private:
    QWidget *                   mParentWidget;
    MatchigGraphicsView *       mView;
    QGraphicsScene              mScene;
    QPixmap *                   mPixmap;
    QGraphicsPixmapItem *       mPixmapItem;
    QPainter *                  mPainter;
    float                       mLastScaleFactor;
    float                       mAccumulatedScaleFactor;

};

#endif // MATCHINGVIEWER_H
