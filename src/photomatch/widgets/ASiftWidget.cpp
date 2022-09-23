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


#include "ASiftWidget.h"

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

ASiftWidgetImp::ASiftWidgetImp(QWidget *parent)
  : ASiftWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelFeaturesNumber(new QLabel(this)),
    mFeaturesNumber(new QSpinBox(this)),
    mLabelOctaveLayers(new QLabel(this)),
    mOctaveLayers(new QSpinBox(this)),
    mLabelContrastThreshold(new QLabel(this)),
    mContrastThreshold(new QDoubleSpinBox(this)),
    mLabelEdgeThreshold(new QLabel(this)),
    mEdgeThreshold(new QDoubleSpinBox(this)),
    mLabelSigma(new QLabel(this)),
    mSigma(new QDoubleSpinBox(this)),
    mLabelMinTilt(new QLabel(this)),
    mSpinBoxMinTilt(new QSpinBox(this)),
    mLabelMaxTilt(new QLabel(this)),
    mSpinBoxMaxTilt(new QSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

ASiftWidgetImp::~ASiftWidgetImp()
{

}

int ASiftWidgetImp::featuresNumber() const
{
  return mFeaturesNumber->value();
}

int ASiftWidgetImp::octaveLayers() const
{
  return mOctaveLayers->value();
}

double ASiftWidgetImp::contrastThreshold()
{
  return mContrastThreshold->value();
}

double ASiftWidgetImp::edgeThreshold()
{
  return mEdgeThreshold->value();
}

double ASiftWidgetImp::sigma()
{
  return mSigma->value();
}

int ASiftWidgetImp::minTilt() const
{
  return mSpinBoxMinTilt->value();
}

int ASiftWidgetImp::maxTilt() const
{
  return mSpinBoxMaxTilt->value();
}

void ASiftWidgetImp::setFeaturesNumber(int featuresNumber)
{
  const QSignalBlocker blockerFeaturesNumber(mFeaturesNumber);
  mFeaturesNumber->setValue(featuresNumber);
}

void ASiftWidgetImp::setOctaveLayers(int octaveLayers)
{
  const QSignalBlocker blockerFeaturesNumber(mOctaveLayers);
  mOctaveLayers->setValue(octaveLayers);
}

void ASiftWidgetImp::setContrastThreshold(double contrastThreshold)
{
  const QSignalBlocker blockerContrastThreshold(mContrastThreshold);
  mContrastThreshold->setValue(contrastThreshold);
}

void ASiftWidgetImp::setEdgeThreshold(double edgeThreshold)
{
  const QSignalBlocker blockerEdgeThreshold(mEdgeThreshold);
  mEdgeThreshold->setValue(edgeThreshold);
}

void ASiftWidgetImp::setSigma(double sigma)
{
  const QSignalBlocker blockerSigma(mSigma);
  mSigma->setValue(sigma);
}

void ASiftWidgetImp::setMinTilt(int minTilt)
{
  mSpinBoxMinTilt->setValue(minTilt);
}

void ASiftWidgetImp::setMaxTilt(int maxTilt)
{
  mSpinBoxMaxTilt->setValue(maxTilt);
}


void ASiftWidgetImp::initUI()
{
  this->setWindowTitle("SIFT");
  this->setObjectName("ASiftWidget");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mLabelFeaturesNumber, 0, 0);
  mFeaturesNumber->setRange(0, 50000);
  propertiesLayout->addWidget(mFeaturesNumber, 0, 1);

  propertiesLayout->addWidget(mLabelOctaveLayers, 1, 0);
  mOctaveLayers->setRange(0, 10);
  propertiesLayout->addWidget(mOctaveLayers, 1, 1);

  propertiesLayout->addWidget(mLabelContrastThreshold, 2, 0);
  mContrastThreshold->setRange(0., 10.);  //TODO: ver que el rango tenga sentido
  mContrastThreshold->setDecimals(3);
  mContrastThreshold->setSingleStep(0.01);
  propertiesLayout->addWidget(mContrastThreshold, 2, 1);

  propertiesLayout->addWidget(mLabelEdgeThreshold, 3, 0);
  mEdgeThreshold->setRange(0., 100.);
  propertiesLayout->addWidget(mEdgeThreshold, 3, 1);

  propertiesLayout->addWidget(mLabelSigma, 4, 0);
  mSigma->setRange(0., 100.);
  mSigma->setSingleStep(0.1);
  propertiesLayout->addWidget(mSigma, 4, 1);

  propertiesLayout->addWidget(mLabelMinTilt, 5, 0);
  mSpinBoxMinTilt->setRange(0, 6);
  mSpinBoxMinTilt->setSingleStep(1);
  propertiesLayout->addWidget(mSpinBoxMinTilt, 5, 1);

  propertiesLayout->addWidget(mLabelMaxTilt, 6, 0);
  mSpinBoxMaxTilt->setRange(0, 6);
  mSpinBoxMaxTilt->setSingleStep(1);
  propertiesLayout->addWidget(mSpinBoxMaxTilt, 6, 1);

  this->retranslate();
  this->reset(); /// set default values
  this->update();
}

