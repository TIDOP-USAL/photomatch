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


#include "AkazeWidget.h"

#include <QSpinBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

AkazeWidgetImp::AkazeWidgetImp(QWidget *parent)
  : AkazeWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelDescriptorType(new QLabel(this)),
    mDescriptorType(new QComboBox(this)),
    mLabelDescriptorSize(new QLabel(this)),
    mDescriptorSize(new QSpinBox(this)),
    mLabelDescriptorChannels(new QLabel(this)),
    mDescriptorChannels(new QSpinBox(this)),
    mLabelThreshold(new QLabel(this)),
    mThreshold(new QDoubleSpinBox(this)),
    mLabelOctaves(new QLabel(this)),
    mOctaves(new QSpinBox(this)),
    mLabelOctaveLayers(new QLabel(this)),
    mOctaveLayers(new QSpinBox(this)),
    mLabelDiffusivity(new QLabel(this)),
    mDiffusivity(new QComboBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

AkazeWidgetImp::~AkazeWidgetImp()
{

}

QString AkazeWidgetImp::descriptorType() const
{
  return mDescriptorType->currentText();
}

int AkazeWidgetImp::descriptorSize() const
{
  return mDescriptorSize->value();
}

int AkazeWidgetImp::descriptorChannels() const
{
  return mDescriptorChannels->value();
}

double AkazeWidgetImp::threshold() const
{
  return mThreshold->value();
}

int AkazeWidgetImp::octaves() const
{
  return mOctaves->value();
}

int AkazeWidgetImp::octaveLayers() const
{
  return mOctaveLayers->value();
}

QString AkazeWidgetImp::diffusivity() const
{
  return mDiffusivity->currentText();
}

void AkazeWidgetImp::setDescriptorType(const QString &descriptorType)
{
  const QSignalBlocker blockerDescriptorType(mDescriptorType);
  mDescriptorType->setCurrentText(descriptorType);
}

void AkazeWidgetImp::setDescriptorSize(int descriptorSize)
{
  const QSignalBlocker blockerDescriptorSize(mDescriptorSize);
  mDescriptorSize->setValue(descriptorSize);
}

void AkazeWidgetImp::setDescriptorChannels(int channels)
{
  const QSignalBlocker blockerDescriptorChannels(mDescriptorChannels);
  mDescriptorChannels->setValue(channels);
}

void AkazeWidgetImp::setThreshold(double threshold)
{
  const QSignalBlocker blockerThreshold(mThreshold);
  mThreshold->setValue(threshold);
}

void AkazeWidgetImp::setOctaves(int octaves)
{
  const QSignalBlocker blockerOctaves(mOctaves);
  mOctaves->setValue(octaves);
}

void AkazeWidgetImp::setOctaveLayers(int octaveLayers)
{
  const QSignalBlocker blockerOctaveLayers(mOctaveLayers);
  mOctaveLayers->setValue(octaveLayers);
}

void AkazeWidgetImp::setDiffusivity(const QString &diffusivity)
{
  const QSignalBlocker blockerDiffusivity(mDiffusivity);
  mDiffusivity->setCurrentText(diffusivity);
}

void AkazeWidgetImp::update()
{

}

void AkazeWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("AkazeWidgetImp", "AKAZE Parameters", nullptr));
  mLabelDescriptorType->setText(QApplication::translate("AkazeWidgetImp", "Descriptor Type:", nullptr));
  mLabelDescriptorSize->setText(QApplication::translate("AkazeWidgetImp", "Descriptor Size:", nullptr));
  mLabelDescriptorChannels->setText(QApplication::translate("AkazeWidgetImp", "Descriptor Channels:", nullptr));
  mLabelThreshold->setText(QApplication::translate("AkazeWidgetImp", "Threshold:", nullptr));
  mLabelOctaves->setText(QApplication::translate("AkazeWidgetImp", "Octaves:", nullptr));
  mLabelOctaveLayers->setText(QApplication::translate("AkazeWidgetImp", "Octave Layers:", nullptr));
  mLabelDiffusivity->setText(QApplication::translate("AkazeWidgetImp", "Diffusivity:", nullptr));
}

