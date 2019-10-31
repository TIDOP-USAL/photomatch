#include <QRegExp>
#include <QImageReader>
#include <QFileInfo>

#include "PWImage.h"


PWImage::PWImage():
    mCamera(NULL),
    mActiveExtOrientation(NULL),
    mMask(NULL),
    mID(0)
{
}

PWImage::PWImage(QString url):
    mCamera(NULL),
    mActiveExtOrientation(NULL),
    mMask(NULL),
    mID(0)
{
    QFileInfo fileInfo(url);
    mFileName=fileInfo.fileName();
    mBasePath=fileInfo.absolutePath();
//    mFileName = url.right(url.length()-url.lastIndexOf(QRegExp("/"))-1);
//    mBasePath = url.left(url.lastIndexOf(QRegExp("/")));
    QImageReader imageReader(url);
    mSize = imageReader.size();
}

PWImage::~PWImage(){
    for(int i=0; i<mControlPoints.count(); i++)
        delete mControlPoints.at(i);

    for(int i=0; i<mExtOrientations.count(); i++)
        delete mExtOrientations.at(i);
}

int PWImage::getID()
{
    return mID;
}

QString PWImage::getFullPath()
{
    return mBasePath + "/" + mFileName;
}

void PWImage::setBasePath(QString url)
{
    mBasePath = url;
}

void PWImage::setMask(QPolygonF mask)
{
    mMask = mask;
}

QPolygonF PWImage::getMask()
{
    return mMask;
}

void PWImage::setExteriorOrientation(ExteriorOrientation *orientation)
{
    mExtOrientations.append(orientation);
    mActiveExtOrientation = orientation;    /*TODO*/
}

ExteriorOrientation * PWImage::getExteriorOrientation()
{
    return mActiveExtOrientation;
}

ExteriorOrientation * PWImage::getExteriorOrientation(int index)
{
    return mExtOrientations.at(index);
}

QString PWImage::getFileName()
{
    return mFileName;
}

QList<PW2dPoint *> * PWImage::getControlPoints()
{
    return &mControlPoints;
}

void PWImage::setCamera(Camera *camera)
{
    mCamera = camera;
}

Camera * PWImage::getCamera()
{
    return mCamera;
}

QSize PWImage::getSize()
{
    return mSize;
}

void PWImage::setID(int id)
{
    mID = id;
}
