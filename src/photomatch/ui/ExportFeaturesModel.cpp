#include "ExportFeaturesModel.h"

#include "photomatch/ui/ProjectModel.h"

#include <QImageReader>
#include <QFileInfo>

namespace photomatch
{

ExportFeaturesModel::ExportFeaturesModel(IProjectModel *mProjectModel)
  : IExportFeaturesModel(),
    mProjectModel(mProjectModel)
{
  init();
}

ExportFeaturesModel::~ExportFeaturesModel()
{

}

QStringList ExportFeaturesModel::sessions() const
{
  QStringList sessions;

  for (auto it = mProjectModel->sessionBegin(); it != mProjectModel->sessionEnd(); it++){
    sessions.push_back((*it)->name());
  }

  return sessions;
}

QString ExportFeaturesModel::activeSessionName() const
{
  return mProjectModel->currentSession()->name();
}

QStringList ExportFeaturesModel::formats() const
{
  QStringList formats;
  formats.push_back("OpenCV XML");
  formats.push_back("OpenCV YML");
  formats.push_back("Plain text");
  return formats;
}

QStringList ExportFeaturesModel::features(const QString &sessionName) const
{
  QStringList images;

  if (std::shared_ptr<Session> session = mProjectModel->findSession(sessionName)){
    if (session->features().size() > 0 ){
      for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
        images.push_back((*it)->name());
      }
    }
  }

  return images;
}

void ExportFeaturesModel::exportFeatures(const QString &sessionName,
                                         const QStringList &features,
                                         const QString &path,
                                         const QString &format) const
{
  if (std::shared_ptr<Session> session = mProjectModel->findSession(sessionName)){

    QString ext;

    if (format.compare("OpenCV XML") == 0){
      ext = ".xml";
    } else if (format.compare("OpenCV YML") == 0) {
      ext = ".yml";
    } else if (format.compare("Plain text") == 0) {
      ext = ".txt";
    } else {
      /// Formato desconocido
      return;
    }

    for (auto &id_image : features){
      std::vector<cv::KeyPoint> cvKeyPoints;
      cv::Mat descriptors;
      featuresRead(session->features(id_image), cvKeyPoints, descriptors);

      if (cvKeyPoints.size() > 0){
        QString file = path;
        file.append("\\").append(id_image).append(ext);
        featuresWrite(file, cvKeyPoints, descriptors);
      }

    }

  }
}

void ExportFeaturesModel::init()
{
}

} // namespace photomatch


