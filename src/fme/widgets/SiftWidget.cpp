#include "SiftWidget.h"

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

SiftWidget::SiftWidget(QWidget *parent)
  : ISiftWidget(parent),
    mFeaturesNumber(new QSpinBox(this)),
    mOctaveLayers(new QSpinBox(this)),
    mContrastThreshold(new QDoubleSpinBox(this)),
    mEdgeThreshold(new QDoubleSpinBox(this)),
    mSigma(new QDoubleSpinBox(this))
{
  init();

  /// Signals and slots

  connect(mFeaturesNumber,    SIGNAL(valueChanged(int)),    this, SIGNAL(featuresNumberChange(int)));
  connect(mOctaveLayers,      SIGNAL(valueChanged(int)),    this, SIGNAL(octaveLayersChange(int)));
  connect(mContrastThreshold, SIGNAL(valueChanged(double)), this, SIGNAL(contrastThresholdChange(double)));
  connect(mEdgeThreshold,     SIGNAL(valueChanged(double)), this, SIGNAL(edgeThresholdChange(double)));
  connect(mSigma,             SIGNAL(valueChanged(double)), this, SIGNAL(sigmaChange(double)));

}

SiftWidget::~SiftWidget()
{

}

int SiftWidget::featuresNumber() const
{
  return mFeaturesNumber->value();
}

int SiftWidget::octaveLayers() const
{
  return mOctaveLayers->value();
}

double SiftWidget::contrastThreshold()
{
  return mContrastThreshold->value();
}

double SiftWidget::edgeThreshold()
{
  return mEdgeThreshold->value();
}

double SiftWidget::sigma()
{
  return mSigma->value();
}

void SiftWidget::setFeaturesNumber(int featuresNumber)
{
  const QSignalBlocker blockerFeaturesNumber(mFeaturesNumber);
  mFeaturesNumber->setValue(featuresNumber);
}

void SiftWidget::setOctaveLayers(int octaveLayers)
{
  const QSignalBlocker blockerFeaturesNumber(mOctaveLayers);
  mOctaveLayers->setValue(octaveLayers);
}

void SiftWidget::setContrastThreshold(double contrastThreshold)
{
  const QSignalBlocker blockerContrastThreshold(mContrastThreshold);
  mContrastThreshold->setValue(contrastThreshold);
}

void SiftWidget::setEdgeThreshold(double edgeThreshold)
{
  const QSignalBlocker blockerEdgeThreshold(mEdgeThreshold);
  mEdgeThreshold->setValue(edgeThreshold);
}

void SiftWidget::setSigma(double sigma)
{
  const QSignalBlocker blockerSigma(mSigma);
  mSigma->setValue(sigma);
}

void SiftWidget::update()
{

}

void SiftWidget::reset()
{
  const QSignalBlocker blockerFeaturesNumber(mFeaturesNumber);
  const QSignalBlocker blockerOctaveLayers(mOctaveLayers);
  const QSignalBlocker blockerContrastThreshold(mContrastThreshold);
  const QSignalBlocker blockerEdgeThreshold(mEdgeThreshold);
  const QSignalBlocker blockerSigma(mSigma);

  mFeaturesNumber->setValue(5000);     // OpenCV default value = 0
  mOctaveLayers->setValue(3);          // OpenCV default value = 3
  mContrastThreshold->setValue(0.04);  // OpenCV default value = 0.04
  mEdgeThreshold->setValue(10.);
  mSigma->setValue(1.6);
}

void SiftWidget::init()
{
  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("SIFT Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout(this);
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Features Number:")), 0, 0);
  mFeaturesNumber->setRange(0, 50000);
  propertiesLayout->addWidget(mFeaturesNumber, 0, 1);

  propertiesLayout->addWidget(new QLabel(tr("Octave Layers:")), 1, 0);
  mOctaveLayers->setRange(0, 10);
  propertiesLayout->addWidget(mOctaveLayers, 1, 1);

  propertiesLayout->addWidget(new QLabel(tr("Contrast Threshold:")), 2, 0);
  mContrastThreshold->setRange(0., 10.);  //TODO: ver que el rango tenga sentido
  mContrastThreshold->setDecimals(3);
  mContrastThreshold->setSingleStep(0.01);
  propertiesLayout->addWidget(mContrastThreshold, 2, 1);

  propertiesLayout->addWidget(new QLabel(tr("Edge Threshold:")), 3, 0);
  mEdgeThreshold->setRange(0., 100.);
  propertiesLayout->addWidget(mEdgeThreshold, 3, 1);

  propertiesLayout->addWidget(new QLabel(tr("Sigma:")), 4, 0);
  mSigma->setRange(0., 100.);
  mSigma->setSingleStep(0.1);
  propertiesLayout->addWidget(mSigma, 4, 1);

  reset(); /// set default values

  update();
}


} // namespace fme
