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


#include "PassPointsGroupingProcess.h"

#include "photomatch/core/features/features.h"
#include "photomatch/core/features/matcher.h"

#include <tidop/core/messages.h>

#include <QFileInfo>

namespace photomatch
{

PassPointsGroupingProcess::PassPointsGroupingProcess(const std::list<std::tuple<QString, QString, QString> > &pairs,
                                                     const QString &passPointsFile)
  : ProcessConcurrent(),
    mPairs(pairs),
    mPassPointsFile(passPointsFile)
{

}

void PassPointsGroupingProcess::run()
{

  std::vector<std::vector<std::pair<QString,int>>> idx_pass_points;

  for (auto &pair : mPairs){
    QString features1;
    QString features2;
    QString matches;
    std::tie(features1, features2, matches) = pair;

    std::vector<cv::KeyPoint> keyPoints1;
    cv::Mat descriptors1;
    featuresRead(features1, keyPoints1, descriptors1);

    std::vector<cv::KeyPoint> keyPoints2;
    cv::Mat descriptors2;
    featuresRead(features2, keyPoints2, descriptors2);

    std::vector<cv::DMatch> match;
    matchesRead(matches, &match);

    QString idImage1 = QFileInfo(features1).baseName();
    QString idImage2 = QFileInfo(features2).baseName();

    /// ¿Buscar sólo los matches buenos?

    int idx1, idx2;
    for (size_t i = 0; i < match.size(); i++) {
      idx1 = match[i].queryIdx;
      idx2 = match[i].trainIdx;

      //Busqueda de si ya esta añadido ese punto
      bool b_exist_pt1 = false;
      bool b_exist_pt2 = false;
      for (size_t id_pp = 0; id_pp < idx_pass_points.size(); id_pp++) {

        for (size_t j = 0; j < idx_pass_points[id_pp].size(); j++){

          if (idx_pass_points[id_pp][j].first.compare(idImage1) == 0 && idx_pass_points[id_pp][j].second == idx1) {
            b_exist_pt1 = true;
          }

          if (idx_pass_points[id_pp][j].first.compare(idImage2) == 0 && idx_pass_points[id_pp][j].second == idx2){
            b_exist_pt2 = true;
          }

          if (b_exist_pt1 == true && b_exist_pt2 == true){
            break;
          }
        }

        if (b_exist_pt1 == true && b_exist_pt2 == false){
          idx_pass_points[id_pp].push_back(std::make_pair(idImage2,idx2));
          break;
        } else if (b_exist_pt1 == false && b_exist_pt2 == true){
          idx_pass_points[id_pp].push_back(std::make_pair(idImage1,idx1));
          break;
        } else if (b_exist_pt1 == true && b_exist_pt2 == true){
          break;
        }

      }

      if (b_exist_pt1 == false && b_exist_pt2 == false){
        std::vector<std::pair<QString,int>> pass_point;
        pass_point.push_back(std::make_pair(idImage1,idx1));
        pass_point.push_back(std::make_pair(idImage2,idx2));
        idx_pass_points.push_back(pass_point);
      }

    }
  }

  TL_TODO("Llamar a passPointsWrite()")

  std::ofstream ofs(mPassPointsFile.toStdString(), std::ofstream::trunc);
  if (ofs.is_open()){

    for (size_t i = 0; i < idx_pass_points.size(); i++) {

      ofs << i;

      for (size_t j = 0; j < idx_pass_points[i].size(); j++){
        ofs << " " << idx_pass_points[i][j].first.toStdString()
            << " " << idx_pass_points[i][j].second;
      }

      ofs << std::endl;
    }

    emit writeFinished(mPassPointsFile);

    ofs.close();
  }

}

QString PassPointsGroupingProcess::passPointsFile() const
{
  return mPassPointsFile;
}

void PassPointsGroupingProcess::setPassPointsFile(const QString &passPointsFile)
{
  mPassPointsFile = passPointsFile;
}

std::list<std::tuple<QString, QString, QString> > PassPointsGroupingProcess::pairs() const
{
  return mPairs;
}

void PassPointsGroupingProcess::setPairs(const std::list<std::tuple<QString, QString, QString> > &pairs)
{
  mPairs = pairs;
}

} // namespace photomatch
