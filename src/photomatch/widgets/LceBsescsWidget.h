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


#ifndef PHOTOMATCH_LCE_BSESCS_WIDGET_H
#define PHOTOMATCH_LCE_BSESCS_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QGroupBox;
class QLabel;
class QDoubleSpinBox;
class QSpinBox;

namespace photomatch
{

class PHOTOMATCH_EXPORT LceBsescsWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  LceBsescsWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~LceBsescsWidget() {}

  virtual QSize blockSize() const = 0;

signals:

  void blockSizeChange(QSize);

public slots:

  virtual void setBlockSize(const QSize &blockSize) = 0;

};


class PHOTOMATCH_EXPORT LceBsescsWidgetImp
  : public LceBsescsWidget
{
  Q_OBJECT

public:

  LceBsescsWidgetImp(QWidget *parent = nullptr);
  ~LceBsescsWidgetImp() override;

protected slots:

  void onBlockSizeXChange(int gx);
  void onBlockSizeYChange(int gy);

// ICLAHEWidget interface

public:

  QSize blockSize() const override;

public slots:

  void setBlockSize(const QSize &blockSize) override;

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

};

} // namespace photomatch

#endif // PHOTOMATCH_LCE_BSESCS_WIDGET_H
