#include "HomographyViewerPresenter.h"

#include "fme/ui/HomographyViewerModel.h"
#include "fme/ui/HomographyViewerView.h"

#include <QFileInfo>
#include <QImageReader>

namespace fme
{

HomographyViewerPresenter::HomographyViewerPresenter(IHomographyViewerView *view,
                                                     IHomographyViewerModel *model)
  : IHomographyViewerPresenter(),
    mView(view),
    mModel(model)/*,
    mHelp(nullptr)*/
{
  init();

  connect(mView, SIGNAL(leftImageChange(QString)),         this, SLOT(loadLeftImage(QString)));
  connect(mView, SIGNAL(rightImageChange(QString)),        this, SLOT(loadRightImage(QString)));
  connect(mView, SIGNAL(homography(QString, QString)),     this, SLOT(homography(QString, QString)));


  //connect(mView, SIGNAL(accepted()), this, SLOT(save()));
  //connect(mView, SIGNAL(rejected()), this, SLOT(discart()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));
}

HomographyViewerPresenter::~HomographyViewerPresenter()
{

}

void HomographyViewerPresenter::help()
{
}

void HomographyViewerPresenter::open()
{
  mView->clear();
  mView->show();

  std::vector<QString> imagesLeft = mModel->images();
  if (imagesLeft.empty() == false) {
    mView->setLeftImageList(imagesLeft);
    this->loadLeftImage(imagesLeft[0]);
  }
}

void HomographyViewerPresenter::init()
{
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

} // namespace fme


