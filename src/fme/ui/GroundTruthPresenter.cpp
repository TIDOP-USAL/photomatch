#include "GroundTruthPresenter.h"

#include "fme/ui/GroundTruthModel.h"
#include "fme/ui/GroundTruthView.h"

#include <QStandardPaths>
#include <QDir>

namespace fme
{

GroundTruthPresenter::GroundTruthPresenter(IGroundTruthView *view,
                                           IGroundTruthModel *model)
  : IGroundTruthPresenter(),
    mView(view),
    mModel(model)/*,
    mHelp(nullptr)*/
{
  init();

  connect(mView, SIGNAL(leftImageChange(QString)),         this, SLOT(loadLeftImage(QString)));
  connect(mView, SIGNAL(rightImageChange(QString)),        this, SLOT(loadRightImage(QString)));
  connect(mView, SIGNAL(markedLeftPoint(QPointF)),         this, SLOT(markedLeftPoint(QPointF)));
  connect(mView, SIGNAL(markedRightPoint(QPointF)),        this, SLOT(markedRightPoint(QPointF)));
  connect(mView, SIGNAL(addPoint(QString,QPointF,QString,QPointF)),
          this, SLOT(addPoint(QString,QPointF,QString,QPointF)));
}

GroundTruthPresenter::~GroundTruthPresenter()
{

}

void GroundTruthPresenter::loadLeftImage(const QString &image)
{
  mView->setLeftImage(image);
  std::vector<QString> imagesRight = mModel->imagePairs(QFileInfo(image).baseName());
  if (imagesRight.empty() == false){
    mView->setRightImageList(imagesRight);
    mView->setRightImage(imagesRight[0]);
  }
}

void GroundTruthPresenter::loadRightImage(const QString &image)
{
  mView->setRightImage(image);
}

void GroundTruthPresenter::markedLeftPoint(const QPointF &pt)
{
  mView->setPointLeft(pt);
}

void GroundTruthPresenter::markedRightPoint(const QPointF &pt)
{
  mView->setPointRight(pt);
}

void GroundTruthPresenter::addPoint(const QString &image1, const QPointF &pt1, const QString &image2, const QPointF &pt2)
{
  size_t id1 = mModel->addPoint(image1, pt1);
  size_t id2 = mModel->addPoint(image2, pt2);
  mModel->addCorrespondence(image1, id1, image2, id2);

  ///TODO: Actualizar los puntos en mView.
  mView->addHomologousPoints(pt1, pt2);
}

void GroundTruthPresenter::help()
{
}

void GroundTruthPresenter::open()
{
  mView->clear();
  mView->show();


  /// Se cargan las imágenes despues de mostrar el Dialog porque si se hace antes
  /// el QGraphicView no tiene el tamaño adecuado
  std::vector<QString> imagesLeft = mModel->images();
  if (imagesLeft.empty() == false) {
    mView->setLeftImageList(imagesLeft);
    loadLeftImage(imagesLeft[0]);
  }
}

void GroundTruthPresenter::init()
{
}

} // namespace fme



