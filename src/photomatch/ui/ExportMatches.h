#ifndef PHOTOMATCH_EXPORT_MATCHES_INTERFACES_H
#define PHOTOMATCH_EXPORT_MATCHES_INTERFACES_H

#include "photomatch/ui/mvp.h"


namespace photomatch
{

class ProjectModelImp;

class ExportMatchesModel
  : public IModel
{

  Q_OBJECT

public:

  ExportMatchesModel() {}
  virtual ~ExportMatchesModel() override = default;

  virtual QStringList sessions() const = 0;
  virtual QString sessionName() const = 0;
  virtual QStringList formats() const = 0;

public slots:

  virtual void exportMatches(const QString &file, const QString &format) const = 0;
  virtual void setSessionName(const QString &session) = 0;

};



class ExportMatchesView
  : public IDialogView
{

  Q_OBJECT

public:

  ExportMatchesView(QWidget *parent) : IDialogView(parent) {}
  virtual ~ExportMatchesView() override = default;

public slots:

  virtual void setSessions(const QStringList &sessions) = 0;
  virtual void setActiveSession(const QString &session) = 0;

signals:

  void sessionChange(QString);
};


class ExportMatchesPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  ExportMatchesPresenter(){}
  virtual ~ExportMatchesPresenter() override = default;

public slots:

  virtual void save() = 0;
  virtual void sessionChange(const QString &session) = 0;

};


} // namespace photomatch

#endif // PHOTOMATCH_EXPORT_MATCHES_INTERFACES_H
