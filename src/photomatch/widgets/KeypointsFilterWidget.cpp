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


#include "KeypointsFilterWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>

namespace photomatch
{

KeypointsFilterWidgetImp::KeypointsFilterWidgetImp(QWidget *parent)
  : KeypointsFilterWidget(parent),
    mCheckBoxPointsNumber(new QCheckBox(this)),
    mPointsNumber(new QSpinBox(this)),
    mCheckBoxSize(new QCheckBox(this)),
    mMinSize(new QDoubleSpinBox(this)),
    mMaxSize(new QDoubleSpinBox(this)),
    mCheckBoxRemoveDuplicated(new QCheckBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

KeypointsFilterWidgetImp::~KeypointsFilterWidgetImp()
{
}

int KeypointsFilterWidgetImp::nPoints() const
{
  return mPointsNumber->value();
}

double KeypointsFilterWidgetImp::minSize() const
{
  return mMinSize->value();
}

double KeypointsFilterWidgetImp::maxSize() const
{
  return mMaxSize->value();
}

bool KeypointsFilterWidgetImp::isActiveFilterBest() const
{
  return bActiveFilterBest;
}

bool KeypointsFilterWidgetImp::isActiveFilterSize() const
{
  return bActiveFilterSize;
}

bool KeypointsFilterWidgetImp::isActiveRemoveDuplicated() const
{
  return bActiveRemoveDuplicated;
}

void KeypointsFilterWidgetImp::setNPoints(int nPoints)
{
  const QSignalBlocker blockerNPoints(mPointsNumber);
  mPointsNumber->setValue(nPoints);
}

void KeypointsFilterWidgetImp::setMinSize(double minSize)
{
  const QSignalBlocker blockerMinSize(mMinSize);
  mMinSize->setValue(minSize);
  update();
}

void KeypointsFilterWidgetImp::setMaxSize(double maxSize)
{
  const QSignalBlocker blockerMaxSizee(mMaxSize);
  mMaxSize->setValue(maxSize);
  update();
}

void KeypointsFilterWidgetImp::setActiveFilterBest(bool active)
{
  mCheckBoxPointsNumber->setChecked(active);
  update();
}

void KeypointsFilterWidgetImp::setActiveFilterSize(bool active)
{
  mCheckBoxSize->setChecked(active);
  update();
}

void KeypointsFilterWidgetImp::setActiveRemoveDuplicated(bool active)
{
  mCheckBoxRemoveDuplicated->setChecked(active);
  update();
}

void KeypointsFilterWidgetImp::update()
{
  bActiveFilterBest = mCheckBoxPointsNumber->isChecked();
  bActiveFilterSize = mCheckBoxSize->isChecked();
  bActiveRemoveDuplicated = mCheckBoxRemoveDuplicated->isChecked();
  mPointsNumber->setEnabled(bActiveFilterBest);
  mMinSize->setEnabled(bActiveFilterSize);
  mMaxSize->setEnabled(bActiveFilterSize);

  mMaxSize->setMinimum(mMinSize->value());
  mMinSize->setMaximum(mMaxSize->value());
}

void KeypointsFilterWidgetImp::retranslate()
{

}

void KeypointsFilterWidgetImp::reset()
{
  const QSignalBlocker blockerNPoints(mPointsNumber);
  const QSignalBlocker blockerMinSize(mMinSize);
  const QSignalBlocker blockerMaxSizee(mMaxSize);

  mCheckBoxPointsNumber->setChecked(false);
  mPointsNumber->setValue(10000);
  mCheckBoxSize->setChecked(false);
  mMinSize->setValue(0.);
  mMaxSize->setValue(50.);
  mCheckBoxRemoveDuplicated->setChecked(false);

  update();
}

void KeypointsFilterWidgetImp::initUI()
{
  this->setWindowTitle("Keypoints Filter");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("Keypoints Filters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  groupBox->setLayout(propertiesLayout);

  mCheckBoxPointsNumber->setText(tr("N Best"));
  mCheckBoxPointsNumber->setChecked(false);
  propertiesLayout->addWidget(mCheckBoxPointsNumber, 0, 0, 1, 1);

  mPointsNumber->setRange(0, 100000);
  propertiesLayout->addWidget(mPointsNumber, 0, 1, 1, 4);

  mCheckBoxSize->setText(tr("Keypoints Size"));
  mCheckBoxSize->setChecked(false);
  propertiesLayout->addWidget(mCheckBoxSize, 1, 0, 1, 1);

  propertiesLayout->addWidget(new QLabel(tr("Min:")), 1, 1, 1, 1);
  mMinSize->setRange(0., 49.);
  mMinSize->setSingleStep(0.01);
  mMinSize->setDecimals(3);
  propertiesLayout->addWidget(mMinSize, 1, 2, 1, 1);

  propertiesLayout->addWidget(new QLabel(tr("Max:")), 1, 3, 1, 1);
  mMaxSize->setRange(50., 10000.);
  mMaxSize->setSingleStep(0.01);
  mMaxSize->setDecimals(3);
  propertiesLayout->addWidget(mMaxSize, 1, 4, 1, 1);

  mCheckBoxRemoveDuplicated->setText(tr("Remove duplicated keypoints"));
  propertiesLayout->addWidget(mCheckBoxRemoveDuplicated, 2, 0, 1, 4);

  reset();
}

void KeypointsFilterWidgetImp::initSignalAndSlots()
{
  connect(mCheckBoxPointsNumber,     SIGNAL(clicked(bool)),            this, SLOT(update()));
  connect(mCheckBoxSize,             SIGNAL(clicked(bool)),            this, SLOT(update()));
  connect(mCheckBoxRemoveDuplicated, SIGNAL(clicked(bool)),            this, SLOT(update()));
  connect(mMinSize,                  SIGNAL(valueChanged(double)),     this, SLOT(update()));
  connect(mMaxSize,                  SIGNAL(valueChanged(double)),     this, SLOT(update()));

  connect(mPointsNumber,  SIGNAL(valueChanged(int)),        this, SIGNAL(nPointsChange(int)));
  connect(mMinSize,       SIGNAL(valueChanged(double)),     this, SIGNAL(minSizeChange(double)));
  connect(mMaxSize,       SIGNAL(valueChanged(double)),     this, SIGNAL(maxSizeChange(double)));
}

} // namespace photomatch


