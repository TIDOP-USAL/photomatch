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


#include "GroundTruthModel.h"

#include "photomatch/ui/ProjectModel.h"
#include "photomatch/core/features/groundtruth.h"
#include "photomatch/core/utils.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QImageReader>

namespace photomatch
{

GroundTruthModelImp::GroundTruthModelImp(ProjectModel *mProjectModel)
  : GroundTruthModel(),
    mProjectModel(mProjectModel),
    mGroundTruth(nullptr)
{

}

GroundTruthModelImp::~GroundTruthModelImp()
{
  if (mGroundTruth) {
    delete mGroundTruth;
    mGroundTruth = nullptr;
  }
}

QPointF GroundTruthModelImp::findPoint(const QString &image1,
                                       const QString &image2,
                                       const QPointF &ptImage1)
{
  QTransform trf = this->homography(image1, image2);
  if (trf.isIdentity() == false){
    QPointF trf_point = trf.map(ptImage1);

    /// - se calcula una ventana a partir de pt
    /// - se lee el trozo de imagen correspondiente a la ventana
    QImageReader reader1(mProjectModel->findImageByName(image1)->path());
    double offset_x = ptImage1.x() - round(ptImage1.x());
    double offset_y = ptImage1.y() - round(ptImage1.y());
    QRect rect1(static_cast<int>(ptImage1.x()) - 10, static_cast<int>(ptImage1.y()) - 10, 20, 20);

    reader1.setClipRect(rect1);
    QImage qImage1 = reader1.read();

    /// - se aplica la transformación proyectiva a la imagen y se utiliza como template
    cv::Mat templ1 = qImageToCvMat(qImage1);

    QImageReader reader2(mProjectModel->findImageByName(image2)->path());
    QRect rect2(static_cast<int>(trf_point.x()) - 150, static_cast<int>(trf_point.y()) - 150, 300, 300);
    reader2.setClipRect(rect2);
    QImage qImage2 = reader2.read();
    cv::Mat search_mat = qImageToCvMat(qImage2);

    cv::Mat result(search_mat.rows - templ1.rows + 1, search_mat.cols - templ1.cols + 1, CV_32FC1);

    int mMatchMmethod = cv::TM_CCORR_NORMED;
    cv::matchTemplate(search_mat, templ1, result, mMatchMmethod);
    double minVal; double maxVal;
    cv::Point minLoc;
    cv::Point maxLoc;

    cv::Point matchLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());
    if (mMatchMmethod == cv::TM_SQDIFF || mMatchMmethod == cv::TM_SQDIFF_NORMED) {
      matchLoc = minLoc;
    } else {
      matchLoc = maxLoc;
    }

    if (maxVal > 0.99) {
      return QPointF(matchLoc.x + 10 + rect2.x() + offset_x, matchLoc.y + 10 + rect2.y() + offset_y);
    }

  }

  return QPointF();
}

QPointF GroundTruthModelImp::findProjectedPoint(const QString &image1,
                                                const QString & image2,
                                                const QPointF & ptImage1)
{
  QTransform trf = this->homography(image1, image2);
  if (trf.isIdentity() == false)
    return trf.map(ptImage1);
  else 
    return QPointF();
}

void GroundTruthModelImp::init()
{

}

void GroundTruthModelImp::loadGroundTruth()
{
  if (mGroundTruth == nullptr){
    mGroundTruth = new GroundTruth;
  } else {
    mGroundTruth->clear();
  }

  if (mProjectModel->groundTruth().isEmpty() == false)
    mGroundTruth->read(mProjectModel->groundTruth());
}

std::vector<QString> GroundTruthModelImp::images() const
{
  std::vector<QString> images;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    images.push_back((*it)->path());
  }
  return images;
}

std::vector<QString> GroundTruthModelImp::imagePairs(const QString &imageName) const
{
  std::vector<QString> pairs;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    if (imageName.compare((*it)->name()) != 0){
      pairs.push_back((*it)->path());
    }
  }
  return pairs;
}

std::vector<std::pair<QPointF, QPointF> > GroundTruthModelImp::groundTruth(const QString &imgName1,
                                                                           const QString &imgName2) const
{
  std::vector<std::pair<QPointF,QPointF>> r_ground_truth;

  std::shared_ptr<HomologusPoints> ground_truth = mGroundTruth->findPair(imgName1, imgName2);
  if (ground_truth){
    r_ground_truth = ground_truth->homologusPoints();
  }

  std::shared_ptr<HomologusPoints> ground_truth_inv = mGroundTruth->findPair(imgName2, imgName1);
  if (ground_truth_inv){
    for (auto &homologusPoint : ground_truth_inv->homologusPoints()){
      r_ground_truth.push_back(std::make_pair(homologusPoint.second, homologusPoint.first)); /// .....
    }
  }

  return r_ground_truth;
}

std::pair<QPointF, QPointF> GroundTruthModelImp::homologus(const QString &imgName1,
                                                           const QString &imgName2,
                                                           int pointId) const
{
  std::pair<QPointF, QPointF> homologus;
  if (std::shared_ptr<HomologusPoints> homologus = mGroundTruth->pair(imgName1, imgName2)){
    QPointF ptLeft = homologus->at(static_cast<size_t>(pointId-1)).first;
    QPointF ptRight = homologus->at(static_cast<size_t>(pointId-1)).second;
    return std::make_pair(ptLeft,ptRight);
  }
  return homologus;
}

