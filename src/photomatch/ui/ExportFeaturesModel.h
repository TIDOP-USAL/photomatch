#ifndef PHOTOMATCH_EXPORT_FEATURES_MODEL_H
#define PHOTOMATCH_EXPORT_FEATURES_MODEL_H


#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel;

class IExportFeaturesModel
  : public IModel
{

  Q_OBJECT

public:

  IExportFeaturesModel() {}
  virtual ~IExportFeaturesModel() override = default;

  virtual QStringList sessions() const = 0;
  //virtual QString sessionName() const = 0;
  virtual QString activeSessionName() const = 0;
  virtual QStringList formats() const = 0;
  virtual QStringList features(const QString &sessionName) const = 0;

public slots:

  virtual void exportFeatures(const QString &sessionName, const QStringList &features, const QString &path, const QString &format) const = 0;
  //virtual void setSessionName(const QString &session) = 0;

};

class ExportFeaturesModel
  : public IExportFeaturesModel
{

  Q_OBJECT

public:

  ExportFeaturesModel(IProjectModel *mProjectModel);
  ~ExportFeaturesModel() override;

  QStringList sessions() const override;
  //QString sessionName() const override;
  QString activeSessionName() const override;
  QStringList formats() const override;
  QStringList features(const QString &sessionName) const override;

public slots:

  void exportFeatures(const QString &sessionName, const QStringList &features, const QString &path, const QString &format) const override;
  //void setSessionName(const QString &session) override;

// IModel interface

private:

  void init() override;

protected:

  IProjectModel *mProjectModel;
  //QString mSession;

};

} // namespace photomatch

#endif // PHOTOMATCH_EXPORT_FEATURES_MODEL_H
