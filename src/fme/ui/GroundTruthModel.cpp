#include "GroundTruthModel.h"

#include "fme/ui/ProjectModel.h"

namespace fme
{

GroundTruthModel::GroundTruthModel(IProjectModel *mProjectModel)
  : IGroundTruthModel(),
    mProjectModel(mProjectModel)
{

}



void GroundTruthModel::init()
{
}

std::vector<QString> GroundTruthModel::images() const
{
  std::vector<QString> images;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    images.push_back((*it)->path());
  }
  return images;
}

std::vector<QString> GroundTruthModel::imagePairs(const QString &imageName) const
{
  std::vector<QString> pairs;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    if (imageName.compare((*it)->name()) != 0){
      pairs.push_back((*it)->path());
    }
  }
  return pairs;
}

size_t GroundTruthModel::addPoint(const QString &image, const QPointF &pt)
{
  size_t id = mPoints[image].size();
  mPoints[image].push_back(pt);

  return id;
}

void GroundTruthModel::addCorrespondence(const QString &image1, size_t idPt1, const QString &image2, size_t idPt2)
{
  mControlPointsCorrespondences[image1][image2].push_back(std::make_pair(idPt1, idPt2));
}

} // namespace fme
