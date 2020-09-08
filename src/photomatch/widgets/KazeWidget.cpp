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


#include "KazeWidget.h"

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

KazeWidgetImp::KazeWidgetImp(QWidget *parent)
  : KazeWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mExtended(new QCheckBox(this)),
    mUpright(new QCheckBox(this)),
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

KazeWidgetImp::~KazeWidgetImp()
{
}

void KazeWidgetImp::initUI()
{
  this->setWindowTitle("KAZE");
  this->setObjectName("KazeWidget");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mExtended, 0, 0);

  propertiesLayout->addWidget(mUpright, 1, 0);

  propertiesLayout->addWidget(mLabelThreshold, 2, 0);
  mThreshold->setDecimals(3);
  mThreshold->setRange(0, 99.99);
  mThreshold->setSingleStep(0.001);
  propertiesLayout->addWidget(mThreshold, 2, 1);

  propertiesLayout->addWidget(mLabelOctaves, 3, 0);
  mOctaves->setRange(0, 100);
  propertiesLayout->addWidget(mOctaves, 3, 1);

  propertiesLayout->addWidget(mLabelOctaveLayers, 4, 0);
  mOctaveLayers->setRange(0, 100);
  propertiesLayout->addWidget(mOctaveLayers, 4, 1);

  propertiesLayout->addWidget(mLabelDiffusivity, 5, 0);
  mDiffusivity->addItem("DIFF_PM_G1");
  mDiffusivity->addItem("DIFF_PM_G2");
  mDiffusivity->addItem("DIFF_WEICKERT");
  mDiffusivity->addItem("DIFF_CHARBONNIER");
  propertiesLayout->addWidget(mDiffusivity, 5, 1);

  this->retranslate();
  this->reset(); // Set default values
  this->update();
}

void KazeWidgetImp::initSignalAndSlots()
{
  connect(mExtended,     &QAbstractButton::clicked,                             this, &KazeWidget::extendedDescriptorChange);
  connect(mUpright,      &QAbstractButton::clicked,                             this, &KazeWidget::uprightDescriptorChange);
  connect(mThreshold,    QOverload<double>::of(&QDoubleSpinBox::valueChanged),  this, &KazeWidget::thresholdChange);
  connect(mOctaves,      QOverload<int>::of(&QSpinBox::valueChanged),           this, &KazeWidget::octavesChange);
  connect(mOctaveLayers, QOverload<int>::of(&QSpinBox::valueChanged),           this, &KazeWidget::octaveLayersChange);
  connect(mDiffusivity,  &QComboBox::currentTextChanged,                        this, &KazeWidget::diffusivityChange);
}

void KazeWidgetImp::reset()
{
  const QSignalBlocker blockerHessianThreshold(mThreshold);
  const QSignalBlocker blockerOctaves(mOctaves);
  const QSignalBlocker blockerOctaveLayers(mOctaveLayers);
  const QSignalBlocker blockerDiffusivity(mDiffusivity);

  mExtended->setChecked(false);
  mUpright->setChecked(false);
  mThreshold->setValue(0.001);
  mOctaves->setValue(4);
  mOctaveLayers->setValue(4);
  mDiffusivity->setCurrentText("DIFF_PM_G2");
}

void KazeWidgetImp::update()
{
}

void KazeWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("KazeWidget", "KAZE Parameters"));
  mExtended->setText(QApplication::translate("KazeWidget","Extended Descriptors"));
  mUpright->setText(QApplication::translate("KazeWidget","Upright Descriptors"));
  mLabelThreshold->setText(QApplication::translate("KazeWidget", "Threshold:"));
  mLabelOctaves->setText(QApplication::translate("KazeWidget", "Octaves:"));
  mLabelOctaveLayers->setText(QApplication::translate("KazeWidget", "Octave Layers:"));
  mLabelDiffusivity->setText(QApplication::translate("KazeWidget", "Diffusivity:"));
}

bool KazeWidgetImp::extendedDescriptor() const
{
  return mExtended->isChecked();
}

bool KazeWidgetImp::uprightDescriptor() const
{
  return mUpright->isChecked();
}

double KazeWidgetImp::threshold() const
{
  return mThreshold->value();
}

int KazeWidgetImp::octaves() const
{
  return mOctaves->value();
}

int KazeWidgetImp::octaveLayers() const
{
  return mOctaveLayers->value();
}

QString KazeWidgetImp::diffusivity() const
{
  return mDiffusivity->currentText();
}

void KazeWidgetImp::setExtendedDescriptor(bool extended)
{
  mExtended->setChecked(extended);
}

void KazeWidgetImp::setUprightDescriptor(bool upright)
{
  mUpright->setChecked(upright);
}

void KazeWidgetImp::setThreshold(double threshold)
{
  const QSignalBlocker blockerHessianThreshold(mThreshold);
  mThreshold->setValue(threshold);
}

void KazeWidgetImp::setOctaves(int octaves)
{
  const QSignalBlocker blockerOctaves(mOctaves);
  mOctaves->setValue(octaves);
}

void KazeWidgetImp::setOctaveLayers(int octaveLayers)
{
  const QSignalBlocker blockerOctaveLayers(mOctaveLayers);
  mOctaveLayers->setValue(octaveLayers);
}

void KazeWidgetImp::setDiffusivity(const QString &diffusivity)
{
  const QSignalBlocker blockerDiffusivity(mDiffusivity);
  mDiffusivity->setCurrentText(diffusivity);
}

} // namespace photomatch



