#ifndef PHOTOMATCH_FAST_WIDGET_H
#define PHOTOMATCH_FAST_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QSpinBox;
class QComboBox;
class QCheckBox;

namespace photomatch
{

/*!
 * \brief Interface for FAST Widgets class
 *
 */
class PHOTOMATCH_EXPORT IFastWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  IFastWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~IFastWidget() = default;

  /*!
   * \brief threshold (Default=10)
   * \return
   */
  virtual int threshold() const = 0;

  /*!
   * \brief Non Maximal Suppression for removing adjacent corners (default=true)
   * \return
   */
  virtual bool nonmaxSuppression() const = 0;

  /*!
   * \brief Detector Types
   * - TYPE_5_8: FAST-5 decision tree whith the 8 pixels mask
   * - TYPE_7_12: FAST-7 decision tree whith the 12 pixels mask
   * - TYPE_9_16: FAST-9 decision tree whith the 16 pixels mask (default)
   * \return Detector Type
   */
  virtual QString detectorType() const = 0;

signals:

  void thresholdChange(int);
  void nonmaxSuppressionChange(bool);
  void detectorTypeChange(QString);

public slots:

  /*!
   * \brief Set the threshold
   * \param threshold Threshold
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
   * - TYPE_5_8: FAST-5 decision tree whith the 8 pixels mask
   * - TYPE_7_12: FAST-7 decision tree whith the 12 pixels mask
   * - TYPE_9_16: FAST-9 decision tree whith the 16 pixels mask (default)
   *
   * \param[in] detectorType Detector Type
   */
  virtual void setDetectorType(QString detectorType) = 0;

};

class PHOTOMATCH_EXPORT FastWidget
  : public IFastWidget
{

  Q_OBJECT

public:

  FastWidget(QWidget *parent = nullptr);
  ~FastWidget() override;

// IFastWidget interface

public:

  int threshold() const override;
  bool nonmaxSuppression() const override;
  QString detectorType() const override;

public slots:

  void setThreshold(int threshold) override;
  void setNonmaxSuppression(bool nonmaxSuppression) override;
  void setDetectorType(QString detectorType) override;

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

#endif // PHOTOMATCH_FAST_WIDGET_H
