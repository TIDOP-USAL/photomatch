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


#include "LatchWidget.h"

#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

LatchWidgetImp::LatchWidgetImp(QWidget *parent)
  : LatchWidget(parent),
    mBytes(new QComboBox(this)),
    mRotationInvariance(new QCheckBox(this)),
    mHalfSsdSize(new QSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

LatchWidgetImp::~LatchWidgetImp()
{

}

QString LatchWidgetImp::bytes() const
{
  return mBytes->currentText();
}

bool LatchWidgetImp::rotationInvariance() const
{
  return mRotationInvariance->isChecked();
}

int LatchWidgetImp::halfSsdSize() const
{
  return mHalfSsdSize->value();
}

void LatchWidgetImp::setBytes(const QString &bytes)
{
  const QSignalBlocker blockerBytes(mBytes);
  mBytes->setCurrentText(bytes);
}

void LatchWidgetImp::setRotationInvariance(bool rotationInvariance)
{
  mRotationInvariance->setChecked(rotationInvariance);
}

void LatchWidgetImp::setHalfSsdSize(int halfSsdSize)
{
  const QSignalBlocker blockerHalfSsdSize(mHalfSsdSize);
  mHalfSsdSize->setValue(halfSsdSize);
}

void LatchWidgetImp::update()
{
}

void LatchWidgetImp::retranslate()
{

}

void LatchWidgetImp::reset()
{
  const QSignalBlocker blockerBytes(mBytes);
  const QSignalBlocker blockerHalfSsdSize(mHalfSsdSize);

  mBytes->setCurrentText("32");
  mRotationInvariance->setChecked(true);
  mHalfSsdSize->setValue(3);
}

void LatchWidgetImp::initUI()
{
  this->setWindowTitle("LATCH");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("LATCH Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Descriptor Bytes:")), 0, 0);
  mBytes->addItem("1");
  mBytes->addItem("2");
  mBytes->addItem("4");
  mBytes->addItem("8");
  mBytes->addItem("16");
  mBytes->addItem("32");
  mBytes->addItem("64");
  propertiesLayout->addWidget(mBytes, 0, 1);

  mRotationInvariance->setText(tr("Rotation Invariance"));
  propertiesLayout->addWidget(mRotationInvariance, 1, 0);

  propertiesLayout->addWidget(new QLabel(tr("Half of the mini-patches size:")), 2, 0);
  mHalfSsdSize->setRange(0, 100);
  propertiesLayout->addWidget(mHalfSsdSize, 2, 1);

  reset();

  update();
}

void LatchWidgetImp::initSignalAndSlots()
{
  connect(mBytes,               SIGNAL(currentTextChanged(QString)),  this, SIGNAL(bytesChange(QString)));
  connect(mRotationInvariance,  SIGNAL(clicked(bool)),                this, SIGNAL(rotationInvarianceChange(bool)));
  connect(mHalfSsdSize,         SIGNAL(valueChanged(int)),            this, SIGNAL(halfSsdSizeChange(int)));
}

} // namespace photomatch


