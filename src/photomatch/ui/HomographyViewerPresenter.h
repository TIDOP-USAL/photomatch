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

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IHomographyViewerView;
class IHomographyViewerModel;
class ISettingsModel;
class HelpDialog;


class IHomographyViewerPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IHomographyViewerPresenter() : IPresenter() {}
  virtual ~IHomographyViewerPresenter() {}

protected slots:

  virtual void loadLeftImage(const QString &image) = 0;
  virtual void loadRightImage(const QString &image) = 0;
  virtual void homography(const QString &imageLeft, const QString &imageRight) = 0;

};

class HomographyViewerPresenter
  : public IHomographyViewerPresenter
{

  Q_OBJECT

public:

  HomographyViewerPresenter(IHomographyViewerView *view,
                            IHomographyViewerModel *model,
                            ISettingsModel *settings);
  ~HomographyViewerPresenter() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(std::shared_ptr<HelpDialog> &help) override;

private:

  void init() override;

// IHomographyViewerPresenter interface

protected slots:

  void loadLeftImage(const QString &image) override;
  void loadRightImage(const QString &image) override;
  void homography(const QString &imageLeft, const QString &imageRight) override;

private:

  IHomographyViewerView *mView;
  IHomographyViewerModel *mModel;
  ISettingsModel *mSettingsModel;
  std::shared_ptr<HelpDialog> mHelp;
};

} // namespace photomatch

#endif // PHOTOMATCH_HOMOGRAPHY_VIEWER_PRESENTER_H
