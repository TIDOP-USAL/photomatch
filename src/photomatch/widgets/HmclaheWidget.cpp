#include "HmclaheWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

HmclaheWidget::HmclaheWidget(QWidget *parent)
  : IHmclaheWidget(parent),
    mBlockSizeX(new QSpinBox(this)),
    mBlockSizeY(new QSpinBox(this)),
    mL(new QDoubleSpinBox(this)),
    mPhi(new QDoubleSpinBox(this))
{
  init();

  retranslate();

  /// Signals and slots
  connect(mBlockSizeX,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeXChange(int)));
  connect(mBlockSizeY,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeYChange(int)));
  connect(mL,             SIGNAL(valueChanged(double)),     this, SIGNAL(lChange(double)));
  connect(mPhi,           SIGNAL(valueChanged(double)),     this, SIGNAL(phiChange(double)));

}

HmclaheWidget::~HmclaheWidget()
{

}

void HmclaheWidget::onBlockSizeXChange(int blockSizeX)
{
  emit blockSizeChange(QSize(blockSizeX, mBlockSizeY->value()));
}

void HmclaheWidget::onBlockSizeYChange(int blockSizeY)
{
  emit blockSizeChange(QSize(mBlockSizeX->value(), blockSizeY));
}

QSize HmclaheWidget::blockSize() const
{
  return QSize(mBlockSizeX->value(), mBlockSizeY->value());
}

double HmclaheWidget::l() const
{
  return mL->value();
}

double HmclaheWidget::phi() const
{
  return mPhi->value();
}

void HmclaheWidget::setBlockSize(const QSize &blockSize)
{
  const QSignalBlocker blockerTilesGridX(mBlockSizeX);
  const QSignalBlocker blockerTilesGridY(mBlockSizeY);
  mBlockSizeX->setValue(blockSize.width());
  mBlockSizeY->setValue(blockSize.height());
}

void HmclaheWidget::setL(double l)
{
  const QSignalBlocker blockerL(mL);
  mL->setValue(static_cast<double>(l));
}

void HmclaheWidget::setPhi(double phi)
{
  const QSignalBlocker blockerPhi(mPhi);
  mPhi->setValue(static_cast<double>(phi));
}

void HmclaheWidget::update()
{
}

void HmclaheWidget::retranslate()
{
#ifndef QT_NO_WHATSTHIS
  mL->setWhatsThis(tr("<html><head/><body><p>Use to district the range of histogram. Range between 0 and 1.</p></body></html>"));
  mPhi->setWhatsThis(tr("<html><head/><body><p>Use to adjust the histogram. Range between 0 and 1.</p></body></html>"));
  mBlockSizeX->setWhatsThis(tr("<html><head/><body><p><p>Block size X.</p></p></body></html>"));
  mBlockSizeY->setWhatsThis(tr("<html><head/><body><p><p>Block size Y.</p></p></body></html>"));
#endif // QT_NO_WHATSTHIS
}

void HmclaheWidget::reset()
{
  const QSignalBlocker blockerBlockSizeX(mBlockSizeX);
  const QSignalBlocker blockerBlockSizeY(mBlockSizeY);
  const QSignalBlocker blockerL(mL);
  const QSignalBlocker blockerPhi(mPhi);

  mBlockSizeX->setValue(17);
  mBlockSizeY->setValue(17);
  mL->setValue(0.03);
  mPhi->setValue(0.5);
}

void HmclaheWidget::init()
{
  this->setWindowTitle("HMCLAHE");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("HMCLAHE Parameters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout(groupBox);

  QLabel *lbl = new QLabel(tr("Histogram Modified Contrast Limited Adaptive Histogram Equalization"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  lbl->setFont(font);
  propertiesLayout->addWidget(lbl, 0, 0, 1, 2);

  QGroupBox *groupBoxBlocksize = new QGroupBox(tr("Block Size"), groupBox);

  QGridLayout *propertiesLayoutBlocksize = new QGridLayout(groupBoxBlocksize);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Width:")), 0, 0, 1, 1);
  mBlockSizeX->setRange(0, 1000);
  propertiesLayoutBlocksize->addWidget(mBlockSizeX, 0, 1, 1, 1);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Height:")),  1, 0, 1, 1);
  mBlockSizeY->setRange(0, 1000);
  propertiesLayoutBlocksize->addWidget(mBlockSizeY, 1, 1, 1, 1);

  propertiesLayout->addWidget(groupBoxBlocksize, 1, 0, 1, 2);

  propertiesLayout->addWidget(new QLabel(tr("L:")), 2, 0, 1, 1);
  mL->setRange(0., 1.);
  mL->setSingleStep(0.01);
  mL->setDecimals(2);
  propertiesLayout->addWidget(mL, 2, 1, 1, 1);

  propertiesLayout->addWidget(new QLabel(tr("Phi:")), 3, 0, 1, 1);
  mPhi->setRange(0., 1.);
  mPhi->setSingleStep(0.1);
  mPhi->setDecimals(2);
  propertiesLayout->addWidget(mPhi, 3, 1, 1, 1);

  reset();
  update();
}

} // namespace photomatch

