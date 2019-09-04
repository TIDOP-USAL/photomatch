#ifndef FME_DESCRIPTOR_MATCHER_PRESENTER_H
#define FME_DESCRIPTOR_MATCHER_PRESENTER_H

#include "fme/fme_global.h"

#include <QObject>

#include "mvp.h"

class MultiProcess;

namespace fme
{

class IDescriptorMatcherView;
class IDescriptorMatcherModel;
class IProjectModel;
class ISettingsModel;
class IProgressDialog;

class IDescriptorMatcherPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IDescriptorMatcherPresenter() {}
  virtual ~IDescriptorMatcherPresenter(){}

signals:

  void matchesFinished();

public slots:

  virtual void setProgressDialog(IProgressDialog *progressDialog) = 0;

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

private:

  void init() override;

// IDescriptorMatcherPresenter interface

public slots:

  void setProgressDialog(IProgressDialog *progressDialog) override;

private slots:

  void run() override;
  void onError(int code, const QString &msg);
  void onFinished();

protected:

  IDescriptorMatcherView *mView;
  IDescriptorMatcherModel *mModel;
  IProjectModel *mProjectModel;
  ISettingsModel *mSettingsModel;
  MultiProcess *mMultiProcess;
  IProgressDialog *mProgressDialog;
};

} // namespace fme

#endif // FME_DESCRIPTOR_MATCHER_PRESENTER_H