void ASiftWidgetImp::initSignalAndSlots()
{
  connect(mFeaturesNumber,    QOverload<int>::of(&QSpinBox::valueChanged),          this, &ASiftWidget::featuresNumberChange);
  connect(mOctaveLayers,      QOverload<int>::of(&QSpinBox::valueChanged),          this, &ASiftWidget::octaveLayersChange);
  connect(mContrastThreshold, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &ASiftWidget::contrastThresholdChange);
  connect(mEdgeThreshold,     QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &ASiftWidget::edgeThresholdChange);
  connect(mSigma,             QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &ASiftWidget::sigmaChange);
  connect(mSpinBoxMinTilt,    QOverload<int>::of(&QSpinBox::valueChanged),          this, &ASiftWidget::minTiltChange);
  connect(mSpinBoxMaxTilt,    QOverload<int>::of(&QSpinBox::valueChanged),          this, &ASiftWidget::maxTiltChange);
}

void ASiftWidgetImp::reset()
{
  const QSignalBlocker blockerFeaturesNumber(mFeaturesNumber);
  const QSignalBlocker blockerOctaveLayers(mOctaveLayers);
  const QSignalBlocker blockerContrastThreshold(mContrastThreshold);
  const QSignalBlocker blockerEdgeThreshold(mEdgeThreshold);
  const QSignalBlocker blockerSigma(mSigma);
  const QSignalBlocker blockerMinTilt(mSpinBoxMinTilt);
  const QSignalBlocker blockerMaxTilt(mSpinBoxMaxTilt);

  mFeaturesNumber->setValue(5000);     // OpenCV default value = 0
  mOctaveLayers->setValue(3);          // OpenCV default value = 3
  mContrastThreshold->setValue(0.04);  // OpenCV default value = 0.04
  mEdgeThreshold->setValue(10.);
  mSigma->setValue(1.6);
  mSpinBoxMinTilt->setValue(0);
  mSpinBoxMaxTilt->setValue(6);
}

void ASiftWidgetImp::update()
{

}

void ASiftWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("ASiftWidget", "SIFT Parameters", nullptr));
  mLabelFeaturesNumber->setText(QApplication::translate("ASiftWidget", "Features Number:"));
  mLabelOctaveLayers->setText(QApplication::translate("ASiftWidget", "Octave Layers:"));
  mLabelContrastThreshold->setText(QApplication::translate("ASiftWidget", "Contrast Threshold:"));
  mLabelEdgeThreshold->setText(QApplication::translate("ASiftWidget", "Edge Threshold:"));
  mLabelSigma->setText(QApplication::translate("ASiftWidget", "Sigma:"));
  mLabelMinTilt->setText(QApplication::translate("ASiftWidget", "MinTilt:"));
  mLabelMaxTilt->setText(QApplication::translate("ASiftWidget", "MaxTilt:"));
}

} // namespace photomatch
