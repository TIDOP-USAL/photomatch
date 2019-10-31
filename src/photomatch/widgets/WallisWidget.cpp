#include "WallisWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>

namespace photomatch
{

WallisWidget::WallisWidget(QWidget *parent)
  : IWallisWidget(parent),
    mContrast(new QDoubleSpinBox(this)),
    mBrightness(new QDoubleSpinBox(this)),
    mImposedAverage(new QSpinBox(this)),
    mImposedLocalStdDev(new QSpinBox(this)),
    mKernelSize(new QSpinBox(this))
{
  init();

  /// Signals and slots

  connect(mContrast,            SIGNAL(valueChanged(double)),     this, SIGNAL(contrastChange(double)));
  connect(mBrightness,          SIGNAL(valueChanged(double)),     this, SIGNAL(brightnessChange(double)));
  connect(mImposedAverage,      SIGNAL(valueChanged(int)),        this, SIGNAL(imposedAverageChange(int)));
  connect(mImposedLocalStdDev,  SIGNAL(valueChanged(int)),        this, SIGNAL(imposedLocalStdDevChange(int)));
  connect(mKernelSize,          SIGNAL(valueChanged(int)),        this, SIGNAL(kernelSizeChange(int)));
}

WallisWidget::~WallisWidget()
{

}

double WallisWidget::contrast() const
{
  return mContrast->value();
}

double WallisWidget::brightness() const
{
  return mBrightness->value();
}

int WallisWidget::imposedAverage() const
{
  return mImposedAverage->value();
}

int WallisWidget::imposedLocalStdDev() const
{
  return mImposedLocalStdDev->value();
}

int WallisWidget::kernelSize() const
{
  return mKernelSize->value();
}

void WallisWidget::setContrast(double contrast)
{
  const QSignalBlocker blockerContrast(mContrast);
  mContrast->setValue(contrast);
}

void WallisWidget::setBrightness(double brightness)
{
  const QSignalBlocker blockerBrightness(mBrightness);
  mBrightness->setValue(brightness);
}

void WallisWidget::setImposedAverage(int imposedAverage)
{
  const QSignalBlocker blockerImposedAverage(mImposedAverage);
  mImposedAverage->setValue(imposedAverage);
}

void WallisWidget::setImposedLocalStdDev(int imposedLocalStdDev)
{
  const QSignalBlocker blockerImposedLocalStdDev(mImposedLocalStdDev);
  mImposedLocalStdDev->setValue(imposedLocalStdDev);
}

void WallisWidget::setKernelSize(int kernelSize)
{
  const QSignalBlocker blockerKernelSize(mKernelSize);
  mKernelSize->setValue(kernelSize);
}

void WallisWidget::update()
{
}

void WallisWidget::reset()
{
  const QSignalBlocker blockerContrast(mContrast);
  const QSignalBlocker blockerBrightness(mBrightness);
  const QSignalBlocker blockerImposedAverage(mImposedAverage);
  const QSignalBlocker blockerImposedLocalStdDev(mImposedLocalStdDev);
  const QSignalBlocker blockerKernelSize(mKernelSize);

  mContrast->setValue(1.0);
  mBrightness->setValue(0.2);
  mImposedAverage->setValue(41);
  mImposedLocalStdDev->setValue(127);
  mKernelSize->setValue(50);
}

void WallisWidget::init()
{
  this->setWindowTitle("Wallis Filter");

  QGridLayout *layout = new QGridLayout();

  layout->addWidget(new QLabel(tr("Contrast:")), 0, 0);
  mContrast->setRange(0, 1);
  mContrast->setSingleStep(0.1);
  layout->addWidget(mContrast, 0, 1);

  layout->addWidget(new QLabel(tr("Brightness:")), 1, 0);
  mBrightness->setRange(0, 1);
  mBrightness->setSingleStep(0.1);
  layout->addWidget(mBrightness, 1, 1);

  layout->addWidget(new QLabel(tr("Imposed Average:")), 2, 0);
  mImposedAverage->setRange(1, 1000);
  mImposedAverage->setSingleStep(1);
  layout->addWidget(mImposedAverage, 2,1);

  layout->addWidget(new QLabel(tr("Imposed Local StdDev:")), 3, 0);
  mImposedLocalStdDev->setRange(1, 10000);
  mImposedLocalStdDev->setSingleStep(1);
  layout->addWidget(mImposedLocalStdDev, 3, 1);

  layout->addWidget(new QLabel(tr("Kernel Size:")), 4, 0);
  mKernelSize->setRange(1, 10000);
  mKernelSize->setSingleStep(1);
  layout->addWidget(mKernelSize, 4, 1);

  this->setLayout(layout);

  reset(); /// set default values

  update();
}

} // namespace photomatch




