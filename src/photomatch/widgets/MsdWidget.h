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


#ifndef PHOTOMATCH_MSD_WIDGET_H
#define PHOTOMATCH_MSD_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QDoubleSpinBox;
class QSpinBox;
class QCheckBox;

namespace photomatch
{

class PHOTOMATCH_EXPORT MsdWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  MsdWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~MsdWidget() = default;

  virtual double thresholdSaliency() const = 0;
  virtual int pathRadius() const = 0;
  virtual int knn() const = 0;
  virtual int areaRadius() const = 0;
  virtual double scaleFactor() const = 0;
  virtual int NMSRadius() const = 0;
  virtual int nScales() const = 0;
  virtual int NMSScaleR() const = 0;
  virtual bool computeOrientations() const = 0;
  virtual bool affineMSD() const = 0;
  virtual int tilts() const = 0;

signals:

  void thresholdSaliencyChange(double);
  void pathRadiusChange(int);
  void KNNChange(int);
  void areaRadiusChange(int);
  void scaleFactorChange(double);
  void NMSRadiusChange(int);
  void nScalesChange(int);
  void NMSScaleRChange(int);
  void computeOrientationsChange(bool);
  void affineMSDChange(bool);
  void tiltsChange(int);

public slots:

  virtual void setThresholdSaliency(double thresholdSaliency) = 0;
  virtual void setPatchRadius(int pathRadius) = 0;
  virtual void setKNN(int knn) = 0;
  virtual void setAreaRadius(int areaRadius) = 0;
  virtual void setScaleFactor(double scaleFactor) = 0;
  virtual void setNMSRadius(int NMSRadius) = 0;
  virtual void setNScales(int nScales) = 0;
  virtual void setNMSScaleR(int NMSScaleR) = 0;
  virtual void setComputeOrientations(bool computeOrientations) = 0;
  virtual void setAffineMSD(bool affineMSD) = 0;
  virtual void setTilts(int tilts) = 0;

};

class PHOTOMATCH_EXPORT MsdWidgetImp
  : public MsdWidget
{
  Q_OBJECT

public:

  MsdWidgetImp(QWidget *parent = nullptr);
  ~MsdWidgetImp() override;


// IMsdWidget interface

public:

  double thresholdSaliency() const override;
  int pathRadius() const override;
  int knn() const override;
  int areaRadius() const override;
  double scaleFactor() const override;
  int NMSRadius() const override;
  int nScales() const override;
  int NMSScaleR() const override;
  bool computeOrientations() const override;
  bool affineMSD() const override;
  int tilts() const override;

public slots:

  void setThresholdSaliency(double thresholdSaliency) override;
  void setPatchRadius(int pathRadius) override;
  void setKNN(int knn) override;
  void setAreaRadius(int areaRadius) override;
  void setScaleFactor(double scaleFactor) override;
  void setNMSRadius(int NMSRadius) override;
  void setNScales(int nScales) override;
  void setNMSScaleR(int NMSScaleR) override;
  void setComputeOrientations(bool computeOrientations) override;
  void setAffineMSD(bool affineMSD) override;
  void setTilts(int tilts) override;

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  void init() override;

protected:

  QDoubleSpinBox *mThresholdSaliency;
  QSpinBox *mPathRadius;
  QSpinBox *mKNN;
  QSpinBox *mAreaRadius;
  QDoubleSpinBox *mScaleFactor;
  QSpinBox *mNMSRadius;
  QSpinBox *mNScales;
  QSpinBox *mNMSScaleR;
  QCheckBox *mComputeOrientations;
  QCheckBox *mAffineMSD;
  QSpinBox *mTilts;

};

} // namespace photomatch

#endif // PHOTOMATCH_MSD_WIDGET_H
