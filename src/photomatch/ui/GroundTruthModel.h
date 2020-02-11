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


#ifndef PHOTOMATCH_GROUND_TRUTH_MODEL_H
#define PHOTOMATCH_GROUND_TRUTH_MODEL_H

#include <memory>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel;
class GroundTruth;

class IGroundTruthModel
  : public IModel
{

  Q_OBJECT

public:

  IGroundTruthModel(){}
  virtual ~IGroundTruthModel() override {}

  virtual void loadGroundTruth() = 0;
  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;
  virtual std::vector<std::pair<QPointF, QPointF>> groundTruth(const QString &imgName1, const QString &imgName2) const = 0;
  virtual std::pair<QPointF, QPointF> homologus(const QString &imgName1, const QString &imgName2, int pointId) const = 0;

  virtual QTransform transform(const QString &imgName1, const QString &imgName2, std::vector<double> *distances = nullptr, double *emc = nullptr) const = 0;
  virtual void saveGroundTruth() = 0;
  virtual void setGroundTruth(const QString &file) = 0;
  virtual bool existGroundTruth() const = 0;
  virtual QString projectPath() const = 0;
  virtual QPointF findLeftPoint(const QString &image1, const QString &image2, const QPointF &pt) = 0;
  virtual QPointF findRightPoint(const QString &image1, const QString &image2, const QPointF &pt) = 0;
  virtual QPointF findProjectedLeftPoint(const QString &image1, const QString &image2, const QPointF &pt) = 0;
  virtual QPointF findProjectedRightPoint(const QString &image1, const QString &image2, const QPointF &pt) = 0;

public slots:

  virtual void addHomologus(const QString &image1, const QPointF &pt1, const QString &image2, const QPointF &pt2) = 0;
  virtual void deleteHomologus(const QString &image1, const QString &image2, int pointId) = 0;

};


class GroundTruthModel
  : public IGroundTruthModel
{

  Q_OBJECT

public:

  GroundTruthModel(IProjectModel *mProjectModel);
  ~GroundTruthModel() override;

private:

  QPointF findPoint(const QString &image1, const QString &image2, const QPointF &ptImage1);
  QPointF findProjectedPoint(const QString &image1, const QString &image2, const QPointF &ptImage1);

// IModel interface

private:

  void init() override;

// IGroundTruthModel interface

public:

  void loadGroundTruth() override;
  std::vector<QString> images() const override;
  std::vector<QString> imagePairs(const QString &imageName) const override;
  std::vector<std::pair<QPointF, QPointF>> groundTruth(const QString &imgName1, const QString &imgName2) const override;
  std::pair<QPointF, QPointF> homologus(const QString &imgName1, const QString &imgName2, int pointId) const override;

  QTransform transform(const QString &imgName1, const QString &imgName2, std::vector<double> *distances = nullptr, double *emc = nullptr) const override;
  void saveGroundTruth() override;
  void setGroundTruth(const QString &file) override;
  bool existGroundTruth() const override;
  QString projectPath() const override;
  QPointF findLeftPoint(const QString &image1, const QString &image2, const QPointF &pt) override;
  QPointF findRightPoint(const QString &image1, const QString &image2, const QPointF &pt) override;
  QPointF findProjectedLeftPoint(const QString &image1, const QString &image2, const QPointF &pt) override;
  QPointF findProjectedRightPoint(const QString &image1, const QString &image2, const QPointF &pt) override;

public slots:

  void addHomologus(const QString &image1, const QPointF &pt1, const QString &image2, const QPointF &pt2) override;
  void deleteHomologus(const QString &image1, const QString &image2, int pointId) override;

protected:

  IProjectModel *mProjectModel;
  GroundTruth *mGroundTruth;

};


} // namespace photomatch

#endif // PHOTOMATCH_GROUND_TRUTH_MODEL_H
