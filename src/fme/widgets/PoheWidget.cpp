#include "PoheWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

PoheWidget::PoheWidget(QWidget *parent)
  : IPoheWidget(parent),
    mBlockSizeX(new QSpinBox(this)),
    mBlockSizeY(new QSpinBox(this))
{
  init();

  /// Signals and slots
  connect(mBlockSizeX,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeXChange(int)));
  connect(mBlockSizeY,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeYChange(int)));

}

PoheWidget::~PoheWidget()
{

}

void PoheWidget::onBlockSizeXChange(int blockSizeX)
{
  emit blockSizeChange(QSize(blockSizeX, mBlockSizeY->value()));
}

void PoheWidget::onBlockSizeYChange(int blockSizeY)
{
  emit blockSizeChange(QSize(mBlockSizeX->value(), blockSizeY));
}

QSize PoheWidget::blockSize() const
{
  return QSize(mBlockSizeX->value(), mBlockSizeY->value());
}

void PoheWidget::setBlockSize(const QSize &blockSize)
{
  const QSignalBlocker blockerTilesGridX(mBlockSizeX);
  const QSignalBlocker blockerTilesGridY(mBlockSizeY);
  mBlockSizeX->setValue(blockSize.width());
  mBlockSizeY->setValue(blockSize.height());

}

void PoheWidget::update()
{
}

void PoheWidget::reset()
{
  const QSignalBlocker blockerBlockSizeX(mBlockSizeX);
  const QSignalBlocker blockerBlockSizeY(mBlockSizeY);

  mBlockSizeX->setValue(127);
  mBlockSizeY->setValue(127);
}

void PoheWidget::init()
{
  this->setWindowTitle("POHE");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("POHE Parameters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout(groupBox);

  QLabel *lbl = new QLabel(tr("Parametric-Oriented Histogram Equalization"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  lbl->setFont(font);
  propertiesLayout->addWidget(lbl, 0, 0);

  QGroupBox *groupBoxBlocksize = new QGroupBox(tr("Block Size"), this);
  propertiesLayout->addWidget(groupBoxBlocksize, 1, 0);
  QGridLayout *propertiesLayoutBlocksize = new QGridLayout();
  groupBoxBlocksize->setLayout(propertiesLayoutBlocksize);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Width:")), 0, 0);
  mBlockSizeX->setRange(0, 1000);
  propertiesLayoutBlocksize->addWidget(mBlockSizeX, 0, 1);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Height:")), 1, 0);
  mBlockSizeY->setRange(0, 1000);
  propertiesLayoutBlocksize->addWidget(mBlockSizeY, 1, 1);


  reset(); /// set default values

  update();
}

} // namespace fme
