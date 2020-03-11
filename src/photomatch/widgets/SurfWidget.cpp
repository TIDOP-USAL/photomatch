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


#include "SurfWidget.h"

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

SurfWidgetImp::SurfWidgetImp(QWidget *parent)
  : SurfWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelHessianThreshold(new QLabel(this)),
    mHessianThreshold(new QDoubleSpinBox(this)),
    mLabelOctaves(new QLabel(this)),
    mOctaves(new QSpinBox(this)),
    mLabelOctaveLayers(new QLabel(this)),
    mOctaveLayers(new QSpinBox(this)),
    mExtendedDescriptor(new QCheckBox(this)),
    mUpright(new QCheckBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

SurfWidgetImp::~SurfWidgetImp()
{
}

double SurfWidgetImp::hessianThreshold() const
{
  return mHessianThreshold->value();
}

int SurfWidgetImp::octaves() const
{
  return mOctaves->value();
}

int SurfWidgetImp::octaveLayers() const
{
  return mOctaveLayers->value();
}

bool SurfWidgetImp::extendedDescriptor() const
{
  return mExtendedDescriptor->isChecked();
}

bool SurfWidgetImp::upright() const
{
  return mUpright->isChecked();
}

void SurfWidgetImp::setHessianThreshold(double hessianThreshold)
{
  const QSignalBlocker blockerHessianThreshold(mHessianThreshold);
  mHessianThreshold->setValue(hessianThreshold);
}

void SurfWidgetImp::setOctaves(int octaves)
{
  const QSignalBlocker blockerOctaves(mOctaves);
  mOctaves->setValue(octaves);
}

void SurfWidgetImp::setOctaveLayers(int octaveLayers)
{
  const QSignalBlocker blockerOctaveLayers(mOctaveLayers);
  mOctaveLayers->setValue(octaveLayers);
}

void SurfWidgetImp::setExtendedDescriptor(bool extendedDescriptor)
{
  mExtendedDescriptor->setChecked(extendedDescriptor);
}

void SurfWidgetImp::seUpright(bool upright)
{
  mUpright->setChecked(upright);
}

void SurfWidgetImp::update()
{
}

void SurfWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("SurfWidgetImp", "SURF Parameters"));
  mLabelHessianThreshold->setText(QApplication::translate("SurfWidgetImp", "Hessian Threshold:"));
  mLabelOctaves->setText(QApplication::translate("SurfWidgetImp", "Octaves:"));
  mLabelOctaveLayers->setText(QApplication::translate("SurfWidgetImp", "Octave Layers:"));
  mExtendedDescriptor->setText(QApplication::translate("SurfWidgetImp", "Extended Descriptor"));
  mUpright->setText(QApplication::translate("SurfWidgetImp", "Upright"));
}

void SurfWidgetImp::reset()
{
  const QSignalBlocker blockerHessianThreshold(mHessianThreshold);
  const QSignalBlocker blockerOctaves(mOctaves);
  const QSignalBlocker blockerOctaveLayers(mOctaveLayers);

  mHessianThreshold->setValue(100);
  mOctaves->setValue(4);
  mOctaveLayers->setValue(3);
  mExtendedDescriptor->setChecked(false);
  mUpright->setChecked(false);
}

void SurfWidgetImp::initUI()
{
  this->setWindowTitle("SURF");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mLabelHessianThreshold, 0, 0);
  mHessianThreshold->setRange(0, 10000);
  propertiesLayout->addWidget(mHessianThreshold, 0, 1);

  propertiesLayout->addWidget(mLabelOctaves, 1, 0);
  mOctaves->setRange(0, 100);
  propertiesLayout->addWidget(mOctaves, 1, 1);

  propertiesLayout->addWidget(mLabelOctaveLayers, 2, 0);
  mOctaveLayers->setRange(0, 100);
  propertiesLayout->addWidget(mOctaveLayers, 2, 1);

  propertiesLayout->addWidget(mExtendedDescriptor, 3, 0);

  propertiesLayout->addWidget(mUpright, 4, 0);

  this->retranslate();
  this->reset(); /// set default values
  this->update();
}

void SurfWidgetImp::initSignalAndSlots()
{
  connect(mHessianThreshold,    SIGNAL(valueChanged(double)),    this, SIGNAL(hessianThresholdChange(double)));
  connect(mOctaves,             SIGNAL(valueChanged(int)),       this, SIGNAL(octavesChange(int)));
  connect(mOctaveLayers,        SIGNAL(valueChanged(int)),       this, SIGNAL(octaveLayersChange(int)));
  connect(mExtendedDescriptor,  SIGNAL(clicked(bool)),           this, SIGNAL(extendedDescriptorChange(bool)));
  connect(mUpright,             SIGNAL(clicked(bool)),           this, SIGNAL(rotatedFeaturesChange(bool)));

}

void SurfWidgetImp::changeEvent(QEvent *event)
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

