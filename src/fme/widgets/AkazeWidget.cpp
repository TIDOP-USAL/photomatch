#include "AkazeWidget.h"

#include <QSpinBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

AkazeWidget::AkazeWidget(QWidget *parent)
  : IAkazeWidget(parent),
    mDescriptorType(new QComboBox(this)),
    mDescriptorSize(new QSpinBox(this)),
    mDescriptorChannels(new QSpinBox(this)),
    mThreshold(new QDoubleSpinBox(this)),
    mOctaves(new QSpinBox(this)),
    mOctaveLayers(new QSpinBox(this)),
    mDiffusivity(new QComboBox(this))
{
  init();

  /// Signals and slots
  connect(mDescriptorType,     SIGNAL(currentTextChanged(QString)), this, SIGNAL(descriptorTypeChange(QString)));
  connect(mDescriptorSize,     SIGNAL(valueChanged(int)),           this, SIGNAL(descriptorSizeChange(int)));
  connect(mDescriptorChannels, SIGNAL(valueChanged(int)),           this, SIGNAL(descriptorChannelsChange(int)));
  connect(mThreshold,          SIGNAL(valueChanged(double)),        this, SIGNAL(thresholdChange(double)));
  connect(mOctaves,            SIGNAL(valueChanged(int)),           this, SIGNAL(octavesChange(int)));
  connect(mOctaveLayers,       SIGNAL(valueChanged(int)),           this, SIGNAL(octaveLayersChange(int)));
  connect(mDiffusivity,        SIGNAL(currentTextChanged(QString)), this, SIGNAL(diffusivityChange(QString)));
}

AkazeWidget::~AkazeWidget()
{

}

QString AkazeWidget::descriptorType() const
{
  return mDescriptorType->currentText();
}

int AkazeWidget::descriptorSize() const
{
  return mDescriptorSize->value();
}

int AkazeWidget::descriptorChannels() const
{
  return mDescriptorChannels->value();
}

double AkazeWidget::threshold() const
{
  return mThreshold->value();
}

int AkazeWidget::octaves() const
{
  return mOctaves->value();
}

int AkazeWidget::octaveLayers() const
{
  return mOctaveLayers->value();
}

QString AkazeWidget::diffusivity() const
{
  return mDiffusivity->currentText();
}

void AkazeWidget::setDescriptorType(const QString &descriptorType)
{
  const QSignalBlocker blockerDescriptorType(mDescriptorType);
  mDescriptorType->setCurrentText(descriptorType);
}

void AkazeWidget::setDescriptorSize(int descriptorSize)
{
  const QSignalBlocker blockerDescriptorSize(mDescriptorSize);
  mDescriptorSize->setValue(descriptorSize);
}

void AkazeWidget::setDescriptorChannels(int channels)
{
  const QSignalBlocker blockerDescriptorChannels(mDescriptorChannels);
  mDescriptorChannels->setValue(channels);
}

void AkazeWidget::setThreshold(double threshold)
{
  const QSignalBlocker blockerThreshold(mThreshold);
  mThreshold->setValue(threshold);
}

void AkazeWidget::setOctaves(int octaves)
{
  const QSignalBlocker blockerOctaves(mOctaves);
  mOctaves->setValue(octaves);
}

void AkazeWidget::setOctaveLayers(int octaveLayers)
{
  const QSignalBlocker blockerOctaveLayers(mOctaveLayers);
  mOctaveLayers->setValue(octaveLayers);
}

void AkazeWidget::setDiffusivity(const QString &diffusivity)
{
  const QSignalBlocker blockerDiffusivity(mDiffusivity);
  mDiffusivity->setCurrentText(diffusivity);
}

void AkazeWidget::update()
{

}

void AkazeWidget::reset()
{
  const QSignalBlocker blockerDescriptorType(mDescriptorType);
  const QSignalBlocker blockerDescriptorSize(mDescriptorSize);
  const QSignalBlocker blockerDescriptorChannels(mDescriptorChannels);
  const QSignalBlocker blockerThreshold(mThreshold);
  const QSignalBlocker blockerOctaves(mOctaves);
  const QSignalBlocker blockerOctaveLayers(mOctaveLayers);
  const QSignalBlocker blockerDiffusivity(mDiffusivity);

  mDescriptorType->setCurrentText("MLDB");
  mDescriptorSize->setValue(0);
  mDescriptorChannels->setValue(3);
  mThreshold->setValue(0.001);
  mOctaves->setValue(4);
  mOctaveLayers->setValue(4);
  mDiffusivity->setCurrentText("DIFF_PM_G2");
}

void AkazeWidget::init()
{
  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("AKAZE Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout(this);
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Descriptor Type:")), 0, 0);
  mDescriptorType->addItem("KAZE");
  mDescriptorType->addItem("KAZE_UPRIGHT");
  mDescriptorType->addItem("MLDB");
  mDescriptorType->addItem("MLDB_UPRIGHT");
  mDescriptorType->setCurrentText("MLDB");
  propertiesLayout->addWidget(mDescriptorType, 0, 1);

  propertiesLayout->addWidget(new QLabel(tr("Descriptor Size:")), 1, 0);
  mDescriptorSize->setRange(0, 64); // TODO: creo que no soporta mas que 64. comprobar
  propertiesLayout->addWidget(mDescriptorSize, 1, 1);

  propertiesLayout->addWidget(new QLabel(tr("Descriptor Channels:")), 2, 0);
  mDescriptorChannels->setRange(1, 3);
  propertiesLayout->addWidget(mDescriptorChannels, 2, 1);

  propertiesLayout->addWidget(new QLabel(tr("Threshold:")), 3, 0);
  mThreshold->setDecimals(3);
  mThreshold->setRange(0, 99.99);
  mThreshold->setSingleStep(0.01);
  propertiesLayout->addWidget(mThreshold, 3, 1);

  propertiesLayout->addWidget(new QLabel(tr("Octaves:")), 4, 0);
  mOctaves->setRange(0, 100);
  propertiesLayout->addWidget(mOctaves, 4, 1);

  propertiesLayout->addWidget(new QLabel(tr("Octave Layers:")), 5, 0);
  mOctaveLayers->setRange(0, 100);
  propertiesLayout->addWidget(mOctaveLayers, 5, 1);

  propertiesLayout->addWidget(new QLabel(tr("Diffusivity:")), 6, 0);
  mDiffusivity->addItem("DIFF_PM_G1");
  mDiffusivity->addItem("DIFF_PM_G2");
  mDiffusivity->addItem("DIFF_WEICKERT");
  mDiffusivity->addItem("DIFF_CHARBONNIER");
  propertiesLayout->addWidget(mDiffusivity, 6, 1);

  reset();  /// set default values

  update();
}

} // namespace fme
