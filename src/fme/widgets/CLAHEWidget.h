#ifndef FME_CLAHE_WIDGET_H
#define FME_CLAHE_WIDGET_H

#include <QWidget>

class QDoubleSpinBox;
class QSpinBox;

namespace fme
{

/*!
 * \brief CLAHE (Contrast Limited Adaptive Histogram Equalization)
 * Equalizes the histogram of a grayscale image using Contrast Limited
 * Adaptive Histogram Equalization.
 */
class ICLAHEWidget
  : public QWidget
{
  Q_OBJECT

public:

  ICLAHEWidget(QWidget *parent = nullptr) : QWidget(parent){}
  virtual ~ICLAHEWidget() {}

  virtual double clipLimit() const = 0;
  virtual QSize tileGridSize() const = 0;

signals:

  void clipLimitChange(double);
  void tileGridSizeChange(QSize);

public slots:

  virtual void setClipLimit(double clipLimit) = 0;
  virtual void setTilesGridSize (QSize tileGridSize) = 0;

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;

};


class CLAHEWidget
  : public ICLAHEWidget
{
  Q_OBJECT

public:

  CLAHEWidget(QWidget *parent = nullptr);
  ~CLAHEWidget() override;

protected slots:

  void onTilesGridXChange(int gx);
  void onTilesGridYChange(int gy);

// ICLAHEWidget interface

public:

  double clipLimit() const override;
  QSize tileGridSize() const override;

public slots:

  void setClipLimit(double clipLimit) override;
  void setTilesGridSize(QSize tileGridSize) override;
  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QDoubleSpinBox *mClipLimit;
  QSpinBox *mTilesGridX;
  QSpinBox *mTilesGridY;

};

} // namespace fme

#endif // FME_CLAHE_WIDGET_H
