#ifndef FME_FAHE_WIDGET_H
#define FME_FAHE_WIDGET_H

#include "fme/fme_global.h"

#include <QWidget>

class QDoubleSpinBox;
class QSpinBox;

namespace fme
{

/*!
 * \brief Interface for FAHE Widgets class
 * Z. Wang and J. Tao, "A fast implementation of adaptive 
 * histogram equalization," in Proc. ICSP, 2006.
 */
class FME_EXPORT IFaheWidget
  : public QWidget
{
  Q_OBJECT

public:

  IFaheWidget(QWidget *parent = nullptr) : QWidget(parent){}
  virtual ~IFaheWidget() {}

  virtual QSize blockSize() const = 0;

signals:

  void blockSizeChange(QSize);

public slots:

  virtual void setBlockSize(const QSize &blockSize) = 0;

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;

};


class FME_EXPORT FaheWidget
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
  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mBlockSizeX;
  QSpinBox *mBlockSizeY;

};

} // namespace fme

#endif // FME_FAHE_WIDGET_H
