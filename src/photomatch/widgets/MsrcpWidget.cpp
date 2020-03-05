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


#include "MsrcpWidget.h"

#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

MsrcpWidgetImp::MsrcpWidgetImp(QWidget *parent)
  : MsrcpWidget(parent),
    mSmallScale(new QDoubleSpinBox(this)),
    mMidScale(new QDoubleSpinBox(this)),
    mLargeScale(new QDoubleSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
  this->retranslate();
}

double MsrcpWidgetImp::smallScale() const
{
  return mSmallScale->value();
}

double MsrcpWidgetImp::midScale() const
{
  return mMidScale->value();
}

double MsrcpWidgetImp::largeScale() const
{
  return mLargeScale->value();
}

void MsrcpWidgetImp::setSmallScale(double smallScale)
{
  const QSignalBlocker blockerSmallScale(mSmallScale);
  mSmallScale->setValue(smallScale);
}

void MsrcpWidgetImp::setMidScale(double midScale)
{
  const QSignalBlocker blockerMidScale(mMidScale);
  mMidScale->setValue(midScale);
}

void MsrcpWidgetImp::setLargeScale(double largeScale)
{
  const QSignalBlocker blockerLargeScale(mLargeScale);
  mLargeScale->setValue(largeScale);
}

void MsrcpWidgetImp::update()
{
}

void MsrcpWidgetImp::retranslate()
{

}

void MsrcpWidgetImp::reset()
{
  const QSignalBlocker blockerSmallScale(mSmallScale);
  const QSignalBlocker blockerMidScale(mMidScale);
  const QSignalBlocker blockerLargeScale(mLargeScale);

  mSmallScale->setValue(10.);
  mMidScale->setValue(100.);
  mLargeScale->setValue(220.);

}

void MsrcpWidgetImp::initUI()
{
  this->setWindowTitle("MSRCP");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("MSRCP Parameters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout(groupBox);

  QLabel *lbl = new QLabel(tr("MultiScale Retinex with Chromaticity Preservation"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  lbl->setFont(font);
  propertiesLayout->addWidget(lbl, 0, 0);

  QGroupBox *groupBoxBlocksize = new QGroupBox(tr("Retinex Scales"), this);
  propertiesLayout->addWidget(groupBoxBlocksize, 1, 0);
  QGridLayout *propertiesLayoutBlocksize = new QGridLayout();
  groupBoxBlocksize->setLayout(propertiesLayoutBlocksize);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Small Scale:")), 0, 0);
  mSmallScale->setRange(0., 19.99);
  propertiesLayoutBlocksize->addWidget(mSmallScale, 0, 1);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Mid Scale:")), 1, 0);
  mMidScale->setRange(20., 199.99);
  propertiesLayoutBlocksize->addWidget(mMidScale, 1, 1);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Large Scale:")), 2, 0);
  mLargeScale->setRange(200., 256.);
  propertiesLayoutBlocksize->addWidget(mLargeScale, 2, 1);

  reset();
  update();
}

void MsrcpWidgetImp::initSignalAndSlots()
{
  connect(mSmallScale,      SIGNAL(valueChanged(double)),     this, SIGNAL(smallScaleChange(double)));
  connect(mMidScale,        SIGNAL(valueChanged(double)),     this, SIGNAL(midScaleChange(double)));
  connect(mLargeScale,      SIGNAL(valueChanged(double)),     this, SIGNAL(largeScaleChange(double)));
}

} // namespace photomatch



