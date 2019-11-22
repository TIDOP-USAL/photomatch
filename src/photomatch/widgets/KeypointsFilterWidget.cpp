#include "KeypointsFilterWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>

namespace photomatch
{

KeypointsFilterWidget::KeypointsFilterWidget(QWidget *parent)
  : IKeypointsFilterWidget(parent),
    mCheckBoxPointsNumber(new QCheckBox(this)),
    mPointsNumber(new QSpinBox(this)),
    mCheckBoxSize(new QCheckBox(this)),
    mMinSize(new QDoubleSpinBox(this)),
    mMaxSize(new QDoubleSpinBox(this))
{
  init();

  connect(mPointsNumber,  SIGNAL(valueChanged(int)),        this, SIGNAL(nPointsChange(int)));
  connect(mMinSize,       SIGNAL(valueChanged(double)),     this, SIGNAL(minSizeChange(double)));
  connect(mMaxSize,       SIGNAL(valueChanged(double)),     this, SIGNAL(maxSizeChange(double)));

}

KeypointsFilterWidget::~KeypointsFilterWidget()
{
}

int KeypointsFilterWidget::nPoints() const
{
  return mPointsNumber->value();
}

double KeypointsFilterWidget::minSize() const
{
  return mMinSize->value();
}

double KeypointsFilterWidget::maxSize() const
{
  return mMaxSize->value();
}

void KeypointsFilterWidget::setNPoints(int nPoints)
{
  const QSignalBlocker blockerNPoints(mPointsNumber);
  mPointsNumber->setValue(nPoints);
}

void KeypointsFilterWidget::setMinSize(double minSize)
{
  const QSignalBlocker blockerMinSize(mMinSize);
  mMinSize->setValue(minSize);
  mMaxSize->setMinimum(minSize);
}

void KeypointsFilterWidget::setMaxSize(double maxSize)
{
  const QSignalBlocker blockerMaxSizee(mMaxSize);
  mMaxSize->setValue(maxSize);
  mMinSize->setMaximum(maxSize);
}

void KeypointsFilterWidget::update()
{
  mPointsNumber->setEnabled(mCheckBoxPointsNumber->isChecked());
  mMinSize->setEnabled(mCheckBoxSize->isChecked());
  mMaxSize->setEnabled(mCheckBoxSize->isChecked());
}

void KeypointsFilterWidget::reset()
{
  const QSignalBlocker blockerNPoints(mPointsNumber);
  const QSignalBlocker blockerMinSize(mMinSize);
  const QSignalBlocker blockerMaxSizee(mMaxSize);

  mCheckBoxPointsNumber->setChecked(false);
  mPointsNumber->setValue(10000);
  mCheckBoxSize->setChecked(false);
  mMinSize->setValue(0.);
  mMaxSize->setValue(10000.);

  update();
}

void KeypointsFilterWidget::init()
{
  this->setWindowTitle("Keypoints Filter");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("Keypoints Filters"), this);
  layout->addWidget(groupBox);

  mCheckBoxPointsNumber->setText(tr("N Best"));
  mCheckBoxPointsNumber->setChecked(false);
  layout->addWidget(mCheckBoxPointsNumber, 0, 0, 1, 1);

  mPointsNumber->setRange(0, 100000);
  layout->addWidget(mPointsNumber, 0, 1, 1, 4);

  mCheckBoxSize->setText(tr("Keypoints Size"));
  mCheckBoxSize->setChecked(false);
  layout->addWidget(mCheckBoxPointsNumber, 1, 0, 1, 1);

  layout->addWidget(new QLabel(tr("Min:")), 1, 1, 1, 1);
  mMinSize->setRange(0., 99.);
  layout->addWidget(mMinSize, 1, 2, 1, 1);

  layout->addWidget(new QLabel(tr("Max:")), 3, 1, 1, 1);
  mMaxSize->setRange(0., 99.);
  layout->addWidget(mMaxSize, 1, 4, 1, 1);

  reset();
  update();
}

} // namespace photomatch