HomologusPoints GroundTruthModelImp::homologusPoints(const QString &imgName1,
                                                     const QString &imgName2) const
{
  HomologusPoints homologus_points(imgName1, imgName2);
  if (std::shared_ptr<HomologusPoints> ground_truth_direct = mGroundTruth->findPair(imgName1, imgName2)){
    for (auto &homolPoint : ground_truth_direct->homologusPoints()){
      homologus_points.push_back(homolPoint);
    }
  }

  if (std::shared_ptr<HomologusPoints> ground_truth_inverse = mGroundTruth->findPair(imgName2, imgName1)){
    for (auto &homolPoint : ground_truth_inverse->homologusPoints()){
      homologus_points.addPoints(homolPoint.second, homolPoint.first);
    }
  }
  return homologus_points;
}

QTransform GroundTruthModelImp::homography(const QString &imgName1,
                                           const QString &imgName2) const
{
  return homography(homologusPoints(imgName1, imgName2));
}

QTransform GroundTruthModelImp::homography(const HomologusPoints &homologusPoints) const
{
  QTransform trf;
  if (homologusPoints.empty() == false && homologusPoints.size() >= 4) {
  cv::Mat h = homologusPoints.homography();
  if (h.empty() == false){
    trf.setMatrix(h.at<double>(0, 0), h.at<double>(1, 0), h.at<double>(2, 0),
                  h.at<double>(0, 1), h.at<double>(1, 1), h.at<double>(2, 1),
                  h.at<double>(0, 2), h.at<double>(1, 2), h.at<double>(2, 2));
    }
  }
  return trf;
}

cv::Mat GroundTruthModelImp::fundamental(const QString &imgName1,
                                         const QString &imgName2) const
{
  return fundamental(homologusPoints(imgName1, imgName2));
}

cv::Mat GroundTruthModelImp::fundamental(const HomologusPoints &homologusPoints) const
{
  cv::Mat fundamental;
  if (homologusPoints.empty() == false && homologusPoints.size() >= 4) {
    fundamental = homologusPoints.fundamental();
  }
  return fundamental;
}

std::vector<double> GroundTruthModelImp::errorsHomography(const QString &imgName1,
                                                          const QString &imgName2) const
{
  HomologusPoints homologus_points = homologusPoints(imgName1, imgName2);
  std::vector<double> errors(homologus_points.size(), -1.);
  QTransform trf = homography(homologus_points);
  if (!trf.isIdentity()){
    for (size_t i = 0; i < homologus_points.size(); i++){
      QPointF pt1 = homologus_points[i].first;
      QPointF pt2 = homologus_points[i].second;
      if (!pt1.isNull() && !pt2.isNull()){
        QPointF pt1_trf = trf.map(pt1);
        QPointF v = pt1_trf - pt2;
        double aux = QPointF::dotProduct(v, v);
        errors[i] = sqrt(aux);
      }
    }
  }
  return errors;
}

std::vector<double> GroundTruthModelImp::errorsFundamental(const QString &imgName1,
                                                           const QString &imgName2) const
{
  HomologusPoints homologus_points = homologusPoints(imgName1, imgName2);
  std::vector<double> errors(homologus_points.size(), -1.);
  cv::Mat fundamental_matrix = fundamental(homologus_points);
  if (!fundamental_matrix.empty()) {
    std::vector<cv::Vec3f> lines;
    std::vector<cv::Point2f> query_points = homologus_points.queryPoints();
    std::vector<cv::Point2f> train_points = homologus_points.trainPoints();
    cv::computeCorrespondEpilines(query_points, 1, fundamental_matrix, lines);

    for (size_t i = 0; i < train_points.size(); i++){
      errors[i] = static_cast<double>(distancePointLine(train_points[i], lines[i]));
    }
  }
  return errors;
}

void GroundTruthModelImp::saveGroundTruth()
{
  if (mProjectModel->groundTruth().isEmpty()){
    QString gt = mProjectModel->projectFolder();
    gt.append("/GroundTruth.txt");
    mProjectModel->setGroundTruth(gt);
  }
  mGroundTruth->write(mProjectModel->groundTruth());
}

void GroundTruthModelImp::setGroundTruth(const QString &file)
{
  mProjectModel->setGroundTruth(file);
  this->loadGroundTruth();
}

bool GroundTruthModelImp::existGroundTruth() const
{
  return !mProjectModel->groundTruth().isEmpty();
}

QString GroundTruthModelImp::projectPath() const
{
  return mProjectModel->projectFolder();
}

QPointF GroundTruthModelImp::findLeftPoint(const QString &image1,
                                           const QString &image2,
                                           const QPointF &pt)
{
  return findPoint(image2, image1, pt);
}

QPointF GroundTruthModelImp::findRightPoint(const QString &image1,
                                            const QString &image2,
                                            const QPointF &pt)
{
  return findPoint(image1, image2, pt);
}

QPointF GroundTruthModelImp::findProjectedLeftPoint(const QString &image1,
                                                    const QString &image2,
                                                    const QPointF &pt)
{
  return findProjectedPoint(image2, image1, pt);
}

QPointF GroundTruthModelImp::findProjectedRightPoint(const QString &image1,
                                                     const QString &image2,
                                                     const QPointF &pt)
{
  return findProjectedPoint(image1, image2, pt);
}

void GroundTruthModelImp::addHomologus(const QString &image1,
                                       const QPointF &pt1,
                                       const QString &image2,
                                       const QPointF &pt2)
{
  if (std::shared_ptr<HomologusPoints> homologus = mGroundTruth->pair(image1, image2)){
    homologus->addPoints(pt1, pt2);
  }
}

void GroundTruthModelImp::deleteHomologus(const QString &image1,
                                          const QString &image2,
                                          int pointId)
{
  if (std::shared_ptr<HomologusPoints> homologus = mGroundTruth->pair(image1, image2)){
    /// Se marca como nulo
    homologus->at(static_cast<size_t>(pointId-1)).first = QPoint();
    homologus->at(static_cast<size_t>(pointId-1)).second = QPoint();
  }
}




} // namespace photomatch
