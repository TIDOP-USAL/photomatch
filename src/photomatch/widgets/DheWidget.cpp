#include "DheWidget.h"

#include <QSpinBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

DheWidget::DheWidget(QWidget *parent)
  : IDheWidget(parent),
    mX(new QSpinBox(this))
{
  init();

  /// Signals and slots
  connect(mX,    SIGNAL(valueChanged(int)),      this, SIGNAL(xChange(int)));

}

DheWidget::~DheWidget()
{

}

int DheWidget::x() const
{
  return mX->value();
}

void DheWidget::setX(int x)
{
  const QSignalBlocker blockerX(mX);
  mX->setValue(x);
}

void DheWidget::update()
{

}

void DheWidget::retranslate()
{

}

void DheWidget::reset()
{
  const QSignalBlocker blockerX(mX);

  mX->setValue(1);
}

void DheWidget::init()
{
  this->setWindowTitle("DHE");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("DHE Parameters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout(groupBox);

  QLabel *lbl = new QLabel(tr("Dynamic Histogram Equalization"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  lbl->setFont(font);
  propertiesLayout->addWidget(lbl, 0, 0, 1, 2);

  propertiesLayout->addWidget(new QLabel(tr("x:")), 1, 0, 1, 1);
  mX->setRange(0, 5);
  propertiesLayout->addWidget(mX, 1, 1, 1, 1);

  reset(); /// set default values

  update();
}


} // namespace photomatch


