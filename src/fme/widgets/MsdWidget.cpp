#include "MsdWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>

namespace fme
{

MsdWidget::MsdWidget(QWidget *parent)
  : IMsdWidget(parent),
    mThresholdSaliency(new QDoubleSpinBox(this)),
    mPathRadius(new QSpinBox(this)),
    mKNN(new QSpinBox(this)),
    mAreaRadius(new QSpinBox(this)),
    mScaleFactor(new QDoubleSpinBox(this)),
    mNMSRadius(new QSpinBox(this)),
    mNScales(new QSpinBox(this)),
    mNMSScaleR(new QSpinBox(this)),
    mComputeOrientations(new QCheckBox(this)),
    mAffineMSD(new QCheckBox(this)),
    mTilts(new QSpinBox(this))
{
  init();

  connect(mThresholdSaliency,   SIGNAL(valueChanged(double)),  this, SIGNAL(thresholdSaliencyChange(double)));
  connect(mPathRadius,          SIGNAL(valueChanged(int)),     this, SIGNAL(pathRadiusChange(int)));
  connect(mKNN,                 SIGNAL(valueChanged(int)),     this, SIGNAL(KNNChange(int)));
  connect(mAreaRadius,          SIGNAL(valueChanged(int)),     this, SIGNAL(areaRadiusChange(int)));
  connect(mScaleFactor,         SIGNAL(valueChanged(double)),  this, SIGNAL(scaleFactorChange(double)));
  connect(mNMSRadius,           SIGNAL(valueChanged(int)),     this, SIGNAL(NMSRadiusChange(int)));
  connect(mNScales,             SIGNAL(valueChanged(int)),     this, SIGNAL(nScalesChange(int)));
  connect(mNMSScaleR,           SIGNAL(valueChanged(int)),     this, SIGNAL(NMSScaleRChange(int)));
  connect(mComputeOrientations, SIGNAL(clicked(bool)),         this, SIGNAL(computeOrientationsChange(bool)));
  connect(mAffineMSD,           SIGNAL(clicked(bool)),         this, SIGNAL(affineMSDChange(bool)));
  connect(mTilts,               SIGNAL(valueChanged(int)),     this, SIGNAL(tiltsChange(int)));

}

MsdWidget::~MsdWidget()
{
}

double MsdWidget::thresholdSaliency() const
{
  return  mThresholdSaliency->value();
}

int MsdWidget::pathRadius() const
{
  return mPathRadius->value();
}

int MsdWidget::knn() const
{
  return mKNN->value();
}

int MsdWidget::areaRadius() const
{
  return mAreaRadius->value();
}

double MsdWidget::scaleFactor() const
{
  return mScaleFactor->value();
}

int MsdWidget::NMSRadius() const
{
  return mNMSRadius->value();
}

int MsdWidget::nScales() const
{
  return mNScales->value();
}

int MsdWidget::NMSScaleR() const
{
  return mNMSScaleR->value();
}

bool MsdWidget::computeOrientations() const
{
  return mComputeOrientations->isChecked();
}

bool MsdWidget::affineMSD() const
{
  return mAffineMSD->isChecked();
}

int MsdWidget::tilts() const
{
  return mTilts->value();
}

void MsdWidget::setThresholdSaliency(double thresholdSaliency)
{
  const QSignalBlocker blocker(mThresholdSaliency);
  mThresholdSaliency->setValue(thresholdSaliency);
}

void MsdWidget::setPatchRadius(int pathRadius)
{
  const QSignalBlocker blocker(mPathRadius);
  mPathRadius->setValue(pathRadius);
}

void MsdWidget::setKNN(int knn)
{
  const QSignalBlocker blocker(mKNN);
  mKNN->setValue(knn);
}

void MsdWidget::setAreaRadius(int areaRadius)
{
  const QSignalBlocker blocker(mAreaRadius);
  mAreaRadius->setValue(areaRadius);
}

void MsdWidget::setScaleFactor(double scaleFactor)
{
  const QSignalBlocker blocker(mScaleFactor);
  mScaleFactor->setValue(scaleFactor);
}

void MsdWidget::setNMSRadius(int NMSRadius)
{
  const QSignalBlocker blocker(mNMSRadius);
  mNMSRadius->setValue(NMSRadius);
}

void MsdWidget::setNScales(int nScales)
{
  const QSignalBlocker blocker(mNScales);
  mNScales->setValue(nScales);
}

void MsdWidget::setNMSScaleR(int NMSScaleR)
{
  const QSignalBlocker blocker(mNMSScaleR);
  mNMSScaleR->setValue(NMSScaleR);
}

void MsdWidget::setComputeOrientations(bool computeOrientations)
{
  mComputeOrientations->setChecked(computeOrientations);
}

void MsdWidget::setAffineMSD(bool affineMSD)
{
  mAffineMSD->setChecked(affineMSD);
}

void MsdWidget::setTilts(int tilts)
{
  const QSignalBlocker blocker(mTilts);
  mTilts->setValue(tilts);
}

void MsdWidget::update()
{
}

void MsdWidget::reset()
{
  const QSignalBlocker blocker1(mThresholdSaliency);
  const QSignalBlocker blocker2(mPathRadius);
  const QSignalBlocker blocker3(mKNN);
  const QSignalBlocker blocker4(mAreaRadius);
  const QSignalBlocker blocker5(mScaleFactor);
  const QSignalBlocker blocker6(mNMSRadius);
  const QSignalBlocker blocker7(mNScales);
  const QSignalBlocker blocker8(mNMSScaleR);
  const QSignalBlocker blocker9(mTilts);

  mThresholdSaliency->setValue(250);
  mPathRadius->setValue(3);
  mKNN->setValue(4);
  mAreaRadius->setValue(5);
  mScaleFactor->setValue(1.25);
  mNMSRadius->setValue(5);
  mNScales->setValue(-1);
  mNMSScaleR->setValue(0);
  mComputeOrientations->setChecked(false);
  mAffineMSD->setChecked(false);
  mTilts->setValue(3);
}

void MsdWidget::init()
{
  this->setWindowTitle("MSD");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("MSD Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Threshold Saliency:")), 0, 0, 1, 2);
  mThresholdSaliency->setRange(0, 2000);
  mThresholdSaliency->setSingleStep(1);
  propertiesLayout->addWidget(mThresholdSaliency, 0, 2, 1, 2);

  propertiesLayout->addWidget(new QLabel(tr("Path radius:")), 1, 0);
  mPathRadius->setRange(1, 10);
  mPathRadius->setSingleStep(1);
  propertiesLayout->addWidget(mPathRadius, 1, 1);

  propertiesLayout->addWidget(new QLabel(tr("KNN:")), 1, 2);
  mKNN->setRange(1,10);
  mKNN->setSingleStep(1);
  propertiesLayout->addWidget(mKNN, 1, 3);

  propertiesLayout->addWidget(new QLabel(tr("Area radius:")), 2, 0);
  mAreaRadius->setRange(1, 10);
  mAreaRadius->setSingleStep(1);
  propertiesLayout->addWidget(mAreaRadius, 2, 1);

  propertiesLayout->addWidget(new QLabel(tr("Scale factor:")), 2, 2);
  mScaleFactor->setRange(1, 10);
  mScaleFactor->setSingleStep(0.05);
  propertiesLayout->addWidget(mScaleFactor, 2, 3);

  propertiesLayout->addWidget(new QLabel(tr("NMS radius:")), 3, 0);
  mNMSRadius->setRange(1, 10);
  mNMSRadius->setSingleStep(1);
  propertiesLayout->addWidget(mNMSRadius, 3, 1);

  propertiesLayout->addWidget(new QLabel(tr("N Scales:")), 3, 2);
  mNScales->setRange(-1, 10);
  mNScales->setSingleStep(1);
  propertiesLayout->addWidget(mNScales, 3, 3);

  propertiesLayout->addWidget(new QLabel(tr("NMS Scale R.:")), 4, 0);
  mNMSScaleR->setRange(0, 10);
  mNMSScaleR->setSingleStep(1);
  propertiesLayout->addWidget(mNMSScaleR, 4, 1);

  mComputeOrientations->setText(tr("Compute orientations"));
  propertiesLayout->addWidget(mComputeOrientations, 4, 2, 1, 2); //Check orientations

  mAffineMSD->setText(tr("Affine MSD"));
  propertiesLayout->addWidget(mAffineMSD, 5, 0, 1, 2); //CheckAffine

  propertiesLayout->addWidget(new QLabel(tr("Tilts:")), 5, 2);
  mTilts->setRange(3,10);
  mTilts->setSingleStep(1);
  propertiesLayout->addWidget(mTilts, 5, 3);

  reset();

  update();
}


} // namespace fme
