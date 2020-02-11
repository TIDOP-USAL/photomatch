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


#ifndef PHOTOMATCH_FEATURES_VIEWER_MODEL_H
#define PHOTOMATCH_FEATURES_VIEWER_MODEL_H

#include <memory>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel;

class IFeaturesViewerModel
  : public IModel
{

  Q_OBJECT

public:

  IFeaturesViewerModel() {}
  virtual ~IFeaturesViewerModel() = default;

  virtual QString sessionName() const = 0;
  virtual void setSessionName(const QString &session) = 0;
  virtual std::vector<QString> images() const = 0;
  virtual std::vector<std::tuple<QPointF, double, double>> loadKeypoints(const QString &image) = 0;


};

class FeaturesViewerModel
  : public IFeaturesViewerModel
{

 Q_OBJECT

public:

  FeaturesViewerModel(IProjectModel *mProjectModel);
  ~FeaturesViewerModel() override;

protected:

  IProjectModel *mProjectModel;

// IModel interface

private:

  void init() override;

// IFeaturesViewerModel interface

public:

  QString sessionName() const override;
  void setSessionName(const QString &session) override;
  std::vector<QString> images() const override;
  std::vector<std::tuple<QPointF, double, double>> loadKeypoints(const QString &image) override;

protected:

  QString mSession;
};

} // namespace photomatch

#endif // PHOTOMATCH_FEATURES_VIEWER_MODEL_H
