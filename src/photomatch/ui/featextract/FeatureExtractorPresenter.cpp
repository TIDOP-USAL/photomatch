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


#include "FeatureExtractorPresenter.h"

#include "photomatch/core/features/features.h"
#include "photomatch/core/features/agast.h"
#include "photomatch/core/features/akaze.h"
#include "photomatch/core/features/asift.h"
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR == 3 && CV_VERSION_MINOR > 2)
#include "photomatch/core/features/boost.h"
#endif
#include "photomatch/core/features/brief.h"
#include "photomatch/core/features/brisk.h"
#include "photomatch/core/features/d2net.h"
#include "photomatch/core/features/daisy.h"
#include "photomatch/core/features/fast.h"
#include "photomatch/core/features/freak.h"
#include "photomatch/core/features/gftt.h"
#include "photomatch/core/features/hog.h"
#include "photomatch/core/features/latch.h"
#include "photomatch/core/features/lucid.h"
#include "photomatch/core/features/lss.h"
#include "photomatch/core/features/msd.h"
#include "photomatch/core/features/mser.h"
#include "photomatch/core/features/kaze.h"
#include "photomatch/core/features/orb.h"
#include "photomatch/core/features/sift.h"
#include "photomatch/core/features/star.h"
#include "photomatch/core/features/surf.h"
#include "photomatch/core/features/vgg.h"
#include "photomatch/core/preprocess/decolor.h"

#include "photomatch/ui/featextract/FeatureExtractorView.h"
#include "photomatch/ui/ProjectModel.h"
#include "photomatch/ui/settings/SettingsModel.h"
#include "photomatch/ui/HelpDialog.h"
#include "photomatch/ui/utils/ProgressHandler.h"

#include "photomatch/widgets/AgastWidget.h"
#include "photomatch/widgets/AkazeWidget.h"
#include "photomatch/widgets/ASiftWidget.h"
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR == 3 && CV_VERSION_MINOR > 2)
#include "photomatch/widgets/BoostWidget.h"
#endif
#include "photomatch/widgets/BriefWidget.h"
#include "photomatch/widgets/BriskWidget.h"
#include "photomatch/widgets/D2NetWidget.h"
#include "photomatch/widgets/DaisyWidget.h"
#include "photomatch/widgets/FastWidget.h"
#include "photomatch/widgets/FreakWidget.h"
#include "photomatch/widgets/GfttWidget.h"
#include "photomatch/widgets/HogWidget.h"
#include "photomatch/widgets/KazeWidget.h"
#include "photomatch/widgets/LatchWidget.h"
#include "photomatch/widgets/LssWidget.h"
#include "photomatch/widgets/MsdWidget.h"
#include "photomatch/widgets/MserWidget.h"
#include "photomatch/widgets/OrbWidget.h"
#if (CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && CV_VERSION_MINOR >= 4)) || defined OPENCV_ENABLE_NONFREE
#include "photomatch/widgets/SiftWidget.h"
#endif
#include "photomatch/widgets/StarWidget.h"
#ifdef OPENCV_ENABLE_NONFREE
#include "photomatch/widgets/SurfWidget.h"
#endif
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR == 3 && CV_VERSION_MINOR > 2)
#include "photomatch/widgets/VggWidget.h"
#endif
#include "photomatch/widgets/KeypointsFilterWidget.h"

#include "photomatch/process/MultiProcess.h"
#include "photomatch/process/features/FeatureExtractorProcess.h"
#include "photomatch/process/preprocess/ImagePreprocess.h"

#include <tidop/core/messages.h>
#include <tidop/core/path.h>

#include <QFileInfo>
#include <QDir>
#include <QImageReader>
#include <QMessageBox>

namespace photomatch
{

FeatureExtractorPresenterImp::FeatureExtractorPresenterImp(FeatureExtractorView *view,
                                                           ProjectModel *projectModel,
                                                           SettingsModel *settingsModel)
  : FeatureExtractorPresenter(),
    mView(view),
    mProjectModel(projectModel),
    mSettingsModel(settingsModel),
    mHelp(nullptr),
    mAgastDetector(new AgastWidgetImp),
    mAkazeDetector(new AkazeWidgetImp),
    mASiftDetector(new ASiftWidgetImp),
    mBriskDetector(new BriskWidgetImp),
    mD2NetDetector(new D2NetWidgetImp),
    mFastDetector(new FastWidgetImp),
    mGfttDetector(new GfttWidgetImp),
    mKazeDetector(new KazeWidgetImp),
    mMsdDetector(new MsdWidgetImp),
    mMserDetector(new MserWidgetImp),
    mOrbDetector(new OrbWidgetImp),
#if (CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && CV_VERSION_MINOR >= 4)) || defined OPENCV_ENABLE_NONFREE
    mSiftDetector(new SiftWidgetImp),
#endif
    mStarDetector(new StarWidgetImp),
#ifdef OPENCV_ENABLE_NONFREE
    mSurfDetector(new SurfWidgetImp),
#endif
    mAkazeDescriptor(new AkazeWidgetImp),
    mASiftDescriptor(new ASiftWidgetImp),
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR == 3 && CV_VERSION_MINOR > 2)
    mBoostDescriptor(new BoostWidgetImp),
#endif
    mBriefDescriptor(new BriefWidgetImp),
    mBriskDescriptor(new BriskWidgetImp),
    mD2NetDescriptor(new D2NetWidgetImp),
    mDaisyDescriptor(new DaisyWidgetImp),
    mFreakDescriptor(new FreakWidgetImp),
    mHogDescriptor(new HogWidgetImp),
    mKazeDescriptor(new KazeWidgetImp),
    mLatchDescriptor(new LatchWidgetImp),
    mLssDescriptor(new LssWidgetImp),
    mOrbDescriptor(new OrbWidgetImp),
#if (CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && CV_VERSION_MINOR >= 4)) || defined OPENCV_ENABLE_NONFREE
    mSiftDescriptor(new SiftWidgetImp),
#endif
#ifdef OPENCV_ENABLE_NONFREE
  mSurfDescriptor(new SurfWidgetImp),
#endif
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR == 3 && CV_VERSION_MINOR > 2)
    mVggDescriptor(new VggWidgetImp),
#endif
    mKeypointsFilterWidget(new KeypointsFilterWidgetImp)
{
  this->init();
  this->initSignalAndSlots();
}

FeatureExtractorPresenterImp::~FeatureExtractorPresenterImp()
{
  if (mAgastDetector){
    delete mAgastDetector;
    mAgastDetector = nullptr;
  }

  if (mAkazeDetector){
    delete mAkazeDetector;
    mAkazeDetector = nullptr;
  }

  if(mASiftDetector) {
    delete mASiftDetector;
    mASiftDetector = nullptr;
  }

  if (mBriskDetector){
    delete mBriskDetector;
    mBriskDetector = nullptr;
  }

  if(mD2NetDetector) {
    delete mD2NetDetector;
    mD2NetDetector = nullptr;
  }

  if (mFastDetector){
    delete mFastDetector;
    mFastDetector = nullptr;
  }

  if (mGfttDetector){
    delete mGfttDetector;
    mGfttDetector = nullptr;
  }

  if (mKazeDetector){
    delete mKazeDetector;
    mKazeDetector = nullptr;
  }

  if (mMsdDetector){
    delete mMsdDetector;
    mMsdDetector = nullptr;
  }

  if (mMserDetector){
    delete mMserDetector;
    mMserDetector = nullptr;
  }

  if (mOrbDetector){
    delete mOrbDetector;
    mOrbDetector = nullptr;
  }

#if (CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && CV_VERSION_MINOR >= 4)) || defined OPENCV_ENABLE_NONFREE
  if (mSiftDetector){
    delete mSiftDetector;
    mSiftDetector = nullptr;
  }
#endif

  if (mStarDetector){
    delete mStarDetector;
    mStarDetector = nullptr;
  }

#ifdef OPENCV_ENABLE_NONFREE
  if (mSurfDetector){
    delete mSurfDetector;
    mSurfDetector = nullptr;
  }
#endif

  if (mAkazeDescriptor){
    delete mAkazeDescriptor;
    mAkazeDescriptor = nullptr;
  }

  if(mASiftDescriptor) {
    delete mASiftDescriptor;
    mASiftDescriptor = nullptr;
  }

#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR == 3 && CV_VERSION_MINOR > 2)
  if (mBoostDescriptor){
    delete mBoostDescriptor;
    mBoostDescriptor = nullptr;
  }
#endif

  if (mBriefDescriptor){
    delete mBriefDescriptor;
    mBriefDescriptor = nullptr;
  }

  if (mBriskDescriptor){
    delete mBriskDescriptor;
    mBriskDescriptor = nullptr;
  }


  if(mD2NetDescriptor) {
    delete mD2NetDescriptor;
    mD2NetDescriptor = nullptr;
  }

  if (mDaisyDescriptor){
    delete mDaisyDescriptor;
    mDaisyDescriptor = nullptr;
  }

  if (mFreakDescriptor){
    delete mFreakDescriptor;
    mFreakDescriptor = nullptr;
  }

  if (mHogDescriptor){
    delete mHogDescriptor;
    mHogDescriptor = nullptr;
  }

  if (mKazeDescriptor){
    delete mKazeDescriptor;
    mKazeDescriptor = nullptr;
  }

  if (mLatchDescriptor){
    delete mLatchDescriptor;
    mLatchDescriptor = nullptr;
  }

  if (mLssDescriptor){
    delete mLssDescriptor;
    mLssDescriptor = nullptr;
  }

  if (mOrbDescriptor){
    delete mOrbDescriptor;
    mOrbDescriptor = nullptr;
  }

#if (CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && CV_VERSION_MINOR >= 4)) || defined OPENCV_ENABLE_NONFREE
  if (mSiftDescriptor){
    delete mSiftDescriptor;
    mSiftDescriptor = nullptr;
  }

  if (mSurfDescriptor){
    delete mSurfDescriptor;
    mSurfDescriptor = nullptr;
  }
#endif

#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR == 3 && CV_VERSION_MINOR > 2)
  if (mVggDescriptor){
    delete mVggDescriptor;
    mVggDescriptor = nullptr;
  }
#endif

  if (mKeypointsFilterWidget){
    delete mKeypointsFilterWidget;
    mKeypointsFilterWidget = nullptr;
  }

}

void FeatureExtractorPresenterImp::init()
{
  mView->addKeypointDetector(mAgastDetector);
  mView->addKeypointDetector(mAkazeDetector);
  mView->addKeypointDetector(mASiftDetector);
  mView->addKeypointDetector(mBriskDetector);
  mView->addKeypointDetector(mD2NetDetector);
  mView->addKeypointDetector(mFastDetector);
  mView->addKeypointDetector(mGfttDetector);
  mView->addKeypointDetector(mKazeDetector);
  mView->addKeypointDetector(mMsdDetector);
  mView->addKeypointDetector(mMserDetector);
  mView->addKeypointDetector(mOrbDetector);
#if (CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && CV_VERSION_MINOR >= 4)) || defined OPENCV_ENABLE_NONFREE
  mView->addKeypointDetector(mSiftDetector);
#endif
  mView->addKeypointDetector(mStarDetector);
#ifdef OPENCV_ENABLE_NONFREE
  mView->addKeypointDetector(mSurfDetector);
#endif

  mView->addDescriptorExtractor(mAkazeDescriptor);
  mView->addDescriptorExtractor(mASiftDescriptor);
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR == 3 && CV_VERSION_MINOR > 2)
  mView->addDescriptorExtractor(mBoostDescriptor);
