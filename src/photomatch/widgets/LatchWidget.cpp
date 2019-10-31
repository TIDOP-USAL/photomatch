#include "LatchWidget.h"

#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

LatchWidget::LatchWidget(QWidget *parent)
  : ILatchWidget(parent),
    mBytes(new QComboBox(this)),
    mRotationInvariance(new QCheckBox(this)),
    mHalfSsdSize(new QSpinBox(this))
{
  init();

  /// Signals and slots
  connect(mBytes,               SIGNAL(currentTextChanged(QString)),  this, SIGNAL(bytesChange(QString)));
  connect(mRotationInvariance,  SIGNAL(clicked(bool)),                this, SIGNAL(rotationInvarianceChange(bool)));
  connect(mHalfSsdSize,         SIGNAL(valueChanged(int)),            this, SIGNAL(halfSsdSizeChange(int)));

}

LatchWidget::~LatchWidget()
{

}

QString LatchWidget::bytes() const
{
  return mBytes->currentText();
}

bool LatchWidget::rotationInvariance() const
{
  return mRotationInvariance->isChecked();
}

int LatchWidget::halfSsdSize() const
{
  return mHalfSsdSize->value();
}

void LatchWidget::setBytes(const QString &bytes)
{
  const QSignalBlocker blockerBytes(mBytes);
  mBytes->setCurrentText(bytes);
}

void LatchWidget::setRotationInvariance(bool rotationInvariance)
{
  mRotationInvariance->setChecked(rotationInvariance);
}

void LatchWidget::setHalfSsdSize(int halfSsdSize)
{
  const QSignalBlocker blockerHalfSsdSize(mHalfSsdSize);
  mHalfSsdSize->setValue(halfSsdSize);
}

void LatchWidget::update()
{
}

void LatchWidget::reset()
{
  const QSignalBlocker blockerBytes(mBytes);
  const QSignalBlocker blockerHalfSsdSize(mHalfSsdSize);

  mBytes->setCurrentText("32");
  mRotationInvariance->setChecked(true);
  mHalfSsdSize->setValue(3);
}

void LatchWidget::init()
{
  this->setWindowTitle("LATCH");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("LATCH Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Descriptor Bytes:")), 0, 0);
  mBytes->addItem("1");
  mBytes->addItem("2");
  mBytes->addItem("4");
  mBytes->addItem("8");
  mBytes->addItem("16");
  mBytes->addItem("32");
  mBytes->addItem("64");
  propertiesLayout->addWidget(mBytes, 0, 1);

  mRotationInvariance->setText(tr("Rotation Invariance"));
  propertiesLayout->addWidget(mRotationInvariance, 1, 0);

  propertiesLayout->addWidget(new QLabel(tr("Half of the mini-patches size:")), 2, 0);
  mHalfSsdSize->setRange(0, 100);
  propertiesLayout->addWidget(mHalfSsdSize, 2, 1);

  reset();

  update();
}

} // namespace photomatch


