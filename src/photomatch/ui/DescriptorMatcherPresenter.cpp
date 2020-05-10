/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#include "DescriptorMatcherPresenter.h"

#include "photomatch/core/features/matcher.h"
//#include "photomatch/ui/DescriptorMatcherModel.h"
#include "photomatch/ui/DescriptorMatcherView.h"
#include "photomatch/ui/ProjectModel.h"
#include "photomatch/ui/SettingsModel.h"
#include "photomatch/ui/HelpDialog.h"
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

DescriptorMatcherPresenterImp::DescriptorMatcherPresenterImp(DescriptorMatcherView *view,
                                                             ProjectModel *projectModel,
                                                             SettingsModel *settingsModel)
  : DescriptorMatcherPresenter(),
    mView(view),
    mProjectModel(projectModel),
    mSettingsModel(settingsModel),
    mHelp(nullptr),
    mMultiProcess(new MultiProcess(true)),
    mProgressHandler(nullptr)
{
  this->init();
  this->initSignalAndSlots();
}

DescriptorMatcherPresenterImp::~DescriptorMatcherPresenterImp()
{
  if (mMultiProcess){
    delete mMultiProcess;
    mMultiProcess = nullptr;
  }
}

void DescriptorMatcherPresenterImp::help()
{
  if (mHelp){
    mHelp->setPage("feature_matching.html");
    mHelp->show();
  }
}

