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


#ifndef PHOTOMATCH_BRISK_WIDGET_H
#define PHOTOMATCH_BRISK_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"


#include <QWidget>

class QSpinBox;
class QDoubleSpinBox;

namespace photomatch
{

/*!
 * \brief Interface for BRISK Widgets class
 * Stefan Leutenegger, Margarita Chli, and Roland Yves Siegwart.
 * Brisk: Binary robust invariant scalable keypoints. In Computer
 * Vision (ICCV), 2011 IEEE International Conference on, pages
 * 2548–2555. IEEE, 2011
 * http://margaritachli.com/papers/ICCV2011paper.pdf
 */
class PHOTOMATCH_EXPORT BriskWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  BriskWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~BriskWidget() = default;

  /*!
   * \brief AGAST detection threshold score (Default=30)
   * \return Threshold
   */
  virtual int threshold() const = 0;

  /*!
   * \brief Detection octaves (Default=3)
   * \return
   */
  virtual int octaves() const = 0;

  /*!
   * \brief Pattern Scale (Default=1.0)
   * \return
   */
  virtual double patternScale() const = 0;

signals:

  void thresholdChange(int);
  void octavesChange(int);
  void patternScaleChange(double);

public slots:

  /*!
   * \brief Set the AGAST detection threshold score
   * \param[in] threshold AGAST detection threshold
   */
  virtual void setThreshold(int threshold) = 0;

  /*!
   * \brief Set detection octaves
   * \param[in] octaves Octaves
   */
  virtual void setOctaves(int octaves) = 0;

  /*!
   * \brief Set Pattern Scale
   * \param[in] patternScale Pattern Scale
   */
  virtual void setPatternScale(double patternScale) = 0;

};

class PHOTOMATCH_EXPORT BriskWidgetImp
  : public BriskWidget
{
  Q_OBJECT

public:

  BriskWidgetImp(QWidget *parent = nullptr);
  ~BriskWidgetImp() override;

// IBriskWidget interface

  int threshold() const override;
  int octaves() const override;
  double patternScale() const override;

public slots:

  void setThreshold(int threshold) override;
  void setOctaves(int octaves) override;
  void setPatternScale(double patternScale) override;

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mThreshold;
  QSpinBox *mOctaves;
  QDoubleSpinBox *mPatternScale;
};

} // namespace photomatch

#endif // PHOTOMATCH_BRISK_WIDGET_H