#endif
  mView->addDescriptorExtractor(mBriefDescriptor);
  mView->addDescriptorExtractor(mBriskDescriptor);
  mView->addDescriptorExtractor(mDaisyDescriptor);
  mView->addDescriptorExtractor(mD2NetDescriptor);
  mView->addDescriptorExtractor(mFreakDescriptor);
  mView->addDescriptorExtractor(mHogDescriptor);
  mView->addDescriptorExtractor(mKazeDescriptor);
  mView->addDescriptorExtractor(mLatchDescriptor);
  mView->addDescriptorExtractor(mLssDescriptor);
  mView->addDescriptorExtractor(mOrbDescriptor);
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR == 3 && CV_VERSION_MINOR > 2)
  mView->addDescriptorExtractor(mVggDescriptor);
#endif
#if (CV_VERSION_MAJOR > 4 || (CV_VERSION_MAJOR == 4 && CV_VERSION_MINOR >= 4)) || defined OPENCV_ENABLE_NONFREE
  mView->addDescriptorExtractor(mSiftDescriptor);
  this->setCurrentkeypointDetector(mSiftDescriptor->windowTitle());
#else
  this->setCurrentkeypointDetector(mOrbDescriptor->windowTitle());
#endif
#ifdef OPENCV_ENABLE_NONFREE  
  mView->addDescriptorExtractor(mSurfDescriptor);
#endif

  mView->addKeypointsFilter(mKeypointsFilterWidget);
  
}

void FeatureExtractorPresenterImp::initSignalAndSlots()
{
  connect(mView, SIGNAL(keypointDetectorChange(QString)),      this, SLOT(setCurrentkeypointDetector(QString)));
  connect(mView, SIGNAL(descriptorExtractorChange(QString)),   this, SLOT(setCurrentDescriptorExtractor(QString)));

  connect(mView, SIGNAL(run()),                                this, SLOT(run()));
  connect(mView, SIGNAL(help()),                               this, SLOT(help()));
}

void FeatureExtractorPresenterImp::help()
{
  if (mHelp){
    mHelp->setPage("feature_extraction.html");
    mHelp->show();
  }
}

void FeatureExtractorPresenterImp::open()
{
  std::shared_ptr<Session> current_session = mProjectModel->currentSession();
  if (current_session == nullptr) {
    msgError("No active session found");
    return;
  }

  if (auto detector = current_session->detector()){
    setCurrentkeypointDetector(detector->name());
  }
  if (auto descriptor = current_session->descriptor()){
    setCurrentDescriptorExtractor(descriptor->name());
  }

  setDetectorAndDescriptorProperties();

  mView->setSessionName(current_session->name());
  mView->exec();
}

void FeatureExtractorPresenterImp::setHelp(HelpDialog *help)
{
  mHelp = help;
}

void FeatureExtractorPresenterImp::onError(int code, const QString &msg)
{
  ProcessPresenter::onError(code, msg);

  if (mProgressHandler) {
    mProgressHandler->setDescription(tr("Feature detection and description error"));
  }
}

void FeatureExtractorPresenterImp::onFinished()
{
  ProcessPresenter::onFinished();

  if (mProgressHandler) {
    mProgressHandler->setDescription(tr("Feature detection and description finished"));
  }

  msgInfo("Feature detection and description finished.");
}

void FeatureExtractorPresenterImp::createProcess()
{
  std::shared_ptr<Session> current_session = mProjectModel->currentSession();
  if (current_session == nullptr) throw std::runtime_error("No active session found");
  

  std::shared_ptr<Preprocess> preprocess = current_session->preprocess();
  std::shared_ptr<ImageProcess> imageProcess;
  tl::Path preprocessed_path;

  if (preprocess == nullptr){
    imageProcess = std::make_shared<DecolorPreprocess>();
    mProjectModel->setMaxImageSize(2000);
    mProjectModel->setPreprocess(std::dynamic_pointer_cast<Preprocess>(imageProcess));
    preprocessed_path = mProjectModel->projectFolder().toStdWString();
    preprocessed_path.append(mProjectModel->currentSession()->name().toStdWString());
    preprocessed_path.append("preprocess");
    preprocessed_path.createDirectories();
  }

  auto detector = current_session->detector();
  auto descriptor = current_session->descriptor();
  if (detector && descriptor){
    int i_ret = QMessageBox(QMessageBox::Warning,
                            tr("Previous results"),
                            tr("The previous results will be overwritten. Do you wish to continue?"),
                            QMessageBox::Yes|QMessageBox::No).exec();
    if (i_ret == QMessageBox::No) {
      //return;
      throw std::runtime_error("Canceled by user");
    }
  }

  QString currentKeypointDetector = mView->currentKeypointDetector();
  QString currentDescriptorExtractor = mView->currentDescriptorExtractor();
  
  if(currentKeypointDetector == "D2Net") {

    std::shared_ptr<FeatureExtractorPython> featureExtractor = std::make_shared<D2NetDetectorDescriptor>(mD2NetDetector->multiscale());

    mProjectModel->setDetector(std::dynamic_pointer_cast<Feature>(featureExtractor));
    mProjectModel->setDescriptor(std::dynamic_pointer_cast<Feature>(featureExtractor));

    for(auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++) {
      QString fileName = (*it)->name();
      QString filePath = (*it)->path();
      QString preprocessed_image;

      if(imageProcess) {
        tl::Path preprocessed_image_path = preprocessed_path;
        preprocessed_image_path.append(tl::Path(filePath.toStdWString()).fileName());
        preprocessed_image = QString::fromStdWString(preprocessed_image_path.toWString());
        std::shared_ptr<ImagePreprocess> preprocess = createImagePreprocess(imageProcess, filePath, preprocessed_image);
        mMultiProcess->appendProcess(preprocess);
      } else {
        preprocessed_image = mProjectModel->currentSession()->preprocessImage(fileName);
      }

      QString features = featuresFile(fileName);
      double scale = imageScale(filePath);

      std::list<std::shared_ptr<KeyPointsFilterProcess>> keyPointsFiltersProcess = createKeyPointsFilterProcess(scale);

      std::shared_ptr<FeatureExtractorPythonTask> feat_extract(new FeatureExtractorPythonTask(preprocessed_image,
                                                                                              features,
                                                                                              scale,
                                                                                              featureExtractor,
                                                                                              keyPointsFiltersProcess));
      connect(feat_extract.get(), SIGNAL(featuresExtracted(QString)), this, SLOT(onFeaturesExtracted(QString)));

      mMultiProcess->appendProcess(feat_extract);
    }

  } else {
    std::shared_ptr<KeypointDetector> keypointDetector = makeKeypointDetector(currentKeypointDetector);
    std::shared_ptr<DescriptorExtractor> descriptorExtractor = makeDescriptorExtractor(currentDescriptorExtractor, 
                                                                                       currentKeypointDetector);
    mProjectModel->setDetector(std::dynamic_pointer_cast<Feature>(keypointDetector));
    mProjectModel->setDescriptor(std::dynamic_pointer_cast<Feature>(descriptorExtractor));

    for(auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++) {
      QString fileName = (*it)->name();
      QString filePath = (*it)->path();
      QString preprocessed_image;

      if(imageProcess) {
        tl::Path preprocessed_image_path = preprocessed_path;
        preprocessed_image_path.append(tl::Path(filePath.toStdWString()).fileName());
        preprocessed_image = QString::fromStdWString(preprocessed_image_path.toWString());
        std::shared_ptr<ImagePreprocess> preprocess = createImagePreprocess(imageProcess, filePath, preprocessed_image);
        mMultiProcess->appendProcess(preprocess);
      } else {
        preprocessed_image = mProjectModel->currentSession()->preprocessImage(fileName);
      }

      QString features = featuresFile(fileName);

      double scale = imageScale(filePath);

      std::list<std::shared_ptr<KeyPointsFilterProcess>> keyPointsFiltersProcess = createKeyPointsFilterProcess(scale);

      std::shared_ptr<FeatureExtractor> feat_extract(new FeatureExtractor(preprocessed_image,
                                                                          features,
                                                                          scale,
                                                                          keypointDetector,
                                                                          descriptorExtractor,
                                                                          keyPointsFiltersProcess));
      connect(feat_extract.get(), SIGNAL(featuresExtracted(QString)), this, SLOT(onFeaturesExtracted(QString)));

      mMultiProcess->appendProcess(feat_extract);
    }

  }

  if (mProgressHandler){
    mProgressHandler->setTitle("Computing Features...");
    mProgressHandler->setDescription("Computing Features...");
  }

  mView->hide();

  msgInfo("Starting Feature Extraction");
  QByteArray ba = currentKeypointDetector.toLocal8Bit();
  const char *keypoint_detector = ba.constData();
  msgInfo("  Feature Detector     :  %s", keypoint_detector);
  ba = currentDescriptorExtractor.toLocal8Bit();
  const char *descriptor_extractor = ba.constData();
  msgInfo("  DescriptorExtractor  :  %s", descriptor_extractor);

}

double FeatureExtractorPresenterImp::imageScale(const QString &image)
{
  double scale = 1;
  if(mProjectModel->fullImageSize() == false) {
    int maxSize = mProjectModel->maxImageSize();
    QImageReader imageReader(image);
    QSize size = imageReader.size();
    int w = size.width();
    int h = size.height();
    if(w > h) {
      scale = w / static_cast<double>(maxSize);
    } else {
      scale = h / static_cast<double>(maxSize);
    }
    if(scale < 1.) scale = 1.;
  }
  return scale;
}

std::list<std::shared_ptr<KeyPointsFilterProcess>> FeatureExtractorPresenterImp::createKeyPointsFilterProcess(double scale)
{
  std::list<std::shared_ptr<KeyPointsFilterProcess>> keyPointsFiltersProcess;

  if(mKeypointsFilterWidget->isActiveFilterBest()) {
    std::shared_ptr<KeyPointsFilterProcess> keyPointsFilterNBest = std::make_shared<KeyPointsFilterNBest>(mKeypointsFilterWidget->nPoints());
    keyPointsFiltersProcess.push_back(keyPointsFilterNBest);
  }
  if(mKeypointsFilterWidget->isActiveFilterSize()) {
    std::shared_ptr<KeyPointsFilterProcess> keyPointsFilterBySize = std::make_shared<KeyPointsFilterBySize>(mKeypointsFilterWidget->minSize() / scale,
                                                                                                            mKeypointsFilterWidget->maxSize() / scale);
    keyPointsFiltersProcess.push_back(keyPointsFilterBySize);
  }
  if(mKeypointsFilterWidget->isActiveRemoveDuplicated()) {
    std::shared_ptr<KeyPointsFilterProcess> keyPointsFilterRemoveDuplicated = std::make_shared<KeyPointsFilterRemoveDuplicated>();
    keyPointsFiltersProcess.push_back(keyPointsFilterRemoveDuplicated);
  }

  return keyPointsFiltersProcess;
}

