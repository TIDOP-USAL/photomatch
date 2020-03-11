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


#include "MserWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

MserWidgetImp::MserWidgetImp(QWidget *parent)
  : MserWidget (parent),
    mGroupBox(new QGroupBox(this)),
    mLabelDelta(new QLabel(this)),
    mDelta(new QSpinBox(this)),
    mLabelMinArea(new QLabel(this)),
    mMinArea(new QSpinBox(this)),
    mLabelMaxArea(new QLabel(this)),
    mMaxArea(new QSpinBox(this)),
    mLabelMaxVariation(new QLabel(this)),
    mMaxVariation(new QDoubleSpinBox(this)),
    mLabelMinDiversity(new QLabel(this)),
    mMinDiversity(new QDoubleSpinBox(this)),
    mLabelMaxEvolution(new QLabel(this)),
    mMaxEvolution(new QSpinBox(this)),
    mLabelAreaThreshold(new QLabel(this)),
    mAreaThreshold(new QDoubleSpinBox(this)),
    mLabelMinMargin(new QLabel(this)),
    mMinMargin(new QDoubleSpinBox(this)),
    mLabelEdgeBlurSize(new QLabel(this)),
    mEdgeBlurSize(new QSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

MserWidgetImp::~MserWidgetImp()
{

}

int MserWidgetImp::delta() const
{
  return mDelta->value();
}

int MserWidgetImp::minArea() const
{
  return mMinArea->value();
}

int MserWidgetImp::maxArea() const
{
  return mMaxArea->value();
}

double MserWidgetImp::maxVariation() const
{
  return mMaxVariation->value();
}

double MserWidgetImp::minDiversity() const
{
  return mMinDiversity->value();
}

int MserWidgetImp::maxEvolution() const
{
  return mMaxEvolution->value();
}

double MserWidgetImp::areaThreshold() const
{
  return mAreaThreshold->value();
}

double MserWidgetImp::minMargin() const
{
  return mMinMargin->value();
}

int MserWidgetImp::edgeBlurSize() const
{
  return mEdgeBlurSize->value();
}

void MserWidgetImp::setDelta(int delta)
{
  const QSignalBlocker blockerDelta(mDelta);
  mDelta->setValue(delta);
}

void MserWidgetImp::setMinArea(int minArea)
{
  const QSignalBlocker blockerMinArea(mMinArea);
  mMinArea->setValue(minArea);
}

void MserWidgetImp::setMaxArea(int maxArea)
{
  const QSignalBlocker blockerMaxArea(mMaxArea);
  //mMinArea->setRange(0, mMaxArea->value() - 1);
  //mMaxArea->setRange(mMinArea->value() + 1, 100000);
  mMaxArea->setValue(maxArea);
}

void MserWidgetImp::setMaxVariation(double maxVariation)
{
  const QSignalBlocker blockerMaxVariation(mMaxVariation);
  mMaxVariation->setValue(maxVariation);
}

void MserWidgetImp::setMinDiversity(double minDiversity)
{
  const QSignalBlocker blockerMinDiversity(mMinDiversity);
  mMinDiversity->setValue(minDiversity);
}

void MserWidgetImp::setMaxEvolution(int maxEvolution)
{
  const QSignalBlocker blockerMaxEvolution(mMaxEvolution);
  mMaxEvolution->setValue(maxEvolution);
}

void MserWidgetImp::setAreaThreshold(double areaThreshold)
{
  const QSignalBlocker blockerAreaThreshold(mAreaThreshold);
  mAreaThreshold->setValue(areaThreshold);
}

void MserWidgetImp::setMinMargin(double minMargin)
{
  const QSignalBlocker blockerMinMargin(mMinMargin);
  mMinMargin->setValue(minMargin);
}

void MserWidgetImp::setEdgeBlurSize(int edgeBlurSize)
{
  const QSignalBlocker blockerEdgeBlurSize(mEdgeBlurSize);
  mEdgeBlurSize->setValue(edgeBlurSize);
}

void MserWidgetImp::update()
{
  //mMinArea->setRange(0, mMaxArea->value() - 1);
  //mMaxArea->setRange(mMinArea->value() + 1, 100000);
}

void MserWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("MserWidgetImp", "MSER Parameters"));
  mLabelDelta->setText(QApplication::translate("MserWidgetImp", "Delta:"));
  mLabelMinArea->setText(QApplication::translate("MserWidgetImp", "Min Area:"));
  mLabelMaxArea->setText(QApplication::translate("MserWidgetImp", "Max Area:"));
  mLabelMaxVariation->setText(QApplication::translate("MserWidgetImp", "Max Variation:"));
  mLabelMinDiversity->setText(QApplication::translate("MserWidgetImp", "Min Diversity:"));
  mLabelMaxEvolution->setText(QApplication::translate("MserWidgetImp", "Max Evolution:"));
  mLabelAreaThreshold->setText(QApplication::translate("MserWidgetImp", "Area Threshold:"));
  mLabelMinMargin->setText(QApplication::translate("MserWidgetImp", "Min Margin:"));
  mLabelEdgeBlurSize->setText(QApplication::translate("MserWidgetImp", "Edge Blur Size:"));
}

