#include "ExportFeaturesPresenter.h"

#include "photomatch/ui/ExportFeaturesModel.h"
#include "photomatch/ui/ExportFeaturesView.h"
#include "photomatch/ui/HelpDialog.h"

namespace photomatch
{

ExportFeaturesPresenter::ExportFeaturesPresenter(IExportFeaturesView *view,
                                                 IExportFeaturesModel *model)
  : IExportFeaturesPresenter(),
    mView(view),
    mModel(model),
    mHelp(nullptr)
{
  init();

  connect(mView, SIGNAL(sessionChange(QString)),   this, SLOT(sessionChange(QString)));
  connect(mView, SIGNAL(accepted()),               this, SLOT(save()));
  connect(mView, SIGNAL(help()),                   this, SLOT(help()));
}

ExportFeaturesPresenter::~ExportFeaturesPresenter()
{

}

void ExportFeaturesPresenter::help()
{
  if (mHelp){
    mHelp->setPage("index.html#export_keypoints");
    mHelp->show();
  }
}

void ExportFeaturesPresenter::open()
{
  mView->clear();

  mView->setSessions(mModel->sessions());
  mView->setSessionToExport(mModel->activeSessionName());
  mView->setFormats(mModel->formats());
  mView->setImageFiles(mModel->features(mModel->activeSessionName()));

  mView->exec();
}

void ExportFeaturesPresenter::setHelp(std::shared_ptr<HelpDialog> &help)
{
  mHelp = help;
}

void ExportFeaturesPresenter::init()
{
}

void ExportFeaturesPresenter::save()
{
  mModel->exportFeatures(mView->session(),
                         mView->exportFiles(),
                         mView->exportPath(),
                         mView->format());
}

void ExportFeaturesPresenter::sessionChange(const QString &session)
{
  mView->setSessionToExport(session);
  mView->setFormats(mModel->formats());
  mView->setImageFiles(mModel->features(session));
}

} // namespace photomatch
