/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#ifndef PHOTOMATCH_DESCRIPTOR_MATCHER_WIDGET_H
#define PHOTOMATCH_DESCRIPTOR_MATCHER_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QSpinBox;
class QComboBox;
class QCheckBox;
class QDoubleSpinBox;
class QLabel;
class QGroupBox;

namespace photomatch
{

class PHOTOMATCH_EXPORT DescriptorMatcherWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  DescriptorMatcherWidget(QWidget *parent = nullptr)
    : PhotoMatchWidget(parent){}
  virtual ~DescriptorMatcherWidget() = default;

  /*!
   * \brief matchingMethod
   * \return
   */
  virtual QString matchingMethod() const = 0;

  virtual QString matchingStrategy() const = 0;

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
   * \brief One of HOMOGRAPHY_MATRIX, FUNDAMENTAL_MATRIX, ESSENTIAL_MATRIX
   * \return
   */
  virtual QString geometricTest() const = 0;

  /*!
   * \brief homographyComputeMethod
   * \return
   */
  virtual QString homographyComputeMethod() const = 0;

  /*!
   * \brief fundamentalComputeMethod
   * \return
   */
  virtual QString fundamentalComputeMethod() const = 0;

  /*!
   * \brief essentialComputeMethod
   * \return
   */
  virtual QString essentialComputeMethod() const = 0;

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
   * \brief maxIters
   */
  virtual int maxIters() const = 0;

  virtual bool usacIsParallel() const = 0;
  virtual int usacLocalOptimIterations() const = 0;
  virtual int usacLocalSampleSize() const = 0;
  virtual int usacMaxIters() const = 0;

  /*!
   * \brief crossMatching
   * \return
   */
  virtual bool crossMatching() const = 0;

  virtual bool gmsRotation() const = 0;
  virtual bool gmsScale() const = 0;
  virtual double gmsThreshold() const = 0;

signals:

  void matchingMethodChange(QString);
  void matchingStrategyChange(QString);
  void normTypeChange(QString);
  void ratioChange(double);
  void geometricTestChange(QString);
  void homographyComputeMethodChange(QString);
  void fundamentalComputeMethodChange(QString);
  void essentialComputeMethodChange(QString);
  void distanceChange(double);
  void confidenceChange(double);
  void crossMatchingChange(bool);
  void maxItersChange(int);
  void gmsRotationChange(bool);
  void gmsScaleChange(bool);
  void gmsThresholdChange(double);
  void usacIsParallelChanged(bool);
  void usacLocalOptimIterationsChanged(int);
  void usacLocalSampleSizeChanged(int);
  void usacMaxItersChanged(int);

public slots:

  /*!
   * \brief setMatchingMethod
   * \param matchingMethod
   */
  virtual void setMatchingMethod(const QString &matchingMethod) = 0;

  virtual void setMatchingStrategy(const QString &matchingStrategy) = 0;

  /*!
   * \brief setNormType
   * \param[in] normType
   */
  virtual void setNormType(const QString &normType) = 0;

  /*!
   * \brief setGeometricTest
   * \param geometricTest
   */
  virtual void setGeometricTest(const QString &geometricTest) = 0;

  /*!
   * \brief setRatio
   * \param[in] ratio
   */
  virtual void setRatio(double ratio) = 0;

  /*!
   * \brief setHomographyComputeMethod
   * \param computeMethod
   */
  virtual void setHomographyComputeMethod(const QString &computeMethod) = 0;

  /*!
   * \brief setHomographyComputeMethod
   * \param computeMethod
   */
  virtual void setFundamentalComputeMethod(const QString &computeMethod) = 0;

  /*!
   * \brief setHomographyComputeMethod
   * \param computeMethod
   */
  virtual void setEssentialComputeMethod(const QString &computeMethod) = 0;

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
   * \brief setMaxIters
   * \param maxIter
   */
  virtual void setMaxIters(int maxIter) = 0;

  virtual void setUsacIsParallel(bool usacIsParallel) = 0;
  virtual void setUsacLocalOptimIterations(int usacLocalOptimIterations) = 0;
  virtual void setUsacLocalSampleSize(int usacLocalSampleSize) = 0;
  virtual void setUsacMaxIters(int usacMaxIters) = 0;

  /*!
   * \brief setCrossMatching
   * \param[in] crossMatching
   */
  virtual void setCrossMatching(bool crossMatching) = 0;

  virtual void disableBruteForceNorm(const QString &norm) = 0;
  virtual void enableBruteForceNorm(const QString &norm) = 0;

