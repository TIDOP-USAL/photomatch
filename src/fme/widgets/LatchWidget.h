#ifndef FME_LATCH_WIDGET_H
#define FME_LATCH_WIDGET_H

#include "fme/widgets/FmeWidget.h"

class QComboBox;
class QCheckBox;
class QSpinBox;

namespace fme
{

class FME_EXPORT ILatchWidget
  : public FmeWidget
{
  Q_OBJECT

public:

  ILatchWidget(QWidget *parent = nullptr) : FmeWidget(parent){}
  virtual ~ILatchWidget() = default;

  virtual QString bytes() const = 0;
  virtual bool rotationInvariance() const = 0;
  virtual int halfSsdSize() const = 0;

signals:

  void bytesChange(QString);
  void rotationInvarianceChange(bool);
  void halfSsdSizeChange(int);

public slots:

  virtual void setBytes(const QString &bytes) = 0;
  virtual void setRotationInvariance(bool rotationInvariance) = 0;
  virtual void setHalfSsdSize(int halfSsdSize) = 0;

};


class FME_EXPORT LatchWidget
  : public ILatchWidget
{
  Q_OBJECT

public:

  LatchWidget(QWidget *parent = nullptr);
  ~LatchWidget() override;

// ILatchWidget interface

public:

  QString bytes() const override;
  bool rotationInvariance() const override;
  int halfSsdSize() const override;

public slots:

  void setBytes(const QString &bytes) override;
  void setRotationInvariance(bool rotationInvariance) override;
  void setHalfSsdSize(int halfSsdSize) override;

// FmeWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QComboBox *mBytes;
  QCheckBox *mRotationInvariance;
  QSpinBox *mHalfSsdSize;

};



} // namespace fme

#endif // FME_LATCH_WIDGET_H
