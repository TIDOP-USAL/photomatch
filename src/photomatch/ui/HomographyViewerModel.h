#ifndef PHOTOMATCH_HOMOGRAPHY_VIEWER_MODEL_H
#define PHOTOMATCH_HOMOGRAPHY_VIEWER_MODEL_H

#include <memory>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel;

class IHomographyViewerModel
  : public IModel
{

  Q_OBJECT

public:

  IHomographyViewerModel(){}
  virtual ~IHomographyViewerModel() {}

  virtual QString currentSession() const = 0;
  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;
  virtual QImage homography(const QString &imgName1, const QString &imgName2) const = 0;
  virtual void setUseCuda(bool active) = 0;

};

class HomographyViewerModel
  : public IHomographyViewerModel
{

  Q_OBJECT

public:

  HomographyViewerModel(IProjectModel *mProjectModel);
  ~HomographyViewerModel() override;

// IHomographyViewerModel interface

public:

  QString currentSession() const override;
  std::vector<QString> images() const override;
  std::vector<QString> imagePairs(const QString &imageName) const override;
  QImage homography(const QString &imgName1, const QString &imgName2) const override;
  void setUseCuda(bool active) override;

// IModel interface

private:

  void init() override;

protected:

  IProjectModel *mProjectModel;
  bool bUseCuda;
};


} // namespace photomatch

#endif // PHOTOMATCH_HOMOGRAPHY_VIEWER_MODEL_H
