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


#ifndef PHOTOMATCH_HMCLAHE_WIDGET_H
#define PHOTOMATCH_HMCLAHE_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QGroupBox;
class QLabel;
class QSpinBox;
class QDoubleSpinBox;

namespace photomatch
{

class PHOTOMATCH_EXPORT HmclaheWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  HmclaheWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~HmclaheWidget() = default;

  virtual QSize blockSize() const = 0;
  virtual double l() const = 0;
  virtual double phi() const  = 0;

signals:

  void blockSizeChange(QSize);
  void lChange(double);
  void phiChange(double);

public slots:

  virtual void setBlockSize(const QSize &blockSize) = 0;
  virtual void setL(double l) = 0;
  virtual void setPhi(double phi) = 0;

};




class PHOTOMATCH_EXPORT HmclaheWidgetImp
  : public HmclaheWidget
{
  Q_OBJECT

public:

  HmclaheWidgetImp(QWidget *parent = nullptr);
  ~HmclaheWidgetImp() override;

protected slots:

  void onBlockSizeXChange(int blockSizeX);
  void onBlockSizeYChange(int blockSizeY);

// HmclaheWidget interface

public:

  QSize blockSize() const override;
  double l() const override;
  double phi() const override;

public slots:

  void setBlockSize(const QSize &blockSize) override;
  void setL(double l) override;
  void setPhi(double phi) override;

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
  QLabel *mLabelDescription;
  QGroupBox *mGroupBoxBlocksize;
  QLabel *mLabelBlockSizeX;
  QSpinBox *mBlockSizeX;
  QLabel *mLabelBlockSizeY;
  QSpinBox *mBlockSizeY;
  QLabel *mLabelL;
  QDoubleSpinBox *mL;
  QLabel *mLabelPhi;
  QDoubleSpinBox *mPhi;

};

} // namespace photomatch

#endif // PHOTOMATCH_HMCLAHE_WIDGET_H
