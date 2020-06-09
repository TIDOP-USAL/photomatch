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


#ifndef PHOTOMATCH_KEYPOINTS_FILTER_WIDGET_H
#define PHOTOMATCH_KEYPOINTS_FILTER_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QGroupBox;
class QLabel;
class QSpinBox;
class QDoubleSpinBox;
class QCheckBox;

namespace photomatch
{

class PHOTOMATCH_EXPORT KeypointsFilterWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  KeypointsFilterWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~KeypointsFilterWidget() = default;

  virtual int nPoints() const = 0;
  virtual double minSize() const = 0;
  virtual double maxSize() const = 0;

  virtual bool isActiveFilterBest() const = 0;
  virtual bool isActiveFilterSize() const = 0;
  virtual bool isActiveRemoveDuplicated() const = 0;

signals:

  void nPointsChange(int);
  void minSizeChange(double);
  void maxSizeChange(double);

public slots:

  virtual void setNPoints(int nPoints) = 0;
  virtual void setMinSize(double minSize) = 0;
  virtual void setMaxSize(double maxSize) = 0;

  virtual void setActiveFilterBest(bool active) = 0;
  virtual void setActiveFilterSize(bool active) = 0;
  virtual void setActiveRemoveDuplicated(bool active) = 0;
};




class PHOTOMATCH_EXPORT KeypointsFilterWidgetImp
  : public KeypointsFilterWidget
{
  Q_OBJECT

public:

  KeypointsFilterWidgetImp(QWidget *parent = nullptr);
  ~KeypointsFilterWidgetImp() override;

// KeypointsFilterWidget interface

public:

  int nPoints() const override;
  double minSize() const override;
  double maxSize() const override;
  bool isActiveFilterBest() const override;
  bool isActiveFilterSize() const override;
  bool isActiveRemoveDuplicated() const override;

public slots:

  void setNPoints(int nPoints) override;
  void setMinSize(double minSize) override;
  void setMaxSize(double maxSize) override;
  void setActiveFilterBest(bool active) override;
  void setActiveFilterSize(bool active) override;
  void setActiveRemoveDuplicated(bool active) override;

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
  QCheckBox *mCheckBoxPointsNumber;

  QSpinBox *mPointsNumber;
  QCheckBox *mCheckBoxSize;
  QLabel *mLabelMinSize;
  QDoubleSpinBox *mMinSize;
  QLabel *mLabelMaxSize;
  QDoubleSpinBox *mMaxSize;
  QCheckBox *mCheckBoxRemoveDuplicated;
  bool bActiveFilterBest;
  bool bActiveFilterSize;
  bool bActiveRemoveDuplicated;
};

} // namespace photomatch

#endif // PHOTOMATCH_KEYPOINTS_FILTER_WIDGET_H
