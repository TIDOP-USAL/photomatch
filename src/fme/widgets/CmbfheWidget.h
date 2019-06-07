#ifndef FME_CMBFHE_WIDGET_H
#define FME_CMBFHE_WIDGET_H

#include "fme/fme_global.h"

#include <QWidget>

class QDoubleSpinBox;
class QSpinBox;

namespace fme
{

/*!
 * \brief Interface for CMBFHE Widgets class
 * F. Lamberti, B. Montrucchio, and A. Sanna, "CMBFHE: a novel contrast 
 * enhancement technique based on cascaded multistep binomial filtering 
 * histogram equalization," TCE, vol. 52, no. 3, 2006.
 */
class FME_EXPORT ICmbfheWidget
  : public QWidget
{
  Q_OBJECT

public:

  ICmbfheWidget(QWidget *parent = nullptr) : QWidget(parent){}
  virtual ~ICmbfheWidget() {}

  virtual QSize blockSize() const = 0;
   
  /// TODO: virtual QSize stepSize() const = 0;
  // S - Number of regions divided by the step size. S should >2xB. 
  // .This should be the "Bx2" or "Bx4" or "Bx8" etc multiple of 2. 
  // "S" should be B's power (i.e., 2,4,8,16,32,64,128...). 
  // Bigger S, better image quality, and slower.
  
signals:

  void blockSizeChange(QSize);
  //void stepSizeChange(QSize);
  
public slots:

  virtual void setBlockSize(const QSize &blockSize) = 0;
  //virtual void setStepSize(const QSize &stepSize) = 0;
  
  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;

};


class FME_EXPORT CmbfheWidget
  : public ICmbfheWidget
{
  Q_OBJECT

public:

  CmbfheWidget(QWidget *parent = nullptr);
  ~CmbfheWidget() override;

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

#endif // FME_CMBFHE_WIDGET_H
