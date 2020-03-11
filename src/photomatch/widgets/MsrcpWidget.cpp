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
#include <QApplication>

namespace photomatch
{

MsrcpWidgetImp::MsrcpWidgetImp(QWidget *parent)
  : MsrcpWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelDescription(new QLabel(this)),
    mGroupBoxBlocksize(new QGroupBox(this)),
    mLabelSmallScale(new QLabel(this)),
    mSmallScale(new QDoubleSpinBox(this)),
    mLabelMidScale(new QLabel(this)),
    mMidScale(new QDoubleSpinBox(this)),
    mLabelLargeScale(new QLabel(this)),
    mLargeScale(new QDoubleSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
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
  mGroupBox->setTitle(QApplication::translate("MsrcpWidgetImp", "MSRCP Parameters"));
  mLabelDescription->setText(QApplication::translate("MsrcpWidgetImp", "MultiScale Retinex with Chromaticity Preservation"));
  mGroupBoxBlocksize->setTitle(QApplication::translate("MsrcpWidgetImp", "Retinex Scales"));
  mLabelSmallScale->setText(QApplication::translate("MsrcpWidgetImp", "Small Scale:"));
  mLabelMidScale->setText(QApplication::translate("MsrcpWidgetImp", "Mid Scale:"));
  mLabelLargeScale->setText(QApplication::translate("MsrcpWidgetImp", "Large Scale:"));
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

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout(mGroupBox);

  mLabelDescription->setWordWrap(true);
  QFont font;
  font.setBold(true);
  mLabelDescription->setFont(font);
  propertiesLayout->addWidget(mLabelDescription, 0, 0);

  propertiesLayout->addWidget(mGroupBoxBlocksize, 1, 0);
  QGridLayout *propertiesLayoutBlocksize = new QGridLayout();
  mGroupBoxBlocksize->setLayout(propertiesLayoutBlocksize);

  propertiesLayoutBlocksize->addWidget(mLabelSmallScale, 0, 0);
  mSmallScale->setRange(0., 19.99);
  propertiesLayoutBlocksize->addWidget(mSmallScale, 0, 1);

  propertiesLayoutBlocksize->addWidget(mLabelMidScale, 1, 0);
  mMidScale->setRange(20., 199.99);
  propertiesLayoutBlocksize->addWidget(mMidScale, 1, 1);

  propertiesLayoutBlocksize->addWidget(mLabelLargeScale, 2, 0);
  mLargeScale->setRange(200., 256.);
  propertiesLayoutBlocksize->addWidget(mLargeScale, 2, 1);

  this->retranslate();
  this->reset(); // Set default values
  this->update();
}

void MsrcpWidgetImp::initSignalAndSlots()
{
  connect(mSmallScale,      SIGNAL(valueChanged(double)),     this, SIGNAL(smallScaleChange(double)));
  connect(mMidScale,        SIGNAL(valueChanged(double)),     this, SIGNAL(midScaleChange(double)));
  connect(mLargeScale,      SIGNAL(valueChanged(double)),     this, SIGNAL(largeScaleChange(double)));
}

void MsrcpWidgetImp::changeEvent(QEvent *event)
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



