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


#ifndef PHOTOMATCH_FEATURE_EXTRACTOR_PRESENTER_H
#define PHOTOMATCH_FEATURE_EXTRACTOR_PRESENTER_H

#include "photomatch/photomatch_global.h"

#include <QObject>

#include <opencv2/core.hpp>

#include "mvp.h"

class MultiProcess;

namespace photomatch
{

class IFeatureExtractorView;
class IFeatureExtractorModel;
class IProjectModel;
class ISettingsModel;
class HelpDialog;

class AgastWidget;
class AkazeWidget;
class BoostWidget;
class BriefWidget;
class BriskWidget;
class DaisyWidget;
class FastWidget;
class FreakWidget;
class GfttWidget;
class HogWidget;
class KazeWidget;
class LatchWidget;
//class ILucidWidget;
class LssWidget;
class MsdWidget;
class MserWidget;
class OrbWidget;
class SiftWidget;
class StarWidget;
class SurfWidget;
class VggWidget;
class KeypointsFilterWidget;

class ProgressHandler;

class IFeatureExtractorPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IFeatureExtractorPresenter() {}
  virtual ~IFeatureExtractorPresenter(){}

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


class FeatureExtractorPresenter
  : public IFeatureExtractorPresenter
{
  Q_OBJECT

public:

  FeatureExtractorPresenter(IFeatureExtractorView *view,
                            IFeatureExtractorModel *model,
                            IProjectModel *projectModel,
                            ISettingsModel *settingsModel);
  ~FeatureExtractorPresenter() override;

private:

  void setDetectorAndDescriptorProperties();
  void setAgastDetectorProperties();
  void setAkazeDetectorPropierties();
  void setAkazeDescriptorProperties();
  void setBoostDescriptorProperties();
  void setBriefDescriptorProperties();
  void setBriskDetectorProperties();
  void setBriskDescriptorProperties();
  void setDaisyDescriptorProperties();
  void setFastDetectorProperties();
  void setFreakDescriptorProperties();
  void setGfttDetectorProperties();
  void setHogDescriptorProperties();
  void setKazeDetectorProperties();
  void setKazeDescriptorProperties();
  void setLatchDescriptorProperties();
  void setMsdDetectorProperties();
  void setMserDetectorProperties();
  void setOrbDetectorProperties();
  void setOrbDescriptorProperties();
  void setSiftDetectorProperties();
  void setSiftDescriptorProperties();
  void setStarDetectorProperties();
  void setSurfDetectorProperties();
  void setSurfDescriptorProperties();
  void setVggDescriptorProperties();

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(std::shared_ptr<HelpDialog> &help) override;

private:

  void init() override;

// IFeatureExtractorPresenter interface

public slots:

  void setProgressHandler(ProgressHandler *progressHandler) override;
  void cancel() override;

private slots:

  void run() override;
  void setCurrentkeypointDetector(const QString &keypointDetector) override;
  void setCurrentDescriptorExtractor(const QString &descriptorExtractor) override;

  void onError(int code, const QString &msg);
  void onFinished();
  void onImagePreprocessed(const QString &image);
  void onFeaturesExtracted(const QString &features);

protected:

  IFeatureExtractorView *mView;
  IFeatureExtractorModel *mModel;  /// Por ahora es una clase vacia.
  IProjectModel *mProjectModel;
  ISettingsModel *mSettingsModel;
  std::shared_ptr<HelpDialog> mHelp;

  AgastWidget *mAgastDetector;
  AkazeWidget *mAkazeDetector;
  BriskWidget *mBriskDetector;
  FastWidget *mFastDetector;
  GfttWidget *mGfttDetector;
  KazeWidget *mKazeDetector;
  MsdWidget *mMsdDetector;
  MserWidget *mMserDetector;
  OrbWidget *mOrbDetector;
#ifdef OPENCV_ENABLE_NONFREE
  SiftWidget *mSiftDetector;
#endif
  StarWidget *mStarDetector;
#ifdef OPENCV_ENABLE_NONFREE
  SurfWidget *mSurfDetector;
#endif

  AkazeWidget *mAkazeDescriptor;
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  BoostWidget *mBoostDescriptor;
#endif
  BriefWidget *mBriefDescriptor;
  BriskWidget *mBriskDescriptor;
  DaisyWidget *mDaisyDescriptor;
  FreakWidget *mFreakDescriptor;
  HogWidget *mHogDescriptor;
  KazeWidget *mKazeDescriptor;
  LatchWidget *mLatchDescriptor;
  //ILucidWidget *mLucidDescriptor;
  LssWidget *mLssDescriptor;
  OrbWidget *mOrbDescriptor;
#ifdef OPENCV_ENABLE_NONFREE
  SiftWidget *mSiftDescriptor;
  SurfWidget *mSurfDescriptor;
#endif
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  VggWidget *mVggDescriptor;
#endif
  KeypointsFilterWidget *mKeypointsFilterWidget;
  MultiProcess *mMultiProcess;
  ProgressHandler *mProgressHandler;
};

} // namespace photomatch

#endif // PHOTOMATCH_FEATURE_EXTRACTOR_PRESENTER_H
