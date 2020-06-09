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


#ifndef PHOTOMATCH_LATCH_WIDGET_H
#define PHOTOMATCH_LATCH_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QGroupBox;
class QLabel;
class QComboBox;
class QCheckBox;
class QSpinBox;

namespace photomatch
{

class PHOTOMATCH_EXPORT LatchWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  LatchWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~LatchWidget() = default;

  virtual QString bytes() const = 0;
  virtual bool rotationInvariance() const = 0;
  virtual int halfSsdSize() const = 0;

signals:

  void bytesChange(QString);
  void rotationInvarianceChange(bool);
  void halfSsdSizeChange(int);

public slots:

  virtual void setBytes(const QString &bytes) = 0;
  virtual void setRotationInvariance(bool rotationInvariance) = 0;
  virtual void setHalfSsdSize(int halfSsdSize) = 0;

};




class PHOTOMATCH_EXPORT LatchWidgetImp
  : public LatchWidget
{
  Q_OBJECT

public:

  LatchWidgetImp(QWidget *parent = nullptr);
  ~LatchWidgetImp() override;

// LatchWidget interface

public:

  QString bytes() const override;
  bool rotationInvariance() const override;
  int halfSsdSize() const override;

public slots:

  void setBytes(const QString &bytes) override;
  void setRotationInvariance(bool rotationInvariance) override;
  void setHalfSsdSize(int halfSsdSize) override;

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
  QLabel *mLabelBytes;
  QComboBox *mBytes;
  QCheckBox *mRotationInvariance;
  QLabel *mLabelHalfSsdSize;
  QSpinBox *mHalfSsdSize;

};



} // namespace photomatch

#endif // PHOTOMATCH_LATCH_WIDGET_H
