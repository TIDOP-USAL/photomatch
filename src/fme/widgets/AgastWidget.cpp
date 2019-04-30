#include "AgastWidget.h"

#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>

namespace fme
{

AgastWidget::AgastWidget(QWidget *parent)
  : IAgastWidget(parent),
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

AgastWidget::~AgastWidget()
{

}

int AgastWidget::threshold() const
{
  return mThreshold->value();
}

bool AgastWidget::nonmaxSuppression() const
{
  return mNonmaxSuppression->isChecked();
}

QString AgastWidget::detectorType() const
{
  return mDetectorType->currentText();
}

void AgastWidget::setThreshold(int threshold)
{
  const QSignalBlocker blockerFastThreshold(mThreshold);
  mThreshold->setValue(threshold);
}

void AgastWidget::setNonmaxSuppression(bool nonmaxSuppression)
{
  mNonmaxSuppression->setChecked(nonmaxSuppression);
}

void AgastWidget::setDetectorType(QString detectorType)
{
  const QSignalBlocker blockerDetectorType(mDetectorType);
  mDetectorType->setCurrentText(detectorType);
}

void AgastWidget::update()
{

}

void AgastWidget::reset()
{
  const QSignalBlocker blockerFastThreshold(mThreshold);
  const QSignalBlocker blockerDetectorType(mDetectorType);

  mThreshold->setValue(10);
  mNonmaxSuppression->setChecked(true);
  mDetectorType->setCurrentText("OAST_9_16");
}

void AgastWidget::init()
{

  QGridLayout *layout = new QGridLayout();

  layout->addWidget(new QLabel(tr("Threshold:")), 0, 0);
  mThreshold->setRange(0, 100);
  layout->addWidget(mThreshold, 0, 1);

  //layout->addWidget(new QLabel(tr("Nonmax Suppression:")), 1, 0);
  mNonmaxSuppression->setText(tr("Nonmax Suppression"));
  layout->addWidget(mNonmaxSuppression, 1, 0);

  layout->addWidget(new QLabel(tr("Detector Type:")), 2, 0);
  mDetectorType->addItem("AGAST_5_8");
  mDetectorType->addItem("AGAST_7_12d");
  mDetectorType->addItem("AGAST_7_12s");
  mDetectorType->addItem("OAST_9_16");
  layout->addWidget(mDetectorType, 2, 1);

  this->setLayout(layout);

  reset(); /// set default values

  update();
}

} // namespace fme
