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


#include "ExportMatchesModel.h"

#include "photomatch/ui/ProjectModel.h"
#include "photomatch/core/features/matcher.h"
#include "photomatch/core/features/features.h"
#include "photomatch/core/features/featio.h"

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
    if ((*it)->matches().empty() == false)
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

void ExportMatchesModel::exportMatches(const QString &file, const QString &format) const
{
  if (std::shared_ptr<Session> session = mProjectModel->findSession(mSession)){

    std::vector<std::vector<std::pair<QString,int>>> pass_points;
    passPointsRead(session->passPoints(), pass_points);

    QByteArray ba = file.toLocal8Bit();
    const char *c_file = ba.data();
    msgInfo("Exported matches: %s", c_file);

    //QString ext;

    /*if (format.compare("OpenCV XML") == 0){
      ext = ".xml";
    } else if (format.compare("OpenCV YML") == 0) {
      ext = ".yml";
    } else*/

    if (format.compare("ORIMA") == 0) {

      std::ofstream ofs(file.toStdString(), std::ofstream::trunc);
      if (ofs.is_open()){

        for (auto &feat : session->features()){
          QString image_id = QFileInfo(feat).baseName();

          std::unique_ptr<FeaturesReader> featuresRead = FeaturesReaderFactory::createReader(feat);
          featuresRead->read();
          std::vector<cv::KeyPoint> keyPoints = featuresRead->keyPoints();
          featuresRead.reset(nullptr);

          for (size_t i = 0; i < pass_points.size(); i++) {

            for (size_t j = 0; j < pass_points[i].size(); j++){
              if (pass_points[i][j].first.compare(image_id) == 0){
                size_t pt_id = static_cast<size_t>(pass_points[i][j].second);
                ofs << "\"" << image_id.toStdString() << "\" " << i << " "
                    << keyPoints[pt_id].pt.x << " " << keyPoints[pt_id].pt.y
                    << " 0 M" << std::endl;
                break;
              }
            }

          }
        }

        ofs.close();
      }

    } else if (format.compare("BINGO") == 0) {

      std::ofstream ofs(file.toStdString(), std::ofstream::trunc);
      if (ofs.is_open()){
        for (auto &feat : session->features()){

          QString image_id = QFileInfo(feat).baseName();
          ofs << image_id.toStdString() << std::endl;

//          std::vector<cv::KeyPoint> keyPoints;
//          cv::Mat descriptors;
//          featuresRead(feat, keyPoints, descriptors);
//          descriptors.release();
          std::unique_ptr<FeaturesReader> featuresRead = FeaturesReaderFactory::createReader(feat);
          featuresRead->read();
          std::vector<cv::KeyPoint> keyPoints = featuresRead->keyPoints();

          for (size_t i = 0; i < pass_points.size(); i++) {

            for (size_t j = 0; j < pass_points[i].size(); j++){
              if (pass_points[i][j].first.compare(image_id) == 0){
                size_t pt_id = static_cast<size_t>(pass_points[i][j].second);
                ofs << i << " " << keyPoints[pt_id].pt.x
                         << " " << keyPoints[pt_id].pt.y  << std::endl;
                break;
              }
            }

          }
          ofs << -99 << std::endl;
        }
        ofs.close();
      }

    } else {

      QByteArray ba = format.toLocal8Bit();
      msgError("unknown format: %s", ba.data());
      return;
    }

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


