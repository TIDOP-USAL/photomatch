#include "MatchViewerPresenter.h"

#include "photomatch/ui/MatchViewerModel.h"
#include "photomatch/ui/MatchViewerView.h"
#include "photomatch/ui/SettingsModel.h"

//#include "ui/help.h"

#include <QStandardPaths>
#include <QDir>

namespace photomatch
{

MatchViewerPresenter::MatchViewerPresenter(IMatchViewerView *view,
                                           IMatchViewerModel *model,
                                           ISettingsModel *settings)
  : IMatchViewerPresenter(),
    mView(view),
    mModel(model),
    mSettingsModel(settings)/*,
    mHelp(nullptr)*/
{
  init();

  connect(mView, SIGNAL(leftImageChange(QString)),         this, SLOT(loadLeftImage(QString)));
  connect(mView, SIGNAL(rightImageChange(QString)),        this, SLOT(loadRightImage(QString)));
  connect(mView, SIGNAL(loadMatches(QString, QString)),    this, SLOT(loadMatches(QString, QString)));

  connect(mView, SIGNAL(deleteMatch(QString, QString, int, int)),
          this,  SLOT(deleteMatch(QString, QString, int, int)));

  connect(mView, SIGNAL(help()),     this, SLOT(help()));
}

MatchViewerPresenter::~MatchViewerPresenter()
{

}

void MatchViewerPresenter::loadLeftImage(const QString &image)
{
  mView->setLeftImage(image);
  std::vector<QString> imagesRight = mModel->imagePairs(QFileInfo(image).baseName());
  if (imagesRight.empty() == false){
    mView->setRightImageList(imagesRight);
    mView->setRightImage(imagesRight[0]);
    loadMatches(image, imagesRight[0]);
  }
}

void MatchViewerPresenter::loadRightImage(const QString &image)
{
  mView->setRightImage(image);
}

void MatchViewerPresenter::loadMatches(const QString &imageLeft, const QString &imageRight)
{
  std::vector<std::tuple<size_t, QPointF, size_t, QPointF, float>> matches = mModel->loadMatches(QFileInfo(imageLeft).baseName(), QFileInfo(imageRight).baseName());
  mView->setMatches(matches);
}

void MatchViewerPresenter::deleteMatch(const QString &imageLeft, const QString &imageRight, int query_id, int train_id)
{
  mModel->deleteMatch(imageLeft, imageRight, query_id, train_id);
}

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

  mView->setSessionName(mModel->sessionName());
  mView->setBGColor(mSettingsModel->matchesViewerBGColor());
  mView->setMarkerStyle(mSettingsModel->matchesViewerMarkerColor(),
                        mSettingsModel->matchesViewerMarkerWidth(),
                        mSettingsModel->matchesViewerMarkerType(),
                        mSettingsModel->matchesViewerMarkerSize());
  mView->setLineStyle(mSettingsModel->matchesViewerLineColor(),
                      mSettingsModel->matchesViewerLineWidth());

  mView->show();

  /// Se cargan las imágenes despues de mostrar el Dialog porque si se hace antes
  /// el QGraphicView no tiene el tamaño adecuado
  std::vector<QString> imagesLeft = mModel->images();
  if (imagesLeft.empty() == false) {
    mView->setLeftImageList(imagesLeft);
    loadLeftImage(imagesLeft[0]);
  }

}

//void MatchViewerPresenter::setHelp(std::shared_ptr<Help> &help)
//{
//  mHelp = help;
//}

void MatchViewerPresenter::init()
{
}

} // namespace photomatch
