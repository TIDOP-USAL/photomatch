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


#include "MultiViewPresenter.h"

#include "photomatch/ui/multiview/MultiViewModel.h"
#include "photomatch/ui/multiview/MultiViewView.h"
#include "photomatch/ui/HelpDialog.h"

namespace photomatch
{

MultiViewMatchingAssessmentPresenterImp::MultiViewMatchingAssessmentPresenterImp(MultiviewMatchingAssessmentView *view,
                                                                                 MultiViewMatchingAssessmentModel *model)
  : MultiViewMatchingAssessmentPresenter(),
    mView(view),
    mModel(model),
    mHelp(nullptr)
{
  this->init();
  this->initSignalAndSlots();
}

void MultiViewMatchingAssessmentPresenterImp::onIdChange(int id)
{
  mView->setImages(mModel->images(static_cast<size_t>(id)));
}

void MultiViewMatchingAssessmentPresenterImp::setSession(const QString &session)
{
  mModel->setSessionName(session);
  mView->clear();
  mView->setSessionName(mModel->sessionName());
}

void MultiViewMatchingAssessmentPresenterImp::help()
{
  if (mHelp){
    mHelp->setPage("index.html");
    mHelp->show();
  }
}

void MultiViewMatchingAssessmentPresenterImp::open()
{
  mView->clear();

  /// Se carga el fichero de puntos de paso.
  mModel->loadPassPoints();

  //mView->setPassPointIds(mModel->passPointIds());
  for (auto &id_size : mModel->passPointIdsAndSize()){
    mView->addPassPointIdsAndNImages(id_size.first, id_size.second);
  }

  mView->show();
}

void MultiViewMatchingAssessmentPresenterImp::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void MultiViewMatchingAssessmentPresenterImp::init()
{
}

void MultiViewMatchingAssessmentPresenterImp::initSignalAndSlots()
{
  connect(mView, SIGNAL(idChange(int)),  this, SLOT(onIdChange(int)));
}

} // namespace photomatch


