#include "NoshpWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

NoshpWidget::NoshpWidget(QWidget *parent)
  : INoshpWidget(parent),
    mBlockSizeX(new QSpinBox(this)),
    mBlockSizeY(new QSpinBox(this))
{
  init();

  /// Signals and slots
  connect(mBlockSizeX,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeXChange(int)));
  connect(mBlockSizeY,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeYChange(int)));

}

NoshpWidget::~NoshpWidget()
{

}

void NoshpWidget::onBlockSizeXChange(int blockSizeX)
{
  emit blockSizeChange(QSize(blockSizeX, mBlockSizeY->value()));
}

void NoshpWidget::onBlockSizeYChange(int blockSizeY)
{
  emit blockSizeChange(QSize(mBlockSizeX->value(), blockSizeY));
}

QSize NoshpWidget::blockSize() const
{
  return QSize(mBlockSizeX->value(), mBlockSizeY->value());
}

void NoshpWidget::setBlockSize(const QSize &blockSize)
{
  const QSignalBlocker blockerTilesGridX(mBlockSizeX);
  const QSignalBlocker blockerTilesGridY(mBlockSizeY);
  mBlockSizeX->setValue(blockSize.width());
  mBlockSizeY->setValue(blockSize.height());

}

void NoshpWidget::update()
{
}

void NoshpWidget::reset()
{
  const QSignalBlocker blockerBlockSizeX(mBlockSizeX);
  const QSignalBlocker blockerBlockSizeY(mBlockSizeY);

  mBlockSizeX->setValue(127);
  mBlockSizeY->setValue(127);
}

void NoshpWidget::init()
{
  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("NOSHP Parameters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout(this);
  groupBox->setLayout(propertiesLayout);

  QLabel *lbl = new QLabel(tr("Non-Overlapped Sub-blocks and local Histogram Projection"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  lbl->setFont(font);
  propertiesLayout->addWidget(lbl, 0, 0);

  QGroupBox *groupBoxBlocksize = new QGroupBox(tr("Block Size"), this);
  propertiesLayout->addWidget(groupBoxBlocksize, 1, 0);
  QGridLayout *propertiesLayoutBlocksize = new QGridLayout(this);
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
