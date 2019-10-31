#include "HogWidget.h"

#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

HogWidget::HogWidget(QWidget *parent)
  : IHogWidget(parent),
    mWinSizeHeight(new QSpinBox(this)),
    mWinSizeWidth(new QSpinBox(this)),
    mBlockSizeX(new QSpinBox(this)),
    mBlockSizeY(new QSpinBox(this)),
    mBlockStrideX(new QSpinBox(this)),
    mBlockStrideY(new QSpinBox(this)),
    mCellSizeX(new QSpinBox(this)),
    mCellSizeY(new QSpinBox(this)),
    mNbins(new QSpinBox(this)),
    mDerivAperture(new QSpinBox(this))/*,
    mWinSigma(new QDoubleSpinBox(this)),
    mHistogramNormType(new QComboBox(this)),
    mL2HysThreshold(new QDoubleSpinBox(this)),
    mGammaCorrection(new QCheckBox(this)),
    mFreeCoef(new QDoubleSpinBox(this)),
    mNlevels(new QSpinBox(this)),
    mSignedGradient(new QCheckBox(this))*/
{
  init();

  /// Signals and slots
  connect(mWinSizeHeight,  SIGNAL(valueChanged(int)),        this, SLOT(onWinSizeHeightChange(int)));
  connect(mWinSizeWidth,   SIGNAL(valueChanged(int)),        this, SLOT(onWinSizeWidthChange(int)));
  connect(mBlockSizeX,     SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeXChange(int)));
  connect(mBlockSizeY,     SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeYChange(int)));
  connect(mBlockStrideX,   SIGNAL(valueChanged(int)),        this, SLOT(onBlockStrideXChange(int)));
  connect(mBlockStrideY,   SIGNAL(valueChanged(int)),        this, SLOT(onBlockStrideYChange(int)));
  connect(mCellSizeX,      SIGNAL(valueChanged(int)),        this, SLOT(onCellSizeXChange(int)));
  connect(mCellSizeY,      SIGNAL(valueChanged(int)),        this, SLOT(onCellSizeYChange(int)));
  connect(mNbins,          SIGNAL(valueChanged(int)),        this, SIGNAL(nbinsChange(int)));
  connect(mDerivAperture,  SIGNAL(valueChanged(int)),        this, SIGNAL(derivApertureChange(int)));
}

HogWidget::~HogWidget()
{

}

void HogWidget::onWinSizeHeightChange(int height)
{
  emit winSizeChange(QSize(mWinSizeWidth->value(), height));
}

void HogWidget::onWinSizeWidthChange(int width)
{
  emit winSizeChange(QSize(width, mWinSizeHeight->value()));
}

void HogWidget::onBlockSizeXChange(int blockSizeX)
{
  emit blockSizeChange(QSize(blockSizeX,mBlockSizeY->value()));
}

void HogWidget::onBlockSizeYChange(int blockSizeY)
{
  emit blockSizeChange(QSize(mBlockSizeX->value(),blockSizeY));
}

void HogWidget::onBlockStrideXChange(int blockStrideX)
{
  emit blockStrideChange(QSize(blockStrideX,mBlockStrideY->value()));
}

void HogWidget::onBlockStrideYChange(int blockStrideY)
{
  emit blockStrideChange(QSize(mBlockStrideX->value(),blockStrideY));
}

void HogWidget::onCellSizeXChange(int cellSizeX)
{
  emit cellSizeChange(QSize(cellSizeX,mCellSizeY->value()));
}

void HogWidget::onCellSizeYChange(int cellSizeY)
{
  emit cellSizeChange(QSize(mCellSizeX->value(),cellSizeY));
}


QSize HogWidget::winSize() const
{
  return QSize(mWinSizeWidth->value(), mWinSizeHeight->value());
}

QSize HogWidget::blockSize() const
{
  return QSize(mBlockSizeX->value(), mBlockSizeY->value());
}

QSize HogWidget::blockStride() const
{
  return QSize(mBlockStrideX->value(), mBlockStrideY->value());
}

QSize HogWidget::cellSize() const
{
  return QSize(mCellSizeX->value(), mCellSizeY->value());
}

int HogWidget::nbins() const
{
  return mNbins->value();
}

int HogWidget::derivAperture() const
{
  return mDerivAperture->value();
}

//double HogWidget::winSigma() const
//{
//  return mWinSigma->value();
//}

//QString HogWidget::histogramNormType() const
//{
//  return mHistogramNormType->currentText();
//}

//double HogWidget::l2HysThreshold() const
//{
//  return mL2HysThreshold->value();
//}

