#ifndef FME_CURVES_VIEWER_MODEL_H
#define FME_CURVES_VIEWER_MODEL_H

#include <memory>

#include "fme/ui/mvp.h"

namespace fme
{

class IProjectModel;

class ICurvesViewerModel
  : public IModel
{

  Q_OBJECT

public:

  ICurvesViewerModel(){}
  virtual ~ICurvesViewerModel() {}

  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;
  virtual std::vector<std::tuple<QString, QString, QString>> sessions() const = 0;
};


class CurvesViewerModel
  : public ICurvesViewerModel
{

  Q_OBJECT

public:

  CurvesViewerModel(IProjectModel *mProjectModel);
  ~CurvesViewerModel() override;

// ICurvesViewerModel interface

public:

  std::vector<QString> images() const override;
  std::vector<QString> imagePairs(const QString &imageName) const override;
  std::vector<std::tuple<QString, QString, QString>> sessions() const override;

// IModel interface

private:

  void init() override;

protected:

  IProjectModel *mProjectModel;
};


} // namespace fme

#endif // FME_CURVES_VIEWER_MODEL_H
