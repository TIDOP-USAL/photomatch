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
#include <QApplication>

namespace photomatch
{

DaisyWidgetImp::DaisyWidgetImp(QWidget *parent)
  : DaisyWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelRadius(new QLabel(this)),
    mRadius(new QDoubleSpinBox(this)),
    mLabelQRadius(new QLabel(this)),
    mQRadius(new QSpinBox(this)),
    mLabelQTheta(new QLabel(this)),
    mQTheta(new QSpinBox(this)),
    mLabelQHist(new QLabel(this)),
    mQHist(new QSpinBox(this)),
    mLabelNorm(new QLabel(this)),
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

void DaisyWidgetImp::initUI()
{
  this->setWindowTitle("DAISY");
  this->setObjectName("DaisyWidget");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mLabelRadius, 0, 0);
  mRadius->setRange(0., 100.);
  propertiesLayout->addWidget(mRadius, 0, 1);

  propertiesLayout->addWidget(mLabelQRadius, 1, 0);
  mQRadius->setRange(1, 100);
  propertiesLayout->addWidget(mQRadius, 1, 1);

  propertiesLayout->addWidget(mLabelQTheta, 2, 0);
  mQTheta->setRange(0, 100);
  propertiesLayout->addWidget(mQTheta, 2, 1);

  propertiesLayout->addWidget(mLabelQHist, 3, 0);
  mQHist->setRange(0, 100);
  propertiesLayout->addWidget(mQHist, 3, 1);

  propertiesLayout->addWidget(mInterpolation, 4, 0);

  propertiesLayout->addWidget(mUseOrientation, 5, 0);

  propertiesLayout->addWidget(mLabelNorm, 6, 0);
  mNorm->addItem("NRM_NONE");
  mNorm->addItem("NRM_PARTIAL");
  mNorm->addItem("NRM_FULL");
  mNorm->addItem("NRM_SIFT");
  propertiesLayout->addWidget(mNorm, 6, 1);

  this->retranslate();
  this->reset(); /// set default values
  this->update();
}

void DaisyWidgetImp::initSignalAndSlots()
{
  connect(mRadius,         QOverload<double>::of(&QDoubleSpinBox::valueChanged),   this, &DaisyWidget::radiusChange);
  connect(mQRadius,        QOverload<int>::of(&QSpinBox::valueChanged),            this, &DaisyWidget::qRadiusChange);
  connect(mQTheta,         QOverload<int>::of(&QSpinBox::valueChanged),            this, &DaisyWidget::qThetaChange);
  connect(mQHist,          QOverload<int>::of(&QSpinBox::valueChanged),            this, &DaisyWidget::qHistChange);
  connect(mNorm,           &QComboBox::currentTextChanged,                         this, &DaisyWidget::normChange);
  connect(mInterpolation,  &QAbstractButton::clicked,                              this, &DaisyWidget::interpolationChange);
  connect(mUseOrientation, &QAbstractButton::clicked,                              this, &DaisyWidget::useOrientationChange);
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

void DaisyWidgetImp::update()
{
}

void DaisyWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("DaisyWidget", "DAISY Parameters"));
  mLabelRadius->setText(QApplication::translate("DaisyWidget", "Radius:"));
  mLabelQRadius->setText(QApplication::translate("DaisyWidget", "Radial range division quantity:"));
  mLabelQTheta->setText(QApplication::translate("DaisyWidget", "Angular range division quantity:"));
  mLabelQHist->setText(QApplication::translate("DaisyWidget", "Gradient orientations range division quantity:"));
  mLabelNorm->setText(QApplication::translate("DaisyWidget", "Descriptor normalization type:"));
  mInterpolation->setText(QApplication::translate("DaisyWidget", "Interpolation"));
  mUseOrientation->setText(QApplication::translate("DaisyWidget", "Keypoints orientation"));
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

} // namespace photomatch
