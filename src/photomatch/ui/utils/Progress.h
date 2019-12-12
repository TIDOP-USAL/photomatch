#ifndef PHOTOMATCH_PROGRESS_H
#define PHOTOMATCH_PROGRESS_H

#include <QObject>

namespace photomatch
{


class ProgressHandler
  : public QObject
{
  Q_OBJECT

public:

  ProgressHandler(QObject *parent = nullptr);
  ~ProgressHandler() override;

signals:

  void rangeChange(int, int);
  void valueChange(int);
  void initialized();
  void finished();
  void titleChange(QString);
  void descriptionChange(QString);

public slots:

  void setRange(int min, int max);
  void setValue(int value);
  void onNextPosition();
  void onInit();
  void onFinish();
  void setTitle(const QString &title);
  void setDescription(const QString &description);

protected:

  int mMin;
  int mMax;
  int mValue;

};

} // namespace photomatch

#endif // PHOTOMATCH_PROGRESS_H
