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


#ifndef PHOTOMATCH_HOMOGRAPHY_VIEWER_PRESENTER_H
#define PHOTOMATCH_HOMOGRAPHY_VIEWER_PRESENTER_H

#include <memory>

#include <QObject>

#include "photomatch/ui/HomographyViewer.h"

namespace photomatch
{

class HomographyViewerView;
class HomographyViewerModel;
class SettingsModel;
class HelpDialog;


class HomographyViewerPresenterImp
  : public HomographyViewerPresenter
{

  Q_OBJECT

public:

  HomographyViewerPresenterImp(HomographyViewerView *view,
                            HomographyViewerModel *model,
                            SettingsModel *settings);
  ~HomographyViewerPresenterImp() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(HelpDialog *help) override;

private:

  void init() override;

// IHomographyViewerPresenter interface

protected slots:

  void loadLeftImage(const QString &image) override;
  void loadRightImage(const QString &image) override;
  void homography(const QString &imageLeft, const QString &imageRight) override;

private:

  HomographyViewerView *mView;
  HomographyViewerModel *mModel;
  SettingsModel *mSettingsModel;
  HelpDialog *mHelp;
};

} // namespace photomatch

#endif // PHOTOMATCH_HOMOGRAPHY_VIEWER_PRESENTER_H