void DescriptorMatcherPresenterImp::open()
{
  std::shared_ptr<Session> current_session = mProjectModel->currentSession();
  if (current_session == nullptr) {
    msgError("No active session found");
    return;
  }

  if (MatchingMethod *matcher = current_session->matchingMethod().get()){
    if (matcher->type() == MatchingMethod::Type::brute_force){
      mView->setMatchingMethod("Brute-Force");
      BruteForceMatcherImp::Norm norm = dynamic_cast<BruteForceMatcher *>(matcher)->normType();
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

  if (MatchingStrategy *matchingStrategy = current_session->matchingStrategy().get()){

    if (matchingStrategy->strategy() == MatchingStrategy::Strategy::robust_matching) {
      RobustMatcher *robustMatcherRefinement = dynamic_cast<RobustMatcher *>(matchingStrategy);
      mView->setRatio(robustMatcherRefinement->ratio());
      mView->setCrossMatching(robustMatcherRefinement->crossCheck());

      RobustMatcher::GeometricTest geometricTest = robustMatcherRefinement->geometricTest();
      if (geometricTest == RobustMatcher::GeometricTest::homography){
        mView->setGeometricTest("Homography Matrix");
        mView->setConfidence(robustMatcherRefinement->confidence());
        RobustMatcher::HomographyComputeMethod hcm = robustMatcherRefinement->homographyComputeMethod();
        if (hcm == RobustMatcher::HomographyComputeMethod::all_points){
          mView->setHomographyComputeMethod("All Points");
        } else if (hcm == RobustMatcher::HomographyComputeMethod::ransac){
          mView->setHomographyComputeMethod("RANSAC");
          mView->setDistance(robustMatcherRefinement->distance());
          mView->setMaxIters(robustMatcherRefinement->maxIter());
        } else if (hcm == RobustMatcher::HomographyComputeMethod::lmeds){
          mView->setHomographyComputeMethod("LMedS");
        } else if (hcm == RobustMatcher::HomographyComputeMethod::rho){
          mView->setHomographyComputeMethod("RHO");
          mView->setDistance(robustMatcherRefinement->distance());
        }
      } else if (geometricTest == RobustMatcher::GeometricTest::fundamental){
        mView->setGeometricTest("Fundamental Matrix");
        RobustMatcher::FundamentalComputeMethod fcm =  robustMatcherRefinement->fundamentalComputeMethod();
        if (fcm == RobustMatcher::FundamentalComputeMethod::lmeds){
          mView->setFundamentalComputeMethod("LMedS");
          mView->setConfidence(robustMatcherRefinement->confidence());
        } else if (fcm == RobustMatcher::FundamentalComputeMethod::ransac){
          mView->setFundamentalComputeMethod("RANSAC");
          mView->setDistance(robustMatcherRefinement->distance());
          mView->setConfidence(robustMatcherRefinement->confidence());
        } else if (fcm == RobustMatcher::FundamentalComputeMethod::algorithm_7_point){
          mView->setFundamentalComputeMethod("7-point algorithm");
        } else if (fcm == RobustMatcher::FundamentalComputeMethod::algorithm_8_point){
          mView->setFundamentalComputeMethod("8-point algorithm");
        }
      } else if (geometricTest == RobustMatcher::GeometricTest::essential){
        mView->setGeometricTest("Essential Matrix");
        mView->setConfidence(robustMatcherRefinement->confidence());
        RobustMatcher::EssentialComputeMethod ecm = robustMatcherRefinement->essentialComputeMethod();
        if (ecm == RobustMatcher::EssentialComputeMethod::ransac){
          mView->setEssentialComputeMethod("RANSAC");
          mView->setDistance(robustMatcherRefinement->distance());
        } else if (ecm == RobustMatcher::EssentialComputeMethod::lmeds){
          mView->setEssentialComputeMethod("LMedS");
        }
      }

    } else {
      Gms *gms = dynamic_cast<Gms *>(matchingStrategy);
      ///TODO: leer de proyecto o de configuración
      mView->setGmsScale(gms->scale());
      mView->setGmsRotation(gms->rotation());
      mView->setGmsThreshold(gms->threshold());
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
      QString descriptorType = dynamic_cast<Akaze *>(descriptor)->descriptorType();

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
      int wta_k = dynamic_cast<Orb *>(descriptor)->wta_k();
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

void DescriptorMatcherPresenterImp::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void DescriptorMatcherPresenterImp::init()
{
}

void DescriptorMatcherPresenterImp::initSignalAndSlots()
{
  connect(mView, SIGNAL(run()),      this, SLOT(run()));
  connect(mView, SIGNAL(help()),     this, SLOT(help()));
}

void DescriptorMatcherPresenterImp::setProgressHandler(ProgressHandler *progressHandler)
{
  mProgressHandler = progressHandler;
}

void DescriptorMatcherPresenterImp::cancel()
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

void DescriptorMatcherPresenterImp::run()
{
  std::shared_ptr<Session> current_session = mProjectModel->currentSession();
  if (current_session == nullptr) {
    msgError("No active session found");
    return;
  }

  if(MatchingMethod *matcher = current_session->matchingMethod().get()){
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
  BruteForceMatcherImp::Norm norm = BruteForceMatcherProperties::Norm::l2;
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
    if (mSettingsModel->useCuda() && norm != BruteForceMatcherProperties::Norm::hamming2){
      descriptorMatcher = std::make_shared<BruteForceMatcherCuda>(norm);
    } else {
#endif // HAVE_CUDA
      descriptorMatcher = std::make_shared<BruteForceMatcherImp>(norm);
#ifdef HAVE_CUDA
    }
#endif // HAVE_CUDA
  } else if (matchingMethod.compare("FLANN") == 0){

    FlannMatcherImp::Index index;
    Feature *descriptor = mProjectModel->currentSession()->descriptor().get();
    if (descriptor->type() == Feature::Type::orb ||
        descriptor->type() == Feature::Type::brief ||
        descriptor->type() == Feature::Type::freak ||
        descriptor->type() == Feature::Type::latch ||
        descriptor->type() == Feature::Type::lucid ||
        descriptor->type() == Feature::Type::brisk){
      index = FlannMatcherImp::Index::lsh;
    } else if (descriptor->type() == Feature::Type::akaze) {
      QString descriptorType = dynamic_cast<Akaze *>(descriptor)->descriptorType();
      if (descriptorType.compare("KAZE") == 0 ||
          descriptorType.compare("KAZE_UPRIGHT") == 0){
        index = FlannMatcherImp::Index::kdtree;
      } else if (descriptorType.compare("MLDB") == 0 ||
                 descriptorType.compare("MLDB_UPRIGHT") == 0){
        index = FlannMatcherImp::Index::lsh;
      }
    } else {
      index = FlannMatcherImp::Index::kdtree;
    }

    descriptorMatcher = std::make_shared<FlannMatcherImp>(index);
  } else {
    ///TODO: error
    return;
  }

  mProjectModel->setMatcher(std::dynamic_pointer_cast<MatchingMethod>(descriptorMatcher));

  std::shared_ptr<MatchingAlgorithm> matchingAlgorithm;

  QString matchingStrategy = mView->matchingStrategy();
  if (matchingStrategy.compare("Robust Matching") == 0){
    matchingAlgorithm = std::make_shared<RobustMatchingImp>(descriptorMatcher);
    std::shared_ptr<RobustMatchingImp> robustMatchingStrategy = std::dynamic_pointer_cast<RobustMatchingImp>(matchingAlgorithm);
    robustMatchingStrategy->setRatio(mView->ratio());
    robustMatchingStrategy->setCrossCheck(mView->crossMatching());
    QString geometricTest = mView->geometricTest();
    if (geometricTest == "Homography Matrix"){
      robustMatchingStrategy->setGeometricTest(RobustMatcher::GeometricTest::homography);
      QString computeMethod = mView->homographyComputeMethod();
      RobustMatcher::HomographyComputeMethod hcm = RobustMatcher::HomographyComputeMethod::ransac;
      if (computeMethod.compare("All Points") == 0){
        hcm = RobustMatcher::HomographyComputeMethod::all_points;
      } else if (computeMethod.compare("RANSAC") == 0){
        hcm = RobustMatcher::HomographyComputeMethod::ransac;
      } else if (computeMethod.compare("LMedS") == 0){
        hcm = RobustMatcher::HomographyComputeMethod::lmeds;
      } else if (computeMethod.compare("RHO") == 0){
        hcm = RobustMatcher::HomographyComputeMethod::rho;
      }
      robustMatchingStrategy->setHomographyComputeMethod(hcm);
    } else if (geometricTest == "Fundamental Matrix"){
      robustMatchingStrategy->setGeometricTest(RobustMatcher::GeometricTest::fundamental);
      QString computeMethod = mView->fundamentalComputeMethod();
      RobustMatcher::FundamentalComputeMethod fcm = RobustMatcher::FundamentalComputeMethod::ransac;
      if (computeMethod.compare("LMedS") == 0){
        fcm = RobustMatcher::FundamentalComputeMethod::lmeds;
      } else if (computeMethod.compare("RANSAC") == 0){
        fcm = RobustMatcher::FundamentalComputeMethod::ransac;
      } else if (computeMethod.compare("7-point algorithm") == 0){
        fcm = RobustMatcher::FundamentalComputeMethod::algorithm_7_point;
      } else if (computeMethod.compare("8-point algorithm") == 0){
        fcm = RobustMatcher::FundamentalComputeMethod::algorithm_8_point;
      }
      robustMatchingStrategy->setFundamentalComputeMethod(fcm);
    } else if (geometricTest == "Essential Matrix"){
      robustMatchingStrategy->setGeometricTest(RobustMatcher::GeometricTest::essential);
      QString computeMethod = mView->essentialComputeMethod();
      RobustMatcher::EssentialComputeMethod ecm = RobustMatcher::EssentialComputeMethod::ransac;
      if (computeMethod.compare("RANSAC") == 0){
        ecm = RobustMatcher::EssentialComputeMethod::ransac;
      } else if (computeMethod.compare("LMedS") == 0){
        ecm = RobustMatcher::EssentialComputeMethod::lmeds;
      }
      robustMatchingStrategy->setEssentialComputeMethod(ecm);
    }
    robustMatchingStrategy->setDistance(mView->distance());
    robustMatchingStrategy->setConfidence(mView->confidence());
    robustMatchingStrategy->setMaxIters(mView->maxIters());
  } else {
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR >= 3 && CV_VERSION_MINOR >= 4 && CV_VERSION_REVISION >= 1)
    matchingAlgorithm = std::make_shared<GsmImp>(descriptorMatcher,
                                                 mView->gmsRotation(),
                                                 mView->gmsScale(),
                                                 mView->gmsThreshold());
#else
    int i_ret = QMessageBox(QMessageBox::Information,
                            tr("GMS not supported"),
                            tr("GMS (Grid-based Motion Statistics) not supported in the current OpenCV version"),
                            QMessageBox::Ok).exec();
    if (i_ret == QMessageBox::Ok) {
      return;
    }
#endif
  }


  /// TODO: Guardar en proyecto
  //mProjectModel->setRobustMatcherRefinement(matchingAlgorithm);

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

      std::shared_ptr<MatchingProcess> matcher(new MatchingProcess(features1,
                                                                   features2,
                                                                   matches,
                                                                   matchingAlgorithm,
                                                                   (*it)->path(),
                                                                   (*it2)->path()));
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

void DescriptorMatcherPresenterImp::onError(int code, const QString &msg)
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

void DescriptorMatcherPresenterImp::onFinished()
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

void DescriptorMatcherPresenterImp::onMatchCompute(const QString &left,
                                                   const QString &right,
                                                   const QString &match)
{
  mProjectModel->addMatches(left, right, match);
  emit matchCompute(match);
}

void DescriptorMatcherPresenterImp::onPassPointsFinished(const QString &file)
{
  mProjectModel->setPassPoints(file);
}

} // namespace photomatch

