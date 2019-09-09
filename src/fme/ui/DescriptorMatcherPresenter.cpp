#include "DescriptorMatcherPresenter.h"

#include "fme/core/features/matcher.h"
#include "fme/ui/DescriptorMatcherModel.h"
#include "fme/ui/DescriptorMatcherView.h"
#include "fme/ui/ProjectModel.h"
#include "fme/ui/SettingsModel.h"
#include "fme/ui/utils/ProgressDialog.h"

#include "fme/process/MultiProcess.h"
#include "fme/process/Matching/MatchingProcess.h"

#include <tidop/core/messages.h>

#include <QFileInfo>
#include <QDir>

namespace fme
{

DescriptorMatcherPresenter::DescriptorMatcherPresenter(IDescriptorMatcherView *view,
                                                       IDescriptorMatcherModel *model,
                                                       IProjectModel *projectModel,
                                                       ISettingsModel *settingsModel)
  : IDescriptorMatcherPresenter(),
    mView(view),
    mModel(model),
    mProjectModel(projectModel),
    mSettingsModel(settingsModel),
    mMultiProcess(new MultiProcess(true)),
    mProgressDialog(nullptr)
{
  init();

  connect(mView, SIGNAL(run()),      this, SLOT(run()));
  connect(mView, SIGNAL(rejected()), this, SLOT(discart()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));

  connect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
  connect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));

}

DescriptorMatcherPresenter::~DescriptorMatcherPresenter()
{
  if (mMultiProcess){
    delete mMultiProcess;
    mMultiProcess = nullptr;
  }
}

void DescriptorMatcherPresenter::help()
{
}

void DescriptorMatcherPresenter::open()
{
//  mView->setRatio(mSettingsModel->matchRatio());
//  mView->setDistance(mSettingsModel->matchDistance());
//  mView->setNormType(mSettingsModel->matchNormType());
//  mView->setConfidence(mSettingsModel->matchConfidence());
//  mView->setCrossMatching(mSettingsModel->matchCrossMatching());
//  mView->setMatchingMethod(mSettingsModel->matchMatchingMethod());

  mView->exec();
}

void DescriptorMatcherPresenter::init()
{
}

void DescriptorMatcherPresenter::setProgressDialog(IProgressDialog *progressDialog)
{
  mProgressDialog = progressDialog;
}

void DescriptorMatcherPresenter::run()
{
  mMultiProcess->clearProcessList();

  QString matchingMethod = mView->matchingMethod();

  QString normType = mView->normType();
  BruteForceMatcher::Norm norm = BruteForceMatcherProperties::Norm::l2;
  if (normType.compare("NORM_L1") == 0) {
    norm = BruteForceMatcherProperties::Norm::l1;
  } else if (normType.compare("NORM_L2") == 0) {
    norm = BruteForceMatcherProperties::Norm::l2;
  } else if (normType.compare("NORM_HAMMING") == 0) {
    norm = BruteForceMatcherProperties::Norm::hamming;
  } else if (normType.compare("NORM_HAMMING2") == 0) {
    norm = BruteForceMatcherProperties::Norm::hamming2;
  }

  std::shared_ptr<DescriptorMatcher> descriptorMatcher;
  if (matchingMethod.compare("Brute-Force") == 0){
    descriptorMatcher = std::make_shared<BruteForceMatcher>(norm);
  } else if (matchingMethod.compare("FLANN") == 0){
    descriptorMatcher = std::make_shared<FlannMatcher>();
  } else {
    ///TODO: error
    return;
  }

  mProjectModel->setMatcher(std::dynamic_pointer_cast<Match>(descriptorMatcher));

  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){

    auto it2 = it;
    it2++;
    for (; it2 != mProjectModel->imageEnd(); it2++){

      QString file1 = (*it)->path();
      QFileInfo fileInfo(file1);
      QString features1 = fileInfo.path();
      features1.append("\\").append(mProjectModel->currentSession()->name());
      features1.append("\\features\\");
      QString features2 = features1;
      features1.append(fileInfo.fileName()).append(".xml");
      QString file2 = (*it2)->path();
      QFileInfo fileInfo2(file2);
      features2.append(fileInfo2.fileName()).append(".xml");

      QString matches = fileInfo.path();
      matches.append("\\").append(mProjectModel->currentSession()->name());
      matches.append("\\matches\\");

      QDir dir_out(matches);
      if (!dir_out.exists()) {
        dir_out.mkpath(".");
      }
      matches.append(fileInfo.baseName()).append("_").append(fileInfo2.baseName()).append(".xml");

      std::shared_ptr<MatchingProcess> matcher(new MatchingProcess(features1, features2, matches, descriptorMatcher));
      connect(matcher.get(), SIGNAL(matchCompute(QString,QString,QString)), this, SLOT(onMatchCompute(QString,QString,QString)));
      mMultiProcess->appendProcess(matcher);

    }

  }

  mView->hide();

  if (mProgressDialog){
    connect(mProgressDialog, SIGNAL(cancel()), mMultiProcess, SLOT(stop()));
    mProgressDialog->setRange(0, 0);
    mProgressDialog->setWindowTitle("Matching Features...");
    mProgressDialog->setStatusText("Matching Features...");
    mProgressDialog->setFinished(false);
    mProgressDialog->show();
  }

  emit running();

  mMultiProcess->start();
}

void DescriptorMatcherPresenter::onError(int code, const QString &msg)
{
  QByteArray ba = msg.toLocal8Bit();
  msgError("(%i) %s", code, ba.constData());
  emit finished();
}

void DescriptorMatcherPresenter::onFinished()
{

  if (mProgressDialog) {
    mProgressDialog->setRange(0,1);
    mProgressDialog->setValue(1);
    mProgressDialog->setFinished(true);
    mProgressDialog->setStatusText(tr("Feature matching finished."));
    disconnect(mProgressDialog, SIGNAL(cancel()), mMultiProcess, SLOT(stop()));
  }

  emit finished();
  msgInfo("Feature matching finished.");
}

void DescriptorMatcherPresenter::onMatchCompute(const QString &left, const QString &right, const QString &match)
{
  mProjectModel->addMatches(left, right, match);
  emit matchCompute(match);
}

} // namespace fme

