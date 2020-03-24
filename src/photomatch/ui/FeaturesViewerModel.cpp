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


#include "FeaturesViewerModel.h"

#include "photomatch/core/features/featio.h"
#include "photomatch/ui/ProjectModel.h"

#include <tidop/core/messages.h>

namespace photomatch
{

FeaturesViewerModelImp::FeaturesViewerModelImp(ProjectModel *mProjectModel)
  : FeaturesViewerModel(),
    mProjectModel(mProjectModel)
{
  init();
}

FeaturesViewerModelImp::~FeaturesViewerModelImp()
{

}

void FeaturesViewerModelImp::init()
{
  if (mProjectModel->currentSession())
    mSession = mProjectModel->currentSession()->name();
}

QString FeaturesViewerModelImp::sessionName() const
{
  return mSession;
}

void FeaturesViewerModelImp::setSessionName(const QString &session)
{
  mSession = session;
}

std::vector<QString> FeaturesViewerModelImp::images() const
{
  std::vector<QString> images;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    images.push_back((*it)->path());
  }
  return images;
}

std::vector<std::tuple<QPointF, double, double> > FeaturesViewerModelImp::loadKeypoints(const QString &image)
{
  try {
    std::vector<std::tuple<QPointF, double, double>> keyPoints;

    if (std::shared_ptr<Session> session = mProjectModel->findSession(mSession)){

      std::unique_ptr<FeaturesReader> featuresRead = FeaturesReaderFactory::createReader(session->features(image));
      featuresRead->read();
      std::vector<cv::KeyPoint> cvKeyPoints = featuresRead->keyPoints();

      if (cvKeyPoints.size() > 0){

        for (size_t i = 0; i < cvKeyPoints.size(); i++){
          QPointF pt(static_cast<qreal>(cvKeyPoints[i].pt.x),
                     static_cast<qreal>(cvKeyPoints[i].pt.y));
          keyPoints.push_back(std::make_tuple(pt, static_cast<double>(cvKeyPoints[i].size), static_cast<double>(cvKeyPoints[i].angle)));
        }

      }
    }

    return keyPoints;
  } catch (std::exception &e) {
    msgError(e.what());
    return std::vector<std::tuple<QPointF, double, double>>();
  }
}

} // namespace photomatch
