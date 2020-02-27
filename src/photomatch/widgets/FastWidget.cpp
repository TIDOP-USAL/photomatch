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


#include "FastWidget.h"

#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

FastWidgetImp::FastWidgetImp(QWidget *parent)
  : FastWidget(parent),
    mThreshold(new QSpinBox(this)),
    mNonmaxSuppression(new QCheckBox(this)),
    mDetectorType(new QComboBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

FastWidgetImp::~FastWidgetImp()
{
}

int FastWidgetImp::threshold() const
{
  return mThreshold->value();
}

bool FastWidgetImp::nonmaxSuppression() const
{
  return mNonmaxSuppression->isChecked();
}

QString FastWidgetImp::detectorType() const
{
  return mDetectorType->currentText();
}

void FastWidgetImp::setThreshold(int threshold)
{
  const QSignalBlocker blockerFastThreshold(mThreshold);
  mThreshold->setValue(threshold);
}

void FastWidgetImp::setNonmaxSuppression(bool nonmaxSuppression)
{
  mNonmaxSuppression->setChecked(nonmaxSuppression);
}

void FastWidgetImp::setDetectorType(QString detectorType)
{
  const QSignalBlocker blockerDetectorType(mDetectorType);
  mDetectorType->setCurrentText(detectorType);
}

void FastWidgetImp::update()
{
}

void FastWidgetImp::retranslate()
{

}

void FastWidgetImp::reset()
{
  const QSignalBlocker blockerFastThreshold(mThreshold);
  const QSignalBlocker blockerDetectorType(mDetectorType);

  mThreshold->setValue(10);
  mNonmaxSuppression->setChecked(true);
  mDetectorType->setCurrentText("TYPE_9_16");
}

void FastWidgetImp::initUI()
{
  this->setWindowTitle("FAST");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("FAST Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Threshold:")), 0, 0);
  mThreshold->setRange(0, 100);
  propertiesLayout->addWidget(mThreshold, 0, 1);

  mNonmaxSuppression->setText(tr("Nonmax Suppression"));
  propertiesLayout->addWidget(mNonmaxSuppression, 1, 0);

  propertiesLayout->addWidget(new QLabel(tr("Detector Type:")), 2, 0);
  mDetectorType->addItem("TYPE_5_8");
  mDetectorType->addItem("TYPE_7_12");
  mDetectorType->addItem("TYPE_9_16");
  propertiesLayout->addWidget(mDetectorType, 2, 1);

  reset();

  update();
}

void FastWidgetImp::initSignalAndSlots()
{
  connect(mThreshold,          SIGNAL(valueChanged(int)),            this, SIGNAL(thresholdChange(int)));
  connect(mNonmaxSuppression,  SIGNAL(clicked(bool)),                this, SIGNAL(nonmaxSuppressionChange(bool)));
  connect(mDetectorType,       SIGNAL(currentTextChanged(QString)),  this, SIGNAL(detectorTypeChange(QString)));
}

} // namespace photomatch