QString FeatureExtractorPresenterImp::featuresFile(QString &fileName)
{
  QString features = mProjectModel->projectFolder();
  features.append("\\").append(mProjectModel->currentSession()->name());
  features.append("\\features\\");
  QDir dir_out(features);
  if(!dir_out.exists()) {
    dir_out.mkpath(".");
  }
  features.append(fileName);
  QString keypointsFormat = mSettingsModel->keypointsFormat();
  if(keypointsFormat.compare("Binary") == 0) {
    features.append(".bin");
  } else if(keypointsFormat.compare("YML") == 0) {
    features.append(".yml");
  } else {
    features.append(".xml");
  }
  return features;
}

std::shared_ptr<ImagePreprocess> FeatureExtractorPresenterImp::createImagePreprocess(std::shared_ptr<photomatch::ImageProcess> &imageProcess,
                                                         const QString &filePath,
                                                         QString &preprocessed_image)
{
  std::shared_ptr<ImagePreprocess> preprocess(new ImagePreprocess(filePath,
                                                                  preprocessed_image,
                                                                  imageProcess,
                                                                  2000));
  connect(preprocess.get(), SIGNAL(preprocessed(QString)), this, SLOT(onImagePreprocessed(QString)));
  
  return preprocess;
}

void FeatureExtractorPresenterImp::cancel()
{
  ProcessPresenter::cancel();
  msgWarning("Processing has been canceled by the user");
}

void FeatureExtractorPresenterImp::setDetectorAndDescriptorProperties()
{
  setAgastDetectorProperties();
  setAkazeDetectorPropierties();
  setASiftDetectorPropierties();
  setASiftDescriptorPropierties();
  setAkazeDescriptorProperties();
  setBoostDescriptorProperties();
  setBriefDescriptorProperties();
  setBriskDetectorProperties();
  setBriskDescriptorProperties();
  setD2NetDetectorProperties();
  setD2NetDescriptorProperties();
  setDaisyDescriptorProperties();
  setFastDetectorProperties();
  setFreakDescriptorProperties();
  setGfttDetectorProperties();
  setHogDescriptorProperties();
  setKazeDetectorProperties();
  setKazeDescriptorProperties();
  setLatchDescriptorProperties();
  setMsdDetectorProperties();
  setMserDetectorProperties();
  setOrbDetectorProperties();
  setOrbDescriptorProperties();
  setSiftDetectorProperties();
  setSiftDescriptorProperties();
  setStarDetectorProperties();
  setSurfDetectorProperties();
  setSurfDescriptorProperties();
  setVggDescriptorProperties();

  ///TODO: guardar en proyecto y configuración y recuperarlo desde aqui
  //mKeypointsFilterWidget->setNPoints();
  //mKeypointsFilterWidget->setMinSize();
  //mKeypointsFilterWidget->setMaxSize();
}

void FeatureExtractorPresenterImp::setAgastDetectorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *detector = current_session->detector().get();

    mAgastDetector->setThreshold(detector && detector->type() == Feature::Type::agast ?
                                 dynamic_cast<Agast *>(detector)->threshold() :
                                 mSettingsModel->agastThreshold());

    mAgastDetector->setDetectorType(detector && detector->type() == Feature::Type::agast ?
                                    dynamic_cast<Agast *>(detector)->detectorType() :
                                    mSettingsModel->agastDetectorType());

    mAgastDetector->setNonmaxSuppression(detector && detector->type() == Feature::Type::agast ?
                                         dynamic_cast<Agast *>(detector)->nonmaxSuppression() :
                                         mSettingsModel->agastNonmaxSuppression());

  }
}

void FeatureExtractorPresenterImp::setAkazeDetectorPropierties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *detector = current_session->detector().get();

    mAkazeDetector->setOctaves(detector && detector->type() == Feature::Type::akaze ?
                               dynamic_cast<Akaze *>(detector)->octaves() :
                               mSettingsModel->akazeOctaves());
    mAkazeDetector->setThreshold(detector && detector->type() == Feature::Type::akaze ?
                                 dynamic_cast<Akaze *>(detector)->threshold() :
                                 mSettingsModel->akazeThreshold());
    mAkazeDetector->setDiffusivity(detector && detector->type() == Feature::Type::akaze ?
                                   dynamic_cast<Akaze *>(detector)->diffusivity() :
                                   mSettingsModel->akazeDiffusivity());
    mAkazeDetector->setOctaveLayers(detector && detector->type() == Feature::Type::akaze ?
                                    dynamic_cast<Akaze *>(detector)->octaveLayers() :
                                    mSettingsModel->akazeOctaveLayers());
    mAkazeDetector->setDescriptorSize(detector && detector->type() == Feature::Type::akaze ?
                                      dynamic_cast<Akaze *>(detector)->descriptorSize() :
                                      mSettingsModel->akazeDescriptorSize());
    mAkazeDetector->setDescriptorType(detector && detector->type() == Feature::Type::akaze ?
                                      dynamic_cast<Akaze *>(detector)->descriptorType() :
                                      mSettingsModel->akazeDescriptorType());
    mAkazeDetector->setDescriptorChannels(detector && detector->type() == Feature::Type::akaze ?
                                          dynamic_cast<Akaze *>(detector)->descriptorChannels() :
                                          mSettingsModel->akazeDescriptorChannels());
  }
}

void FeatureExtractorPresenterImp::setASiftDetectorPropierties()
{
  if(std::shared_ptr<Session> current_session = mProjectModel->currentSession()) {

    auto detector = std::dynamic_pointer_cast<Sift>(current_session->detector());

    mSiftDetector->setSigma(detector && detector->type() == Feature::Type::asift ?
                              detector->sigma() :
                              mSettingsModel->asiftSigma());
    mSiftDetector->setOctaveLayers(detector && detector->type() == Feature::Type::asift ?
                                     detector->octaveLayers() :
                                     mSettingsModel->asiftOctaveLayers());
    mSiftDetector->setEdgeThreshold(detector && detector->type() == Feature::Type::asift ?
                                      detector->edgeThreshold() :
                                      mSettingsModel->asiftEdgeThreshold());
    mSiftDetector->setFeaturesNumber(detector && detector->type() == Feature::Type::asift ?
                                       detector->featuresNumber() :
                                       mSettingsModel->asiftFeaturesNumber());
    mSiftDetector->setContrastThreshold(detector && detector->type() == Feature::Type::asift ?
                                          detector->contrastThreshold() :
                                          mSettingsModel->asiftContrastThreshold());
  }
}

void FeatureExtractorPresenterImp::setASiftDescriptorPropierties()
{
  if(std::shared_ptr<Session> current_session = mProjectModel->currentSession()) {

    auto detector = std::dynamic_pointer_cast<Sift>(current_session->detector());

    mSiftDetector->setSigma(detector && detector->type() == Feature::Type::asift ?
                              detector->sigma() :
                              mSettingsModel->asiftSigma());
    mSiftDetector->setOctaveLayers(detector && detector->type() == Feature::Type::asift ?
                                     detector->octaveLayers() :
                                     mSettingsModel->asiftOctaveLayers());
    mSiftDetector->setEdgeThreshold(detector && detector->type() == Feature::Type::asift ?
                                      detector->edgeThreshold() :
                                      mSettingsModel->asiftEdgeThreshold());
    mSiftDetector->setFeaturesNumber(detector && detector->type() == Feature::Type::asift ?
                                       detector->featuresNumber() :
                                       mSettingsModel->asiftFeaturesNumber());
    mSiftDetector->setContrastThreshold(detector && detector->type() == Feature::Type::asift ?
                                          detector->contrastThreshold() :
                                          mSettingsModel->asiftContrastThreshold());
  }
}

void FeatureExtractorPresenterImp::setAkazeDescriptorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *descriptor = current_session->descriptor().get();

    mAkazeDescriptor->setOctaves(descriptor && descriptor->type() == Feature::Type::akaze ?
                                 dynamic_cast<Akaze *>(descriptor)->octaves() :
                                 mSettingsModel->akazeOctaves());
    mAkazeDescriptor->setThreshold(descriptor && descriptor->type() == Feature::Type::akaze ?
                                   dynamic_cast<Akaze *>(descriptor)->threshold() :
                                   mSettingsModel->akazeThreshold());
    mAkazeDescriptor->setDiffusivity(descriptor && descriptor->type() == Feature::Type::akaze ?
                                     dynamic_cast<Akaze *>(descriptor)->diffusivity() :
                                     mSettingsModel->akazeDiffusivity());
    mAkazeDescriptor->setOctaveLayers(descriptor && descriptor->type() == Feature::Type::akaze ?
                                      dynamic_cast<Akaze *>(descriptor)->octaveLayers() :
                                      mSettingsModel->akazeOctaveLayers());
    mAkazeDescriptor->setDescriptorSize(descriptor && descriptor->type() == Feature::Type::akaze ?
                                        dynamic_cast<Akaze *>(descriptor)->descriptorSize() :
                                        mSettingsModel->akazeDescriptorSize());
    mAkazeDescriptor->setDescriptorType(descriptor && descriptor->type() == Feature::Type::akaze ?
                                        dynamic_cast<Akaze *>(descriptor)->descriptorType() :
                                        mSettingsModel->akazeDescriptorType());
    mAkazeDescriptor->setDescriptorChannels(descriptor && descriptor->type() == Feature::Type::akaze ?
                                            dynamic_cast<Akaze *>(descriptor)->descriptorChannels() :
                                            mSettingsModel->akazeDescriptorChannels());
  }
}

void FeatureExtractorPresenterImp::setBoostDescriptorProperties()
{
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR == 3 && CV_VERSION_MINOR > 2)
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *descriptor = current_session->descriptor().get();

    mBoostDescriptor->setDescriptorType(descriptor && descriptor->type() == Feature::Type::boost ?
                                        dynamic_cast<Boost *>(descriptor)->descriptorType() :
                                        mSettingsModel->boostDescriptorType());
    mBoostDescriptor->setUseOrientation(descriptor && descriptor->type() == Feature::Type::boost ?
                                          dynamic_cast<Boost *>(descriptor)->useOrientation() :
                                          mSettingsModel->boostUseOrientation());
    mBoostDescriptor->setScaleFactor(descriptor && descriptor->type() == Feature::Type::boost ?
                                       dynamic_cast<Boost *>(descriptor)->scaleFactor() :
                                       mSettingsModel->boostScaleFactor());
  }
#endif
}

void FeatureExtractorPresenterImp::setBriefDescriptorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *descriptor = current_session->descriptor().get();

    mBriefDescriptor->setBytes(descriptor && descriptor->type() == Feature::Type::brief ?
                                 dynamic_cast<Brief *>(descriptor)->bytes() :
                                 mSettingsModel->briefBytes());
    mBriefDescriptor->setUseOrientation(descriptor && descriptor->type() == Feature::Type::brief ?
                                          dynamic_cast<Brief *>(descriptor)->useOrientation() :
                                          mSettingsModel->briefUseOrientation());
  }
}

