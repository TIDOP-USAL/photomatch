/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#include "HogWidget.h"

#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

HogWidgetImp::HogWidgetImp(QWidget *parent)
  : HogWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelWinSizeHeight(new QLabel(this)),
    mWinSizeHeight(new QSpinBox(this)),
    mLabelWinSizeWidth(new QLabel(this)),
    mWinSizeWidth(new QSpinBox(this)),
    mLabelBlockSizeX(new QLabel(this)),
    mBlockSizeX(new QSpinBox(this)),
    mLabelBlockSizeY(new QLabel(this)),
    mBlockSizeY(new QSpinBox(this)),
    mLabelBlockStrideX(new QLabel(this)),
    mBlockStrideX(new QSpinBox(this)),
    mLabelBlockStrideY(new QLabel(this)),
    mBlockStrideY(new QSpinBox(this)),
    mLabelCellSizeX(new QLabel(this)),
    mCellSizeX(new QSpinBox(this)),
    mLabelCellSizeY(new QLabel(this)),
    mCellSizeY(new QSpinBox(this)),
    mLabelNbins(new QLabel(this)),
    mNbins(new QSpinBox(this)),
    mLabelDerivAperture(new QLabel(this)),
    mDerivAperture(new QSpinBox(this))/*,
    mWinSigma(new QDoubleSpinBox(this)),
    mHistogramNormType(new QComboBox(this)),
    mL2HysThreshold(new QDoubleSpinBox(this)),
    mGammaCorrection(new QCheckBox(this)),
    mFreeCoef(new QDoubleSpinBox(this)),
    mNlevels(new QSpinBox(this)),
    mSignedGradient(new QCheckBox(this))*/
{
  this->initUI();
  this->initSignalAndSlots();
}

HogWidgetImp::~HogWidgetImp()
{

}

void HogWidgetImp::onWinSizeHeightChange(int height)
{
  emit winSizeChange(QSize(mWinSizeWidth->value(), height));
}

void HogWidgetImp::onWinSizeWidthChange(int width)
{
  emit winSizeChange(QSize(width, mWinSizeHeight->value()));
}

void HogWidgetImp::onBlockSizeXChange(int blockSizeX)
{
  emit blockSizeChange(QSize(blockSizeX,mBlockSizeY->value()));
}

void HogWidgetImp::onBlockSizeYChange(int blockSizeY)
{
  emit blockSizeChange(QSize(mBlockSizeX->value(),blockSizeY));
}

void HogWidgetImp::onBlockStrideXChange(int blockStrideX)
{
  emit blockStrideChange(QSize(blockStrideX,mBlockStrideY->value()));
}

void HogWidgetImp::onBlockStrideYChange(int blockStrideY)
{
  emit blockStrideChange(QSize(mBlockStrideX->value(),blockStrideY));
}

void HogWidgetImp::onCellSizeXChange(int cellSizeX)
{
  emit cellSizeChange(QSize(cellSizeX,mCellSizeY->value()));
}

void HogWidgetImp::onCellSizeYChange(int cellSizeY)
{
  emit cellSizeChange(QSize(mCellSizeX->value(),cellSizeY));
}


QSize HogWidgetImp::winSize() const
{
  return QSize(mWinSizeWidth->value(), mWinSizeHeight->value());
}

QSize HogWidgetImp::blockSize() const
{
  return QSize(mBlockSizeX->value(), mBlockSizeY->value());
}

QSize HogWidgetImp::blockStride() const
{
  return QSize(mBlockStrideX->value(), mBlockStrideY->value());
}

QSize HogWidgetImp::cellSize() const
{
  return QSize(mCellSizeX->value(), mCellSizeY->value());
}

int HogWidgetImp::nbins() const
{
  return mNbins->value();
}

int HogWidgetImp::derivAperture() const
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

void HogWidgetImp::setWinSize(const QSize &winSize)
{
  const QSignalBlocker blockerWinSizeHeight(mWinSizeHeight);
  const QSignalBlocker blockerWinSizeWidth(mWinSizeWidth);
  mWinSizeHeight->setValue(winSize.height());
  mWinSizeWidth->setValue(winSize.width());
}

void HogWidgetImp::setBlockSize(const QSize &blockSize)
{
  const QSignalBlocker blockerBlockSizeX(mBlockSizeX);
  const QSignalBlocker blockerBlockSizeY(mBlockSizeY);
  mBlockSizeX->setValue(blockSize.width());
  mBlockSizeY->setValue(blockSize.height());
}

