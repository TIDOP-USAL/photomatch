#include "LceBsescsWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

LceBsescsWidget::LceBsescsWidget(QWidget *parent)
  : ILceBsescsWidget(parent),
    mBlockSizeX(new QSpinBox(this)),
    mBlockSizeY(new QSpinBox(this))
{
  init();

  /// Signals and slots
  connect(mBlockSizeX,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeXChange(int)));
  connect(mBlockSizeY,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeYChange(int)));

}

LceBsescsWidget::~LceBsescsWidget()
{

}

void LceBsescsWidget::onBlockSizeXChange(int gx)
{
  emit blockSizeChange(QSize(gx, mBlockSizeY->value()));
}

void LceBsescsWidget::onBlockSizeYChange(int gy)
{
  emit blockSizeChange(QSize(mBlockSizeX->value(), gy));
}

QSize LceBsescsWidget::blockSize() const
{
  return QSize(mBlockSizeX->value(), mBlockSizeY->value());
}

void LceBsescsWidget::setBlockSize(const QSize &blockSize)
{
  const QSignalBlocker blockerTilesGridX(mBlockSizeX);
  const QSignalBlocker blockerTilesGridY(mBlockSizeY);
  mBlockSizeX->setValue(blockSize.width());
  mBlockSizeY->setValue(blockSize.height());

}

void LceBsescsWidget::update()
{
}

void LceBsescsWidget::reset()
{
  const QSignalBlocker blockerBlockSizeX(mBlockSizeX);
  const QSignalBlocker blockerBlockSizeY(mBlockSizeY);

  mBlockSizeX->setValue(33);
  mBlockSizeY->setValue(33);
}

void LceBsescsWidget::init()
{
  this->setWindowTitle("LCE-BSESCS");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("LCE-BSESCS Parameters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout(groupBox);

  QLabel *lbl = new QLabel(tr("Local Contrast Enhancement Utilizing "
                           "Bidirectional Switching Equalization of "
                           "Separated and Clipped Subhistograms"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  lbl->setFont(font);
  propertiesLayout->addWidget(lbl, 0, 0);

  QGroupBox *groupBoxBlocksize = new QGroupBox(tr("Blocksize"), this);
  propertiesLayout->addWidget(groupBoxBlocksize, 1, 0);
  QGridLayout *propertiesLayoutBlocksize = new QGridLayout();
  groupBoxBlocksize->setLayout(propertiesLayoutBlocksize);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Width:")), 0, 0);
  mBlockSizeX->setRange(0, 100);
  propertiesLayoutBlocksize->addWidget(mBlockSizeX, 0, 1);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Height:")), 1, 0);
  mBlockSizeY->setRange(0, 100);
  propertiesLayoutBlocksize->addWidget(mBlockSizeY, 1, 1);


  reset(); /// set default values

  update();
}

} // namespace fme
