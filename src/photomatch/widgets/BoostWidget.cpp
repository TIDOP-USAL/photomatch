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


#include "BoostWidget.h"

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QDoubleSpinBox>

namespace photomatch
{

BoostWidgetImp::BoostWidgetImp(QWidget *parent)
  : BoostWidget(parent),
    mDescriptorType(new QComboBox(this)),
    mUseOrientation(new QCheckBox(this)),
    mScaleFactor(new QDoubleSpinBox(this))
{
  init();

  /// Signals and slots
  connect(mDescriptorType,    SIGNAL(currentTextChanged(QString)),   this, SIGNAL(descriptorTypeChange(QString)));
  connect(mUseOrientation,    SIGNAL(clicked(bool)),                 this, SIGNAL(useOrientationChange(bool)));
  connect(mScaleFactor,       SIGNAL(valueChanged(double)),          this, SIGNAL(scaleFactorChange(double)));
}

BoostWidgetImp::~BoostWidgetImp()
{

}

QString BoostWidgetImp::descriptorType() const
{
  return mDescriptorType->currentText();
}

bool BoostWidgetImp::useOrientation() const
{
  return mUseOrientation->isChecked();
}

double BoostWidgetImp::scaleFactor() const
{
  return mScaleFactor->value();
}

void BoostWidgetImp::setDescriptorType(const QString &descriptorType)
{
  const QSignalBlocker blockerBytes(mDescriptorType);
  mDescriptorType->setCurrentText(descriptorType);
}

void BoostWidgetImp::setUseOrientation(bool useOrientation)
{
  mUseOrientation->setChecked(useOrientation);
}

void BoostWidgetImp::setScaleFactor(double scaleFactor)
{
  const QSignalBlocker blockerScaleFactor(mScaleFactor);
  mScaleFactor->setValue(scaleFactor);
}

void BoostWidgetImp::update()
{
}

void BoostWidgetImp::retranslate()
{

}

void BoostWidgetImp::reset()
{
  const QSignalBlocker blockerBytes(mDescriptorType);
  const QSignalBlocker blockerScaleFactor(mScaleFactor);
  
  mDescriptorType->setCurrentText("BINBOOST_256");
  mUseOrientation->setChecked(true);
  mScaleFactor->setValue(6.25);
}

void BoostWidgetImp::init()
{
  this->setWindowTitle("BOOST");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("BOOST Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Descriptor Type:")), 0, 0);
  mDescriptorType->addItem("BGM");
  mDescriptorType->addItem("BGM_HARD");
  mDescriptorType->addItem("BGM_BILINEAR");
  mDescriptorType->addItem("LBGM");
  mDescriptorType->addItem("BINBOOST_64");
  mDescriptorType->addItem("BINBOOST_128");
  mDescriptorType->addItem("BINBOOST_256");
  propertiesLayout->addWidget(mDescriptorType, 0, 1);

  mUseOrientation->setText(tr("Use Keypoints Orientation"));
  propertiesLayout->addWidget(mUseOrientation, 1, 0);

  //propertiesLayout->addWidget(new QLabel(tr("Scale Factor:")), 2, 0);
  propertiesLayout->addWidget(mScaleFactor, 2, 1);
  mScaleFactor->setVisible(false); ///Se desactiva y se modifica internamente según el detector usado

  reset();

  update();
}

} // namespace photomatch


