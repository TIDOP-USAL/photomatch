#ifndef FME_MSRCP_WIDGET_H
#define FME_MSRCP_WIDGET_H

#include "fme/widgets/FmeWidget.h"

class QDoubleSpinBox;

namespace fme
{

class FME_EXPORT IMsrcpWidget
  : public FmeWidget
{
  Q_OBJECT

public:

  IMsrcpWidget(QWidget *parent = nullptr) : FmeWidget(parent){}
  virtual ~IMsrcpWidget() = default;

  virtual double smallScale() const = 0;
  virtual double midScale() const  = 0;
  virtual double largeScale() const = 0;

signals:

  void smallScaleChange(double);
  void midScaleChange(double);
  void largeScaleChange(double);

public slots:

  virtual void setSmallScale(double smallScale) = 0;
  virtual void setMidScale(double midScale) = 0;
  virtual void setLargeScale(double largeScale) = 0;

};


class FME_EXPORT MsrcpWidget
  : public IMsrcpWidget
{
  Q_OBJECT

public:

  MsrcpWidget(QWidget *parent = nullptr);
  ~MsrcpWidget() override = default;


// IMsrcpWidget interface

public:

  double smallScale() const override;
  double midScale() const override;
  double largeScale() const override;

public slots:

  void setSmallScale(double smallScale) override;
  void setMidScale(double midScale) override;
  void setLargeScale(double largeScale) override;

// FmeWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QDoubleSpinBox *mSmallScale;
  QDoubleSpinBox *mMidScale;
  QDoubleSpinBox *mLargeScale;
};


} // namespace fme


#endif // FME_MSRCP_WIDGET_H
