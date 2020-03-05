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


#ifndef PHOTOMATCH_AGAST_WIDGET_H
#define PHOTOMATCH_AGAST_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QSpinBox;
class QComboBox;
class QCheckBox;

namespace photomatch
{

/*!
 * \brief Agast Widget Interface
 * AGAST: Adaptive and Generic Corner Detection Based on the Accelerated Segment Test
 *
 * Mair E., Hager G.D., Burschka D., Suppa M., Hirzinger G. (2010) Adaptive and Generic
 * Corner Detection Based on the Accelerated Segment Test. In: Daniilidis K., Maragos P.,
 * Paragios N. (eds) Computer Vision – ECCV 2010. ECCV 2010.
 * ecture Notes in Computer Science, vol 6312. Springer, Berlin, Heidelberg
 * https://mediatum.ub.tum.de/doc/1287456/1287456.pdf
 */
class PHOTOMATCH_EXPORT AgastWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  AgastWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~AgastWidget() = default;

  /*!
   * \brief threshold
   * The AST applies a minimum difference threshold when comparing
   * the value of a pixel on the pattern with the brightness of
   * the nucleus. This parameter controls the sensitivity of the
   * corner response.
   * A large threshold value results in few but therefore only
   * strong corners, while a small threshold value yields also
   * corners with smoother gradients.
   * \return
   */
  virtual int threshold() const = 0;

  /*!
   * \brief Non Maximal Suppression for removing adjacent corners
   * \return
   */
  virtual bool nonmaxSuppression() const = 0;

  /*!
   * \brief Detector Types
   * - AGAST_5_8: AGAST-5 decision tree whith the 8 pixels mask
   * - AGAST_7_12d: AGAST-7 decision tree whith the Diamond shaped 12 pixels mask
   * - AGAST_7_12s: AGAST-7 decision tree whith the Squared shaped 12 pixels mask
   * - OAST_9_16: OAST-9 (Optimal AST) decision tree whith the 16 pixels mask
   * \return Detector Type
   */
  virtual QString detectorType() const = 0;

signals:

  void thresholdChange(int);
  void nonmaxSuppressionChange(bool);
  void detectorTypeChange(QString);

public slots:

  /*!
   * \brief Set Threshold
   * \param[in] threshold Default=10
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
   * - AGAST_5_8: AGAST-5 decision tree whith the 8 pixels mask
   * - AGAST_7_12d: AGAST-7 decision tree whith the Diamond shaped 12 pixels mask
   * - AGAST_7_12s: AGAST-7 decision tree whith the Squared shaped 12 pixels mask
   * - OAST_9_16: OAST-9 (Optimal AST) decision tree whith the 16 pixels mask
   *
   * \param[in] detectorType Detector Type (Default = OAST_9_16)
   */
  virtual void setDetectorType(const QString &detectorType) = 0;

};

class PHOTOMATCH_EXPORT AgastWidgetImp
  : public AgastWidget
{
  Q_OBJECT

public:

  AgastWidgetImp(QWidget *parent = nullptr);
  ~AgastWidgetImp() override;

// IFastWidget interface

  int threshold() const override;
  bool nonmaxSuppression() const override;
  QString detectorType() const override;

public slots:

  void setThreshold(int threshold) override;
  void setNonmaxSuppression(bool nonmaxSuppression) override;
  void setDetectorType(const QString &detectorType) override;

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  void initUI() override;
  void initSignalAndSlots() override;

protected:

  QSpinBox *mThreshold;
  QCheckBox *mNonmaxSuppression;
  QComboBox *mDetectorType;

};

} // namespace photomatch

#endif // PHOTOMATCH_AGAST_WIDGET_H
