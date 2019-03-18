#include <QDebug>

#include "Camera.h"


Camera::Camera():
    mName(""),
    mLensName(""),
    mSensorHeight(0),
    mSensorWidth(0),
    mDeclaredFocal(0),
    mScaleFactor35(0),
    mActiveCamModel(NULL)
{
}

Camera::Camera(QString name, QString lensName, double width, double height, double focal, double scaleFactor):
    mName(name),
    mLensName(lensName),
    mSensorHeight(height),
    mSensorWidth(width),
    mDeclaredFocal(focal),
    mScaleFactor35(scaleFactor),
    mActiveCamModel(NULL)
{
}

Camera::~Camera(){
//    for(int i=0; i<mCameraModels.count(); i++)
//        delete mCameraModels.at(i);
}

double Camera::getSensorHeight()
{
    return mSensorHeight;
}

double Camera::getSensorWidth()
{
    return mSensorWidth;
}

double Camera::getDeclaredFocal()
{
    return mDeclaredFocal;
}

double Camera::getScaleFactor35()
{
    return mScaleFactor35;
}

QString Camera::getName()
{
    return mName;
}

QString Camera::getLensName()
{
    return mLensName;
}

void Camera::setName(QString name)
{
    mName = name;
}

void Camera::setLensName(QString lensName)
{
    mLensName = lensName;
}

void Camera::setSensorHeight(double height)
{
    mSensorHeight = height;
}

void Camera::setSensorWidth(double width)
{
    mSensorWidth = width;
}

void Camera::setDeclaredFocal(double focal)
{
    mDeclaredFocal = focal;
}

void Camera::setScaleFactor35(double scaleFactor)
{
    mScaleFactor35 = scaleFactor;
}

void Camera::setCameraModel(CameraModel *cameraModel)
{
    if(mCameraModels.count() == 0 && cameraModel != NULL) /*TODO*/
        mCameraModels.append(cameraModel); /*TODO*/
    mActiveCamModel = cameraModel;
}

CameraModel * Camera::getCameraModel(int index)
{
    return mCameraModels.at(index);
}

QList<CameraModel *> Camera::getCameraModels()
{
    return mCameraModels;
}

CameraModel * Camera::getCameraModel()
{
    return mActiveCamModel;
}
