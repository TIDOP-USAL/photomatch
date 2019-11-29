#ifndef PHOTOMATCH_DHE_WIDGET_H
#define PHOTOMATCH_DHE_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QSpinBox;

namespace photomatch
{

class IDheWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  IDheWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~IDheWidget() = default;

  virtual int x() const = 0;

signals:

  void xChange(int);

public slots:

  virtual void setX(int x) = 0;

};

class DheWidget
  : public IDheWidget
{
  Q_OBJECT

public:

  DheWidget(QWidget *parent = nullptr);
  ~DheWidget() override;

// IDheWidget interface

public:

  int x() const override;

public slots:

  void setX(int x) override;

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mX;
};

} // namespace photomatch

#endif // PHOTOMATCH_DHE_WIDGET_H
