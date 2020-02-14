/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#include "ExportFeaturesModel.h"

#include "photomatch/ui/ProjectModel.h"
#include "photomatch/core/features/featio.h"

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
      std::unique_ptr<FeaturesReader> featuresRead = FeaturesReaderFactory::createReader(session->features(id_image));
      featuresRead->read();
      std::vector<cv::KeyPoint> keyPoints1 = featuresRead->keyPoints();
      cv::Mat descriptors = featuresRead->descriptors();
      if (keyPoints1.size() > 0){
        QString file = path;
        file.append("\\").append(id_image).append(ext);
        std::unique_ptr<FeaturesWriter> featuresWriter = FeaturesWriterFactory::createWriter(file);
        featuresWriter->setKeyPoints(keyPoints1);
        featuresWriter->setDescriptors(descriptors);
        featuresWriter->write();
      }

    }

  }
}

void ExportFeaturesModel::init()
{
}

} // namespace photomatch


