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


#ifndef PHOTOMATCH_VGG_WIDGET_H
#define PHOTOMATCH_VGG_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QGroupBox;
class QLabel;
class QCheckBox;
class QComboBox;
class QDoubleSpinBox;

namespace photomatch
{

/*!
 * \brief Interface for VGG Widgets
 */
class PHOTOMATCH_EXPORT VggWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  VggWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~VggWidget() = default;

  virtual QString descriptorType() const = 0;
  virtual double scaleFactor() const = 0;
  virtual double sigma() const = 0;
  virtual bool useNormalizeDescriptor() const = 0;
  virtual bool useNormalizeImage() const = 0;
  virtual bool useScaleOrientation() const = 0;

signals:

  void descriptorTypeChange(const QString &);
  void scaleFactorChange(double);
  void sigmaChange(double);
  void useNormalizeDescriptorChange(bool);
  void useNormalizeImageChange(bool);
  void useScaleOrientationChange(bool);

public slots:

  virtual void setDescriptorType(const QString &descriptorType) = 0;
  virtual void setScaleFactor(double scaleFactor) = 0;
  virtual void setSigma(double sigma) = 0;
  virtual void setUseNormalizeDescriptor(bool active) = 0;
  virtual void setUseNormalizeImage(bool active) = 0;
  virtual void setUseScaleOrientation(bool active) = 0;
};




class PHOTOMATCH_EXPORT VggWidgetImp
  : public VggWidget
{
  Q_OBJECT

public:

  VggWidgetImp(QWidget *parent = nullptr);
  ~VggWidgetImp() override;

// IVggWidget interface

public:

  QString descriptorType() const override;
  double scaleFactor() const override;
  double sigma() const override;
  bool useNormalizeDescriptor() const override;
  bool useNormalizeImage() const override;
  bool useScaleOrientation() const override;

public slots:

  void setDescriptorType(const QString &descriptorType) override;
  void setScaleFactor(double scaleFactor) override;
  void setSigma(double sigma) override;
  void setUseNormalizeDescriptor(bool active) override;
  void setUseNormalizeImage(bool active) override;
  void setUseScaleOrientation(bool active) override;

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
  QLabel *mLabelDescriptorType;
  QComboBox *mDescriptorType;
  //QLabel *mLabelScaleFactor;
  QDoubleSpinBox *mScaleFactor;
  QLabel *mLabelSigma;
  QDoubleSpinBox *mSigma;
  QCheckBox *mUseNormalizeDescriptor;
  QCheckBox *mUseNormalizeImage;
  QCheckBox *mUseScaleOrientation;

};

} // namespace photomatch

#endif // PHOTOMATCH_VGG_WIDGET_H
