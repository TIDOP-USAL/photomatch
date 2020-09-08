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

#include "photomatch/ui/exportfeat/ExportFeaturesModel.h"
#include "photomatch/ui/exportfeat/ExportFeaturesView.h"
#include "photomatch/ui/HelpDialog.h"

namespace photomatch
{

ExportFeaturesPresenterImp::ExportFeaturesPresenterImp(ExportFeaturesView *view,
                                                       ExportFeaturesModel *model)
  : ExportFeaturesPresenter(),
    mView(view),
    mModel(model),
    mHelp(nullptr)
{
  this->init();
  this->initSignalAndSlots();
}

ExportFeaturesPresenterImp::~ExportFeaturesPresenterImp()
{

}

void ExportFeaturesPresenterImp::help()
{
  if (mHelp){
    mHelp->setPage("menus.html#export_keypoints");
    mHelp->show();
  }
}

void ExportFeaturesPresenterImp::open()
{
  mView->clear();

  mView->setSessions(mModel->sessions());
  mView->setSessionToExport(mModel->activeSessionName());
  mView->setFormats(mModel->formats());
  mView->setImageFiles(mModel->features(mModel->activeSessionName()));

  mView->exec();
}

void ExportFeaturesPresenterImp::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void ExportFeaturesPresenterImp::init()
{
}

void ExportFeaturesPresenterImp::initSignalAndSlots()
{
  connect(mView, &ExportFeaturesView::sessionChange,  this, &ExportFeaturesPresenterImp::sessionChange);
  connect(mView, &QDialog::accepted,                  this, &ExportFeaturesPresenterImp::save);
  connect(mView, &PhotoMatchDialogView::help,         this, &ExportFeaturesPresenterImp::help);
}

void ExportFeaturesPresenterImp::save()
{
  mModel->exportFeatures(mView->session(),
                         mView->exportFiles(),
                         mView->exportPath(),
                         mView->format());
}

void ExportFeaturesPresenterImp::sessionChange(const QString &session)
{
  mView->setSessionToExport(session);
  mView->setFormats(mModel->formats());
  mView->setImageFiles(mModel->features(session));
}

} // namespace photomatch
