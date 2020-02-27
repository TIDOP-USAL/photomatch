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


#ifndef PHOTOMATCH_RSWHE_WIDGET_H
#define PHOTOMATCH_RSWHE_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QSpinBox;
class QRadioButton;

namespace photomatch
{

class RswheWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  enum class HistogramCut{
    by_mean,
    by_median
  };

public:

  RswheWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~RswheWidget() = default;

  virtual int histogramDivisions() const = 0;
  virtual HistogramCut histogramCut() const = 0;

signals:

  void histogramDivisionsChange(int);
  void histogramCutChange(int);

public slots:

  virtual void setHistogramDivisions(int histogramDivisions) = 0;
  virtual void setHistogramCut(HistogramCut histogramCut) = 0;

};

class RswheWidgetImp
  : public RswheWidget
{
  Q_OBJECT

public:

  RswheWidgetImp(QWidget *parent = nullptr);
  ~RswheWidgetImp() override;

protected slots:

  void onHistogramCutByMean();
  void onHistogramCutByMedian();

// IRswheWidget interface

public:

  int histogramDivisions() const override;
  HistogramCut histogramCut() const override;

public slots:

  void setHistogramDivisions(int histogramDivisions) override;
  void setHistogramCut(HistogramCut histogramCut) override;

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  void initUI() override;
  void initSignalAndSlots() override;

protected:

  HistogramCut mHistogramCut;
  QSpinBox *mHistogramDivisions;
  QRadioButton *mHistogramCutByMean;
  QRadioButton *mHistogramCutByMedian;
};

} // namespace photomatch

Q_DECLARE_METATYPE(photomatch::RswheWidget::HistogramCut)

#endif // PHOTOMATCH_RSWHE_WIDGET_H
