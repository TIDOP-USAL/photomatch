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


#include "LssWidget.h"


#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

LssWidgetImp::LssWidgetImp(QWidget *parent)
  : LssWidget (parent)
{
  this->initUI();
  this->initSignalAndSlots();
}

LssWidgetImp::~LssWidgetImp()
{

}

void LssWidgetImp::initSignalAndSlots()
{

}

void LssWidgetImp::initUI()
{
  this->setWindowTitle("LSS");
}

void LssWidgetImp::reset()
{
}

void LssWidgetImp::update()
{
}

void LssWidgetImp::retranslate()
{

}


} // namespace photomatch



