#ifndef PHOTOMATCH_FAHE_WIDGET_H
#define PHOTOMATCH_FAHE_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QDoubleSpinBox;
class QSpinBox;

namespace photomatch
{

/*!
 * \brief Interface for FAHE Widgets class
 * Z. Wang and J. Tao, "A fast implementation of adaptive 
 * histogram equalization," in Proc. ICSP, 2006.
 */
class PHOTOMATCH_EXPORT IFaheWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  IFaheWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~IFaheWidget() {}

  virtual QSize blockSize() const = 0;

signals:

  void blockSizeChange(QSize);

public slots:

  virtual void setBlockSize(const QSize &blockSize) = 0;

};


class PHOTOMATCH_EXPORT FaheWidget
  : public IFaheWidget
{
  Q_OBJECT

public:

  FaheWidget(QWidget *parent = nullptr);
  ~FaheWidget() override;

protected slots:

  void onBlockSizeXChange(int blockSizeX);
  void onBlockSizeYChange(int blockSizeY);

// ICLAHEWidget interface

public:

  QSize blockSize() const override;

public slots:

  void setBlockSize(const QSize &blockSize) override;

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

};

} // namespace photomatch

#endif // PHOTOMATCH_FAHE_WIDGET_H