//bool HogWidget::gammaCorrection() const
//{
//  return mGammaCorrection->isChecked();
//}

//double HogWidget::freeCoef() const
//{
//  return mFreeCoef->value();
//}

//int HogWidget::nlevels() const
//{
//  return mNlevels->value();
//}

//bool HogWidget::signedGradient() const
//{
//  return mSignedGradient->isChecked();
//}

void HogWidget::setWinSize(const QSize &winSize)
{
  const QSignalBlocker blockerWinSizeHeight(mWinSizeHeight);
  const QSignalBlocker blockerWinSizeWidth(mWinSizeWidth);
  mWinSizeHeight->setValue(winSize.height());
  mWinSizeWidth->setValue(winSize.width());
}

void HogWidget::setBlockSize(const QSize &blockSize)
{
  const QSignalBlocker blockerBlockSizeX(mBlockSizeX);
  const QSignalBlocker blockerBlockSizeY(mBlockSizeY);
  mBlockSizeX->setValue(blockSize.width());
  mBlockSizeY->setValue(blockSize.height());
}

void HogWidget::setBlockStride(const QSize &blockStride)
{
  const QSignalBlocker blockerBlockStrideX(mBlockStrideX);
  const QSignalBlocker blockerBlockStrideY(mBlockStrideY);
  mBlockStrideX->setValue(blockStride.width());
  mBlockStrideY->setValue(blockStride.height());
}

void HogWidget::setCellSize(const QSize &cellSize)
{
  const QSignalBlocker blockerCellSizeX(mCellSizeX);
  const QSignalBlocker blockerCellSizeY(mCellSizeY);
  mCellSizeX->setValue(cellSize.width());
  mCellSizeY->setValue(cellSize.height());
}

void HogWidget::setNbins(int nbins)
{
  const QSignalBlocker blockerNbins(mNbins);
  mNbins->setValue(nbins);
}

void HogWidget::setDerivAperture(int derivAperture)
{
  const QSignalBlocker blockerDerivAperture(mDerivAperture);
  mDerivAperture->setValue(derivAperture);
}

//void HogWidget::setWinSigma(double winSigma)
//{
//  const QSignalBlocker blockerWinSigma(mWinSigma);
//  mWinSigma->setValue(winSigma);
//}

//void HogWidget::setHistogramNormType(const QString &histogramNormType)
//{
//  const QSignalBlocker blockerHistogramNormType(mHistogramNormType);
//  mHistogramNormType->setCurrentText(histogramNormType);
//}

//void HogWidget::setL2HysThreshold(double l2HysThreshold)
//{
//  const QSignalBlocker blockerL2HysThreshold(mL2HysThreshold);
//  mL2HysThreshold->setValue(l2HysThreshold);
//}

//void HogWidget::setGammaCorrection(bool gammaCorrection)
//{
//  mGammaCorrection->setChecked(gammaCorrection);
//}

//void HogWidget::setFreeCoef(double freeCoef)
//{
//  const QSignalBlocker blockerFreeCoef(mFreeCoef);
//  mFreeCoef->setValue(freeCoef);
//}

//void HogWidget::setNlevels(int nlevels)
//{
//  const QSignalBlocker blockerNlevels(mNlevels);
//  mNlevels->setValue(nlevels);
//}

//void HogWidget::setSignedGradient(bool signedGradient)
//{
//  mSignedGradient->setChecked(signedGradient);
//}

void HogWidget::update()
{
}

void HogWidget::reset()
{
  const QSignalBlocker blockerWinSizeHeight(mWinSizeHeight);
  const QSignalBlocker blockerWinSizeWidth(mWinSizeWidth);
  const QSignalBlocker blockerBlockSizeX(mBlockSizeX);
  const QSignalBlocker blockerBlockSizeY(mBlockSizeY);
  const QSignalBlocker blockerBlockStrideX(mBlockStrideX);
  const QSignalBlocker blockerBlockStrideY(mBlockStrideY);
  const QSignalBlocker blockerCellSizeX(mCellSizeX);
  const QSignalBlocker blockerCellSizeY(mCellSizeY);
  const QSignalBlocker blockerNbins(mNbins);
  const QSignalBlocker blockerDerivAperture(mDerivAperture);
//  const QSignalBlocker blockerWinSigma(mWinSigma);
//  const QSignalBlocker blockerHistogramNormType(mHistogramNormType);
//  const QSignalBlocker blockerL2HysThreshold(mL2HysThreshold);
//  const QSignalBlocker blockerFreeCoef(mFreeCoef);
//  const QSignalBlocker blockerNlevels(mNlevels);

  mWinSizeWidth->setValue(64);
  mWinSizeHeight->setValue(128);
  mBlockSizeX->setValue(16);
  mBlockSizeY->setValue(16);
  mBlockStrideX->setValue(8);
  mBlockStrideY->setValue(8);
  mCellSizeX->setValue(8);
  mCellSizeY->setValue(8);
  mNbins->setValue(9);
  mDerivAperture->setValue(1);
//  mWinSigma->setValue(-1);
//  mHistogramNormType->setCurrentText("L2Hys");
//  mL2HysThreshold->setValue(0.2);
//  mGammaCorrection->setChecked(true);
//  mFreeCoef->setValue(-1.);
//  mNlevels->setValue(64);
//  mSignedGradient->setChecked(false);
}

