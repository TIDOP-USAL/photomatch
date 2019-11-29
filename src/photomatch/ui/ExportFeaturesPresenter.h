#ifndef PHOTOMATCH_EXPORT_FEATURES_PRESENTER_H
#define PHOTOMATCH_EXPORT_FEATURES_PRESENTER_H

#include <QObject>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IExportFeaturesView;
class IExportFeaturesModel;
class Help;

class IExportFeaturesPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IExportFeaturesPresenter(){}
  virtual ~IExportFeaturesPresenter() override = default;

public slots:

  virtual void save() = 0;
  virtual void sessionChange(const QString &session) = 0;

};


class ExportFeaturesPresenter
  : public IExportFeaturesPresenter
{

  Q_OBJECT

public:

  ExportFeaturesPresenter(IExportFeaturesView *view,
                          IExportFeaturesModel *model);
  ~ExportFeaturesPresenter() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;

private:

  void init() override;

// IExportFeaturesPresenter interface

public:

  void save() override;
  void sessionChange(const QString &session) override;

protected:

  IExportFeaturesView *mView;
  IExportFeaturesModel *mModel;
};



} // namespace photomatch

#endif // PHOTOMATCH_EXPORT_FEATURES_PRESENTER_H
