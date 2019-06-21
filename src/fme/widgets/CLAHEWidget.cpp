#include "CLAHEWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

CLAHEWidget::CLAHEWidget(QWidget *parent)
  : ICLAHEWidget(parent),
    mClipLimit(new QDoubleSpinBox(this)),
    mTilesGridX(new QSpinBox(this)),
    mTilesGridY(new QSpinBox(this))
{
  init();

  /// Signals and slots
  connect(mClipLimit,     SIGNAL(valueChanged(double)),     this, SIGNAL(clipLimitChange(double)));
  connect(mTilesGridX,    SIGNAL(valueChanged(int)),        this, SLOT(onTilesGridXChange(int)));
  connect(mTilesGridY,    SIGNAL(valueChanged(int)),        this, SLOT(onTilesGridYChange(int)));

}

CLAHEWidget::~CLAHEWidget()
{

}

void CLAHEWidget::onTilesGridXChange(int gx)
{
  emit tileGridSizeChange(QSize(gx, mTilesGridY->value()));
}

void CLAHEWidget::onTilesGridYChange(int gy)
{
  emit tileGridSizeChange(QSize(mTilesGridX->value(), gy));
}

double CLAHEWidget::clipLimit() const
{
  return mClipLimit->value();
}

QSize CLAHEWidget::tileGridSize() const
{
  return QSize(mTilesGridX->value(), mTilesGridY->value());
}

void CLAHEWidget::setClipLimit(double clipLimit)
{
  const QSignalBlocker blockerClipLimit(mClipLimit);
  mClipLimit->setValue(clipLimit);
}

void CLAHEWidget::setTilesGridSize(const QSize &tileGridSize)
{
  const QSignalBlocker blockerTilesGridX(mTilesGridX);
  const QSignalBlocker blockerTilesGridY(mTilesGridY);
  mTilesGridX->setValue(tileGridSize.width());
  mTilesGridY->setValue(tileGridSize.height());

}

void CLAHEWidget::update()
{
}

void CLAHEWidget::reset()
{
  const QSignalBlocker blockerClipLimit(mClipLimit);
  const QSignalBlocker blockerTilesGridX(mTilesGridX);
  const QSignalBlocker blockerTilesGridY(mTilesGridY);

  mClipLimit->setValue(40.0);
  mTilesGridX->setValue(8);
  mTilesGridY->setValue(8);
}

void CLAHEWidget::init()
{
  this->setWindowTitle("CLAHE");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("CLAHE Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout(this);
  mGroupBox->setLayout(propertiesLayout);

  QLabel *lbl = new QLabel(tr("Contrast Limited Adaptive Histogram Equalization"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  lbl->setFont(font);
  propertiesLayout->addWidget(lbl, 0, 0);

  propertiesLayout->addWidget(new QLabel(tr("Clip Limit:")), 0, 0);
  mClipLimit->setRange(0, 100);
  propertiesLayout->addWidget(mClipLimit, 0, 1);

  propertiesLayout->addWidget(new QLabel(tr("Tiles Size X:")), 1, 0);
  mTilesGridX->setRange(0, 100);
  propertiesLayout->addWidget(mTilesGridX, 1, 1);

  propertiesLayout->addWidget(new QLabel(tr("Tiles Size Y:")), 1, 0);
  mTilesGridY->setRange(0, 100);
  propertiesLayout->addWidget(mTilesGridY, 2, 1);

  reset(); /// set default values

  update();
}

} // namespace fme
