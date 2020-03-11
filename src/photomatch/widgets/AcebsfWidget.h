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


#ifndef PHOTOMATCH_ACEBSF_WIDGET_H
#define PHOTOMATCH_ACEBSF_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QGroupBox;
class QLabel;
class QSpinBox;
class QDoubleSpinBox;

namespace photomatch
{

class AcebsfWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  AcebsfWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~AcebsfWidget() = default;

  virtual QSize blockSize() const = 0;
  virtual double l() const = 0;
  virtual double k1() const  = 0;
  virtual double k2() const = 0;

signals:

  void blockSizeChange(QSize);
  void lChange(double);
  void k1Change(double);
  void k2Change(double);

public slots:

  virtual void setBlockSize(const QSize &blockSize) = 0;
  virtual void setL(double l) = 0;
  virtual void setK1(double k1) = 0;
  virtual void setK2(double k2) = 0;

};

class AcebsfWidgetImp
  : public AcebsfWidget
{
  Q_OBJECT

public:

  AcebsfWidgetImp(QWidget *parent = nullptr);
  ~AcebsfWidgetImp() override;

protected slots:

  void onBlockSizeXChange(int blockSizeX);
  void onBlockSizeYChange(int blockSizeY);

// IAcebsfWidget interface

public:

  QSize blockSize() const override;
  double l() const override;
  double k1() const override;
  double k2() const override;

public slots:

  void setBlockSize(const QSize &blockSize) override;
  void setL(double l) override;
  void setK1(double k1) override;
  void setK2(double k2) override;

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  void initUI() override;
  void initSignalAndSlots() override;

// QWidget interface

protected:

  void changeEvent(QEvent *event) override;

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
  QLabel *mLabelK1;
  QDoubleSpinBox *mK1;
  QLabel *mLabelK2;
  QDoubleSpinBox *mK2;


};

} // namespace photomatch

#endif // PHOTOMATCH_ACEBSF_WIDGET_H
