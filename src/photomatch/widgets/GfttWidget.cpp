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


#include "GfttWidget.h"

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

GfttWidgetImp::GfttWidgetImp(QWidget *parent)
  : GfttWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelMaxFeatures(new QLabel(this)),
    mMaxFeatures(new QSpinBox(this)),
    mLabelQualityLevel(new QLabel(this)),
    mQualityLevel(new QDoubleSpinBox(this)),
    mLabelMinDistance(new QLabel(this)),
    mMinDistance(new QDoubleSpinBox(this)),
    mLabelBlockSize(new QLabel(this)),
    mBlockSize(new QSpinBox(this)),
    mHarrisDetector(new QCheckBox(this)),
    mLabelK(new QLabel(this)),
    mK(new QDoubleSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

GfttWidgetImp::~GfttWidgetImp()
{

}

int GfttWidgetImp::maxFeatures() const
{
  return mMaxFeatures->value();
}

double GfttWidgetImp::qualityLevel() const
{
  return mQualityLevel->value();
}

double GfttWidgetImp::minDistance() const
{
  return mMinDistance->value();
}

int GfttWidgetImp::blockSize() const
{
  return mBlockSize->value();
}

bool GfttWidgetImp::harrisDetector() const
{
  return mHarrisDetector->isChecked();
}

double GfttWidgetImp::k() const
{
  return mK->value();
}

void GfttWidgetImp::setMaxFeatures(int maxFeatures)
{
  const QSignalBlocker blocker(mMaxFeatures);
  mMaxFeatures->setValue(maxFeatures);
}

void GfttWidgetImp::setQualityLevel(double qlevel)
{
  const QSignalBlocker blocker(mQualityLevel);
  mQualityLevel->setValue(qlevel);
}

void GfttWidgetImp::setMinDistance(double minDistance)
{
  const QSignalBlocker blocker(mMinDistance);
  mMinDistance->setValue(minDistance);
}

void GfttWidgetImp::setBlockSize(int blockSize)
{
  const QSignalBlocker blocker(mBlockSize);
  mBlockSize->setValue(blockSize);
}

void GfttWidgetImp::setHarrisDetector(bool value)
{
  mHarrisDetector->setChecked(value);
}

void GfttWidgetImp::setK(double k)
{
  const QSignalBlocker blocker(mK);
  mK->setValue(k);
}

void GfttWidgetImp::update()
{
}

void GfttWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("GfttWidgetImp", "GFTT Parameters"));
  mLabelMaxFeatures->setText(QApplication::translate("GfttWidgetImp", "Max Features:"));
  mLabelQualityLevel->setText(QApplication::translate("GfttWidgetImp", "Quality Level:"));
  mLabelMinDistance->setText(QApplication::translate("GfttWidgetImp", "Min Distance:"));
  mLabelBlockSize->setText(QApplication::translate("GfttWidgetImp", "Block Size:"));
  mHarrisDetector->setText(QApplication::translate("GfttWidgetImp", "Harris Detector"));
  mLabelK->setText(QApplication::translate("GfttWidgetImp", "K:"));
}

void GfttWidgetImp::reset()
{
  const QSignalBlocker blocker1(mMaxFeatures);
  const QSignalBlocker blocker2(mQualityLevel);
  const QSignalBlocker blocker3(mMinDistance);
  const QSignalBlocker blocker4(mBlockSize);
  const QSignalBlocker blocker5(mK);

  mMaxFeatures->setValue(1000);
  mQualityLevel->setValue(0.01);
  mMinDistance->setValue(1);
  mBlockSize->setValue(3);
  mHarrisDetector->setChecked(false);
  mK->setValue(0.04);
}

void GfttWidgetImp::initUI()
{
  this->setWindowTitle("GFTT");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mLabelMaxFeatures, 0, 0);
  mMaxFeatures->setRange(0, 1000000);
  propertiesLayout->addWidget(mMaxFeatures, 0, 1);

  propertiesLayout->addWidget(mLabelQualityLevel, 1, 0);
  mQualityLevel->setRange(0., 100.);
  mQualityLevel->setSingleStep(0.01);
  propertiesLayout->addWidget(mQualityLevel, 1, 1);

  propertiesLayout->addWidget(mLabelMinDistance, 2, 0);
  mMinDistance->setRange(0., 10000.);
  propertiesLayout->addWidget(mMinDistance, 2, 1);

  propertiesLayout->addWidget(mLabelBlockSize, 3, 0);
  mBlockSize->setRange(0, 100);
  propertiesLayout->addWidget(mBlockSize, 3, 1);


  propertiesLayout->addWidget(mHarrisDetector, 4, 0);

  propertiesLayout->addWidget(mLabelK, 5, 0);
  mK->setRange(0., 100.);
  mK->setSingleStep(0.01);
  propertiesLayout->addWidget(mK, 5, 1);

  this->retranslate();
  this->reset(); // Set default values
  this->update();
}

void GfttWidgetImp::initSignalAndSlots()
{
  connect(mMaxFeatures,       SIGNAL(valueChanged(int)),      this, SIGNAL(maxFeaturesChange(int)));
  connect(mQualityLevel,      SIGNAL(valueChanged(double)),   this, SIGNAL(qualityLevelChange(double)));
  connect(mMinDistance,       SIGNAL(valueChanged(double)),   this, SIGNAL(minDistanceChange(double)));
  connect(mBlockSize,         SIGNAL(valueChanged(int)),      this, SIGNAL(blockSizeChange(int)));
  connect(mHarrisDetector,    SIGNAL(clicked(bool)),          this, SIGNAL(harrisDetectorChange(bool)));
  connect(mK,                 SIGNAL(valueChanged(double)),   this, SIGNAL(kChange(double)));
}

void GfttWidgetImp::changeEvent(QEvent *event)
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
