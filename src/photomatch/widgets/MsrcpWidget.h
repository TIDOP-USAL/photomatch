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


#ifndef PHOTOMATCH_MSRCP_WIDGET_H
#define PHOTOMATCH_MSRCP_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QDoubleSpinBox;

namespace photomatch
{

class PHOTOMATCH_EXPORT MsrcpWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  MsrcpWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~MsrcpWidget() = default;

  virtual double smallScale() const = 0;
  virtual double midScale() const  = 0;
  virtual double largeScale() const = 0;

signals:

  void smallScaleChange(double);
  void midScaleChange(double);
  void largeScaleChange(double);

public slots:

  virtual void setSmallScale(double smallScale) = 0;
  virtual void setMidScale(double midScale) = 0;
  virtual void setLargeScale(double largeScale) = 0;

};


class PHOTOMATCH_EXPORT MsrcpWidgetImp
  : public MsrcpWidget
{
  Q_OBJECT

public:

  MsrcpWidgetImp(QWidget *parent = nullptr);
  ~MsrcpWidgetImp() override = default;


// IMsrcpWidget interface

public:

  double smallScale() const override;
  double midScale() const override;
  double largeScale() const override;

public slots:

  void setSmallScale(double smallScale) override;
  void setMidScale(double midScale) override;
  void setLargeScale(double largeScale) override;

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  void init() override;

protected:

  QDoubleSpinBox *mSmallScale;
  QDoubleSpinBox *mMidScale;
  QDoubleSpinBox *mLargeScale;
};


} // namespace photomatch


#endif // PHOTOMATCH_MSRCP_WIDGET_H
