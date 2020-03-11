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
#include <QApplication>

namespace photomatch
{

BoostWidgetImp::BoostWidgetImp(QWidget *parent)
  : BoostWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelDescriptorType(new QLabel(this)),
    mDescriptorType(new QComboBox(this)),
    mUseOrientation(new QCheckBox(this)),
    mScaleFactor(new QDoubleSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
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
  mGroupBox->setTitle(QApplication::translate("BoostWidgetImp", "BOOST Parameters", nullptr));
  mLabelDescriptorType->setText(QApplication::translate("BoostWidgetImp", "Descriptor Type:", nullptr));
  mUseOrientation->setText(QApplication::translate("BoostWidgetImp", "Use Keypoints Orientation"));

}

void BoostWidgetImp::reset()
{
  const QSignalBlocker blockerBytes(mDescriptorType);
  const QSignalBlocker blockerScaleFactor(mScaleFactor);
  
  mDescriptorType->setCurrentText("BINBOOST_256");
  mUseOrientation->setChecked(true);
  mScaleFactor->setValue(6.25);
}

void BoostWidgetImp::initUI()
{
  this->setWindowTitle("BOOST");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mLabelDescriptorType, 0, 0);
  mDescriptorType->addItem("BGM");
  mDescriptorType->addItem("BGM_HARD");
  mDescriptorType->addItem("BGM_BILINEAR");
  mDescriptorType->addItem("LBGM");
  mDescriptorType->addItem("BINBOOST_64");
  mDescriptorType->addItem("BINBOOST_128");
  mDescriptorType->addItem("BINBOOST_256");
  propertiesLayout->addWidget(mDescriptorType, 0, 1);

  propertiesLayout->addWidget(mUseOrientation, 1, 0);

  //propertiesLayout->addWidget(new QLabel(tr("Scale Factor:")), 2, 0);
  propertiesLayout->addWidget(mScaleFactor, 2, 1);
  mScaleFactor->setVisible(false); ///Se desactiva y se modifica internamente según el detector usado

  this->retranslate();
  this->reset();
  this->update();
}

void BoostWidgetImp::initSignalAndSlots()
{
  connect(mDescriptorType,    SIGNAL(currentTextChanged(QString)),   this, SIGNAL(descriptorTypeChange(QString)));
  connect(mUseOrientation,    SIGNAL(clicked(bool)),                 this, SIGNAL(useOrientationChange(bool)));
  connect(mScaleFactor,       SIGNAL(valueChanged(double)),          this, SIGNAL(scaleFactorChange(double)));
}

void BoostWidgetImp::changeEvent(QEvent *event)
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



