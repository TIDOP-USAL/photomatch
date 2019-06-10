#ifndef FME_LCE_BSESCS_WIDGET_H
#define FME_LCE_BSESCS_WIDGET_H

#include "fme/widgets/FmeWidget.h"

class QDoubleSpinBox;
class QSpinBox;

namespace fme
{

class FME_EXPORT ILceBsescsWidget
  : public FmeWidget
{
  Q_OBJECT

public:

  ILceBsescsWidget(QWidget *parent = nullptr) : FmeWidget(parent){}
  virtual ~ILceBsescsWidget() {}

  virtual QSize blockSize() const = 0;

signals:

  void blockSizeChange(QSize);

public slots:

  virtual void setBlockSize(const QSize &blockSize) = 0;

};


class FME_EXPORT LceBsescsWidget
  : public ILceBsescsWidget
{
  Q_OBJECT

public:

  LceBsescsWidget(QWidget *parent = nullptr);
  ~LceBsescsWidget() override;

protected slots:

  void onBlockSizeXChange(int gx);
  void onBlockSizeYChange(int gy);

// ICLAHEWidget interface

public:

  QSize blockSize() const override;

public slots:

  void setBlockSize(const QSize &blockSize) override;

// FmeWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mBlockSizeX;
  QSpinBox *mBlockSizeY;

};

} // namespace fme

#endif // FME_LCE_BSESCS_WIDGET_H
