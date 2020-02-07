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

namespace photomatch
{

BriefWidgetImp::BriefWidgetImp(QWidget *parent)
  : BriefWidget(parent),
    mBytes(new QComboBox(this)),
    mUseOrientation(new QCheckBox(this))
{
  init();

  /// Signals and slots
  connect(mBytes,             SIGNAL(currentTextChanged(QString)),   this, SIGNAL(bytesChange(QString)));
  connect(mUseOrientation,    SIGNAL(clicked(bool)),                 this, SIGNAL(useOrientationChange(bool)));
}

BriefWidgetImp::~BriefWidgetImp()
{

}

QString BriefWidgetImp::bytes() const
{
  return mBytes->currentText();
}

bool BriefWidgetImp::useOrientation() const
{
  return mUseOrientation->isChecked();
}

void BriefWidgetImp::setBytes(const QString &bytes)
{
  const QSignalBlocker blockerBytes(mBytes);
  mBytes->setCurrentText(bytes);
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

}

void BriefWidgetImp::reset()
{
  const QSignalBlocker blockerBytes(mBytes);

  mBytes->setCurrentText("32");
  mUseOrientation->setChecked(false);
}

void BriefWidgetImp::init()
{
  this->setWindowTitle("BRIEF");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("BRIEF Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Descriptor Bytes:")), 0, 0);
  mBytes->addItem("16");
  mBytes->addItem("32");
  mBytes->addItem("64");
  propertiesLayout->addWidget(mBytes, 0, 1);

  mUseOrientation->setText(tr("Use Keypoints Orientation"));
  propertiesLayout->addWidget(mUseOrientation, 1, 0);

  reset();

  update();
}

} // namespace photomatch


