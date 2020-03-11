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


#ifndef PHOTOMATCH_FAST_WIDGET_H
#define PHOTOMATCH_FAST_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QGroupBox;
class QLabel;
class QSpinBox;
class QComboBox;
class QCheckBox;

namespace photomatch
{

/*!
 * \brief Interface for FAST Widgets class
 *
 */
class PHOTOMATCH_EXPORT FastWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  FastWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~FastWidget() = default;

  /*!
   * \brief threshold (Default=10)
   * \return
   */
  virtual int threshold() const = 0;

  /*!
   * \brief Non Maximal Suppression for removing adjacent corners (default=true)
   * \return
   */
  virtual bool nonmaxSuppression() const = 0;

  /*!
   * \brief Detector Types
   * - TYPE_5_8: FAST-5 decision tree whith the 8 pixels mask
   * - TYPE_7_12: FAST-7 decision tree whith the 12 pixels mask
   * - TYPE_9_16: FAST-9 decision tree whith the 16 pixels mask (default)
   * \return Detector Type
   */
  virtual QString detectorType() const = 0;

signals:

  void thresholdChange(int);
  void nonmaxSuppressionChange(bool);
  void detectorTypeChange(QString);

public slots:

  /*!
   * \brief Set the threshold
   * \param threshold Threshold
   */
  virtual void setThreshold(int threshold) = 0;

  /*!
   * \brief Set Non Maximal Suppression
   * \param[in] nonmaxSuppression Non Maximal Suppression for removing adjacent corners (Default=true)
   */
  virtual void setNonmaxSuppression(bool nonmaxSuppression) = 0;

  /*!
   * \brief Set the Detector Type
   * Suported types:
   * - TYPE_5_8: FAST-5 decision tree whith the 8 pixels mask
   * - TYPE_7_12: FAST-7 decision tree whith the 12 pixels mask
   * - TYPE_9_16: FAST-9 decision tree whith the 16 pixels mask (default)
   *
   * \param[in] detectorType Detector Type
   */
  virtual void setDetectorType(QString detectorType) = 0;

};

class PHOTOMATCH_EXPORT FastWidgetImp
  : public FastWidget
{

  Q_OBJECT

public:

  FastWidgetImp(QWidget *parent = nullptr);
  ~FastWidgetImp() override;

// IFastWidget interface

public:

  int threshold() const override;
  bool nonmaxSuppression() const override;
  QString detectorType() const override;

public slots:

  void setThreshold(int threshold) override;
  void setNonmaxSuppression(bool nonmaxSuppression) override;
  void setDetectorType(QString detectorType) override;

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
  QLabel *mLabelThreshold;
  QSpinBox *mThreshold;
  QCheckBox *mNonmaxSuppression;
  QLabel *mLabelDetectorType;
  QComboBox *mDetectorType;

};

} // namespace photomatch

#endif // PHOTOMATCH_FAST_WIDGET_H
