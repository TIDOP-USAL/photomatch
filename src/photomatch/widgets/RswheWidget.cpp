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

namespace photomatch
{

RswheWidgetImp::RswheWidgetImp(QWidget *parent)
  : RswheWidget(parent),
    mHistogramCut(HistogramCut::by_mean),
    mHistogramDivisions(new QSpinBox(this)),
    mHistogramCutByMean(new QRadioButton(this)),
    mHistogramCutByMedian(new QRadioButton(this))
{
  init();

  retranslate();

  /// Signals and slots
  connect(mHistogramDivisions,    SIGNAL(valueChanged(int)),        this, SIGNAL(histogramDivisionsChange(int)));
  connect(mHistogramCutByMean,    SIGNAL(clicked()),                this, SLOT(onHistogramCutByMean()));
  connect(mHistogramCutByMedian,  SIGNAL(clicked()),                this, SLOT(onHistogramCutByMedian()));

}

RswheWidgetImp::~RswheWidgetImp()
{

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

}

void RswheWidgetImp::reset()
{
  const QSignalBlocker blockerHistogramDivisions(mHistogramDivisions);

  mHistogramDivisions->setValue(2);
  mHistogramCut = HistogramCut::by_mean;
}

void RswheWidgetImp::init()
{
  this->setWindowTitle("RSWHE");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("RSWHE Parameters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout(groupBox);

  QLabel *lbl = new QLabel(tr("Recursively Separated and Weighted Histogram Equalization"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  lbl->setFont(font);
  propertiesLayout->addWidget(lbl, 0, 0, 1, 2);

  mHistogramCutByMean->setText(tr("Histogram cut by mean"));
  propertiesLayout->addWidget(mHistogramCutByMean, 1, 0, 1, 2);

  mHistogramCutByMedian->setText(tr("Histogram cut by median"));
  propertiesLayout->addWidget(mHistogramCutByMedian, 2, 0, 1, 2);

  propertiesLayout->addWidget(new QLabel(tr("Histogram Divisions:")), 3, 0, 1, 1);
  mHistogramDivisions->setRange(1, 256);
  propertiesLayout->addWidget(mHistogramDivisions, 3, 1, 1, 1);

  reset(); /// set default values

  update();
}


} // namespace photomatch


