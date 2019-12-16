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

class IAgastWidget;
class IAkazeWidget;
class IBoostWidget;
class IBriefWidget;
class IBriskWidget;
class IDaisyWidget;
class IFastWidget;
class IFreakWidget;
class IGfttWidget;
class IHogWidget;
class IKazeWidget;
class ILatchWidget;
//class ILucidWidget;
class ILssWidget;
class IMsdWidget;
class IMserWidget;
class IOrbWidget;
class ISiftWidget;
class IStarWidget;
class ISurfWidget;
class IVggWidget;
class IKeypointsFilterWidget;

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

  IAgastWidget *mAgastDetector;
  IAkazeWidget *mAkazeDetector;
  IBriskWidget *mBriskDetector;
  IFastWidget *mFastDetector;
  IGfttWidget *mGfttDetector;
  IKazeWidget *mKazeDetector;
  IMsdWidget *mMsdDetector;
  IMserWidget *mMserDetector;
  IOrbWidget *mOrbDetector;
#ifdef OPENCV_ENABLE_NONFREE
  ISiftWidget *mSiftDetector;
#endif
  IStarWidget *mStarDetector;
#ifdef OPENCV_ENABLE_NONFREE
  ISurfWidget *mSurfDetector;
#endif

  IAkazeWidget *mAkazeDescriptor;
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  IBoostWidget *mBoostDescriptor;
#endif
  IBriefWidget *mBriefDescriptor;
  IBriskWidget *mBriskDescriptor;
  IDaisyWidget *mDaisyDescriptor;
  IFreakWidget *mFreakDescriptor;
  IHogWidget *mHogDescriptor;
  IKazeWidget *mKazeDescriptor;
  ILatchWidget *mLatchDescriptor;
  //ILucidWidget *mLucidDescriptor;
  ILssWidget *mLssDescriptor;
  IOrbWidget *mOrbDescriptor;
#ifdef OPENCV_ENABLE_NONFREE
  ISiftWidget *mSiftDescriptor;
  ISurfWidget *mSurfDescriptor;
#endif
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR > 2)
  IVggWidget *mVggDescriptor;
#endif
  IKeypointsFilterWidget *mKeypointsFilterWidget;
  MultiProcess *mMultiProcess;
  ProgressHandler *mProgressHandler;
};

} // namespace photomatch

#endif // PHOTOMATCH_FEATURE_EXTRACTOR_PRESENTER_H
