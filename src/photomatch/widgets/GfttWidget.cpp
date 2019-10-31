#include "GfttWidget.h"

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>

namespace photomatch
{

GfttWidget::GfttWidget(QWidget *parent)
  : IGfttWidget(parent),
    mMaxFeatures(new QSpinBox(this)),
    mQualityLevel(new QDoubleSpinBox(this)),
    mMinDistance(new QDoubleSpinBox(this)),
    mBlockSize(new QSpinBox(this)),
    mHarrisDetector(new QCheckBox(this)),
    mK(new QDoubleSpinBox(this))
{
  init();

  /// Signals and slots
  connect(mMaxFeatures,       SIGNAL(valueChanged(int)),      this, SIGNAL(maxFeaturesChange(int)));
  connect(mQualityLevel,      SIGNAL(valueChanged(double)),   this, SIGNAL(qualityLevelChange(double)));
  connect(mMinDistance,       SIGNAL(valueChanged(double)),   this, SIGNAL(minDistanceChange(double)));
  connect(mBlockSize,         SIGNAL(valueChanged(int)),      this, SIGNAL(blockSizeChange(int)));
  connect(mHarrisDetector,    SIGNAL(clicked(bool)),          this, SIGNAL(harrisDetectorChange(bool)));
  connect(mK,                 SIGNAL(valueChanged(double)),   this, SIGNAL(kChange(double)));
}

GfttWidget::~GfttWidget()
{

}

int GfttWidget::maxFeatures() const
{
  return mMaxFeatures->value();
}

double GfttWidget::qualityLevel() const
{
  return mQualityLevel->value();
}

double GfttWidget::minDistance() const
{
  return mMinDistance->value();
}

int GfttWidget::blockSize() const
{
  return mBlockSize->value();
}

bool GfttWidget::harrisDetector() const
{
  return mHarrisDetector->isChecked();
}

double GfttWidget::k() const
{
  return mK->value();
}

void GfttWidget::setMaxFeatures(int maxFeatures)
{
  const QSignalBlocker blocker(mMaxFeatures);
  mMaxFeatures->setValue(maxFeatures);
}

void GfttWidget::setQualityLevel(double qlevel)
{
  const QSignalBlocker blocker(mQualityLevel);
  mQualityLevel->setValue(qlevel);
}

void GfttWidget::setMinDistance(double minDistance)
{
  const QSignalBlocker blocker(mMinDistance);
  mMinDistance->setValue(minDistance);
}

void GfttWidget::setBlockSize(int blockSize)
{
  const QSignalBlocker blocker(mBlockSize);
  mBlockSize->setValue(blockSize);
}

void GfttWidget::setHarrisDetector(bool value)
{
  mHarrisDetector->setChecked(value);
}

void GfttWidget::setK(double k)
{
  const QSignalBlocker blocker(mK);
  mK->setValue(k);
}

void GfttWidget::update()
{
}

void GfttWidget::reset()
{
  const QSignalBlocker blocker1(mMaxFeatures);
  const QSignalBlocker blocker2(mQualityLevel);
  const QSignalBlocker blocker3(mMinDistance);
  const QSignalBlocker blocker4(mBlockSize);
  const QSignalBlocker blocker5(mK);

  mMaxFeatures->setValue(1000);
  mQualityLevel->setValue(0.01);
  mMinDistance->setValue(1);
  mBlockSize->setValue(3);
  mHarrisDetector->setChecked(false);
  mK->setValue(0.04);
}

void GfttWidget::init()
{
  this->setWindowTitle("GFTT");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("GFTT Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Max Features:")), 0, 0);
  mMaxFeatures->setRange(0, 1000000);
  propertiesLayout->addWidget(mMaxFeatures, 0, 1);

  propertiesLayout->addWidget(new QLabel(tr("Quality Level:")), 1, 0);
  mQualityLevel->setRange(0., 100.);
  mQualityLevel->setSingleStep(0.01);
  propertiesLayout->addWidget(mQualityLevel, 1, 1);

  propertiesLayout->addWidget(new QLabel(tr("Min Distance:")), 2, 0);
  mMinDistance->setRange(0., 10000.);
  propertiesLayout->addWidget(mMinDistance, 2, 1);

  propertiesLayout->addWidget(new QLabel(tr("Block Size:")), 3, 0);
  mBlockSize->setRange(0, 100);
  propertiesLayout->addWidget(mBlockSize, 3, 1);

  mHarrisDetector->setText(tr("Harris Detector"));
  propertiesLayout->addWidget(mHarrisDetector, 4, 0);

  propertiesLayout->addWidget(new QLabel(tr("K:")), 5, 0);
  mK->setRange(0., 100.);
  mK->setSingleStep(0.01);
  propertiesLayout->addWidget(mK, 5, 1);

  reset(); /// set default values

  update();
}


} // namespace photomatch
