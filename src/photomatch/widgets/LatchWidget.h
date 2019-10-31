#ifndef PHOTOMATCH_LATCH_WIDGET_H
#define PHOTOMATCH_LATCH_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QComboBox;
class QCheckBox;
class QSpinBox;

namespace photomatch
{

class PHOTOMATCH_EXPORT ILatchWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  ILatchWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
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


class PHOTOMATCH_EXPORT LatchWidget
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

// PhotoMatchWidget interface

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



} // namespace photomatch

#endif // PHOTOMATCH_LATCH_WIDGET_H
