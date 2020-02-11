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


#ifndef PHOTOMATCH_MULTIVIEW_MODEL_H
#define PHOTOMATCH_MULTIVIEW_MODEL_H

#include <memory>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel;

class IMultiViewModel
  : public IModel
{

  Q_OBJECT

public:

  IMultiViewModel(){}
  virtual ~IMultiViewModel() override {}

  virtual QString sessionName() const = 0;
  virtual void setSessionName(const QString &session) = 0;
  virtual void loadPassPoints() = 0;
  virtual std::vector<size_t> passPointIds() const = 0;
  virtual std::vector<std::pair<size_t, size_t>> passPointIdsAndSize() const = 0;
  virtual std::vector<std::pair<QString, QPointF>> images(size_t passPointId) const = 0;
};



class MultiViewModel
  : public IMultiViewModel
{

  Q_OBJECT

public:

  MultiViewModel(IProjectModel *mProjectModel);
  ~MultiViewModel() override;

// IMatchViewerModel interface

public:

  QString sessionName() const override;
  void setSessionName(const QString &session) override;
  void loadPassPoints() override;
  std::vector<size_t> passPointIds() const override;
  std::vector<std::pair<size_t, size_t>> passPointIdsAndSize() const override;
  std::vector<std::pair<QString, QPointF>> images(size_t passPointId) const override;

// IModel interface

private:

  void init() override;

protected:

  IProjectModel *mProjectModel;
  std::vector<std::vector<std::pair<QString,int>>> mPassPoints;
  QString mSession;

};

} // namespace photomatch

#endif // PHOTOMATCH_MULTIVIEW_MODEL_H
