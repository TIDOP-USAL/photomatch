#ifndef FME_WALLIS_WIDGET_H
#define FME_WALLIS_WIDGET_H

#include "fme/fme_global.h"

#include <QWidget>

class QDoubleSpinBox;
class QSpinBox;

namespace fme
{

class FME_EXPORT IWallisWidget
  : public QWidget
{
  Q_OBJECT

public:

  IWallisWidget(QWidget *parent = nullptr) : QWidget(parent){}
  virtual ~IWallisWidget() = default;

  virtual double contrast() const = 0;
  virtual double brightness() const = 0;
  virtual int imposedAverage() const = 0;
  virtual int imposedLocalStdDev() const = 0;
  virtual int kernelSize() const = 0;

signals:

  void contrastChange(double);
  void brightnessChange(double);
  void imposedAverageChange(int);
  void imposedLocalStdDevChange(int);
  void kernelSizeChange(int);

public slots:

  virtual void setContrast(double contrast) = 0;
  virtual void setBrightness(double brightness) = 0;
  virtual void setImposedAverage(int imposedAverage) = 0;
  virtual void setImposedLocalStdDev(int imposedLocalStdDev) = 0;
  virtual void setKernelSize(int kernelSize) = 0;

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;
};

class FME_EXPORT WallisWidget
  : public IWallisWidget
{
  Q_OBJECT

public:

  WallisWidget(QWidget *parent = nullptr);
  ~WallisWidget() override;

// IWallisWidget interface

public:

  double contrast() const override;
  double brightness() const override;
  int imposedAverage() const override;
  int imposedLocalStdDev() const override;
  int kernelSize() const override;

public slots:

  void setContrast(double contrast) override;
  void setBrightness(double brightness) override;
  void setImposedAverage(int imposedAverage) override;
  void setImposedLocalStdDev(int imposedLocalStdDev) override;
  void setKernelSize(int kernelSize) override;

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QDoubleSpinBox *mContrast;
  QDoubleSpinBox *mBrightness;
  QSpinBox *mImposedAverage;
  QSpinBox *mImposedLocalStdDev;
  QSpinBox *mKernelSize;
};

} // namespace fme

#endif // FME_WALLIS_WIDGET_H
