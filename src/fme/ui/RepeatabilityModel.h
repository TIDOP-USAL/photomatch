#ifndef FME_REPEATABILITY_MODEL_H
#define FME_REPEATABILITY_MODEL_H

#include <memory>

#include <QPointF>

#include "fme/ui/mvp.h"

namespace fme
{

class IProjectModel;

class IRepeatabilityModel
  : public IModel
{

  Q_OBJECT

public:

  IRepeatabilityModel(){}
  virtual ~IRepeatabilityModel() {}

  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;
  virtual std::vector<std::tuple<QString, QString, QString>> sessions() const = 0;
  virtual std::vector<std::tuple<QString, QString, QString, float, int>> computeRepeatability(const QString &session/*, const QString &imgLeft, const QString &imgRight*/) const = 0;

};


class RepeatabilityModel
  : public IRepeatabilityModel
{

  Q_OBJECT

public:

  RepeatabilityModel(IProjectModel *projectModel);
  virtual ~RepeatabilityModel() override;

// IRepeteabilityModel interface

public:

  std::vector<QString> images() const override;
  std::vector<QString> imagePairs(const QString &imageName) const override;
  std::vector<std::tuple<QString, QString, QString>> sessions() const override;
  std::vector<std::tuple<QString, QString, QString, float, int>> computeRepeatability(const QString &session/*, const QString &imgLeft, const QString &imgRight*/) const override;

// IModel interface

private:

  void init() override;

protected:

  IProjectModel *mProjectModel;
};


} // namespace fme

#endif // FME_REPEATABILITY_MODEL_H
