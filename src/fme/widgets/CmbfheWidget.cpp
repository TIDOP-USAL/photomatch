#include "CmbfheWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

CmbfheWidget::CmbfheWidget(QWidget *parent)
  : ICmbfheWidget(parent),
    mBlockSizeX(new QSpinBox(this)),
    mBlockSizeY(new QSpinBox(this))
{
  init();

  /// Signals and slots
  connect(mBlockSizeX,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeXChange(int)));
  connect(mBlockSizeY,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeYChange(int)));

}

CmbfheWidget::~CmbfheWidget()
{

}

void CmbfheWidget::onBlockSizeXChange(int blockSizeX)
{
  emit blockSizeChange(QSize(blockSizeX, mBlockSizeY->value()));
}

void CmbfheWidget::onBlockSizeYChange(int blockSizeY)
{
  emit blockSizeChange(QSize(mBlockSizeX->value(), blockSizeY));
}

QSize CmbfheWidget::blockSize() const
{
  return QSize(mBlockSizeX->value(), mBlockSizeY->value());
}

void CmbfheWidget::setBlockSize(const QSize &blockSize)
{
  const QSignalBlocker blockerTilesGridX(mBlockSizeX);
  const QSignalBlocker blockerTilesGridY(mBlockSizeY);
  mBlockSizeX->setValue(blockSize.width());
  mBlockSizeY->setValue(blockSize.height());

}

void CmbfheWidget::update()
{
}

void CmbfheWidget::reset()
{
  const QSignalBlocker blockerBlockSizeX(mBlockSizeX);
  const QSignalBlocker blockerBlockSizeY(mBlockSizeY);

  mBlockSizeX->setValue(11);
  mBlockSizeY->setValue(11);
}

void CmbfheWidget::init()
{
  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("CMBFHE Parameters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout(this);
  groupBox->setLayout(propertiesLayout);

  QLabel *lbl = new QLabel(tr("Cascaded Multistep Binomial Filtering Histogram Equalization"), this);
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
