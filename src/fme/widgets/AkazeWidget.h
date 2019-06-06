#ifndef FME_AKAZE_WIDGET_H
#define FME_AKAZE_WIDGET_H

#include "fme/fme_global.h"

#include <QWidget>

class QCheckBox;
class QSpinBox;
class QDoubleSpinBox;
class QComboBox;

namespace fme
{

class FME_EXPORT IAkazeWidget
  : public QWidget
{
  Q_OBJECT

public:

  IAkazeWidget(QWidget *parent = nullptr) : QWidget(parent){}
  virtual ~IAkazeWidget() = default;

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

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;

};

class FME_EXPORT AkazeWidget
  : public IAkazeWidget
{
  Q_OBJECT

public:

  AkazeWidget(QWidget *parent = nullptr);
  ~AkazeWidget() override;

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

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QComboBox *mDescriptorType;
  QSpinBox *mDescriptorSize;
  QSpinBox *mDescriptorChannels;
  QDoubleSpinBox *mThreshold;
  QSpinBox *mOctaves;
  QSpinBox *mOctaveLayers;
  QComboBox *mDiffusivity;

};

} // namespace fme

#endif // FME_AKAZE_WIDGET_H
