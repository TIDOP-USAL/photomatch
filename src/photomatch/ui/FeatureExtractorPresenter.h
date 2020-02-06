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
