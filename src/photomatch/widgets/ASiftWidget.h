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


#ifndef PHOTOMATCH_ASIFT_WIDGET_H
#define PHOTOMATCH_ASIFT_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QGroupBox;
class QLabel;
class QSpinBox;
class QDoubleSpinBox;

namespace photomatch
{

/*!
 * \brief Interface SIFT Widget
 */
class PHOTOMATCH_EXPORT ASiftWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  ASiftWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~ASiftWidget() = default;

  /*!
   * \brief featuresNumber
   * \return
   */
  virtual int featuresNumber() const = 0;

  /*!
   * \brief octaveLayers
   * \return
   */
  virtual int octaveLayers() const = 0;

  /*!
   * \brief contrastThreshold
   * \return
   */
  virtual double contrastThreshold() = 0;

  /*!
   * \brief edgeThreshold
   * \return
   */
  virtual double edgeThreshold() = 0;

  /*!
   * \brief sigma
   * \return
   */
  virtual double sigma() = 0;

  virtual int minTilt() const = 0;
  virtual int maxTilt() const = 0;

signals:

  void featuresNumberChange(int);
  void octaveLayersChange(int);
  void contrastThresholdChange(double);
  void edgeThresholdChange(double);
  void sigmaChange(double);
  void minTiltChange(int);
  void maxTiltChange(int);

public slots:

  /*!
   * \brief setFeaturesNumber
   * \param featuresNumber
   */
  virtual void setFeaturesNumber(int featuresNumber) = 0;

  /*!
   * \brief setOctaveLayers
   * \param octaveLayers
   */
  virtual void setOctaveLayers(int octaveLayers) = 0;

  /*!
   * \brief setContrastThreshold
   * \param contrastThreshold
   */
  virtual void setContrastThreshold(double contrastThreshold) = 0;

  /*!
   * \brief setEdgeThreshold
   * \param edgeThreshold
   */
  virtual void setEdgeThreshold(double edgeThreshold) = 0;

  /*!
   * \brief setSigma
   * \param sigma
   */
  virtual void setSigma(double sigma) = 0;

  virtual void setMinTilt(int minTilt) = 0;
  virtual void setMaxTilt(int maxTilt) = 0;

};




class PHOTOMATCH_EXPORT ASiftWidgetImp
  : public ASiftWidget
{
  Q_OBJECT

public:

  ASiftWidgetImp(QWidget *parent = nullptr);
  ~ASiftWidgetImp() override;

// ASiftWidget interface

public:

  int featuresNumber() const override;
  int octaveLayers() const override;
  double contrastThreshold() override;
  double edgeThreshold() override;
  double sigma() override;
  int minTilt() const override;
  int maxTilt() const override;

public slots:

  void setFeaturesNumber(int featuresNumber) override;
  void setOctaveLayers(int octaveLayers) override;
  void setContrastThreshold(double contrastThreshold) override;
  void setEdgeThreshold(double edgeThreshold) override;
  void setSigma(double sigma) override;
  void setMinTilt(int minTilt) override;
  void setMaxTilt(int maxTilt) override;

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
  QLabel *mLabelOctaveLayers;
  QSpinBox *mOctaveLayers;
  QLabel *mLabelContrastThreshold;
  QDoubleSpinBox *mContrastThreshold;
  QLabel *mLabelEdgeThreshold;
  QDoubleSpinBox *mEdgeThreshold;
  QLabel *mLabelSigma;
  QDoubleSpinBox *mSigma;
  QLabel *mLabelMinTilt;
  QSpinBox *mSpinBoxMinTilt;
  QLabel *mLabelMaxTilt;
  QSpinBox *mSpinBoxMaxTilt;
};

} // namespace photomatch

#endif // PHOTOMATCH_ASIFT_WIDGET_H
