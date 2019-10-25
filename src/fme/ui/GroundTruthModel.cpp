#include "GroundTruthModel.h"

#include "fme/ui/ProjectModel.h"
#include "fme/core/features/groundtruth.h"

namespace fme
{

GroundTruthModel::GroundTruthModel(IProjectModel *mProjectModel)
  : IGroundTruthModel(),
    mProjectModel(mProjectModel),
    mGroundTruth(nullptr)
{

}

GroundTruthModel::~GroundTruthModel()
{
  if (mGroundTruth) {
    delete mGroundTruth;
    mGroundTruth = nullptr;
  }
}

void GroundTruthModel::init()
{

}

void GroundTruthModel::loadGroundTruth()
{
  if (mGroundTruth == nullptr){
    mGroundTruth = new GroundTruth;
  } else {
    mGroundTruth->clear();
  }

  if (mProjectModel->groundTruth().isEmpty() == false)
    mGroundTruth->read(mProjectModel->groundTruth());
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

std::vector<std::pair<QPointF, QPointF> > GroundTruthModel::groundTruth(const QString &imgName1, const QString &imgName2) const
{
  std::vector<std::pair<QPointF,QPointF>> r_ground_truth;
  std::shared_ptr<HomologusPoints> ground_truth = mGroundTruth->findPair(imgName1, imgName2);
  if (ground_truth){
    r_ground_truth = ground_truth->homologusPoints();
  }
  return r_ground_truth;
}

QTransform GroundTruthModel::transform(const QString &imgName1, const QString &imgName2) const
{
  QTransform trf;
  std::shared_ptr<HomologusPoints> ground_truth = mGroundTruth->findPair(imgName1, imgName2);
  cv::Mat h = ground_truth->homography();
  if (h.empty() == false){
    trf.setMatrix(h.at<float>(0, 0), h.at<float>(0, 1), h.at<float>(0, 2),
                  h.at<float>(1, 0), h.at<float>(1, 1), h.at<float>(1, 2),
                  h.at<float>(2, 0), h.at<float>(2, 1), h.at<float>(2, 2));
  }

  return trf;
}

void GroundTruthModel::saveGroundTruth()
{
  if (mProjectModel->groundTruth().isEmpty()){
    QString gt = mProjectModel->projectFolder();
    gt.append("/GroundTruth.txt");
    mProjectModel->setGroundTruth(gt);
  }
  mGroundTruth->write(mProjectModel->groundTruth());
}

void GroundTruthModel::addHomologusPoints(const QString &image1, QPointF pt1, const QString &image2, QPointF pt2)
{
  std::shared_ptr<HomologusPoints> homologus = mGroundTruth->pair(image1, image2);
  homologus->addPoints(pt1, pt2);
}


} // namespace fme
