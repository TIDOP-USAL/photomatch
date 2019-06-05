#ifndef FME_LATCH_WIDGET_H
#define FME_LATCH_WIDGET_H

#include "fme/fme_global.h"

#include <QWidget>

class QComboBox;
class QCheckBox;
class QSpinBox;

namespace fme
{

class FME_EXPORT ILatchWidget
  : public QWidget
{
  Q_OBJECT

public:

  ILatchWidget(QWidget *parent = nullptr) : QWidget(parent){}
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

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;

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
