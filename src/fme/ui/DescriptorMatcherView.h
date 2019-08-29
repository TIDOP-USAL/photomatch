#ifndef FME_DESCRIPTOR_MATCHER_VIEW_H
#define FME_DESCRIPTOR_MATCHER_VIEW_H

#include "mvp.h"

class QDialogButtonBox;

namespace fme
{

class IDescriptorMatcherWidget;

class IDescriptorMatcherView
  : public IDialogView
{

  Q_OBJECT

public:

  IDescriptorMatcherView(QWidget *parent = nullptr) : IDialogView(parent) {}
  virtual ~IDescriptorMatcherView(){}

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

  void MatchMethodChange(QString);
  void run();

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

};

class DescriptorMatcherView
  : public IDescriptorMatcherView
{

  Q_OBJECT

public:

  DescriptorMatcherView(QWidget *parent = nullptr);
  ~DescriptorMatcherView() override;

// IDescriptorMatcherView interface

public:

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

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;

protected:

  QDialogButtonBox *mButtonBox;
  IDescriptorMatcherWidget *mDescriptorMatcherWidget;

};

} // namespace fme

#endif // FME_DESCRIPTOR_MATCHER_VIEW_H
