#ifndef FME_HOMOGRAPHY_VIEWER_MODEL_H
#define FME_HOMOGRAPHY_VIEWER_MODEL_H

#include <memory>

#include "fme/ui/mvp.h"

namespace fme
{

class IProjectModel;

class IHomographyViewerModel
  : public IModel
{

  Q_OBJECT

public:

  IHomographyViewerModel(){}
  virtual ~IHomographyViewerModel() {}

  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;
  virtual QImage homography(const QString &imgName1, const QString &imgName2) const = 0;

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

  std::vector<QString> images() const override;
  std::vector<QString> imagePairs(const QString &imageName) const override;
  QImage homography(const QString &imgName1, const QString &imgName2) const override;

// IModel interface

private:

  void init() override;

protected:

  IProjectModel *mProjectModel;



};


} // namespace fme

#endif // FME_HOMOGRAPHY_VIEWER_MODEL_H
