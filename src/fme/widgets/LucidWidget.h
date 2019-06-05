#ifndef FME_LUCID_WIDGET_H
#define FME_LUCID_WIDGET_H

#include "fme/fme_global.h"

#include <QWidget>

class QSpinBox;

namespace fme
{

class FME_EXPORT ILucidWidget
  : public QWidget
{

  Q_OBJECT

public:

  ILucidWidget(QWidget *parent = nullptr) : QWidget(parent){}
  virtual ~ILucidWidget() = default;

  virtual int lucidKernel() const = 0;
  virtual int blurKernel() const = 0;

signals:

  void lucidKernelChange(int);
  void blurKernelChange(int);

public slots:

  virtual void setLucidKernel(int lucidKernel) = 0;
  virtual void setBlurKernel(int blurKernel) = 0;

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;
};


class FME_EXPORT LucidWidget
  : public ILucidWidget
{

Q_OBJECT

public:

  LucidWidget(QWidget *parent = nullptr);
  ~LucidWidget() override;

// ILucidWidget interface

public:

  int lucidKernel() const override;
  int blurKernel() const override;

public slots:

  void setLucidKernel(int lucidKernel) override;
  void setBlurKernel(int blurKernel) override;
  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mLucidKernel;
  QSpinBox *mBlurKernel;
};

} // namespace fme

#endif // FME_LUCID_WIDGET_H
