#include "FeaturesViewerPresenter.h"

#include "photomatch/ui/FeaturesViewerModel.h"
#include "photomatch/ui/FeaturesViewerView.h"
#include "photomatch/ui/SettingsModel.h"
#include "photomatch/ui/HelpDialog.h"

#include <QFileInfo>

namespace photomatch
{

FeaturesViewerPresenter::FeaturesViewerPresenter(photomatch::IFeaturesViewerView *view,
                                                 photomatch::IFeaturesViewerModel *model,
                                                 ISettingsModel *settingsModel)
  : IFeaturesViewerPresenter(),
    mView(view),
    mModel(model),
    mSettingsModel(settingsModel),
    mHelp(nullptr)
{
  init();

  connect(mView, SIGNAL(imageChange(QString)),     this, SLOT(setImageActive(QString)));

  connect(mView, SIGNAL(help()),     this, SLOT(help()));
}

FeaturesViewerPresenter::~FeaturesViewerPresenter()
{

}

void FeaturesViewerPresenter::help()
{
  if (mHelp){
    mHelp->setPage("keypoints_viewer.html");
    //mHelp->setModal(true);
    mHelp->showMaximized();
  }
}

void FeaturesViewerPresenter::open()
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

void FeaturesViewerPresenter::setHelp(std::shared_ptr<HelpDialog> &help)
{
  mHelp = help;
}

void FeaturesViewerPresenter::init()
{
}

void FeaturesViewerPresenter::setSession(const QString &session)
{
  mModel->setSessionName(session);
  mView->clear();
  mView->setSessionName(mModel->sessionName());
}

void FeaturesViewerPresenter::setImageActive(const QString &image)
{
  mView->setCurrentImage(image);
  loadKeypoints(image);
}

void FeaturesViewerPresenter::loadKeypoints(const QString &image)
{
  std::vector<std::tuple<QPointF, double, double>> keypoints = mModel->loadKeypoints(image);
  mView->setKeyPoints(keypoints);
}

} // namespace photomatch
