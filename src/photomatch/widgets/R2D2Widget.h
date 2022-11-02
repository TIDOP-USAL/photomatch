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


#ifndef PHOTOMATCH_R2D2_WIDGET_H
#define PHOTOMATCH_R2D2_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QGroupBox;
class QCheckBox;
class QSpinBox;
class QDoubleSpinBox;
class QComboBox;
class QLabel;

namespace photomatch
{

class PHOTOMATCH_EXPORT R2D2Widget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  R2D2Widget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~R2D2Widget() = default;

  virtual double scaleF() const = 0;
  virtual int minSize() const = 0;
  virtual int maxSize() const = 0;
  virtual double minScale() const = 0;
  virtual double maxScale() const = 0;
  virtual double reliabilityThreshold() const = 0;
  virtual double repeatabilityThreshold() const = 0;

signals:

  void scaleFChanged(double);
  void minSizeChanged(int);
  void maxSizeChanged(int);
  void minScaleChanged(double);
  void maxScaleChanged(double);
  void reliabilityThresholdChanged(double);
  void repeatabilityThresholdChanged(double);

public slots:

  virtual void setScaleF(double scaleF) = 0;
  virtual void setMinSize(int size) = 0;
  virtual void setMaxSize(int size) = 0;
  virtual void setMinScale(double minScale) = 0;
  virtual void setMaxScale(double maxScale) = 0;
  virtual void setReliabilityThreshold(double reliabilityThreshold) = 0;
  virtual void setRepeatabilityThreshold(double repeatabilityThreshold) = 0;

};




class PHOTOMATCH_EXPORT R2D2WidgetImp
  : public R2D2Widget
{
  Q_OBJECT

public:

  R2D2WidgetImp(QWidget *parent = nullptr);
  ~R2D2WidgetImp() override;

// R2D2Widget interface

  double scaleF() const override;
  int minSize() const override;
  int maxSize() const override;
  double minScale() const override;
  double maxScale() const override;
  double reliabilityThreshold() const override;
  double repeatabilityThreshold() const override;

public slots:

  //¿Scale factor?
  void setScaleF(double scaleF) override;
  void setMinSize(int size) override;
  void setMaxSize(int size) override;
  void setMinScale(double minScale) override;
  void setMaxScale(double maxScale) override;
  void setReliabilityThreshold(double reliabilityThreshold) override;
  void setRepeatabilityThreshold(double repeatabilityThreshold) override;

// PhotoMatchWidget interface

private:

  void initUI() override;
  void initSignalAndSlots() override;

public slots:

  void reset() override;

protected slots:

  void update() override;
  void retranslate() override;

protected:

  QGroupBox *mGroupBox;
  QLabel *mLabelScaleF;
  QDoubleSpinBox *mDoubleSpinBoxScaleF;
  QLabel *mLabelMinSize;
  QSpinBox *mSpinBoxMinSize;
  QLabel *mLabelMaxSize;
  QSpinBox *mSpinBoxMaxSize;
  QLabel *mLabelMinScale;
  QDoubleSpinBox *mDoubleSpinBoxMinScale;
  QLabel *mLabelMaxScale;
  QDoubleSpinBox *mDoubleSpinBoxMaxScale;
  QLabel *mLabelReliabilityThreshold;
  QDoubleSpinBox *mDoubleSpinBoxReliabilityThreshold;
  QLabel *mLabelRepeatabilityThreshold;
  QDoubleSpinBox *mDoubleSpinBoxRepeatabilityThreshold;

};

} // namespace photomatch

#endif // PHOTOMATCH_R2D2_WIDGET_H
