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
class PHOTOMATCH_EXPORT IAgastWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  IAgastWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~IAgastWidget() = default;

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

class PHOTOMATCH_EXPORT AgastWidget
  : public IAgastWidget
{
  Q_OBJECT

public:

  AgastWidget(QWidget *parent = nullptr);
  ~AgastWidget() override;

// IFastWidget interface

  int threshold() const override;
  bool nonmaxSuppression() const override;
  QString detectorType() const override;

public slots:

  void setThreshold(int threshold) override;
  void setNonmaxSuppression(bool nonmaxSuppression) override;
  void setDetectorType(const QString &detectorType) override;

// PhotoMatchWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mThreshold;
  QCheckBox *mNonmaxSuppression;
  QComboBox *mDetectorType;

};

} // namespace photomatch

#endif // PHOTOMATCH_AGAST_WIDGET_H
