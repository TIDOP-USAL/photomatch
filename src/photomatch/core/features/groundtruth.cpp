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

#include "groundtruth.h"

#include <fstream>

#include <QStringList>

#include <tidop/core/messages.h>

namespace photomatch
{

HomologusPoints::HomologusPoints(const QString &idImg1,
                                 const QString &idImg2)
  : mIdImage1(idImg1),
    mIdImage2(idImg2),
    mHomologusPoints(0)
{}

void HomologusPoints::addPoints(const QPointF &pt1, 
                                const QPointF &pt2)
{
  mHomologusPoints.emplace_back(pt1, pt2);
}

HomologusPoints::iterator HomologusPoints::begin()
{
  return mHomologusPoints.begin();
}

HomologusPoints::const_iterator HomologusPoints::begin() const
{
  return mHomologusPoints.cbegin();
}

HomologusPoints::iterator HomologusPoints::end()
{
  return mHomologusPoints.end();
}

HomologusPoints::const_iterator HomologusPoints::end() const
{
  return mHomologusPoints.cend();
}

void HomologusPoints::push_back(const std::pair<QPointF, QPointF> &points)
{
  mHomologusPoints.push_back(points);
}

HomologusPoints::const_reference HomologusPoints::at(HomologusPoints::size_type position) const
{
  return mHomologusPoints.at(position);
}

HomologusPoints::reference HomologusPoints::at(HomologusPoints::size_type position)
{
  return mHomologusPoints.at(position);
}

void HomologusPoints::clear()
{
  mHomologusPoints.clear();
}

bool HomologusPoints::empty() const
{
  return mHomologusPoints.empty();
}

void HomologusPoints::reserve(HomologusPoints::size_type size)
{
  mHomologusPoints.reserve(size);
}

void HomologusPoints::resize(HomologusPoints::size_type count)
{
  mHomologusPoints.resize(count);
}

void HomologusPoints::resize(size_type count, 
                             const std::pair<QPointF, QPointF> &points)
{
  mHomologusPoints.resize(count, points);
}

HomologusPoints::size_type HomologusPoints::size() const
{
  return mHomologusPoints.size();
}

HomologusPoints::const_reference HomologusPoints::operator[](HomologusPoints::size_type position) const
{
  return mHomologusPoints[position];
}

HomologusPoints::reference HomologusPoints::operator[](HomologusPoints::size_type position)
{
  return mHomologusPoints[position];
}

HomologusPoints::iterator HomologusPoints::erase(HomologusPoints::const_iterator first, 
                                                 HomologusPoints::const_iterator last)
{
  return mHomologusPoints.erase(first, last);
}

QString HomologusPoints::idImg1() const
{
  return mIdImage1;
}

QString HomologusPoints::idImg2() const
{
  return mIdImage2;
}

std::vector<std::pair<QPointF, QPointF>> HomologusPoints::homologusPoints() const
{
  return mHomologusPoints;
}

cv::Mat HomologusPoints::homography() const
{
  cv::Mat homography_matrix;
  try {
    homography_matrix = cv::findHomography(queryPoints(), trainPoints());
  } catch (cv::Exception &e){
    msgError(e.what());
  }
  return homography_matrix;
}

cv::Mat HomologusPoints::fundamental() const
{
  cv::Mat fundamental_matrix;
  try {
    fundamental_matrix = cv::findFundamentalMat(queryPoints(), trainPoints());
  } catch (cv::Exception &e){
    msgError(e.what());
  }
  return fundamental_matrix;
}

std::vector<cv::Point2f> HomologusPoints::queryPoints() const
{
  std::vector<cv::Point2f> pts_query;

  for (const auto &homologusPoint : mHomologusPoints){
    if (!homologusPoint.first.isNull() && !homologusPoint.second.isNull()){
      pts_query.emplace_back(static_cast<float>(homologusPoint.first.x()),
                             static_cast<float>(homologusPoint.first.y()));
    }
  }

  return pts_query;
}

std::vector<cv::Point2f> HomologusPoints::trainPoints() const
{
  std::vector<cv::Point2f> pts_train;

  for (const auto &homologusPoint : mHomologusPoints){
    if (!homologusPoint.first.isNull() && !homologusPoint.second.isNull()){
      pts_train.emplace_back(static_cast<float>(homologusPoint.second.x()),
                             static_cast<float>(homologusPoint.second.y()));
    }
  }

  return pts_train;
}

//std::vector<std::pair<QPointF, QPointF> > HomologusPoints::invert() const
//{
//  for (size_t i = 0; i < mHomologusPoints.size(); i++){

//  }
//}





GroundTruth::GroundTruth()
  : mGroundTruthFile()
{

}

GroundTruth::GroundTruth(const QString &gtFile)
  : mGroundTruthFile(gtFile)
{
  read(gtFile);
}

void GroundTruth::read(const QString &gtFile)
{
  mGroundTruthFile = gtFile;

  std::ifstream ifs(gtFile.toStdString(), std::ifstream::in);

  std::string line;
  if (ifs.is_open()){

    while (std::getline(ifs, line)) {

      QStringList list = QString(line.c_str()).split(";");
      if (list.size() == 6){
        std::shared_ptr<HomologusPoints> homologus = this->findPair(list[0], list[1]);
        QPointF pt_query;
        QPointF pt_train;
        if (homologus != nullptr){
          pt_query = QPointF(list[2].toDouble(), list[3].toDouble());
          pt_train = QPointF(list[4].toDouble(), list[5].toDouble());
        } else {
          homologus = this->findPair(list[1], list[0]);
          if (homologus != nullptr){
            pt_query = QPointF(list[4].toDouble(), list[5].toDouble());
            pt_train = QPointF(list[2].toDouble(), list[3].toDouble());
            homologus->addPoints(pt_query, pt_train);
          } else {
            homologus = std::make_shared<HomologusPoints>(list[0], list[1]);
            mHomologusPoints.push_back(homologus);
            pt_query = QPointF(list[2].toDouble(), list[3].toDouble());
            pt_train = QPointF(list[4].toDouble(), list[5].toDouble());
          }
        }

        homologus->addPoints(pt_query, pt_train);
      }

    }

    ifs.close();

  }
}

void GroundTruth::write(const QString &gtFile)
{
  std::ofstream ofs(gtFile.toStdString(), std::ofstream::trunc);
  if (ofs.is_open()){

    for (auto &homologusPoints : mHomologusPoints){
      std::string idImg1 = homologusPoints->idImg1().toStdString();
      std::string idImg2 = homologusPoints->idImg2().toStdString();
      for (auto points : *homologusPoints){
        if (!points.first.isNull() &&
            !points.second.isNull()){
          ofs << idImg1 << ";" << idImg2 << ";" <<
                 points.first.x() << ";" << points.first.y() << ";" <<
                 points.second.x() << ";" << points.second.y() << std::endl;
        }
      }
    }

    ofs.close();
  }
}

std::shared_ptr<HomologusPoints> GroundTruth::findPair(const QString &idImg1, 
                                                       const QString &idImg2)
{
  for (auto &homologusPoints : mHomologusPoints) {
    if (homologusPoints->idImg1().compare(idImg1) == 0 &&
        homologusPoints->idImg2().compare(idImg2) == 0){
      return homologusPoints;
    }
  }

  return nullptr;
}

std::shared_ptr<HomologusPoints> GroundTruth::pair(const QString &idImg1, 
                                                   const QString &idImg2)
{
  std::shared_ptr<HomologusPoints> homologus = this->findPair(idImg1, idImg2);
  if (homologus == nullptr){
    homologus = std::make_shared<HomologusPoints>(idImg1, idImg2);
    mHomologusPoints.push_back(homologus);
  }
  return homologus;
}

void GroundTruth::clear()
{
  mGroundTruthFile.clear();
  mHomologusPoints.clear();
}

} // namespace photomatch
