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


#ifndef PHOTOMATCH_NEW_PROJECT_PRESENTER_H
#define PHOTOMATCH_NEW_PROJECT_PRESENTER_H

#include <memory>

#include <QObject>

#include "photomatch/ui/NewProject.h"

namespace photomatch
{

class NewProjectView;
class ProjectModel;
class HelpDialog;


class NewProjectPresenterImp
  : public NewProjectPresenter
{
  Q_OBJECT

public:

  NewProjectPresenterImp(NewProjectView *view,
                         ProjectModel *model);
  ~NewProjectPresenterImp() override;

// NewProjectPresenter interface

protected slots:

  void saveProject() override;
  void discartProject() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(HelpDialog *help) override;

private:

  void init() override;
  void initSignalAndSlots() override;

private:

  NewProjectView *mView;
  ProjectModel *mProjectModel;
  QString mProjectsDefaultPath;
  HelpDialog *mHelp;

};

} // namespace photomatch


#endif // PHOTOMATCH_NEW_PROJECT_PRESENTER_H
