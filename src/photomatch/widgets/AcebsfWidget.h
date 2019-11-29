#ifndef PHOTOMATCH_ACEBSF_WIDGET_H
#define PHOTOMATCH_ACEBSF_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QSpinBox;
class QDoubleSpinBox;

namespace photomatch
{

class IAcebsfWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  IAcebsfWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
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

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

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

} // namespace photomatch

#endif // PHOTOMATCH_ACEBSF_WIDGET_H
