#ifndef FME_PROGRESS_H
#define FME_PROGRESS_H

#include <QObject>

namespace fme
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
  //void positionNext();
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





//class IProgress
//  : public QObject
//{
//  Q_OBJECT

//public:

//  IProgress() {}
//  virtual ~IProgress() = default;

//public slots:

//  virtual void setRange(int min, int max) = 0;
//  virtual void setValue(int value) = 0;
//  virtual void setTitle(const QString &title) = 0;
//  virtual void setDescription(const QString &value) = 0;

//signals:

//  void rangeChange(int, int);
//  void valueChange(int);
//  void finished();

//};



//class Progress
//  : public IProgress
//{

//  Q_OBJECT

//public:

//  Progress();
//  ~Progress() override;

//// IProgress interface

//public slots:

//  void setRange(int min, int max) override;
//  void setValue(int value) override;
//  void setTitle(const QString &title) override;
//  void setDescription(const QString &value) override;
//};

} // namespace fme

#endif // FME_PROGRESS_H
