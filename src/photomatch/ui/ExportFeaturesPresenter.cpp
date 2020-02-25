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


#include "ExportFeaturesPresenter.h"

#include "photomatch/ui/ExportFeaturesModel.h"
#include "photomatch/ui/ExportFeaturesView.h"
#include "photomatch/ui/HelpDialog.h"

namespace photomatch
{

ExportFeaturesPresenter::ExportFeaturesPresenter(IExportFeaturesView *view,
                                                 IExportFeaturesModel *model)
  : IExportFeaturesPresenter(),
    mView(view),
    mModel(model),
    mHelp(nullptr)
{
  init();

  connect(mView, SIGNAL(sessionChange(QString)),   this, SLOT(sessionChange(QString)));
  connect(mView, SIGNAL(accepted()),               this, SLOT(save()));
  connect(mView, SIGNAL(help()),                   this, SLOT(help()));
}

ExportFeaturesPresenter::~ExportFeaturesPresenter()
{

}

void ExportFeaturesPresenter::help()
{
  if (mHelp){
    mHelp->setPage("menus.html#export_keypoints");
    mHelp->show();
  }
}

void ExportFeaturesPresenter::open()
{
  mView->clear();

  mView->setSessions(mModel->sessions());
  mView->setSessionToExport(mModel->activeSessionName());
  mView->setFormats(mModel->formats());
  mView->setImageFiles(mModel->features(mModel->activeSessionName()));

  mView->exec();
}

void ExportFeaturesPresenter::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void ExportFeaturesPresenter::init()
{
}

void ExportFeaturesPresenter::save()
{
  mModel->exportFeatures(mView->session(),
                         mView->exportFiles(),
                         mView->exportPath(),
                         mView->format());
}

void ExportFeaturesPresenter::sessionChange(const QString &session)
{
  mView->setSessionToExport(session);
  mView->setFormats(mModel->formats());
  mView->setImageFiles(mModel->features(session));
}

} // namespace photomatch
