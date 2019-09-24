#include "DescriptorMatcherPresenter.h"

#include "fme/core/features/matcher.h"
#include "fme/ui/DescriptorMatcherModel.h"
#include "fme/ui/DescriptorMatcherView.h"
#include "fme/ui/ProjectModel.h"
#include "fme/ui/SettingsModel.h"
#include "fme/ui/utils/Progress.h"

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
    mProgressHandler(nullptr)
{
  init();

  connect(mView, SIGNAL(run()),      this, SLOT(run()));
  connect(mView, SIGNAL(rejected()), this, SLOT(discart()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));

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
  TL_TODO("Leer valores guardados en proyecto")
//  Match *matcher = mProjectModel->currentSession()->matcher().get();
//  matcher->type() == Match::Type::flann;
//  matcher->type() == Match::Type::brute_force;

  mView->setRatio(mSettingsModel->matchRatio());
  mView->setDistance(mSettingsModel->matchDistance());
  mView->setNormType(mSettingsModel->matchNormType());
  mView->setConfidence(mSettingsModel->matchConfidence());
  mView->setCrossMatching(mSettingsModel->matchCrossMatching());

  if (Feature *descriptor = mProjectModel->currentSession()->descriptor().get()){

    if (descriptor->type() == Feature::Type::akaze){
      QString descriptorType = dynamic_cast<IAkaze *>(descriptor)->descriptorType();

      if (descriptorType.compare("KAZE") == 0 ||
          descriptorType.compare("KAZE_UPRIGHT") == 0){
        mView->disableBruteForceNorm("NORM_HAMMING");
        mView->disableBruteForceNorm("NORM_HAMMING2");
      } else if (descriptorType.compare("MLDB") == 0 ||
                 descriptorType.compare("MLDB_UPRIGHT") == 0){
        mView->enableBruteForceNorm("NORM_HAMMING");
        mView->enableBruteForceNorm("NORM_HAMMING2");
      }
    } else if (descriptor->type() == Feature::Type::brief ||
               descriptor->type() == Feature::Type::brisk ||
               descriptor->type() == Feature::Type::freak ||
               descriptor->type() == Feature::Type::latch ||
               descriptor->type() == Feature::Type::lucid ||
               descriptor->type() == Feature::Type::lss){
      mView->enableBruteForceNorm("NORM_HAMMING");
      mView->enableBruteForceNorm("NORM_HAMMING2");
      mView->setNormType("NORM_HAMMING");
    } else if (descriptor->type() == Feature::Type::orb){
      int wta_k = dynamic_cast<IOrb *>(descriptor)->wta_k();
      if (wta_k == 3 || wta_k == 4){
        mView->setNormType("NORM_HAMMING2");
      } else {
        mView->setNormType("NORM_HAMMING");
      }
      mView->enableBruteForceNorm("NORM_HAMMING");
      mView->enableBruteForceNorm("NORM_HAMMING2");
      TL_TODO("Con L1 y L2 funciona aunque la documentación indica que se debe usar NORM_HAMMING o NORM_HAMMING2")
    } else if (descriptor->type() == Feature::Type::sift ||
               descriptor->type() == Feature::Type::surf ||
               descriptor->type() == Feature::Type::daisy ||
               descriptor->type() == Feature::Type::kaze ||
               descriptor->type() == Feature::Type::hog){
      mView->disableBruteForceNorm("NORM_HAMMING");
      mView->disableBruteForceNorm("NORM_HAMMING2");
    }

  }


  mView->exec();
}

void DescriptorMatcherPresenter::init()
{
}

void DescriptorMatcherPresenter::setProgressHandler(ProgressHandler *progressHandler)
{
  mProgressHandler = progressHandler;
}

