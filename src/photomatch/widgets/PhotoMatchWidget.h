#ifndef PHOTOMATCH_WIDGET_H
#define PHOTOMATCH_WIDGET_H

#include "photomatch/photomatch_global.h"

#include <QWidget>

namespace photomatch
{

class PHOTOMATCH_EXPORT PhotoMatchWidget
  : public QWidget
{

public:

  PhotoMatchWidget(QWidget *parent = nullptr) : QWidget(parent){}
  ~PhotoMatchWidget() = default;

protected slots:

  virtual void update() = 0;
  virtual void retranslate() = 0;

public slots:

  virtual void reset() = 0;

private:

  virtual void init() = 0;
};

} // namespace photomatch

#endif // PHOTOMATCH_WIDGET_H
