#include "SurfWidget.h"

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

SurfWidget::SurfWidget(QWidget *parent)
  : ISurfWidget(parent),
    mHessianThreshold(new QDoubleSpinBox(this)),
    mOctaves(new QSpinBox(this)),
    mOctaveLayers(new QSpinBox(this)),
    mExtendedDescriptor(new QCheckBox(this)),
    mRotatedFeatures(new QCheckBox(this))
{
  init();

  /// Signals and slots
  connect(mHessianThreshold,    SIGNAL(valueChanged(double)),    this, SIGNAL(hessianThresholdChange(double)));
  connect(mOctaves,             SIGNAL(valueChanged(int)),       this, SIGNAL(octavesChange(int)));
  connect(mOctaveLayers,        SIGNAL(valueChanged(int)),       this, SIGNAL(octaveLayersChange(int)));
  connect(mExtendedDescriptor,  SIGNAL(clicked(bool)),           this, SIGNAL(extendedDescriptorChange(bool)));
  connect(mRotatedFeatures,     SIGNAL(clicked(bool)),           this, SIGNAL(rotatedFeaturesChange(bool)));
}

SurfWidget::~SurfWidget()
{
}

double SurfWidget::hessianThreshold() const
{
  return mHessianThreshold->value();
}

int SurfWidget::octaves() const
{
  return mOctaves->value();
}

int SurfWidget::octaveLayers() const
{
  return mOctaveLayers->value();
}

bool SurfWidget::extendedDescriptor() const
{
  return mExtendedDescriptor->isChecked();
}

bool SurfWidget::rotatedFeatures() const
{
  return mRotatedFeatures->isChecked();
}

void SurfWidget::setHessianThreshold(double hessianThreshold)
{
  const QSignalBlocker blockerHessianThreshold(mHessianThreshold);
  mHessianThreshold->setValue(hessianThreshold);
}

void SurfWidget::setOctaves(int octaves)
{
  const QSignalBlocker blockerOctaves(mOctaves);
  mOctaves->setValue(octaves);
}

void SurfWidget::setOctaveLayers(int octaveLayers)
{
  const QSignalBlocker blockerOctaveLayers(mOctaveLayers);
  mOctaveLayers->setValue(octaveLayers);
}

void SurfWidget::setExtendedDescriptor(bool extendedDescriptor)
{
  mExtendedDescriptor->setChecked(extendedDescriptor);
}

void SurfWidget::setRotatedFeatures(bool rotatedFeatures)
{
  mRotatedFeatures->setChecked(rotatedFeatures);
}

void SurfWidget::update()
{
}

void SurfWidget::reset()
{
  const QSignalBlocker blockerHessianThreshold(mHessianThreshold);
  const QSignalBlocker blockerOctaves(mOctaves);
  const QSignalBlocker blockerOctaveLayers(mOctaveLayers);

  mHessianThreshold->setValue(100);
  mOctaves->setValue(4);
  mOctaveLayers->setValue(3);
  mExtendedDescriptor->setChecked(false);
  mRotatedFeatures->setChecked(false);
}

void SurfWidget::init()
{
  this->setWindowTitle("SURF");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("SURF Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout(this);
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Hessian Threshold:")), 0, 0);
  mHessianThreshold->setRange(0, 10000);
  propertiesLayout->addWidget(mHessianThreshold, 0, 1);

  propertiesLayout->addWidget(new QLabel(tr("Octaves:")), 1, 0);
  mOctaves->setRange(0, 100);
  propertiesLayout->addWidget(mOctaves, 1, 1);

  propertiesLayout->addWidget(new QLabel(tr("Octave Layers:")), 2, 0);
  mOctaveLayers->setRange(0, 100);
  propertiesLayout->addWidget(mOctaveLayers, 2, 1);

  mExtendedDescriptor->setText(tr("Extended Descriptor"));
  propertiesLayout->addWidget(mExtendedDescriptor, 3, 0);

  mRotatedFeatures->setText(tr("Rotated Features"));
  propertiesLayout->addWidget(mRotatedFeatures, 4, 0);

  reset(); /// set default values

  update();
}

} // namespace fme

