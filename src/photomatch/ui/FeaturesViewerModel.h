#ifndef PHOTOMATCH_FEATURES_VIEWER_MODEL_H
#define PHOTOMATCH_FEATURES_VIEWER_MODEL_H

#include <memory>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel;

class IFeaturesViewerModel
  : public IModel
{

  Q_OBJECT

public:

  IFeaturesViewerModel() {}
  virtual ~IFeaturesViewerModel() = default;

  virtual QString sessionName() const = 0;
  virtual void setSessionName(const QString &session) = 0;
  virtual std::vector<QString> images() const = 0;
  virtual std::vector<std::tuple<QPointF, double, double>> loadKeypoints(const QString &image) = 0;


};

class FeaturesViewerModel
  : public IFeaturesViewerModel
{

 Q_OBJECT

public:

  FeaturesViewerModel(IProjectModel *mProjectModel);
  ~FeaturesViewerModel() override;

protected:

  IProjectModel *mProjectModel;

// IModel interface

private:

  void init() override;

// IFeaturesViewerModel interface
public:

  QString sessionName() const override;
  void setSessionName(const QString &session) override;
  std::vector<QString> images() const override;
  std::vector<std::tuple<QPointF, double, double>> loadKeypoints(const QString &image) override;

protected:

  QString mSession;
};

} // namespace photomatch

#endif // PHOTOMATCH_FEATURES_VIEWER_MODEL_H
