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

#include "photomatch/ui/featextract/FeatureExtractor.h"

namespace photomatch
{

class FeatureExtractorView;
class ProjectModel;
class SettingsModel;
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
class LssWidget;
class MsdWidget;
class MserWidget;
class OrbWidget;
class SiftWidget;
class StarWidget;
class SurfWidget;
class VggWidget;
class KeypointsFilterWidget;
class KeypointDetector;
class DescriptorExtractor;


class FeatureExtractorPresenterImp
  : public FeatureExtractorPresenter
{
  Q_OBJECT

public:

  FeatureExtractorPresenterImp(FeatureExtractorView *view,
                               ProjectModel *projectModel,
                               SettingsModel *settingsModel);
  ~FeatureExtractorPresenterImp() override;

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

  std::shared_ptr<KeypointDetector> makeKeypointDetector(const QString &keypointDetector);
  std::shared_ptr<DescriptorExtractor> makeDescriptorExtractor(const QString &descriptorExtractor, 
                                                               const QString &keypointDetector);

// FeatureExtractorPresenter interface

private slots:

  void setCurrentkeypointDetector(const QString &keypointDetector) override;
  void setCurrentDescriptorExtractor(const QString &descriptorExtractor) override;

  void onImagePreprocessed(const QString &image);
  void onFeaturesExtracted(const QString &features);

// ProcessPresenter interface

protected slots:

  void onError(int code, const QString &msg) override;
  void onFinished() override;
  void createProcess() override;

public slots:

  void cancel() override;

// PhotoMatchPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(HelpDialog *help) override;

private:

  void init() override;
  void initSignalAndSlots() override;

protected:

  FeatureExtractorView *mView;
  ProjectModel *mProjectModel;
  SettingsModel *mSettingsModel;
  HelpDialog *mHelp;

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

};

} // namespace photomatch

#endif // PHOTOMATCH_FEATURE_EXTRACTOR_PRESENTER_H
