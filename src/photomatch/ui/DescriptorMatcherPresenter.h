#ifndef PHOTOMATCH_DESCRIPTOR_MATCHER_PRESENTER_H
#define PHOTOMATCH_DESCRIPTOR_MATCHER_PRESENTER_H

#include "photomatch/photomatch_global.h"

#include <QObject>

#include "mvp.h"

class MultiProcess;

namespace photomatch
{

class IDescriptorMatcherView;
class IDescriptorMatcherModel;
class IProjectModel;
class ISettingsModel;
class HelpDialog;
class ProgressHandler;

class IDescriptorMatcherPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IDescriptorMatcherPresenter() {}
  virtual ~IDescriptorMatcherPresenter(){}

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

class DescriptorMatcherPresenter
  : public IDescriptorMatcherPresenter
{

  Q_OBJECT

public:

  DescriptorMatcherPresenter(IDescriptorMatcherView *view,
                             IDescriptorMatcherModel *model,
                             IProjectModel *projectModel,
                             ISettingsModel *settingsModel);
  ~DescriptorMatcherPresenter() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(std::shared_ptr<HelpDialog> &help) override;

private:

  void init() override;

// IDescriptorMatcherPresenter interface

public slots:

  void setProgressHandler(ProgressHandler *progressHandler) override;
  void cancel() override;

private slots:

  void run() override;
  void onError(int code, const QString &msg);
  void onFinished();
  void onMatchCompute(const QString &left, const QString &right, const QString &match);
  void onPassPointsFinished(const QString &file);
protected:

  IDescriptorMatcherView *mView;
  IDescriptorMatcherModel *mModel;
  IProjectModel *mProjectModel;
  ISettingsModel *mSettingsModel;
  std::shared_ptr<HelpDialog> mHelp;
  MultiProcess *mMultiProcess;
  ProgressHandler *mProgressHandler;
};

} // namespace photomatch

#endif // PHOTOMATCH_DESCRIPTOR_MATCHER_PRESENTER_H
