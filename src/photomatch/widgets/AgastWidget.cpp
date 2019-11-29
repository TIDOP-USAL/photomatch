#include "AgastWidget.h"

#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

AgastWidget::AgastWidget(QWidget *parent)
  : IAgastWidget(parent),
    mThreshold(new QSpinBox(this)),
    mNonmaxSuppression(new QCheckBox(this)),
    mDetectorType(new QComboBox(this))
{
  init();

  retranslate();

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

void AgastWidget::setDetectorType(const QString &detectorType)
{
  const QSignalBlocker blockerDetectorType(mDetectorType);
  mDetectorType->setCurrentText(detectorType);
}

void AgastWidget::update()
{

}

void AgastWidget::retranslate()
{
#ifndef QT_NO_WHATSTHIS
  mThreshold->setWhatsThis(tr("<html><head/><body><p>The <strong>AST (Accelerated Segment Test)</strong> applies a minimum difference <strong>threshold</strong> when comparing&nbsp;the value of a pixel on the circular pattern with the brightness of the nucleus.&nbsp;This parameter controls the sensitivity of the corner response. A large <strong>threshold</strong>&nbsp;value&nbsp;results in few but therefore only strong corners, while a small <strong>threshold</strong> value yields also&nbsp;corners with smoother gradients.</p></body></html>"));
  mNonmaxSuppression->setWhatsThis(tr("<html><head/><body><p><strong>Non Maximal Suppression</strong> for removing adjacent corners</p></body></html>"));
  mDetectorType->setWhatsThis(tr("<html><head/><body><p>AST (Accelerated Segment Test) decision tree and mask used. Suported types are:</p>"
                                 "<ul>"
                                 "<li><strong>AGAST_5_8</strong>: AGAST-5 decision tree with 8 pixels mask</li>"
                                 "<li><strong>AGAST_7_12d</strong>: AGAST-7 decision tree with Diamond shaped 12 pixels mask</li>"
                                 "<li><strong>AGAST_7_12s</strong>: AGAST-7 decision tree with Squared shaped 12 pixels mask</li>"
                                 "<li><strong>OAST_9_16</strong>: OAST-9 (Optimal AST) decision tree with 16 pixels mask</li>"
                                 "</ul></body></html>"));
#endif // QT_NO_WHATSTHIS
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
  this->setWindowTitle("AGAST");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("AGAST Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Threshold:")), 0, 0);
  mThreshold->setRange(0, 100);
  propertiesLayout->addWidget(mThreshold, 0, 1);

  mNonmaxSuppression->setText(tr("Nonmax Suppression"));
  propertiesLayout->addWidget(mNonmaxSuppression, 1, 0);

  propertiesLayout->addWidget(new QLabel(tr("Detector Type:")), 2, 0);
  mDetectorType->addItem("AGAST_5_8");
  mDetectorType->addItem("AGAST_7_12d");
  mDetectorType->addItem("AGAST_7_12s");
  mDetectorType->addItem("OAST_9_16");
  propertiesLayout->addWidget(mDetectorType, 2, 1);

  reset(); /// set default values

  update();
}

} // namespace photomatch
