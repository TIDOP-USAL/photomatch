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


#ifndef PHOTOMATCH_MATCH_VIEWER_MODEL_H
#define PHOTOMATCH_MATCH_VIEWER_MODEL_H

#include <memory>

#include "photomatch/ui/matchviewer/MatchViewer.h"

namespace photomatch
{

class ProjectModel;


class MatchViewerModelImp
  : public MatchViewerModel
{

  Q_OBJECT

public:

  MatchViewerModelImp(ProjectModel *mProjectModel);


// PhotoMatchModel interface

private:

  void init() override;

// IMatchViewerModel interface

public:

  QString sessionName() const override;
  void setSessionName(const QString &session) override;
  std::vector<QString> images() const override;
  std::vector<QString> imagePairs(const QString &imageName) const override;
  std::vector<std::tuple<size_t,size_t,QPointF,size_t,QPointF,float> > loadMatches(const QString &imgName1,
                                                                                   const QString &imgName2) const override;
  void deleteMatch(const QString &imgName1,
                   const QString &imgName2,
                   int query_id,
                   int train_id) override;
  void loadPassPoints() override;

protected:

  ProjectModel *mProjectModel;
  std::vector<std::vector<std::pair<QString,int>>> mPassPoints;
  QString mSession;

};

} // namespace photomatch

#endif // PHOTOMATCH_MATCH_VIEWER_MODEL_H
