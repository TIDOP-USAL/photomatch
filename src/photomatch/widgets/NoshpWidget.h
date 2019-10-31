#ifndef PHOTOMATCH_NOSHP_WIDGET_H
#define PHOTOMATCH_NOSHP_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QDoubleSpinBox;
class QSpinBox;

namespace photomatch
{

/*!
 * \brief Interface for NOSHP Widgets class
 */
class PHOTOMATCH_EXPORT INoshpWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  INoshpWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~INoshpWidget() {}

  virtual QSize blockSize() const = 0;

signals:

  void blockSizeChange(QSize);

public slots:

  virtual void setBlockSize(const QSize &blockSize) = 0;

};


class PHOTOMATCH_EXPORT NoshpWidget
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

#endif // PHOTOMATCH_NOSHP_WIDGET_H
