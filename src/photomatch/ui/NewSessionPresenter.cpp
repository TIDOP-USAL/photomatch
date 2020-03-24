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


#include "NewSessionPresenter.h"

#include "photomatch/ui/ProjectModel.h"
#include "photomatch/ui/NewSessionView.h"
#include "photomatch/ui/HelpDialog.h"

namespace photomatch
{

NewSessionPresenterImp::NewSessionPresenterImp(NewSessionView *view, ProjectModel *model)
  : NewSessionPresenter(),
    mView(view),
    mProjectModel(model),
    mHelp(nullptr)
{
  init();

  connect(mView, SIGNAL(sessionNameChange(QString)), this, SLOT(checkSessionName(QString)));

  connect(mView, SIGNAL(accepted()), this, SLOT(saveProject()));
  connect(mView, SIGNAL(rejected()), this, SLOT(discartProject()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));
}

NewSessionPresenterImp::~NewSessionPresenterImp()
{

}

void NewSessionPresenterImp::help()
{
  if (mHelp){
    mHelp->setPage("menus.html#new_session");
    mHelp->show();
  }
}

void NewSessionPresenterImp::open()
{
  mView->exec();
}

void NewSessionPresenterImp::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void NewSessionPresenterImp::init()
{
}

void NewSessionPresenterImp::saveProject()
{
  mProjectModel->addSession(mView->sessionName(), mView->sessionDescription());

  emit sessionCreate(mView->sessionName());

  mView->clear();
}

void NewSessionPresenterImp::discartProject()
{
  mView->clear();
}

void NewSessionPresenterImp::checkSessionName(const QString &name)
{
  std::shared_ptr<Session> session = mProjectModel->findSession(name);
  if (session)
    mView->setExistingName(true);
  else
    mView->setExistingName(false);
}

} // namespace photomatch
