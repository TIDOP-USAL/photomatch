#include "StarWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

StarWidget::StarWidget(QWidget *parent)
  : IStarWidget(parent),
    mMaxSize(new QSpinBox(this)),
    mResponseThreshold(new QSpinBox(this)),
    mLineThresholdProjected(new QSpinBox(this)),
    mLineThresholdBinarized(new QSpinBox(this)),
    mSuppressNonmaxSize(new QSpinBox(this))
{
  init();

  /// Signals and slots
  connect(mMaxSize,                    SIGNAL(valueChanged(int)),            this, SIGNAL(maxSizeChange(int)));
  connect(mResponseThreshold,          SIGNAL(valueChanged(int)),            this, SIGNAL(responseThresholdChange(int)));
  connect(mLineThresholdProjected,     SIGNAL(valueChanged(int)),            this, SIGNAL(lineThresholdProjectedChange(int)));
  connect(mLineThresholdBinarized,     SIGNAL(valueChanged(int)),            this, SIGNAL(lineThresholdBinarizedChange(int)));
  connect(mSuppressNonmaxSize,         SIGNAL(valueChanged(int)),            this, SIGNAL(suppressNonmaxSizeChange(int)));

}

StarWidget::~StarWidget()
{

}

int StarWidget::maxSize() const
{
  return mMaxSize->value();
}

int StarWidget::responseThreshold() const
{
  return mResponseThreshold->value();
}

int StarWidget::lineThresholdProjected() const
{
  return mLineThresholdProjected->value();
}

int StarWidget::lineThresholdBinarized() const
{
  return mLineThresholdBinarized->value();
}

int StarWidget::suppressNonmaxSize() const
{
  return mSuppressNonmaxSize->value();
}

void StarWidget::setMaxSize(int maxSize)
{
  const QSignalBlocker blockerMaxSize(mMaxSize);
  mMaxSize->setValue(maxSize);
}

void StarWidget::setResponseThreshold(int responseThreshold)
{
  const QSignalBlocker blockerResponseThreshold(mResponseThreshold);
  mResponseThreshold->setValue(responseThreshold);
}

void StarWidget::setLineThresholdProjected(int lineThresholdProjected)
{
  const QSignalBlocker blockerLineThresholdProjected(mLineThresholdProjected);
  mLineThresholdProjected->setValue(lineThresholdProjected);
}

void StarWidget::setLineThresholdBinarized(int lineThresholdBinarized)
{
  const QSignalBlocker blockerLineThresholdBinarized(mLineThresholdBinarized);
  mLineThresholdBinarized->setValue(lineThresholdBinarized);
}

void StarWidget::setSuppressNonmaxSize(int suppressNonmaxSize)
{
  const QSignalBlocker blockerSuppressNonmaxSize(mSuppressNonmaxSize);
  mSuppressNonmaxSize->setValue(suppressNonmaxSize);
}

void StarWidget::update()
{
}

void StarWidget::retranslate()
{

}

void StarWidget::reset()
{
  const QSignalBlocker blockerMaxSize(mMaxSize);
  const QSignalBlocker blockerResponseThreshold(mResponseThreshold);
  const QSignalBlocker blockerLineThresholdProjected(mLineThresholdProjected);
  const QSignalBlocker blockerLineThresholdBinarized(mLineThresholdBinarized);
  const QSignalBlocker blockerSuppressNonmaxSize(mSuppressNonmaxSize);

  mMaxSize->setValue(45);
  mResponseThreshold->setValue(30);
  mLineThresholdProjected->setValue(10);
  mLineThresholdBinarized->setValue(8);
  mSuppressNonmaxSize->setValue(5);
}

void StarWidget::init()
{
  this->setWindowTitle("STAR");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("STAR Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Max Size:")), 0, 0);
  mMaxSize->setRange(0, 100);
  propertiesLayout->addWidget(mMaxSize, 0, 1);

  propertiesLayout->addWidget(new QLabel(tr("Response Threshold:")), 1, 0);
  mResponseThreshold->setRange(0, 100);
  propertiesLayout->addWidget(mResponseThreshold, 1, 1);

  propertiesLayout->addWidget(new QLabel(tr("Line Threshold Projected:")), 2, 0);
  mLineThresholdProjected->setRange(0, 100);
  propertiesLayout->addWidget(mLineThresholdProjected, 2, 1);

  propertiesLayout->addWidget(new QLabel(tr("Line Threshold Binarized:")), 3, 0);
  mLineThresholdBinarized->setRange(0, 100);
  propertiesLayout->addWidget(mLineThresholdBinarized, 3, 1);

  propertiesLayout->addWidget(new QLabel(tr("Suppress Nonmax Size:")), 4, 0);
  mSuppressNonmaxSize->setRange(0, 100);
  propertiesLayout->addWidget(mSuppressNonmaxSize, 4, 1);

  reset();
  update();
}

} // namespace photomatch