void FeatureExtractorPresenterImp::setBriskDetectorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *detector = current_session->detector().get();

    mBriskDetector->setThreshold(detector && detector->type() == Feature::Type::brisk ?
                                   dynamic_cast<Brisk *>(detector)->threshold() :
                                   mSettingsModel->briskThreshold());
    mBriskDetector->setOctaves(detector && detector->type() == Feature::Type::brisk ?
                                 dynamic_cast<Brisk *>(detector)->octaves() :
                                 mSettingsModel->briskOctaves());
    mBriskDetector->setPatternScale(detector && detector->type() == Feature::Type::brisk ?
                                      dynamic_cast<Brisk *>(detector)->patternScale() :
                                      mSettingsModel->briskPatternScale());
  }
}

void FeatureExtractorPresenterImp::setBriskDescriptorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *descriptor = current_session->descriptor().get();

    mBriskDescriptor->setThreshold(descriptor && descriptor->type() == Feature::Type::brisk ?
                                     dynamic_cast<Brisk *>(descriptor)->threshold() :
                                     mSettingsModel->briskThreshold());
    mBriskDescriptor->setOctaves(descriptor && descriptor->type() == Feature::Type::brisk ?
                                   dynamic_cast<Brisk *>(descriptor)->threshold() :
                                   mSettingsModel->briskOctaves());
    mBriskDescriptor->setPatternScale(descriptor && descriptor->type() == Feature::Type::brisk ?
                                        dynamic_cast<Brisk *>(descriptor)->patternScale() :
                                        mSettingsModel->briskPatternScale());
  }
}

void FeatureExtractorPresenterImp::setD2NetDetectorProperties()
{
  if(std::shared_ptr<Session> current_session = mProjectModel->currentSession()) {

    auto detector = current_session->detector();

    mD2NetDetector->setMultiscale(detector && detector->type() == Feature::Type::d2net ?
                                  std::dynamic_pointer_cast<D2Net>(detector)->multiscale() :
                                  false);
  }
}

void FeatureExtractorPresenterImp::setD2NetDescriptorProperties()
{
  if(std::shared_ptr<Session> current_session = mProjectModel->currentSession()) {

    auto descriptor = current_session->descriptor();

    mD2NetDescriptor->setMultiscale(descriptor && descriptor->type() == Feature::Type::d2net ?
                                    std::dynamic_pointer_cast<D2Net>(descriptor)->multiscale() :
                                    false);
  }
}

void FeatureExtractorPresenterImp::setDaisyDescriptorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *descriptor = current_session->descriptor().get();

    mDaisyDescriptor->setRadius(descriptor && descriptor->type() == Feature::Type::daisy ?
                                  dynamic_cast<Daisy *>(descriptor)->radius() :
                                  mSettingsModel->daisyRadius());
    mDaisyDescriptor->setQRadius(descriptor && descriptor->type() == Feature::Type::daisy ?
                                   dynamic_cast<Daisy *>(descriptor)->qRadius() :
                                   mSettingsModel->daisyQRadius());
    mDaisyDescriptor->setQTheta(descriptor && descriptor->type() == Feature::Type::daisy ?
                                  dynamic_cast<Daisy *>(descriptor)->qTheta() :
                                  mSettingsModel->daisyQTheta());
    mDaisyDescriptor->setQHist(descriptor && descriptor->type() == Feature::Type::daisy ?
                                 dynamic_cast<Daisy *>(descriptor)->qHist() :
                                 mSettingsModel->daisyQHist());
    mDaisyDescriptor->setNorm(descriptor && descriptor->type() == Feature::Type::daisy ?
                                dynamic_cast<Daisy *>(descriptor)->norm() :
                                mSettingsModel->daisyNorm());
    mDaisyDescriptor->setInterpolation(descriptor && descriptor->type() == Feature::Type::daisy ?
                                         dynamic_cast<Daisy *>(descriptor)->interpolation() :
                                         mSettingsModel->daisyInterpolation());
    mDaisyDescriptor->setUseOrientation(descriptor && descriptor->type() == Feature::Type::daisy ?
                                          dynamic_cast<Daisy *>(descriptor)->useOrientation() :
                                          mSettingsModel->daisyUseOrientation());
  }
}

void FeatureExtractorPresenterImp::setFastDetectorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *detector = current_session->detector().get();

    mFastDetector->setThreshold(detector && detector->type() == Feature::Type::fast ?
                                  dynamic_cast<Fast *>(detector)->threshold() :
                                  mSettingsModel->fastThreshold());
    mFastDetector->setNonmaxSuppression(detector && detector->type() == Feature::Type::fast ?
                                          dynamic_cast<Fast *>(detector)->nonmaxSuppression() :
                                          mSettingsModel->fastNonmaxSuppression());
    mFastDetector->setDetectorType(detector && detector->type() == Feature::Type::fast ?
                                     dynamic_cast<Fast *>(detector)->detectorType() :
                                     mSettingsModel->fastdetectorType());
  }
}

void FeatureExtractorPresenterImp::setFreakDescriptorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *descriptor = current_session->descriptor().get();

    mFreakDescriptor->setOrientationNormalized(descriptor && descriptor->type() == Feature::Type::freak ?
                                                 dynamic_cast<Freak *>(descriptor)->orientationNormalized() :
                                                 mSettingsModel->freakOrientationNormalized());
    mFreakDescriptor->setScaleNormalized(descriptor && descriptor->type() == Feature::Type::freak ?
                                           dynamic_cast<Freak *>(descriptor)->scaleNormalized() :
                                           mSettingsModel->freakScaleNormalized());
    mFreakDescriptor->setPatternScale(descriptor && descriptor->type() == Feature::Type::freak ?
                                        dynamic_cast<Freak *>(descriptor)->patternScale() :
                                        mSettingsModel->freakPatternScale());
    mFreakDescriptor->setOctaves(descriptor && descriptor->type() == Feature::Type::freak ?
                                   dynamic_cast<Freak *>(descriptor)->octaves() :
                                   mSettingsModel->freakOctaves());
  }
}

void FeatureExtractorPresenterImp::setGfttDetectorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *detector = current_session->detector().get();

    mGfttDetector->setMaxFeatures(detector && detector->type() == Feature::Type::gftt ?
                                    dynamic_cast<Gftt *>(detector)->maxFeatures() :
                                    mSettingsModel->gfttMaxFeatures());
    mGfttDetector->setQualityLevel(detector && detector->type() == Feature::Type::gftt ?
                                     dynamic_cast<Gftt *>(detector)->qualityLevel() :
                                     mSettingsModel->gfttQualityLevel());
    mGfttDetector->setMinDistance(detector && detector->type() == Feature::Type::gftt ?
                                    dynamic_cast<Gftt *>(detector)->minDistance() :
                                    mSettingsModel->gfttMinDistance());
    mGfttDetector->setBlockSize(detector && detector->type() == Feature::Type::gftt ?
                                  dynamic_cast<Gftt *>(detector)->blockSize() :
                                  mSettingsModel->gfttBlockSize());
    mGfttDetector->setHarrisDetector(detector && detector->type() == Feature::Type::gftt ?
                                       dynamic_cast<Gftt *>(detector)->harrisDetector() :
                                       mSettingsModel->gfttHarrisDetector());
    mGfttDetector->setK(detector && detector->type() == Feature::Type::gftt ?
                          dynamic_cast<Gftt *>(detector)->k() :
                          mSettingsModel->gfttK());
  }
}

void FeatureExtractorPresenterImp::setHogDescriptorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *descriptor = current_session->descriptor().get();

    mHogDescriptor->setWinSize(descriptor && descriptor->type() == Feature::Type::hog ?
                                 dynamic_cast<Hog *>(descriptor)->winSize() :
                                 mSettingsModel->hogWinSize());
    mHogDescriptor->setBlockSize(descriptor && descriptor->type() == Feature::Type::hog ?
                                   dynamic_cast<Hog *>(descriptor)->blockSize() :
                                   mSettingsModel->hogBlockSize());
    mHogDescriptor->setBlockStride(descriptor && descriptor->type() == Feature::Type::hog ?
                                     dynamic_cast<Hog *>(descriptor)->blockStride() :
                                     mSettingsModel->hogBlockStride());
    mHogDescriptor->setCellSize(descriptor && descriptor->type() == Feature::Type::hog ?
                                  dynamic_cast<Hog *>(descriptor)->cellSize() :
                                  mSettingsModel->hogCellSize());
    mHogDescriptor->setNbins(descriptor && descriptor->type() == Feature::Type::hog ?
                               dynamic_cast<Hog *>(descriptor)->nbins() :
                               mSettingsModel->hogNbins());
    mHogDescriptor->setDerivAperture(descriptor && descriptor->type() == Feature::Type::hog ?
                                       dynamic_cast<Hog *>(descriptor)->derivAperture() :
                                       mSettingsModel->hogDerivAperture());
  }
}

void FeatureExtractorPresenterImp::setKazeDetectorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *detector = current_session->detector().get();

    mKazeDetector->setExtendedDescriptor(detector && detector->type() == Feature::Type::kaze ?
                                           dynamic_cast<Kaze *>(detector)->extendedDescriptor() :
                                           mSettingsModel->kazeExtendedDescriptor());
    mKazeDetector->setUprightDescriptor(detector && detector->type() == Feature::Type::kaze ?
                                dynamic_cast<Kaze *>(detector)->uprightDescriptor() :
                                mSettingsModel->kazeUpright());
    mKazeDetector->setThreshold(detector && detector->type() == Feature::Type::kaze ?
                                  dynamic_cast<Kaze *>(detector)->threshold() :
                                  mSettingsModel->kazeThreshold());
    mKazeDetector->setOctaves(detector && detector->type() == Feature::Type::kaze ?
                                dynamic_cast<Kaze *>(detector)->octaves() :
                                mSettingsModel->kazeOctaves());
    mKazeDetector->setOctaveLayers(detector && detector->type() == Feature::Type::kaze ?
                                     dynamic_cast<Kaze *>(detector)->octaveLayers() :
                                     mSettingsModel->kazeOctaveLayers());
    mKazeDetector->setDiffusivity(detector && detector->type() == Feature::Type::kaze ?
                                    dynamic_cast<Kaze *>(detector)->diffusivity() :
                                    mSettingsModel->kazeDiffusivity());
  }
}

void FeatureExtractorPresenterImp::setKazeDescriptorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *descriptor = current_session->descriptor().get();

    mKazeDescriptor->setExtendedDescriptor(descriptor && descriptor->type() == Feature::Type::kaze ?
                                             dynamic_cast<Kaze *>(descriptor)->extendedDescriptor() :
                                             mSettingsModel->kazeExtendedDescriptor());
    mKazeDescriptor->setUprightDescriptor(descriptor && descriptor->type() == Feature::Type::kaze ?
                                  dynamic_cast<Kaze *>(descriptor)->uprightDescriptor() :
                                  mSettingsModel->kazeUpright());
    mKazeDescriptor->setThreshold(descriptor && descriptor->type() == Feature::Type::kaze ?
                                    dynamic_cast<Kaze *>(descriptor)->threshold() :
                                    mSettingsModel->kazeThreshold());
    mKazeDescriptor->setOctaves(descriptor && descriptor->type() == Feature::Type::kaze ?
                                  dynamic_cast<Kaze *>(descriptor)->octaves() :
                                  mSettingsModel->kazeOctaves());
    mKazeDescriptor->setOctaveLayers(descriptor && descriptor->type() == Feature::Type::kaze ?
                                       dynamic_cast<Kaze *>(descriptor)->octaveLayers() :
                                       mSettingsModel->kazeOctaveLayers());
    mKazeDescriptor->setDiffusivity(descriptor && descriptor->type() == Feature::Type::kaze ?
                                      dynamic_cast<Kaze *>(descriptor)->diffusivity() :
                                      mSettingsModel->kazeDiffusivity());
  }
}

