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


#include "MsdWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

MsdWidgetImp::MsdWidgetImp(QWidget *parent)
  : MsdWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelThresholdSaliency(new QLabel(this)),
    mThresholdSaliency(new QDoubleSpinBox(this)),
    mLabelPathRadius(new QLabel(this)),
    mPathRadius(new QSpinBox(this)),
    mLabelKNN(new QLabel(this)),
    mKNN(new QSpinBox(this)),
    mLabelAreaRadius(new QLabel(this)),
    mAreaRadius(new QSpinBox(this)),
    mLabelScaleFactor(new QLabel(this)),
    mScaleFactor(new QDoubleSpinBox(this)),
    mLabelNMSRadius(new QLabel(this)),
    mNMSRadius(new QSpinBox(this)),
    mLabelNScales(new QLabel(this)),
    mNScales(new QSpinBox(this)),
    mLabelNMSScaleR(new QLabel(this)),
    mNMSScaleR(new QSpinBox(this)),
    mComputeOrientations(new QCheckBox(this)),
    mAffineMSD(new QCheckBox(this)),
    mLabelTilts(new QLabel(this)),
    mTilts(new QSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

MsdWidgetImp::~MsdWidgetImp()
{
}

double MsdWidgetImp::thresholdSaliency() const
{
  return  mThresholdSaliency->value();
}

int MsdWidgetImp::pathRadius() const
{
  return mPathRadius->value();
}

int MsdWidgetImp::knn() const
{
  return mKNN->value();
}

int MsdWidgetImp::areaRadius() const
{
  return mAreaRadius->value();
}

double MsdWidgetImp::scaleFactor() const
{
  return mScaleFactor->value();
}

int MsdWidgetImp::NMSRadius() const
{
  return mNMSRadius->value();
}

int MsdWidgetImp::nScales() const
{
  return mNScales->value();
}

int MsdWidgetImp::NMSScaleR() const
{
  return mNMSScaleR->value();
}

bool MsdWidgetImp::computeOrientations() const
{
  return mComputeOrientations->isChecked();
}

bool MsdWidgetImp::affineMSD() const
{
  return mAffineMSD->isChecked();
}

int MsdWidgetImp::tilts() const
{
  return mTilts->value();
}

void MsdWidgetImp::setThresholdSaliency(double thresholdSaliency)
{
  const QSignalBlocker blocker(mThresholdSaliency);
  mThresholdSaliency->setValue(thresholdSaliency);
}

void MsdWidgetImp::setPatchRadius(int pathRadius)
{
  const QSignalBlocker blocker(mPathRadius);
  mPathRadius->setValue(pathRadius);
}

void MsdWidgetImp::setKNN(int knn)
{
  const QSignalBlocker blocker(mKNN);
  mKNN->setValue(knn);
}

void MsdWidgetImp::setAreaRadius(int areaRadius)
{
  const QSignalBlocker blocker(mAreaRadius);
  mAreaRadius->setValue(areaRadius);
}

void MsdWidgetImp::setScaleFactor(double scaleFactor)
{
  const QSignalBlocker blocker(mScaleFactor);
  mScaleFactor->setValue(scaleFactor);
}

void MsdWidgetImp::setNMSRadius(int NMSRadius)
{
  const QSignalBlocker blocker(mNMSRadius);
  mNMSRadius->setValue(NMSRadius);
}

void MsdWidgetImp::setNScales(int nScales)
{
  const QSignalBlocker blocker(mNScales);
  mNScales->setValue(nScales);
}

void MsdWidgetImp::setNMSScaleR(int NMSScaleR)
{
  const QSignalBlocker blocker(mNMSScaleR);
  mNMSScaleR->setValue(NMSScaleR);
}

void MsdWidgetImp::setComputeOrientations(bool computeOrientations)
{
  mComputeOrientations->setChecked(computeOrientations);
}

void MsdWidgetImp::setAffineMSD(bool affineMSD)
{
  mAffineMSD->setChecked(affineMSD);
}

void MsdWidgetImp::setTilts(int tilts)
{
  const QSignalBlocker blocker(mTilts);
  mTilts->setValue(tilts);
}

void MsdWidgetImp::update()
{
}

void MsdWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("MsdWidgetImp", "MSD Parameters"));
  mLabelThresholdSaliency->setText(QApplication::translate("MsdWidgetImp", "Threshold Saliency:"));
  mLabelPathRadius->setText(QApplication::translate("MsdWidgetImp", "Path radius:"));
  mLabelKNN->setText(QApplication::translate("MsdWidgetImp", "KNN:"));
  mLabelAreaRadius->setText(QApplication::translate("MsdWidgetImp", "Area radius:"));
  mLabelScaleFactor->setText(QApplication::translate("MsdWidgetImp", "Scale factor:"));
  mLabelNMSRadius->setText(QApplication::translate("MsdWidgetImp", "NMS radius:"));
  mLabelNScales->setText(QApplication::translate("MsdWidgetImp", "N Scales:"));
  mLabelNMSScaleR->setText(QApplication::translate("MsdWidgetImp", "NMS Scale R:"));
  mComputeOrientations->setText(QApplication::translate("MsdWidgetImp", "Compute orientations"));
  mAffineMSD->setText(QApplication::translate("MsdWidgetImp", "Affine MSD"));
  mLabelTilts->setText(QApplication::translate("MsdWidgetImp", "Tilts:"));
}

