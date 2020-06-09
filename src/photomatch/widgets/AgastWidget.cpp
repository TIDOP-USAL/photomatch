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


#include "AgastWidget.h"

#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

AgastWidgetImp::AgastWidgetImp(QWidget *parent)
  : AgastWidget(parent),
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

AgastWidgetImp::~AgastWidgetImp()
{

}

void AgastWidgetImp::initUI()
{
  this->setWindowTitle("AGAST");
  this->setObjectName("AgastWidget");

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
  mDetectorType->addItem("AGAST_5_8");
  mDetectorType->addItem("AGAST_7_12d");
  mDetectorType->addItem("AGAST_7_12s");
  mDetectorType->addItem("OAST_9_16");
  propertiesLayout->addWidget(mDetectorType, 2, 1);

  this->retranslate();
  this->reset(); /// set default values
  this->update();
}

void AgastWidgetImp::initSignalAndSlots()
{
  connect(mThreshold,          QOverload<int>::of(&QSpinBox::valueChanged), this, &AgastWidget::thresholdChange);
  connect(mNonmaxSuppression,  &QAbstractButton::clicked,                   this, &AgastWidget::nonmaxSuppressionChange);
  connect(mDetectorType,       &QComboBox::currentTextChanged,              this, &AgastWidget::detectorTypeChange);
}

void AgastWidgetImp::reset()
{
  const QSignalBlocker blockerFastThreshold(mThreshold);
  const QSignalBlocker blockerDetectorType(mDetectorType);

  mThreshold->setValue(10);
  mNonmaxSuppression->setChecked(true);
  mDetectorType->setCurrentText("OAST_9_16");
}

void AgastWidgetImp::update()
{

}

void AgastWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("AgastWidget", "AGAST Parameters", nullptr));
  mLabelThreshold->setText(QApplication::translate("AgastWidget", "Threshold:", nullptr));
  mNonmaxSuppression->setText(QApplication::translate("AgastWidget", "Nonmax Suppression:", nullptr));
  mLabelDetectorType->setText(QApplication::translate("AgastWidget", "Detector Type:", nullptr));
}

int AgastWidgetImp::threshold() const
{
  return mThreshold->value();
}

bool AgastWidgetImp::nonmaxSuppression() const
{
  return mNonmaxSuppression->isChecked();
}

QString AgastWidgetImp::detectorType() const
{
  return mDetectorType->currentText();
}

void AgastWidgetImp::setThreshold(int threshold)
{
  const QSignalBlocker blockerFastThreshold(mThreshold);
  mThreshold->setValue(threshold);
}

void AgastWidgetImp::setNonmaxSuppression(bool nonmaxSuppression)
{
  mNonmaxSuppression->setChecked(nonmaxSuppression);
}

void AgastWidgetImp::setDetectorType(const QString &detectorType)
{
  const QSignalBlocker blockerDetectorType(mDetectorType);
  mDetectorType->setCurrentText(detectorType);
}

} // namespace photomatch


