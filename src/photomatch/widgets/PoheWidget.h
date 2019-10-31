#ifndef PHOTOMATCH_POHE_WIDGET_H
#define PHOTOMATCH_POHE_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QDoubleSpinBox;
class QSpinBox;

namespace photomatch
{

/*!
 * \brief Interface for POHE Widgets class
 * Y. F. Liu, J. M. Guo, B. S. Lai, and J. D. Lee, "High efficient
 * contrast enhancement using parametric approximation,"
 * in Proc. IEEE ICASSP, pp. 2444-2448, 26-31 May 2013.
 */
class PHOTOMATCH_EXPORT IPoheWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  IPoheWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~IPoheWidget() {}

  virtual QSize blockSize() const = 0;

signals:

  void blockSizeChange(QSize);

public slots:

  virtual void setBlockSize(const QSize &blockSize) = 0;

};


class PHOTOMATCH_EXPORT PoheWidget
  : public IPoheWidget
{
  Q_OBJECT

public:

  PoheWidget(QWidget *parent = nullptr);
  ~PoheWidget() override;

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

#endif // PHOTOMATCH_POHE_WIDGET_H
