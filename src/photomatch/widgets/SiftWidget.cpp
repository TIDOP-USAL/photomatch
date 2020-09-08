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


#include "SiftWidget.h"

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

SiftWidgetImp::SiftWidgetImp(QWidget *parent)
  : SiftWidget(parent),
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
    mSigma(new QDoubleSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

SiftWidgetImp::~SiftWidgetImp()
{

}

int SiftWidgetImp::featuresNumber() const
{
  return mFeaturesNumber->value();
}

int SiftWidgetImp::octaveLayers() const
{
  return mOctaveLayers->value();
}

double SiftWidgetImp::contrastThreshold()
{
  return mContrastThreshold->value();
}

double SiftWidgetImp::edgeThreshold()
{
  return mEdgeThreshold->value();
}

double SiftWidgetImp::sigma()
{
  return mSigma->value();
}

void SiftWidgetImp::setFeaturesNumber(int featuresNumber)
{
  const QSignalBlocker blockerFeaturesNumber(mFeaturesNumber);
  mFeaturesNumber->setValue(featuresNumber);
}

void SiftWidgetImp::setOctaveLayers(int octaveLayers)
{
  const QSignalBlocker blockerFeaturesNumber(mOctaveLayers);
  mOctaveLayers->setValue(octaveLayers);
}

void SiftWidgetImp::setContrastThreshold(double contrastThreshold)
{
  const QSignalBlocker blockerContrastThreshold(mContrastThreshold);
  mContrastThreshold->setValue(contrastThreshold);
}

void SiftWidgetImp::setEdgeThreshold(double edgeThreshold)
{
  const QSignalBlocker blockerEdgeThreshold(mEdgeThreshold);
  mEdgeThreshold->setValue(edgeThreshold);
}

void SiftWidgetImp::setSigma(double sigma)
{
  const QSignalBlocker blockerSigma(mSigma);
  mSigma->setValue(sigma);
}


void SiftWidgetImp::initUI()
{
  this->setWindowTitle("SIFT");
  this->setObjectName("SiftWidget");

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

  this->retranslate();
  this->reset(); /// set default values
  this->update();
}

void SiftWidgetImp::initSignalAndSlots()
{
  connect(mFeaturesNumber,    QOverload<int>::of(&QSpinBox::valueChanged),          this, &SiftWidget::featuresNumberChange);
  connect(mOctaveLayers,      QOverload<int>::of(&QSpinBox::valueChanged),          this, &SiftWidget::octaveLayersChange);
  connect(mContrastThreshold, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &SiftWidget::contrastThresholdChange);
  connect(mEdgeThreshold,     QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &SiftWidget::edgeThresholdChange);
  connect(mSigma,             QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &SiftWidget::sigmaChange);
}

void SiftWidgetImp::reset()
{
  const QSignalBlocker blockerFeaturesNumber(mFeaturesNumber);
  const QSignalBlocker blockerOctaveLayers(mOctaveLayers);
  const QSignalBlocker blockerContrastThreshold(mContrastThreshold);
  const QSignalBlocker blockerEdgeThreshold(mEdgeThreshold);
  const QSignalBlocker blockerSigma(mSigma);

  mFeaturesNumber->setValue(5000);     // OpenCV default value = 0
  mOctaveLayers->setValue(3);          // OpenCV default value = 3
  mContrastThreshold->setValue(0.04);  // OpenCV default value = 0.04
  mEdgeThreshold->setValue(10.);
  mSigma->setValue(1.6);
}

void SiftWidgetImp::update()
{

}

void SiftWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("SiftWidget", "SIFT Parameters", nullptr));
  mLabelFeaturesNumber->setText(QApplication::translate("SiftWidget", "Features Number:"));
  mLabelOctaveLayers->setText(QApplication::translate("SiftWidget", "Octave Layers:"));
  mLabelContrastThreshold->setText(QApplication::translate("SiftWidget", "Contrast Threshold:"));
  mLabelEdgeThreshold->setText(QApplication::translate("SiftWidget", "Edge Threshold:"));
  mLabelSigma->setText(QApplication::translate("SiftWidget", "Sigma:"));
}

} // namespace photomatch
