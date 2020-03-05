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


#ifndef PHOTOMATCH_WALLIS_WIDGET_H
#define PHOTOMATCH_WALLIS_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QDoubleSpinBox;
class QSpinBox;

namespace photomatch
{

class PHOTOMATCH_EXPORT WallisWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  WallisWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~WallisWidget() = default;

  virtual double contrast() const = 0;
  virtual double brightness() const = 0;
  virtual int imposedAverage() const = 0;
  virtual int imposedLocalStdDev() const = 0;
  virtual int kernelSize() const = 0;

signals:

  void contrastChange(double);
  void brightnessChange(double);
  void imposedAverageChange(int);
  void imposedLocalStdDevChange(int);
  void kernelSizeChange(int);

public slots:

  virtual void setContrast(double contrast) = 0;
  virtual void setBrightness(double brightness) = 0;
  virtual void setImposedAverage(int imposedAverage) = 0;
  virtual void setImposedLocalStdDev(int imposedLocalStdDev) = 0;
  virtual void setKernelSize(int kernelSize) = 0;

};

class PHOTOMATCH_EXPORT WallisWidgetImp
  : public WallisWidget
{
  Q_OBJECT

public:

  WallisWidgetImp(QWidget *parent = nullptr);
  ~WallisWidgetImp() override;

// IWallisWidget interface

public:

  double contrast() const override;
  double brightness() const override;
  int imposedAverage() const override;
  int imposedLocalStdDev() const override;
  int kernelSize() const override;

public slots:

  void setContrast(double contrast) override;
  void setBrightness(double brightness) override;
  void setImposedAverage(int imposedAverage) override;
  void setImposedLocalStdDev(int imposedLocalStdDev) override;
  void setKernelSize(int kernelSize) override;

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

  QDoubleSpinBox *mContrast;
  QDoubleSpinBox *mBrightness;
  QSpinBox *mImposedAverage;
  QSpinBox *mImposedLocalStdDev;
  QSpinBox *mKernelSize;
};

} // namespace photomatch

#endif // PHOTOMATCH_WALLIS_WIDGET_H
