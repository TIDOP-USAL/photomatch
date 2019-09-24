#include "Progress.h"

namespace fme
{

ProgressHandler::ProgressHandler(QObject *parent)
  : QObject(parent),
    mMin(0),
    mMax(1),
    mValue(0)
{

}

ProgressHandler::~ProgressHandler()
{

}

void ProgressHandler::setRange(int min, int max)
{
  mMin = min;
  mMax = max;
  emit rangeChange(min, max);
}

void ProgressHandler::setValue(int value)
{
  mValue = value;
  emit valueChange(value);
}

void ProgressHandler::onNextPosition()
{
  setValue(++mValue);
  //emit positionNext();
}

void ProgressHandler::onInit()
{
  emit initialized();
}

void ProgressHandler::onFinish()
{
  emit finished();
}

void ProgressHandler::setTitle(const QString &title)
{
  emit titleChange(title);
}

void ProgressHandler::setDescription(const QString &description)
{
  emit descriptionChange(description);
}

//Progress::Progress()
//{}

//Progress::~Progress()
//{}

//void Progress::setRange(int min, int max)
//{
//  emit rangeChange(min, max);
//}

//void Progress::setValue(int value)
//{
//  emit valueChange(value);
//}

//void Progress::setTitle(const QString &title)
//{

//}

//void Progress::setDescription(const QString &value)
//{

//}

} // namespace fme


