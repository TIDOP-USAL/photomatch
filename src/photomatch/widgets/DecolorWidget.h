#ifndef PHOTOMATCH_DECOLOR_WIDGET_H
#define PHOTOMATCH_DECOLOR_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

namespace photomatch
{

class IDecolorWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  IDecolorWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~IDecolorWidget() = default;

};

class DecolorWidget
  : public IDecolorWidget
{

  Q_OBJECT

public:

  DecolorWidget(QWidget *parent = nullptr);
  ~DecolorWidget() override;

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  void init() override;
};


} // namespace photomatch

#endif // PHOTOMATCH_DECOLOR_WIDGET_H
