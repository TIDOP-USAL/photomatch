#include "LucidWidget.h"


#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

LucidWidget::LucidWidget(QWidget *parent)
  : ILucidWidget (parent),
    mLucidKernel(new QSpinBox(this)),
    mBlurKernel(new QSpinBox(this))
{
  init();

  connect(mLucidKernel,         SIGNAL(valueChanged(int)),            this, SIGNAL(lucidKernelChange(int)));
  connect(mBlurKernel,          SIGNAL(valueChanged(int)),            this, SIGNAL(blurKernelChange(int)));

}

LucidWidget::~LucidWidget()
{

}

int LucidWidget::lucidKernel() const
{
  return mLucidKernel->value();
}

int LucidWidget::blurKernel() const
{
  return mBlurKernel->value();
}

void LucidWidget::setLucidKernel(int lucidKernel)
{
  const QSignalBlocker blockerLucidKernel(mLucidKernel);
  mLucidKernel->setValue(lucidKernel);
}

void LucidWidget::setBlurKernel(int blurKernel)
{
  const QSignalBlocker blockerBlurKernel(mBlurKernel);
  mBlurKernel->setValue(blurKernel);
}

void LucidWidget::update()
{
}

void LucidWidget::retranslate()
{

}

void LucidWidget::reset()
{
  const QSignalBlocker blockerLucidKernel(mLucidKernel);
  const QSignalBlocker blockerBlurKernel(mBlurKernel);

  mLucidKernel->setValue(1);
  mBlurKernel->setValue(2);
}

void LucidWidget::init()
{
  this->setWindowTitle("LUCID");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("LUCID Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Lucid Kernel:")), 0, 0);
  mLucidKernel->setRange(0, 100);
  propertiesLayout->addWidget(mLucidKernel, 0, 1);

  propertiesLayout->addWidget(new QLabel(tr("Blur Kernel:")), 1, 0);
  mBlurKernel->setRange(0, 100);
  propertiesLayout->addWidget(mBlurKernel, 1, 1);

  reset();
  update();
}

} // namespace photomatch



