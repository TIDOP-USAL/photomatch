#include "KazeWidget.h"

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>

namespace fme
{

KazeWidget::KazeWidget(QWidget *parent)
  : IKazeWidget(parent),
    mExtended(new QCheckBox(this)),
    mUpright(new QCheckBox(this)),
    mThreshold(new QDoubleSpinBox(this)),
    mOctaves(new QSpinBox(this)),
    mOctaveLayers(new QSpinBox(this)),
    mDiffusivity(new QComboBox(this))
{
  init();

  /// Signals and slots
  connect(mExtended,     SIGNAL(clicked(bool)),               this, SIGNAL(extendedDescriptorChange(bool)));
  connect(mUpright,      SIGNAL(clicked(bool)),               this, SIGNAL(uprightChange(bool)));
  connect(mThreshold,    SIGNAL(valueChanged(double)),        this, SIGNAL(thresholdChange(double)));
  connect(mOctaves,      SIGNAL(valueChanged(int)),           this, SIGNAL(octavesChange(int)));
  connect(mOctaveLayers, SIGNAL(valueChanged(int)),           this, SIGNAL(octaveLayersChange(int)));
  connect(mDiffusivity,  SIGNAL(currentTextChanged(QString)), this, SIGNAL(diffusivityChange(QString)));

}

KazeWidget::~KazeWidget()
{
}

bool KazeWidget::extendedDescriptor() const
{
  return mExtended->isChecked();
}

bool KazeWidget::upright() const
{
  return mUpright->isChecked();
}

double KazeWidget::threshold() const
{
  return mThreshold->value();
}

int KazeWidget::octaves() const
{
  return mOctaves->value();
}

int KazeWidget::octaveLayers() const
{
  return mOctaveLayers->value();
}

QString KazeWidget::diffusivity() const
{
  return mDiffusivity->currentText();
}

void KazeWidget::setExtendedDescriptor(bool extended)
{
  mExtended->setChecked(extended);
}

void KazeWidget::setUpright(bool upright)
{
  mUpright->setChecked(upright);
}

void KazeWidget::setThreshold(double threshold)
{
  const QSignalBlocker blockerHessianThreshold(mThreshold);
  mThreshold->setValue(threshold);
}

void KazeWidget::setOctaves(int octaves)
{
  const QSignalBlocker blockerOctaves(mOctaves);
  mOctaves->setValue(octaves);
}

void KazeWidget::setOctaveLayers(int octaveLayers)
{
  const QSignalBlocker blockerOctaveLayers(mOctaveLayers);
  mOctaveLayers->setValue(octaveLayers);
}

void KazeWidget::setDiffusivity(const QString &diffusivity)
{
  const QSignalBlocker blockerDiffusivity(mDiffusivity);
  mDiffusivity->setCurrentText(diffusivity);
}

void KazeWidget::update()
{
}

void KazeWidget::reset()
{
  const QSignalBlocker blockerHessianThreshold(mThreshold);
  const QSignalBlocker blockerOctaves(mOctaves);
  const QSignalBlocker blockerOctaveLayers(mOctaveLayers);
  const QSignalBlocker blockerDiffusivity(mDiffusivity);

  mExtended->setChecked(false);
  mUpright->setChecked(false);
  mThreshold->setValue(0.001);
  mOctaves->setValue(4);
  mOctaveLayers->setValue(4);
  mDiffusivity->setCurrentText("DIFF_PM_G2");
}

void KazeWidget::init()
{
  QGridLayout *layout = new QGridLayout();

  //layout->addWidget(new QLabel(tr("Extended:")), 0, 0);
  mExtended->setText(tr("Extended"));
  layout->addWidget(mExtended, 0, 0);

  //layout->addWidget(new QLabel(tr("Upright:")), 1, 0);
  mUpright->setText(tr("Upright"));
  layout->addWidget(mUpright, 1, 0);

  layout->addWidget(new QLabel(tr("Threshold:")), 2, 0);
  mThreshold->setDecimals(3);
  mThreshold->setRange(0, 99.99);
  layout->addWidget(mThreshold, 2, 1);

  layout->addWidget(new QLabel(tr("Octaves:")), 3, 0);
  mOctaves->setRange(0, 100);
  layout->addWidget(mOctaves, 3, 1);

  layout->addWidget(new QLabel(tr("Octave Layers:")), 4, 0);
  mOctaveLayers->setRange(0, 100);
  layout->addWidget(mOctaveLayers, 4, 1);

  layout->addWidget(new QLabel(tr("Diffusivity:")), 5, 0);
  mDiffusivity->addItem("DIFF_PM_G1");
  mDiffusivity->addItem("DIFF_PM_G2");
  mDiffusivity->addItem("DIFF_WEICKERT");
  mDiffusivity->addItem("DIFF_CHARBONNIER");
  layout->addWidget(mDiffusivity, 5, 1);

  this->setLayout(layout);

  reset(); /// set default values

  update();
}

} // namespace fme



