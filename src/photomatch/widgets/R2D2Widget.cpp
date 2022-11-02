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


#include "R2D2Widget.h"

#include <QSpinBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

R2D2WidgetImp::R2D2WidgetImp(QWidget *parent)
  : R2D2Widget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelScaleF(new QLabel(this)),
  mDoubleSpinBoxScaleF(new QDoubleSpinBox(this)),
  mLabelMinSize(new QLabel(this)),
  mSpinBoxMinSize(new QSpinBox(this)),
  mLabelMaxSize(new QLabel(this)),
  mSpinBoxMaxSize(new QSpinBox(this)),
  mLabelMinScale(new QLabel(this)),
  mDoubleSpinBoxMinScale(new QDoubleSpinBox(this)),
  mLabelMaxScale(new QLabel(this)),
  mDoubleSpinBoxMaxScale(new QDoubleSpinBox(this)),
  mLabelReliabilityThreshold(new QLabel(this)),
  mDoubleSpinBoxReliabilityThreshold(new QDoubleSpinBox(this)),
  mLabelRepeatabilityThreshold(new QLabel(this)),
  mDoubleSpinBoxRepeatabilityThreshold(new QDoubleSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

R2D2WidgetImp::~R2D2WidgetImp()
{

}

void R2D2WidgetImp::initUI()
{
  this->setWindowTitle("R2D2");
  this->setObjectName("R2D2Widget");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mLabelScaleF, 0, 0);
  propertiesLayout->addWidget(mDoubleSpinBoxScaleF, 0, 1);

  propertiesLayout->addWidget(mLabelMinSize, 1, 0);
  mSpinBoxMinSize->setRange(0, 10000);
  propertiesLayout->addWidget(mSpinBoxMinSize, 1, 1);

  propertiesLayout->addWidget(mLabelMaxSize, 2, 0);
  mSpinBoxMaxSize->setRange(0, 10000);
  propertiesLayout->addWidget(mSpinBoxMaxSize, 2, 1);

  propertiesLayout->addWidget(mLabelMinScale, 3, 0);
  propertiesLayout->addWidget(mDoubleSpinBoxMinScale, 3, 1);

  propertiesLayout->addWidget(mLabelMaxScale, 4, 0);
  propertiesLayout->addWidget(mDoubleSpinBoxMaxScale, 4, 1);

  propertiesLayout->addWidget(mLabelReliabilityThreshold, 5, 0);
  propertiesLayout->addWidget(mDoubleSpinBoxReliabilityThreshold, 5, 1);

  propertiesLayout->addWidget(mLabelRepeatabilityThreshold, 6, 0);
  propertiesLayout->addWidget(mDoubleSpinBoxRepeatabilityThreshold, 6, 1);

  this->retranslate();
  this->reset();  /// set default values
  this->update();
}

void R2D2WidgetImp::initSignalAndSlots()
{
  connect(mDoubleSpinBoxScaleF, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &R2D2Widget::scaleFChanged);
  connect(mSpinBoxMinSize, QOverload<int>::of(&QSpinBox::valueChanged),
          this, &R2D2Widget::minSizeChanged);
  connect(mSpinBoxMaxSize, QOverload<int>::of(&QSpinBox::valueChanged),
          this, &R2D2Widget::maxSizeChanged);
  connect(mDoubleSpinBoxMinScale, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &R2D2Widget::minScaleChanged);
  connect(mDoubleSpinBoxMaxScale, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &R2D2Widget::maxScaleChanged);
  connect(mDoubleSpinBoxReliabilityThreshold, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &R2D2Widget::reliabilityThresholdChanged);
  connect(mDoubleSpinBoxRepeatabilityThreshold, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &R2D2Widget::repeatabilityThresholdChanged);
}

