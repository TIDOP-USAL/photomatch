#ifndef FME_ACEBSF_WIDGET_H
#define FME_ACEBSF_WIDGET_H

#include "fme/fme_global.h"

#include <QWidget>

class QSpinBox;
class QDoubleSpinBox;

namespace fme
{

class IAcebsfWidget
  : public QWidget
{
  Q_OBJECT

public:

  IAcebsfWidget(QWidget *parent = nullptr) : QWidget(parent){}
  virtual ~IAcebsfWidget() = default;

  virtual QSize blockSize() const = 0;
  virtual double l() const = 0;
  virtual double k1() const  = 0;
  virtual double k2() const = 0;

signals:

  void blockSizeChange(QSize);
  void lChange(double);
  void k1Change(double);
  void k2Change(double);

public slots:

  virtual void setBlockSize(const QSize &blockSize) = 0;
  virtual void setL(double l) = 0;
  virtual void setK1(double k1) = 0;
  virtual void setK2(double k2) = 0;

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;

};

class AcebsfWidget
  : public IAcebsfWidget
{
  Q_OBJECT

public:

  AcebsfWidget(QWidget *parent = nullptr);
  ~AcebsfWidget() override;

protected slots:

  void onBlockSizeXChange(int blockSizeX);
  void onBlockSizeYChange(int blockSizeY);

// IAcebsfWidget interface

public:

  QSize blockSize() const override;
  double l() const override;
  double k1() const override;
  double k2() const override;

public slots:

  void setBlockSize(const QSize &blockSize) override;
  void setL(double l) override;
  void setK1(double k1) override;
  void setK2(double k2) override;
  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mBlockSizeX;
  QSpinBox *mBlockSizeY;
  QDoubleSpinBox *mL;
  QDoubleSpinBox *mK1;
  QDoubleSpinBox *mK2;
};

} // namespace fme

#endif // FME_ACEBSF_WIDGET_H