void AkazeWidgetImp::reset()
{
  const QSignalBlocker blockerDescriptorType(mDescriptorType);
  const QSignalBlocker blockerDescriptorSize(mDescriptorSize);
  const QSignalBlocker blockerDescriptorChannels(mDescriptorChannels);
  const QSignalBlocker blockerThreshold(mThreshold);
  const QSignalBlocker blockerOctaves(mOctaves);
  const QSignalBlocker blockerOctaveLayers(mOctaveLayers);
  const QSignalBlocker blockerDiffusivity(mDiffusivity);

  mDescriptorType->setCurrentText("MLDB");
  mDescriptorSize->setValue(0);
  mDescriptorChannels->setValue(3);
  mThreshold->setValue(0.001);
  mOctaves->setValue(4);
  mOctaveLayers->setValue(4);
  mDiffusivity->setCurrentText("DIFF_PM_G2");
}

void AkazeWidgetImp::initUI()
{
  this->setWindowTitle("AKAZE");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mLabelDescriptorType, 0, 0);
  mDescriptorType->addItem("KAZE");
  mDescriptorType->addItem("KAZE_UPRIGHT");
  mDescriptorType->addItem("MLDB");
  mDescriptorType->addItem("MLDB_UPRIGHT");
  mDescriptorType->setCurrentText("MLDB");
  propertiesLayout->addWidget(mDescriptorType, 0, 1);

  propertiesLayout->addWidget(mLabelDescriptorSize, 1, 0);
  mDescriptorSize->setRange(0, 64); // TODO: creo que no soporta mas que 64. comprobar
  propertiesLayout->addWidget(mDescriptorSize, 1, 1);

  propertiesLayout->addWidget(mLabelDescriptorChannels, 2, 0);
  mDescriptorChannels->setRange(1, 3);
  propertiesLayout->addWidget(mDescriptorChannels, 2, 1);

  propertiesLayout->addWidget(mLabelThreshold, 3, 0);
  mThreshold->setDecimals(3);
  mThreshold->setRange(0, 99.99);
  mThreshold->setSingleStep(0.01);
  propertiesLayout->addWidget(mThreshold, 3, 1);

  propertiesLayout->addWidget(mLabelOctaves, 4, 0);
  mOctaves->setRange(0, 100);
  propertiesLayout->addWidget(mOctaves, 4, 1);

  propertiesLayout->addWidget(mLabelOctaveLayers, 5, 0);
  mOctaveLayers->setRange(0, 100);
  propertiesLayout->addWidget(mOctaveLayers, 5, 1);

  propertiesLayout->addWidget(mLabelDiffusivity, 6, 0);
  mDiffusivity->addItem("DIFF_PM_G1");
  mDiffusivity->addItem("DIFF_PM_G2");
  mDiffusivity->addItem("DIFF_WEICKERT");
  mDiffusivity->addItem("DIFF_CHARBONNIER");
  propertiesLayout->addWidget(mDiffusivity, 6, 1);

  this->retranslate();
  this->reset();  /// set default values
  this->update();
}

void AkazeWidgetImp::initSignalAndSlots()
{
  connect(mDescriptorType,     SIGNAL(currentTextChanged(QString)), this, SIGNAL(descriptorTypeChange(QString)));
  connect(mDescriptorSize,     SIGNAL(valueChanged(int)),           this, SIGNAL(descriptorSizeChange(int)));
  connect(mDescriptorChannels, SIGNAL(valueChanged(int)),           this, SIGNAL(descriptorChannelsChange(int)));
  connect(mThreshold,          SIGNAL(valueChanged(double)),        this, SIGNAL(thresholdChange(double)));
  connect(mOctaves,            SIGNAL(valueChanged(int)),           this, SIGNAL(octavesChange(int)));
  connect(mOctaveLayers,       SIGNAL(valueChanged(int)),           this, SIGNAL(octaveLayersChange(int)));
  connect(mDiffusivity,        SIGNAL(currentTextChanged(QString)), this, SIGNAL(diffusivityChange(QString)));
}

void AkazeWidgetImp::changeEvent(QEvent *event)
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



