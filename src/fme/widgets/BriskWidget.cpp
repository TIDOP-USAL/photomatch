#include "BriskWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

BriskWidget::BriskWidget(QWidget *parent)
  : IBriskWidget(parent),
    mThreshold(new QSpinBox(this)),
    mOctaves(new QSpinBox(this)),
    mPatternScale(new QDoubleSpinBox(this))
{
  init();

  /// Signals and slots
  connect(mThreshold,        SIGNAL(valueChanged(int)),        this, SIGNAL(thresholdChange(int)));
  connect(mOctaves,          SIGNAL(valueChanged(int)),        this, SIGNAL(octavesChange(int)));
  connect(mPatternScale,     SIGNAL(valueChanged(double)),     this, SIGNAL(patternScaleChange(double)));

}

BriskWidget::~BriskWidget()
{

}

int BriskWidget::threshold() const
{
  return mThreshold->value();
}

int BriskWidget::octaves() const
{
  return mOctaves->value();
}

double BriskWidget::patternScale() const
{
  return mPatternScale->value();
}

void BriskWidget::setThreshold(int threshold)
{
  const QSignalBlocker blockerThreshold(mThreshold);
  mThreshold->setValue(threshold);
}

void BriskWidget::setOctaves(int octaves)
{
  const QSignalBlocker blockerOctaves(mOctaves);
  mOctaves->setValue(octaves);
}

void BriskWidget::setPatternScale(double patternScale)
{
  const QSignalBlocker blockerPatternScale(mPatternScale);
  mPatternScale->setValue(patternScale);
}

void BriskWidget::update()
{
}

void BriskWidget::reset()
{
  const QSignalBlocker blockerThreshold(mThreshold);
  const QSignalBlocker blockerOctaves(mOctaves);
  const QSignalBlocker blockerPatternScale(mPatternScale);

  mThreshold->setValue(30);
  mOctaves->setValue(3);
  mPatternScale->setValue(1.0);
}

void BriskWidget::init()
{
  this->setWindowTitle("BRISK");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("BRISK Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Threshold:")), 0, 0);
  mThreshold->setRange(0, 100);
  propertiesLayout->addWidget(mThreshold, 0, 1);

  propertiesLayout->addWidget(new QLabel(tr("Octaves:")), 1, 0);
  mOctaves->setRange(0, 100);
  propertiesLayout->addWidget(mOctaves, 1, 1);

  propertiesLayout->addWidget(new QLabel(tr("Pattern Scale:")), 2, 0);
  mPatternScale->setRange(0., 10000.);
  propertiesLayout->addWidget(mPatternScale, 2, 1);

  reset(); // set default values

  update();
}

} // namespace fme
