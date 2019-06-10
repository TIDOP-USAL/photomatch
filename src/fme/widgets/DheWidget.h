#ifndef FME_DHE_WIDGET_H
#define FME_DHE_WIDGET_H

#include "fme/widgets/FmeWidget.h"

class QSpinBox;

namespace fme
{

class IDheWidget
  : public FmeWidget
{
  Q_OBJECT

public:

  IDheWidget(QWidget *parent = nullptr) : FmeWidget(parent){}
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

// FmeWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mX;
};

} // namespace fme

#endif // FME_DHE_WIDGET_H
