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


#ifndef PHOTOMATCH_REPEATABILITY_MODEL_H
#define PHOTOMATCH_REPEATABILITY_MODEL_H

#include <memory>

#include <QPointF>

#include "photomatch/ui/Repeatability.h"

namespace photomatch
{

class ProjectModel;


class RepeatabilityModelImp
  : public RepeatabilityModel
{

  Q_OBJECT

public:

  RepeatabilityModelImp(ProjectModel *projectModel);
  virtual ~RepeatabilityModelImp() override;

// IRepeteabilityModel interface

public:

  std::vector<QString> images() const override;
  std::vector<QString> imagePairs(const QString &imageName) const override;
  std::vector<std::tuple<QString, QString, QString>> sessions() const override;
  std::vector<std::tuple<QString, QString, QString, float, int>> computeRepeatability(const QString &session/*, const QString &imgLeft, const QString &imgRight*/) const override;

// IModel interface

private:

  void init() override;

protected:

  ProjectModel *mProjectModel;
};


} // namespace photomatch

#endif // PHOTOMATCH_REPEATABILITY_MODEL_H
