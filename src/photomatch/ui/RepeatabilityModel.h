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

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel;

class IRepeatabilityModel
  : public IModel
{

  Q_OBJECT

public:

  IRepeatabilityModel(){}
  virtual ~IRepeatabilityModel() {}

  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;
  virtual std::vector<std::tuple<QString, QString, QString>> sessions() const = 0;
  virtual std::vector<std::tuple<QString, QString, QString, float, int>> computeRepeatability(const QString &session/*, const QString &imgLeft, const QString &imgRight*/) const = 0;

};


class RepeatabilityModel
  : public IRepeatabilityModel
{

  Q_OBJECT

public:

  RepeatabilityModel(IProjectModel *projectModel);
  virtual ~RepeatabilityModel() override;

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

  IProjectModel *mProjectModel;
};


} // namespace photomatch

#endif // PHOTOMATCH_REPEATABILITY_MODEL_H
