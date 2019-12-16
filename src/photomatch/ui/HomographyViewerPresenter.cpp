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
    //mHelp->setModal(true);
    mHelp->showMaximized();
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

void HomographyViewerPresenter::setHelp(std::shared_ptr<HelpDialog> &help)
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


