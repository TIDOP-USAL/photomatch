#ifndef PHOTOMATCH_LSS_WIDGET_H
#define PHOTOMATCH_LSS_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QSpinBox;

namespace photomatch
{

/*!
 * \brief Interface for LSS Widgets class
 */
class PHOTOMATCH_EXPORT ILssWidget
  : public PhotoMatchWidget
{

  Q_OBJECT

public:

  ILssWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~ILssWidget() = default;

};


class PHOTOMATCH_EXPORT LssWidget
  : public ILssWidget
{

Q_OBJECT

public:

  LssWidget(QWidget *parent = nullptr);
  ~LssWidget() override;


// PhotoMatchWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

};

} // namespace photomatch

#endif // PHOTOMATCH_LSS_WIDGET_H
