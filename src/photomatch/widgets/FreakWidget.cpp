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


#include "FreakWidget.h"

#include <QSpinBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

FreakWidgetImp::FreakWidgetImp(QWidget *parent)
  : FreakWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mOrientationNormalized(new QCheckBox(this)),
    mScaleNormalized(new QCheckBox(this)),
    mLabelPatternScale(new QLabel(this)),
    mPatternScale(new QDoubleSpinBox(this)),
    mLabelOctaves(new QLabel(this)),
    mOctaves(new QSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

FreakWidgetImp::~FreakWidgetImp()
{

}

void FreakWidgetImp::initUI()
{
  this->setWindowTitle("FREAK");
  this->setObjectName("FreakWidget");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mOrientationNormalized, 1, 0);

  propertiesLayout->addWidget(mScaleNormalized, 2, 0);

  propertiesLayout->addWidget(mLabelPatternScale, 3, 0);
  mPatternScale->setRange(0., 1000.);
  propertiesLayout->addWidget(mPatternScale, 3, 1);

  propertiesLayout->addWidget(mLabelOctaves, 4, 0);
  mOctaves->setRange(0, 100);
  propertiesLayout->addWidget(mOctaves, 4, 1);

  this->retranslate();
  this->reset(); // Set default values
  this->update();
}

void FreakWidgetImp::initSignalAndSlots()
{
  connect(mOrientationNormalized,  &QAbstractButton::clicked,                            this, &FreakWidget::orientationNormalizedChange);
  connect(mScaleNormalized,        &QAbstractButton::clicked,                            this, &FreakWidget::scaleNormalizedChange);
  connect(mPatternScale,           QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &FreakWidget::patternScaleChange);
  connect(mOctaves,                QOverload<int>::of(&QSpinBox::valueChanged),          this, &FreakWidget::octavesChange);
}

void FreakWidgetImp::reset()
{
  const QSignalBlocker blockerPatternScale(mPatternScale);
  const QSignalBlocker blockerOctaves(mOctaves);

  mOrientationNormalized->setChecked(true);
  mScaleNormalized->setChecked(true);
  mPatternScale->setValue(22.0);
  mOctaves->setValue(4);
}

void FreakWidgetImp::update()
{
}

void FreakWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("FreakWidget", "FREAK Parameters"));
  mOrientationNormalized->setText(QApplication::translate("FreakWidget", "Orientation Normalization"));
  mScaleNormalized->setText(QApplication::translate("FreakWidget", "Scale Normalization"));
  mLabelPatternScale->setText(QApplication::translate("FreakWidget", "Pattern Scale:"));
  mLabelOctaves->setText(QApplication::translate("FreakWidget", "Number of Octaves:"));
}

bool FreakWidgetImp::orientationNormalized() const
{
  return mOrientationNormalized->isChecked();
}

bool FreakWidgetImp::scaleNormalized() const
{
  return mScaleNormalized->isChecked();
}

double FreakWidgetImp::patternScale() const
{
  return mPatternScale->value();
}

int FreakWidgetImp::octaves() const
{
  return mOctaves->value();
}

void FreakWidgetImp::setOrientationNormalized(bool orientationNormalized)
{
  mOrientationNormalized->setChecked(orientationNormalized);
}

void FreakWidgetImp::setScaleNormalized(bool scaleNormalized)
{
  mScaleNormalized->setChecked(scaleNormalized);
}

void FreakWidgetImp::setPatternScale(double patternScale)
{
  const QSignalBlocker blockerPatternScale(mPatternScale);
  mPatternScale->setValue(patternScale);
}

void FreakWidgetImp::setOctaves(int octaves)
{
  const QSignalBlocker blockerOctaves(mOctaves);
  mOctaves->setValue(octaves);
}

} // namespace photomatch

