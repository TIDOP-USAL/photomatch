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


#ifndef PHOTOMATCH_AKAZE_WIDGET_H
#define PHOTOMATCH_AKAZE_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QGroupBox;
class QCheckBox;
class QSpinBox;
class QDoubleSpinBox;
class QComboBox;
class QLabel;

namespace photomatch
{

class PHOTOMATCH_EXPORT AkazeWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  AkazeWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~AkazeWidget() = default;

  /*!
   * \brief Type of the extracted descriptor
   * \return KAZE, KAZE_UPRIGHT, MLDB or MLDB_UPRIGHT
   */
  virtual QString descriptorType() const = 0;

  /*!
   * \brief Size of the descriptor in bits. 0 -\> Full size
   * \return Descriptor size
   */
  virtual int descriptorSize() const = 0;

  /*!
   * \brief Number of channels in the descriptor [1, 2, 3 (default)]
   * \return Number of channels
   */
  virtual int descriptorChannels() const = 0;

  /*!
   * \brief Detector response threshold to accept point
   * \return threshold
   */
  virtual double threshold() const = 0;

  /*!
   * \brief Maximum octave evolution of the image
   * \return
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

  void descriptorTypeChange(QString);
  void descriptorSizeChange(int);
  void descriptorChannelsChange(int);
  void thresholdChange(double);
  void octavesChange(int);
  void octaveLayersChange(int);
  void diffusivityChange(QString);

public slots:

  /*!
   * \brief Set the type of the extracted descriptor
   * \param[in] descriptorType Descriptor type: KAZE, KAZE_UPRIGHT, MLDB or MLDB_UPRIGHT
   */
  virtual void setDescriptorType(const QString &descriptorType) = 0;

  /*!
   * \brief Set the size of the descriptor in bits.
   * \param[in] descriptorSize
   */
  virtual void setDescriptorSize(int descriptorSize) = 0;

  /*!
   * \brief Set the number of channels in the descriptor
   * \param[in] channels 1, 2 or 3 (default)
   */
  virtual void setDescriptorChannels(int channels) = 0;

  /*!
   * \brief Set the detector response threshold to accept point
   * \param[in] threshold
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

class PHOTOMATCH_EXPORT AkazeWidgetImp
  : public AkazeWidget
{
  Q_OBJECT

public:

  AkazeWidgetImp(QWidget *parent = nullptr);
  ~AkazeWidgetImp() override;

// IAkazeWidget interface

  QString descriptorType() const override;
  int descriptorSize() const override;
  int descriptorChannels() const override;
  double threshold() const override;
  int octaves() const override;
  int octaveLayers() const override;
  QString diffusivity() const override;

public slots:

  void setDescriptorType(const QString &descriptorType) override;
  void setDescriptorSize(int descriptorSize) override;
  void setDescriptorChannels(int channels) override;
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

// QWidget interface

protected:

  void changeEvent(QEvent *event) override;

protected:

  QGroupBox *mGroupBox;
  QLabel *mLabelDescriptorType;
  QComboBox *mDescriptorType;
  QLabel *mLabelDescriptorSize;
  QSpinBox *mDescriptorSize;
  QLabel *mLabelDescriptorChannels;
  QSpinBox *mDescriptorChannels;
  QLabel *mLabelThreshold;
  QDoubleSpinBox *mThreshold;
  QLabel *mLabelOctaves;
  QSpinBox *mOctaves;
  QLabel *mLabelOctaveLayers;
  QSpinBox *mOctaveLayers;
  QLabel *mLabelDiffusivity;
  QComboBox *mDiffusivity;

};

} // namespace photomatch

#endif // PHOTOMATCH_AKAZE_WIDGET_H
