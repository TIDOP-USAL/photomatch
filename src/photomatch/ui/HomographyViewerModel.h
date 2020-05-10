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


#ifndef PHOTOMATCH_HOMOGRAPHY_VIEWER_MODEL_H
#define PHOTOMATCH_HOMOGRAPHY_VIEWER_MODEL_H

#include <memory>

#include "photomatch/ui/HomographyViewer.h"

namespace photomatch
{

class ProjectModel;


class HomographyViewerModelImp
  : public HomographyViewerModel
{

  Q_OBJECT

public:

  HomographyViewerModelImp(ProjectModel *mProjectModel);
  ~HomographyViewerModelImp() override;

// HomographyViewerModel interface

public:

  QString currentSession() const override;
  std::vector<QString> images() const override;
  std::vector<QString> imagePairs(const QString &imageName) const override;
  QImage homography(const QString &imgName1,
                    const QString &imgName2) const override;
  void setUseCuda(bool active) override;

// IModel interface

private:

  void init() override;

protected:

  ProjectModel *mProjectModel;
  bool bUseCuda;
};


} // namespace photomatch

#endif // PHOTOMATCH_HOMOGRAPHY_VIEWER_MODEL_H
