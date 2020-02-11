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


#ifndef PHOTOMATCH_FEATURE_EXTRACTOR_VIEW_H
#define PHOTOMATCH_FEATURE_EXTRACTOR_VIEW_H

#include "mvp.h"

class QGridLayout;
class QComboBox;
class QDialogButtonBox;
class QSpinBox;
class QCheckBox;

namespace photomatch
{

class IFeatureExtractorView
  : public IDialogView
{

  Q_OBJECT

public:

  IFeatureExtractorView(QWidget *parent = nullptr) : IDialogView(parent) {}
  virtual ~IFeatureExtractorView(){}

  virtual void setSessionName(const QString &name) = 0;
  virtual void addKeypointDetector(QWidget *keypointDetector) = 0;
  virtual void addDescriptorExtractor(QWidget *descriptorExtractor) = 0;
  virtual QString currentKeypointDetector() const = 0;
  virtual QString currentDescriptorExtractor() const = 0;
  virtual void addKeypointsFilter(QWidget *keypointsFilter) = 0;

signals:

  void keypointDetectorChange(QString);
  void descriptorExtractorChange(QString);
  void run();

public slots:

  virtual void setCurrentKeypointDetector(const QString &keypointDetector) = 0;
  virtual void setCurrentDescriptorExtractor(const QString &descriptorExtractor) = 0;
  virtual void disableDescriptorExtractor(const QString &descriptorExtractor) = 0;
  virtual void enableDescriptorExtractor(const QString &descriptorExtractor) = 0;

};


class FeatureExtractorView
  : public IFeatureExtractorView
{

  Q_OBJECT

public:

  FeatureExtractorView(QWidget *parent = nullptr);
  ~FeatureExtractorView() override;

protected slots:

// IFeatureExtractorView interface

public:

  void setSessionName(const QString &name) override;
  void addKeypointDetector(QWidget *keypointDetector) override;
  void addDescriptorExtractor(QWidget *descriptorExtractor) override;
  QString currentKeypointDetector() const override;
  QString currentDescriptorExtractor() const override;
  void addKeypointsFilter(QWidget *keypointsFilter) override;

public slots:

  void setCurrentKeypointDetector(const QString &keypointDetector) override;
  void setCurrentDescriptorExtractor(const QString &descriptorExtractor) override;
  void disableDescriptorExtractor(const QString &descriptorExtractor) override;
  void enableDescriptorExtractor(const QString &descriptorExtractor) override;

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

protected:

  QGridLayout *mGridLayoutKeypointDetector;
  QGridLayout *mGridLayoutDescriptorExtractor;
  QGridLayout *mGridLayoutKeypointsFilter;
  QComboBox *mComboBoxKeypointDetector;
  QComboBox *mComboBoxDescriptorExtractor;
  QDialogButtonBox *mButtonBox;
  QString mCurrentKeypointDetector;
  QString mCurrentDescriptorExtractor;
};

} // namespace photomatch

#endif // PHOTOMATCH_FEATURE_EXTRACTOR_VIEW_H
