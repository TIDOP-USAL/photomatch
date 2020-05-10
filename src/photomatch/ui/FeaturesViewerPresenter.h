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


#ifndef PHOTOMATCH_FEATURES_VIEWER_PRESENTER_H
#define PHOTOMATCH_FEATURES_VIEWER_PRESENTER_H

#include <memory>

#include <QObject>

#include "photomatch/ui/FeaturesViewer.h"

namespace photomatch
{

class FeaturesViewerView;
class FeaturesViewerModel;
class SettingsModel;
class HelpDialog;



class FeaturesViewerPresenterImp
  : public FeaturesViewerPresenter
{

  Q_OBJECT

public:

  FeaturesViewerPresenterImp(FeaturesViewerView *view,
                             FeaturesViewerModel *model,
                             SettingsModel *settingsModel);
  ~FeaturesViewerPresenterImp() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(HelpDialog *help) override;

private:

  void init() override;
  void initSignalAndSlots() override;

// FeaturesViewerPresenter interface

public slots:

  void setSession(const QString &session) override;
  void setImageActive(const QString &image) override;
  void openKeypointsFromSession(const QString &session) override;
  void openKeypointsFromSessionAndImage(const QString &session,
                                        const QString &image) override;

protected slots:

  void loadKeypoints(const QString &image) override;

private:

  FeaturesViewerView *mView;
  FeaturesViewerModel *mModel;
  SettingsModel *mSettingsModel;
  HelpDialog *mHelp;

};

} // namespace photomatch

#endif // PHOTOMATCH_FEATURES_VIEWER_PRESENTER_H
