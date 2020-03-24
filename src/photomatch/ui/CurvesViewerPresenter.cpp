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


#include "CurvesViewerPresenter.h"

#include "photomatch/ui/CurvesViewerModel.h"
#include "photomatch/ui/CurvesViewerView.h"
#include "photomatch/ui/HelpDialog.h"

#include <QFileInfo>

namespace photomatch
{

CurvesViewerPresenterImp::CurvesViewerPresenterImp(CurvesViewerView *view,
                                             CurvesViewerModel *model)
  : CurvesViewerPresenter(),
    mView(view),
    mModel(model),
    mHelp(nullptr)
{
  init();

  connect(mView, SIGNAL(leftImageChange(QString)),           this, SLOT(loadLeftImage(QString)));
  connect(mView, SIGNAL(rightImageChange(QString)),          this, SLOT(loadRightImage(QString)));
  connect(mView, SIGNAL(activeSession(QString)),             this, SLOT(activeSession(QString)));
  connect(mView, SIGNAL(disableSession(QString)),            this, SLOT(disableSession(QString)));
  connect(mView, SIGNAL(help()),                             this, SLOT(help()));
}

void CurvesViewerPresenterImp::loadLeftImage(const QString &image)
{
  std::vector<QString> imagesRight = mModel->imagePairs(QFileInfo(image).baseName());
  if (imagesRight.empty() == false){
    mView->setRightImageList(imagesRight);
    mView->setRightImage(imagesRight[0]);
    std::vector<QString> session_names = mModel->sessionNames();
    for (auto &session_name : session_names){
      if (mView->isSessionActive(session_name)){
        this->deleteCurve(session_name);
        this->computeCurve(session_name, image, mView->rightImage());
      }
    }
  }
}

void CurvesViewerPresenterImp::loadRightImage(const QString &image)
{
  std::vector<QString> session_names = mModel->sessionNames();
  for (auto &session_name : session_names){
    if (mView->isSessionActive(session_name)){
      this->deleteCurve(session_name);
      this->computeCurve(session_name, mView->leftImage(), image);
    }
  }
}

void CurvesViewerPresenterImp::activeSession(const QString &session)
{
  this->computeCurve(session, mView->leftImage(), mView->rightImage());
}

void CurvesViewerPresenterImp::disableSession(const QString &session)
{
  this->deleteCurve(session);
}

void CurvesViewerPresenterImp::computeCurve(const QString &session, const QString &imageLeft, const QString &imageRight)
{
  std::vector<QPointF> curve;
  double auc = mModel->computeCurve(session, imageLeft, imageRight, curve);
  QString title = session;
  title.append(" [AUC=").append(QString::number(auc, 'g', 3)).append("]");
  mView->setCurve(title, curve);
}

void CurvesViewerPresenterImp::deleteCurve(const QString &session)
{
  mView->eraseCurve(session);
}

void CurvesViewerPresenterImp::help()
{
  if (mHelp){
    mHelp->setPage("roc_curves.html");
    mHelp->show();
  }
}

void CurvesViewerPresenterImp::open()
{
  mView->clear();


  std::vector<QString> imagesLeft = mModel->images();
  if (imagesLeft.empty() == false) {
    mView->setLeftImageList(imagesLeft);
    this->loadLeftImage(imagesLeft[0]);
  }

  std::vector<std::tuple<QString,QString,QString>> sessions = mModel->sessions();
  for (auto &session : sessions){
    QString sessionName;
    QString sessionDetector;
    QString sessionDescriptor;
    std::tie(sessionName, sessionDetector, sessionDescriptor) = session;
    mView->addSession(sessionName, sessionDetector, sessionDescriptor);
  }

  mView->show();
}

void CurvesViewerPresenterImp::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void CurvesViewerPresenterImp::init()
{
}

} // namespace photomatch
