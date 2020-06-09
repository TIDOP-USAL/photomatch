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


#ifndef PHOTOMATCH_CLAHE_WIDGET_H
#define PHOTOMATCH_CLAHE_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QGroupBox;
class QLabel;
class QDoubleSpinBox;
class QSpinBox;

namespace photomatch
{

/*!
 * \brief CLAHE (Contrast Limited Adaptive Histogram Equalization)
 * Equalizes the histogram of a grayscale image using Contrast Limited
 * Adaptive Histogram Equalization.
 */
class PHOTOMATCH_EXPORT ClaheWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  ClaheWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~ClaheWidget() {}

  virtual double clipLimit() const = 0;
  virtual QSize tileGridSize() const = 0;

signals:

  void clipLimitChange(double);
  void tileGridSizeChange(QSize);

public slots:

  virtual void setClipLimit(double clipLimit) = 0;
  virtual void setTilesGridSize (const QSize &tileGridSize) = 0;

};





class PHOTOMATCH_EXPORT ClaheWidgetImp
  : public ClaheWidget
{
  Q_OBJECT

public:

  ClaheWidgetImp(QWidget *parent = nullptr);
  ~ClaheWidgetImp() override;

protected slots:

  void onTilesGridXChange(int gx);
  void onTilesGridYChange(int gy);

// ClaheWidget interface

public:

  double clipLimit() const override;
  QSize tileGridSize() const override;

public slots:

  void setClipLimit(double clipLimit) override;
  void setTilesGridSize(const QSize &tileGridSize) override;

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
  QLabel *mLabelClipLimit;
  QDoubleSpinBox *mClipLimit;
  QGroupBox *mGroupBoxBlockSize;
  QLabel *mLabelTilesGridX;
  QSpinBox *mTilesGridX;
  QLabel *mLabelTilesGridY;
  QSpinBox *mTilesGridY;
};

} // namespace photomatch

#endif // PHOTOMATCH_CLAHE_WIDGET_H
