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

#ifndef PHOTOMATCH_DESCRIPTOR_MATCHER_INTERFACES_H
#define PHOTOMATCH_DESCRIPTOR_MATCHER_INTERFACES_H

#include "photomatch/ui/mvp.h"


namespace photomatch
{

class ProgressHandler;


class DescriptorMatcherModel
{

public:

  DescriptorMatcherModel() {}
};



class DescriptorMatcherView
  : public IDialogView
{

  Q_OBJECT

public:

  DescriptorMatcherView(QWidget *parent = nullptr) : IDialogView(parent) {}
  virtual ~DescriptorMatcherView(){}

  virtual void setSessionName(const QString &name) = 0;

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

  /*!
   * \brief crossMatching
   * \return
   */
  virtual bool crossMatching() const = 0;

  virtual bool gmsRotation() const = 0;
  virtual bool gmsScale() const = 0;
  virtual double gmsThreshold() const = 0;

signals:

  void matchMethodChange(QString);
  void run();

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


class DescriptorMatcherPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  DescriptorMatcherPresenter() {}
  virtual ~DescriptorMatcherPresenter(){}

signals:

  void running();
  void matchCompute(QString);
  void finished();

public slots:

  virtual void setProgressHandler(ProgressHandler *progressHandler) = 0;
  virtual void cancel() = 0;

private slots:

  virtual void run() = 0;

};


} // namespace photomatch


#endif // PHOTOMATCH_DESCRIPTOR_MATCHER_INTERFACES_H
