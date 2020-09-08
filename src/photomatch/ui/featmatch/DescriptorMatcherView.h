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


#ifndef PHOTOMATCH_DESCRIPTOR_MATCHER_VIEW_H
#define PHOTOMATCH_DESCRIPTOR_MATCHER_VIEW_H

#include "photomatch/ui/featmatch/DescriptorMatcher.h"

class QDialogButtonBox;

namespace photomatch
{

class DescriptorMatcherWidget;


class DescriptorMatcherViewImp
  : public DescriptorMatcherView
{

  Q_OBJECT

public:

  DescriptorMatcherViewImp(QWidget *parent = nullptr);
  ~DescriptorMatcherViewImp() override;

// DescriptorMatcherView interface

public:

  void setSessionName(const QString &name) override;
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
  void setCrossMatching(bool crossMatching) override;
  void disableBruteForceNorm(const QString &norm) override;
  void enableBruteForceNorm(const QString &norm) override;
  void setGmsRotation(bool active) override;
  void setGmsScale(bool active) override;
  void setGmsThreshold(double threshold) override;

// PhotoMatchDialogView interface

private:

  void initUI() override;
  void initSignalAndSlots() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

protected:

  QDialogButtonBox *mButtonBox;
  DescriptorMatcherWidget *mDescriptorMatcherWidget;

};

} // namespace photomatch

#endif // PHOTOMATCH_DESCRIPTOR_MATCHER_VIEW_H