void MsdWidgetImp::reset()
{
  const QSignalBlocker blocker1(mThresholdSaliency);
  const QSignalBlocker blocker2(mPathRadius);
  const QSignalBlocker blocker3(mKNN);
  const QSignalBlocker blocker4(mAreaRadius);
  const QSignalBlocker blocker5(mScaleFactor);
  const QSignalBlocker blocker6(mNMSRadius);
  const QSignalBlocker blocker7(mNScales);
  const QSignalBlocker blocker8(mNMSScaleR);
  const QSignalBlocker blocker9(mTilts);

  mThresholdSaliency->setValue(250);
  mPathRadius->setValue(3);
  mKNN->setValue(4);
  mAreaRadius->setValue(5);
  mScaleFactor->setValue(1.25);
  mNMSRadius->setValue(5);
  mNScales->setValue(-1);
  mNMSScaleR->setValue(0);
  mComputeOrientations->setChecked(false);
  mAffineMSD->setChecked(false);
  mTilts->setValue(3);
}

void MsdWidgetImp::initUI()
{
  this->setWindowTitle("MSD");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mLabelThresholdSaliency, 0, 0, 1, 1);
  mThresholdSaliency->setRange(0, 2000);
  mThresholdSaliency->setSingleStep(1);
  propertiesLayout->addWidget(mThresholdSaliency, 0, 1, 1, 1);

  propertiesLayout->addWidget(mLabelPathRadius, 1, 0, 1, 1);
  mPathRadius->setRange(1, 10);
  mPathRadius->setSingleStep(1);
  propertiesLayout->addWidget(mPathRadius, 1, 1, 1, 1);

  propertiesLayout->addWidget(mLabelKNN, 2, 0, 1, 1);
  mKNN->setRange(1,10);
  mKNN->setSingleStep(1);
  propertiesLayout->addWidget(mKNN, 2, 1, 1, 1);

  propertiesLayout->addWidget(mLabelAreaRadius, 3, 0, 1, 1);
  mAreaRadius->setRange(1, 10);
  mAreaRadius->setSingleStep(1);
  propertiesLayout->addWidget(mAreaRadius, 3, 1, 1, 1);

  propertiesLayout->addWidget(mLabelScaleFactor, 4, 0, 1, 1);
  mScaleFactor->setRange(1, 10);
  mScaleFactor->setSingleStep(0.05);
  propertiesLayout->addWidget(mScaleFactor, 4, 1, 1, 1);

  propertiesLayout->addWidget(mLabelNMSRadius, 5, 0, 1, 1);
  mNMSRadius->setRange(1, 10);
  mNMSRadius->setSingleStep(1);
  propertiesLayout->addWidget(mNMSRadius, 5, 1, 1, 1);

  propertiesLayout->addWidget(mLabelNScales, 6, 0, 1, 1);
  mNScales->setRange(-1, 10);
  mNScales->setSingleStep(1);
  propertiesLayout->addWidget(mNScales, 6, 1, 1, 1);

  propertiesLayout->addWidget(mLabelNMSScaleR, 7, 0, 1, 1);
  mNMSScaleR->setRange(0, 10);
  mNMSScaleR->setSingleStep(1);
  propertiesLayout->addWidget(mNMSScaleR, 7, 1, 1, 1);

  propertiesLayout->addWidget(mComputeOrientations, 8, 0, 1, 2); //Check orientations

  propertiesLayout->addWidget(mAffineMSD, 9, 0, 1, 2); //CheckAffine

  propertiesLayout->addWidget(mLabelTilts, 10, 0, 1, 1);
  mTilts->setRange(3,10);
  mTilts->setSingleStep(1);
  propertiesLayout->addWidget(mTilts, 10, 1, 1, 1);

  this->retranslate();
  this->reset(); // Set default values
  this->update();
}

void MsdWidgetImp::initSignalAndSlots()
{
  connect(mThresholdSaliency,   SIGNAL(valueChanged(double)),  this, SIGNAL(thresholdSaliencyChange(double)));
  connect(mPathRadius,          SIGNAL(valueChanged(int)),     this, SIGNAL(pathRadiusChange(int)));
  connect(mKNN,                 SIGNAL(valueChanged(int)),     this, SIGNAL(KNNChange(int)));
  connect(mAreaRadius,          SIGNAL(valueChanged(int)),     this, SIGNAL(areaRadiusChange(int)));
  connect(mScaleFactor,         SIGNAL(valueChanged(double)),  this, SIGNAL(scaleFactorChange(double)));
  connect(mNMSRadius,           SIGNAL(valueChanged(int)),     this, SIGNAL(NMSRadiusChange(int)));
  connect(mNScales,             SIGNAL(valueChanged(int)),     this, SIGNAL(nScalesChange(int)));
  connect(mNMSScaleR,           SIGNAL(valueChanged(int)),     this, SIGNAL(NMSScaleRChange(int)));
  connect(mComputeOrientations, SIGNAL(clicked(bool)),         this, SIGNAL(computeOrientationsChange(bool)));
  connect(mAffineMSD,           SIGNAL(clicked(bool)),         this, SIGNAL(affineMSDChange(bool)));
  connect(mTilts,               SIGNAL(valueChanged(int)),     this, SIGNAL(tiltsChange(int)));
}

void MsdWidgetImp::changeEvent(QEvent *event)
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
