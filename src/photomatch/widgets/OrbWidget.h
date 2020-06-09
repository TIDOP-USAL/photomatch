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


#ifndef PHOTOMATCH_ORB_WIDGET_H
#define PHOTOMATCH_ORB_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QGroupBox;
class QLabel;
class QSpinBox;
class QDoubleSpinBox;
class QComboBox;

namespace photomatch
{

/*!
 * \brief Interface ORB Widget
 */
class PHOTOMATCH_EXPORT OrbWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  OrbWidget(QWidget *parent = nullptr)
    : PhotoMatchWidget(parent){}
  virtual ~OrbWidget() = default;

  virtual int featuresNumber() const = 0;
  virtual double scaleFactor() const = 0;
  virtual int levelsNumber() const = 0;
  virtual int edgeThreshold() const = 0;
  virtual int wta_k() const = 0;
  virtual QString scoreType() const = 0;
  virtual int patchSize() const = 0;
  virtual int fastThreshold() const = 0;

signals:

  void featuresNumberChange(int);
  void scaleFactorChange(double);
  void levelsNumberChange(int);
  void edgeThresholdChange(int);
  void wta_kChange(int);
  void scoreTypeChange(QString);
  void patchSizeChange(int);
  void fastThresholdChange(int);

public slots:

  virtual void setScaleFactor(double scaleFactor) = 0;
  virtual void setFeaturesNumber(int featuresNumber) = 0;
  virtual void setLevelsNumber(int levelsNumber) = 0;
  virtual void setEdgeThreshold(int edgeThreshold) = 0;
  virtual void setWTA_K(int WTA_K) = 0;
  virtual void setScoreType(const QString &scoreType) = 0;
  virtual void setPatchSize(int patchSize) = 0;
  virtual void setFastThreshold(int fastThreshold) = 0;

};




class PHOTOMATCH_EXPORT OrbWidgetImp
  : public OrbWidget
{
  Q_OBJECT

public:

  explicit OrbWidgetImp(QWidget *parent = nullptr);
  ~OrbWidgetImp() override;

// OrbWidget interface

public:

  int featuresNumber() const override;
  double scaleFactor() const override;
  int levelsNumber() const override;
  int edgeThreshold() const override;
  int wta_k() const override;
  QString scoreType() const override;
  int patchSize() const override;
  int fastThreshold() const override;

public slots:

  void setScaleFactor(double scaleFactor) override;
  void setFeaturesNumber(int featuresNumber) override;
  void setLevelsNumber(int levelsNumber) override;
  void setEdgeThreshold(int edgeThreshold) override;
  void setWTA_K(int WTA_K) override;
  void setScoreType(const QString &scoreType) override;
  void setPatchSize(int patchSize) override;
  void setFastThreshold(int fastThreshold) override;

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
  QLabel *mLabelFeaturesNumber;
  QSpinBox *mFeaturesNumber;
  QLabel *mLabelScaleFactor;
  QDoubleSpinBox *mScaleFactor;
  QLabel *mLabelLevelsNumber;
  QSpinBox *mLevelsNumber;
  QLabel *mLabelEdgeThreshold;
  QSpinBox *mEdgeThreshold;
  //QSpinBox *mFirstLevel;
  QLabel *mLabelWTA_K;
  QSpinBox *mWTA_K;
  QLabel *mLabelScoreType;
  QComboBox *mScoreType;
  QLabel *mLabelPatchSize;
  QSpinBox *mPatchSize;
  QLabel *mLabelFastThreshold;
  QSpinBox *mFastThreshold;

};

} // namespace photomatch

#endif // PHOTOMATCH_ORB_WIDGET_H
