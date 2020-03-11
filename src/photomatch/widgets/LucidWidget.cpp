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


#include "LucidWidget.h"


#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

LucidWidgetImp::LucidWidgetImp(QWidget *parent)
  : LucidWidget (parent),
    mGroupBox(new QGroupBox(this)),
    mLabelLucidKernel(new QLabel(this)),
    mLucidKernel(new QSpinBox(this)),
    mLabelBlurKernel(new QLabel(this)),
    mBlurKernel(new QSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

LucidWidgetImp::~LucidWidgetImp()
{

}

int LucidWidgetImp::lucidKernel() const
{
  return mLucidKernel->value();
}

int LucidWidgetImp::blurKernel() const
{
  return mBlurKernel->value();
}

void LucidWidgetImp::setLucidKernel(int lucidKernel)
{
  const QSignalBlocker blockerLucidKernel(mLucidKernel);
  mLucidKernel->setValue(lucidKernel);
}

void LucidWidgetImp::setBlurKernel(int blurKernel)
{
  const QSignalBlocker blockerBlurKernel(mBlurKernel);
  mBlurKernel->setValue(blurKernel);
}

void LucidWidgetImp::update()
{
}

void LucidWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("LucidWidgetImp", "LUCID Parameters"));
  mLabelLucidKernel->setText(QApplication::translate("LucidWidgetImp", "Lucid Kernel:"));
  mLabelBlurKernel->setText(QApplication::translate("LucidWidgetImp", "Blur Kernel:"));
}

void LucidWidgetImp::reset()
{
  const QSignalBlocker blockerLucidKernel(mLucidKernel);
  const QSignalBlocker blockerBlurKernel(mBlurKernel);

  mLucidKernel->setValue(1);
  mBlurKernel->setValue(2);
}

void LucidWidgetImp::initUI()
{
  this->setWindowTitle("LUCID");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mLabelLucidKernel, 0, 0);
  mLucidKernel->setRange(0, 100);
  propertiesLayout->addWidget(mLucidKernel, 0, 1);

  propertiesLayout->addWidget(mLabelBlurKernel, 1, 0);
  mBlurKernel->setRange(0, 100);
  propertiesLayout->addWidget(mBlurKernel, 1, 1);

  this->retranslate();
  this->reset(); // Set default values
  this->update();
}

void LucidWidgetImp::initSignalAndSlots()
{
  connect(mLucidKernel,  SIGNAL(valueChanged(int)),  this, SIGNAL(lucidKernelChange(int)));
  connect(mBlurKernel,   SIGNAL(valueChanged(int)),  this, SIGNAL(blurKernelChange(int)));
}

void LucidWidgetImp::changeEvent(QEvent *event)
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