void R2D2WidgetImp::reset()
{
  const QSignalBlocker blockerDescriptorType(mDoubleSpinBoxScaleF);
  const QSignalBlocker blockerDescriptorSize(mSpinBoxMinSize);
  const QSignalBlocker blockerDescriptorChannels(mSpinBoxMaxSize);
  const QSignalBlocker blockerThreshold(mDoubleSpinBoxMinScale);
  const QSignalBlocker blockerOctaves(mDoubleSpinBoxMaxScale);
  const QSignalBlocker blockerOctaveLayers(mDoubleSpinBoxReliabilityThreshold);
  const QSignalBlocker blockerDiffusivity(mDoubleSpinBoxRepeatabilityThreshold);

  mDoubleSpinBoxScaleF->setValue(pow(2, 0.25));
  mSpinBoxMinSize->setValue(256);
  mSpinBoxMaxSize->setValue(1024);
  mDoubleSpinBoxMinScale->setValue(0.);
  mDoubleSpinBoxMaxScale->setValue(1.);
  mDoubleSpinBoxReliabilityThreshold->setValue(0.7);
  mDoubleSpinBoxRepeatabilityThreshold->setValue(0.7);
}

void R2D2WidgetImp::update()
{

}

void R2D2WidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("R2D2Widget", "R2D2 Parameters", nullptr));
  mLabelScaleF->setText(QApplication::translate("R2D2Widget", "Scale F:", nullptr));
  mLabelMinSize->setText(QApplication::translate("R2D2Widget", "Min Size:", nullptr));
  mLabelMaxSize->setText(QApplication::translate("R2D2Widget", "Max Size:", nullptr));
  mLabelMinScale->setText(QApplication::translate("R2D2Widget", "Min Scale:", nullptr));
  mLabelMaxScale->setText(QApplication::translate("R2D2Widget", "Max Scale:", nullptr));
  mLabelReliabilityThreshold->setText(QApplication::translate("R2D2Widget", "Reliability Threshold:", nullptr));
  mLabelRepeatabilityThreshold->setText(QApplication::translate("R2D2Widget", "Repeatability Threshold:", nullptr));
}

double R2D2WidgetImp::scaleF() const
{
  return mDoubleSpinBoxScaleF->value();
}

int R2D2WidgetImp::minSize() const
{
  return mSpinBoxMinSize->value();
}

int R2D2WidgetImp::maxSize() const
{
  return mSpinBoxMaxSize->value();
}

double R2D2WidgetImp::minScale() const
{
  return mDoubleSpinBoxMinScale->value();
}

double R2D2WidgetImp::maxScale() const
{
  return mDoubleSpinBoxMaxScale->value();
}

double R2D2WidgetImp::reliabilityThreshold() const
{
  return mDoubleSpinBoxReliabilityThreshold->value();
}

double R2D2WidgetImp::repeatabilityThreshold() const
{
  return mDoubleSpinBoxRepeatabilityThreshold->value();
}

void R2D2WidgetImp::setScaleF(double scaleF)
{
  const QSignalBlocker blockerDescriptorType(mDoubleSpinBoxScaleF);
  mDoubleSpinBoxScaleF->setValue(scaleF);
}

void R2D2WidgetImp::setMinSize(int size)
{
  const QSignalBlocker blockerDescriptorType(mSpinBoxMinSize);
  mSpinBoxMinSize->setValue(size);
}

void R2D2WidgetImp::setMaxSize(int size)
{
  const QSignalBlocker blockerDescriptorType(mSpinBoxMaxSize);
  mSpinBoxMaxSize->setValue(size);
}

void R2D2WidgetImp::setMinScale(double minScale)
{
  const QSignalBlocker blockerDescriptorType(mDoubleSpinBoxMinScale);
  mDoubleSpinBoxMinScale->setValue(minScale);
}

void R2D2WidgetImp::setMaxScale(double maxScale)
{
  const QSignalBlocker blockerDescriptorType(mDoubleSpinBoxMaxScale);
  mDoubleSpinBoxMaxScale->setValue(maxScale);
}

void R2D2WidgetImp::setReliabilityThreshold(double reliabilityThreshold)
{
  const QSignalBlocker blockerDescriptorType(mDoubleSpinBoxReliabilityThreshold);
  mDoubleSpinBoxReliabilityThreshold->setValue(reliabilityThreshold);
}

void R2D2WidgetImp::setRepeatabilityThreshold(double repeatabilityThreshold)
{
  const QSignalBlocker blockerDescriptorType(mDoubleSpinBoxRepeatabilityThreshold);
  mDoubleSpinBoxRepeatabilityThreshold->setValue(repeatabilityThreshold);
}



} // namespace photomatch