void FeatureExtractorPresenterImp::setLatchDescriptorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *descriptor = current_session->descriptor().get();

    mLatchDescriptor->setBytes(descriptor && descriptor->type() == Feature::Type::latch ?
                                 dynamic_cast<Latch *>(descriptor)->bytes() :
                                 mSettingsModel->latchBytes());
    mLatchDescriptor->setRotationInvariance(descriptor && descriptor->type() == Feature::Type::latch ?
                                              dynamic_cast<Latch *>(descriptor)->rotationInvariance() :
                                              mSettingsModel->latchRotationInvariance());
    mLatchDescriptor->setHalfSsdSize(descriptor && descriptor->type() == Feature::Type::latch ?
                                       dynamic_cast<Latch *>(descriptor)->halfSsdSize() :
                                       mSettingsModel->latchHalfSsdSize());
  }
}

void FeatureExtractorPresenterImp::setMsdDetectorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *detector = current_session->detector().get();

    mMsdDetector->setThresholdSaliency(detector && detector->type() == Feature::Type::msd ?
                                         dynamic_cast<Msd *>(detector)->thresholdSaliency() :
                                         mSettingsModel->msdThresholdSaliency());
    mMsdDetector->setPatchRadius(detector && detector->type() == Feature::Type::msd ?
                                  dynamic_cast<Msd *>(detector)->patchRadius() :
                                  mSettingsModel->msdPathRadius());
    mMsdDetector->setKNN(detector && detector->type() == Feature::Type::msd ?
                           dynamic_cast<Msd *>(detector)->knn() :
                           mSettingsModel->msdKnn());
    mMsdDetector->setAreaRadius(detector && detector->type() == Feature::Type::msd ?
                                  dynamic_cast<Msd *>(detector)->searchAreaRadius() :
                                  mSettingsModel->msdAreaRadius());
    mMsdDetector->setScaleFactor(detector && detector->type() == Feature::Type::msd ?
                                   dynamic_cast<Msd *>(detector)->scaleFactor() :
                                   mSettingsModel->msdScaleFactor());
    mMsdDetector->setNMSRadius(detector && detector->type() == Feature::Type::msd ?
                                 dynamic_cast<Msd *>(detector)->NMSRadius() :
                                 mSettingsModel->msdNMSRadius());
    mMsdDetector->setNScales(detector && detector->type() == Feature::Type::msd ?
                               dynamic_cast<Msd *>(detector)->nScales() :
                               mSettingsModel->msdNScales());
    mMsdDetector->setNMSScaleR(detector && detector->type() == Feature::Type::msd ?
                                 dynamic_cast<Msd *>(detector)->NMSScaleRadius() :
                                 mSettingsModel->msdNMSScaleR());
    mMsdDetector->setComputeOrientations(detector && detector->type() == Feature::Type::msd ?
                                           dynamic_cast<Msd *>(detector)->computeOrientation() :
                                           mSettingsModel->msdComputeOrientations());
    mMsdDetector->setAffineMSD(detector && detector->type() == Feature::Type::msd ?
                                 dynamic_cast<Msd *>(detector)->affineMSD() :
                                 mSettingsModel->msdAffineMSD());
    mMsdDetector->setTilts(detector && detector->type() == Feature::Type::msd ?
                             dynamic_cast<Msd *>(detector)->affineTilts() :
                             mSettingsModel->msdTilts());
  }
}

void FeatureExtractorPresenterImp::setMserDetectorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *detector = current_session->detector().get();

    mMserDetector->setDelta(detector && detector->type() == Feature::Type::mser ?
                              dynamic_cast<Mser *>(detector)->delta() :
                              mSettingsModel->mserDelta());
    mMserDetector->setMaxArea(detector && detector->type() == Feature::Type::mser ?
                                dynamic_cast<Mser *>(detector)->maxArea() :
                                mSettingsModel->mserMaxArea());
    mMserDetector->setMinArea(detector && detector->type() == Feature::Type::mser ?
                                dynamic_cast<Mser *>(detector)->minArea() :
                                mSettingsModel->mserMinArea());
    mMserDetector->setMaxVariation(detector && detector->type() == Feature::Type::mser ?
                                     dynamic_cast<Mser *>(detector)->maxVariation() :
                                     mSettingsModel->mserMaxVariation());
    mMserDetector->setMinDiversity(detector && detector->type() == Feature::Type::mser ?
                                     dynamic_cast<Mser *>(detector)->minDiversity() :
                                     mSettingsModel->mserMinDiversity());
    mMserDetector->setMaxEvolution(detector && detector->type() == Feature::Type::mser ?
                                     dynamic_cast<Mser *>(detector)->maxEvolution() :
                                     mSettingsModel->mserMaxEvolution());
    mMserDetector->setAreaThreshold(detector && detector->type() == Feature::Type::mser ?
                                      dynamic_cast<Mser *>(detector)->areaThreshold() :
                                      mSettingsModel->mserAreaThreshold());
    mMserDetector->setMinMargin(detector && detector->type() == Feature::Type::mser ?
                                  dynamic_cast<Mser *>(detector)->minMargin() :
                                  mSettingsModel->mserMinMargin());
    mMserDetector->setEdgeBlurSize(detector && detector->type() == Feature::Type::mser ?
                                     dynamic_cast<Mser *>(detector)->edgeBlurSize() :
                                     mSettingsModel->mserEdgeBlurSize());
  }
}

void FeatureExtractorPresenterImp::setOrbDetectorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *detector = current_session->detector().get();

    mOrbDetector->setScaleFactor(detector && detector->type() == Feature::Type::orb ?
                                   dynamic_cast<Orb *>(detector)->scaleFactor() :
                                   mSettingsModel->orbScaleFactor());
    mOrbDetector->setFeaturesNumber(detector && detector->type() == Feature::Type::orb ?
                                      dynamic_cast<Orb *>(detector)->featuresNumber() :
                                      mSettingsModel->orbFeaturesNumber());
    mOrbDetector->setLevelsNumber(detector && detector->type() == Feature::Type::orb ?
                                    dynamic_cast<Orb *>(detector)->levelsNumber() :
                                    mSettingsModel->orbLevelsNumber());
    mOrbDetector->setEdgeThreshold(detector && detector->type() == Feature::Type::orb ?
                                     dynamic_cast<Orb *>(detector)->edgeThreshold() :
                                     mSettingsModel->orbEdgeThreshold());
    mOrbDetector->setWTA_K(detector && detector->type() == Feature::Type::orb ?
                             dynamic_cast<Orb *>(detector)->wta_k() :
                             mSettingsModel->orbWta_k());
    mOrbDetector->setScoreType(detector && detector->type() == Feature::Type::orb ?
                                 dynamic_cast<Orb *>(detector)->scoreType() :
                                 mSettingsModel->orbScoreType());
    mOrbDetector->setPatchSize(detector && detector->type() == Feature::Type::orb ?
                                 dynamic_cast<Orb *>(detector)->patchSize() :
                                 mSettingsModel->orbPatchSize());
    mOrbDetector->setFastThreshold(detector && detector->type() == Feature::Type::orb ?
                                     dynamic_cast<Orb *>(detector)->fastThreshold() :
                                     mSettingsModel->orbFastThreshold());
  }
}

void FeatureExtractorPresenterImp::setOrbDescriptorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *descriptor = current_session->descriptor().get();

    mOrbDescriptor->setScaleFactor(descriptor && descriptor->type() == Feature::Type::orb ?
                                     dynamic_cast<Orb *>(descriptor)->scaleFactor() :
                                     mSettingsModel->orbScaleFactor());
    mOrbDescriptor->setFeaturesNumber(descriptor && descriptor->type() == Feature::Type::orb ?
                                        dynamic_cast<Orb *>(descriptor)->featuresNumber() :
                                        mSettingsModel->orbFeaturesNumber());
    mOrbDescriptor->setLevelsNumber(descriptor && descriptor->type() == Feature::Type::orb ?
                                      dynamic_cast<Orb *>(descriptor)->levelsNumber() :
                                      mSettingsModel->orbLevelsNumber());
    mOrbDescriptor->setEdgeThreshold(descriptor && descriptor->type() == Feature::Type::orb ?
                                       dynamic_cast<Orb *>(descriptor)->edgeThreshold() :
                                       mSettingsModel->orbEdgeThreshold());
    mOrbDescriptor->setWTA_K(descriptor && descriptor->type() == Feature::Type::orb ?
                               dynamic_cast<Orb *>(descriptor)->wta_k() :
                               mSettingsModel->orbWta_k());
    mOrbDescriptor->setScoreType(descriptor && descriptor->type() == Feature::Type::orb ?
                                   dynamic_cast<Orb *>(descriptor)->scoreType() :
                                   mSettingsModel->orbScoreType());
    mOrbDescriptor->setPatchSize(descriptor && descriptor->type() == Feature::Type::orb ?
                                   dynamic_cast<Orb *>(descriptor)->patchSize() :
                                   mSettingsModel->orbPatchSize());
    mOrbDescriptor->setFastThreshold(descriptor && descriptor->type() == Feature::Type::orb ?
                                       dynamic_cast<Orb *>(descriptor)->fastThreshold() :
                                       mSettingsModel->orbFastThreshold());
  }
}

void FeatureExtractorPresenterImp::setSiftDetectorProperties()
{
#ifdef OPENCV_ENABLE_NONFREE
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *detector = current_session->detector().get();

    mSiftDetector->setSigma(detector && detector->type() == Feature::Type::sift ?
                              dynamic_cast<Sift *>(detector)->sigma() :
                              mSettingsModel->siftSigma());
    mSiftDetector->setOctaveLayers(detector && detector->type() == Feature::Type::sift ?
                                     dynamic_cast<Sift *>(detector)->octaveLayers() :
                                     mSettingsModel->siftOctaveLayers());
    mSiftDetector->setEdgeThreshold(detector && detector->type() == Feature::Type::sift ?
                                      dynamic_cast<Sift *>(detector)->edgeThreshold() :
                                      mSettingsModel->siftEdgeThreshold());
    mSiftDetector->setFeaturesNumber(detector && detector->type() == Feature::Type::sift ?
                                       dynamic_cast<Sift *>(detector)->featuresNumber() :
                                       mSettingsModel->siftFeaturesNumber());
    mSiftDetector->setContrastThreshold(detector && detector->type() == Feature::Type::sift ?
                                          dynamic_cast<Sift *>(detector)->contrastThreshold() :
                                          mSettingsModel->siftContrastThreshold());
  }
