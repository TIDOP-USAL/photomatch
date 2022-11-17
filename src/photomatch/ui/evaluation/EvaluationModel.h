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


#ifndef PHOTOMATCH_EVALUATION_MODEL_H
#define PHOTOMATCH_EVALUATION_MODEL_H

#include <memory>

#include <opencv2/core.hpp>

#include <QPointF>

#include "photomatch/ui/evaluation/Evaluation.h"

namespace photomatch
{

class ProjectModel;

class EvaluationModelImp
  : public EvaluationModel
{

  Q_OBJECT

public:

  explicit EvaluationModelImp(ProjectModel *projectModel);
  virtual ~EvaluationModelImp() override;

private:

  void loadGroundTruth(const QString &groundTruthFile,
                       const QString &imgLeft, 
                       const QString &imgRight, 
                       std::vector<cv::Point2f> &ptsQuery,
                       std::vector<cv::Point2f> &ptsTrain) const;
  cv::Mat computeFundamentalMatrix(std::vector<cv::Point2f> &ptsQuery,
                                   std::vector<cv::Point2f> &ptsTrain) const;
  std::vector<double> computeFundamentalMatrixError(std::vector<cv::Point2f> &ptsQuery,
                                                    std::vector<cv::Point2f> &ptsTrain,
                                                    cv::Mat &fundamentalMatrix) const;
  cv::Mat computeHomography(std::vector<cv::Point2f> &ptsQuery,
                            std::vector<cv::Point2f> &ptsTrain) const;
  std::vector<double> computeHomographyError(std::vector<cv::Point2f> &ptsQuery,
                                             std::vector<cv::Point2f> &ptsTrain,
                                             cv::Mat &homography) const;

// EvaluationModel interface

public:

  std::vector<QString> images() const override;
  std::vector<QString> imagePairs(const QString &imageName) const override;
  std::vector<QString> sessionNames() const override;
  std::vector<std::tuple<QString, QString, QString>> sessions() const override;
  Report computeErrors(const QString &session,
                       const QString &imgLeft,
                       const QString &imgRight,
                       double errorThreshold) const override;
  
  QString adjustMatrix() const override;
  void setAdjustMatrix(const QString &adjustMatrix) override;

// PhotoMatchModel interface

private:

  void init() override;

protected:

  ProjectModel *mProjectModel;
  QString mMatrix;
};



} // namespace photomatch

#endif // PHOTOMATCH_EVALUATION_MODEL_H
