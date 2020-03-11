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


#include "BriefWidget.h"

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

BriefWidgetImp::BriefWidgetImp(QWidget *parent)
  : BriefWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelDescriptorBytes(new QLabel(this)),
    mDescriptorBytes(new QComboBox(this)),
    mUseOrientation(new QCheckBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

BriefWidgetImp::~BriefWidgetImp()
{

}

QString BriefWidgetImp::bytes() const
{
  return mDescriptorBytes->currentText();
}

bool BriefWidgetImp::useOrientation() const
{
  return mUseOrientation->isChecked();
}

void BriefWidgetImp::setBytes(const QString &bytes)
{
  const QSignalBlocker blockerBytes(mDescriptorBytes);
  mDescriptorBytes->setCurrentText(bytes);
}

void BriefWidgetImp::setUseOrientation(bool useOrientation)
{
  mUseOrientation->setChecked(useOrientation);
}

void BriefWidgetImp::update()
{
}

void BriefWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("BriefWidgetImp", "BRIEF Parameters"));
  mLabelDescriptorBytes->setText(QApplication::translate("BriefWidgetImp", "Descriptor Bytes:"));
  mUseOrientation->setText(QApplication::translate("BriefWidgetImp", "Use Keypoints Orientation"));
}

void BriefWidgetImp::reset()
{
  const QSignalBlocker blockerBytes(mDescriptorBytes);

  mDescriptorBytes->setCurrentText("32");
  mUseOrientation->setChecked(false);
}

void BriefWidgetImp::initUI()
{
  this->setWindowTitle("BRIEF");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mLabelDescriptorBytes, 0, 0);
  mDescriptorBytes->addItem("16");
  mDescriptorBytes->addItem("32");
  mDescriptorBytes->addItem("64");
  propertiesLayout->addWidget(mDescriptorBytes, 0, 1);

  propertiesLayout->addWidget(mUseOrientation, 1, 0);

  this->retranslate();
  this->reset();  /// set default values
  this->update();
}

void BriefWidgetImp::initSignalAndSlots()
{
  connect(mDescriptorBytes, SIGNAL(currentTextChanged(QString)), this, SIGNAL(bytesChange(QString)));
  connect(mUseOrientation,  SIGNAL(clicked(bool)),               this, SIGNAL(useOrientationChange(bool)));
}

void BriefWidgetImp::changeEvent(QEvent *event)
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




