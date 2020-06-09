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


#include "AcebsfWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

AcebsfWidgetImp::AcebsfWidgetImp(QWidget *parent)
  : AcebsfWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelDescription(new QLabel(this)),
    mGroupBoxBlocksize(new QGroupBox(this)),
    mLabelBlockSizeX(new QLabel(this)),
    mBlockSizeX(new QSpinBox(this)),
    mLabelBlockSizeY(new QLabel(this)),
    mBlockSizeY(new QSpinBox(this)),
    mLabelL(new QLabel(this)),
    mL(new QDoubleSpinBox(this)),
    mLabelK1(new QLabel(this)),
    mK1(new QDoubleSpinBox(this)),
    mLabelK2(new QLabel(this)),
    mK2(new QDoubleSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

AcebsfWidgetImp::~AcebsfWidgetImp()
{

}

void AcebsfWidgetImp::initUI()
{
  this->setWindowTitle("ACEBSF");
  this->setObjectName("AcebsfWidget");

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

  propertiesLayout->addWidget(mGroupBoxBlocksize, 1, 0, 1, 2);
  QGridLayout *propertiesLayoutBlocksize = new QGridLayout();
  mGroupBoxBlocksize->setLayout(propertiesLayoutBlocksize);

  propertiesLayoutBlocksize->addWidget(mLabelBlockSizeX, 0, 0);
  mBlockSizeX->setRange(0, 100);
  propertiesLayoutBlocksize->addWidget(mBlockSizeX, 0, 1);

  propertiesLayoutBlocksize->addWidget(mLabelBlockSizeY, 1, 0);
  mBlockSizeY->setRange(0, 100);
  propertiesLayoutBlocksize->addWidget(mBlockSizeY, 1, 1);

  propertiesLayout->addWidget(mLabelL, 2, 0);
  mL->setRange(0, 1);
  mL->setSingleStep(0.01);
  propertiesLayout->addWidget(mL, 2, 1);

  propertiesLayout->addWidget(mLabelK1, 3, 0);
  mK1->setRange(1, 100);
  propertiesLayout->addWidget(mK1, 3, 1);

  propertiesLayout->addWidget(mLabelK2, 4, 0);
  mK2->setRange(0, 1);
  mK2->setSingleStep(0.01);
  propertiesLayout->addWidget(mK2, 4, 1);

  this->retranslate();
  this->reset(); // Set default values
  this->update();
}

void AcebsfWidgetImp::initSignalAndSlots()
{
  connect(mBlockSizeX,  QOverload<int>::of(&QSpinBox::valueChanged),          this, &AcebsfWidgetImp::onBlockSizeXChange);
  connect(mBlockSizeY,  QOverload<int>::of(&QSpinBox::valueChanged),          this, &AcebsfWidgetImp::onBlockSizeYChange);
  connect(mL,           QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &AcebsfWidget::lChange);
  connect(mK1,          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &AcebsfWidget::k1Change);
  connect(mK2,          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &AcebsfWidget::k2Change);
}

void AcebsfWidgetImp::reset()
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

void AcebsfWidgetImp::update()
{
}

void AcebsfWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("AcebsfWidget", "ACEBSF Parameters", nullptr));
  mLabelDescription->setText(QApplication::translate("AcebsfWidget", "Adaptive Contrast Enhancement Based on modified Sigmoid Function", nullptr));
  mGroupBoxBlocksize->setTitle(QApplication::translate("AcebsfWidget", "Block Size", nullptr));
  mLabelBlockSizeX->setText(QApplication::translate("AcebsfWidget", "Width:", nullptr));
  mLabelBlockSizeY->setText(QApplication::translate("AcebsfWidget", "Height:", nullptr));
  mLabelL->setText(QApplication::translate("AcebsfWidget", "L:", nullptr));
  mLabelK1->setText(QApplication::translate("AcebsfWidget", "K1:", nullptr));
  mLabelK2->setText(QApplication::translate("AcebsfWidget", "K2:", nullptr));
}

void AcebsfWidgetImp::onBlockSizeXChange(int blockSizeX)
{
  emit blockSizeChange(QSize(blockSizeX, mBlockSizeY->value()));
}

void AcebsfWidgetImp::onBlockSizeYChange(int blockSizeY)
{
  emit blockSizeChange(QSize(mBlockSizeX->value(), blockSizeY));
}

QSize AcebsfWidgetImp::blockSize() const
{
  return QSize(mBlockSizeX->value(), mBlockSizeY->value());
}

double AcebsfWidgetImp::l() const
{
  return mL->value();
}

double AcebsfWidgetImp::k1() const
{
  return mK1->value();
}

double AcebsfWidgetImp::k2() const
{
  return mK2->value();
}

void AcebsfWidgetImp::setBlockSize(const QSize &blockSize)
{
  const QSignalBlocker blockerTilesGridX(mBlockSizeX);
  const QSignalBlocker blockerTilesGridY(mBlockSizeY);
  mBlockSizeX->setValue(blockSize.width());
  mBlockSizeY->setValue(blockSize.height());
}

void AcebsfWidgetImp::setL(double l)
{
  const QSignalBlocker blockerL(mL);
  mL->setValue(l);
}

void AcebsfWidgetImp::setK1(double k1)
{
  const QSignalBlocker blockerK1(mK1);
  mK1->setValue(k1);
}

void AcebsfWidgetImp::setK2(double k2)
{
  const QSignalBlocker blockerK2(mK2);
  mK2->setValue(k2);
}

} // namespace photomatch



