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

#include "photomatch/ui/FeaturesViewer.h"

namespace photomatch
{

class ProjectModel;

class FeaturesViewerModelImp
  : public FeaturesViewerModel
{

 Q_OBJECT

public:

  FeaturesViewerModelImp(ProjectModel *mProjectModel);
  ~FeaturesViewerModelImp() override;

protected:

  ProjectModel *mProjectModel;

// IModel interface

private:

  void init() override;

// FeaturesViewerModel interface

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
