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


#include "FeaturesViewerPresenter.h"

#include "photomatch/ui/featviewer/FeaturesViewerModel.h"
#include "photomatch/ui/featviewer/FeaturesViewerView.h"
#include "photomatch/ui/settings/SettingsModel.h"
#include "photomatch/ui/HelpDialog.h"

#include <QFileInfo>

namespace photomatch
{

FeaturesViewerPresenterImp::FeaturesViewerPresenterImp(FeaturesViewerView *view,
                                                       FeaturesViewerModel *model,
                                                       SettingsModel *settingsModel)
  : FeaturesViewerPresenter(),
    mView(view),
    mModel(model),
    mSettingsModel(settingsModel),
    mHelp(nullptr)
{
  this->init();
  this->initSignalAndSlots();
}

FeaturesViewerPresenterImp::~FeaturesViewerPresenterImp()
{

}

void FeaturesViewerPresenterImp::help()
{
  if (mHelp){
    mHelp->setPage("keypoints_viewer.html");
    mHelp->show();
  }
}

void FeaturesViewerPresenterImp::open()
{
  mView->clear();

  mView->setSessionName(mModel->sessionName());
  mView->setBGColor(mSettingsModel->keypointsViewerBGColor());
  mView->setSelectedMarkerStyle(mSettingsModel->keypointsViewerSelectMarkerColor(),
                                mSettingsModel->keypointsViewerSelectMarkerWidth());
  mView->setMarkerStyle(mSettingsModel->keypointsViewerMarkerColor(),
                        mSettingsModel->keypointsViewerMarkerWidth(),
                        mSettingsModel->keypointsViewerMarkerType(),
                        mSettingsModel->keypointsViewerMarkerSize());

  mView->show();

  std::vector<QString> images = mModel->images();
  if (images.empty() == false) {
    mView->setImageList(images);
    setImageActive(QFileInfo(images[0]).baseName());
  }
}

void FeaturesViewerPresenterImp::openKeypointsFromSession(const QString &session)
{
  this->setSession(session);
  this->open();
}

void FeaturesViewerPresenterImp::openKeypointsFromSessionAndImage(const QString &session,
                                                                  const QString &image)
{
  this->setSession(session);
  this->open();
  this->setImageActive(image);
}

void FeaturesViewerPresenterImp::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void FeaturesViewerPresenterImp::init()
{
}

void FeaturesViewerPresenterImp::initSignalAndSlots()
{
  connect(mView, SIGNAL(imageChange(QString)),     this, SLOT(setImageActive(QString)));

  connect(mView, SIGNAL(help()),     this, SLOT(help()));
}

void FeaturesViewerPresenterImp::setSession(const QString &session)
{
  mModel->setSessionName(session);
  mView->clear();
  mView->setSessionName(mModel->sessionName());
}

void FeaturesViewerPresenterImp::setImageActive(const QString &image)
{
  mView->setCurrentImage(image);
  loadKeypoints(image);
}

void FeaturesViewerPresenterImp::loadKeypoints(const QString &image)
{
  std::vector<std::tuple<QPointF, double, double>> keypoints = mModel->loadKeypoints(image);
  mView->setKeyPoints(keypoints);
}

} // namespace photomatch
