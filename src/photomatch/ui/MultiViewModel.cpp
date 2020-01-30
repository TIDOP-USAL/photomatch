#include "MultiViewModel.h"

#include "photomatch/ui/ProjectModel.h"

#include <QImageReader>

namespace photomatch
{

MultiViewModel::MultiViewModel(IProjectModel *mProjectModel)
  : IMultiViewModel(),
    mProjectModel(mProjectModel)
{
  init();
}

MultiViewModel::~MultiViewModel()
{

}

QString MultiViewModel::sessionName() const
{
  return mSession;
}

void MultiViewModel::setSessionName(const QString &session)
{
  mSession = session;
}

void MultiViewModel::loadPassPoints()
{
  if (std::shared_ptr<Session> session = mProjectModel->findSession(mSession)){
    passPointsRead(session->passPoints(), mPassPoints);
  } else {
    mPassPoints.clear();
  }
}

std::vector<size_t> MultiViewModel::passPointIds() const
{
  std::vector<size_t> ids;

  for (size_t i = 0; i < mPassPoints.size(); i++) {
    if (mPassPoints[i].empty() == false)
      ids.push_back(i);
  }

  return ids;
}

std::vector<std::pair<size_t, size_t> > MultiViewModel::passPointIdsAndSize() const
{
  std::vector<std::pair<size_t, size_t>> ids;

  for (size_t i = 0; i < mPassPoints.size(); i++) {
    if (mPassPoints[i].empty() == false)
      ids.push_back(std::make_pair(i, mPassPoints[i].size()));
  }

  return ids;
}

std::vector<std::pair<QString, QPointF>> MultiViewModel::images(size_t passPointId) const
{
  std::vector<std::pair<QString, QPointF>> images;

  if (passPointId < mPassPoints.size()){
    if (std::shared_ptr<Session> session = mProjectModel->findSession(mSession)){

      for (size_t j = 0; j < mPassPoints[passPointId].size(); j++) {
        QString img_name = mPassPoints[passPointId][j].first;
        size_t pt_id = static_cast<size_t>(mPassPoints[passPointId][j].second);
        for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++) {
          if ((*it)->name().compare(img_name) == 0){
            /// Fichero imagen
            QString img_file = (*it)->path();

            /// Busqueda del punto
            std::vector<cv::KeyPoint> keyPoints;
            cv::Mat descriptors;
            featuresRead(session->features(img_name), keyPoints, descriptors);
            descriptors.release();

            QPointF pt(static_cast<double>(keyPoints[pt_id].pt.x),
                       static_cast<double>(keyPoints[pt_id].pt.y));
            images.push_back(std::make_pair(img_file, pt));

            break;
          }
        }
      }
    }
  }
  return images;
}

void MultiViewModel::init()
{
  if (mProjectModel->currentSession())
    mSession = mProjectModel->currentSession()->name();
}

} // namespace photomatch