void HogWidgetImp::setBlockStride(const QSize &blockStride)
{
  const QSignalBlocker blockerBlockStrideX(mBlockStrideX);
  const QSignalBlocker blockerBlockStrideY(mBlockStrideY);
  mBlockStrideX->setValue(blockStride.width());
  mBlockStrideY->setValue(blockStride.height());
}

void HogWidgetImp::setCellSize(const QSize &cellSize)
{
  const QSignalBlocker blockerCellSizeX(mCellSizeX);
  const QSignalBlocker blockerCellSizeY(mCellSizeY);
  mCellSizeX->setValue(cellSize.width());
  mCellSizeY->setValue(cellSize.height());
}

void HogWidgetImp::setNbins(int nbins)
{
  const QSignalBlocker blockerNbins(mNbins);
  mNbins->setValue(nbins);
}

void HogWidgetImp::setDerivAperture(int derivAperture)
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

void HogWidgetImp::update()
{
}

void HogWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("HogWidgetImp", "HOG Parameters"));
  mLabelWinSizeHeight->setText(QApplication::translate("HogWidgetImp", "Window Height:"));
  mLabelWinSizeWidth->setText(QApplication::translate("HogWidgetImp", "Window Width:"));
  mLabelBlockSizeX->setText(QApplication::translate("HogWidgetImp", "Block Size X:"));
  mLabelBlockSizeY->setText(QApplication::translate("HogWidgetImp", "Block Size Y:"));
  mLabelBlockStrideX->setText(QApplication::translate("HogWidgetImp", "Block Stride X:"));
  mLabelBlockStrideY->setText(QApplication::translate("HogWidgetImp", "Block Stride Y:"));
  mLabelCellSizeX->setText(QApplication::translate("HogWidgetImp", "Cell Size X:"));
  mLabelCellSizeY->setText(QApplication::translate("HogWidgetImp", "Cell Size Y:"));
  mLabelNbins->setText(QApplication::translate("HogWidgetImp", "nbins:"));
  mLabelDerivAperture->setText(QApplication::translate("HogWidgetImp", "DerivAperture:"));
}

void HogWidgetImp::reset()
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

void HogWidgetImp::initUI()
{
  this->setWindowTitle("HOG");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mLabelWinSizeHeight, 0, 0);
  mWinSizeHeight->setRange(0, 10000);
  propertiesLayout->addWidget(mWinSizeHeight, 0, 1);
  propertiesLayout->addWidget(mLabelWinSizeWidth, 0, 2);
  mWinSizeWidth->setRange(0, 10000);
  propertiesLayout->addWidget(mWinSizeWidth, 0, 3);

  propertiesLayout->addWidget(mLabelBlockSizeX, 1, 0);
  mBlockSizeX->setRange(0, 10000);
  propertiesLayout->addWidget(mBlockSizeX, 1, 1);
  propertiesLayout->addWidget(mLabelBlockSizeY, 1, 2);
  mBlockSizeY->setRange(0, 10000);
  propertiesLayout->addWidget(mBlockSizeY, 1, 3);

  propertiesLayout->addWidget(mLabelBlockStrideX, 2, 0);
  mBlockStrideX->setRange(0, 10000);
  propertiesLayout->addWidget(mBlockStrideX, 2, 1);
  propertiesLayout->addWidget(mLabelBlockStrideY, 2, 2);
  mBlockStrideY->setRange(0, 10000);
  propertiesLayout->addWidget(mBlockStrideY, 2, 3);

  propertiesLayout->addWidget(mLabelCellSizeX, 3, 0);
  mCellSizeX->setRange(0, 10000);
  propertiesLayout->addWidget(mCellSizeX, 3, 1);
  propertiesLayout->addWidget(mLabelCellSizeY, 3, 2);
  mCellSizeY->setRange(0, 10000);
  propertiesLayout->addWidget(mCellSizeY, 3, 3);

  propertiesLayout->addWidget(mLabelNbins, 4, 0);
  mNbins->setRange(0, 10000);
  propertiesLayout->addWidget(mNbins, 4, 1);

  propertiesLayout->addWidget(mLabelDerivAperture, 5, 0);
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

  this->retranslate();
  this->reset(); // Set default values
  this->update();
}

void HogWidgetImp::initSignalAndSlots()
{
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

void HogWidgetImp::changeEvent(QEvent *event)
{
  QWidget::changeEvent(event);
  switch (event->type()) {
    case QEvent::LanguageChange:
      this->retranslate();
      break;
    default:
      break;
  }
}

} // namespace photomatch

