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


#include "HomographyViewerPresenter.h"

#include "photomatch/ui/HomographyViewerModel.h"
#include "photomatch/ui/HomographyViewerView.h"
#include "photomatch/ui/SettingsModel.h"
#include "photomatch/ui/HelpDialog.h"

#include <QFileInfo>
#include <QImageReader>

namespace photomatch
{

HomographyViewerPresenter::HomographyViewerPresenter(IHomographyViewerView *view,
                                                     IHomographyViewerModel *model,
                                                     ISettingsModel *settings)
  : IHomographyViewerPresenter(),
    mView(view),
    mModel(model),
    mSettingsModel(settings),
    mHelp(nullptr)
{
  init();

  connect(mView, SIGNAL(leftImageChange(QString)),         this, SLOT(loadLeftImage(QString)));
  connect(mView, SIGNAL(rightImageChange(QString)),        this, SLOT(loadRightImage(QString)));
  connect(mView, SIGNAL(homography(QString, QString)),     this, SLOT(homography(QString, QString)));

  connect(mView, SIGNAL(help()),     this, SLOT(help()));
}

HomographyViewerPresenter::~HomographyViewerPresenter()
{

}

void HomographyViewerPresenter::help()
{
  if (mHelp){
    mHelp->setPage("homography.html");
    mHelp->show();
  }
}

void HomographyViewerPresenter::open()
{
  mView->clear();
  mView->setSessionName(mModel->currentSession());
  mView->show();

  std::vector<QString> imagesLeft = mModel->images();
  if (imagesLeft.empty() == false) {
    mView->setLeftImageList(imagesLeft);
    this->loadLeftImage(imagesLeft[0]);
  }
}

void HomographyViewerPresenter::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void HomographyViewerPresenter::init()
{
  mModel->setUseCuda(mSettingsModel->useCuda());
}

void HomographyViewerPresenter::loadLeftImage(const QString &image)
{
  mView->setLeftImage(image);
  std::vector<QString> imagesRight = mModel->imagePairs(QFileInfo(image).baseName());
  if (imagesRight.empty() == false){
    mView->setRightImageList(imagesRight);
    mView->setRightImage(imagesRight[0]);
    homography(QFileInfo(image).baseName(), QFileInfo(imagesRight[0]).baseName());
  }
}

void HomographyViewerPresenter::loadRightImage(const QString &image)
{
  mView->setRightImage(image);
}

void HomographyViewerPresenter::homography(const QString &imageLeft, const QString &imageRight)
{
  QImage image = mModel->homography(imageLeft, imageRight);
  mView->setHomography(image);
}

} // namespace photomatch


