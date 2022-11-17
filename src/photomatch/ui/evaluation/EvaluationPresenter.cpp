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


#include "EvaluationPresenter.h"

#include "photomatch/ui/evaluation/EvaluationModel.h"
#include "photomatch/ui/evaluation/EvaluationView.h"
#include "photomatch/ui/settings/SettingsModel.h"
#include "photomatch/ui/HelpDialog.h"

#include <tidop/core/exception.h>

#include <QFileInfo>

namespace photomatch
{

EvaluationPresenterImp::EvaluationPresenterImp(EvaluationView *view,
                                               EvaluationModel *model,
                                               SettingsModel *settings)
  : EvaluationPresenter(),
    mView(view),
    mModel(model),
    mSettingsModel(settings),
    mHelp(nullptr)
{
  this->init();
  this->initSignalAndSlots();
}

void EvaluationPresenterImp::loadLeftImage(const QString &image)
{
  mView->removeErrors();

  std::vector<QString> imagesRight = mModel->imagePairs(QFileInfo(image).baseName());
  if (imagesRight.empty() == false){
    mView->setRightImageList(imagesRight);
    mView->setRightImage(imagesRight[0]);
    std::vector<QString> session_names = mModel->sessionNames();
  }

  std::vector<std::tuple<QString, QString, QString>> sessions = mModel->sessions();
  for (auto &session : sessions) {

    
    QString sessionName;
    QString sessionDetector;
    QString sessionDescriptor;
    std::tie(sessionName, sessionDetector, sessionDescriptor) = session;

    if (mView->isSessionActive(sessionName)) {
      activeSession(sessionName);
    }
  }
  
}

void EvaluationPresenterImp::loadRightImage(const QString &image)
{
  mView->removeErrors();

  std::vector<std::tuple<QString, QString, QString>> sessions = mModel->sessions();
  for (auto &session : sessions) {

    QString sessionName;
    QString sessionDetector;
    QString sessionDescriptor;
    std::tie(sessionName, sessionDetector, sessionDescriptor) = session;

    if (mView->isSessionActive(sessionName)) {
      activeSession(sessionName);
    }
  }
}

void EvaluationPresenterImp::activeSession(const QString &session)
{
  try {
    
    Report report = mModel->computeErrors(session, mView->leftImage(), mView->rightImage(), mView->errorThreshold());
    mView->setErrors(session, report);

  } catch (const std::exception &e) {
    tl::printException(e);
  }

}

void EvaluationPresenterImp::disableSession(const QString &session)
{
  mView->removeErrors(session);
}

void EvaluationPresenterImp::setErrorThreshold(double error)
{
  mView->removeErrors();

  auto sessions = mModel->sessions();
  for (auto &session : sessions) {

    QString sessionName;
    QString sessionDetector;
    QString sessionDescriptor;
    std::tie(sessionName, sessionDetector, sessionDescriptor) = session;

    if (mView->isSessionActive(sessionName)) {
      activeSession(sessionName);
    }
  }
}

void EvaluationPresenterImp::help()
{
  if (mHelp){
    mHelp->setPage("roc_curves.html");
    mHelp->show();
  }
}

void EvaluationPresenterImp::open()
{
  mView->clear();

  /// TODO: esto tiene que ser un parametro
  QString matrixAdjust = mSettingsModel->groundTruthEditorMatrixAdjust();
  mModel->setAdjustMatrix(matrixAdjust);

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

void EvaluationPresenterImp::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void EvaluationPresenterImp::init()
{
}

void EvaluationPresenterImp::initSignalAndSlots()
{
  connect(mView, &EvaluationView::leftImageChange,    this, &EvaluationPresenterImp::loadLeftImage);
  connect(mView, &EvaluationView::rightImageChange,   this, &EvaluationPresenterImp::loadRightImage);
  connect(mView, &EvaluationView::activeSession,      this, &EvaluationPresenterImp::activeSession);
  connect(mView, &EvaluationView::disableSession,     this, &EvaluationPresenterImp::disableSession);
  connect(mView, &EvaluationView::error_threshold_changed, this, &EvaluationPresenterImp::setErrorThreshold);
  connect(mView, &PhotoMatchDialogView::help,         this, &EvaluationPresenterImp::help);
}

} // namespace photomatch
