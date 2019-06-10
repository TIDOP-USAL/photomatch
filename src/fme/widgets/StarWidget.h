#ifndef FME_STAR_WIDGET_H
#define FME_STAR_WIDGET_H

#include "fme/widgets/FmeWidget.h"

class QSpinBox;

namespace fme
{

class FME_EXPORT IStarWidget
  : public FmeWidget
{
  Q_OBJECT

public:

  IStarWidget(QWidget *parent = nullptr) : FmeWidget(parent){}
  virtual ~IStarWidget() = default;

  virtual int maxSize() const  = 0;
  virtual int responseThreshold() const  = 0;
  virtual int lineThresholdProjected() const  = 0;
  virtual int lineThresholdBinarized() const  = 0;
  virtual int suppressNonmaxSize() const  = 0;

signals:

  void maxSizeChange(int);
  void responseThresholdChange(int);
  void lineThresholdProjectedChange(int);
  void lineThresholdBinarizedChange(int);
  void suppressNonmaxSizeChange(int);

public slots:

  virtual void setMaxSize(int maxSize) = 0;
  virtual void setResponseThreshold(int responseThreshold) = 0;
  virtual void setLineThresholdProjected(int lineThresholdProjected) = 0;
  virtual void setLineThresholdBinarized(int lineThresholdBinarized) = 0;
  virtual void setSuppressNonmaxSize(int suppressNonmaxSize) = 0;

};

class FME_EXPORT StarWidget
  : public IStarWidget
{
  Q_OBJECT

public:

  StarWidget(QWidget *parent = nullptr);
  ~StarWidget() override;

// IStarWidget interface

public:

  int maxSize() const override;
  int responseThreshold() const override;
  int lineThresholdProjected() const override;
  int lineThresholdBinarized() const override;
  int suppressNonmaxSize() const override;

public slots:

  void setMaxSize(int maxSize) override;
  void setResponseThreshold(int responseThreshold) override;
  void setLineThresholdProjected(int lineThresholdProjected) override;
  void setLineThresholdBinarized(int lineThresholdBinarized) override;
  void setSuppressNonmaxSize(int suppressNonmaxSize) override;

// FmeWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mMaxSize;
  QSpinBox *mResponseThreshold;
  QSpinBox *mLineThresholdProjected;
  QSpinBox *mLineThresholdBinarized;
  QSpinBox *mSuppressNonmaxSize;
};

} // namespace fme

#endif // FME_STAR_WIDGET_H
