#ifndef FME_PROGRESS_H
#define FME_PROGRESS_H

#include <QObject>

namespace fme
{

class IProgress
  : public QObject
{
  Q_OBJECT

public:

  IProgress() {}
  virtual ~IProgress() = default;

public slots:

  virtual void setRange(int min, int max) = 0;
  virtual void setValue(int value) = 0;

signals:

  void rangeChange(int, int);
  void valueChange(int);
  void finished();

};



class Progress
  : public IProgress
{

  Q_OBJECT

public:

  Progress();
  ~Progress() override;

// IProgress interface

public slots:

  void setRange(int min, int max) override;
  void setValue(int value) override;
};

} // namespace fme

#endif // FME_PROGRESS_H
