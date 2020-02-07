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


#include "VggWidget.h"

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QDoubleSpinBox>

namespace photomatch
{

VggWidgetImp::VggWidgetImp(QWidget *parent)
  : VggWidget(parent),
    mDescriptorType(new QComboBox(this)),
    mScaleFactor(new QDoubleSpinBox(this)),
    mSigma(new QDoubleSpinBox(this)),
    mUseNormalizeDescriptor(new QCheckBox(this)),
    mUseNormalizeImage(new QCheckBox(this)),
    mUseScaleOrientation(new QCheckBox(this))
{
  init();

  /// Signals and slots
  connect(mDescriptorType,          SIGNAL(currentTextChanged(QString)),   this, SIGNAL(descriptorTypeChange(QString)));
  connect(mScaleFactor,             SIGNAL(valueChanged(double)),          this, SIGNAL(scaleFactorChange(double)));
  connect(mSigma,                   SIGNAL(valueChanged(double)),          this, SIGNAL(sigmaChange(double)));
  connect(mUseNormalizeDescriptor,  SIGNAL(clicked(bool)),                 this, SIGNAL(useNormalizeDescriptorChange(bool)));
  connect(mUseNormalizeImage,       SIGNAL(clicked(bool)),                 this, SIGNAL(useNormalizeImageChange(bool)));
  connect(mUseScaleOrientation,     SIGNAL(clicked(bool)),                 this, SIGNAL(useScaleOrientationChange(bool)));
}

VggWidgetImp::~VggWidgetImp()
{

}

QString VggWidgetImp::descriptorType() const
{
  return mDescriptorType->currentText();
}

double VggWidgetImp::scaleFactor() const
{
  return mScaleFactor->value();
}

double VggWidgetImp::sigma() const
{
  return mSigma->value();
}

bool VggWidgetImp::useNormalizeDescriptor() const
{
  return mUseNormalizeDescriptor->isChecked();
}

bool VggWidgetImp::useNormalizeImage() const
{
  return mUseNormalizeImage->isChecked();
}

bool VggWidgetImp::useScaleOrientation() const
{
  return mUseScaleOrientation->isChecked();
}

void VggWidgetImp::setDescriptorType(const QString &descriptorType)
{
  const QSignalBlocker blockerBytes(mDescriptorType);
  mDescriptorType->setCurrentText(descriptorType);
}

void VggWidgetImp::setScaleFactor(double scaleFactor)
{
  const QSignalBlocker blockerScaleFactor(mScaleFactor);
  mScaleFactor->setValue(scaleFactor);
}

void VggWidgetImp::setSigma(double sigma)
{
  const QSignalBlocker blockerSigma(mSigma);
  mSigma->setValue(sigma);
}

void VggWidgetImp::setUseNormalizeDescriptor(bool active)
{
  mUseNormalizeDescriptor->setChecked(active);
}

void VggWidgetImp::setUseNormalizeImage(bool active)
{
  mUseNormalizeImage->setChecked(active);
}

void VggWidgetImp::setUseScaleOrientation(bool active)
{
  mUseScaleOrientation->setChecked(active);
}

void VggWidgetImp::update()
{
}

void VggWidgetImp::retranslate()
{

}

void VggWidgetImp::reset()
{
  const QSignalBlocker blockerBytes(mDescriptorType);
  const QSignalBlocker blockerScaleFactor(mScaleFactor);
  const QSignalBlocker blockerSigma(mSigma);

  mDescriptorType->setCurrentText("VGG_120");
  mScaleFactor->setValue(6.25);
  mSigma->setValue(1.4);
  mUseNormalizeDescriptor->setChecked(false);
  mUseNormalizeImage->setChecked(true);
  mUseScaleOrientation->setChecked(true);
}

void VggWidgetImp::init()
{
  this->setWindowTitle("VGG");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("VGG Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Descriptor Type:")), 0, 0);
  mDescriptorType->addItem("VGG_120");
  mDescriptorType->addItem("VGG_80");
  mDescriptorType->addItem("VGG_64");
  mDescriptorType->addItem("VGG_48");
  propertiesLayout->addWidget(mDescriptorType, 0, 1);

  //propertiesLayout->addWidget(new QLabel(tr("Scale Factor:")), 1, 0);
  propertiesLayout->addWidget(mScaleFactor, 1, 1);
  mScaleFactor->setVisible(false); ///Se desactiva y se modifica internamente según el detector usado

  propertiesLayout->addWidget(new QLabel(tr("Sigma:")), 2, 0);
  propertiesLayout->addWidget(mSigma, 2, 1);

  mUseNormalizeDescriptor->setText(tr("Use Normalize Descriptor"));
  propertiesLayout->addWidget(mUseNormalizeDescriptor, 3, 0);

  mUseNormalizeImage->setText(tr("Use Normalize Image"));
  propertiesLayout->addWidget(mUseNormalizeImage, 4, 0);

  mUseScaleOrientation->setText(tr("Use Scale Orientation"));
  propertiesLayout->addWidget(mUseScaleOrientation, 5, 0);

  reset();

  update();
}

} // namespace photomatch





