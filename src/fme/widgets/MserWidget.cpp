#include "MserWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

MserWidget::MserWidget(QWidget *parent)
  : IMserWidget (parent),
    mDelta(new QSpinBox(this)),
    mMinArea(new QSpinBox(this)),
    mMaxArea(new QSpinBox(this)),
    mMaxVariation(new QDoubleSpinBox(this)),
    mMinDiversity(new QDoubleSpinBox(this)),
    mMaxEvolution(new QSpinBox(this)),
    mAreaThreshold(new QDoubleSpinBox(this)),
    mMinMargin(new QDoubleSpinBox(this)),
    mEdgeBlurSize(new QSpinBox(this))
{
  init();

  /// Signals and slots
  ///
  connect(mDelta,           SIGNAL(valueChanged(int)),       this, SIGNAL(deltaChange(int)));
  connect(mMinArea,         SIGNAL(valueChanged(int)),       this, SIGNAL(minAreaChange(int)));
  connect(mMaxArea,         SIGNAL(valueChanged(int)),       this, SIGNAL(maxAreaChange(int)));
  connect(mMaxVariation,    SIGNAL(valueChanged(double)),    this, SIGNAL(maxVariationChange(double)));
  connect(mMinDiversity,    SIGNAL(valueChanged(double)),    this, SIGNAL(minDiversityChange(double)));
  connect(mMaxEvolution,    SIGNAL(valueChanged(int)),       this, SIGNAL(maxEvolutionChange(int)));
  connect(mAreaThreshold,   SIGNAL(valueChanged(double)),    this, SIGNAL(areaThresholdChange(double)));
  connect(mMinMargin,       SIGNAL(valueChanged(double)),    this, SIGNAL(minMarginChange(double)));
  connect(mEdgeBlurSize,    SIGNAL(valueChanged(int)),       this, SIGNAL(edgeBlurSizeChange(int)));

}

MserWidget::~MserWidget()
{

}

int MserWidget::delta() const
{
  return mDelta->value();
}

int MserWidget::minArea() const
{
  return mMinArea->value();
}

int MserWidget::maxArea() const
{
  return mMaxArea->value();
}

double MserWidget::maxVariation() const
{
  return mMaxVariation->value();
}

double MserWidget::minDiversity() const
{
  return mMinDiversity->value();
}

int MserWidget::maxEvolution() const
{
  return mMaxEvolution->value();
}

double MserWidget::areaThreshold() const
{
  return mAreaThreshold->value();
}

double MserWidget::minMargin() const
{
  return mMinMargin->value();
}

int MserWidget::edgeBlurSize() const
{
  return mEdgeBlurSize->value();
}

void MserWidget::setDelta(int delta)
{
  const QSignalBlocker blockerDelta(mDelta);
  mDelta->setValue(delta);
}

void MserWidget::setMinArea(int minArea)
{
  const QSignalBlocker blockerMinArea(mMinArea);
  mMinArea->setValue(minArea);
}

void MserWidget::setMaxArea(int maxArea)
{
  const QSignalBlocker blockerMaxArea(mMaxArea);
  //mMinArea->setRange(0, mMaxArea->value() - 1);
  //mMaxArea->setRange(mMinArea->value() + 1, 100000);
  mMaxArea->setValue(maxArea);
}

void MserWidget::setMaxVariation(double maxVariation)
{
  const QSignalBlocker blockerMaxVariation(mMaxVariation);
  mMaxVariation->setValue(maxVariation);
}

void MserWidget::setMinDiversity(double minDiversity)
{
  const QSignalBlocker blockerMinDiversity(mMinDiversity);
  mMinDiversity->setValue(minDiversity);
}

void MserWidget::setMaxEvolution(int maxEvolution)
{
  const QSignalBlocker blockerMaxEvolution(mMaxEvolution);
  mMaxEvolution->setValue(maxEvolution);
}

void MserWidget::setAreaThreshold(double areaThreshold)
{
  const QSignalBlocker blockerAreaThreshold(mAreaThreshold);
  mAreaThreshold->setValue(areaThreshold);
}

void MserWidget::setMinMargin(double minMargin)
{
  const QSignalBlocker blockerMinMargin(mMinMargin);
  mMinMargin->setValue(minMargin);
}

void MserWidget::setEdgeBlurSize(int edgeBlurSize)
{
  const QSignalBlocker blockerEdgeBlurSize(mEdgeBlurSize);
  mEdgeBlurSize->setValue(edgeBlurSize);
}

void MserWidget::update()
{
  //mMinArea->setRange(0, mMaxArea->value() - 1);
  //mMaxArea->setRange(mMinArea->value() + 1, 100000);
}

void MserWidget::reset()
{
  const QSignalBlocker blockerDelta(mDelta);
  const QSignalBlocker blockerMinArea(mMinArea);
  const QSignalBlocker blockerMaxArea(mMaxArea);
  const QSignalBlocker blockerMaxVariation(mMaxVariation);
  const QSignalBlocker blockerMinDiversity(mMinDiversity);
  const QSignalBlocker blockerMaxEvolution(mMaxEvolution);
  const QSignalBlocker blockerAreaThreshold(mAreaThreshold);
  const QSignalBlocker blockerMinMargin(mMinMargin);
  const QSignalBlocker blockerEdgeBlurSize(mEdgeBlurSize);

  mDelta->setValue(5);
  mMinArea->setValue(60);
  mMaxArea->setValue(14400);
  mMaxVariation->setValue(0.25);
  mMinDiversity->setValue(.2);
  mMaxEvolution->setValue(200);
  mAreaThreshold->setValue(1.01);
  mMinMargin->setValue(0.003);
  mEdgeBlurSize->setValue(5);
}

void MserWidget::init()
{
  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("MSER Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout(this);
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Delta:")), 0, 0);
  mDelta->setRange(0, 10000);
  propertiesLayout->addWidget(mDelta, 0, 1);

  propertiesLayout->addWidget(new QLabel(tr("Min Area:")), 1, 0);
  mMinArea->setRange(0, 100000);
  propertiesLayout->addWidget(mMinArea, 1, 1);

  propertiesLayout->addWidget(new QLabel(tr("Max Area:")), 2, 0);
  mMaxArea->setRange(0, 100000);
  propertiesLayout->addWidget(mMaxArea, 2, 1);

  propertiesLayout->addWidget(new QLabel(tr("Max Variation:")), 3, 0);
  propertiesLayout->addWidget(mMaxVariation, 3, 1);

  propertiesLayout->addWidget(new QLabel(tr("Min Diversity:")), 4, 0);
  propertiesLayout->addWidget(mMinDiversity, 4, 1);

  propertiesLayout->addWidget(new QLabel(tr("Max Evolution:")), 5, 0);
  mMaxEvolution->setRange(0, 10000);
  propertiesLayout->addWidget(mMaxEvolution, 5, 1);

  propertiesLayout->addWidget(new QLabel(tr("Area Threshold:")), 6, 0);
  mAreaThreshold->setRange(0, 99.99);
  propertiesLayout->addWidget(mAreaThreshold, 6, 1);

  propertiesLayout->addWidget(new QLabel(tr("Min Margin:")), 7, 0);
  mMinMargin->setDecimals(3);
  propertiesLayout->addWidget(mMinMargin, 7, 1);

  propertiesLayout->addWidget(new QLabel(tr("Edge Blur Size:")), 8, 0);
  mEdgeBlurSize->setRange(0, 10000);
  propertiesLayout->addWidget(mEdgeBlurSize, 8, 1);

  reset(); /// set default values

  update();
}

} // namespace fme

