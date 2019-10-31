#ifndef PHOTOMATCH_LCE_BSESCS_WIDGET_H
#define PHOTOMATCH_LCE_BSESCS_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QDoubleSpinBox;
class QSpinBox;

namespace photomatch
{

class PHOTOMATCH_EXPORT ILceBsescsWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  ILceBsescsWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~ILceBsescsWidget() {}

  virtual QSize blockSize() const = 0;

signals:

  void blockSizeChange(QSize);

public slots:

  virtual void setBlockSize(const QSize &blockSize) = 0;

};


class PHOTOMATCH_EXPORT LceBsescsWidget
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

// PhotoMatchWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mBlockSizeX;
  QSpinBox *mBlockSizeY;

};

} // namespace photomatch

#endif // PHOTOMATCH_LCE_BSESCS_WIDGET_H
