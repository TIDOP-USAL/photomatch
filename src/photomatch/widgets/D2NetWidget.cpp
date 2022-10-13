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


#include "D2NetWidget.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

D2NetWidgetImp::D2NetWidgetImp(QWidget *parent)
  : D2NetWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mCheckBoxMultiscale(new QCheckBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

D2NetWidgetImp::~D2NetWidgetImp()
{

}

void D2NetWidgetImp::initUI()
{
  this->setWindowTitle("D2Net");
  this->setObjectName("D2NetWidget");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mCheckBoxMultiscale, 0, 0);

  this->retranslate();
  this->reset();  /// set default values
  this->update();
}

void D2NetWidgetImp::initSignalAndSlots()
{
  connect(mCheckBoxMultiscale, &QAbstractButton::clicked, this, &D2NetWidget::multiscaleChange);
}

void D2NetWidgetImp::reset()
{
  const QSignalBlocker blocker(mCheckBoxMultiscale);

  mCheckBoxMultiscale->setChecked(false);
}

void D2NetWidgetImp::update()
{

}

void D2NetWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("D2NetWidget", "D2Net Parameters", nullptr));
  mCheckBoxMultiscale->setText(QApplication::translate("D2NetWidget", "Multiscale", nullptr));
}

bool D2NetWidgetImp::multiscale() const
{
  return mCheckBoxMultiscale->isChecked();
}

void D2NetWidgetImp::setMultiscale(bool multiscale)
{
  mCheckBoxMultiscale->setChecked(multiscale);
}

} // namespace photomatch



