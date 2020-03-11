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


#include "StarWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

StarWidgetImp::StarWidgetImp(QWidget *parent)
  : StarWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelMaxSize(new QLabel(this)),
    mMaxSize(new QSpinBox(this)),
    mLabelResponseThreshold(new QLabel(this)),
    mResponseThreshold(new QSpinBox(this)),
    mLabelLineThresholdProjected(new QLabel(this)),
    mLineThresholdProjected(new QSpinBox(this)),
    mLabelLineThresholdBinarized(new QLabel(this)),
    mLineThresholdBinarized(new QSpinBox(this)),
    mLabelSuppressNonmaxSize(new QLabel(this)),
    mSuppressNonmaxSize(new QSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

StarWidgetImp::~StarWidgetImp()
{

}

int StarWidgetImp::maxSize() const
{
  return mMaxSize->value();
}

int StarWidgetImp::responseThreshold() const
{
  return mResponseThreshold->value();
}

int StarWidgetImp::lineThresholdProjected() const
{
  return mLineThresholdProjected->value();
}

int StarWidgetImp::lineThresholdBinarized() const
{
  return mLineThresholdBinarized->value();
}

int StarWidgetImp::suppressNonmaxSize() const
{
  return mSuppressNonmaxSize->value();
}

void StarWidgetImp::setMaxSize(int maxSize)
{
  const QSignalBlocker blockerMaxSize(mMaxSize);
  mMaxSize->setValue(maxSize);
}

void StarWidgetImp::setResponseThreshold(int responseThreshold)
{
  const QSignalBlocker blockerResponseThreshold(mResponseThreshold);
  mResponseThreshold->setValue(responseThreshold);
}

void StarWidgetImp::setLineThresholdProjected(int lineThresholdProjected)
{
  const QSignalBlocker blockerLineThresholdProjected(mLineThresholdProjected);
  mLineThresholdProjected->setValue(lineThresholdProjected);
}

void StarWidgetImp::setLineThresholdBinarized(int lineThresholdBinarized)
{
  const QSignalBlocker blockerLineThresholdBinarized(mLineThresholdBinarized);
  mLineThresholdBinarized->setValue(lineThresholdBinarized);
}

void StarWidgetImp::setSuppressNonmaxSize(int suppressNonmaxSize)
{
  const QSignalBlocker blockerSuppressNonmaxSize(mSuppressNonmaxSize);
  mSuppressNonmaxSize->setValue(suppressNonmaxSize);
}

void StarWidgetImp::update()
{
}

void StarWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("StarWidgetImp", "STAR Parameters"));
  mLabelMaxSize->setText(QApplication::translate("StarWidgetImp", "Max Size:"));
  mLabelResponseThreshold->setText(QApplication::translate("StarWidgetImp", "Response Threshold:"));
  mLabelLineThresholdProjected->setText(QApplication::translate("StarWidgetImp", "Line Threshold Projected:"));
  mLabelLineThresholdBinarized->setText(QApplication::translate("StarWidgetImp", "Line Threshold Binarized:"));
  mLabelSuppressNonmaxSize->setText(QApplication::translate("StarWidgetImp", "Suppress Nonmax Size:"));
}

void StarWidgetImp::reset()
{
  const QSignalBlocker blockerMaxSize(mMaxSize);
  const QSignalBlocker blockerResponseThreshold(mResponseThreshold);
  const QSignalBlocker blockerLineThresholdProjected(mLineThresholdProjected);
  const QSignalBlocker blockerLineThresholdBinarized(mLineThresholdBinarized);
  const QSignalBlocker blockerSuppressNonmaxSize(mSuppressNonmaxSize);

  mMaxSize->setValue(45);
  mResponseThreshold->setValue(30);
  mLineThresholdProjected->setValue(10);
  mLineThresholdBinarized->setValue(8);
  mSuppressNonmaxSize->setValue(5);
}

void StarWidgetImp::initUI()
{
  this->setWindowTitle("STAR");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mLabelMaxSize, 0, 0);
  mMaxSize->setRange(0, 100);
  propertiesLayout->addWidget(mMaxSize, 0, 1);

  propertiesLayout->addWidget(mLabelResponseThreshold, 1, 0);
  mResponseThreshold->setRange(0, 100);
  propertiesLayout->addWidget(mResponseThreshold, 1, 1);

  propertiesLayout->addWidget(mLabelLineThresholdProjected, 2, 0);
  mLineThresholdProjected->setRange(0, 100);
  propertiesLayout->addWidget(mLineThresholdProjected, 2, 1);

  propertiesLayout->addWidget(mLabelLineThresholdBinarized, 3, 0);
  mLineThresholdBinarized->setRange(0, 100);
  propertiesLayout->addWidget(mLineThresholdBinarized, 3, 1);

  propertiesLayout->addWidget(mLabelSuppressNonmaxSize, 4, 0);
  mSuppressNonmaxSize->setRange(0, 100);
  propertiesLayout->addWidget(mSuppressNonmaxSize, 4, 1);

  this->retranslate();
  this->reset(); /// set default values
  this->update();
}

void StarWidgetImp::initSignalAndSlots()
{
  connect(mMaxSize,                    SIGNAL(valueChanged(int)),            this, SIGNAL(maxSizeChange(int)));
  connect(mResponseThreshold,          SIGNAL(valueChanged(int)),            this, SIGNAL(responseThresholdChange(int)));
  connect(mLineThresholdProjected,     SIGNAL(valueChanged(int)),            this, SIGNAL(lineThresholdProjectedChange(int)));
  connect(mLineThresholdBinarized,     SIGNAL(valueChanged(int)),            this, SIGNAL(lineThresholdBinarizedChange(int)));
  connect(mSuppressNonmaxSize,         SIGNAL(valueChanged(int)),            this, SIGNAL(suppressNonmaxSizeChange(int)));
}

void StarWidgetImp::changeEvent(QEvent *event)
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



