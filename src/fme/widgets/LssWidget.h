#ifndef FME_LSS_WIDGET_H
#define FME_LSS_WIDGET_H

#include "fme/widgets/FmeWidget.h"

class QSpinBox;

namespace fme
{

/*!
 * \brief Interface for LSS Widgets class
 */
class FME_EXPORT ILssWidget
  : public FmeWidget
{

  Q_OBJECT

public:

  ILssWidget(QWidget *parent = nullptr) : FmeWidget(parent){}
  virtual ~ILssWidget() = default;

};


class FME_EXPORT LssWidget
  : public ILssWidget
{

Q_OBJECT

public:

  LssWidget(QWidget *parent = nullptr);
  ~LssWidget() override;


// FmeWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

};

} // namespace fme

#endif // FME_LSS_WIDGET_H
