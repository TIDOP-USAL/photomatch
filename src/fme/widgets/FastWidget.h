#ifndef FME_FAST_WIDGET_H
#define FME_FAST_WIDGET_H

#include <QWidget>

class QSpinBox;
class QComboBox;
class QCheckBox;

namespace fme
{

class IFastWidget
  : public QWidget
{
  Q_OBJECT

public:

  IFastWidget(QWidget *parent = nullptr) : QWidget(parent){}
  virtual ~IFastWidget() = default;

  virtual int threshold() const = 0;
  virtual bool nonmaxSuppression() const = 0;
  virtual QString detectorType() const = 0;

signals:

  void thresholdChange(int);
  void nonmaxSuppressionChange(bool);
  void detectorTypeChange(QString);

public slots:

  virtual void setThreshold(int threshold) = 0;
  virtual void setNonmaxSuppression(bool nonmaxSuppression) = 0;
  virtual void setDetectorType(QString detectorType) = 0;

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;

};

class FastWidget
  : public IFastWidget
{

  Q_OBJECT

public:

  FastWidget(QWidget *parent = nullptr);
  ~FastWidget() override;

// IFastWidget interface

public:

  int threshold() const override;
  bool nonmaxSuppression() const override;
  QString detectorType() const override;

public slots:

  void setThreshold(int threshold) override;
  void setNonmaxSuppression(bool nonmaxSuppression) override;
  void setDetectorType(QString detectorType) override;

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mThreshold;
  QCheckBox *mNonmaxSuppression;
  QComboBox *mDetectorType;

};

} // namespace fme

#endif // FME_FAST_WIDGET_H
