#include "MultiViewPresenter.h"

#include "photomatch/ui/MultiViewModel.h"
#include "photomatch/ui/MultiViewView.h"
#include "photomatch/ui/HelpDialog.h"

namespace photomatch
{

MultiViewPresenter::MultiViewPresenter(IMultiViewView *view,
                                       IMultiViewModel *model)
  : IMultiViewPresenter(),
    mView(view),
    mModel(model),
    mHelp(nullptr)
{
  init();

  connect(mView, SIGNAL(idChange(int)),  this, SLOT(onIdChange(int)));
}

void MultiViewPresenter::onIdChange(int id)
{
  mView->setImages(mModel->images(static_cast<size_t>(id)));
}

void MultiViewPresenter::setSession(const QString &session)
{
  mModel->setSessionName(session);
  mView->clear();
  mView->setSessionName(mModel->sessionName());
}

void MultiViewPresenter::help()
{
  if (mHelp){
    mHelp->setPage("index.html");
    mHelp->show();
  }
}

void MultiViewPresenter::open()
{
  mView->clear();

  /// Se carga el fichero de puntos de paso.
  mModel->loadPassPoints();

  //mView->setPassPointIds(mModel->passPointIds());
  for (auto &id_size : mModel->passPointIdsAndSize()){
    mView->addPassPointIdsAndNImages(id_size.first, id_size.second);
  }

  mView->show();
}

void MultiViewPresenter::setHelp(std::shared_ptr<HelpDialog> &help)
{
  mHelp = help;
}

void MultiViewPresenter::init()
{
}

} // namespace photomatch


