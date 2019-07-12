#include "DaisyWidget.h"

#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

DaisyWidget::DaisyWidget(QWidget *parent)
  : IDaisyWidget(parent),
    mRadius(new QDoubleSpinBox(this)),
    mQRadius(new QSpinBox(this)),
    mQTheta(new QSpinBox(this)),
    mQHist(new QSpinBox(this)),
    mNorm(new QComboBox(this)),
    mInterpolation(new QCheckBox(this)),
    mUseOrientation(new QCheckBox(this))
{
  init();

  /// Signals and slots
  connect(mRadius,         SIGNAL(valueChanged(double)),         this, SIGNAL(radiusChange(double)));
  connect(mQRadius,        SIGNAL(valueChanged(int)),            this, SIGNAL(qRadiusChange(int)));
  connect(mQTheta,         SIGNAL(valueChanged(int)),            this, SIGNAL(qThetaChange(int)));
  connect(mQHist,          SIGNAL(valueChanged(int)),            this, SIGNAL(qHistChange(int)));
  connect(mNorm,           SIGNAL(currentTextChanged(QString)),  this, SIGNAL(normChange(QString)));
  connect(mInterpolation,  SIGNAL(clicked(bool)),                this, SIGNAL(interpolationChange(bool)));
  connect(mUseOrientation, SIGNAL(clicked(bool)),                this, SIGNAL(useOrientationChange(bool)));

}

DaisyWidget::~DaisyWidget()
{

}

double DaisyWidget::radius() const
{
  return mRadius->value();
}

int DaisyWidget::qRadius() const
{
  return mQRadius->value();
}

int DaisyWidget::qTheta() const
{
  return mQTheta->value();
}

int DaisyWidget::qHist() const
{
  return mQHist->value();
}

QString DaisyWidget::norm() const
{
  return mNorm->currentText();
}

bool DaisyWidget::interpolation() const
{
  return mInterpolation->isChecked();
}

bool DaisyWidget::useOrientation() const
{
  return mUseOrientation->isChecked();
}

void DaisyWidget::setRadius(double radius)
{
  const QSignalBlocker blockerRadius(mRadius);
  mRadius->setValue(radius);
}

void DaisyWidget::setQRadius(int qRadius)
{
  const QSignalBlocker blockerQRadius(mQRadius);
  mQRadius->setValue(qRadius);
}

void DaisyWidget::setQTheta(int qTheta)
{
  const QSignalBlocker blockerQTheta(mQTheta);
  mQTheta->setValue(qTheta);
}

void DaisyWidget::setQHist(int qHist)
{
  const QSignalBlocker blockerQHist(mQHist);
  mQHist->setValue(qHist);
}

void DaisyWidget::setNorm(const QString &norm)
{
  const QSignalBlocker blockerNorm(mNorm);
  mNorm->setCurrentText(norm);
}

void DaisyWidget::setInterpolation(bool interpolation)
{
  mInterpolation->setChecked(interpolation);
}

void DaisyWidget::setUseOrientation(bool useOrientation)
{
  mUseOrientation->setChecked(useOrientation);
}

void DaisyWidget::update()
{
}

void DaisyWidget::reset()
{
  const QSignalBlocker blockerRadius(mRadius);
  const QSignalBlocker blockerQRadius(mQRadius);
  const QSignalBlocker blockerQTheta(mQTheta);
  const QSignalBlocker blockerQHist(mQHist);
  const QSignalBlocker blockerNorm(mNorm);

  mRadius->setValue(15.);
  mQRadius->setValue(3);
  mQTheta->setValue(8);
  mQHist->setValue(8);
  mNorm->setCurrentText("NRM_NONE");
  mInterpolation->setChecked(true);
  mUseOrientation->setChecked(false);
}

void DaisyWidget::init()
{
  this->setWindowTitle("DAISY");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("DAISY Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Radius:")), 0, 0);
  mRadius->setRange(0., 100.);
  propertiesLayout->addWidget(mRadius, 0, 1);

  propertiesLayout->addWidget(new QLabel(tr("Radial range division quantity:")), 1, 0);
  mQRadius->setRange(1, 100);
  propertiesLayout->addWidget(mQRadius, 1, 1);

  propertiesLayout->addWidget(new QLabel(tr("Angular range division quantity:")), 2, 0);
  mQTheta->setRange(0, 100);
  propertiesLayout->addWidget(mQTheta, 2, 1);

  propertiesLayout->addWidget(new QLabel(tr("Gradient orientations range division quantity:")), 3, 0);
  mQHist->setRange(0, 100);
  propertiesLayout->addWidget(mQHist, 3, 1);

  mInterpolation->setText(tr("Interpolation"));
  propertiesLayout->addWidget(mInterpolation, 4, 0);

  mUseOrientation->setText(tr("Keypoints orientation"));
  propertiesLayout->addWidget(mUseOrientation, 5, 0);

  propertiesLayout->addWidget(new QLabel(tr("Descriptor normalization type:")), 6, 0);
  mNorm->addItem("NRM_NONE");
  mNorm->addItem("NRM_PARTIAL");
  mNorm->addItem("NRM_FULL");
  mNorm->addItem("NRM_SIFT");
  propertiesLayout->addWidget(mNorm, 6, 1);



  reset();

  update();
}

} // namespace fme

