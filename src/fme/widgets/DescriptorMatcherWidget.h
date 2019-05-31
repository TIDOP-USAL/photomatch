#ifndef FME_DESCRIPTOR_MATCHER_WIDGET_H
#define FME_DESCRIPTOR_MATCHER_WIDGET_H

#include <QWidget>

class QSpinBox;
class QComboBox;
class QCheckBox;
class QDoubleSpinBox;
class QLabel;

namespace fme
{

class IDescriptorMatcherWidget
  : public QWidget
{
  Q_OBJECT

public:

  IDescriptorMatcherWidget(QWidget *parent = nullptr) : QWidget(parent){}
  virtual ~IDescriptorMatcherWidget() = default;

  /*!
   * \brief matchingMethod
   * \return
   */
  virtual QString matchingMethod() const = 0;

  /*!
   * \brief One of NORM_L1, NORM_L2, NORM_HAMMING, NORM_HAMMING2.
   * \return
   */
  virtual QString normType() const = 0;

  /*!
   * \brief ratio
   * \return
   */
  virtual double ratio() const = 0;

  /*!
   * \brief distance
   * \return
   */
  virtual double distance() const = 0;

  /*!
   * \brief confidence
   * \return
   */
  virtual double confidence() const = 0;

  /*!
   * \brief crossMatching
   * \return
   */
 virtual bool crossMatching() const = 0;

signals:

  void matchingMethodChange(QString);
  void normTypeChange(QString);
  void ratioChange(double);
  void distanceChange(double);
  void confidenceChange(double);
  void crossMatchingChange(bool);

public slots:

  /*!
   * \brief setMatchingMethod
   * \param matchingMethod
   */
  virtual void setMatchingMethod(const QString &matchingMethod) = 0;

  /*!
   * \brief setNormType
   * \param[in] normType
   */
  virtual void setNormType(const QString &normType) = 0;

  /*!
   * \brief setRatio
   * \param[in] ratio
   */
  virtual void setRatio(double ratio) = 0;

  /*!
   * \brief setDistance
   * \param[in] distance
   */
  virtual void setDistance(double distance) = 0;

  /*!
   * \brief setConfidence
   * \param[in] confidence
   */
  virtual void setConfidence(double confidence) = 0;

  /*!
   * \brief setCrossMatching
   * \param[in] crossMatching
   */
  virtual void setCrossMatching(bool crossMatching) = 0;

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;

};

class DescriptorMatcherWidget
  : public IDescriptorMatcherWidget
{

  Q_OBJECT

public:

  DescriptorMatcherWidget(QWidget *parent = nullptr);
  ~DescriptorMatcherWidget() override;

private slots:

  void onMatchingMethodChanged(const QString &method);

// IDescriptorMatcherWidget interface

  QString matchingMethod() const override;
  QString normType() const override;
  double ratio() const override;
  double distance() const override;
  double confidence() const override;
  bool crossMatching() const override;

public slots:

  void setMatchingMethod(const QString &matchingMethod) override;
  void setNormType(const QString &normType) override;
  void setRatio(double ratio) override;
  void setDistance(double distance) override;
  void setConfidence(double confidence) override;
  void setCrossMatching(bool crossMatching) override;

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QComboBox *mMatchingMethod;
  QComboBox *mNormType;
  QDoubleSpinBox *mRatio;
  QDoubleSpinBox *mDistance;
  QDoubleSpinBox *mConfidence;
  QCheckBox *mCrossMatching;

private:

  QLabel *mNormTypeLabel;
};

} // namespace fme

#endif // FME_DESCRIPTOR_MATCHER_WIDGET_H
