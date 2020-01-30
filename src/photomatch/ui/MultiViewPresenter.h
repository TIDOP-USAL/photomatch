#ifndef PHOTOMATCH_MULTIVIEW_PRESENTER_H
#define PHOTOMATCH_MULTIVIEW_PRESENTER_H

#include <memory>

#include <QObject>

#include "photomatch/ui/mvp.h"


namespace photomatch
{

class IMultiViewView;
class IMultiViewModel;
class HelpDialog;

class IMultiViewPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IMultiViewPresenter(){}
  virtual ~IMultiViewPresenter() {}

public slots:

  virtual void setSession(const QString &session) = 0;

protected slots:


};


class MultiViewPresenter
  : public IMultiViewPresenter
{
  Q_OBJECT

public:

  MultiViewPresenter(IMultiViewView *view,
                     IMultiViewModel *model);

private slots:

  void onIdChange(int id);

// IPresenter interface

public slots:

  void setSession(const QString &session) override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(std::shared_ptr<HelpDialog> &help) override;

private:

  void init() override;

private:

  IMultiViewView *mView;
  IMultiViewModel *mModel;
  std::shared_ptr<HelpDialog> mHelp;

};


} // namespace photomatch

#endif // PHOTOMATCH_MULTIVIEW_PRESENTER_H
