#include "DescriptorMatcherPresenter.h"

#include "photomatch/core/features/matcher.h"
#include "photomatch/ui/DescriptorMatcherModel.h"
#include "photomatch/ui/DescriptorMatcherView.h"
#include "photomatch/ui/ProjectModel.h"
#include "photomatch/ui/SettingsModel.h"
#include "photomatch/ui/utils/Progress.h"

#include "photomatch/process/MultiProcess.h"
#include "photomatch/process/Matching/MatchingProcess.h"
#include "photomatch/process/Matching/PassPointsGroupingProcess.h"

#include <tidop/core/messages.h>

#include <QFileInfo>
#include <QDir>
#include <QMessageBox>

namespace photomatch
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
  std::shared_ptr<Session> current_session = mProjectModel->currentSession();
  if (current_session == nullptr) {
    msgError("No active session found");
    return;
  }

  if (Match *matcher = current_session->matcher().get()){
    if (matcher->type() == Match::Type::brute_force){
      mView->setMatchingMethod("Brute-Force");
      BruteForceMatcher::Norm norm = dynamic_cast<IBruteForceMatcher *>(matcher)->normType();
      QString s_norm = "NORM_L2";
      if (norm == BruteForceMatcherProperties::Norm::l1) {
        s_norm = "NORM_L1";
      } else if (norm == BruteForceMatcherProperties::Norm::l2) {
        s_norm = "NORM_L2";
      } else if (norm == BruteForceMatcherProperties::Norm::hamming) {
        s_norm = "NORM_HAMMING";
      } else if (norm == BruteForceMatcherProperties::Norm::hamming2) {
        s_norm = "NORM_HAMMING2";
      }
      mView->setNormType(s_norm);
    } else {
      mView->setMatchingMethod("FLANN");
    }
  } else {
    mView->setMatchingMethod("Brute-Force");
    mView->setNormType(mSettingsModel->matchNormType());
  }


  if (IRobustMatcherRefinement *robustMatcherRefinement = current_session->robustMatcherRefinement().get()){

    mView->setRatio(robustMatcherRefinement->ratio());
    mView->setCrossMatching(robustMatcherRefinement->crossCheck());

    IRobustMatcherRefinement::GeometricTest geometricTest = robustMatcherRefinement->geometricTest();
    if (geometricTest == IRobustMatcherRefinement::GeometricTest::homography){
      mView->setGeometricTest("Homography Matrix");
      mView->setConfidence(robustMatcherRefinement->confidence());
      IRobustMatcherRefinement::HomographyComputeMethod hcm = robustMatcherRefinement->homographyComputeMethod();
      if (hcm == IRobustMatcherRefinement::HomographyComputeMethod::all_points){
        mView->setHomographyComputeMethod("All Points");
      } else if (hcm == IRobustMatcherRefinement::HomographyComputeMethod::ransac){
        mView->setHomographyComputeMethod("RANSAC");
        mView->setDistance(robustMatcherRefinement->distance());
        mView->setMaxIters(robustMatcherRefinement->maxIter());
      } else if (hcm == IRobustMatcherRefinement::HomographyComputeMethod::lmeds){
        mView->setHomographyComputeMethod("LMedS");
      } else if (hcm == IRobustMatcherRefinement::HomographyComputeMethod::rho){
        mView->setHomographyComputeMethod("RHO");
        mView->setDistance(robustMatcherRefinement->distance());
      }
    } else if (geometricTest == IRobustMatcherRefinement::GeometricTest::fundamental){
      mView->setGeometricTest("Fundamental Matrix");
      IRobustMatcherRefinement::FundamentalComputeMethod fcm =  robustMatcherRefinement->fundamentalComputeMethod();
      if (fcm == IRobustMatcherRefinement::FundamentalComputeMethod::lmeds){
        mView->setFundamentalComputeMethod("LMedS");
        mView->setConfidence(robustMatcherRefinement->confidence());
      } else if (fcm == IRobustMatcherRefinement::FundamentalComputeMethod::ransac){
        mView->setFundamentalComputeMethod("RANSAC");
        mView->setDistance(robustMatcherRefinement->distance());
        mView->setConfidence(robustMatcherRefinement->confidence());
      } else if (fcm == IRobustMatcherRefinement::FundamentalComputeMethod::algorithm_7_point){
        mView->setFundamentalComputeMethod("7-point algorithm");
      } else if (fcm == IRobustMatcherRefinement::FundamentalComputeMethod::algorithm_8_point){
        mView->setFundamentalComputeMethod("8-point algorithm");
      }
    } else if (geometricTest == IRobustMatcherRefinement::GeometricTest::essential){
      mView->setGeometricTest("Essential Matrix");
      mView->setConfidence(robustMatcherRefinement->confidence());
      IRobustMatcherRefinement::EssentialComputeMethod ecm = robustMatcherRefinement->essentialComputeMethod();
      if (ecm == IRobustMatcherRefinement::EssentialComputeMethod::ransac){
        mView->setEssentialComputeMethod("RANSAC");
        mView->setDistance(robustMatcherRefinement->distance());
      } else if (ecm == IRobustMatcherRefinement::EssentialComputeMethod::lmeds){
        mView->setEssentialComputeMethod("LMedS");
      }
    }
  } else {
    mView->setGeometricTest("Homography Matrix");
    mView->setHomographyComputeMethod("RANSAC");
    mView->setRatio(mSettingsModel->matchRatio());
    mView->setDistance(mSettingsModel->matchDistance());
    mView->setConfidence(mSettingsModel->matchConfidence());
    mView->setCrossMatching(mSettingsModel->matchCrossMatching());
  }

  if (Feature *descriptor = current_session->descriptor().get()){

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


  mView->setSessionName(current_session->name());
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

  emit finished();

  msgWarning("Processing has been canceled by the user");
}

