#ifndef PHOTOMATCH_MSRCP_WIDGET_H
#define PHOTOMATCH_MSRCP_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QDoubleSpinBox;

namespace photomatch
{

class PHOTOMATCH_EXPORT IMsrcpWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  IMsrcpWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
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


class PHOTOMATCH_EXPORT MsrcpWidget
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

// PhotoMatchWidget interface

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


} // namespace photomatch


#endif // PHOTOMATCH_MSRCP_WIDGET_H
