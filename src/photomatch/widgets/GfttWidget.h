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


#ifndef PHOTOMATCH_GFTT_WIDGET_H
#define PHOTOMATCH_GFTT_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QGroupBox;
class QLabel;
class QSpinBox;
class QDoubleSpinBox;
class QCheckBox;

namespace photomatch
{

class PHOTOMATCH_EXPORT GfttWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  GfttWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~GfttWidget() = default;

  virtual int maxFeatures() const = 0;
  virtual double qualityLevel() const = 0;
  virtual double minDistance() const = 0;
  virtual int blockSize() const = 0;
  virtual bool harrisDetector() const = 0;
  virtual double k() const = 0;

signals:

  void maxFeaturesChange(int);
  void qualityLevelChange(double);
  void minDistanceChange(double);
  void blockSizeChange(int);
  void harrisDetectorChange(bool);
  void kChange(double);

public slots:

  virtual void setMaxFeatures(int maxFeatures) = 0;
  virtual void setQualityLevel(double qlevel) = 0;
  virtual void setMinDistance(double minDistance) = 0;
  virtual void setBlockSize(int blockSize) = 0;
  virtual void setHarrisDetector(bool value) = 0;
  virtual void setK(double k) = 0;
};

class PHOTOMATCH_EXPORT GfttWidgetImp
  : public GfttWidget
{
  Q_OBJECT

public:

  GfttWidgetImp(QWidget *parent = nullptr);
  ~GfttWidgetImp() override;

// IGfttWidget interface

public:

  int maxFeatures() const override;
  double qualityLevel() const override;
  double minDistance() const override;
  int blockSize() const override;
  bool harrisDetector() const override;
  double k() const override;

public slots:

  void setMaxFeatures(int maxFeatures) override;
  void setQualityLevel(double qlevel) override;
  void setMinDistance(double minDistance) override;
  void setBlockSize(int blockSize) override;
  void setHarrisDetector(bool value) override;
  void setK(double k) override;

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
  QLabel *mLabelMaxFeatures;
  QSpinBox *mMaxFeatures;
  QLabel *mLabelQualityLevel;
  QDoubleSpinBox *mQualityLevel;
  QLabel *mLabelMinDistance;
  QDoubleSpinBox *mMinDistance;
  QLabel *mLabelBlockSize;
  QSpinBox *mBlockSize;
  QCheckBox *mHarrisDetector;
  QLabel *mLabelK;
  QDoubleSpinBox *mK;
};

} // namespace photomatch

#endif // PHOTOMATCH_GFTT_WIDGET_H
