#include "ExportFeaturesPresenter.h"

#include "photomatch/ui/ExportFeaturesModel.h"
#include "photomatch/ui/ExportFeaturesView.h"

namespace photomatch
{

ExportFeaturesPresenter::ExportFeaturesPresenter(IExportFeaturesView *view,
                                                 IExportFeaturesModel *model)
  : IExportFeaturesPresenter(),
    mView(view),
    mModel(model)
{
  init();

  connect(mView, SIGNAL(sessionChange(QString)),   this, SLOT(sessionChange(QString)));
  connect(mView, SIGNAL(accepted()),               this, SLOT(save()));

  //connect(mView, SIGNAL(rejected()),        this, SLOT(discart()));
  connect(mView, SIGNAL(help()),            this, SLOT(help()));
}

ExportFeaturesPresenter::~ExportFeaturesPresenter()
{

}

void ExportFeaturesPresenter::help()
{
}

void ExportFeaturesPresenter::open()
{
  mView->clear();

  mView->setSessions(mModel->sessions());
  mView->setActiveSession(mModel->sessionName());
  mView->setFormats(mModel->formats());
  mView->setImageFiles(mModel->features());

  mView->exec();
}

void ExportFeaturesPresenter::init()
{
}

void ExportFeaturesPresenter::save()
{
  mModel->exportFeatures(mView->exportFiles(),
                         mView->exportPath(),
                         mView->format());
}

void ExportFeaturesPresenter::sessionChange(const QString &session)
{
  mModel->setSessionName(session);
  mView->setActiveSession(session);
  mView->setFormats(mModel->formats());
}

} // namespace photomatch
