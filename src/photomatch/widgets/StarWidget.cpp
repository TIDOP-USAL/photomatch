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


void StarWidgetImp::initUI()
{
  this->setWindowTitle("STAR");
  this->setObjectName("StarWidget");

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
  connect(mMaxSize,                 QOverload<int>::of(&QSpinBox::valueChanged),  this, &StarWidget::maxSizeChange);
  connect(mResponseThreshold,       QOverload<int>::of(&QSpinBox::valueChanged),  this, &StarWidget::responseThresholdChange);
  connect(mLineThresholdProjected,  QOverload<int>::of(&QSpinBox::valueChanged),  this, &StarWidget::lineThresholdProjectedChange);
  connect(mLineThresholdBinarized,  QOverload<int>::of(&QSpinBox::valueChanged),  this, &StarWidget::lineThresholdBinarizedChange);
  connect(mSuppressNonmaxSize,      QOverload<int>::of(&QSpinBox::valueChanged),  this, &StarWidget::suppressNonmaxSizeChange);
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

void StarWidgetImp::update()
{
}

void StarWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("StarWidget", "STAR Parameters"));
  mLabelMaxSize->setText(QApplication::translate("StarWidget", "Max Size:"));
  mLabelResponseThreshold->setText(QApplication::translate("StarWidget", "Response Threshold:"));
  mLabelLineThresholdProjected->setText(QApplication::translate("StarWidget", "Line Threshold Projected:"));
  mLabelLineThresholdBinarized->setText(QApplication::translate("StarWidget", "Line Threshold Binarized:"));
  mLabelSuppressNonmaxSize->setText(QApplication::translate("StarWidget", "Suppress Nonmax Size:"));
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



} // namespace photomatch



