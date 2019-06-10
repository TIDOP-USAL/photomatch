#ifndef FME_POHE_WIDGET_H
#define FME_POHE_WIDGET_H

#include "fme/widgets/FmeWidget.h"

class QDoubleSpinBox;
class QSpinBox;

namespace fme
{

/*!
 * \brief Interface for POHE Widgets class
 * Y. F. Liu, J. M. Guo, B. S. Lai, and J. D. Lee, "High efficient
 * contrast enhancement using parametric approximation,"
 * in Proc. IEEE ICASSP, pp. 2444-2448, 26-31 May 2013.
 */
class FME_EXPORT IPoheWidget
  : public FmeWidget
{
  Q_OBJECT

public:

  IPoheWidget(QWidget *parent = nullptr) : FmeWidget(parent){}
  virtual ~IPoheWidget() {}

  virtual QSize blockSize() const = 0;

signals:

  void blockSizeChange(QSize);

public slots:

  virtual void setBlockSize(const QSize &blockSize) = 0;

};


class FME_EXPORT PoheWidget
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

#endif // FME_POHE_WIDGET_H
