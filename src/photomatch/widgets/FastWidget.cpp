#include "FastWidget.h"

#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

FastWidget::FastWidget(QWidget *parent)
  : IFastWidget(parent),
    mThreshold(new QSpinBox(this)),
    mNonmaxSuppression(new QCheckBox(this)),
    mDetectorType(new QComboBox(this))
{
  init();

  /// Signals and slots

  connect(mThreshold,          SIGNAL(valueChanged(int)),            this, SIGNAL(thresholdChange(int)));
  connect(mNonmaxSuppression,  SIGNAL(clicked(bool)),                this, SIGNAL(nonmaxSuppressionChange(bool)));
  connect(mDetectorType,       SIGNAL(currentTextChanged(QString)),  this, SIGNAL(detectorTypeChange(QString)));
}

FastWidget::~FastWidget()
{
}

int FastWidget::threshold() const
{
  return mThreshold->value();
}

bool FastWidget::nonmaxSuppression() const
{
  return mNonmaxSuppression->isChecked();
}

QString FastWidget::detectorType() const
{
  return mDetectorType->currentText();
}

void FastWidget::setThreshold(int threshold)
{
  const QSignalBlocker blockerFastThreshold(mThreshold);
  mThreshold->setValue(threshold);
}

void FastWidget::setNonmaxSuppression(bool nonmaxSuppression)
{
  mNonmaxSuppression->setChecked(nonmaxSuppression);
}

void FastWidget::setDetectorType(QString detectorType)
{
  const QSignalBlocker blockerDetectorType(mDetectorType);
  mDetectorType->setCurrentText(detectorType);
}

void FastWidget::update()
{
}

void FastWidget::reset()
{
  const QSignalBlocker blockerFastThreshold(mThreshold);
  const QSignalBlocker blockerDetectorType(mDetectorType);

  mThreshold->setValue(10);      // OpenCV default value  = 10
  mNonmaxSuppression->setChecked(true);
  mDetectorType->setCurrentText("TYPE_9_16");
}

void FastWidget::init()
{
  this->setWindowTitle("FAST");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("FAST Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Threshold:")), 0, 0);
  mThreshold->setRange(0, 100);
  propertiesLayout->addWidget(mThreshold, 0, 1);

  mNonmaxSuppression->setText(tr("Nonmax Suppression"));
  propertiesLayout->addWidget(mNonmaxSuppression, 1, 0);

  propertiesLayout->addWidget(new QLabel(tr("Detector Type:")), 2, 0);
  mDetectorType->addItem("TYPE_5_8");
  mDetectorType->addItem("TYPE_7_12");
  mDetectorType->addItem("TYPE_9_16");
  propertiesLayout->addWidget(mDetectorType, 2, 1);

  reset(); /// set default values

  update();
}

} // namespace photomatch
