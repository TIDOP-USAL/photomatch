#ifndef PHOTOMATCH_SIFT_WIDGET_H
#define PHOTOMATCH_SIFT_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QSpinBox;
class QDoubleSpinBox;

namespace photomatch
{

/*!
 * \brief Interface SIFT Widget
 */
class PHOTOMATCH_EXPORT ISiftWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  ISiftWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~ISiftWidget() = default;

  /*!
   * \brief featuresNumber
   * \return
   */
  virtual int featuresNumber() const = 0;

  /*!
   * \brief octaveLayers
   * \return
   */
  virtual int octaveLayers() const = 0;

  /*!
   * \brief contrastThreshold
   * \return
   */
  virtual double contrastThreshold() = 0;

  /*!
   * \brief edgeThreshold
   * \return
   */
  virtual double edgeThreshold() = 0;

  /*!
   * \brief sigma
   * \return
   */
  virtual double sigma() = 0;

signals:

  void featuresNumberChange(int);
  void octaveLayersChange(int);
  void contrastThresholdChange(double);
  void edgeThresholdChange(double);
  void sigmaChange(double);

public slots:

  /*!
   * \brief setFeaturesNumber
   * \param featuresNumber
   */
  virtual void setFeaturesNumber(int featuresNumber) = 0;

  /*!
   * \brief setOctaveLayers
   * \param octaveLayers
   */
  virtual void setOctaveLayers(int octaveLayers) = 0;

  /*!
   * \brief setContrastThreshold
   * \param contrastThreshold
   */
  virtual void setContrastThreshold(double contrastThreshold) = 0;

  /*!
   * \brief setEdgeThreshold
   * \param edgeThreshold
   */
  virtual void setEdgeThreshold(double edgeThreshold) = 0;

  /*!
   * \brief setSigma
   * \param sigma
   */
  virtual void setSigma(double sigma) = 0;

};


class PHOTOMATCH_EXPORT SiftWidget
  : public ISiftWidget
{
  Q_OBJECT

public:

  SiftWidget(QWidget *parent = nullptr);
  ~SiftWidget() override;

// ISiftWidget interface

public:

  int featuresNumber() const override;
  int octaveLayers() const override;
  double contrastThreshold() override;
  double edgeThreshold() override;
  double sigma() override;

public slots:

  void setFeaturesNumber(int featuresNumber) override;
  void setOctaveLayers(int octaveLayers) override;
  void setContrastThreshold(double contrastThreshold) override;
  void setEdgeThreshold(double edgeThreshold) override;
  void setSigma(double sigma) override;

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mFeaturesNumber;
  QSpinBox *mOctaveLayers;
  QDoubleSpinBox *mContrastThreshold;
  QDoubleSpinBox *mEdgeThreshold;
  QDoubleSpinBox *mSigma;

};

} // namespace photomatch

#endif // PHOTOMATCH_SIFT_WIDGET_H