void DescriptorMatcherPresenter::run()
{
  std::shared_ptr<Session> current_session = mProjectModel->currentSession();
  if (current_session == nullptr) {
    msgError("No active session found");
    return;
  }

  if(Match *matcher = current_session->matcher().get()){
    int i_ret = QMessageBox(QMessageBox::Warning,
                            tr("Previous results"),
                            tr("The previous results will be overwritten. Do you wish to continue?"),
                            QMessageBox::Yes|QMessageBox::No).exec();
    if (i_ret == QMessageBox::No) {
      return;
    }
  }

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
#ifdef HAVE_CUDA
    if (mSettingsModel->useCuda()){
      descriptorMatcher = std::make_shared<BruteForceMatcherCuda>(norm);
    } else {
#endif // HAVE_CUDA
      descriptorMatcher = std::make_shared<BruteForceMatcher>(norm);
#ifdef HAVE_CUDA
    }
#endif // HAVE_CUDA
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

  std::shared_ptr<RobustMatching> robustMatching(new RobustMatching(descriptorMatcher));

  robustMatching->setRatio(mView->ratio());
  robustMatching->setCrossCheck(mView->crossMatching());
  QString geometricTest = mView->geometricTest();
  if (geometricTest == "Homography Matrix"){
    robustMatching->setGeometricTest(IRobustMatcherRefinement::GeometricTest::homography);
    QString computeMethod = mView->homographyComputeMethod();
    IRobustMatcherRefinement::HomographyComputeMethod hcm = IRobustMatcherRefinement::HomographyComputeMethod::ransac;
    if (computeMethod.compare("All Points") == 0){
      hcm = IRobustMatcherRefinement::HomographyComputeMethod::all_points;
    } else if (computeMethod.compare("RANSAC") == 0){
      hcm = IRobustMatcherRefinement::HomographyComputeMethod::ransac;
    } else if (computeMethod.compare("LMedS") == 0){
      hcm = IRobustMatcherRefinement::HomographyComputeMethod::lmeds;
    } else if (computeMethod.compare("RHO") == 0){
      hcm = IRobustMatcherRefinement::HomographyComputeMethod::rho;
    }
    robustMatching->setHomographyComputeMethod(hcm);
  } else if (geometricTest == "Fundamental Matrix"){
    robustMatching->setGeometricTest(IRobustMatcherRefinement::GeometricTest::fundamental);
    QString computeMethod = mView->fundamentalComputeMethod();
    IRobustMatcherRefinement::FundamentalComputeMethod fcm = IRobustMatcherRefinement::FundamentalComputeMethod::ransac;
    if (computeMethod.compare("LMedS") == 0){
      fcm = IRobustMatcherRefinement::FundamentalComputeMethod::lmeds;
    } else if (computeMethod.compare("RANSAC") == 0){
      fcm = IRobustMatcherRefinement::FundamentalComputeMethod::ransac;
    } else if (computeMethod.compare("7-point algorithm") == 0){
      fcm = IRobustMatcherRefinement::FundamentalComputeMethod::algorithm_7_point;
    } else if (computeMethod.compare("8-point algorithm") == 0){
      fcm = IRobustMatcherRefinement::FundamentalComputeMethod::algorithm_8_point;
    }
    robustMatching->setFundamentalComputeMethod(fcm);
  } else if (geometricTest == "Essential Matrix"){
    robustMatching->setGeometricTest(IRobustMatcherRefinement::GeometricTest::essential);
    QString computeMethod = mView->essentialComputeMethod();
    IRobustMatcherRefinement::EssentialComputeMethod ecm = IRobustMatcherRefinement::EssentialComputeMethod::ransac;
    if (computeMethod.compare("RANSAC") == 0){
      ecm = IRobustMatcherRefinement::EssentialComputeMethod::ransac;
    } else if (computeMethod.compare("LMedS") == 0){
      ecm = IRobustMatcherRefinement::EssentialComputeMethod::lmeds;
    }
    robustMatching->setEssentialComputeMethod(ecm);
  }
  robustMatching->setDistance(mView->distance());
  robustMatching->setConfidence(mView->confidence());
  robustMatching->setMaxIters(mView->maxIters());

  mProjectModel->setRobustMatcherRefinement(robustMatching);

  /// Listado con los ficheros de puntos de interés de un par de fotogramas y el de las correspondencias entre ellos
  std::list<std::tuple<QString,QString,QString>> pairs;

  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){

    auto it2 = it;
    it2++;
    for (; it2 != mProjectModel->imageEnd(); it2++){

      QString features1 = mProjectModel->currentSession()->features((*it)->name());
      QString features2 = mProjectModel->currentSession()->features((*it2)->name());

      QString matches = mProjectModel->projectFolder();
      matches.append("\\").append(mProjectModel->currentSession()->name());
      matches.append("\\matches\\");

      QDir dir_out(matches);
      if (!dir_out.exists()) {
        dir_out.mkpath(".");
      }
      matches.append((*it)->name()).append("_").append((*it2)->name());
      QString matchesFormat = mSettingsModel->matchesFormat();
      if (matchesFormat.compare("Binary") == 0){
        matches.append(".bin");
      } else if (matchesFormat.compare("YML") == 0){
        matches.append(".yml");
      } else {
        matches.append(".xml");
      }

      std::shared_ptr<MatchingProcess> matcher(new MatchingProcess(features1, features2, matches, robustMatching));
      connect(matcher.get(), SIGNAL(matchCompute(QString,QString,QString)), this, SLOT(onMatchCompute(QString,QString,QString)));
      mMultiProcess->appendProcess(matcher);

      pairs.push_back(std::make_tuple(features1, features2, matches));
    }

  }

  /// Se identifican los puntos de paso entre todas las imagenes

  QString pass_points_ids = mProjectModel->projectFolder();
  pass_points_ids.append("\\").append(mProjectModel->currentSession()->name());
  pass_points_ids.append("\\matches\\pass_points_ids.txt");

  std::shared_ptr<PassPointsGroupingProcess> passPointsGroupingProcess(new PassPointsGroupingProcess(pairs, pass_points_ids));
  connect(passPointsGroupingProcess.get(), SIGNAL(writeFinished(QString)), this, SLOT(onPassPointsFinished(QString)));
  mMultiProcess->appendProcess(passPointsGroupingProcess);
  ///

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

void DescriptorMatcherPresenter::onPassPointsFinished(const QString &file)
{
  mProjectModel->setPassPoints(file);
}

} // namespace photomatch

