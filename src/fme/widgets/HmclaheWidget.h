#ifndef FME_HMCLAHE_WIDGET_H
#define FME_HMCLAHE_WIDGET_H

#include "fme/fme_global.h"

#include <QWidget>

class QSpinBox;
class QDoubleSpinBox;

namespace fme
{

class IHmclaheWidget
  : public QWidget
{
  Q_OBJECT

public:

  IHmclaheWidget(QWidget *parent = nullptr) : QWidget(parent){}
  virtual ~IHmclaheWidget() = default;

  virtual QSize blockSize() const = 0;
  virtual double l() const = 0;
  virtual double phi() const  = 0;

signals:

  void blockSizeChange(QSize);
  void lChange(double);
  void phiChange(double);

public slots:

  virtual void setBlockSize(const QSize &blockSize) = 0;
  virtual void setL(double l) = 0;
  virtual void setPhi(double phi) = 0;

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;

};

class HmclaheWidget
  : public IHmclaheWidget
{
  Q_OBJECT

public:

  HmclaheWidget(QWidget *parent = nullptr);
  ~HmclaheWidget() override;

protected slots:

  void onBlockSizeXChange(int blockSizeX);
  void onBlockSizeYChange(int blockSizeY);

// IHmclaheWidget interface

public:

  QSize blockSize() const override;
  double l() const override;
  double phi() const override;

public slots:

  void setBlockSize(const QSize &blockSize) override;
  void setL(double l) override;
  void setPhi(double phi) override;
  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mBlockSizeX;
  QSpinBox *mBlockSizeY;
  QDoubleSpinBox *mL;
  QDoubleSpinBox *mPhi;

};

} // namespace fme

#endif // FME_HMCLAHE_WIDGET_H
