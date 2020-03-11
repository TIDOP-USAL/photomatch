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


#include "BriskWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

BriskWidgetImp::BriskWidgetImp(QWidget *parent)
  : BriskWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelThreshold(new QLabel(this)),
    mThreshold(new QSpinBox(this)),
    mLabelOctaves(new QLabel(this)),
    mOctaves(new QSpinBox(this)),
    mLabelPatternScale(new QLabel(this)),
    mPatternScale(new QDoubleSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

BriskWidgetImp::~BriskWidgetImp()
{

}

int BriskWidgetImp::threshold() const
{
  return mThreshold->value();
}

int BriskWidgetImp::octaves() const
{
  return mOctaves->value();
}

double BriskWidgetImp::patternScale() const
{
  return mPatternScale->value();
}

void BriskWidgetImp::setThreshold(int threshold)
{
  const QSignalBlocker blockerThreshold(mThreshold);
  mThreshold->setValue(threshold);
}

void BriskWidgetImp::setOctaves(int octaves)
{
  const QSignalBlocker blockerOctaves(mOctaves);
  mOctaves->setValue(octaves);
}

void BriskWidgetImp::setPatternScale(double patternScale)
{
  const QSignalBlocker blockerPatternScale(mPatternScale);
  mPatternScale->setValue(patternScale);
}

void BriskWidgetImp::update()
{
}

void BriskWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("BriskWidgetImp", "BRISK Parameters"));
  mLabelThreshold->setText(QApplication::translate("BriskWidgetImp", "Threshold:"));
  mLabelOctaves->setText(QApplication::translate("BriskWidgetImp", "Octaves:"));
  mLabelPatternScale->setText(QApplication::translate("BriskWidgetImp", "Pattern Scale:"));
}

void BriskWidgetImp::reset()
{
  const QSignalBlocker blockerThreshold(mThreshold);
  const QSignalBlocker blockerOctaves(mOctaves);
  const QSignalBlocker blockerPatternScale(mPatternScale);

  mThreshold->setValue(30);
  mOctaves->setValue(3);
  mPatternScale->setValue(1.0);
}

void BriskWidgetImp::initUI()
{
  this->setWindowTitle("BRISK");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mLabelThreshold, 0, 0);
  mThreshold->setRange(0, 100);
  propertiesLayout->addWidget(mThreshold, 0, 1);

  propertiesLayout->addWidget(mLabelOctaves, 1, 0);
  mOctaves->setRange(0, 100);
  propertiesLayout->addWidget(mOctaves, 1, 1);

  propertiesLayout->addWidget(mLabelPatternScale, 2, 0);
  mPatternScale->setRange(0., 10000.);
  propertiesLayout->addWidget(mPatternScale, 2, 1);

  this->retranslate();
  this->reset(); // set default values
  this->update();
}

void BriskWidgetImp::initSignalAndSlots()
{
  connect(mThreshold,        SIGNAL(valueChanged(int)),        this, SIGNAL(thresholdChange(int)));
  connect(mOctaves,          SIGNAL(valueChanged(int)),        this, SIGNAL(octavesChange(int)));
  connect(mPatternScale,     SIGNAL(valueChanged(double)),     this, SIGNAL(patternScaleChange(double)));
}

void BriskWidgetImp::changeEvent(QEvent *event)
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


