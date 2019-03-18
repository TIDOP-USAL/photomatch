#include "PWPoint.h"


PWPoint::PWPoint(PointType type, QString name):
    mType(type),
    mName(name)
{
}

QList<PWPoint *> PWPoint::getAssociatedPoints()
{
    return mAssociatedPoints;
}

PWPoint::PointType PWPoint::getType()
{
    return mType;
}

QString PWPoint::getName()
{
    return mName;
}

void PWPoint::setName(QString name)
{
    mName = name;
}
