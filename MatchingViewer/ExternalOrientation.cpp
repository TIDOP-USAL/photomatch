#include "ExternalOrientation.h"


ExteriorOrientation::ExteriorOrientation()
{
}

ExteriorOrientation::ExteriorOrientation(QVector<double> cp, QVector< QVector<double> > r):
    mCP(cp),
    mR(r)
{

}

void ExteriorOrientation::setCP(QVector<double> cp)
{
    mCP = cp;
}

void ExteriorOrientation::setR(QVector< QVector<double> > r)
{
    mR = r;
}

QVector<double> *ExteriorOrientation::getCP()
{
    return &mCP;
}

QVector< QVector<double> > *ExteriorOrientation::getR()
{
    return &mR;
}
