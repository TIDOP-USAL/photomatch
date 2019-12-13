#include "RepeatabilityPresenter.h"

#include "photomatch/ui/RepeatabilityModel.h"
#include "photomatch/ui/RepeatabilityView.h"
#include "photomatch/ui/HelpDialog.h"

#include <QFileInfo>

namespace photomatch
{

RepeatabilityPresenter::RepeatabilityPresenter(IRepeatabilityView *view,
                                               IRepeatabilityModel *model)
  : IRepeatabilityPresenter(),
    mView(view),
    mModel(model),
    mHelp(nullptr)
{
  init();

  connect(mView, SIGNAL(selectSession(QString)), this, SLOT(selectSession(QString)));

  connect(mView, SIGNAL(help()),     this, SLOT(help()));
}

void RepeatabilityPresenter::selectSession(const QString &session)
{
  mView->setRepeatability(mModel->computeRepeatability(session));
}

//void RepeatabilityPresenter::loadLeftImage(const QString &image)
//{
//  mView->setLeftImage(image);
//  std::vector<QString> imagesRight = mModel->imagePairs(QFileInfo(image).baseName());
//  if (imagesRight.empty() == false){
//    mView->setRightImageList(imagesRight);
//    mView->setRightImage(imagesRight[0]);
//  }
//}
//
//void RepeatabilityPresenter::loadRightImage(const QString &image)
//{
//  mView->setRightImage(image);
//}

void RepeatabilityPresenter::help()
{
  if (mHelp){
    mHelp->setPage("index.html");
    //mHelp->setModal(true);
    mHelp->showMaximized();
  }
}

void RepeatabilityPresenter::open()
{
  mView->clear();

  std::vector<std::tuple<QString,QString,QString>> sessions = mModel->sessions();
  for (auto &session : sessions){
    QString sessionName;
    QString sessionDetector;
    QString sessionDescriptor;
    std::tie(sessionName, sessionDetector, sessionDescriptor) = session;
    mView->addSession(sessionName, sessionDetector, sessionDescriptor);
  }

  this->selectSession(std::get<0>(sessions[0]));

  mView->show();
}

void RepeatabilityPresenter::setHelp(std::shared_ptr<HelpDialog> &help)
{
  mHelp = help;
}

void RepeatabilityPresenter::init()
{
}

} // namespace photomatch
