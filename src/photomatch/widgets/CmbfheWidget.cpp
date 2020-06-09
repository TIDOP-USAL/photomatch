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


#include "CmbfheWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

CmbfheWidgetImp::CmbfheWidgetImp(QWidget *parent)
  : CmbfheWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelDescription(new QLabel(this)),
    mGroupBoxBlocksize(new QGroupBox(this)),
    mLabelBlockSizeX(new QLabel(this)),
    mBlockSizeX(new QSpinBox(this)),
    mLabelBlockSizeY(new QLabel(this)),
    mBlockSizeY(new QSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

CmbfheWidgetImp::~CmbfheWidgetImp()
{

}

void CmbfheWidgetImp::initUI()
{
  this->setWindowTitle("CMBFHE");
  this->setObjectName("CmbfheWidget");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  mLabelDescription->setWordWrap(true);
  QFont font;
  font.setBold(true);
  mLabelDescription->setFont(font);
  propertiesLayout->addWidget(mLabelDescription, 0, 0);

  propertiesLayout->addWidget(mGroupBoxBlocksize, 1, 0);
  QGridLayout *propertiesLayoutBlocksize = new QGridLayout();
  mGroupBoxBlocksize->setLayout(propertiesLayoutBlocksize);

  propertiesLayoutBlocksize->addWidget(mLabelBlockSizeX, 0, 0);
  mBlockSizeX->setRange(0, 1000);
  propertiesLayoutBlocksize->addWidget(mBlockSizeX, 0, 1);

  propertiesLayoutBlocksize->addWidget(mLabelBlockSizeY, 1, 0);
  mBlockSizeY->setRange(0, 1000);
  propertiesLayoutBlocksize->addWidget(mBlockSizeY, 1, 1);

  this->retranslate();
  this->reset();  /// set default values
  this->update();
}

void CmbfheWidgetImp::initSignalAndSlots()
{
  connect(mBlockSizeX,  QOverload<int>::of(&QSpinBox::valueChanged),  this, &CmbfheWidgetImp::onBlockSizeXChange);
  connect(mBlockSizeY,  QOverload<int>::of(&QSpinBox::valueChanged),  this, &CmbfheWidgetImp::onBlockSizeYChange);
}

void CmbfheWidgetImp::reset()
{
  const QSignalBlocker blockerBlockSizeX(mBlockSizeX);
  const QSignalBlocker blockerBlockSizeY(mBlockSizeY);

  mBlockSizeX->setValue(11);
  mBlockSizeY->setValue(11);
}

void CmbfheWidgetImp::update()
{
}

void CmbfheWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("CmbfheWidget", "CMBFHE Parameters"));
  mLabelDescription->setText(QApplication::translate("CmbfheWidget", "Cascaded Multistep Binomial Filtering Histogram Equalization", nullptr));
  mGroupBoxBlocksize->setTitle(QApplication::translate("CmbfheWidget", "Block Size"));
  mLabelBlockSizeX->setText(QApplication::translate("CmbfheWidget", "Width:"));
  mLabelBlockSizeY->setText(QApplication::translate("CmbfheWidget", "Height:"));
}

void CmbfheWidgetImp::onBlockSizeXChange(int blockSizeX)
{
  emit blockSizeChange(QSize(blockSizeX, mBlockSizeY->value()));
}

void CmbfheWidgetImp::onBlockSizeYChange(int blockSizeY)
{
  emit blockSizeChange(QSize(mBlockSizeX->value(), blockSizeY));
}

QSize CmbfheWidgetImp::blockSize() const
{
  return QSize(mBlockSizeX->value(), mBlockSizeY->value());
}

void CmbfheWidgetImp::setBlockSize(const QSize &blockSize)
{
  const QSignalBlocker blockerTilesGridX(mBlockSizeX);
  const QSignalBlocker blockerTilesGridY(mBlockSizeY);
  mBlockSizeX->setValue(blockSize.width());
  mBlockSizeY->setValue(blockSize.height());
}

} // namespace photomatch


