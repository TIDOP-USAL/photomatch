#include "DheWidget.h"

#include <QSpinBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
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

void DheWidget::reset()
{
  const QSignalBlocker blockerX(mX);

  mX->setValue(1);
}

void DheWidget::init()
{
  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("Dhe Parameters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout(this);
  groupBox->setLayout(propertiesLayout);

  QLabel *lbl = new QLabel(tr("Dynamic Histogram Equalization"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  lbl->setFont(font);
  propertiesLayout->addWidget(lbl, 0, 0);

  propertiesLayout->addWidget(new QLabel(tr("x:")), 0, 0);
  mX->setRange(0, 5);
  propertiesLayout->addWidget(mX, 0, 1);

  reset(); /// set default values

  update();
}


} // namespace fme


