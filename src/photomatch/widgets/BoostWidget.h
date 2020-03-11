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


#ifndef PHOTOMATCH_BOOST_WIDGET_H
#define PHOTOMATCH_BOOST_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QGroupBox;
class QCheckBox;
class QComboBox;
class QDoubleSpinBox;
class QLabel;

namespace photomatch
{

/*!
 * \brief Interface for BOOST Widgets
 */
class PHOTOMATCH_EXPORT BoostWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  BoostWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~BoostWidget() = default;

  virtual QString descriptorType() const = 0;
  virtual bool useOrientation() const = 0;
  virtual double scaleFactor() const = 0;

signals:

  void descriptorTypeChange(QString);
  void useOrientationChange(bool);
  void scaleFactorChange(double);
  
public slots:

  virtual void setDescriptorType(const QString &descriptorType) = 0;
  virtual void setUseOrientation(bool useOrientation) = 0;
  virtual void setScaleFactor(double scaleFactor) = 0;

};

class PHOTOMATCH_EXPORT BoostWidgetImp
  : public BoostWidget
{
  Q_OBJECT

public:

  BoostWidgetImp(QWidget *parent = nullptr);
  ~BoostWidgetImp() override;

// IBoostWidget interface

public:

  QString descriptorType() const override;
  bool useOrientation() const override;
  double scaleFactor() const override;
  
public slots:

  void setDescriptorType(const QString &descriptorType) override;
  void setUseOrientation(bool useOrientation) override;
  void setScaleFactor(double scaleFactor) override;
  
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
  QLabel *mLabelDescriptorType;
  QComboBox *mDescriptorType;
  QCheckBox *mUseOrientation;
  QDoubleSpinBox *mScaleFactor;
  
};

} // namespace photomatch

#endif // PHOTOMATCH_BOOST_WIDGET_H
