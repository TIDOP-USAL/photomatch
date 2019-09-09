#ifndef FME_DECOLOR_WIDGET_H
#define FME_DECOLOR_WIDGET_H

#include "fme/widgets/FmeWidget.h"

namespace fme
{

class IDecolorWidget
  : public FmeWidget
{
  Q_OBJECT

public:

  IDecolorWidget(QWidget *parent = nullptr) : FmeWidget(parent){}
  virtual ~IDecolorWidget() = default;

};

class DecolorWidget
  : public IDecolorWidget
{

  Q_OBJECT

public:

  DecolorWidget(QWidget *parent = nullptr);
  ~DecolorWidget() override;

// FmeWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;
};


} // namespace fme

#endif // FME_DECOLOR_WIDGET_H
