#ifndef PHOTOMATCH_EXPORT_MATCHES_MODEL_H
#define PHOTOMATCH_EXPORT_MATCHES_MODEL_H


#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel;

class IExportMatchesModel
  : public IModel
{

  Q_OBJECT

public:

  IExportMatchesModel() {}
  virtual ~IExportMatchesModel() override = default;

  virtual QStringList sessions() const = 0;
  virtual QString sessionName() const = 0;
  virtual QStringList formats() const = 0;
  //virtual QStringList features() const = 0;

public slots:

  virtual void exportMatches(const QString &file, const QString &format) const = 0;
  virtual void setSessionName(const QString &session) = 0;

};

class ExportMatchesModel
  : public IExportMatchesModel
{

  Q_OBJECT

public:

  ExportMatchesModel(IProjectModel *mProjectModel);
  ~ExportMatchesModel() override;

  QStringList sessions() const override;
  QString sessionName() const override;
  QStringList formats() const override;
  //QStringList features() const override;

public slots:

  void exportMatches(const QString &file, const QString &format) const override;
  void setSessionName(const QString &session) override;

// IModel interface

private:

  void init() override;

protected:

  IProjectModel *mProjectModel;
  QString mSession;

};

} // namespace photomatch

#endif // PHOTOMATCH_EXPORT_MATCHES_MODEL_H