#endif
}

void FeatureExtractorPresenterImp::setSiftDescriptorProperties()
{
#ifdef OPENCV_ENABLE_NONFREE
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *descriptor = current_session->descriptor().get();

    mSiftDescriptor->setSigma(descriptor && descriptor->type() == Feature::Type::sift ?
                                dynamic_cast<Sift *>(descriptor)->sigma() :
                                mSettingsModel->siftSigma());
    mSiftDescriptor->setOctaveLayers(descriptor && descriptor->type() == Feature::Type::sift ?
                                       dynamic_cast<Sift *>(descriptor)->octaveLayers() :
                                       mSettingsModel->siftOctaveLayers());
    mSiftDescriptor->setEdgeThreshold(descriptor && descriptor->type() == Feature::Type::sift ?
                                        dynamic_cast<Sift *>(descriptor)->edgeThreshold() :
                                        mSettingsModel->siftEdgeThreshold());
    mSiftDescriptor->setFeaturesNumber(descriptor && descriptor->type() == Feature::Type::sift ?
                                         dynamic_cast<Sift *>(descriptor)->featuresNumber() :
                                         mSettingsModel->siftFeaturesNumber());
    mSiftDescriptor->setContrastThreshold(descriptor && descriptor->type() == Feature::Type::sift ?
                                            dynamic_cast<Sift *>(descriptor)->contrastThreshold() :
                                            mSettingsModel->siftContrastThreshold());
  }
#endif
}

void FeatureExtractorPresenterImp::setStarDetectorProperties()
{
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *detector = current_session->detector().get();

    mStarDetector->setMaxSize(detector && detector->type() == Feature::Type::star ?
                                dynamic_cast<Star *>(detector)->maxSize() :
                                mSettingsModel->starMaxSize());
    mStarDetector->setResponseThreshold(detector && detector->type() == Feature::Type::star ?
                                          dynamic_cast<Star *>(detector)->responseThreshold() :
                                          mSettingsModel->starResponseThreshold());
    mStarDetector->setLineThresholdProjected(detector && detector->type() == Feature::Type::star ?
                                               dynamic_cast<Star *>(detector)->lineThresholdProjected() :
                                               mSettingsModel->starLineThresholdProjected());
    mStarDetector->setLineThresholdBinarized(detector && detector->type() == Feature::Type::star ?
                                               dynamic_cast<Star *>(detector)->lineThresholdBinarized() :
                                               mSettingsModel->starLineThresholdBinarized());
    mStarDetector->setSuppressNonmaxSize(detector && detector->type() == Feature::Type::star ?
                                           dynamic_cast<Star *>(detector)->suppressNonmaxSize() :
                                           mSettingsModel->starSuppressNonmaxSize());
  }
}

void FeatureExtractorPresenterImp::setSurfDetectorProperties()
{
#ifdef OPENCV_ENABLE_NONFREE
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *detector = current_session->detector().get();

    mSurfDetector->setOctaves(detector && detector->type() == Feature::Type::surf ?
                              dynamic_cast<Surf *>(detector)->octaves() :
                              mSettingsModel->surfOctaves());
    mSurfDetector->setOctaveLayers(detector && detector->type() == Feature::Type::surf ?
                                   dynamic_cast<Surf *>(detector)->octaveLayers() :
                                   mSettingsModel->surfOctaveLayers());
    mSurfDetector->seUpright(detector && detector->type() == Feature::Type::surf ?
                                      dynamic_cast<Surf *>(detector)->upright() :
                                      mSettingsModel->surfRotatedFeatures());
    mSurfDetector->setHessianThreshold(detector && detector->type() == Feature::Type::surf ?
                                       dynamic_cast<Surf *>(detector)->hessianThreshold() :
                                       mSettingsModel->surfHessianThreshold());
    mSurfDetector->setExtendedDescriptor(detector && detector->type() == Feature::Type::surf ?
                                         dynamic_cast<Surf *>(detector)->extendedDescriptor() :
                                         mSettingsModel->surfExtendedDescriptor());
  }
#endif
}

void FeatureExtractorPresenterImp::setSurfDescriptorProperties()
{
#ifdef OPENCV_ENABLE_NONFREE
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *descriptor = current_session->descriptor().get();

    mSurfDescriptor->setOctaves(descriptor && descriptor->type() == Feature::Type::surf ?
                                dynamic_cast<Surf *>(descriptor)->octaves() :
                                mSettingsModel->surfOctaves());
    mSurfDescriptor->setOctaveLayers(descriptor && descriptor->type() == Feature::Type::surf ?
                                     dynamic_cast<Surf *>(descriptor)->octaveLayers() :
                                     mSettingsModel->surfOctaveLayers());
    mSurfDescriptor->seUpright(descriptor && descriptor->type() == Feature::Type::surf ?
                                        dynamic_cast<Surf *>(descriptor)->upright() :
                                        mSettingsModel->surfRotatedFeatures());
    mSurfDescriptor->setHessianThreshold(descriptor && descriptor->type() == Feature::Type::surf ?
                                         dynamic_cast<Surf *>(descriptor)->hessianThreshold() :
                                         mSettingsModel->surfHessianThreshold());
    mSurfDescriptor->setExtendedDescriptor(descriptor && descriptor->type() == Feature::Type::surf ?
                                           dynamic_cast<Surf *>(descriptor)->extendedDescriptor() :
                                           mSettingsModel->surfExtendedDescriptor());
  }
#endif
}

void FeatureExtractorPresenterImp::setVggDescriptorProperties()
{
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR == 3 && CV_VERSION_MINOR > 2)
  if (std::shared_ptr<Session> current_session = mProjectModel->currentSession()){

    Feature *descriptor = current_session->descriptor().get();

    mVggDescriptor->setDescriptorType(descriptor && descriptor->type() == Feature::Type::vgg ?
                                          dynamic_cast<Vgg *>(descriptor)->descriptorType() :
                                          mSettingsModel->vggDescriptorType());
    mVggDescriptor->setScaleFactor(descriptor && descriptor->type() == Feature::Type::vgg ?
                                       dynamic_cast<Vgg *>(descriptor)->scaleFactor() :
                                       mSettingsModel->vggScaleFactor());
    mVggDescriptor->setSigma(descriptor && descriptor->type() == Feature::Type::vgg ?
                                          dynamic_cast<Vgg *>(descriptor)->sigma() :
                                          mSettingsModel->vggSigma());
    mVggDescriptor->setUseNormalizeDescriptor(descriptor && descriptor->type() == Feature::Type::vgg ?
                                          dynamic_cast<Vgg *>(descriptor)->useNormalizeDescriptor() :
                                          mSettingsModel->vggUseNormalizeDescriptor());
    mVggDescriptor->setUseNormalizeImage(descriptor && descriptor->type() == Feature::Type::vgg ?
                                          dynamic_cast<Vgg *>(descriptor)->useNormalizeImage() :
                                          mSettingsModel->vggUseNormalizeImage());
    mVggDescriptor->setUseScaleOrientation(descriptor && descriptor->type() == Feature::Type::vgg ?
                                       dynamic_cast<Vgg *>(descriptor)->useScaleOrientation() :
                                       mSettingsModel->vggUseScaleOrientation());
  }
#endif
}

std::shared_ptr<KeypointDetector> FeatureExtractorPresenterImp::makeKeypointDetector(const QString &keypointDetector)
{
  std::shared_ptr<KeypointDetector> keypoint_detector;

  if (keypointDetector.compare("AGAST") == 0) {
    keypoint_detector = std::make_shared<AgastDetector>(mAgastDetector->threshold(),
                                                       mAgastDetector->nonmaxSuppression(),
                                                       mAgastDetector->detectorType());
  } else if (keypointDetector.compare("AKAZE") == 0){
    keypoint_detector = std::make_shared<AkazeDetectorDescriptor>(mAkazeDetector->descriptorType(),
                                                                 mAkazeDetector->descriptorSize(),
                                                                 mAkazeDetector->descriptorChannels(),
                                                                 mAkazeDetector->threshold(),
                                                                 mAkazeDetector->octaves(),
                                                                 mAkazeDetector->octaveLayers(),
                                                                 mAkazeDetector->diffusivity());
  } 
#ifdef OPENCV_ENABLE_NONFREE
  else if(keypointDetector.compare("ASIFT") == 0) {
    keypoint_detector = std::make_shared<ASiftDetectorDescriptor>(mASiftDetector->featuresNumber(),
                                                                  mASiftDetector->octaveLayers(),
                                                                  mASiftDetector->contrastThreshold(),
                                                                  mASiftDetector->edgeThreshold(),
                                                                  mASiftDetector->sigma(),
                                                                  mASiftDetector->minTilt(),
                                                                  mASiftDetector->maxTilt());
  }
#endif  
  else if (keypointDetector.compare("BRISK") == 0){
    keypoint_detector = std::make_shared<BriskDetectorDescriptor>(mBriskDetector->threshold(),
                                                                 mBriskDetector->octaves(),
                                                                 mBriskDetector->patternScale());
  } else if (keypointDetector.compare("FAST") == 0){
    keypoint_detector = std::make_shared<FastDetector>(mFastDetector->threshold(),
                                                      mFastDetector->nonmaxSuppression(),
                                                      mFastDetector->detectorType());
  } else if (keypointDetector.compare("GFTT") == 0){
    keypoint_detector = std::make_shared<GfttDetector>(mGfttDetector->maxFeatures(),
                                                      mGfttDetector->qualityLevel(),
                                                      mGfttDetector->minDistance(),
                                                      mGfttDetector->blockSize(),
                                                      mGfttDetector->harrisDetector(),
                                                      mGfttDetector->k());
  } else if (keypointDetector.compare("KAZE") == 0){
    keypoint_detector = std::make_shared<KazeDetectorDescriptor>(mKazeDetector->extendedDescriptor(),
                                                                mKazeDetector->uprightDescriptor(),
                                                                mKazeDetector->threshold(),
                                                                mKazeDetector->octaves(),
                                                                mKazeDetector->octaveLayers(),
                                                                mKazeDetector->diffusivity());
  } else if (keypointDetector.compare("MSD") == 0){
    keypoint_detector = std::make_shared<MsdDetector>(mMsdDetector->thresholdSaliency(),
                                                     mMsdDetector->pathRadius(),
                                                     mMsdDetector->knn(),
                                                     mMsdDetector->areaRadius(),
                                                     mMsdDetector->scaleFactor(),
                                                     mMsdDetector->NMSRadius(),
                                                     mMsdDetector->nScales(),
                                                     mMsdDetector->NMSScaleR(),
                                                     mMsdDetector->computeOrientations(),
                                                     mMsdDetector->affineMSD(),
                                                     mMsdDetector->tilts());
  } else if (keypointDetector.compare("MSER") == 0){
    keypoint_detector = std::make_shared<MserDetector>(mMserDetector->delta(),
                                                      mMserDetector->minArea(),
                                                      mMserDetector->maxArea(),
                                                      mMserDetector->maxVariation(),
                                                      mMserDetector->minDiversity(),
                                                      mMserDetector->maxEvolution(),
                                                      mMserDetector->areaThreshold(),
                                                      mMserDetector->minMargin(),
                                                      mMserDetector->edgeBlurSize());
  } else if (keypointDetector.compare("ORB") == 0){
#ifdef HAVE_CUDA
    if (mSettingsModel->useCuda()){
      keypoint_detector = std::make_shared<OrbCudaDetectorDescriptor>(mOrbDetector->featuresNumber(),
                                                                     mOrbDetector->scaleFactor(),
                                                                     mOrbDetector->levelsNumber(),
                                                                     mOrbDetector->edgeThreshold(),
                                                                     mOrbDetector->wta_k(),
                                                                     mOrbDetector->scoreType(),
                                                                     mOrbDetector->patchSize(),
                                                                     mOrbDetector->fastThreshold());
    } else {
#endif // HAVE_CUDA
      keypoint_detector = std::make_shared<OrbDetectorDescriptor>(mOrbDetector->featuresNumber(),
                                                                 mOrbDetector->scaleFactor(),
                                                                 mOrbDetector->levelsNumber(),
                                                                 mOrbDetector->edgeThreshold(),
                                                                 mOrbDetector->wta_k(),
                                                                 mOrbDetector->scoreType(),
                                                                 mOrbDetector->patchSize(),
                                                                 mOrbDetector->fastThreshold());

#ifdef HAVE_CUDA
    }
#endif // HAVE_CUDA
  } 
#ifdef OPENCV_ENABLE_NONFREE
  else if (keypointDetector.compare("SIFT") == 0){
    keypoint_detector = std::make_shared<SiftDetectorDescriptor>(mSiftDetector->featuresNumber(),
                                                                mSiftDetector->octaveLayers(),
                                                                mSiftDetector->contrastThreshold(),
                                                                mSiftDetector->edgeThreshold(),
                                                                mSiftDetector->sigma());
  }
#endif
  else if (keypointDetector.compare("STAR") == 0){
    keypoint_detector = std::make_shared<StarDetector>(mStarDetector->maxSize(),
                                                      mStarDetector->responseThreshold(),
                                                      mStarDetector->lineThresholdProjected(),
                                                      mStarDetector->lineThresholdBinarized(),
                                                      mStarDetector->suppressNonmaxSize());
  } 
#ifdef OPENCV_ENABLE_NONFREE
  else if (keypointDetector.compare("SURF") == 0){
#ifdef HAVE_CUDA
    if (mSettingsModel->useCuda()){
      keypoint_detector = std::make_shared<SurfCudaDetectorDescriptor>(mSurfDetector->hessianThreshold(),
                                                                      mSurfDetector->octaves(),
                                                                      mSurfDetector->octaveLayers(),
                                                                      mSurfDetector->extendedDescriptor(),
                                                                      mSurfDetector->upright());
    } else {
#endif // HAVE_CUDA

    keypoint_detector = std::make_shared<SurfDetectorDescriptor>(mSurfDetector->hessianThreshold(),
                                                                mSurfDetector->octaves(),
                                                                mSurfDetector->octaveLayers(),
                                                                mSurfDetector->extendedDescriptor(),
                                                                mSurfDetector->upright());
#ifdef HAVE_CUDA
    }
#endif // HAVE_CUDA
  } 
#endif
  else {
    throw std::runtime_error("Keypoint Detector not found");
  }

  return keypoint_detector;
}