void HogWidget::init()
{
  this->setWindowTitle("HOG");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("HOG Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Window Width:")), 0, 0);
  mWinSizeHeight->setRange(0, 10000);
  propertiesLayout->addWidget(mWinSizeHeight, 0, 1);
  propertiesLayout->addWidget(new QLabel(tr("Window Height:")), 0, 2);
  mWinSizeWidth->setRange(0, 10000);
  propertiesLayout->addWidget(mWinSizeWidth, 0, 3);

  propertiesLayout->addWidget(new QLabel(tr("Block Size X:")), 1, 0);
  mBlockSizeX->setRange(0, 10000);
  propertiesLayout->addWidget(mBlockSizeX, 1, 1);
  propertiesLayout->addWidget(new QLabel(tr("Block Size Y:")), 1, 2);
  mBlockSizeY->setRange(0, 10000);
  propertiesLayout->addWidget(mBlockSizeY, 1, 3);

  propertiesLayout->addWidget(new QLabel(tr("Block Stride X:")), 2, 0);
  mBlockStrideX->setRange(0, 10000);
  propertiesLayout->addWidget(mBlockStrideX, 2, 1);
  propertiesLayout->addWidget(new QLabel(tr("Block Stride Y:")), 2, 2);
  mBlockStrideY->setRange(0, 10000);
  propertiesLayout->addWidget(mBlockStrideY, 2, 3);

  propertiesLayout->addWidget(new QLabel(tr("Cell Size X:")), 3, 0);
  mCellSizeX->setRange(0, 10000);
  propertiesLayout->addWidget(mCellSizeX, 3, 1);
  propertiesLayout->addWidget(new QLabel(tr("Cell Size Y:")), 3, 2);
  mCellSizeY->setRange(0, 10000);
  propertiesLayout->addWidget(mCellSizeY, 3, 3);

  propertiesLayout->addWidget(new QLabel(tr("nbins:")), 4, 0);
  mNbins->setRange(0, 10000);
  propertiesLayout->addWidget(mNbins, 4, 1);

  propertiesLayout->addWidget(new QLabel(tr("derivAperture:")), 5, 0);
  mDerivAperture->setRange(0, 10000);
  propertiesLayout->addWidget(mDerivAperture, 5, 1);

//  propertiesLayout->addWidget(new QLabel(tr("winSigma:")), 6, 0);
//  mWinSigma->setRange(-1, 10000);
//  propertiesLayout->addWidget(mWinSigma, 6, 1);

//  propertiesLayout->addWidget(new QLabel(tr("Histogram Norm Type:")), 7, 0);
//  mHistogramNormType->addItem("L2Hys");  ///TODO: solo este tipo???
//  propertiesLayout->addWidget(mHistogramNormType, 7, 1);

//  propertiesLayout->addWidget(new QLabel(tr("L2Hys Threshold:")), 8, 0);
//  mL2HysThreshold->setRange(0., 100.);
//  propertiesLayout->addWidget(mL2HysThreshold, 8, 1);

//  mGammaCorrection->setText(tr("Gamma Correction:"));
//  propertiesLayout->addWidget(mGammaCorrection, 9, 1);

//  propertiesLayout->addWidget(new QLabel(tr("free_coef:")), 10, 0);
//  mFreeCoef->setRange(-1., 100.);
//  propertiesLayout->addWidget(mFreeCoef, 10, 1);

//  propertiesLayout->addWidget(new QLabel(tr("N Levels:")), 11, 0);
//  mNlevels->setRange(0, 100);
//  propertiesLayout->addWidget(mNlevels, 11, 1);

//  mSignedGradient->setText(tr("Signed Gradient:"));
//  propertiesLayout->addWidget(mSignedGradient, 12, 1);

  reset();

  update();
}

} // namespace photomatch

