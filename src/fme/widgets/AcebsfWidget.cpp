#include "AcebsfWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

AcebsfWidget::AcebsfWidget(QWidget *parent)
  : IAcebsfWidget(parent),
    mBlockSizeX(new QSpinBox(this)),
    mBlockSizeY(new QSpinBox(this)),
    mL(new QDoubleSpinBox(this)),
    mK1(new QDoubleSpinBox(this)),
    mK2(new QDoubleSpinBox(this))
{
  init();

  /// Signals and slots
  connect(mBlockSizeX,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeXChange(int)));
  connect(mBlockSizeY,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeYChange(int)));
  connect(mL,             SIGNAL(valueChanged(double)),     this, SIGNAL(lChange(double)));
  connect(mK1,            SIGNAL(valueChanged(double)),     this, SIGNAL(k1Change(double)));
  connect(mK2,            SIGNAL(valueChanged(double)),     this, SIGNAL(k2Change(double)));

}

AcebsfWidget::~AcebsfWidget()
{

}

void AcebsfWidget::onBlockSizeXChange(int blockSizeX)
{
  emit blockSizeChange(QSize(blockSizeX, mBlockSizeY->value()));
}

void AcebsfWidget::onBlockSizeYChange(int blockSizeY)
{
  emit blockSizeChange(QSize(mBlockSizeX->value(), blockSizeY));
}

QSize AcebsfWidget::blockSize() const
{
  return QSize(mBlockSizeX->value(), mBlockSizeY->value());
}

double AcebsfWidget::l() const
{
  return mL->value();
}

double AcebsfWidget::k1() const
{
  return mK1->value();
}

double AcebsfWidget::k2() const
{
  return mK2->value();
}

void AcebsfWidget::setBlockSize(const QSize &blockSize)
{
  const QSignalBlocker blockerTilesGridX(mBlockSizeX);
  const QSignalBlocker blockerTilesGridY(mBlockSizeY);
  mBlockSizeX->setValue(blockSize.width());
  mBlockSizeY->setValue(blockSize.height());
}

void AcebsfWidget::setL(double l)
{
  const QSignalBlocker blockerL(mL);
  mL->setValue(l);
}

void AcebsfWidget::setK1(double k1)
{
  const QSignalBlocker blockerK1(mK1);
  mK1->setValue(k1);
}

void AcebsfWidget::setK2(double k2)
{
  const QSignalBlocker blockerK2(mK2);
  mK2->setValue(k2);
}

void AcebsfWidget::update()
{
}

void AcebsfWidget::reset()
{
  const QSignalBlocker blockerBlockSizeX(mBlockSizeX);
  const QSignalBlocker blockerBlockSizeY(mBlockSizeY);
  const QSignalBlocker blockerL(mL);
  const QSignalBlocker blockerK1(mK1);
  const QSignalBlocker blockerK2(mK2);

  mBlockSizeX->setValue(8);
  mBlockSizeY->setValue(8);
  mL->setValue(0.03);
  mK1->setValue(10.);
  mK2->setValue(0.5);
}

void AcebsfWidget::init()
{
  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("ACEBSF Parameters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout(this);
  groupBox->setLayout(propertiesLayout);

  QLabel *lbl = new QLabel(tr("Adaptive Contrast Enhancement Based on modified Sigmoid Function"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  lbl->setFont(font);
  propertiesLayout->addWidget(lbl, 0, 0);

  QGroupBox *groupBoxBlocksize = new QGroupBox(tr("Blocksize"), this);
  propertiesLayout->addWidget(groupBoxBlocksize, 1, 0);
  QGridLayout *propertiesLayoutBlocksize = new QGridLayout(this);
  groupBoxBlocksize->setLayout(propertiesLayoutBlocksize);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Width:")), 0, 0);
  mBlockSizeX->setRange(0, 100);
  propertiesLayoutBlocksize->addWidget(mBlockSizeX, 0, 1);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Height:")), 1, 0);
  mBlockSizeY->setRange(0, 100);
  propertiesLayoutBlocksize->addWidget(mBlockSizeY, 1, 1);


  propertiesLayoutBlocksize->addWidget(new QLabel(tr("L:")), 2, 0);
  mL->setRange(0, 100);
  propertiesLayout->addWidget(mL, 2, 1);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("K1:")), 3, 0);
  mK1->setRange(0, 100);
  propertiesLayout->addWidget(mK1, 3, 1);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("K2:")), 4, 0);
  mK2->setRange(0, 100);
  propertiesLayout->addWidget(mK2, 4, 1);

  reset();
  update();
}

} // namespace fme

