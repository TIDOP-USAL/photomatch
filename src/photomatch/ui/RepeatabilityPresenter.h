#ifndef PHOTOMATCH_REPEATABILITY_PRESENTER_H
#define PHOTOMATCH_REPEATABILITY_PRESENTER_H

#include <memory>

#include <QObject>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IRepeatabilityView;
class IRepeatabilityModel;
class Help;

class IRepeatabilityPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IRepeatabilityPresenter() : IPresenter() {}
  virtual ~IRepeatabilityPresenter() override {}

protected slots:

  virtual void selectSession(const QString &session) = 0;
};

class RepeatabilityPresenter
  : public IRepeatabilityPresenter
{

  Q_OBJECT

public:

  RepeatabilityPresenter(IRepeatabilityView *view,
                         IRepeatabilityModel *model);
  ~RepeatabilityPresenter() override {}

//IRepeatabilityPresenter interface

protected slots:

  void selectSession(const QString &session) override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;

private:

  void init() override;

private:

  IRepeatabilityView *mView;
  IRepeatabilityModel *mModel;
  std::shared_ptr<Help> mHelp;
};

} // namespace photomatch

#endif // PHOTOMATCH_REPEATABILITY_PRESENTER_H
