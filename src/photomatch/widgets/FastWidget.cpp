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
#include <QApplication>

namespace photomatch
{

FastWidgetImp::FastWidgetImp(QWidget *parent)
  : FastWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelThreshold(new QLabel(this)),
    mThreshold(new QSpinBox(this)),
    mNonmaxSuppression(new QCheckBox(this)),
    mLabelDetectorType(new QLabel(this)),
    mDetectorType(new QComboBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

FastWidgetImp::~FastWidgetImp()
{
}

void FastWidgetImp::initUI()
{
  this->setWindowTitle("FAST");
  this->setObjectName("FastWidget");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mLabelThreshold, 0, 0);
  mThreshold->setRange(0, 100);
  propertiesLayout->addWidget(mThreshold, 0, 1);

  propertiesLayout->addWidget(mNonmaxSuppression, 1, 0);

  propertiesLayout->addWidget(mLabelDetectorType, 2, 0);
  mDetectorType->addItem("TYPE_5_8");
  mDetectorType->addItem("TYPE_7_12");
  mDetectorType->addItem("TYPE_9_16");
  propertiesLayout->addWidget(mDetectorType, 2, 1);

  this->retranslate();
  this->reset(); // Set default values
  this->update();
}

void FastWidgetImp::initSignalAndSlots()
{
  connect(mThreshold,          QOverload<int>::of(&QSpinBox::valueChanged), this, &FastWidget::thresholdChange);
  connect(mNonmaxSuppression,  &QAbstractButton::clicked,                   this, &FastWidget::nonmaxSuppressionChange);
  connect(mDetectorType,       &QComboBox::currentTextChanged,              this, &FastWidget::detectorTypeChange);
}

void FastWidgetImp::reset()
{
  const QSignalBlocker blockerFastThreshold(mThreshold);
  const QSignalBlocker blockerDetectorType(mDetectorType);

  mThreshold->setValue(10);
  mNonmaxSuppression->setChecked(true);
  mDetectorType->setCurrentText("TYPE_9_16");
}

void FastWidgetImp::update()
{
}

void FastWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("FastWidget", "FAST Parameters"));
  mLabelThreshold->setText(QApplication::translate("FastWidget", "Threshold:"));
  mNonmaxSuppression->setText(QApplication::translate("FastWidget", "Nonmax Suppression"));
  mLabelDetectorType->setText(QApplication::translate("FastWidget", "Detector Type:"));
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

} // namespace photomatch
