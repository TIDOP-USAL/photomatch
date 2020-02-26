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

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel;

class ICurvesViewerModel
  : public IModel
{

  Q_OBJECT

public:

  ICurvesViewerModel(){}
  virtual ~ICurvesViewerModel() {}

  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;
  virtual std::vector<QString> sessionNames() const = 0;
  virtual std::vector<std::tuple<QString, QString, QString>> sessions() const = 0;
  virtual std::vector<QPointF> computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight) const = 0;
  virtual double computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight, std::vector<QPointF> &curve) const = 0;

};


class CurvesViewerModel
  : public ICurvesViewerModel
{

  Q_OBJECT

public:

  CurvesViewerModel(IProjectModel *projectModel);
  virtual ~CurvesViewerModel() override;

// ICurvesViewerModel interface

public:

  std::vector<QString> images() const override;
  std::vector<QString> imagePairs(const QString &imageName) const override;
  std::vector<QString> sessionNames() const override;
  std::vector<std::tuple<QString, QString, QString>> sessions() const override;

// IModel interface

private:

  void init() override;

protected:

  IProjectModel *mProjectModel;
};




class ROCCurvesViewerModel
  : public CurvesViewerModel
{
  Q_OBJECT

public:

  ROCCurvesViewerModel(IProjectModel *projectModel);
  ~ROCCurvesViewerModel() override;

// ICurvesViewerModel interface

public:

  std::vector<QPointF> computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight) const override;
  double computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight, std::vector<QPointF> &curve) const override;

};



class PRCurvesViewerModel
  : public CurvesViewerModel
{
  Q_OBJECT

public:

  PRCurvesViewerModel(IProjectModel *projectModel);
  ~PRCurvesViewerModel() override;

// ICurvesViewerModel interface

public:

  std::vector<QPointF> computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight) const override;
  double computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight, std::vector<QPointF> &curve) const override;

};


class DETCurvesViewerModel
  : public CurvesViewerModel
{
  Q_OBJECT

public:

  DETCurvesViewerModel(IProjectModel *projectModel);
  ~DETCurvesViewerModel() override;

// ICurvesViewerModel interface

public:

  std::vector<QPointF> computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight) const override;
  double computeCurve(const QString &session, const QString &imgLeft, const QString &imgRight, std::vector<QPointF> &curve) const override;
};



} // namespace photomatch

#endif // PHOTOMATCH_CURVES_VIEWER_MODEL_H