std::shared_ptr<DescriptorExtractor> FeatureExtractorPresenterImp::makeDescriptorExtractor(const QString &descriptorExtractor, 
                                                                                           const QString &keypointDetector)
{
  std::shared_ptr<DescriptorExtractor> descriptor_extractor;

  if (descriptorExtractor.compare("AKAZE") == 0){
    if (keypointDetector.compare("AKAZE") == 0){
      descriptor_extractor = std::make_shared<AkazeDetectorDescriptor>(mAkazeDetector->descriptorType(),
                                                                       mAkazeDetector->descriptorSize(),
                                                                       mAkazeDetector->descriptorChannels(),
                                                                       mAkazeDetector->threshold(),
                                                                       mAkazeDetector->octaves(),
                                                                       mAkazeDetector->octaveLayers(),
                                                                       mAkazeDetector->diffusivity());
    } else {
      descriptor_extractor = std::make_shared<AkazeDetectorDescriptor>(mAkazeDescriptor->descriptorType(),
                                                                       mAkazeDescriptor->descriptorSize(),
                                                                       mAkazeDescriptor->descriptorChannels(),
                                                                       mAkazeDescriptor->threshold(),
                                                                       mAkazeDescriptor->octaves(),
                                                                       mAkazeDescriptor->octaveLayers(),
                                                                       mAkazeDescriptor->diffusivity());
    }
  }
#ifdef OPENCV_ENABLE_NONFREE
  else if(descriptorExtractor.compare("ASIFT") == 0) {
    if(keypointDetector.compare("ASIFT") == 0) {
      descriptor_extractor = std::make_shared<ASiftDetectorDescriptor>(mASiftDetector->featuresNumber(),
                                                                       mASiftDetector->octaveLayers(),
                                                                       mASiftDetector->contrastThreshold(),
                                                                       mASiftDetector->edgeThreshold(),
                                                                       mASiftDetector->sigma(),
                                                                       mASiftDetector->minTilt(),
                                                                       mASiftDetector->maxTilt());
    } else {
      descriptor_extractor = std::make_shared<ASiftDetectorDescriptor>(mASiftDescriptor->featuresNumber(),
                                                                       mASiftDescriptor->octaveLayers(),
                                                                       mASiftDescriptor->contrastThreshold(),
                                                                       mASiftDescriptor->edgeThreshold(),
                                                                       mASiftDescriptor->sigma(),
                                                                       mASiftDetector->minTilt(),
                                                                       mASiftDetector->maxTilt());
    }
  }
#endif 
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR == 3 && CV_VERSION_MINOR > 2)
  else if (descriptorExtractor.compare("BOOST") == 0){
    descriptor_extractor = std::make_shared<BoostDescriptor>(mBoostDescriptor->descriptorType(),
                                                            mBoostDescriptor->useOrientation(),
                                                            mBoostDescriptor->scaleFactor());
  }
#endif
  else if (descriptorExtractor.compare("BRIEF") == 0){
    descriptor_extractor = std::make_shared<BriefDescriptor>(mBriefDescriptor->bytes(),
                                                            mBriefDescriptor->useOrientation());
  } else if (descriptorExtractor.compare("BRISK") == 0){
    descriptor_extractor = std::make_shared<BriskDetectorDescriptor>(mBriskDescriptor->threshold(),
                                                                    mBriskDescriptor->octaves(),
                                                                    mBriskDescriptor->patternScale());
  } else if (descriptorExtractor.compare("DAISY") == 0){
    descriptor_extractor = std::make_shared<DaisyDescriptor>(mDaisyDescriptor->radius(),
                                                             mDaisyDescriptor->qRadius(),
                                                             mDaisyDescriptor->qTheta(),
                                                             mDaisyDescriptor->qHist(),
                                                             mDaisyDescriptor->norm(),
                                                             mDaisyDescriptor->interpolation(),
                                                             mDaisyDescriptor->useOrientation());
  } else if (descriptorExtractor.compare("FREAK") == 0){
    descriptor_extractor = std::make_shared<FreakDescriptor>(mFreakDescriptor->orientationNormalized(),
                                                             mFreakDescriptor->scaleNormalized(),
                                                             mFreakDescriptor->patternScale(),
                                                             mFreakDescriptor->octaves());
  } else if (descriptorExtractor.compare("HOG") == 0){
    descriptor_extractor = std::make_shared<HogDescriptor>(mHogDescriptor->winSize(),
                                                           mHogDescriptor->blockSize(),
                                                           mHogDescriptor->blockStride(),
                                                           mHogDescriptor->cellSize(),
                                                           mHogDescriptor->nbins(),
                                                           mHogDescriptor->derivAperture());
  } else if (descriptorExtractor.compare("KAZE") == 0){
    if (keypointDetector.compare("KAZE") == 0){
      descriptor_extractor = std::make_shared<KazeDetectorDescriptor>(mKazeDetector->extendedDescriptor(),
                                                                      mKazeDetector->uprightDescriptor(),
                                                                      mKazeDetector->threshold(),
                                                                      mKazeDetector->octaves(),
                                                                      mKazeDetector->octaveLayers(),
                                                                      mKazeDetector->diffusivity());
    } else {
      descriptor_extractor = std::make_shared<KazeDetectorDescriptor>(mKazeDescriptor->extendedDescriptor(),
                                                                      mKazeDescriptor->uprightDescriptor(),
                                                                      mKazeDescriptor->threshold(),
                                                                      mKazeDescriptor->octaves(),
                                                                      mKazeDescriptor->octaveLayers(),
                                                                      mKazeDescriptor->diffusivity());
    }
  } else if (descriptorExtractor.compare("LATCH") == 0){
    descriptor_extractor = std::make_shared<LatchDescriptor>(mLatchDescriptor->bytes(),
                                                            mLatchDescriptor->rotationInvariance(),
                                                            mLatchDescriptor->halfSsdSize());
  } /* else if (descriptorExtractor.compare("LUCID") == 0){
    descriptor_extractor = std::make_shared<LucidDescriptor>(mLucidDescriptor->lucidKernel(),
                                                            mLucidDescriptor->blurKernel());
  }*/ else if (descriptorExtractor.compare("LSS") == 0){
    descriptor_extractor = std::make_shared<LssDescriptor>();
  } else if (descriptorExtractor.compare("ORB") == 0){
#ifdef HAVE_CUDA
    if (mSettingsModel->useCuda()){
      if (keypointDetector.compare("ORB") == 0){
        descriptor_extractor = std::make_shared<OrbCudaDetectorDescriptor>(mOrbDetector->featuresNumber(),
                                                                          mOrbDetector->scaleFactor(),
                                                                          mOrbDetector->levelsNumber(),
                                                                          mOrbDetector->edgeThreshold(),
                                                                          mOrbDetector->wta_k(),
                                                                          mOrbDetector->scoreType(),
                                                                          mOrbDetector->patchSize(),
                                                                          mOrbDetector->fastThreshold());
      } else {
        descriptor_extractor = std::make_shared<OrbCudaDetectorDescriptor>(mOrbDescriptor->featuresNumber(),
                                                                          mOrbDescriptor->scaleFactor(),
                                                                          mOrbDescriptor->levelsNumber(),
                                                                          mOrbDescriptor->edgeThreshold(),
                                                                          mOrbDescriptor->wta_k(),
                                                                          mOrbDescriptor->scoreType(),
                                                                          mOrbDescriptor->patchSize(),
                                                                          mOrbDescriptor->fastThreshold());
      }
    } else {
#endif // HAVE_CUDA
      if (keypointDetector.compare("ORB") == 0){
        descriptor_extractor = std::make_shared<OrbDetectorDescriptor>(mOrbDetector->featuresNumber(),
                                                                      mOrbDetector->scaleFactor(),
                                                                      mOrbDetector->levelsNumber(),
                                                                      mOrbDetector->edgeThreshold(),
                                                                      mOrbDetector->wta_k(),
                                                                      mOrbDetector->scoreType(),
                                                                      mOrbDetector->patchSize(),
                                                                      mOrbDetector->fastThreshold());
      } else {
        descriptor_extractor = std::make_shared<OrbDetectorDescriptor>(mOrbDescriptor->featuresNumber(),
                                                                      mOrbDescriptor->scaleFactor(),
                                                                      mOrbDescriptor->levelsNumber(),
                                                                      mOrbDescriptor->edgeThreshold(),
                                                                      mOrbDescriptor->wta_k(),
                                                                      mOrbDescriptor->scoreType(),
                                                                      mOrbDescriptor->patchSize(),
                                                                      mOrbDescriptor->fastThreshold());
      }
#ifdef HAVE_CUDA
    }
#endif // HAVE_CUDA
  } 
