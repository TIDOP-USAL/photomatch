#ifndef PHOTOMATCH_DAISY_WIDGET_H
#define PHOTOMATCH_DAISY_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QSpinBox;
class QDoubleSpinBox;
class QComboBox;
class QCheckBox;

namespace photomatch
{

/*!
 * \brief Interface for DAISY Widgets class
 * E. Tola, V. Lepetit, and P. Fua.
 * DAISY: An Efficient Dense Descriptor Applied to Wide Baseline
 * Stereo. IEEE Transactions on Pattern Analysis and Machine
 * Intelligence, 32(5):815–830, May 2010.
 */
class PHOTOMATCH_EXPORT IDaisyWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  IDaisyWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~IDaisyWidget() = default;

  /*!
   * \brief Radius of the descriptor at the initial scale (Default=15.)
   * \return
   */
  virtual double radius() const = 0;

  /*!
   * \brief Amount of radial range division quantity (Default=3)
   * \return
   */
  virtual int qRadius() const = 0;

  /*!
   * \brief Amount of angular range division quantity (Default=8)
   * \return
   */
  virtual int qTheta() const = 0;

  /*!
   * \brief Amount of gradient orientations range division quantity (Default=8)
   * \return
   */
  virtual int qHist() const = 0;

  /*!
   * \brief Descriptor normalization type
   * Normalization types:
   * - NRM_NONE: not make any normalization (Default)
   * - NRM_PARTIAL: mean that histograms are normalized independently for L2 norm equal to 1.0
   * - NRM_FULL: mean that descriptors are normalized for L2 norm equal to 1.0
   * - NRM_SIFT: mean that descriptors are normalized for L2 norm equal to 1.0 but no individual one is bigger than 0.154 as in SIFT
   * \return
   */
  virtual QString norm() const = 0;

  //virtual homography() const = 0;

  /*!
   * \brief Interpolation disabled or enabled (Default)
   * \return
   */
  virtual bool interpolation() const = 0;

  /*!
   * \brief Using orientation (Default=false)
   * \return
   */
  virtual bool useOrientation() const = 0;

signals:

  void radiusChange(double);
  void qRadiusChange(int);
  void qThetaChange(int);
  void qHistChange(int);
  void normChange(QString);
  void interpolationChange(bool);
  void useOrientationChange(bool);

public slots:

  /*!
   * \brief Set the radius of the descriptor at the initial scale
   * \param[in] radius Radius of the descriptor
   */
  virtual void setRadius(double radius) = 0;

  /*!
   * \brief Set radial range division
   * \param[in] qRadius Radial range division
   */
  virtual void setQRadius(int qRadius) = 0;

  /*!
   * \brief Set angular range division
   * \param[in] qTheta Angular range division
   */
  virtual void setQTheta(int qTheta) = 0;

  /*!
   * \brief Set gradient orientations range division
   * \param[in] qHist gradient orientations range division
   */
  virtual void setQHist(int qHist) = 0;

  /*!
   * \brief Set normalization type
   * Normalization types:
   * - NRM_NONE: not make any normalization (Default)
   * - NRM_PARTIAL: mean that histograms are normalized independently for L2 norm equal to 1.0
   * - NRM_FULL: mean that descriptors are normalized for L2 norm equal to 1.0
   * - NRM_SIFT: mean that descriptors are normalized for L2 norm equal to 1.0 but no individual one is bigger than 0.154 as in SIFT
   * \param[in] norm Normalization type
   */
  virtual void setNorm(const QString &norm) = 0;

  /*!
   * \brief Enable or disable interpolation
   * \param[in] interpolation true for enable interpolation or false for disable
   */
  virtual void setInterpolation(bool interpolation) = 0;

  /*!
   * \brief Enable or disable orientation use
   * \param[in] useOrientation true for enable orientation or false for disable
   */
  virtual void setUseOrientation(bool useOrientation) = 0;

};

class PHOTOMATCH_EXPORT DaisyWidget
  : public IDaisyWidget
{
  Q_OBJECT

public:

  DaisyWidget(QWidget *parent = nullptr);
  ~DaisyWidget() override;

// IDaisyWidget interface

public:

  double radius() const override;
  int qRadius() const override;
  int qTheta() const override;
  int qHist() const override;
  QString norm() const override;
  bool interpolation() const override;
  bool useOrientation() const override;

public slots:

  void setRadius(double radius) override;
  void setQRadius(int qRadius) override;
  void setQTheta(int qTheta) override;
  void setQHist(int qHist) override;
  void setNorm(const QString &norm) override;
  void setInterpolation(bool interpolation) override;
  void setUseOrientation(bool useOrientation) override;

// PhotoMatchWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QDoubleSpinBox *mRadius;
  QSpinBox *mQRadius;
  QSpinBox *mQTheta;
  QSpinBox *mQHist;
  QComboBox *mNorm;
  QCheckBox *mInterpolation;
  QCheckBox *mUseOrientation;

};

} // namespace photomatch

#endif // PHOTOMATCH_DAISY_WIDGET_H
