#ifndef PHOTOMATCH_FEATURE_EXTRACTOR_PRESENTER_H
#define PHOTOMATCH_FEATURE_EXTRACTOR_PRESENTER_H

#include "photomatch/photomatch_global.h"

#include <QObject>

#include "mvp.h"

class MultiProcess;

namespace photomatch
{

class IFeatureExtractorView;
class IFeatureExtractorModel;
class IProjectModel;
class ISettingsModel;

class IAgastWidget;
class IAkazeWidget;
class IBriefWidget;
class IBriskWidget;
class IDaisyWidget;
class IFastWidget;
class IFreakWidget;
class IGfttWidget;
class IHogWidget;
class IKazeWidget;
class ILatchWidget;
class ILucidWidget;
class ILssWidget;
class IMsdWidget;
class IMserWidget;
class IOrbWidget;
class ISiftWidget;
class IStarWidget;
class ISurfWidget;
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
  void featuresExtracted(QString);
  void finished();

public slots:

  virtual void setProgressHandler(ProgressHandler *progressHandler) = 0;
  virtual void cancel() = 0;

private slots:

  virtual void run() = 0;
  virtual void setCurrentkeypointDetector(const QString &featureExtractor) = 0;
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

private:

  void init() override;

// IFeatureExtractorPresenter interface

public slots:

  void setProgressHandler(ProgressHandler *progressHandler) override;
  void cancel() override;

private slots:

  void run() override;
  void setCurrentkeypointDetector(const QString &featureExtractor) override;
  void setCurrentDescriptorExtractor(const QString &descriptorExtractor) override;

  void onError(int code, const QString &msg);
  void onFinished();
  void onFeaturesExtracted(const QString &features);

protected:

  IFeatureExtractorView *mView;
  IFeatureExtractorModel *mModel;
  IProjectModel *mProjectModel;
  ISettingsModel *mSettingsModel;

  IAgastWidget *mAgastDetector;
  IAkazeWidget *mAkazeDetector;
  IBriskWidget *mBriskDetector;
  IFastWidget *mFastDetector;
  IGfttWidget *mGfttDetector;
  IKazeWidget *mKazeDetector;
  IMsdWidget *mMsdDetector;
  IMserWidget *mMserDetector;
  IOrbWidget *mOrbDetector;
  ISiftWidget *mSiftDetector;
  IStarWidget *mStarDetector;
  ISurfWidget *mSurfDetector;

  IAkazeWidget *mAkazeDescriptor;
  IBriefWidget *mBriefDescriptor;
  IBriskWidget *mBriskDescriptor;
  IDaisyWidget *mDaisyDescriptor;
  IFreakWidget *mFreakDescriptor;
  IHogWidget *mHogDescriptor;
  IKazeWidget *mKazeDescriptor;
  ILatchWidget *mLatchDescriptor;
  ILucidWidget *mLucidDescriptor;
  ILssWidget *mLssDescriptor;
  IOrbWidget *mOrbDescriptor;
  ISiftWidget *mSiftDescriptor;
  ISurfWidget *mSurfDescriptor;
  MultiProcess *mMultiProcess;

  ProgressHandler *mProgressHandler;
};

} // namespace photomatch

#endif // PHOTOMATCH_FEATURE_EXTRACTOR_PRESENTER_H
