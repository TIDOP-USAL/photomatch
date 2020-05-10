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


#include "MatchViewerPresenter.h"

#include "photomatch/ui/MatchViewerModel.h"
#include "photomatch/ui/MatchViewerView.h"
#include "photomatch/ui/SettingsModel.h"
#include "photomatch/ui/HelpDialog.h"

#include <QStandardPaths>
#include <QDir>

namespace photomatch
{

MatchViewerPresenterImp::MatchViewerPresenterImp(MatchViewerView *view,
                                                 MatchViewerModel *model,
                                                 SettingsModel *settings)
  : MatchViewerPresenter(),
    mView(view),
    mModel(model),
    mSettingsModel(settings),
    mHelp(nullptr)
{
  this->init();
  this->initSignalAndSlots();
}

MatchViewerPresenterImp::~MatchViewerPresenterImp()
{

}

void MatchViewerPresenterImp::openFromSession(const QString &session)
{
  this->setSession(session);
  this->open();
}

void MatchViewerPresenterImp::openFromSessionAndImages(const QString &session, const QString &imageLeft, const QString &imageRight)
{
  this->setSession(session);
  this->open();
  this->setLeftImage(imageLeft);
  this->setRightImage(imageRight);
}

void MatchViewerPresenterImp::setSession(const QString &session)
{
  mModel->setSessionName(session);
  mView->clear();
  mView->setSessionName(mModel->sessionName());
}

void MatchViewerPresenterImp::setLeftImage(const QString &image)
{
  mView->setLeftImage(image);
  std::vector<QString> imagesRight = mModel->imagePairs(image);
  if (imagesRight.empty() == false){
    mView->setRightImageList(imagesRight);
    mView->setRightImage(QFileInfo(imagesRight[0]).baseName());
    loadMatches(image, QFileInfo(imagesRight[0]).baseName());
  }
}

void MatchViewerPresenterImp::setRightImage(const QString &image)
{
  mView->setRightImage(image);
}

void MatchViewerPresenterImp::loadMatches(const QString &imageLeft, const QString &imageRight)
{
  std::vector<std::tuple<size_t, size_t, QPointF, size_t, QPointF, float>> matches = mModel->loadMatches(imageLeft, imageRight);
  mView->setMatches(matches);
}

void MatchViewerPresenterImp::deleteMatch(const QString &imageLeft, const QString &imageRight, int query_id, int train_id)
{
  mModel->deleteMatch(imageLeft, imageRight, query_id, train_id);
}

void MatchViewerPresenterImp::help()
{
  if (mHelp){
    mHelp->setPage("matches_viewer.html");
    mHelp->show();
  }
}

void MatchViewerPresenterImp::open()
{
  mView->clear();

  mView->setSessionName(mModel->sessionName());
  mView->setBGColor(mSettingsModel->matchesViewerBGColor());
  mView->setSelectedMarkerStyle(mSettingsModel->matchesViewerSelectMarkerColor(),
                                mSettingsModel->matchesViewerSelectMarkerWidth());
  mView->setMarkerStyle(mSettingsModel->matchesViewerMarkerColor(),
                        mSettingsModel->matchesViewerMarkerWidth(),
                        mSettingsModel->matchesViewerMarkerType(),
                        mSettingsModel->matchesViewerMarkerSize());
  mView->setLineStyle(mSettingsModel->matchesViewerLineColor(),
                      mSettingsModel->matchesViewerLineWidth());

  /// Se carga el fichero de puntos de paso.
  mModel->loadPassPoints();

  mView->show();

  /// Se cargan las imágenes despues de mostrar el Dialog porque si se hace antes
  /// el QGraphicView no tiene el tamaño adecuado
  std::vector<QString> imagesLeft = mModel->images();
  if (imagesLeft.empty() == false) {
    mView->setLeftImageList(imagesLeft);
    setLeftImage(QFileInfo(imagesLeft[0]).baseName());
  }

}

void MatchViewerPresenterImp::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void MatchViewerPresenterImp::init()
{
}

void MatchViewerPresenterImp::initSignalAndSlots()
{
  connect(mView, SIGNAL(leftImageChange(QString)),         this, SLOT(setLeftImage(QString)));
  connect(mView, SIGNAL(rightImageChange(QString)),        this, SLOT(setRightImage(QString)));
  connect(mView, SIGNAL(loadMatches(QString, QString)),    this, SLOT(loadMatches(QString, QString)));

  connect(mView, SIGNAL(deleteMatch(QString, QString, int, int)),
          this,  SLOT(deleteMatch(QString, QString, int, int)));

  connect(mView, SIGNAL(help()),     this, SLOT(help()));
}

} // namespace photomatch
