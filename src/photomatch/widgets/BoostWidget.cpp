#include "BoostWidget.h"

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QDoubleSpinBox>

namespace photomatch
{

BoostWidget::BoostWidget(QWidget *parent)
  : IBoostWidget(parent),
    mDescriptorType(new QComboBox(this)),
    mUseOrientation(new QCheckBox(this)),
    mScaleFactor(new QDoubleSpinBox(this))
{
  init();

  /// Signals and slots
  connect(mDescriptorType,    SIGNAL(currentTextChanged(QString)),   this, SIGNAL(descriptorTypeChange(QString)));
  connect(mUseOrientation,    SIGNAL(clicked(bool)),                 this, SIGNAL(useOrientationChange(bool)));
  connect(mScaleFactor,       SIGNAL(valueChanged(double)),          this, SIGNAL(scaleFactorChange(double)));
}

BoostWidget::~BoostWidget()
{

}

QString BoostWidget::descriptorType() const
{
  return mDescriptorType->currentText();
}

bool BoostWidget::useOrientation() const
{
  return mUseOrientation->isChecked();
}

double BoostWidget::scaleFactor() const
{
  return mScaleFactor->value();
}

void BoostWidget::setDescriptorType(const QString &descriptorType)
{
  const QSignalBlocker blockerBytes(mDescriptorType);
  mDescriptorType->setCurrentText(descriptorType);
}

void BoostWidget::setUseOrientation(bool useOrientation)
{
  mUseOrientation->setChecked(useOrientation);
}

void BoostWidget::setScaleFactor(double scaleFactor)
{
  const QSignalBlocker blockerScaleFactor(mScaleFactor);
  mScaleFactor->setValue(scaleFactor);
}

void BoostWidget::update()
{
}

void BoostWidget::reset()
{
  const QSignalBlocker blockerBytes(mDescriptorType);
  const QSignalBlocker blockerScaleFactor(mScaleFactor);
  
  mDescriptorType->setCurrentText("BINBOOST_256");
  mUseOrientation->setChecked(true);
  mScaleFactor->setValue(6.25);
}

void BoostWidget::init()
{
  this->setWindowTitle("BOOST");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("BOOST Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Descriptor Type:")), 0, 0);
  mDescriptorType->addItem("BGM");
  mDescriptorType->addItem("BGM_HARD");
  mDescriptorType->addItem("BGM_BILINEAR");
  mDescriptorType->addItem("LBGM");
  mDescriptorType->addItem("BINBOOST_64");
  mDescriptorType->addItem("BINBOOST_128");
  mDescriptorType->addItem("BINBOOST_256");
  propertiesLayout->addWidget(mDescriptorType, 0, 1);

  mUseOrientation->setText(tr("Use Keypoints Orientation"));
  propertiesLayout->addWidget(mUseOrientation, 1, 0);

  //propertiesLayout->addWidget(new QLabel(tr("Scale Factor:")), 2, 0);
  propertiesLayout->addWidget(mScaleFactor, 2, 1);
  mScaleFactor->setVisible(false); ///Se desactiva y se modifica internamente según el detector usado

  reset();

  update();
}

} // namespace photomatch


