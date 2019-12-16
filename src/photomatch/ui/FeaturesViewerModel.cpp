#include "FeaturesViewerModel.h"

#include "photomatch/ui/ProjectModel.h"

namespace photomatch
{

FeaturesViewerModel::FeaturesViewerModel(IProjectModel *mProjectModel)
  : IFeaturesViewerModel(),
    mProjectModel(mProjectModel)
{
  init();
}

FeaturesViewerModel::~FeaturesViewerModel()
{

}

void FeaturesViewerModel::init()
{
  if (mProjectModel->currentSession())
    mSession = mProjectModel->currentSession()->name();
}

QString FeaturesViewerModel::sessionName() const
{
  return mSession;
}

void FeaturesViewerModel::setSessionName(const QString &session)
{
  mSession = session;
}

std::vector<QString> FeaturesViewerModel::images() const
{
  std::vector<QString> images;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    images.push_back((*it)->path());
  }
  return images;
}

std::vector<std::tuple<QPointF, double, double> > FeaturesViewerModel::loadKeypoints(const QString &image)
{
  std::vector<std::tuple<QPointF, double, double>> keyPoints;

  if (std::shared_ptr<Session> session = mProjectModel->findSession(mSession)){

    std::vector<cv::KeyPoint> cvKeyPoints;
    cv::Mat descriptors;
    featuresRead(session->features(image), cvKeyPoints, descriptors);

    if (cvKeyPoints.size() > 0){

      for (size_t i = 0; i < cvKeyPoints.size(); i++){
        QPointF pt(static_cast<qreal>(cvKeyPoints[i].pt.x),
                   static_cast<qreal>(cvKeyPoints[i].pt.y));
        keyPoints.push_back(std::make_tuple(pt, static_cast<double>(cvKeyPoints[i].size), static_cast<double>(cvKeyPoints[i].angle)));
      }

    }
  }


  return keyPoints;
}

} // namespace photomatch