void DescriptorMatcherPresenter::cancel()
{
  mMultiProcess->stop();

  disconnect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
  disconnect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));

  if (mProgressHandler){
    mProgressHandler->setRange(0,1);
    mProgressHandler->setValue(1);
    mProgressHandler->onFinish();
    mProgressHandler->setDescription(tr("Processing has been canceled by the user"));

    disconnect(mMultiProcess, SIGNAL(finished()),                 mProgressHandler,    SLOT(onFinish()));
    disconnect(mMultiProcess, SIGNAL(statusChangedNext()),        mProgressHandler,    SLOT(onNextPosition()));
    disconnect(mMultiProcess, SIGNAL(error(int, QString)),        mProgressHandler,    SLOT(onFinish()));
  }

  msgInfo("Processing has been canceled by the user");
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

    FlannMatcher::Index index;
    Feature *descriptor = mProjectModel->currentSession()->descriptor().get();
    if (descriptor->type() == Feature::Type::orb ||
        descriptor->type() == Feature::Type::brief ||
        descriptor->type() == Feature::Type::freak ||
        descriptor->type() == Feature::Type::latch ||
        descriptor->type() == Feature::Type::lucid ||
        descriptor->type() == Feature::Type::brisk){
      index = FlannMatcher::Index::lsh;
    } else if (descriptor->type() == Feature::Type::akaze) {
      QString descriptorType = dynamic_cast<IAkaze *>(descriptor)->descriptorType();
      if (descriptorType.compare("KAZE") == 0 ||
          descriptorType.compare("KAZE_UPRIGHT") == 0){
        index = FlannMatcher::Index::kdtree;
      } else if (descriptorType.compare("MLDB") == 0 ||
                 descriptorType.compare("MLDB_UPRIGHT") == 0){
        index = FlannMatcher::Index::lsh;
      }
    } else {
      index = FlannMatcher::Index::kdtree;
    }

    descriptorMatcher = std::make_shared<FlannMatcher>(index);
  } else {
    ///TODO: error
    return;
  }

  mProjectModel->setMatcher(std::dynamic_pointer_cast<Match>(descriptorMatcher));

  std::shared_ptr<RobustMatching> robustMatching(new RobustMatching(descriptorMatcher/*,
                                                                    mView->ratio(),
                                                                    mView->crossMatching()*/));

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

      std::shared_ptr<MatchingProcess> matcher(new MatchingProcess(features1, features2, matches, robustMatching));
      connect(matcher.get(), SIGNAL(matchCompute(QString,QString,QString)), this, SLOT(onMatchCompute(QString,QString,QString)));
      mMultiProcess->appendProcess(matcher);

    }

  }

  mProjectModel->clearMatches();

  connect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
  connect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));

  if (mProgressHandler){
    connect(mMultiProcess, SIGNAL(finished()),             mProgressHandler,    SLOT(onFinish()));
    connect(mMultiProcess, SIGNAL(statusChangedNext()),    mProgressHandler,    SLOT(onNextPosition()));
    connect(mMultiProcess, SIGNAL(error(int, QString)),    mProgressHandler,    SLOT(onFinish()));

    mProgressHandler->setRange(0, mMultiProcess->count());
    mProgressHandler->setValue(0);
    mProgressHandler->setTitle("Feature Matching");
    mProgressHandler->setDescription("Matching Features...");
    mProgressHandler->onInit();
  }

  mView->hide();

  emit running();

  mMultiProcess->start();
}

void DescriptorMatcherPresenter::onError(int code, const QString &msg)
{
  disconnect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
  disconnect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));

  if (mProgressHandler){
    mProgressHandler->setRange(0,1);
    mProgressHandler->setValue(1);
    mProgressHandler->onFinish();
    mProgressHandler->setDescription(tr("Feature Matching error"));

    disconnect(mMultiProcess, SIGNAL(finished()),                 mProgressHandler,    SLOT(onFinish()));
    disconnect(mMultiProcess, SIGNAL(statusChangedNext()),        mProgressHandler,    SLOT(onNextPosition()));
    disconnect(mMultiProcess, SIGNAL(error(int, QString)),        mProgressHandler,    SLOT(onFinish()));
  }

//  QByteArray ba = msg.toLocal8Bit();
//  msgError("(%i) %s", code, ba.constData());
  emit finished();
}

void DescriptorMatcherPresenter::onFinished()
{
  disconnect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
  disconnect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));

  if (mProgressHandler){
    mProgressHandler->setRange(0,1);
    mProgressHandler->setValue(1);
    mProgressHandler->onFinish();
    mProgressHandler->setDescription(tr("Feature Matching finished"));

    disconnect(mMultiProcess, SIGNAL(finished()),                 mProgressHandler,    SLOT(onFinish()));
    disconnect(mMultiProcess, SIGNAL(statusChangedNext()),        mProgressHandler,    SLOT(onNextPosition()));
    disconnect(mMultiProcess, SIGNAL(error(int, QString)),        mProgressHandler,    SLOT(onFinish()));
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

