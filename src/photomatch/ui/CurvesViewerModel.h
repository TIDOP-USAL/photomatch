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


#ifndef PHOTOMATCH_CURVES_VIEWER_MODEL_H
#define PHOTOMATCH_CURVES_VIEWER_MODEL_H

#include <memory>

#include <QPointF>

#include "photomatch/ui/CurvesViewer.h"

namespace photomatch
{

class ProjectModel;


class CurvesViewerModelImp
  : public CurvesViewerModel
{

  Q_OBJECT

public:

  explicit CurvesViewerModelImp(ProjectModel *projectModel);
  virtual ~CurvesViewerModelImp() override;

// ICurvesViewerModel interface

public:

  std::vector<QString> images() const override;
  std::vector<QString> imagePairs(const QString &imageName) const override;
  std::vector<QString> sessionNames() const override;
  std::vector<std::tuple<QString, QString, QString>> sessions() const override;
  std::vector<std::pair<double, int>> classifiedMatches(const QString &session,
                                                        const QString &imgLeft,
                                                        const QString &imgRight) const override;
  QString adjustMatrix() const override;
  void setAdjustMatrix(const QString &adjustMatrix) override;

// IModel interface

private:

  void init() override;

protected:

  ProjectModel *mProjectModel;
  QString mMatrix;
};




class ROCCurvesViewerModel
  : public CurvesViewerModelImp
{
  Q_OBJECT

public:

  explicit ROCCurvesViewerModel(ProjectModel *projectModel);
  ~ROCCurvesViewerModel() override;

// ICurvesViewerModel interface

public:

  std::vector<QPointF> computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight) const override;
  double computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight, std::vector<QPointF> &curve) const override;

};



class PRCurvesViewerModel
  : public CurvesViewerModelImp
{
  Q_OBJECT

public:

  explicit PRCurvesViewerModel(ProjectModel *projectModel);
  ~PRCurvesViewerModel() override;

// ICurvesViewerModel interface

public:

  std::vector<QPointF> computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight) const override;
  double computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight, std::vector<QPointF> &curve) const override;

};


class DETCurvesViewerModel
  : public CurvesViewerModelImp
{
  Q_OBJECT

public:

  explicit DETCurvesViewerModel(ProjectModel *projectModel);
  ~DETCurvesViewerModel() override;

// ICurvesViewerModel interface

public:

  std::vector<QPointF> computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight) const override;
  double computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight, std::vector<QPointF> &curve) const override;
};



} // namespace photomatch

#endif // PHOTOMATCH_CURVES_VIEWER_MODEL_H
