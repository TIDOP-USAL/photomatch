#ifndef FME_NOSHP_WIDGET_H
#define FME_NOSHP_WIDGET_H

#include "fme/widgets/FmeWidget.h"

class QDoubleSpinBox;
class QSpinBox;

namespace fme
{

/*!
 * \brief Interface for NOSHP Widgets class
 */
class FME_EXPORT INoshpWidget
  : public FmeWidget
{
  Q_OBJECT

public:

  INoshpWidget(QWidget *parent = nullptr) : FmeWidget(parent){}
  virtual ~INoshpWidget() {}

  virtual QSize blockSize() const = 0;

signals:

  void blockSizeChange(QSize);

public slots:

  virtual void setBlockSize(const QSize &blockSize) = 0;

};


class FME_EXPORT NoshpWidget
  : public INoshpWidget
{
  Q_OBJECT

public:

  NoshpWidget(QWidget *parent = nullptr);
  ~NoshpWidget() override;

protected slots:

  void onBlockSizeXChange(int blockSizeX);
  void onBlockSizeYChange(int blockSizeY);

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

#endif // FME_NOSHP_WIDGET_H
