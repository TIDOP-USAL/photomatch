#ifndef FME_DAISY_WIDGET_H
#define FME_DAISY_WIDGET_H

#include <QWidget>

class QSpinBox;
class QDoubleSpinBox;
class QComboBox;
class QCheckBox;

namespace fme
{

class IDaisyWidget
  : public QWidget
{
  Q_OBJECT

public:

  IDaisyWidget(QWidget *parent = nullptr) : QWidget(parent){}
  virtual ~IDaisyWidget() = default;

  /*!
   * \brief radius of the descriptor at the initial scale
   * \return
   */
  virtual double radius() const = 0;

  /*!
   * \brief amount of radial range division quantity
   * \return
   */
  virtual int qRadius() const = 0;

  /*!
   * \brief amount of angular range division quantity
   * \return
   */
  virtual int qTheta() const = 0;

  /*!
   * \brief amount of gradient orientations range division quantity
   * \return
   */
  virtual int qHist() const = 0;

  /*!
   * \brief Descriptor normalization type
   * Normalization types:
   * - NRM_NONE: not make any normalization
   * - NRM_PARTIAL: mean that histograms are normalized independently for L2 norm equal to 1.0
   * - NRM_FULL: mean that descriptors are normalized for L2 norm equal to 1.0
   * - NRM_SIFT: mean that descriptors are normalized for L2 norm equal to 1.0 but no individual one is bigger than 0.154 as in SIFT
   * \return
   */
  virtual QString norm() const = 0;

  //virtual homography() const = 0;

  /*!
   * \brief Interpolation disabled or enabled
   * \return
   */
  virtual bool interpolation() const = 0;

  /*!
   * \brief Using keypoints orientation
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

  virtual void setRadius(double radius) = 0;
  virtual void setQRadius(int qRadius) = 0;
  virtual void setQTheta(int qTheta) = 0;
  virtual void setQHist(int qHist) = 0;
  virtual void setNorm(const QString &norm) = 0;
  virtual void setInterpolation(bool interpolation) = 0;
  virtual void setUseOrientation(bool useOrientatione) = 0;

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;

};

class DaisyWidget
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

} // namespace fme

#endif // FME_DAISY_WIDGET_H
