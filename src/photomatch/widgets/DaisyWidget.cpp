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


#include "DaisyWidget.h"

#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

DaisyWidgetImp::DaisyWidgetImp(QWidget *parent)
  : DaisyWidget(parent),
    mRadius(new QDoubleSpinBox(this)),
    mQRadius(new QSpinBox(this)),
    mQTheta(new QSpinBox(this)),
    mQHist(new QSpinBox(this)),
    mNorm(new QComboBox(this)),
    mInterpolation(new QCheckBox(this)),
    mUseOrientation(new QCheckBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

DaisyWidgetImp::~DaisyWidgetImp()
{

}

double DaisyWidgetImp::radius() const
{
  return mRadius->value();
}

int DaisyWidgetImp::qRadius() const
{
  return mQRadius->value();
}

int DaisyWidgetImp::qTheta() const
{
  return mQTheta->value();
}

int DaisyWidgetImp::qHist() const
{
  return mQHist->value();
}

QString DaisyWidgetImp::norm() const
{
  return mNorm->currentText();
}

bool DaisyWidgetImp::interpolation() const
{
  return mInterpolation->isChecked();
}

bool DaisyWidgetImp::useOrientation() const
{
  return mUseOrientation->isChecked();
}

void DaisyWidgetImp::setRadius(double radius)
{
  const QSignalBlocker blockerRadius(mRadius);
  mRadius->setValue(radius);
}

void DaisyWidgetImp::setQRadius(int qRadius)
{
  const QSignalBlocker blockerQRadius(mQRadius);
  mQRadius->setValue(qRadius);
}

void DaisyWidgetImp::setQTheta(int qTheta)
{
  const QSignalBlocker blockerQTheta(mQTheta);
  mQTheta->setValue(qTheta);
}

void DaisyWidgetImp::setQHist(int qHist)
{
  const QSignalBlocker blockerQHist(mQHist);
  mQHist->setValue(qHist);
}

void DaisyWidgetImp::setNorm(const QString &norm)
{
  const QSignalBlocker blockerNorm(mNorm);
  mNorm->setCurrentText(norm);
}

void DaisyWidgetImp::setInterpolation(bool interpolation)
{
  mInterpolation->setChecked(interpolation);
}

void DaisyWidgetImp::setUseOrientation(bool useOrientation)
{
  mUseOrientation->setChecked(useOrientation);
}

void DaisyWidgetImp::update()
{
}

void DaisyWidgetImp::retranslate()
{

}

void DaisyWidgetImp::reset()
{
  const QSignalBlocker blockerRadius(mRadius);
  const QSignalBlocker blockerQRadius(mQRadius);
  const QSignalBlocker blockerQTheta(mQTheta);
  const QSignalBlocker blockerQHist(mQHist);
  const QSignalBlocker blockerNorm(mNorm);

  mRadius->setValue(15.);
  mQRadius->setValue(3);
  mQTheta->setValue(8);
  mQHist->setValue(8);
  mNorm->setCurrentText("NRM_NONE");
  mInterpolation->setChecked(true);
  mUseOrientation->setChecked(false);
}

void DaisyWidgetImp::initUI()
{
  this->setWindowTitle("DAISY");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("DAISY Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Radius:")), 0, 0);
  mRadius->setRange(0., 100.);
  propertiesLayout->addWidget(mRadius, 0, 1);

  propertiesLayout->addWidget(new QLabel(tr("Radial range division quantity:")), 1, 0);
  mQRadius->setRange(1, 100);
  propertiesLayout->addWidget(mQRadius, 1, 1);

  propertiesLayout->addWidget(new QLabel(tr("Angular range division quantity:")), 2, 0);
  mQTheta->setRange(0, 100);
  propertiesLayout->addWidget(mQTheta, 2, 1);

  propertiesLayout->addWidget(new QLabel(tr("Gradient orientations range division quantity:")), 3, 0);
  mQHist->setRange(0, 100);
  propertiesLayout->addWidget(mQHist, 3, 1);

  mInterpolation->setText(tr("Interpolation"));
  propertiesLayout->addWidget(mInterpolation, 4, 0);

  mUseOrientation->setText(tr("Keypoints orientation"));
  propertiesLayout->addWidget(mUseOrientation, 5, 0);

  propertiesLayout->addWidget(new QLabel(tr("Descriptor normalization type:")), 6, 0);
  mNorm->addItem("NRM_NONE");
  mNorm->addItem("NRM_PARTIAL");
  mNorm->addItem("NRM_FULL");
  mNorm->addItem("NRM_SIFT");
  propertiesLayout->addWidget(mNorm, 6, 1);



  reset();

  update();
}

void DaisyWidgetImp::initSignalAndSlots()
{
  connect(mRadius,         SIGNAL(valueChanged(double)),         this, SIGNAL(radiusChange(double)));
  connect(mQRadius,        SIGNAL(valueChanged(int)),            this, SIGNAL(qRadiusChange(int)));
  connect(mQTheta,         SIGNAL(valueChanged(int)),            this, SIGNAL(qThetaChange(int)));
  connect(mQHist,          SIGNAL(valueChanged(int)),            this, SIGNAL(qHistChange(int)));
  connect(mNorm,           SIGNAL(currentTextChanged(QString)),  this, SIGNAL(normChange(QString)));
  connect(mInterpolation,  SIGNAL(clicked(bool)),                this, SIGNAL(interpolationChange(bool)));
  connect(mUseOrientation, SIGNAL(clicked(bool)),                this, SIGNAL(useOrientationChange(bool)));
}

} // namespace photomatch

