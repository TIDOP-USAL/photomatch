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


#include "ExportMatchesPresenter.h"

#include "photomatch/ui/ExportMatchesModel.h"
#include "photomatch/ui/ExportMatchesView.h"
#include "photomatch/ui/HelpDialog.h"

#include <tidop/core/messages.h>

#include <QFileDialog>
#include <QStandardPaths>

namespace photomatch
{

ExportMatchesPresenterImp::ExportMatchesPresenterImp(ExportMatchesView *view,
                                                     ExportMatchesModel *model)
  : ExportMatchesPresenter(),
    mView(view),
    mModel(model),
    mHelp(nullptr)
{
  this->init();
  this->initSignalAndSlots();
}

ExportMatchesPresenterImp::~ExportMatchesPresenterImp()
{

}

void ExportMatchesPresenterImp::help()
{
  if (mHelp){
    mHelp->setPage("menus.html#export_matches");
    mHelp->showMaximized();
  }
}

void ExportMatchesPresenterImp::open()
{
  mView->clear();

  mView->setSessions(mModel->sessions());
  mView->setActiveSession(mModel->sessionName());

  mView->exec();
}

void ExportMatchesPresenterImp::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void ExportMatchesPresenterImp::init()
{
}

void ExportMatchesPresenterImp::initSignalAndSlots()
{
  connect(mView, SIGNAL(sessionChange(QString)),   this, SLOT(sessionChange(QString)));
  connect(mView, SIGNAL(accepted()),               this, SLOT(save()));
  connect(mView, SIGNAL(help()),                   this, SLOT(help()));
}

void ExportMatchesPresenterImp::save()
{

  QString selectedFilter;
  QString pathName = QFileDialog::getSaveFileName(nullptr,
      tr("Export matches"),
      QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
      tr("ORIMA (*.txt);;BINGO (*.txt);;All Files (*)"),
      &selectedFilter);

  if (!pathName.isEmpty()) {

    QString format;
    if (selectedFilter.compare("ORIMA (*.txt)") == 0){
      format = "ORIMA";
    } else if (selectedFilter.compare("BINGO (*.txt)") == 0){
      format = "BINGO";
    } else {
      msgError("Unsupported format");
    }
    mModel->exportMatches(pathName, format);
  }

}

void ExportMatchesPresenterImp::sessionChange(const QString &session)
{
  mModel->setSessionName(session);
  mView->setActiveSession(session);
}

} // namespace photomatch
