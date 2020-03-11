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


#include "DecolorWidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

DecolorWidgetImp::DecolorWidgetImp(QWidget *parent)
  : DecolorWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelDescription(new QLabel(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

DecolorWidgetImp::~DecolorWidgetImp()
{

}

void DecolorWidgetImp::update()
{
}

void DecolorWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("DecolorWidgetImp", "Decolorization Parameters"));
  mLabelDescription->setText(QApplication::translate("DecolorWidgetImp", "Contrast Preserving Decolorization"));
}

void DecolorWidgetImp::reset()
{
}

void DecolorWidgetImp::initUI()
{
  this->setWindowTitle("Decolorization");

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

  this->retranslate();
  this->reset(); // Set default values
  this->update();
}

void DecolorWidgetImp::initSignalAndSlots()
{

}

void DecolorWidgetImp::changeEvent(QEvent *event)
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



