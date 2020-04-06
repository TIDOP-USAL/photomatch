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


#include "GroundTruthPresenter.h"

#include "photomatch/ui/GroundTruthModel.h"
#include "photomatch/ui/GroundTruthView.h"
#include "photomatch/ui/SettingsModel.h"
#include "photomatch/ui/HelpDialog.h"

#include <QStandardPaths>
#include <QDir>
#include <QFileDialog>

namespace photomatch
{

GroundTruthPresenterImp::GroundTruthPresenterImp(GroundTruthView *view,
                                           GroundTruthModel *model,
                                           SettingsModel *settings)
  : GroundTruthPresenter(),
    mView(view),
    mModel(model),
    mSettingsModel(settings),
    mHelp(nullptr)
{
  init();

  connect(mView, SIGNAL(leftImageChange(QString)),         this, SLOT(loadLeftImage(QString)));
  connect(mView, SIGNAL(rightImageChange(QString)),        this, SLOT(loadRightImage(QString)));
  connect(mView, SIGNAL(addHomologousPoints(QString,QPointF,QString,QPointF)),
          this, SLOT(addHomologousPoints(QString,QPointF,QString,QPointF)));
  connect(mView, SIGNAL(loadHomologousPoints(QString, QString)),    this, SLOT(loadGroundTruth(QString, QString)));
  connect(mView, SIGNAL(deleteHomologous(QString, QString, int)), this,  SLOT(deleteHomologous(QString, QString, int)));
  connect(mView, SIGNAL(importGroundTruth()), this, SLOT(importGroundTruth()));
  connect(mView, SIGNAL(saveGroundTruth()),   this, SLOT(save()));
  connect(mView, SIGNAL(selectHomologous(QString, QString, int)), this, SLOT(selectHomologous(QString, QString, int)));
  connect(mView, SIGNAL(leftPointClicked(QString, QString, QPointF)), this, SLOT(leftPointClicked(QString, QString, QPointF)));
  connect(mView, SIGNAL(rightPointClicked(QString, QString, QPointF)), this, SLOT(rightPointClicked(QString, QString, QPointF)));
  connect(mView, SIGNAL(findLeftPoint(QString, QString, QPointF)), this, SLOT(findLeftPoint(QString, QString, QPointF)));
  connect(mView, SIGNAL(findRightPoint(QString, QString, QPointF)), this, SLOT(findRightPoint(QString, QString, QPointF)));

  connect(mView, SIGNAL(rejected()), this, SLOT(discart()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));

}

GroundTruthPresenterImp::~GroundTruthPresenterImp()
{

}

void GroundTruthPresenterImp::loadLeftImage(const QString &image)
{
  mView->setLeftImage(image);
  std::vector<QString> imagesRight = mModel->imagePairs(image);
  if (imagesRight.empty() == false){
    mView->setRightImageList(imagesRight);
    mView->setRightImage(imagesRight[0]);
    loadGroundTruth(image, QFileInfo(imagesRight[0]).baseName());
  }
}

void GroundTruthPresenterImp::loadRightImage(const QString &image)
{
  mView->setRightImage(image);
}

void GroundTruthPresenterImp::errors(const QString &imageLeft,
                                     const QString &imageRight)
{
  if (0 /* bHomography */){
    homographyErrors(imageLeft, imageRight);
  } else {
    fundamentalErrors(imageLeft, imageRight);
  }
}

void GroundTruthPresenterImp::homographyErrors(const QString &imageLeft,
                                               const QString &imageRight)
{
  std::vector<double> errors = mModel->errorsHomography(imageLeft, imageRight);
  for(size_t i = 0; i < errors.size(); i++){
    if (errors[i] >= 0)
      mView->setHomologousError(static_cast<int>(i+1), errors[i]);
  }
  mView->enableLockView(!errors.empty());
}

void GroundTruthPresenterImp::fundamentalErrors(const QString &imageLeft,
                                                const QString &imageRight)
{
  std::vector<double> errors = mModel->errorsFundamental(imageLeft, imageRight);
  for(size_t i = 0; i < errors.size(); i++){
    if (errors[i] >= 0)
      mView->setHomologousError(static_cast<int>(i+1), errors[i]);
  }
  mView->enableLockView(!errors.empty());
}

void GroundTruthPresenterImp::loadGroundTruth(const QString &imageLeft,
                                              const QString &imageRight)
{
  std::vector<std::pair<QPointF, QPointF>> homologousPoints = mModel->groundTruth(imageLeft, imageRight);

  mView->setHomologousPoints(homologousPoints);

  errors(imageLeft, imageRight);
}

void GroundTruthPresenterImp::addHomologousPoints(const QString &image1,
                                                  const QPointF &pt1,
                                                  const QString &image2,
                                                  const QPointF &pt2)
{
  mModel->addHomologus(image1, pt1, image2, pt2);
  mView->addHomologous(pt1, pt2);
  mView->unselectHomologous();

  errors(image1, image2);

  mView->setUnsavedChanges(true);
}

void GroundTruthPresenterImp::deleteHomologous(const QString &image1,
                                               const QString &image2,
                                               int pointId)
{
  mModel->deleteHomologus(image1, image2, pointId);
  mView->deleteHomologous(pointId);

  errors(image1, image2);

  mView->setUnsavedChanges(true);
}

void GroundTruthPresenterImp::importGroundTruth()
{
  QString file = QFileDialog::getOpenFileName(Q_NULLPTR,
                                              tr("Import Ground Truth"),
                                              mModel->projectPath(),
                                              tr("Ground Truth (*.txt)"));
  if (!file.isEmpty()) {
    mModel->setGroundTruth(file);
  }

  loadGroundTruth(mView->leftImage(), mView->rightImage());

  emit groundTruthAdded();
}

void GroundTruthPresenterImp::selectHomologous(const QString &image1,
                                                 const QString &image2,
                                                 int pointId)
{
  std::pair<QPointF, QPointF> homologus = mModel->homologus(image1, image2, pointId);
  mView->setSelectedHomologous(homologus.first, homologus.second);
}

void GroundTruthPresenterImp::leftPointClicked(const QString &image1, const QString &image2, const QPointF &pt)
{
  mView->setSelectLeftPoint(pt, true);
}

void GroundTruthPresenterImp::rightPointClicked(const QString &image1, const QString &image2, const QPointF &pt)
{
  mView->setSelectedRightPoint(pt, true);
}

void GroundTruthPresenterImp::findLeftPoint(const QString &image1, const QString &image2, const QPointF &pt)
{
  QPointF point_left = mModel->findLeftPoint(image1, image2, pt);
  mView->setSelectLeftPoint(point_left, true);
  if (point_left.isNull()) {
    mView->setCenterLeftViewer(mModel->findProjectedLeftPoint(image1, image2, pt));
  } else {
    mView->setCenterLeftViewer(point_left);
  }
}

void GroundTruthPresenterImp::findRightPoint(const QString &image1, const QString &image2, const QPointF &pt)
{
  QPointF point_right = mModel->findRightPoint(image1, image2, pt);
  mView->setSelectedRightPoint(point_right, true);
  if (point_right.isNull()) {
    mView->setCenterRightViewer(mModel->findProjectedRightPoint(image1, image2, pt));
  } else {
    mView->setCenterRightViewer(point_right);
  }
}

void GroundTruthPresenterImp::save()
{
  mView->setUnsavedChanges(false);
  if (mModel->existGroundTruth()) emit groundTruthAdded();
  mModel->saveGroundTruth();
}

void GroundTruthPresenterImp::discart()
{
  mView->setUnsavedChanges(false);
  mModel->loadGroundTruth();
}

void GroundTruthPresenterImp::help()
{
  if (mHelp){
    mHelp->setPage("ground_truth_editor.html");
    mHelp->show();
  }
}

void GroundTruthPresenterImp::open()
{
  mView->clear();

  mView->setBGColor(mSettingsModel->groundTruthEditorBGColor());
  mView->setMarkerStyle(mSettingsModel->groundTruthEditorMarkerColor(),
                        mSettingsModel->groundTruthEditorMarkerWidth(),
                        2,
                        mSettingsModel->groundTruthEditorMarkerSize());
  mView->setSelectedMarkerStyle(mSettingsModel->groundTruthEditorSelectMarkerColor(),
                                mSettingsModel->groundTruthEditorSelectMarkerWidth());
  mView->show();

  mModel->loadGroundTruth();
  mView->setUnsavedChanges(false);

  /// Se cargan las imágenes despues de mostrar el Dialog porque si se hace antes
  /// el QGraphicView no tiene el tamaño adecuado
  std::vector<QString> imagesLeft = mModel->images();
  if (imagesLeft.empty() == false) {
    mView->setLeftImageList(imagesLeft);
    loadLeftImage(QFileInfo(imagesLeft[0]).baseName());
  }
}

void GroundTruthPresenterImp::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void GroundTruthPresenterImp::init()
{
}

} // namespace photomatch



