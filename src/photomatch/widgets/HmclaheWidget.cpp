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


#include "HmclaheWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

HmclaheWidgetImp::HmclaheWidgetImp(QWidget *parent)
  : HmclaheWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelDescription(new QLabel(this)),
    mGroupBoxBlocksize(new QGroupBox(this)),
    mLabelBlockSizeX(new QLabel(this)),
    mBlockSizeX(new QSpinBox(this)),
    mLabelBlockSizeY(new QLabel(this)),
    mBlockSizeY(new QSpinBox(this)),
    mLabelL(new QLabel(this)),
    mL(new QDoubleSpinBox(this)),
    mLabelPhi(new QLabel(this)),
    mPhi(new QDoubleSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

HmclaheWidgetImp::~HmclaheWidgetImp()
{

}

void HmclaheWidgetImp::onBlockSizeXChange(int blockSizeX)
{
  emit blockSizeChange(QSize(blockSizeX, mBlockSizeY->value()));
}

void HmclaheWidgetImp::onBlockSizeYChange(int blockSizeY)
{
  emit blockSizeChange(QSize(mBlockSizeX->value(), blockSizeY));
}

QSize HmclaheWidgetImp::blockSize() const
{
  return QSize(mBlockSizeX->value(), mBlockSizeY->value());
}

double HmclaheWidgetImp::l() const
{
  return mL->value();
}

double HmclaheWidgetImp::phi() const
{
  return mPhi->value();
}

void HmclaheWidgetImp::setBlockSize(const QSize &blockSize)
{
  const QSignalBlocker blockerTilesGridX(mBlockSizeX);
  const QSignalBlocker blockerTilesGridY(mBlockSizeY);
  mBlockSizeX->setValue(blockSize.width());
  mBlockSizeY->setValue(blockSize.height());
}

void HmclaheWidgetImp::setL(double l)
{
  const QSignalBlocker blockerL(mL);
  mL->setValue(static_cast<double>(l));
}

void HmclaheWidgetImp::setPhi(double phi)
{
  const QSignalBlocker blockerPhi(mPhi);
  mPhi->setValue(static_cast<double>(phi));
}

void HmclaheWidgetImp::update()
{
}

void HmclaheWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("HmclaheWidgetImp", "HMCLAHE Parameters"));
  mLabelDescription->setText(QApplication::translate("HmclaheWidgetImp", "Histogram Modified Contrast Limited Adaptive Histogram Equalization"));
  mGroupBoxBlocksize->setTitle(QApplication::translate("HmclaheWidgetImp", "Block Size", nullptr));
  mLabelBlockSizeX->setText(QApplication::translate("HmclaheWidgetImp", "Width:", nullptr));
  mLabelBlockSizeY->setText(QApplication::translate("HmclaheWidgetImp", "Height:", nullptr));
  mLabelL->setText(QApplication::translate("HmclaheWidgetImp", "L:", nullptr));
  mLabelPhi->setText(QApplication::translate("HmclaheWidgetImp", "K1:", nullptr));

//#ifndef QT_NO_WHATSTHIS
//  mL->setWhatsThis(tr("<html><head/><body><p>Use to district the range of histogram. Range between 0 and 1.</p></body></html>"));
//  mPhi->setWhatsThis(tr("<html><head/><body><p>Use to adjust the histogram. Range between 0 and 1.</p></body></html>"));
//  mBlockSizeX->setWhatsThis(tr("<html><head/><body><p><p>Block size X.</p></p></body></html>"));
//  mBlockSizeY->setWhatsThis(tr("<html><head/><body><p><p>Block size Y.</p></p></body></html>"));
//#endif // QT_NO_WHATSTHIS
}

void HmclaheWidgetImp::reset()
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

void HmclaheWidgetImp::initUI()
{
  this->setWindowTitle("HMCLAHE");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout(mGroupBox);

  mLabelDescription->setWordWrap(true);
  QFont font;
  font.setBold(true);
  mLabelDescription->setFont(font);
  propertiesLayout->addWidget(mLabelDescription, 0, 0, 1, 2);

  QGridLayout *propertiesLayoutBlocksize = new QGridLayout(mGroupBoxBlocksize);

  propertiesLayoutBlocksize->addWidget(mLabelBlockSizeX, 0, 0, 1, 1);
  mBlockSizeX->setRange(0, 1000);
  propertiesLayoutBlocksize->addWidget(mBlockSizeX, 0, 1, 1, 1);

  propertiesLayoutBlocksize->addWidget(mLabelBlockSizeY,  1, 0, 1, 1);
  mBlockSizeY->setRange(0, 1000);
  propertiesLayoutBlocksize->addWidget(mBlockSizeY, 1, 1, 1, 1);

  propertiesLayout->addWidget(mGroupBoxBlocksize, 1, 0, 1, 2);

  propertiesLayout->addWidget(mLabelL, 2, 0, 1, 1);
  mL->setRange(0., 1.);
  mL->setSingleStep(0.01);
  mL->setDecimals(2);
  propertiesLayout->addWidget(mL, 2, 1, 1, 1);

  propertiesLayout->addWidget(mLabelPhi, 3, 0, 1, 1);
  mPhi->setRange(0., 1.);
  mPhi->setSingleStep(0.1);
  mPhi->setDecimals(2);
  propertiesLayout->addWidget(mPhi, 3, 1, 1, 1);

  this->retranslate();
  this->reset(); // Set default values
  this->update();
}

void HmclaheWidgetImp::initSignalAndSlots()
{
  connect(mBlockSizeX,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeXChange(int)));
  connect(mBlockSizeY,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeYChange(int)));
  connect(mL,             SIGNAL(valueChanged(double)),     this, SIGNAL(lChange(double)));
  connect(mPhi,           SIGNAL(valueChanged(double)),     this, SIGNAL(phiChange(double)));
}

void HmclaheWidgetImp::changeEvent(QEvent *event)
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

