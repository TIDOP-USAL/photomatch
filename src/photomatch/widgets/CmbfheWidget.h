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


#ifndef PHOTOMATCH_CMBFHE_WIDGET_H
#define PHOTOMATCH_CMBFHE_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QGroupBox;
class QLabel;
class QDoubleSpinBox;
class QSpinBox;

namespace photomatch
{

/*!
 * \brief Interface for CMBFHE Widgets class
 * F. Lamberti, B. Montrucchio, and A. Sanna, "CMBFHE: a novel contrast 
 * enhancement technique based on cascaded multistep binomial filtering 
 * histogram equalization," TCE, vol. 52, no. 3, 2006.
 */
class PHOTOMATCH_EXPORT CmbfheWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  CmbfheWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~CmbfheWidget() {}

  virtual QSize blockSize() const = 0;
   
  /// TODO: virtual QSize stepSize() const = 0;
  // S - Number of regions divided by the step size. S should >2xB. 
  // .This should be the "Bx2" or "Bx4" or "Bx8" etc multiple of 2. 
  // "S" should be B's power (i.e., 2,4,8,16,32,64,128...). 
  // Bigger S, better image quality, and slower.
  
signals:

  void blockSizeChange(QSize);
  //void stepSizeChange(QSize);
  
public slots:

  virtual void setBlockSize(const QSize &blockSize) = 0;
  //virtual void setStepSize(const QSize &stepSize) = 0;

};




class PHOTOMATCH_EXPORT CmbfheWidgetImp
  : public CmbfheWidget
{
  Q_OBJECT

public:

  CmbfheWidgetImp(QWidget *parent = nullptr);
  ~CmbfheWidgetImp() override;

protected slots:

  void onBlockSizeXChange(int blockSizeX);
  void onBlockSizeYChange(int blockSizeY);

// CmbfheWidget interface

public:

  QSize blockSize() const override;

public slots:

  void setBlockSize(const QSize &blockSize) override;

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

};

} // namespace photomatch

#endif // PHOTOMATCH_CMBFHE_WIDGET_H
