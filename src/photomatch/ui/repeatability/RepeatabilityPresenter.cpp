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


#include "RepeatabilityPresenter.h"

#include "photomatch/ui/repeatability/RepeatabilityModel.h"
#include "photomatch/ui/repeatability/RepeatabilityView.h"
#include "photomatch/ui/HelpDialog.h"

#include <QFileInfo>

namespace photomatch
{

RepeatabilityPresenterImp::RepeatabilityPresenterImp(RepeatabilityView *view,
                                               RepeatabilityModel *model)
  : RepeatabilityPresenter(),
    mView(view),
    mModel(model),
    mHelp(nullptr)
{
  this->init();
  this->initSignalAndSlots();
}

void RepeatabilityPresenterImp::selectSession(const QString &session)
{
  mView->setRepeatability(mModel->computeRepeatability(session));
}

//void RepeatabilityPresenter::loadLeftImage(const QString &image)
//{
//  mView->setLeftImage(image);
//  std::vector<QString> imagesRight = mModel->imagePairs(QFileInfo(image).baseName());
//  if (imagesRight.empty() == false){
//    mView->setRightImageList(imagesRight);
//    mView->setRightImage(imagesRight[0]);
//  }
//}
//
//void RepeatabilityPresenter::loadRightImage(const QString &image)
//{
//  mView->setRightImage(image);
//}

void RepeatabilityPresenterImp::help()
{
  if (mHelp){
    mHelp->setPage("index.html");
    mHelp->show();
  }
}

void RepeatabilityPresenterImp::open()
{
  mView->clear();

  std::vector<std::tuple<QString,QString,QString>> sessions = mModel->sessions();
  for (auto &session : sessions){
    QString sessionName;
    QString sessionDetector;
    QString sessionDescriptor;
    std::tie(sessionName, sessionDetector, sessionDescriptor) = session;
    mView->addSession(sessionName, sessionDetector, sessionDescriptor);
  }

  this->selectSession(std::get<0>(sessions[0]));

  mView->show();
}

void RepeatabilityPresenterImp::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void RepeatabilityPresenterImp::init()
{
}

void RepeatabilityPresenterImp::initSignalAndSlots()
{
  connect(mView, SIGNAL(selectSession(QString)), this, SLOT(selectSession(QString)));

  connect(mView, SIGNAL(help()),     this, SLOT(help()));
}

} // namespace photomatch
