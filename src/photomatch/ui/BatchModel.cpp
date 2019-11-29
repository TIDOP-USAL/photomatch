#include "BatchModel.h"

#include "photomatch/ui/ProjectModel.h"

namespace photomatch
{

BatchModel::BatchModel(/*IProjectModel *mProjectModel*/)
  : IBatchModel()/*,
    mProjectModel(mProjectModel)*/
{
  init();
}

BatchModel::~BatchModel()
{

}

void BatchModel::init()
{
  //mSession = mProjectModel->currentSession()->name();
}

//QStringList BatchModel::sessions() const
//{
//  QStringList sessions;

//  for (auto it = mProjectModel->sessionBegin(); it != mProjectModel->sessionEnd(); it++){
//    sessions.push_back((*it)->name());
//  }

//  return sessions;
//}

//QString BatchModel::sessionName() const
//{
//  return mSession;
//}

//void BatchModel::setSessionName(const QString &session)
//{
//  mSession = session;
//}

} // namespace photomatch


