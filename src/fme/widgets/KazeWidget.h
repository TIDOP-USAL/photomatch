#ifndef FME_KAZE_WIDGET_H
#define FME_KAZE_WIDGET_H

#include "fme/fme_global.h"

#include <QWidget>

class QCheckBox;
class QSpinBox;
class QDoubleSpinBox;
class QComboBox;

namespace fme
{

class FME_EXPORT IKazeWidget
  : public QWidget
{
  Q_OBJECT

public:

  IKazeWidget(QWidget *parent = nullptr) : QWidget(parent){}
  virtual ~IKazeWidget() = default;

  /*!
   * \brief Extended descriptor
   * \return true (use extended 128-element descriptors) or false (use 64-element descriptors)
   */
  virtual bool extendedDescriptor() const = 0;

  virtual bool upright() const = 0;

  /*!
   * \brief Detector response threshold to accept point
   * \return threshold
   */
  virtual double threshold() const = 0;

  virtual int octaves() const = 0;

  virtual int octaveLayers() const = 0;

  /*!
   * \brief diffusivity
   * \return diffusivity
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
   * \param[in] extended true for use extended 128-element descriptors or false for use 64-element descriptors)
   */
  virtual void setExtendedDescriptor(bool extended) = 0;

  /*!
   * \brief Set to enable use of upright descriptors (non rotation-invariant)
   * \param[in] upright
   */
  virtual void setUpright(bool upright) = 0;
  virtual void setThreshold(double threshold) = 0;
  virtual void setOctaves(int octaves) = 0;
  virtual void setOctaveLayers(int octaveLayers) = 0;

  /*!
   * \brief Set diffusivity type
   * \param[in] diffusivity
   */
  virtual void setDiffusivity(const QString &diffusivity) = 0;

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;
};

class FME_EXPORT KazeWidget
  : public IKazeWidget
{
  Q_OBJECT

public:

  KazeWidget(QWidget *parent = nullptr);
  ~KazeWidget() override;

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

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QCheckBox *mExtended;
  QCheckBox *mUpright;
  QDoubleSpinBox *mThreshold;
  QSpinBox *mOctaves;
  QSpinBox *mOctaveLayers;
  QComboBox *mDiffusivity;

};

} // namespace fme

#endif // FME_KAZE_WIDGET_H
