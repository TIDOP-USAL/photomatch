#ifndef PHOTOMATCH_EXPORT_MATCHES_PRESENTER_H
#define PHOTOMATCH_EXPORT_MATCHES_PRESENTER_H

#include <QObject>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IExportMatchesView;
class IExportMatchesModel;
class HelpDialog;

class IExportMatchesPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IExportMatchesPresenter(){}
  virtual ~IExportMatchesPresenter() override = default;

public slots:

  virtual void save() = 0;
  virtual void sessionChange(const QString &session) = 0;

};


class ExportMatchesPresenter
  : public IExportMatchesPresenter
{

  Q_OBJECT

public:

  ExportMatchesPresenter(IExportMatchesView *view,
                         IExportMatchesModel *model);
  ~ExportMatchesPresenter() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(std::shared_ptr<HelpDialog> &help) override;

private:

  void init() override;

// IExportMatchesPresenter interface

public:

  void save() override;
  void sessionChange(const QString &session) override;

protected:

  IExportMatchesView *mView;
  IExportMatchesModel *mModel;
  std::shared_ptr<HelpDialog> mHelp;
};



} // namespace photomatch

#endif // PHOTOMATCH_EXPORT_MATCHES_PRESENTER_H
