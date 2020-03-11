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
#include <QApplication>

namespace photomatch
{

DheWidgetImp::DheWidgetImp(QWidget *parent)
  : DheWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelDescription(new QLabel(this)),
    mLabelX(new QLabel(this)),
    mX(new QSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
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
  mGroupBox->setTitle(QApplication::translate("DheWidgetImp", "DHE Parameters"));
  mLabelDescription->setText(QApplication::translate("DheWidgetImp", "Dynamic Histogram Equalization"));
  mLabelX->setText(QApplication::translate("DheWidgetImp", "x:"));
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

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout(mGroupBox);

  mLabelDescription->setWordWrap(true);
  QFont font;
  font.setBold(true);
  mLabelDescription->setFont(font);
  propertiesLayout->addWidget(mLabelDescription, 0, 0, 1, 2);

  propertiesLayout->addWidget(mLabelX, 1, 0, 1, 1);
  mX->setRange(0, 5);
  propertiesLayout->addWidget(mX, 1, 1, 1, 1);

  this->retranslate();
  this->reset(); /// set default values
  this->update();
}

void DheWidgetImp::initSignalAndSlots()
{
  connect(mX,    SIGNAL(valueChanged(int)),      this, SIGNAL(xChange(int)));
}

void DheWidgetImp::changeEvent(QEvent *event)
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


