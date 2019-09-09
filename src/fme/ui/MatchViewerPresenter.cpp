#include "MatchViewerPresenter.h"

#include "fme/ui/MatchViewerModel.h"
#include "fme/ui/MatchViewerView.h"
//#include "ui/help.h"

#include <QStandardPaths>
#include <QDir>

namespace fme
{

MatchViewerPresenter::MatchViewerPresenter(IMatchViewerView *view,
                                           IMatchViewerModel *model)
  : IMatchViewerPresenter(),
    mView(view),
    mModel(model)/*,
    mHelp(nullptr)*/
{
  init();

  connect(mView, SIGNAL(leftImageChange(QString)),         this, SLOT(leftImageChange(QString)));
  connect(mView, SIGNAL(rightImageChange(QString)),        this, SLOT(rightImageChange(QString)));
  connect(mView, SIGNAL(loadMatches(QString, QString)),    this, SLOT(loadMatches(QString, QString)));

  connect(mView, SIGNAL(accepted()), this, SLOT(save()));
  connect(mView, SIGNAL(rejected()), this, SLOT(discart()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));
}

void MatchViewerPresenter::leftImageChange(const QString &image)
{
  mView->setLeftImage(image);
  std::vector<QString> imagesRight = mModel->imagePairs(image);
  if (imagesRight.empty() == false){
    mView->setRightImageList(imagesRight);
    mView->setRightImage(imagesRight[0]);
  }
}

void MatchViewerPresenter::rightImageChange(const QString &image)
{
  mView->setRightImage(image);
}

void MatchViewerPresenter::loadMatches(const QString &imageLeft, const QString &imageRight)
{
  std::vector<std::pair<QPointF, QPointF>> matches = mModel->loadMatches(imageLeft, imageRight);
  mView->setMatches(matches);
}

//void MatchViewerPresenter::save()
//{
//  //if (mModel->isModified()){
//  //  emit projectModified();
//  //}
//  //mModel->save();
//}
//
//void MatchViewerPresenter::discart()
//{
//  mModel->load();
//}

void MatchViewerPresenter::help()
{
//  if (mHelp){
//    mHelp->setPage("MatchViewer.html");
//    mHelp->setModal(true);
//    mHelp->showMaximized();
//  }
}

void MatchViewerPresenter::open()
{
  mView->clear();
  mModel->load();

  mView->show();

  /// Se cargan las imágenes despues de mostrar el Dialog porque si se hace antes
  /// el QGraphicView no tiene el tamaño adecuado
  std::vector<QString> imagesLeft = mModel->images();
  if (imagesLeft.empty() == false) {

    /// Listado de imagenes
    mView->setLeftImageList(imagesLeft);

    /// Se activa la primera imagen
    mView->setLeftImage(imagesLeft[0]);

    // Se recuperan los pares de la primera imagen
    std::vector<QString> imagesRight = mModel->imagePairs(imagesLeft[0]);
    if (imagesRight.empty() == false){
      mView->setRightImageList(imagesRight);
      mView->setRightImage(imagesRight[0]);
      loadMatches(imagesLeft[0], imagesRight[0]);
    }
  }

}

//void MatchViewerPresenter::setHelp(std::shared_ptr<Help> &help)
//{
//  mHelp = help;
//}

void MatchViewerPresenter::init()
{
}

} // namespace fme
