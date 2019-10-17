#include "RepeatabilityPresenter.h"

#include "fme/ui/RepeatabilityModel.h"
#include "fme/ui/RepeatabilityView.h"

#include <QFileInfo>

namespace fme
{

RepeatabilityPresenter::RepeatabilityPresenter(IRepeatabilityView *view,
                                               IRepeatabilityModel *model)
  : IRepeatabilityPresenter(),
    mView(view),
    mModel(model)/*,
    mHelp(nullptr)*/
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

void RepeatabilityPresenter::init()
{
}

} // namespace fme