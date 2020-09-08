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


#include "RswheWidget.h"

#include <QSpinBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

RswheWidgetImp::RswheWidgetImp(QWidget *parent)
  : RswheWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelDescription(new QLabel(this)),
    mHistogramCut(HistogramCut::by_mean),
    mLabelHistogramDivisions(new QLabel(this)),
    mHistogramDivisions(new QSpinBox(this)),
    mHistogramCutByMean(new QRadioButton(this)),
    mHistogramCutByMedian(new QRadioButton(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

RswheWidgetImp::~RswheWidgetImp()
{

}

void RswheWidgetImp::initUI()
{
  this->setWindowTitle("RSWHE");
  this->setObjectName("RswheWidget");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout(mGroupBox);

  mLabelDescription->setWordWrap(true);
  QFont font;
  font.setBold(true);
  mLabelDescription->setFont(font);
  propertiesLayout->addWidget(mLabelDescription, 0, 0, 1, 2);

  propertiesLayout->addWidget(mHistogramCutByMean, 1, 0, 1, 2);

  propertiesLayout->addWidget(mHistogramCutByMedian, 2, 0, 1, 2);

  propertiesLayout->addWidget(mLabelHistogramDivisions, 3, 0, 1, 1);
  mHistogramDivisions->setRange(1, 256);
  propertiesLayout->addWidget(mHistogramDivisions, 3, 1, 1, 1);

  this->retranslate();
  this->reset(); // Set default values
  this->update();
}

void RswheWidgetImp::initSignalAndSlots()
{
  connect(mHistogramDivisions,    QOverload<int>::of(&QSpinBox::valueChanged), this, &RswheWidget::histogramDivisionsChange);
  connect(mHistogramCutByMean,    &QAbstractButton::released,                  this, &RswheWidgetImp::onHistogramCutByMean);
  connect(mHistogramCutByMedian,  &QAbstractButton::released,                  this, &RswheWidgetImp::onHistogramCutByMedian);
}

void RswheWidgetImp::reset()
{
  const QSignalBlocker blockerHistogramDivisions(mHistogramDivisions);

  mHistogramDivisions->setValue(2);
  mHistogramCut = HistogramCut::by_mean;
}

void RswheWidgetImp::update()
{
  const QSignalBlocker blockerHistogramCutByMean(mHistogramCutByMean);
  const QSignalBlocker blockerHistogramCutByMedian(mHistogramCutByMedian);
  if (mHistogramCut == HistogramCut::by_mean){
    mHistogramCutByMean->setChecked(true);
  } else {
    mHistogramCutByMedian->setChecked(true);
  }
}

void RswheWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("RswheWidget", "RSWHE Parameters"));
  mLabelDescription->setText(QApplication::translate("RswheWidget", "Recursively Separated and Weighted Histogram Equalization"));
  mHistogramCutByMean->setText(QApplication::translate("RswheWidget", "Histogram cut by mean"));
  mHistogramCutByMedian->setText(QApplication::translate("RswheWidget", "Histogram cut by median"));
  mLabelHistogramDivisions->setText(QApplication::translate("RswheWidget", "Histogram Divisions:"));
}

void RswheWidgetImp::onHistogramCutByMean()
{
  emit histogramCutChange(static_cast<int>(HistogramCut::by_mean));
}

void RswheWidgetImp::onHistogramCutByMedian()
{
  emit histogramCutChange(static_cast<int>(HistogramCut::by_median));
}

int RswheWidgetImp::histogramDivisions() const
{
  return mHistogramDivisions->value();
}

RswheWidget::HistogramCut RswheWidgetImp::histogramCut() const
{
  return mHistogramCut;
}

void RswheWidgetImp::setHistogramDivisions(int histogramDivisions)
{
  const QSignalBlocker blockerHistogramDivisions(mHistogramDivisions);
  mHistogramDivisions->setValue(histogramDivisions);
}

void RswheWidgetImp::setHistogramCut(RswheWidget::HistogramCut histogramCut)
{
  mHistogramCut = histogramCut;
  update();
}


} // namespace photomatch


