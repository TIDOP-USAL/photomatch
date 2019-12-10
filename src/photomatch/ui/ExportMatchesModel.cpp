#include "ExportMatchesModel.h"

#include "photomatch/ui/ProjectModel.h"

#include <tidop/core/messages.h>

#include <QImageReader>
#include <QFileInfo>

namespace photomatch
{

ExportMatchesModel::ExportMatchesModel(IProjectModel *mProjectModel)
  : IExportMatchesModel(),
    mProjectModel(mProjectModel)
{
  init();
}

ExportMatchesModel::~ExportMatchesModel()
{

}

QStringList ExportMatchesModel::sessions() const
{
  QStringList sessions;

  for (auto it = mProjectModel->sessionBegin(); it != mProjectModel->sessionEnd(); it++){
    sessions.push_back((*it)->name());
  }

  return sessions;
}

QString ExportMatchesModel::sessionName() const
{
  return mSession;
}

QStringList ExportMatchesModel::formats() const
{
  QStringList formats;
  formats.push_back("BINGO");
  formats.push_back("ORIMA");
  return formats;
}

//QStringList ExportMatchesModel::features() const
//{
//  QStringList images;

//  if (std::shared_ptr<Session> session = mProjectModel->findSession(mSession)){
//    if (session->features().size() > 0 ){
//      for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
//        images.push_back((*it)->name());
//      }
//    }
//  }

//  return images;
//}

void ExportMatchesModel::exportMatches(const QString &file, const QString &format) const
{
  if (std::shared_ptr<Session> session = mProjectModel->findSession(mSession)){

    QByteArray ba = file.toLocal8Bit();
    const char *c_file = ba.data();
    msgInfo("Exported matches: %s", c_file);

    QString ext;

    if (format.compare("OpenCV XML") == 0){
      ext = ".xml";
    } else if (format.compare("OpenCV YML") == 0) {
      ext = ".yml";
    } else if (format.compare("ORIMA") == 0) {
      ext = ".txt";
    } else if (format.compare("BINGO") == 0) {
      ext = ".txt";
    } else {
      /// Formato desconocido
      return;
    }

    /// TODO: leer el fichero de pares
    std::vector<std::vector<std::pair<QString,int>>> idx_pass_points;

//    for (auto &id_image : features){
//      std::vector<cv::KeyPoint> cvKeyPoints;
//      cv::Mat descriptors;
//      featuresRead(session->features(id_image), cvKeyPoints, descriptors);

//      if (cvKeyPoints.size() > 0){
//        QString file = path;
//        file.append("\\").append(id_image).append(ext);
//        featuresWrite(file, cvKeyPoints, descriptors);
//      }

//    }

  }
}

void ExportMatchesModel::setSessionName(const QString &session)
{
  mSession = session;
}

void ExportMatchesModel::init()
{
  mSession = mProjectModel->currentSession()->name();
}

} // namespace photomatch


