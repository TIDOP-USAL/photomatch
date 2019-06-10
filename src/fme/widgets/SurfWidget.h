#ifndef FME_SURF_WIDGET_H
#define FME_SURF_WIDGET_H

#include "fme/widgets/FmeWidget.h"

class QDoubleSpinBox;
class QSpinBox;
class QCheckBox;

namespace fme
{

/*!
 * \brief Interface SURF Widget
 */
class FME_EXPORT ISurfWidget
  : public FmeWidget
{

  Q_OBJECT

public:

  ISurfWidget(QWidget *parent = nullptr) : FmeWidget(parent){}
  virtual ~ISurfWidget() = default;

  /*!
   * \brief Threshold for hessian keypoint detector used in SURF
   * \return
   */
  virtual double hessianThreshold() const = 0;

  /*!
   * \brief Number of pyramid octaves the keypoint detector will use.
   * \return
   */
  virtual int octaves() const = 0;

  /*!
   * \brief Number of octave layers within each octave
   * \return
   */
  virtual int octaveLayers() const = 0;

  /*!
   * \brief Extended descriptor
   * \return true (use extended 128-element descriptors) or false (use 64-element descriptors)
   */
  virtual bool extendedDescriptor() const = 0;

  /*!
   * \brief Up-right or rotated features
   * \return true (do not compute orientation of features) or false (compute orientation)
   */
  virtual bool rotatedFeatures() const = 0;

signals:

  void hessianThresholdChange(double);
  void octavesChange(int);
  void octaveLayersChange(int);
  void extendedDescriptorChange(bool);
  void rotatedFeaturesChange(bool);

public slots:

  /*!
   * \brief Threshold for hessian keypoint detector used in SURF
   * \param[in] hessianThreshold
   */
  virtual void setHessianThreshold(double hessianThreshold) = 0;

  /*!
   * \brief Set the number of pyramid octaves
   * \param[in] octaves Number of pyramid octaves the keypoint detector will use.
   */
  virtual void setOctaves(int octaves) = 0;

  /*!
   * \brief Set the number of octave layers
   * \param[in] octaveLayers Number of octave layers within each octave
   */
  virtual void setOctaveLayers(int octaveLayers) = 0;

  /*!
   * \brief setExtendedDescriptor
   * \param[in] extendedDescriptor true for use extended 128-element descriptors or false for use 64-element descriptors)
   */
  virtual void setExtendedDescriptor(bool extendedDescriptor) = 0;

  /*!
   * \brief compute orientation of features
   * \param[in] rotatedFeatures false for compute orientation
   */
  virtual void setRotatedFeatures(bool rotatedFeatures) = 0;

};

class FME_EXPORT SurfWidget
  : public ISurfWidget
{

  Q_OBJECT

public:

  SurfWidget(QWidget *parent = nullptr);
  ~SurfWidget() override;

// ISurfWidget interface

public:

  double hessianThreshold() const override;
  int octaves() const override;
  int octaveLayers() const override;
  bool extendedDescriptor() const override;
  bool rotatedFeatures() const override;

public slots:

  void setHessianThreshold(double hessianThreshold) override;
  void setOctaves(int octaves) override;
  void setOctaveLayers(int octaveLayers) override;
  void setExtendedDescriptor(bool extendedDescriptor) override;
  void setRotatedFeatures(bool rotatedFeatures) override;

// FmeWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QDoubleSpinBox *mHessianThreshold;
  QSpinBox *mOctaves;
  QSpinBox *mOctaveLayers;
  QCheckBox *mExtendedDescriptor;
  QCheckBox *mRotatedFeatures;

};

} // namespace fme

#endif // SURFWIDGET_H
