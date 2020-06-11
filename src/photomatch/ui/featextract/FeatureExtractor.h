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

#ifndef PHOTOMATCH_FEATURE_EXTRACTOR_INTERFACES_H
#define PHOTOMATCH_FEATURE_EXTRACTOR_INTERFACES_H

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class ProgressHandler;


class FeatureExtractorModel
{

public:

  FeatureExtractorModel(){}

};



class FeatureExtractorView
  : public PhotoMatchDialogView
{

  Q_OBJECT

public:

  FeatureExtractorView(QWidget *parent = nullptr) : PhotoMatchDialogView(parent) {}
  virtual ~FeatureExtractorView(){}

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


class FeatureExtractorPresenter
  : public PhotoMatchPresenter
{

  Q_OBJECT

public:

  FeatureExtractorPresenter() {}
  virtual ~FeatureExtractorPresenter(){}

signals:

  void running();
  void imagePreprocessed(QString);
  void featuresExtracted(QString);
  void finished();

public slots:

  virtual void setProgressHandler(ProgressHandler *progressHandler) = 0;
  virtual void cancel() = 0;

private slots:

  virtual void run() = 0;
  virtual void setCurrentkeypointDetector(const QString &keypointDetector) = 0;
  virtual void setCurrentDescriptorExtractor(const QString &descriptorExtractor) = 0;

};


} // namespace photomatch


#endif // PHOTOMATCH_FEATURE_EXTRACTOR_INTERFACES_H
