#include "GroundTruthModel.h"

#include "photomatch/ui/ProjectModel.h"
#include "photomatch/core/features/groundtruth.h"

namespace photomatch
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

  std::shared_ptr<HomologusPoints> ground_truth_inv = mGroundTruth->findPair(imgName2, imgName1);
  if (ground_truth_inv){
    for (auto &homologusPoint : ground_truth_inv->homologusPoints()){
      r_ground_truth.push_back(std::make_pair(homologusPoint.second, homologusPoint.first)); /// .....
    }
  }

  return r_ground_truth;
}

QTransform GroundTruthModel::transform(const QString &imgName1, const QString &imgName2) const
{
  QTransform trf;
  HomologusPoints homologusPoints(imgName1, imgName2);
  if (std::shared_ptr<HomologusPoints> ground_truth_direct = mGroundTruth->findPair(imgName1, imgName2)){
    for (auto &homolPoint : ground_truth_direct->homologusPoints()){
      homologusPoints.push_back(homolPoint);
    }
  }

  if (std::shared_ptr<HomologusPoints> ground_truth_inverse = mGroundTruth->findPair(imgName2, imgName1)){
    for (auto &homolPoint : ground_truth_inverse->homologusPoints()){
      homologusPoints.addPoints(homolPoint.second, homolPoint.first);
    }
  }

  if (homologusPoints.empty() == false) {
    cv::Mat h = homologusPoints.homography();
    if (h.empty() == false){
      trf.setMatrix(h.at<double>(0, 0), h.at<double>(1, 0), h.at<double>(2, 0),
                    h.at<double>(0, 1), h.at<double>(1, 1), h.at<double>(2, 1),
                    h.at<double>(0, 2), h.at<double>(1, 2), h.at<double>(2, 2));
    }
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

void GroundTruthModel::setGroundTruth(const QString &file)
{
  mProjectModel->setGroundTruth(file);
  this->loadGroundTruth();
}

bool GroundTruthModel::existGroundTruth() const
{
  return !mProjectModel->groundTruth().isEmpty();
}

QString GroundTruthModel::projectPath() const
{
  return mProjectModel->projectFolder();
}

void GroundTruthModel::addHomologusPoints(const QString &image1, QPointF pt1, const QString &image2, QPointF pt2)
{
  std::shared_ptr<HomologusPoints> homologus = mGroundTruth->pair(image1, image2);
  if (homologus)
    homologus->addPoints(pt1, pt2);
}


} // namespace photomatch
