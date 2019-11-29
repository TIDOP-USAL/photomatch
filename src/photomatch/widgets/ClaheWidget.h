#ifndef PHOTOMATCH_CLAHE_WIDGET_H
#define PHOTOMATCH_CLAHE_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QDoubleSpinBox;
class QSpinBox;

namespace photomatch
{

/*!
 * \brief CLAHE (Contrast Limited Adaptive Histogram Equalization)
 * Equalizes the histogram of a grayscale image using Contrast Limited
 * Adaptive Histogram Equalization.
 */
class PHOTOMATCH_EXPORT IClaheWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  IClaheWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~IClaheWidget() {}

  virtual double clipLimit() const = 0;
  virtual QSize tileGridSize() const = 0;

signals:

  void clipLimitChange(double);
  void tileGridSizeChange(QSize);

public slots:

  virtual void setClipLimit(double clipLimit) = 0;
  virtual void setTilesGridSize (const QSize &tileGridSize) = 0;

};


class PHOTOMATCH_EXPORT ClaheWidget
  : public IClaheWidget
{
  Q_OBJECT

public:

  ClaheWidget(QWidget *parent = nullptr);
  ~ClaheWidget() override;

protected slots:

  void onTilesGridXChange(int gx);
  void onTilesGridYChange(int gy);

// ICLAHEWidget interface

public:

  double clipLimit() const override;
  QSize tileGridSize() const override;

public slots:

  void setClipLimit(double clipLimit) override;
  void setTilesGridSize(const QSize &tileGridSize) override;

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  void init() override;

protected:

  QDoubleSpinBox *mClipLimit;
  QSpinBox *mTilesGridX;
  QSpinBox *mTilesGridY;

};

} // namespace photomatch

#endif // PHOTOMATCH_CLAHE_WIDGET_H
