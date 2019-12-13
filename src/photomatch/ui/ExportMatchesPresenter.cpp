#include "ExportMatchesPresenter.h"

#include "photomatch/ui/ExportMatchesModel.h"
#include "photomatch/ui/ExportMatchesView.h"
#include "photomatch/ui/HelpDialog.h"

#include <tidop/core/messages.h>

#include <QFileDialog>

namespace photomatch
{

ExportMatchesPresenter::ExportMatchesPresenter(IExportMatchesView *view,
                                               IExportMatchesModel *model)
  : IExportMatchesPresenter(),
    mView(view),
    mModel(model),
    mHelp(nullptr)
{
  connect(mView, SIGNAL(sessionChange(QString)),   this, SLOT(sessionChange(QString)));
  connect(mView, SIGNAL(accepted()),               this, SLOT(save()));
  connect(mView, SIGNAL(help()),                   this, SLOT(help()));
}

ExportMatchesPresenter::~ExportMatchesPresenter()
{

}

void ExportMatchesPresenter::help()
{
  if (mHelp){
    mHelp->setPage("menus.html#new_session");
    mHelp->setModal(true);
    mHelp->showMaximized();
  }
}

void ExportMatchesPresenter::open()
{
  mView->clear();

  mView->setSessions(mModel->sessions());
  mView->setActiveSession(mModel->sessionName());

  mView->exec();
}

void ExportMatchesPresenter::setHelp(std::shared_ptr<HelpDialog> &help)
{
  mHelp = help;
}

void ExportMatchesPresenter::init()
{
}

void ExportMatchesPresenter::save()
{
//  QFileDialog dialog(nullptr, tr("Export matches"), "", tr("ORIMA (*.txt);;BINGO (*.txt);;All Files (*)"));
//  dialog.setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
//  if (dialog.exec() == QDialog::Accepted){
//    dialog.selectNameFilter();

//  }
  QString selectedFilter;
  QString pathName = QFileDialog::getSaveFileName(nullptr,
      tr("Export matches"),
      "",
      tr("ORIMA (*.txt);;BINGO (*.txt);;All Files (*)"),
      &selectedFilter);

    if (!pathName.isEmpty()) {

      QString format;
      if (selectedFilter.compare("ORIMA (*.txt)") == 0){
        format = "ORIMA";
      } else if (selectedFilter.compare("BINGO (*.txt)") == 0){
        format = "BINGO";
      } else {
        msgError("Unsupported format");
      }
      mModel->exportMatches(pathName, format);
    }

//  mModel->exportFeatures(mView->exportFiles(),
//                         mView->exportPath(),
//                         mView->format());
}

void ExportMatchesPresenter::sessionChange(const QString &session)
{
  mModel->setSessionName(session);
  mView->setActiveSession(session);
}

} // namespace photomatch
