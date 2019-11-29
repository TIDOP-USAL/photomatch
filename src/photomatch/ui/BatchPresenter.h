#ifndef PHOTOMATCH_BATCH_PRESENTER_H
#define PHOTOMATCH_BATCH_PRESENTER_H

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IBatchView;
class IBatchModel;
class IProjectModel;
class ISettingsModel;
class Help;

class IBatchPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IBatchPresenter(){}
  virtual ~IBatchPresenter() override = default;

public slots:

  //virtual void save() = 0;
  virtual void sessionChange(const QString &session) = 0;

};


class BatchPresenter
  : public IBatchPresenter
{

  Q_OBJECT

public:

  BatchPresenter(IBatchView *view,
                 IBatchModel *model,
                 IProjectModel *projectModel,
                 ISettingsModel *settingsModel);
  ~BatchPresenter() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;

private:

  void init() override;

// IBatchPresenter interface

public slots:

  void sessionChange(const QString &session) override;

protected:

  IBatchView *mView;
  IBatchModel *mModel;
  IProjectModel *mProjectModel;
  ISettingsModel *mSettingsModel;
};



} // namespace photomatch

#endif // PHOTOMATCH_BATCH_PRESENTER_H
