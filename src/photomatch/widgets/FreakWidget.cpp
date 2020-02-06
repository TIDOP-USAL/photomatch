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

namespace photomatch
{

FreakWidgetImp::FreakWidgetImp(QWidget *parent)
  : FreakWidget(parent),
    mOrientationNormalized(new QCheckBox(this)),
    mScaleNormalized(new QCheckBox(this)),
    mPatternScale(new QDoubleSpinBox(this)),
    mOctaves(new QSpinBox(this))
{
  init();

  /// Signals and slots
  connect(mOrientationNormalized,  SIGNAL(clicked(bool)),                this, SIGNAL(orientationNormalizedChange(bool)));
  connect(mScaleNormalized,        SIGNAL(clicked(bool)),                this, SIGNAL(scaleNormalizedChange(bool)));
  connect(mPatternScale,           SIGNAL(valueChanged(double)),         this, SIGNAL(patternScaleChange(double)));
  connect(mOctaves,                SIGNAL(valueChanged(int)),            this, SIGNAL(octavesChange(int)));
}

FreakWidgetImp::~FreakWidgetImp()
{

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

void FreakWidgetImp::update()
{
}

void FreakWidgetImp::retranslate()
{

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

void FreakWidgetImp::init()
{
  this->setWindowTitle("FREAK");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("FREAK Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  mOrientationNormalized->setText(tr("Orientation Normalization"));
  propertiesLayout->addWidget(mOrientationNormalized, 1, 0);

  mScaleNormalized->setText(tr("Scale Normalization"));
  propertiesLayout->addWidget(mScaleNormalized, 2, 0);

  propertiesLayout->addWidget(new QLabel(tr("Pattern Scale:")), 3, 0);
  mPatternScale->setRange(0., 1000.);
  propertiesLayout->addWidget(mPatternScale, 3, 1);

  propertiesLayout->addWidget(new QLabel(tr("Number of Octaves:")), 4, 0);
  mOctaves->setRange(0, 100);
  propertiesLayout->addWidget(mOctaves, 4, 1);

  reset(); /// set default values

  update();
}

} // namespace photomatch

