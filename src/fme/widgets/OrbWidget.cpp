#include "OrbWidget.h"

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

OrbWidget::OrbWidget(QWidget *parent)
  : IOrbWidget(parent),
    mFeaturesNumber(new QSpinBox(this)),
    mScaleFactor(new QDoubleSpinBox(this)),
    mLevelsNumber(new QSpinBox(this)),
    mEdgeThreshold(new QSpinBox(this)),
    //mFirstLevel(new QSpinBox(this)),
    mWTA_K(new QSpinBox(this)),
    mScoreType(new QComboBox(this)),
    mPatchSize(new QSpinBox(this)),
    mFastThreshold(new QSpinBox(this))
{
  init();

  /// Signals and slots

  connect(mFeaturesNumber, SIGNAL(valueChanged(int)),           this, SIGNAL(featuresNumberChange(int)));
  connect(mScaleFactor,    SIGNAL(valueChanged(double)),        this, SIGNAL(scaleFactorChange(double)));
  connect(mLevelsNumber,   SIGNAL(valueChanged(int)),           this, SIGNAL(levelsNumberChange(int)));
  connect(mEdgeThreshold,  SIGNAL(valueChanged(int)),           this, SIGNAL(edgeThresholdChange(int)));
  connect(mWTA_K,          SIGNAL(valueChanged(int)),           this, SIGNAL(wta_kChange(int)));
  connect(mScoreType,      SIGNAL(currentTextChanged(QString)), this, SIGNAL(scoreTypeChange(QString)));
  connect(mPatchSize,      SIGNAL(valueChanged(int)),           this, SIGNAL(patchSizeChange(int)));
  connect(mFastThreshold,  SIGNAL(valueChanged(int)),           this, SIGNAL(fastThresholdChange(int)));

}

OrbWidget::~OrbWidget()
{

}

/// private:

void OrbWidget::init()
{
  this->setWindowTitle("ORB");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("ORB Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout(this);
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Features Number:")), 0, 0);
  mFeaturesNumber->setRange(0, 50000);
  propertiesLayout->addWidget(mFeaturesNumber, 0, 1);

  propertiesLayout->addWidget(new QLabel(tr("Scale Factor:")), 1, 0);
  mScaleFactor->setRange(1., 100.);
  mScaleFactor->setSingleStep(0.1);
  propertiesLayout->addWidget(mScaleFactor, 1, 1);

  propertiesLayout->addWidget(new QLabel(tr("Levels Number:")), 2, 0);
  mLevelsNumber->setRange(0, 100);
  propertiesLayout->addWidget(mLevelsNumber, 2, 1);

  propertiesLayout->addWidget(new QLabel(tr("Edge Threshold:")), 3, 0);
  mEdgeThreshold->setRange(0, 100);
  propertiesLayout->addWidget(mEdgeThreshold, 3, 1);

  /// OpenCV -> It should be 0 in the current implementation
  //mFirstLevel->setValue(0);

  propertiesLayout->addWidget(new QLabel(tr("WTA_K:")), 4, 0);
  mWTA_K->setRange(2, 4);
  propertiesLayout->addWidget(mWTA_K, 4, 1);

  propertiesLayout->addWidget(new QLabel(tr("Score Type:")), 5, 0);
  mScoreType->addItem("Harris");
  mScoreType->addItem("FAST");
  propertiesLayout->addWidget(mScoreType, 5, 1);

  propertiesLayout->addWidget(new QLabel(tr("Patch Size:")), 6, 0);
  mPatchSize->setRange(0, 100);
  propertiesLayout->addWidget(mPatchSize, 6, 1);

  propertiesLayout->addWidget(new QLabel(tr("Fast Threshold:")), 7, 0);
  mFastThreshold->setRange(0, 100);
  propertiesLayout->addWidget(mFastThreshold, 7, 1);

  reset(); /// set default values

  update();
}

int OrbWidget::featuresNumber() const
{
  return mFeaturesNumber->value();
}

double OrbWidget::scaleFactor() const
{
  return mScaleFactor->value();
}

int OrbWidget::levelsNumber() const
{
  return mLevelsNumber->value();
}

int OrbWidget::edgeThreshold() const
{
  return mEdgeThreshold->value();
}

int OrbWidget::wta_k() const
{
  return mWTA_K->value();
}

QString OrbWidget::scoreType() const
{
  return mScoreType->currentText();
}

int OrbWidget::patchSize() const
{
  return mPatchSize->value();
}

int OrbWidget::fastThreshold() const
{
  return mFastThreshold->value();
}

void OrbWidget::setFeaturesNumber(int featuresNumber)
{
  const QSignalBlocker blockerFeaturesNumber(mFeaturesNumber);
  mFeaturesNumber->setValue(featuresNumber);
}

void OrbWidget::setScaleFactor(double scaleFactor)
{
  const QSignalBlocker blockerScaleFactor(mScaleFactor);
  mScaleFactor->setValue(scaleFactor);
}

void OrbWidget::setLevelsNumber(int levelsNumber)
{
  const QSignalBlocker blockerLevelsNumber(mLevelsNumber);
  mLevelsNumber->setValue(levelsNumber);
}

void OrbWidget::setEdgeThreshold(int edgeThreshold)
{
  const QSignalBlocker blockerEdgeThreshold(mEdgeThreshold);
  mEdgeThreshold->setValue(edgeThreshold);
}

void OrbWidget::setWTA_K(int WTA_K)
{
  const QSignalBlocker blockerWTA_K(mWTA_K);
  mWTA_K->setValue(WTA_K);
}

void OrbWidget::setScoreType(const QString &scoreType)
{
  const QSignalBlocker blockerScoreType(mScoreType);
  mScoreType->setCurrentText(scoreType);
}

void OrbWidget::setPatchSize(int patchSize)
{
  const QSignalBlocker blockerPatchSize(mPatchSize);
  mPatchSize->setValue(patchSize);
}

void OrbWidget::setFastThreshold(int fastThreshold)
{
  const QSignalBlocker blockerFastThreshold(mFastThreshold);
  mFastThreshold->setValue(fastThreshold);
}

void OrbWidget::update()
{
}

void OrbWidget::reset()
{
  const QSignalBlocker blockerFeaturesNumber(mFeaturesNumber);
  const QSignalBlocker blockerScaleFactor(mScaleFactor);
  const QSignalBlocker blockerLevelsNumber(mLevelsNumber);
  const QSignalBlocker blockerEdgeThreshold(mEdgeThreshold);
  const QSignalBlocker blockerWTA_K(mWTA_K);
  const QSignalBlocker blockerScoreType(mScoreType);
  const QSignalBlocker blockerPatchSize(mPatchSize);
  const QSignalBlocker blockerFastThreshold(mFastThreshold);

  mFeaturesNumber->setValue(5000);  // OpenCV default value = 500
  mScaleFactor->setValue(1.2);      // OpenCV default value  = 1.2f
  mLevelsNumber->setValue(8);       // OpenCV default value  = 8
  mEdgeThreshold->setValue(31);     // OpenCV default value  = 31
  mWTA_K->setValue(2);              // OpenCV default value  = 2
  mScoreType->setCurrentText("Harris");
  mPatchSize->setValue(31);          // OpenCV default value  = 31
  mFastThreshold->setValue(20);
}

} // namespace fme
