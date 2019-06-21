#include "DescriptorMatcherWidget.h"

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QCheckBox>

namespace fme
{

DescriptorMatcherWidget::DescriptorMatcherWidget(QWidget *parent)
  : IDescriptorMatcherWidget(parent),
    mMatchingMethod(new QComboBox(this)),
    mNormType(new QComboBox(this)),
    mRatio(new QDoubleSpinBox(this)),
    mDistance(new QDoubleSpinBox(this)),
    mConfidence(new QDoubleSpinBox(this)),
    mCrossMatching(new QCheckBox(this))
{
  init();

  /// Signals and slots
  connect(mMatchingMethod,       SIGNAL(currentTextChanged(QString)),  this, SIGNAL(matchingMethodChange(QString)));
  connect(mNormType,             SIGNAL(currentTextChanged(QString)),  this, SIGNAL(normTypeChange(QString)));
  connect(mRatio,                SIGNAL(valueChanged(double)),         this, SIGNAL(ratioChange(double)));
  connect(mDistance,             SIGNAL(valueChanged(double)),         this, SIGNAL(distanceChange(double)));
  connect(mConfidence,           SIGNAL(valueChanged(double)),         this, SIGNAL(confidenceChange(double)));
  connect(mCrossMatching,        SIGNAL(clicked(bool)),                this, SIGNAL(crossMatchingChange(bool)));

  connect(this, SIGNAL(matchingMethodChange(QString)), this, SLOT(onMatchingMethodChanged(QString)));
}

DescriptorMatcherWidget::~DescriptorMatcherWidget()
{

}

QString DescriptorMatcherWidget::matchingMethod() const
{
  return mMatchingMethod->currentText();
}

QString DescriptorMatcherWidget::normType() const
{
  return mNormType->currentText();
}

double DescriptorMatcherWidget::ratio() const
{
  return mRatio->value();
}

double DescriptorMatcherWidget::distance() const
{
  return mDistance->value();
}

double DescriptorMatcherWidget::confidence() const
{
  return mConfidence->value();
}

bool DescriptorMatcherWidget::crossMatching() const
{
  return mCrossMatching->isChecked();
}

void DescriptorMatcherWidget::setMatchingMethod(const QString &matchingMethod)
{
  const QSignalBlocker blockerMatchingMethod(mMatchingMethod);
  mMatchingMethod->setCurrentText(matchingMethod);
  onMatchingMethodChanged(matchingMethod);
}

void DescriptorMatcherWidget::setNormType(const QString &normType)
{
  const QSignalBlocker blockerNormType(mNormType);
  mNormType->setCurrentText(normType);
}

void DescriptorMatcherWidget::setRatio(double ratio)
{
  const QSignalBlocker blockerRatio(mRatio);
  mRatio->setValue(ratio);
}

void DescriptorMatcherWidget::setDistance(double distance)
{
  const QSignalBlocker blockerDistance(mDistance);
  mDistance->setValue(distance);
}

void DescriptorMatcherWidget::setConfidence(double confidence)
{
  const QSignalBlocker blockerConfidence(mConfidence);
  mConfidence->setValue(confidence);
}

void DescriptorMatcherWidget::setCrossMatching(bool crossMatching)
{
  mCrossMatching->setChecked(crossMatching);
}

void DescriptorMatcherWidget::update()
{
}

void DescriptorMatcherWidget::reset()
{
  const QSignalBlocker blockerMatchingMethod(mMatchingMethod);
  const QSignalBlocker blockerNormType(mNormType);
  const QSignalBlocker blockerRatio(mRatio);
  const QSignalBlocker blockerDistance(mDistance);
  const QSignalBlocker blockerConfidence(mConfidence);

  mMatchingMethod->setCurrentText("Brute-Force");
  mNormType->setCurrentText("NORM_L1");
  mRatio->setValue(0.8);
  mDistance->setValue(0.7);
  mConfidence->setValue(0.999);
  mCrossMatching->setChecked(true);
}

void DescriptorMatcherWidget::init()
{
  this->setWindowTitle("Descriptor Matcher");

  QGridLayout *layout = new QGridLayout();

  layout->addWidget(new QLabel(tr("Matching Method:")), 0, 0);
  mMatchingMethod->addItem("Brute-Force");
  mMatchingMethod->addItem("FLANN");
  layout->addWidget(mMatchingMethod, 0, 1);

  mNormTypeLabel = new QLabel(tr("Norm Type:"));
  layout->addWidget(mNormTypeLabel, 1, 0);
  mNormType->addItem("NORM_L1");
  mNormType->addItem("NORM_L2");
  mNormType->addItem("NORM_HAMMING");
  mNormType->addItem("NORM_HAMMING2");
  layout->addWidget(mNormType, 1, 1);

  layout->addWidget(new QLabel(tr("Ratio:")), 2, 0);
  mRatio->setDecimals(3);
  mRatio->setRange(0.001, 100.);
  mRatio->setSingleStep(0.1);
  layout->addWidget(mRatio, 2, 1);

  layout->addWidget(new QLabel(tr("Distance:")), 3, 0);
  mDistance->setRange(0.001, 100.);
  mDistance->setDecimals(3);
  mDistance->setSingleStep(0.1);
  layout->addWidget(mDistance, 3, 1);

  layout->addWidget(new QLabel(tr("Confidence:")), 4, 0);
  mConfidence->setRange(0., 1.);
  mConfidence->setDecimals(3);
  mConfidence->setSingleStep(0.001);
  layout->addWidget(mConfidence, 4, 1);

  mCrossMatching->setText(tr("Cross Matching"));
  layout->addWidget(mCrossMatching, 5, 0);

  this->setLayout(layout);

  reset(); /// set default values

  update();
}

void DescriptorMatcherWidget::onMatchingMethodChanged(const QString &method)
{
  if (method.compare("FLANN") == 0){
    mNormTypeLabel->hide();
    mNormType->hide();
  } else {
    mNormTypeLabel->show();
    mNormType->show();
  }
}


} // namespace fme