  virtual void setGmsRotation(bool active) = 0;
  virtual void setGmsScale(bool active) = 0;
  virtual void setGmsThreshold(double threshold) = 0;
};




class PHOTOMATCH_EXPORT DescriptorMatcherWidgetImp
  : public DescriptorMatcherWidget
{

  Q_OBJECT

public:

  DescriptorMatcherWidgetImp(QWidget *parent = nullptr);
  ~DescriptorMatcherWidgetImp() override;

// DescriptorMatcherWidget interface

public:

  QString matchingMethod() const override;
  QString matchingStrategy() const override;
  QString normType() const override;
  double ratio() const override;
  QString geometricTest() const override;
  QString homographyComputeMethod() const override;
  QString fundamentalComputeMethod() const override;
  QString essentialComputeMethod() const override;
  double distance() const override;
  double confidence() const override;
  int maxIters() const override;
  bool usacIsParallel() const override;
  int usacLocalOptimIterations() const override;
  int usacLocalSampleSize() const override;
  int usacMaxIters() const override;
  bool crossMatching() const override;
  bool gmsRotation() const override;
  bool gmsScale() const override;
  double gmsThreshold() const override;

public slots:

  void setMatchingMethod(const QString &matchingMethod) override;
  void setMatchingStrategy(const QString &matchingStrategy) override;
  void setNormType(const QString &normType) override;
  void setRatio(double ratio) override;
  void setGeometricTest(const QString &geometricTest) override;
  void setHomographyComputeMethod(const QString &computeMethod) override;
  void setFundamentalComputeMethod(const QString &computeMethod) override;
  void setEssentialComputeMethod(const QString &computeMethod) override;
  void setDistance(double distance) override;
  void setConfidence(double confidence) override;
  void setMaxIters(int maxIter) override;
  void setUsacIsParallel(bool usacIsParallel) override;
  void setUsacLocalOptimIterations(int usacLocalOptimIterations) override;
  void setUsacLocalSampleSize(int usacLocalSampleSize) override;
  void setUsacMaxIters(int usacMaxIters) override;
  void setCrossMatching(bool crossMatching) override;
  void disableBruteForceNorm(const QString &norm) override;
  void enableBruteForceNorm(const QString &norm) override;
  void setGmsRotation(bool active) override;
  void setGmsScale(bool active) override;
  void setGmsThreshold(double threshold) override;

// PhotoMatchWidget interface

private:

  void initUI() override;
  void initSignalAndSlots() override;

public slots:

  void reset() override;

protected slots:

  void update() override;
  void retranslate() override;

protected:

  QLabel *mLabelMatchingMethod;
  QComboBox *mMatchingMethod;
  QLabel *mLabelMatchingStrategy;
  QComboBox *mMatchingStrategy;
  QGroupBox *mGroupBoxBFParameters;
  QComboBox *mNormType;
  QLabel *mNormTypeLabel;
  QGroupBox *mGroupBoxFilteringTest;
  QLabel *mLabelRatio;
  QDoubleSpinBox *mRatio;
  QLabel *mLabelGeometricTest;
  QComboBox *mGeometricTest;
  QDoubleSpinBox *mDistance;
  QLabel *mDistanceLabel;
  QDoubleSpinBox *mConfidence;
  QLabel *mConfidenceLabel;
  QSpinBox  *mMaxIters;
  QLabel *mMaxItersLabel;
  QCheckBox *mCheckBoxIsParallel;
  QLabel *mLabelLocalOptimIterations;
  QSpinBox *mSpinBoxLocalOptimIterations;
  /// cv::LocalOptimMethod loMethod;
  QLabel *mLabelLocalSampleSize;
  QSpinBox *mSpinBoxLocalSampleSize;
  QLabel *mLabelLocalMaxIterations;
  QSpinBox *mSpinBoxLocalMaxIterations;

  QCheckBox *mCrossMatching;
  QComboBox *mHComputeMethod;
  QLabel *mHComputeMethodLabel;
  QComboBox *mFComputeMethod;
  QLabel *mFComputeMethodLabel;
  QComboBox *mEComputeMethod;
  QLabel *mEComputeMethodLabel;
  QGroupBox *mGroupBoxGMS;
  QCheckBox *mRotationGMS;
  QCheckBox *mScaleGMS;
  QLabel *mLabelThresholdGMS;
  QDoubleSpinBox *mThresholdGMS;

};



} // namespace photomatch

#endif // PHOTOMATCH_DESCRIPTOR_MATCHER_WIDGET_H
