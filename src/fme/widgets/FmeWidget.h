#ifndef FME_WIDGET_H
#define FME_WIDGET_H

#include "fme/fme_global.h"

#include <QWidget>

namespace fme
{

class FME_EXPORT FmeWidget
  : public QWidget
{

public:

  FmeWidget(QWidget *parent = nullptr) : QWidget(parent){}
  ~FmeWidget() = default;

public slots:

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;
};

} // namespace fme

#endif // FME_WIDGET_H