#ifdef OPENCV_ENABLE_NONFREE
  else if (descriptorExtractor.compare("SIFT") == 0){
    if (keypointDetector.compare("SIFT") == 0){
      descriptor_extractor = std::make_shared<SiftDetectorDescriptor>(mSiftDetector->featuresNumber(),
                                                                  mSiftDetector->octaveLayers(),
                                                                  mSiftDetector->contrastThreshold(),
                                                                  mSiftDetector->edgeThreshold(),
                                                                  mSiftDetector->sigma());
    } else {
      descriptor_extractor = std::make_shared<SiftDetectorDescriptor>(mSiftDescriptor->featuresNumber(),
                                                                     mSiftDescriptor->octaveLayers(),
                                                                     mSiftDescriptor->contrastThreshold(),
                                                                     mSiftDescriptor->edgeThreshold(),
                                                                     mSiftDescriptor->sigma());
    }
  } else if (descriptorExtractor.compare("SURF") == 0){
#ifdef HAVE_CUDA
    if (mSettingsModel->useCuda()){
      if (keypointDetector.compare("SURF") == 0){
        descriptor_extractor = std::make_shared<SurfCudaDetectorDescriptor>(mSurfDetector->hessianThreshold(),
                                                                           mSurfDetector->octaves(),
                                                                           mSurfDetector->octaveLayers(),
                                                                           mSurfDetector->extendedDescriptor(),
                                                                           mSurfDetector->upright());
      } else {
        descriptor_extractor = std::make_shared<SurfCudaDetectorDescriptor>(mSurfDescriptor->hessianThreshold(),
                                                                           mSurfDescriptor->octaves(),
                                                                           mSurfDescriptor->octaveLayers(),
                                                                           mSurfDescriptor->extendedDescriptor(),
                                                                           mSurfDescriptor->upright());
      }
    } else {
#endif // HAVE_CUDA
      if (keypointDetector.compare("SURF") == 0){
        descriptor_extractor = std::make_shared<SurfDetectorDescriptor>(mSurfDetector->hessianThreshold(),
                                                                       mSurfDetector->octaves(),
                                                                       mSurfDetector->octaveLayers(),
                                                                       mSurfDetector->extendedDescriptor(),
                                                                       mSurfDetector->upright());
      } else {
        descriptor_extractor = std::make_shared<SurfDetectorDescriptor>(mSurfDescriptor->hessianThreshold(),
                                                                       mSurfDescriptor->octaves(),
                                                                       mSurfDescriptor->octaveLayers(),
                                                                       mSurfDescriptor->extendedDescriptor(),
                                                                       mSurfDescriptor->upright());
      }
#ifdef HAVE_CUDA
    }
#endif // HAVE_CUDA
  } 
#endif
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR == 3 && CV_VERSION_MINOR > 2)
  else if (descriptorExtractor.compare("VGG") == 0){
    descriptor_extractor = std::make_shared<VggDescriptor>(mVggDescriptor->descriptorType(),
                                                          mVggDescriptor->scaleFactor(),
                                                          mVggDescriptor->sigma(),
                                                          mVggDescriptor->useNormalizeDescriptor(),
                                                          mVggDescriptor->useNormalizeImage(),
                                                          mVggDescriptor->useScaleOrientation());
  }
#endif
  else {
    throw std::runtime_error("Descriptor Extractor not found");
  }

  return descriptor_extractor;
}

void FeatureExtractorPresenterImp::setProgressHandler(ProgressHandler *progressHandler)
{
  mProgressHandler = progressHandler;
}

void FeatureExtractorPresenterImp::setCurrentkeypointDetector(const QString &keypointDetector)
{
  mView->setCurrentKeypointDetector(keypointDetector);

  mView->disableDescriptorExtractor("AKAZE");
  mView->disableDescriptorExtractor("KAZE");
  mView->disableDescriptorExtractor("ASIFT");
  mView->disableDescriptorExtractor("D2Net");
  mView->enableDescriptorExtractor("BRISK");
  mView->enableDescriptorExtractor("BOOST");
  mView->enableDescriptorExtractor("BRIEF");
  mView->enableDescriptorExtractor("BRISK");
  mView->enableDescriptorExtractor("DAISY");
  mView->enableDescriptorExtractor("FREAK");
  mView->enableDescriptorExtractor("HOG");
  mView->enableDescriptorExtractor("LATCH");
  mView->enableDescriptorExtractor("LSS");
  mView->enableDescriptorExtractor("ORB");
  mView->enableDescriptorExtractor("VGG");
  mView->enableDescriptorExtractor("SIFT");
  mView->enableDescriptorExtractor("SURF");

  if (keypointDetector.compare("AGAST") == 0){
#ifdef OPENCV_ENABLE_NONFREE
    mView->setCurrentDescriptorExtractor("SIFT");
#else
    mView->setCurrentDescriptorExtractor("ORB");
#endif
  } else if (keypointDetector.compare("AKAZE") == 0){
    mView->setCurrentDescriptorExtractor("AKAZE");
    mView->enableDescriptorExtractor("AKAZE");
    mView->enableDescriptorExtractor("KAZE");
  } else if (keypointDetector.compare("BRISK") == 0){
    mView->setCurrentDescriptorExtractor("BRISK");
    mView->disableDescriptorExtractor("HOG");
  } else if (keypointDetector.compare("FAST") == 0){
#ifdef OPENCV_ENABLE_NONFREE
    mView->setCurrentDescriptorExtractor("SIFT");
#else
    mView->setCurrentDescriptorExtractor("ORB");
#endif
  } else if (keypointDetector.compare("GFTT") == 0){
#ifdef OPENCV_ENABLE_NONFREE
    mView->setCurrentDescriptorExtractor("SIFT");
#else
    mView->setCurrentDescriptorExtractor("ORB");
#endif
  } else if (keypointDetector.compare("KAZE") == 0){
    mView->setCurrentDescriptorExtractor("KAZE");
    mView->enableDescriptorExtractor("AKAZE");
    mView->enableDescriptorExtractor("KAZE");
  } else if (keypointDetector.compare("MSD") == 0){
#ifdef OPENCV_ENABLE_NONFREE
    mView->setCurrentDescriptorExtractor("SIFT");
#else
    mView->setCurrentDescriptorExtractor("ORB");
#endif
  } else if (keypointDetector.compare("MSER") == 0){
#ifdef OPENCV_ENABLE_NONFREE
    mView->setCurrentDescriptorExtractor("SIFT");
#else
    mView->setCurrentDescriptorExtractor("ORB");
#endif
  } else if (keypointDetector.compare("ORB") == 0){
    mView->setCurrentDescriptorExtractor("ORB");
  }
#ifdef OPENCV_ENABLE_NONFREE
  else if (keypointDetector.compare("SIFT") == 0){
    mView->setCurrentDescriptorExtractor("SIFT");
    mView->disableDescriptorExtractor("ORB");
  }
#endif
  else if (keypointDetector.compare("STAR") == 0){
#ifdef OPENCV_ENABLE_NONFREE
    mView->setCurrentDescriptorExtractor("SIFT");
#else
    mView->setCurrentDescriptorExtractor("ORB");
#endif
  }
#ifdef OPENCV_ENABLE_NONFREE
  else if (keypointDetector.compare("SURF") == 0){
    mView->setCurrentDescriptorExtractor("SURF");
  }
#endif
  else if(keypointDetector.compare("ASIFT") == 0 ||
          keypointDetector.compare("D2Net") == 0) {
    if(keypointDetector.compare("ASIFT") == 0) {
      mView->setCurrentDescriptorExtractor("ASIFT");
      mView->disableDescriptorExtractor("D2Net");
    } else if (keypointDetector.compare("D2Net") == 0){
      mView->setCurrentDescriptorExtractor("D2Net");
      mView->disableDescriptorExtractor("ASIFT");
    }
    
    mView->disableDescriptorExtractor("AKAZE");
    mView->disableDescriptorExtractor("BRISK");
    mView->disableDescriptorExtractor("BOOST");
    mView->disableDescriptorExtractor("BRIEF");
    mView->disableDescriptorExtractor("BRISK");
    mView->disableDescriptorExtractor("DAISY");
    mView->disableDescriptorExtractor("FREAK");
    mView->disableDescriptorExtractor("HOG");
    mView->disableDescriptorExtractor("KAZE");
    mView->disableDescriptorExtractor("LATCH");
    mView->disableDescriptorExtractor("LSS");
    mView->disableDescriptorExtractor("ORB");
    mView->disableDescriptorExtractor("VGG");
    mView->disableDescriptorExtractor("SIFT");
    mView->disableDescriptorExtractor("SURF");
  }
}

void FeatureExtractorPresenterImp::setCurrentDescriptorExtractor(const QString &descriptorExtractor)
{
#if CV_VERSION_MAJOR >= 4 || (CV_VERSION_MAJOR == 3 && CV_VERSION_MINOR > 2)
  if (descriptorExtractor.compare("BOOST") == 0 ||
      descriptorExtractor.compare("VGG") == 0){
    QString keypointDetector = mView->currentKeypointDetector();
    if (keypointDetector.compare("AGAST") == 0 ||
        keypointDetector.compare("AKAZE") == 0 ||
        keypointDetector.compare("BRISK") == 0 ||
        keypointDetector.compare("FAST") == 0 ||
        keypointDetector.compare("MSD") == 0){
      mBoostDescriptor->setScaleFactor(5.0);
    } else if (keypointDetector.compare("KAZE") == 0 ||
               keypointDetector.compare("SURF") == 0) {
      mBoostDescriptor->setScaleFactor(6.25);
    } else if (keypointDetector.compare("SIFT") == 0) {
     mBoostDescriptor->setScaleFactor(6.75);
   } else if (keypointDetector.compare("ORB") == 0) {
      mBoostDescriptor->setScaleFactor(1.50);
   }
  }
#endif
  mView->setCurrentDescriptorExtractor(descriptorExtractor);
}

void FeatureExtractorPresenterImp::onImagePreprocessed(const QString &image)
{
  mProjectModel->addPreprocessedImage(image);
  emit imagePreprocessed(image);
}

void FeatureExtractorPresenterImp::onFeaturesExtracted(const QString &features)
{
  mProjectModel->addFeatures(features);
  emit featuresExtracted(features);
}

} // namespace photomatch
