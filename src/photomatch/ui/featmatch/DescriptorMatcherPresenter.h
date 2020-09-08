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

#include "photomatch/ui/featmatch/DescriptorMatcher.h"

namespace photomatch
{

class DescriptorMatcherView;
class ProjectModel;
class SettingsModel;
class HelpDialog;
class DescriptorMatcher;
class MatchingAlgorithm;

class DescriptorMatcherPresenterImp
  : public DescriptorMatcherPresenter
{

  Q_OBJECT

public:

  DescriptorMatcherPresenterImp(DescriptorMatcherView *view,
                                ProjectModel *projectModel,
                                SettingsModel *settingsModel);
  ~DescriptorMatcherPresenterImp() override;

private slots:

  void onMatchCompute(const QString &left,
                      const QString &right,
                      const QString &match);
  void onPassPointsFinished(const QString &file);

private:

  std::shared_ptr<DescriptorMatcher> makeDescriptorMatcher(const QString &matchingMethod);
  std::shared_ptr<MatchingAlgorithm> makeMatchingAlgorithm(const QString &matchingStrategy,
                                                           std::shared_ptr<DescriptorMatcher> &descriptorMatcher);

// ProcessPresenter interface

protected slots:

  void onError(int code, const QString &msg) override;
  void onFinished() override;
  void createProcess() override;

public slots:

  void cancel() override;

// PhotoMatchPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(HelpDialog *help) override;

private:

  void init() override;
  void initSignalAndSlots() override;

protected:

  DescriptorMatcherView *mView;
  ProjectModel *mProjectModel;
  SettingsModel *mSettingsModel;
  HelpDialog *mHelp;

};


} // namespace photomatch

#endif // PHOTOMATCH_DESCRIPTOR_MATCHER_PRESENTER_H
