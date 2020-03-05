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


#ifndef PHOTOMATCH_KAZE_WIDGET_H
#define PHOTOMATCH_KAZE_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QCheckBox;
class QSpinBox;
class QDoubleSpinBox;
class QComboBox;

namespace photomatch
{

/*!
 * \brief The IKazeWidget class
 *
 * Multiscale 2D feature detection and description algorithm in nonlinear scale spaces.
 *
 * Alcantarilla P.F., Bartoli A., Davison A.J. (2012) KAZE Features.
 * In: Fitzgibbon A., Lazebnik S., Perona P., Sato Y., Schmid C. (eds)
 * Computer Vision – ECCV 2012. ECCV 2012. Lecture Notes in Computer
 * Science, vol 7577. Springer, Berlin, Heidelberg
 *
 * https://www.doc.ic.ac.uk/~ajd/Publications/alcantarilla_etal_eccv2012.pdf
 */
class PHOTOMATCH_EXPORT KazeWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  KazeWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~KazeWidget() = default;

  /*!
   * \brief Extended descriptor
   * \return true if use extended 128-element descriptors or false if use 64-element descriptors (Default)
   */
  virtual bool extendedDescriptor() const = 0;

  /*!
   * \brief Use of upright descriptors (non rotation-invariant)
   * \return true if use upright descriptors (Default=false)
   */
  virtual bool upright() const = 0;

  /*!
   * \brief Detector response threshold to accept point
   * \return threshold
   */
  virtual double threshold() const = 0;

  /*!
   * \brief Maximum octave evolution of the image
   * \return octaves
   */
  virtual int octaves() const = 0;

  /*!
   * \brief Default number of sublevels per scale level
   * \return
   */
  virtual int octaveLayers() const = 0;

  /*!
   * \brief Diffusivity type
   * \return DIFF_PM_G1, DIFF_PM_G2 (default), DIFF_WEICKERT or DIFF_CHARBONNIER
   */
  virtual QString diffusivity() const = 0;

signals:

  void extendedDescriptorChange(bool);
  void uprightChange(bool);
  void thresholdChange(double);
  void octavesChange(int);
  void octaveLayersChange(int);
  void diffusivityChange(QString);

public slots:

  /*!
   * \brief Set extended descriptor
   * \param[in] extended true for use extended 128-element descriptors or false for use 64-element descriptors (default)
   */
  virtual void setExtendedDescriptor(bool extended) = 0;

  /*!
   * \brief Set to enable use of upright descriptors (non rotation-invariant)
   * \param[in] upright
   */
  virtual void setUpright(bool upright) = 0;

  /*!
   * \brief Set the detector response threshold to accept point
   * \param[in] threshold Threshold
   */
  virtual void setThreshold(double threshold) = 0;

  /*!
   * \brief Set the maximum octave evolution of the image
   * \param[in] octaves
   */
  virtual void setOctaves(int octaves) = 0;

  /*!
   * \brief Sets the default number of sublevels per scale level
   * \param[in] octaveLayers
   */
  virtual void setOctaveLayers(int octaveLayers) = 0;

  /*!
   * \brief Set diffusivity type
   * \param[in] diffusivity DIFF_PM_G1, DIFF_PM_G2 (default), DIFF_WEICKERT or DIFF_CHARBONNIER
   */
  virtual void setDiffusivity(const QString &diffusivity) = 0;

};

class PHOTOMATCH_EXPORT KazeWidgetImp
  : public KazeWidget
{
  Q_OBJECT

public:

  KazeWidgetImp(QWidget *parent = nullptr);
  ~KazeWidgetImp() override;

// IKazeWidget interface

  bool extendedDescriptor() const override;
  bool upright() const override;
  double threshold() const override;
  int octaves() const override;
  int octaveLayers() const override;
  QString diffusivity() const override;

public slots:

  void setExtendedDescriptor(bool extended) override;
  void setUpright(bool upright) override;
  void setThreshold(double threshold) override;
  void setOctaves(int octaves) override;
  void setOctaveLayers(int octaveLayers) override;
  void setDiffusivity(const QString &diffusivity) override;

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

  QCheckBox *mExtended;
  QCheckBox *mUpright;
  QDoubleSpinBox *mThreshold;
  QSpinBox *mOctaves;
  QSpinBox *mOctaveLayers;
  QComboBox *mDiffusivity;

};

} // namespace photomatch

#endif // PHOTOMATCH_KAZE_WIDGET_H
