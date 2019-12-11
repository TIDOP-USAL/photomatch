#include "AcebsfWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
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

  retranslate();

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

void AcebsfWidget::retranslate()
{
#ifndef QT_NO_WHATSTHIS
  mK1->setWhatsThis(tr("<html><head/><body><p><strong>K1</strong> controls the&nbsp;actual contrast of input image. If the value of <strong>K1</strong> is&nbsp;selected <strong>5</strong> then its effect on the input image is little&nbsp;change in the contrast, if the value of <strong>K1</strong> is selected <strong>1&nbsp;</strong>then its reduces contrast to about 20% of original and if&nbsp;the value of <strong>K1</strong> is selected <strong>10</strong> then its increase contrast&nbsp;about to 2.5 times the input image. Therefore a&nbsp;reasonable range of values of K1 is to be selected in the&nbsp;experiments. For effective contrast enhancement of&nbsp;input images <strong>the value of K1 should be lies between 10&nbsp;to 25</strong>.</p></body></html>"));
  mK2->setWhatsThis(tr("<html><head/><body><p><p><strong>K2</strong>&nbsp;represents the&nbsp;normalized gray value about which contrast is&nbsp;increased or decreased. The initial value of <strong>K2</strong> is&nbsp;selected 0.5 (i.e., the midpoint of the gray scale) but&nbsp;different images may require different points of the&nbsp;gray scale to be enhanced. Therefore a reasonable&nbsp;range of values of K2 is to be selected in the&nbsp;experiments. For effective contrast enhancement of&nbsp;input images the value of K2 should be lies between 0&nbsp;to 1. <strong>The typical value of K2 is 0.5</strong>.</p></p></body></html>"));
  mL->setWhatsThis(tr("<html><head/><body><p><p>Use to district the range of histogram. Range between 0 and 1.</p></p></body></html>"));
  mBlockSizeX->setWhatsThis(tr("<html><head/><body><p><p>Block size X.</p></p></body></html>"));
  mBlockSizeY->setWhatsThis(tr("<html><head/><body><p><p>Block size Y.</p></p></body></html>"));
#endif // QT_NO_WHATSTHIS
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
  this->setWindowTitle("ACEBSF");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("ACEBSF Parameters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  groupBox->setLayout(propertiesLayout);

  QLabel *lbl = new QLabel(tr("Adaptive Contrast Enhancement Based on modified Sigmoid Function"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  lbl->setFont(font);
  propertiesLayout->addWidget(lbl, 0, 0);

  QGroupBox *groupBoxBlocksize = new QGroupBox(tr("Blocksize"), this);
  propertiesLayout->addWidget(groupBoxBlocksize, 1, 0, 1, 2);
  QGridLayout *propertiesLayoutBlocksize = new QGridLayout();
  groupBoxBlocksize->setLayout(propertiesLayoutBlocksize);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Width:")), 0, 0);
  mBlockSizeX->setRange(0, 100);
  propertiesLayoutBlocksize->addWidget(mBlockSizeX, 0, 1);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Height:")), 1, 0);
  mBlockSizeY->setRange(0, 100);
  propertiesLayoutBlocksize->addWidget(mBlockSizeY, 1, 1);


  propertiesLayout->addWidget(new QLabel(tr("L:")), 2, 0);
  mL->setRange(0, 1);
  mL->setSingleStep(0.01);
  propertiesLayout->addWidget(mL, 2, 1);

  propertiesLayout->addWidget(new QLabel(tr("K1:")), 3, 0);
  mK1->setRange(1, 100);
  propertiesLayout->addWidget(mK1, 3, 1);

  propertiesLayout->addWidget(new QLabel(tr("K2:")), 4, 0);
  mK2->setRange(0, 1);
  mK2->setSingleStep(0.01);
  propertiesLayout->addWidget(mK2, 4, 1);

  reset();
  update();
}

} // namespace photomatch

