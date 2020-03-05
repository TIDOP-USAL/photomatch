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


#include "DheWidget.h"

#include <QSpinBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

DheWidgetImp::DheWidgetImp(QWidget *parent)
  : DheWidget(parent),
    mX(new QSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
  this->retranslate();
}

DheWidgetImp::~DheWidgetImp()
{

}

int DheWidgetImp::x() const
{
  return mX->value();
}

void DheWidgetImp::setX(int x)
{
  const QSignalBlocker blockerX(mX);
  mX->setValue(x);
}

void DheWidgetImp::update()
{

}

void DheWidgetImp::retranslate()
{

}

void DheWidgetImp::reset()
{
  const QSignalBlocker blockerX(mX);

  mX->setValue(1);
}

void DheWidgetImp::initUI()
{
  this->setWindowTitle("DHE");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("DHE Parameters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout(groupBox);

  QLabel *lbl = new QLabel(tr("Dynamic Histogram Equalization"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  lbl->setFont(font);
  propertiesLayout->addWidget(lbl, 0, 0, 1, 2);

  propertiesLayout->addWidget(new QLabel(tr("x:")), 1, 0, 1, 1);
  mX->setRange(0, 5);
  propertiesLayout->addWidget(mX, 1, 1, 1, 1);

  reset(); /// set default values

  update();
}

void DheWidgetImp::initSignalAndSlots()
{
  connect(mX,    SIGNAL(valueChanged(int)),      this, SIGNAL(xChange(int)));
}


} // namespace photomatch


