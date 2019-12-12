#include "ClaheWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

ClaheWidget::ClaheWidget(QWidget *parent)
  : IClaheWidget(parent),
    mClipLimit(new QDoubleSpinBox(this)),
    mTilesGridX(new QSpinBox(this)),
    mTilesGridY(new QSpinBox(this))
{
  init();

  retranslate();

  /// Signals and slots
  connect(mClipLimit,     SIGNAL(valueChanged(double)),     this, SIGNAL(clipLimitChange(double)));
  connect(mTilesGridX,    SIGNAL(valueChanged(int)),        this, SLOT(onTilesGridXChange(int)));
  connect(mTilesGridY,    SIGNAL(valueChanged(int)),        this, SLOT(onTilesGridYChange(int)));

}

ClaheWidget::~ClaheWidget()
{

}

void ClaheWidget::onTilesGridXChange(int gx)
{
  emit tileGridSizeChange(QSize(gx, mTilesGridY->value()));
}

void ClaheWidget::onTilesGridYChange(int gy)
{
  emit tileGridSizeChange(QSize(mTilesGridX->value(), gy));
}

double ClaheWidget::clipLimit() const
{
  return mClipLimit->value();
}

QSize ClaheWidget::tileGridSize() const
{
  return QSize(mTilesGridX->value(), mTilesGridY->value());
}

void ClaheWidget::setClipLimit(double clipLimit)
{
  const QSignalBlocker blockerClipLimit(mClipLimit);
  mClipLimit->setValue(clipLimit);
}

void ClaheWidget::setTilesGridSize(const QSize &tileGridSize)
{
  const QSignalBlocker blockerTilesGridX(mTilesGridX);
  const QSignalBlocker blockerTilesGridY(mTilesGridY);
  mTilesGridX->setValue(tileGridSize.width());
  mTilesGridY->setValue(tileGridSize.height());

}

void ClaheWidget::update()
{
}

void ClaheWidget::retranslate()
{
#ifndef QT_NO_WHATSTHIS
  mClipLimit->setWhatsThis(tr("<html><head/><body><p>Threshold value for contrast limiting.</p></body></html>"));
  mTilesGridX->setWhatsThis(tr("<html><head/><body><p>Width of grid for histogram equalization.</p></p></body></html>"));
  mTilesGridY->setWhatsThis(tr("<html><head/><body><p>Height of grid for histogram equalization.</p></p></body></html>"));
#endif // QT_NO_WHATSTHIS
}

void ClaheWidget::reset()
{
  const QSignalBlocker blockerClipLimit(mClipLimit);
  const QSignalBlocker blockerTilesGridX(mTilesGridX);
  const QSignalBlocker blockerTilesGridY(mTilesGridY);

  mClipLimit->setValue(40.0);
  mTilesGridX->setValue(8);
  mTilesGridY->setValue(8);
}

void ClaheWidget::init()
{
  this->setWindowTitle("CLAHE");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("CLAHE Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  QLabel *lbl = new QLabel(tr("Contrast Limited Adaptive Histogram Equalization"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  font.setWeight(75);
  lbl->setFont(font);
  lbl->setWordWrap(true);
  propertiesLayout->addWidget(lbl, 0, 0, 1, 2);

  propertiesLayout->addWidget(new QLabel(tr("Clip Limit:")), 1, 0, 1, 1);
  mClipLimit->setRange(0., 100.);
  propertiesLayout->addWidget(mClipLimit, 1, 1, 1, 1);

  QGroupBox *groupBoxTiles = new QGroupBox(tr("Block Size"), mGroupBox);
  QGridLayout *gridLayoutTiles = new QGridLayout(groupBoxTiles);
  gridLayoutTiles->setSpacing(6);
  gridLayoutTiles->setContentsMargins(11, 11, 11, 11);

  gridLayoutTiles->addWidget(new QLabel(tr("Width:")), 0, 0, 1, 1);
  mTilesGridX->setRange(0, 100);
  gridLayoutTiles->addWidget(mTilesGridX, 0, 1, 1, 1);

  gridLayoutTiles->addWidget(new QLabel(tr("Height:")), 1, 0, 1, 1);
  mTilesGridY->setRange(0, 100);
  gridLayoutTiles->addWidget(mTilesGridY, 1, 1, 1, 1);

  propertiesLayout->addWidget(groupBoxTiles, 2, 0, 1, 2);

  reset(); /// set default values

  update();
}

} // namespace photomatch