void MserWidgetImp::reset()
{
  const QSignalBlocker blockerDelta(mDelta);
  const QSignalBlocker blockerMinArea(mMinArea);
  const QSignalBlocker blockerMaxArea(mMaxArea);
  const QSignalBlocker blockerMaxVariation(mMaxVariation);
  const QSignalBlocker blockerMinDiversity(mMinDiversity);
  const QSignalBlocker blockerMaxEvolution(mMaxEvolution);
  const QSignalBlocker blockerAreaThreshold(mAreaThreshold);
  const QSignalBlocker blockerMinMargin(mMinMargin);
  const QSignalBlocker blockerEdgeBlurSize(mEdgeBlurSize);

  mDelta->setValue(5);
  mMinArea->setValue(60);
  mMaxArea->setValue(14400);
  mMaxVariation->setValue(0.25);
  mMinDiversity->setValue(.2);
  mMaxEvolution->setValue(200);
  mAreaThreshold->setValue(1.01);
  mMinMargin->setValue(0.003);
  mEdgeBlurSize->setValue(5);
}

void MserWidgetImp::initUI()
{
  this->setWindowTitle("MSER");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mLabelDelta, 0, 0);
  mDelta->setRange(0, 10000);
  propertiesLayout->addWidget(mDelta, 0, 1);

  propertiesLayout->addWidget(mLabelMinArea, 1, 0);
  mMinArea->setRange(0, 100000);
  propertiesLayout->addWidget(mMinArea, 1, 1);

  propertiesLayout->addWidget(mLabelMaxArea, 2, 0);
  mMaxArea->setRange(0, 100000);
  propertiesLayout->addWidget(mMaxArea, 2, 1);

  propertiesLayout->addWidget(mLabelMaxVariation, 3, 0);
  mMaxVariation->setSingleStep(0.01);
  propertiesLayout->addWidget(mMaxVariation, 3, 1);

  propertiesLayout->addWidget(mLabelMinDiversity, 4, 0);
  mMinDiversity->setSingleStep(0.1);
  propertiesLayout->addWidget(mMinDiversity, 4, 1);

  propertiesLayout->addWidget(mLabelMaxEvolution, 5, 0);
  mMaxEvolution->setRange(0, 10000);
  propertiesLayout->addWidget(mMaxEvolution, 5, 1);

  propertiesLayout->addWidget(mLabelAreaThreshold, 6, 0);
  mAreaThreshold->setRange(0, 99.99);
  mAreaThreshold->setSingleStep(0.01);
  propertiesLayout->addWidget(mAreaThreshold, 6, 1);

  propertiesLayout->addWidget(mLabelMinMargin, 7, 0);
  mMinMargin->setDecimals(3);
  mMinMargin->setSingleStep(0.001);
  propertiesLayout->addWidget(mMinMargin, 7, 1);

  propertiesLayout->addWidget(mLabelEdgeBlurSize, 8, 0);
  mEdgeBlurSize->setRange(0, 10000);
  propertiesLayout->addWidget(mEdgeBlurSize, 8, 1);

  this->retranslate();
  this->reset(); /// set default values
  this->update();
}

void MserWidgetImp::initSignalAndSlots()
{
  connect(mDelta,           SIGNAL(valueChanged(int)),       this, SIGNAL(deltaChange(int)));
  connect(mMinArea,         SIGNAL(valueChanged(int)),       this, SIGNAL(minAreaChange(int)));
  connect(mMaxArea,         SIGNAL(valueChanged(int)),       this, SIGNAL(maxAreaChange(int)));
  connect(mMaxVariation,    SIGNAL(valueChanged(double)),    this, SIGNAL(maxVariationChange(double)));
  connect(mMinDiversity,    SIGNAL(valueChanged(double)),    this, SIGNAL(minDiversityChange(double)));
  connect(mMaxEvolution,    SIGNAL(valueChanged(int)),       this, SIGNAL(maxEvolutionChange(int)));
  connect(mAreaThreshold,   SIGNAL(valueChanged(double)),    this, SIGNAL(areaThresholdChange(double)));
  connect(mMinMargin,       SIGNAL(valueChanged(double)),    this, SIGNAL(minMarginChange(double)));
  connect(mEdgeBlurSize,    SIGNAL(valueChanged(int)),       this, SIGNAL(edgeBlurSizeChange(int)));
}

void MserWidgetImp::changeEvent(QEvent *event)
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

