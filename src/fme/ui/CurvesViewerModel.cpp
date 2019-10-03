#include "CurvesViewerModel.h"

#include <tidop/core/messages.h>

#include "fme/ui/ProjectModel.h"
#include "fme/core/utils.h"

#include <QFileInfo>

namespace fme
{

CurvesViewerModel::CurvesViewerModel(fme::IProjectModel *mProjectModel)
  : ICurvesViewerModel(),
    mProjectModel(mProjectModel)
{
  init();
}

CurvesViewerModel::~CurvesViewerModel()
{

}

std::vector<QString> CurvesViewerModel::images() const
{
  std::vector<QString> images;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    images.push_back((*it)->path());
  }
  return images;
}

std::vector<QString> CurvesViewerModel::imagePairs(const QString &imageName) const
{
  std::vector<QString> pairs;
  if (std::shared_ptr<Session> session = mProjectModel->currentSession()){
    std::vector<std::pair<QString, QString>> matches = session->matches(imageName);
    if (!matches.empty()){
      for (auto &m : matches){
        QString name = m.first;
        for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
          if ((*it)->name().compare(name) == 0){
            pairs.push_back((*it)->path());
            break;
          }
        }
      }
    }
  }

  return pairs;
}

std::vector<std::tuple<QString, QString, QString> > CurvesViewerModel::sessions() const
{
  std::vector<std::tuple<QString, QString, QString>> sessions;

  for (auto it = mProjectModel->sessionBegin(); it != mProjectModel->sessionEnd(); it++){
    if ((*it)->detector() && (*it)->descriptor()){
      QString sessionName = (*it)->name();
      QString detectorName = (*it)->detector()->name();
      QString descriptorName = (*it)->descriptor()->name();
      sessions.push_back(std::make_tuple(sessionName, detectorName, descriptorName));
    }
  }

  return sessions;
}

void CurvesViewerModel::init()
{
}

} // namespace fme


