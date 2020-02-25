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

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IFeaturesViewerView;
class IFeaturesViewerModel;
class ISettingsModel;
class HelpDialog;


class IFeaturesViewerPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IFeaturesViewerPresenter() {}
  virtual ~IFeaturesViewerPresenter() {}

public slots:

  virtual void setSession(const QString &session) = 0;
  virtual void setImageActive(const QString &image) = 0;
  virtual void openImageFromSession(const QString &session, const QString &image) = 0;

protected slots:

  virtual void loadKeypoints(const QString &image) = 0;

};

class FeaturesViewerPresenter
  : public IFeaturesViewerPresenter
{

  Q_OBJECT

public:

  FeaturesViewerPresenter(IFeaturesViewerView *view,
                          IFeaturesViewerModel *model,
                          ISettingsModel *settingsModel);
  ~FeaturesViewerPresenter() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(HelpDialog *help) override;

private:

  void init() override;

// IFeaturesViewerPresenter interface

public slots:

  void setSession(const QString &session) override;
  void setImageActive(const QString &image) override;
  void openImageFromSession(const QString &session, const QString &image) override;

protected slots:

  void loadKeypoints(const QString &image) override;

private:

  IFeaturesViewerView *mView;
  IFeaturesViewerModel *mModel;
  ISettingsModel *mSettingsModel;
  HelpDialog *mHelp;
};

} // namespace photomatch

#endif // PHOTOMATCH_FEATURES_VIEWER_PRESENTER_H
