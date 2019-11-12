#include "GroundTruthPresenter.h"

#include "photomatch/ui/GroundTruthModel.h"
#include "photomatch/ui/GroundTruthView.h"
#include "photomatch/ui/SettingsModel.h"

#include <QStandardPaths>
#include <QDir>
#include <QFileDialog>

namespace photomatch
{

GroundTruthPresenter::GroundTruthPresenter(IGroundTruthView *view,
                                           IGroundTruthModel *model,
                                           ISettingsModel *settings)
  : IGroundTruthPresenter(),
    mView(view),
    mModel(model),
    mSettingsModel(settings)/*,
    mHelp(nullptr)*/
{
  init();

  connect(mView, SIGNAL(leftImageChange(QString)),         this, SLOT(loadLeftImage(QString)));
  connect(mView, SIGNAL(rightImageChange(QString)),        this, SLOT(loadRightImage(QString)));
  //connect(mView, SIGNAL(markedLeftPoint(QPointF)),         this, SLOT(markedLeftPoint(QPointF)));
  //connect(mView, SIGNAL(markedRightPoint(QPointF)),        this, SLOT(markedRightPoint(QPointF)));
  connect(mView, SIGNAL(addPoint(QString,QPointF,QString,QPointF)),
          this, SLOT(addPoint(QString,QPointF,QString,QPointF)));

  connect(mView, SIGNAL(loadHomologousPoints(QString, QString)),    this, SLOT(loadGroundTruth(QString, QString)));
//  connect(mView, SIGNAL(deleteHomologousPoint(QString, QString, int)),
//          this,  SLOT(deleteMatch(QString, QString, int, int)));
  connect(mView, SIGNAL(importGroundTruth()), this, SLOT(importGroundTruth()));

  connect(mView, SIGNAL(accepted()), this, SLOT(save()));
  connect(mView, SIGNAL(rejected()), this, SLOT(discart()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));

}

GroundTruthPresenter::~GroundTruthPresenter()
{

}

void GroundTruthPresenter::loadLeftImage(const QString &image)
{
  mView->setLeftImage(image);
  std::vector<QString> imagesRight = mModel->imagePairs(image);
  if (imagesRight.empty() == false){
    mView->setRightImageList(imagesRight);
    mView->setRightImage(imagesRight[0]);
    loadGroundTruth(image, QFileInfo(imagesRight[0]).baseName());
  }
}

void GroundTruthPresenter::loadRightImage(const QString &image)
{
  mView->setRightImage(image);
}

void GroundTruthPresenter::loadGroundTruth(const QString &imageLeft, const QString &imageRight)
{
  std::vector<std::pair<QPointF, QPointF>> homologousPoints = mModel->groundTruth(imageLeft, imageRight);

  mView->setHomologousPoints(homologousPoints);
  QTransform trf = mModel->transform(imageLeft, imageRight);
  mView->setTransform(trf);
}

//void GroundTruthPresenter::markedLeftPoint(const QPointF &pt)
//{
//  mView->setPointLeft(pt);
//}

//void GroundTruthPresenter::markedRightPoint(const QPointF &pt)
//{
//  mView->setPointRight(pt);
//}

void GroundTruthPresenter::addPoint(const QString &image1, const QPointF &pt1, const QString &image2, const QPointF &pt2)
{
  mModel->addHomologusPoints(image1, pt1, image2, pt2);
  QTransform trf = mModel->transform(image1, image2);
  mView->setTransform(trf);
  mView->addHomologousPoint(pt1, pt2);
  mView->setUnsavedChanges(true);
}

void GroundTruthPresenter::importGroundTruth()
{
  QString file = QFileDialog::getOpenFileName(Q_NULLPTR,
                                              tr("Import Ground Truth"),
                                              mModel->projectPath(),
                                              tr("Ground Truth (*.txt)"));
  if (!file.isEmpty()) {

    mModel->setGroundTruth(file);
  }

  loadGroundTruth(mView->imageLeft(), mView->imageRight());

  emit groundTruthAdded();
}

void GroundTruthPresenter::save()
{
  mView->setUnsavedChanges(false);
  if (mModel->existGroundTruth()) emit groundTruthAdded();
  mModel->saveGroundTruth();
}

void GroundTruthPresenter::discart()
{
  mView->setUnsavedChanges(false);
  mModel->loadGroundTruth();
}

void GroundTruthPresenter::help()
{
}

void GroundTruthPresenter::open()
{
  mView->clear();

  mView->setBGColor(mSettingsModel->matchesViewerBGColor());
  mView->setMarkerStyle(mSettingsModel->matchesViewerMarkerColor(),
                        mSettingsModel->matchesViewerMarkerWidth(),
                        mSettingsModel->matchesViewerMarkerType(),
                        mSettingsModel->matchesViewerMarkerSize());
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

void GroundTruthPresenter::init()
{
}

} // namespace photomatch



