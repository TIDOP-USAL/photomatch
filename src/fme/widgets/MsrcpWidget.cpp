#include "MsrcpWidget.h"

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

MsrcpWidget::MsrcpWidget(QWidget *parent)
  : IMsrcpWidget(parent),
    mSmallScale(new QDoubleSpinBox(this)),
    mMidScale(new QDoubleSpinBox(this)),
    mLargeScale(new QDoubleSpinBox(this))
{
  init();

  /// Signals and slots
  connect(mSmallScale,      SIGNAL(valueChanged(double)),     this, SIGNAL(smallScaleChange(double)));
  connect(mMidScale,        SIGNAL(valueChanged(double)),     this, SIGNAL(midScaleChange(double)));
  connect(mLargeScale,      SIGNAL(valueChanged(double)),     this, SIGNAL(largeScaleChange(double)));
}

double MsrcpWidget::smallScale() const
{
  return mSmallScale->value();
}

double MsrcpWidget::midScale() const
{
  return mMidScale->value();
}

double MsrcpWidget::largeScale() const
{
  return mLargeScale->value();
}

void MsrcpWidget::setSmallScale(double smallScale)
{
  const QSignalBlocker blockerSmallScale(mSmallScale);
  mSmallScale->setValue(smallScale);
}

void MsrcpWidget::setMidScale(double midScale)
{
  const QSignalBlocker blockerMidScale(mMidScale);
  mMidScale->setValue(midScale);
}

void MsrcpWidget::setLargeScale(double largeScale)
{
  const QSignalBlocker blockerLargeScale(mLargeScale);
  mLargeScale->setValue(largeScale);
}

void MsrcpWidget::update()
{
}

void MsrcpWidget::reset()
{
  const QSignalBlocker blockerSmallScale(mSmallScale);
  const QSignalBlocker blockerMidScale(mMidScale);
  const QSignalBlocker blockerLargeScale(mLargeScale);

  mSmallScale->setValue(10.);
  mMidScale->setValue(100.);
  mLargeScale->setValue(220.);

}

void MsrcpWidget::init()
{
  this->setWindowTitle("MSRCP");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("MSRCP Parameters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout(groupBox);

  QLabel *lbl = new QLabel(tr("MultiScale Retinex with Chromaticity Preservation"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  lbl->setFont(font);
  propertiesLayout->addWidget(lbl, 0, 0);

  QGroupBox *groupBoxBlocksize = new QGroupBox(tr("Retinex Scales"), this);
  propertiesLayout->addWidget(groupBoxBlocksize, 1, 0);
  QGridLayout *propertiesLayoutBlocksize = new QGridLayout(this);
  groupBoxBlocksize->setLayout(propertiesLayoutBlocksize);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Small Scale:")), 0, 0);
  mSmallScale->setRange(0., 19.99);
  propertiesLayoutBlocksize->addWidget(mSmallScale, 0, 1);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Mid Scale:")), 1, 0);
  mMidScale->setRange(20., 199.99);
  propertiesLayoutBlocksize->addWidget(mMidScale, 1, 1);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Large Scale:")), 2, 0);
  mLargeScale->setRange(200., 256.);
  propertiesLayoutBlocksize->addWidget(mLargeScale, 2, 1);

  reset();
  update();
}

} // namespace fme



