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

#ifndef PHOTOMATCH_DESCRIPTOR_MATCHER_PRESENTER_H
#define PHOTOMATCH_DESCRIPTOR_MATCHER_PRESENTER_H

#include <QObject>

#include "photomatch/ui/DescriptorMatcher.h"

class MultiProcess;

namespace photomatch
{

class DescriptorMatcherView;
class ProjectModel;
class SettingsModel;
class HelpDialog;
class ProgressHandler;


class DescriptorMatcherPresenterImp
  : public DescriptorMatcherPresenter
{

  Q_OBJECT

public:

  DescriptorMatcherPresenterImp(DescriptorMatcherView *view,
                                ProjectModel *projectModel,
                                SettingsModel *settingsModel);
  ~DescriptorMatcherPresenterImp() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(HelpDialog *help) override;

private:

  void init() override;
  void initSignalAndSlots() override;

// DescriptorMatcherPresenter interface

public slots:

  void setProgressHandler(ProgressHandler *progressHandler) override;
  void cancel() override;

private slots:

  void run() override;
  void onError(int code, const QString &msg);
  void onFinished();
  void onMatchCompute(const QString &left,
                      const QString &right,
                      const QString &match);
  void onPassPointsFinished(const QString &file);

protected:

  DescriptorMatcherView *mView;
  ProjectModel *mProjectModel;
  SettingsModel *mSettingsModel;
  HelpDialog *mHelp;
  MultiProcess *mMultiProcess;
  ProgressHandler *mProgressHandler;

};


} // namespace photomatch

#endif // PHOTOMATCH_DESCRIPTOR_MATCHER_PRESENTER_H
