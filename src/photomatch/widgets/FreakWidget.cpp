#include "FreakWidget.h"

#include <QSpinBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

FreakWidget::FreakWidget(QWidget *parent)
  : IFreakWidget(parent),
    mOrientationNormalized(new QCheckBox(this)),
    mScaleNormalized(new QCheckBox(this)),
    mPatternScale(new QDoubleSpinBox(this)),
    mOctaves(new QSpinBox(this))
{
  init();

  /// Signals and slots
  connect(mOrientationNormalized,  SIGNAL(clicked(bool)),                this, SIGNAL(orientationNormalizedChange(bool)));
  connect(mScaleNormalized,        SIGNAL(clicked(bool)),                this, SIGNAL(scaleNormalizedChange(bool)));
  connect(mPatternScale,           SIGNAL(valueChanged(double)),         this, SIGNAL(patternScaleChange(double)));
  connect(mOctaves,                SIGNAL(valueChanged(int)),            this, SIGNAL(octavesChange(int)));
}

FreakWidget::~FreakWidget()
{

}

bool FreakWidget::orientationNormalized() const
{
  return mOrientationNormalized->isChecked();
}

bool FreakWidget::scaleNormalized() const
{
  return mScaleNormalized->isChecked();
}

double FreakWidget::patternScale() const
{
  return mPatternScale->value();
}

int FreakWidget::octaves() const
{
  return mOctaves->value();
}

void FreakWidget::setOrientationNormalized(bool orientationNormalized)
{
  mOrientationNormalized->setChecked(orientationNormalized);
}

void FreakWidget::setScaleNormalized(bool scaleNormalized)
{
  mScaleNormalized->setChecked(scaleNormalized);
}

void FreakWidget::setPatternScale(double patternScale)
{
  const QSignalBlocker blockerPatternScale(mPatternScale);
  mPatternScale->setValue(patternScale);
}

void FreakWidget::setOctaves(int octaves)
{
  const QSignalBlocker blockerOctaves(mOctaves);
  mOctaves->setValue(octaves);
}

void FreakWidget::update()
{
}

void FreakWidget::retranslate()
{

}

void FreakWidget::reset()
{
  const QSignalBlocker blockerPatternScale(mPatternScale);
  const QSignalBlocker blockerOctaves(mOctaves);

  mOrientationNormalized->setChecked(true);
  mScaleNormalized->setChecked(true);
  mPatternScale->setValue(22.0);
  mOctaves->setValue(4);
}

void FreakWidget::init()
{
  this->setWindowTitle("FREAK");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("FREAK Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  mOrientationNormalized->setText(tr("Orientation Normalization"));
  propertiesLayout->addWidget(mOrientationNormalized, 1, 0);

  mScaleNormalized->setText(tr("Scale Normalization"));
  propertiesLayout->addWidget(mScaleNormalized, 2, 0);

  propertiesLayout->addWidget(new QLabel(tr("Pattern Scale:")), 3, 0);
  mPatternScale->setRange(0., 1000.);
  propertiesLayout->addWidget(mPatternScale, 3, 1);

  propertiesLayout->addWidget(new QLabel(tr("Number of Octaves:")), 4, 0);
  mOctaves->setRange(0, 100);
  propertiesLayout->addWidget(mOctaves, 4, 1);

  reset(); /// set default values

  update();
}

} // namespace photomatch

