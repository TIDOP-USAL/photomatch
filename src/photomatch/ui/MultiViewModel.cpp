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


#include "MultiViewModel.h"

#include "photomatch/core/features/featio.h"
#include "photomatch/ui/ProjectModel.h"

#include <QImageReader>

namespace photomatch
{

MultiviewModel::MultiviewModel(IProjectModel *mProjectModel)
  : IMultiViewModel(),
    mProjectModel(mProjectModel)
{
  init();
}

MultiviewModel::~MultiviewModel()
{

}

QString MultiviewModel::sessionName() const
{
  return mSession;
}

void MultiviewModel::setSessionName(const QString &session)
{
  mSession = session;
}

void MultiviewModel::loadPassPoints()
{
  if (std::shared_ptr<Session> session = mProjectModel->findSession(mSession)){
    passPointsRead(session->passPoints(), mPassPoints);
  } else {
    mPassPoints.clear();
  }
}

std::vector<size_t> MultiviewModel::passPointIds() const
{
  std::vector<size_t> ids;

  for (size_t i = 0; i < mPassPoints.size(); i++) {
    if (mPassPoints[i].empty() == false)
      ids.push_back(i);
  }

  return ids;
}

std::vector<std::pair<size_t, size_t> > MultiviewModel::passPointIdsAndSize() const
{
  std::vector<std::pair<size_t, size_t>> ids;

  for (size_t i = 0; i < mPassPoints.size(); i++) {
    if (mPassPoints[i].empty() == false)
      ids.push_back(std::make_pair(i, mPassPoints[i].size()));
  }

  return ids;
}

std::vector<std::pair<QString, QPointF>> MultiviewModel::images(size_t passPointId) const
{
  std::vector<std::pair<QString, QPointF>> images;

  if (passPointId < mPassPoints.size()){
    if (std::shared_ptr<Session> session = mProjectModel->findSession(mSession)){

      for (size_t j = 0; j < mPassPoints[passPointId].size(); j++) {
        QString img_name = mPassPoints[passPointId][j].first;
        size_t pt_id = static_cast<size_t>(mPassPoints[passPointId][j].second);
        for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++) {
          if ((*it)->name().compare(img_name) == 0){
            QString img_file = (*it)->path();

            std::unique_ptr<FeaturesReader> featuresRead = FeaturesReaderFactory::createReader(session->features(img_name));
            featuresRead->read();
            std::vector<cv::KeyPoint> keyPoints = featuresRead->keyPoints();

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

void MultiviewModel::init()
{
  if (mProjectModel->currentSession())
    mSession = mProjectModel->currentSession()->name();
}

} // namespace photomatch
