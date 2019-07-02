#ifndef FME_SETTINGS_PRESENTER_H
#define FME_SETTINGS_PRESENTER_H

#include "fme/fme_global.h"

#include <QObject>

#include "mvp.h"

namespace fme
{

class ISettingsView;
class ISettingsModel;

class ISettingsPresenter
  : public IPresenter
{
  Q_OBJECT

public:

  ISettingsPresenter() {}
  virtual ~ISettingsPresenter(){}

signals:

private slots:

  virtual void save() = 0;

  virtual void discart() = 0;
};

class SettingsPresenter
  : public ISettingsPresenter
{
  Q_OBJECT

public:

  SettingsPresenter(ISettingsView *view, ISettingsModel *model);
  ~SettingsPresenter() override {}

// IPresenter interface

public slots:

  void help() override;
  void open() override;

private:

  void init() override;

// ISettingsPresenter interface

private slots:

  void save() override;
  void discart() override;

protected:

  ISettingsView *mView;
  ISettingsModel *mModel;

};

} // namespace fme

#endif // FME_SETTINGS_PRESENTER_H
