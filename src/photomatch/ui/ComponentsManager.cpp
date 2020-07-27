#include "ComponentsManager.h"

#include "photomatch/core/utils.h"
#include "photomatch/core/project.h"

#include "photomatch/ui/MainWindowModel.h"
#include "photomatch/ui/MainWindowView.h"
#include "photomatch/ui/MainWindowPresenter.h"

#include "photomatch/ui/ProjectModel.h"

#include "photomatch/ui/createproj/NewProjectPresenter.h"
#include "photomatch/ui/createproj/NewProjectView.h"

#include "photomatch/ui/createsession/NewSessionPresenter.h"
#include "photomatch/ui/createsession/NewSessionView.h"

#include "photomatch/ui/exportfeat/ExportFeaturesModel.h"
#include "photomatch/ui/exportfeat/ExportFeaturesView.h"
#include "photomatch/ui/exportfeat/ExportFeaturesPresenter.h"
#include "photomatch/ui/exportmatch/ExportMatchesModel.h"
#include "photomatch/ui/exportmatch/ExportMatchesView.h"
#include "photomatch/ui/exportmatch/ExportMatchesPresenter.h"

#include "photomatch/ui/settings/SettingsModel.h"
#include "photomatch/ui/settings/SettingsView.h"
#include "photomatch/ui/settings/SettingsPresenter.h"

#include "photomatch/ui/preprocess/PreprocessView.h"
#include "photomatch/ui/preprocess/PreprocessPresenter.h"
#include "photomatch/ui/featextract/FeatureExtractorView.h"
#include "photomatch/ui/featextract/FeatureExtractorPresenter.h"
#include "photomatch/ui/featmatch/DescriptorMatcherView.h"
#include "photomatch/ui/featmatch/DescriptorMatcherPresenter.h"

#include "photomatch/ui/featviewer/FeaturesViewerModel.h"
#include "photomatch/ui/featviewer/FeaturesViewerView.h"
#include "photomatch/ui/featviewer/FeaturesViewerPresenter.h"

#include "photomatch/ui/matchviewer/MatchViewerModel.h"
#include "photomatch/ui/matchviewer/MatchViewerView.h"
#include "photomatch/ui/matchviewer/MatchViewerPresenter.h"

#include "photomatch/ui/multiview/MultiViewModel.h"
#include "photomatch/ui/multiview/MultiViewView.h"
#include "photomatch/ui/multiview/MultiViewPresenter.h"

#include "photomatch/ui/groundtruth/GroundTruthModel.h"
#include "photomatch/ui/groundtruth/GroundTruthView.h"
#include "photomatch/ui/groundtruth/GroundTruthPresenter.h"

#include "photomatch/ui/homography/HomographyViewerModel.h"
#include "photomatch/ui/homography/HomographyViewerView.h"
#include "photomatch/ui/homography/HomographyViewerPresenter.h"

#include "photomatch/ui/curves/CurvesViewerModel.h"
#include "photomatch/ui/curves/CurvesViewerView.h"
#include "photomatch/ui/curves/CurvesViewerPresenter.h"

#include "photomatch/ui/repeatability/RepeatabilityModel.h"
#include "photomatch/ui/repeatability/RepeatabilityView.h"
#include "photomatch/ui/repeatability/RepeatabilityPresenter.h"

#include "photomatch/ui/AboutDialog.h"
#include "photomatch/ui/HelpDialog.h"

#include "photomatch/ui/utils/ProgressHandler.h"
#include "photomatch/ui/utils/ProgressDialog.h"

#include <QProgressBar>

namespace photomatch
{

ComponentsManager::ComponentsManager(QObject *parent)
  : QObject(parent),
    mMainWindowView(nullptr),
    mMainWindowModel(nullptr),
    mMainWindowPresenter(nullptr),
    mProject(new ProjectImp),
    mProjectController(new ProjectControllerImp),
    mProjectModel(nullptr),
    mNewProjectPresenter(nullptr),
    mNewSessionPresenter(nullptr),
    mExportFeaturesPresenter(nullptr),
    mExportFeaturesModel(nullptr),
    mExportMatchesPresenter(nullptr),
    mExportMatchesModel(nullptr),
    mSettings(new SettingsImp),
    mSettingsRW(new SettingsControllerImp),
    mSettingsModel(nullptr),
    mSettingsPresenter(nullptr),
    mPreprocessPresenter(nullptr),
    mFeatureExtractorPresenter(nullptr),
    mDescriptorMatcherPresenter(nullptr),
    mFeaturesViewerPresenter(nullptr),
    mFeaturesViewerModel(nullptr),
    mMatchesViewerPresenter(nullptr),
    mMatchesViewerModel(nullptr),
    mMultiviewMatchingAssessmentModel(nullptr),
    mMultiviewMatchingAssessmentPresenter(nullptr),
    mGroundTruthPresenter(nullptr),
    mGroundTruthModel(nullptr),
    mHomographyViewerPresenter(nullptr),
    mHomographyViewerModel(nullptr),
    mCurvesPRViewerPresenter(nullptr),
    mCurvesPRViewerModel(nullptr),
    mCurvesROCViewerPresenter(nullptr),
    mCurvesROCViewerModel(nullptr),
    mCurvesDETViewerPresenter(nullptr),
    mCurvesDETViewerModel(nullptr),
    mRepeatabilityPresenter(nullptr),
    mRepeatabilityModel(nullptr),
    mAboutDialog(nullptr),
    mHelpDialog(nullptr),
    mProgressHandler(nullptr),
    mProgressDialog(nullptr)
{

}

ComponentsManager::~ComponentsManager()
{

  if (mMainWindowPresenter){
    delete mMainWindowPresenter;
    mMainWindowPresenter = nullptr;
  }

  if (mProject) {
    delete mProject;
    mProject = nullptr;
  }

  if (mProjectController) {
    delete mProjectController;
    mProjectController =nullptr;
  }

  if (mProjectModel){
    delete mProjectModel;
    mProjectModel = nullptr;
  }

  if (mNewProjectPresenter) {
    delete mNewProjectPresenter;
    mNewProjectPresenter = nullptr;
  }

  if (mNewSessionPresenter){
    delete mNewSessionPresenter;
    mNewSessionPresenter = nullptr;
  }

  if (mExportFeaturesModel){
    delete mExportFeaturesModel;
    mExportFeaturesModel = nullptr;
  }

  if (mExportFeaturesPresenter){
    delete mExportFeaturesPresenter;
    mExportFeaturesPresenter = nullptr;
  }

  if (mExportMatchesModel){
    delete mExportMatchesModel;
    mExportMatchesModel = nullptr;
  }

  if (mExportMatchesPresenter){
    delete mExportMatchesPresenter;
    mExportMatchesPresenter = nullptr;
  }

  if (mSettings){
    delete mSettings;
    mSettings = nullptr;
  }

  if (mSettingsRW){
    delete mSettingsRW;
    mSettingsRW = nullptr;
  }

  if (mSettingsModel){
    delete mSettingsModel;
    mSettingsModel = nullptr;
  }

  if (mSettingsPresenter){
    delete mSettingsPresenter;
    mSettingsPresenter = nullptr;
  }

  if (mPreprocessPresenter){
    delete mPreprocessPresenter;
    mPreprocessPresenter = nullptr;
  }

  if (mFeatureExtractorPresenter){
    delete mFeatureExtractorPresenter;
    mFeatureExtractorPresenter = nullptr;
  }

  if (mDescriptorMatcherPresenter){
    delete mDescriptorMatcherPresenter;
    mDescriptorMatcherPresenter = nullptr;
  }

  if (mFeaturesViewerPresenter){
    delete mFeaturesViewerPresenter;
    mFeaturesViewerPresenter = nullptr;
  }

  if (mFeaturesViewerModel){
    delete mFeaturesViewerModel;
    mFeaturesViewerModel = nullptr;
  }

  if (mMatchesViewerPresenter){
    delete mMatchesViewerPresenter;
    mMatchesViewerPresenter = nullptr;
  }

  if (mMatchesViewerModel){
    delete mMatchesViewerModel;
    mMatchesViewerModel = nullptr;
  }

  if (mMultiviewMatchingAssessmentModel){
    delete mMultiviewMatchingAssessmentModel;
    mMultiviewMatchingAssessmentModel = nullptr;
  }

  if (mMultiviewMatchingAssessmentPresenter){
    delete mMultiviewMatchingAssessmentPresenter;
    mMultiviewMatchingAssessmentPresenter = nullptr;
  }

  if (mGroundTruthPresenter){
    delete mGroundTruthPresenter;
    mGroundTruthPresenter = nullptr;
  }

  if (mGroundTruthModel){
    delete mGroundTruthModel;
    mGroundTruthModel = nullptr;
  }

  if (mHomographyViewerPresenter){
    delete mHomographyViewerPresenter;
    mHomographyViewerPresenter = nullptr;
  }

  if (mHomographyViewerModel){
    delete mHomographyViewerModel;
    mHomographyViewerModel = nullptr;
  }

  if (mCurvesPRViewerPresenter){
    delete mCurvesPRViewerPresenter;
    mCurvesPRViewerPresenter = nullptr;
  }

  if (mCurvesPRViewerModel){
    delete mCurvesPRViewerModel;
    mCurvesPRViewerModel = nullptr;
  }

  if (mCurvesROCViewerPresenter){
    delete mCurvesROCViewerPresenter;
    mCurvesROCViewerPresenter = nullptr;
  }

  if (mCurvesROCViewerModel){
    delete mCurvesROCViewerModel;
    mCurvesROCViewerModel = nullptr;
  }

  if (mCurvesDETViewerPresenter){
    delete mCurvesDETViewerPresenter;
    mCurvesDETViewerPresenter = nullptr;
  }

  if (mCurvesDETViewerModel){
    delete mCurvesDETViewerModel;
    mCurvesDETViewerModel = nullptr;
  }

  if (mRepeatabilityPresenter){
    delete mRepeatabilityPresenter;
    mRepeatabilityPresenter = nullptr;
  }

  if (mRepeatabilityModel){
    delete mRepeatabilityModel;
    mRepeatabilityModel = nullptr;
  }

  if (mProgressHandler){
    delete mProgressHandler;
    mProgressHandler = nullptr;
  }

  if (mProgressDialog){
    delete mProgressDialog;
    mProgressDialog = nullptr;
  }

  if (mMainWindowView){
    delete mMainWindowView;
    mMainWindowView = nullptr;
  }

  if (mMainWindowModel){
    delete mMainWindowModel;
    mMainWindowModel = nullptr;
  }
}

MainWindowView *ComponentsManager::mainWindowView()
{
  if (mMainWindowView == nullptr){
    mMainWindowView = new MainWindowView;
  }
  return mMainWindowView;
}

MainWindowModel *ComponentsManager::mainWindowModel()
{
  if (mMainWindowModel == nullptr){
    mMainWindowModel = new MainWindowModel;
  }
  return mMainWindowModel;
}

MainWindowPresenter *ComponentsManager::mainWindowPresenter()
{
  if (mMainWindowPresenter == nullptr){
    mMainWindowPresenter = new MainWindowPresenter(this->mainWindowView(),
                                                   this->mainWindowModel(),
                                                   this->projectModel(),
                                                   this->settingsModel());

    mMainWindowPresenter->setHelp(this->helpDialog());

    this->mainWindowConnectSignalsSlots();
  }
  return mMainWindowPresenter;
}

void ComponentsManager::mainWindowConnectSignalsSlots()
{
  connect(mMainWindowPresenter, &MainWindowPresenter::openNewProjectDialog,
          this, &ComponentsManager::initAndOpenNewProjectDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openNewSessionDialog,
          this, &ComponentsManager::initAndOpenNewSessionDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openPreprocessDialog,
          this, &ComponentsManager::initAndOpenPreprocessDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openFeatureExtractionDialog,
          this, &ComponentsManager::initAndOpenFeatureExtractionDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openFeatureMatchingDialog,
          this, &ComponentsManager::initAndOpenFeatureMatchingDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openKeypointsViewerDialogFromSession,
          this, &ComponentsManager::initAndOpenKeypointsViewerDialogFromSession);
  connect(mMainWindowPresenter, &MainWindowPresenter::openKeypointsViewerDialogFromSessionAndImage,
          this, &ComponentsManager::initAndOpenKeypointsViewerDialogFromSessionAndImage);
  connect(mMainWindowPresenter, &MainWindowPresenter::openMatchesViewerDialogFromSession,
          this, &ComponentsManager::initAndOpenMatchesViewerDialogFromSession);
  connect(mMainWindowPresenter, &MainWindowPresenter::openMatchesViewerDialogFromSessionAndImages,
          this, &ComponentsManager::initAndOpenMatchesViewerDialogFromSessionAndImages);
  connect(mMainWindowPresenter, &MainWindowPresenter::openExportFeaturesDialog,
          this, &ComponentsManager::initAndOpenExportFeaturesDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openExportMatchesDialog,
          this, &ComponentsManager::initAndOpenExportMatchesDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openGroundTruthEditorDialog,
          this, &ComponentsManager::initAndOpenGroundTruthEditorDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openHomographyViewerDialog,
          this, &ComponentsManager::initAndOpenHomographyViewerDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openPRCurvesViewerDialog,
          this, &ComponentsManager::initAndOpenPRCurvesViewerDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openROCCurvesViewerDialog,
          this, &ComponentsManager::initAndOpenROCCurvesViewerDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openDETCurvesViewerDialog,
          this, &ComponentsManager::initAndOpenDETCurvesViewerDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openAboutDialog,
          this, &ComponentsManager::initAndOpenAboutDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openSettingsDialog,
          this, &ComponentsManager::initAndOpenSettingsDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openViewSettingsDialog,
          this, &ComponentsManager::initAndOpenViewSettingsDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openQualityControlSettingsDialog,
          this, &ComponentsManager::initAndOpenQualityControlDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openToolSettingsDialog,
          this, &ComponentsManager::initAndOpenToolSettingsDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openMultiviewMatchingAssessmentDialog,
          this, &ComponentsManager::initAndOpenMultiviewMatchingAssessmentDialog);
}

ProjectModel *ComponentsManager::projectModel()
{
  if (mProjectModel == nullptr){
    mProjectModel = new ProjectModelImp(mProjectController, mProject);
  }
  return mProjectModel;
}

SettingsModel *ComponentsManager::settingsModel()
{
  if (mSettingsModel == nullptr){
    mSettingsModel = new SettingsModelImp(mSettings, mSettingsRW);
    mSettingsModel->read();
  }
  return mSettingsModel;
}

SettingsPresenter *ComponentsManager::settingsPresenter()
{
  if (mSettingsPresenter == nullptr){
//    bool bUseGPU = cudaEnabled(8.0, 5.0);
    SettingsView *view = new SettingsViewImp(this->mainWindowView());
//    if (!bUseGPU) {
//      this->settingsModel()->setUseCuda(false);
//      view->setCudaEnabled(false);
//    }
    mSettingsPresenter = new SettingsPresenterImp(view, this->settingsModel());
  }
  return mSettingsPresenter;
}

NewProjectPresenter *ComponentsManager::newProjectPresenter()
{
  if (mNewProjectPresenter == nullptr){
    NewProjectView *newProjectView = new NewProjectViewImp(this->mainWindowView());
    mNewProjectPresenter = new NewProjectPresenterImp(newProjectView, this->projectModel());
  }
  return mNewProjectPresenter;
}

NewSessionPresenter *ComponentsManager::newSessionPresenter()
{
  if (mNewSessionPresenter == nullptr){
    NewSessionView *newSessionView = new NewSessionViewImp(this->mainWindowView());
    mNewSessionPresenter = new NewSessionPresenterImp(newSessionView, this->projectModel());
  }
  return mNewSessionPresenter;
}

ExportFeaturesPresenter *ComponentsManager::exportFeaturesPresenter()
{
  if (mExportFeaturesPresenter == nullptr){
    ExportFeaturesView *exportFeaturesView = new ExportFeaturesViewImp(this->mainWindowView());
    mExportFeaturesPresenter = new ExportFeaturesPresenterImp(exportFeaturesView, this->exportFeaturesModel());
  }
  return mExportFeaturesPresenter;
}

ExportFeaturesModel *ComponentsManager::exportFeaturesModel()
{
  if (mExportFeaturesModel == nullptr){
    mExportFeaturesModel = new ExportFeaturesModelImp(this->projectModel());
  }
  return mExportFeaturesModel;
}

ExportMatchesPresenter *ComponentsManager::exportMatchesPresenter()
{
  if (mExportMatchesPresenter == nullptr){
    ExportMatchesView *exportMatchesView = new ExportMatchesViewImp(this->mainWindowView());
    mExportMatchesPresenter = new ExportMatchesPresenterImp(exportMatchesView,
                                                            this->exportMatchesModel());
  }
  return mExportMatchesPresenter;
}

ExportMatchesModel *ComponentsManager::exportMatchesModel()
{
  if (mExportMatchesModel == nullptr){
    mExportMatchesModel = new ExportMatchesModelImp(this->projectModel());
  }
  return mExportMatchesModel;
}

PreprocessPresenter *ComponentsManager::preprocessPresenter()
{
  if (mPreprocessPresenter == nullptr){
    PreprocessView *preprocessView = new PreprocessViewImp(this->mainWindowView());
    mPreprocessPresenter = new PreprocessPresenterImp(preprocessView,
                                                      this->projectModel(),
                                                      this->settingsModel());
  }
  return mPreprocessPresenter;
}

FeatureExtractorPresenter *ComponentsManager::featureExtractorPresenter()
{
  if (mFeatureExtractorPresenter == nullptr){
    FeatureExtractorView *featureExtractorView = new FeatureExtractorViewImp(this->mainWindowView());
    mFeatureExtractorPresenter = new FeatureExtractorPresenterImp(featureExtractorView,
                                                                  this->projectModel(),
                                                                  this->settingsModel());
  }
  return mFeatureExtractorPresenter;
}

DescriptorMatcherPresenter *ComponentsManager::descriptorMatcherPresenter()
{
  if (mDescriptorMatcherPresenter == nullptr){
    DescriptorMatcherView *descriptorMatcherView = new DescriptorMatcherViewImp(this->mainWindowView());
    mDescriptorMatcherPresenter = new DescriptorMatcherPresenterImp(descriptorMatcherView,
                                                                    this->projectModel(),
                                                                    this->settingsModel());
  }
  return mDescriptorMatcherPresenter;
}

FeaturesViewerPresenter *ComponentsManager::featuresViewerPresenter()
{
  if (mFeaturesViewerPresenter == nullptr) {

    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    FeaturesViewerView *featuresViewerView = new FeaturesViewerViewImp(this->mainWindowView(), f);
    mFeaturesViewerPresenter = new FeaturesViewerPresenterImp(featuresViewerView,
                                                              this->featuresViewerModel(),
                                                              this->settingsModel());
  }
  return mFeaturesViewerPresenter;
}

FeaturesViewerModel *ComponentsManager::featuresViewerModel()
{
  if (mFeaturesViewerModel == nullptr) {
    mFeaturesViewerModel = new FeaturesViewerModelImp(this->projectModel());
  }
  return mFeaturesViewerModel;
}


MatchViewerPresenter *ComponentsManager::matchesViewerPresenter()
{
  if (mMatchesViewerPresenter == nullptr) {
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    MatchViewerView *matchViewerView = new MatchViewerViewImp(this->mainWindowView(), f);
    mMatchesViewerPresenter = new MatchViewerPresenterImp(matchViewerView,
                                                       this->matchesViewerModel(),
                                                       this->settingsModel());
  }
  return mMatchesViewerPresenter;
}

MatchViewerModel *ComponentsManager::matchesViewerModel()
{
  if (mMatchesViewerModel == nullptr) {
    mMatchesViewerModel = new MatchViewerModelImp(this->projectModel());
  }
  return mMatchesViewerModel;
}

MultiViewMatchingAssessmentModel *ComponentsManager::multiviewMatchingAssessmentModel()
{
  if (mMultiviewMatchingAssessmentModel == nullptr) {
    mMultiviewMatchingAssessmentModel = new MultiviewMatchingAssessmentModelImp(mProjectModel);
  }
  return mMultiviewMatchingAssessmentModel;
}

MultiViewMatchingAssessmentPresenter *ComponentsManager::multiviewMatchingAssessmentPresenter()
{
  if (mMultiviewMatchingAssessmentPresenter == nullptr){

    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    MultiviewMatchingAssessmentView *multiviewView = new MultiviewMatchingAssessmentViewImp(this->mainWindowView(), f);
    mMultiviewMatchingAssessmentPresenter = new MultiViewMatchingAssessmentPresenterImp(multiviewView,
                                                                                        this->multiviewMatchingAssessmentModel());
    mMultiviewMatchingAssessmentPresenter->setHelp(this->helpDialog());
  }
  return mMultiviewMatchingAssessmentPresenter;
}

GroundTruthPresenter *ComponentsManager::groundTruthPresenter()
{
  if (mGroundTruthPresenter == nullptr){

    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    GroundTruthView *groundTruthView = new GroundTruthViewImp(this->mainWindowView(), f);
    mGroundTruthPresenter = new GroundTruthPresenterImp(groundTruthView,
                                                        this->groundTruthModel(),
                                                        this->settingsModel());
  }
  return mGroundTruthPresenter;
}

GroundTruthModel *ComponentsManager::groundTruthModel()
{
  if (mGroundTruthModel == nullptr){
    mGroundTruthModel = new GroundTruthModelImp(this->projectModel());
  }
  return mGroundTruthModel;
}

HomographyViewerPresenter *ComponentsManager::homographyViewerPresenter()
{
  if (mHomographyViewerPresenter == nullptr) {
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    HomographyViewerView *homographyViewerView = new HomographyViewerViewImp(this->mainWindowView(), f);
    mHomographyViewerPresenter = new HomographyViewerPresenterImp(homographyViewerView,
                                                                  this->homographyViewerModel(),
                                                                  this->settingsModel());
  }
  return mHomographyViewerPresenter;
}

HomographyViewerModel *ComponentsManager::homographyViewerModel()
{
  if (mHomographyViewerModel == nullptr){
    mHomographyViewerModel = new HomographyViewerModelImp(mProjectModel);
  }
  return mHomographyViewerModel;
}

CurvesViewerPresenter *ComponentsManager::curvesPRViewerPresenter()
{
  if (mCurvesPRViewerPresenter == nullptr) {

    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    CurvesViewerViewImp *curvesViewerView = new PRCurvesViewer(this->mainWindowView(), f);
    mCurvesPRViewerPresenter = new CurvesViewerPresenterImp(curvesViewerView,
                                                            this->curvesPRViewerModel(),
                                                            this->settingsModel());
  }
  return mCurvesPRViewerPresenter;
}

CurvesViewerModel *ComponentsManager::curvesPRViewerModel()
{
  if (mCurvesPRViewerModel == nullptr){
    mCurvesPRViewerModel = new PRCurvesViewerModel(mProjectModel);
  }
  return mCurvesPRViewerModel;
}

CurvesViewerPresenter *ComponentsManager::curvesROCViewerPresenter()
{
  if (mCurvesROCViewerPresenter == nullptr) {
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    CurvesViewerViewImp *curvesViewerView = new ROCCurvesViewer(this->mainWindowView(), f);
    mCurvesROCViewerPresenter = new CurvesViewerPresenterImp(curvesViewerView,
                                                             this->curvesROCViewerModel(),
                                                             this->settingsModel());
  }
  return mCurvesROCViewerPresenter;
}

CurvesViewerModel *ComponentsManager::curvesROCViewerModel()
{
  if (mCurvesROCViewerModel == nullptr){
    mCurvesROCViewerModel = new ROCCurvesViewerModel(mProjectModel);
  }
  return mCurvesROCViewerModel;
}

CurvesViewerPresenter *ComponentsManager::curvesDETViewerPresenter()
{
  if (mCurvesDETViewerPresenter == nullptr) {
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    CurvesViewerViewImp *curvesViewerView = new DETCurvesViewer(this->mainWindowView(), f);
    mCurvesDETViewerPresenter = new CurvesViewerPresenterImp(curvesViewerView,
                                                             this->curvesDETViewerModel(),
                                                             this->settingsModel());
  }
  return mCurvesDETViewerPresenter;
}

CurvesViewerModel *ComponentsManager::curvesDETViewerModel()
{
  if (mCurvesDETViewerModel == nullptr){
    mCurvesDETViewerModel = new DETCurvesViewerModel(mProjectModel);
  }
  return mCurvesDETViewerModel;
}

RepeatabilityPresenter *ComponentsManager::repeatabilityPresenter()
{
  if (mRepeatabilityPresenter == nullptr){
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    RepeatabilityView *repeatabilityView = new RepeatabilityViewImp(this->mainWindowView(), f);
    mRepeatabilityPresenter = new RepeatabilityPresenterImp(repeatabilityView,
                                                            this->repeatabilityModel());
    mRepeatabilityPresenter->setHelp(this->helpDialog());
  }
  return mRepeatabilityPresenter;
}

RepeatabilityModel *ComponentsManager::repeatabilityModel()
{
  if (mRepeatabilityModel == nullptr) {
    mRepeatabilityModel = new RepeatabilityModelImp(mProjectModel);
  }
  return mRepeatabilityModel;
}

AboutDialog *ComponentsManager::aboutDialog()
{
  if (mAboutDialog == nullptr) {
    mAboutDialog = new AboutDialog(this->mainWindowView());
  }
  return mAboutDialog;
}

HelpDialog *ComponentsManager::helpDialog()
{
  if (mHelpDialog == nullptr) {
    mHelpDialog = new HelpDialog(this->mainWindowView()/*, f*/);
    mHelpDialog->setModal(true);
  }
  return mHelpDialog;
}

ProgressHandler *ComponentsManager::progressHandler()
{
  if (mProgressHandler == nullptr){

    mProgressHandler = new ProgressHandler;

    connect(mProgressHandler, &ProgressHandler::rangeChange,
            this->progressDialog(), &ProgressDialog::setRange);
    connect(mProgressHandler, &ProgressHandler::valueChange,
            this->progressDialog(), &ProgressDialog::setValue);
    connect(mProgressHandler, &ProgressHandler::initialized,
            this->progressDialog(), &ProgressDialog::setInitialized);
    connect(mProgressHandler, &ProgressHandler::finished,
            this->progressDialog(), &ProgressDialog::setFinished);
    connect(mProgressHandler, &ProgressHandler::titleChange,
            this->progressDialog(), &QWidget::setWindowTitle);
    connect(mProgressHandler, &ProgressHandler::descriptionChange,
            this->progressDialog(), &ProgressDialog::setStatusText);

    QProgressBar *statusBarProgress = this->mainWindowView()->progressBar();

    connect(mProgressHandler, &ProgressHandler::rangeChange, statusBarProgress, &QProgressBar::setRange);
    connect(mProgressHandler, &ProgressHandler::valueChange, statusBarProgress, &QProgressBar::setValue);
    connect(mProgressHandler, &ProgressHandler::initialized, statusBarProgress, &QWidget::show);
    connect(mProgressHandler, &ProgressHandler::finished,    statusBarProgress, &QWidget::hide);

  }
  return mProgressHandler;
}

ProgressDialog *ComponentsManager::progressDialog()
{
  if (mProgressDialog == nullptr){
    mProgressDialog = new ProgressDialogImp;
  }
  return mProgressDialog;
}

void ComponentsManager::initAndOpenNewProjectDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openNewProjectDialog,
             this, &ComponentsManager::initAndOpenNewProjectDialog);

  connect(this->mainWindowPresenter(), &MainWindowPresenter::openNewProjectDialog,
          this->newProjectPresenter(), &PhotoMatchPresenter::open);
  connect(this->newProjectPresenter(), SIGNAL(projectCreate()),        this->mainWindowPresenter(), SLOT(loadProject()));

  this->newProjectPresenter()->setHelp(this->helpDialog());
  this->newProjectPresenter()->open();
}

void ComponentsManager::initAndOpenNewSessionDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openNewSessionDialog,
             this, &ComponentsManager::initAndOpenNewSessionDialog);

  connect(this->mainWindowPresenter(), &MainWindowPresenter::openNewSessionDialog,
          this->newSessionPresenter(), &PhotoMatchPresenter::open);
  connect(this->newSessionPresenter(), SIGNAL(sessionCreate(QString)), this->mainWindowPresenter(), SLOT(loadSession(QString)));
  connect(this->newSessionPresenter(), SIGNAL(sessionCreate(QString)), this->mainWindowPresenter(), SLOT(activeSession(QString)));

  this->newSessionPresenter()->setHelp(this->helpDialog());
  this->newSessionPresenter()->open();
}

void ComponentsManager::initAndOpenPreprocessDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openPreprocessDialog,
             this, &ComponentsManager::initAndOpenPreprocessDialog);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openPreprocessDialog,
          this->preprocessPresenter(), &PhotoMatchPresenter::open);
  connect(this->preprocessPresenter(), SIGNAL(running()),   this->mainWindowPresenter(), SLOT(processRunning()));
  connect(this->preprocessPresenter(), SIGNAL(running()),   this->mainWindowPresenter(), SLOT(deletePreprocess()));
  connect(this->preprocessPresenter(), SIGNAL(finished()),  this->mainWindowPresenter(), SLOT(processFinish()));
  connect(this->preprocessPresenter(), SIGNAL(imagePreprocessed(QString)),  this->mainWindowPresenter(), SLOT(updatePreprocess()));
  connect(this->progressDialog(), SIGNAL(cancel()),     this->preprocessPresenter(), SLOT(cancel()));

  this->preprocessPresenter()->setProgressHandler(this->progressHandler());
  this->preprocessPresenter()->setHelp(this->helpDialog());
  this->preprocessPresenter()->open();
}

void ComponentsManager::initAndOpenFeatureExtractionDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openFeatureExtractionDialog,
             this, &ComponentsManager::initAndOpenFeatureExtractionDialog);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openFeatureExtractionDialog,
          this->featureExtractorPresenter(), &PhotoMatchPresenter::open);

  connect(this->featureExtractorPresenter(), SIGNAL(running()),                  this->mainWindowPresenter(), SLOT(processRunning()));
  connect(this->featureExtractorPresenter(), SIGNAL(running()),                  this->mainWindowPresenter(), SLOT(deleteFeatures()));
  connect(this->featureExtractorPresenter(), SIGNAL(finished()),                 this->mainWindowPresenter(), SLOT(processFinish()));
  connect(this->featureExtractorPresenter(), SIGNAL(imagePreprocessed(QString)), this->mainWindowPresenter(), SLOT(updatePreprocess()));
  connect(this->featureExtractorPresenter(), SIGNAL(featuresExtracted(QString)), this->mainWindowPresenter(), SLOT(updateFeatures()));

  connect(this->progressDialog(), SIGNAL(cancel()),     this->featureExtractorPresenter(), SLOT(cancel()));

  this->featureExtractorPresenter()->setProgressHandler(this->progressHandler());
  this->featureExtractorPresenter()->setHelp(this->helpDialog());
  this->featureExtractorPresenter()->open();
}

void ComponentsManager::initAndOpenFeatureMatchingDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openFeatureMatchingDialog,
             this, &ComponentsManager::initAndOpenFeatureMatchingDialog);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openFeatureMatchingDialog,
          this->descriptorMatcherPresenter(), &PhotoMatchPresenter::open);

  connect(this->descriptorMatcherPresenter(), SIGNAL(running()),             this->mainWindowPresenter(), SLOT(processRunning()));
  connect(this->descriptorMatcherPresenter(), SIGNAL(running()),             this->mainWindowPresenter(), SLOT(deleteMatches()));
  connect(this->descriptorMatcherPresenter(), SIGNAL(finished()),            this->mainWindowPresenter(), SLOT(processFinish()));
  connect(this->descriptorMatcherPresenter(), SIGNAL(matchCompute(QString)), this->mainWindowPresenter(), SLOT(updateMatches()));

  connect(this->progressDialog(), SIGNAL(cancel()),     this->descriptorMatcherPresenter(), SLOT(cancel()));

  this->descriptorMatcherPresenter()->setProgressHandler(this->progressHandler());
  this->descriptorMatcherPresenter()->setHelp(this->helpDialog());
  this->descriptorMatcherPresenter()->open();
}

void ComponentsManager::initAndOpenKeypointsViewerDialogFromSession(const QString &session)
{
  this->initKeypointsViewer();
  this->featuresViewerPresenter()->openKeypointsFromSession(session);
}

void ComponentsManager::initAndOpenKeypointsViewerDialogFromSessionAndImage(const QString &session,
                                                                            const QString &image)
{
  this->initKeypointsViewer();
  this->featuresViewerPresenter()->openKeypointsFromSessionAndImage(session, image);
}

void ComponentsManager::initKeypointsViewer()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openKeypointsViewerDialogFromSession,
             this, &ComponentsManager::initAndOpenKeypointsViewerDialogFromSession);
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openKeypointsViewerDialogFromSessionAndImage,
             this, &ComponentsManager::initAndOpenKeypointsViewerDialogFromSessionAndImage);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openKeypointsViewerDialogFromSession,
          this->featuresViewerPresenter(), &FeaturesViewerPresenter::openKeypointsFromSession);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openKeypointsViewerDialogFromSessionAndImage,
          this->featuresViewerPresenter(), &FeaturesViewerPresenter::openKeypointsFromSessionAndImage);

  this->featuresViewerPresenter()->setHelp(this->helpDialog());
}

void ComponentsManager::initAndOpenMatchesViewerDialogFromSession(const QString &session)
{
  this->initMatchesViewer();
  this->matchesViewerPresenter()->openFromSession(session);
}

void ComponentsManager::initAndOpenMatchesViewerDialogFromSessionAndImages(const QString &session,
                                                                           const QString &leftImage,
                                                                           const QString &rightImage)
{
  this->initMatchesViewer();
  this->matchesViewerPresenter()->openFromSessionAndImages(session, leftImage, rightImage);
}

void ComponentsManager::initMatchesViewer()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openMatchesViewerDialogFromSession,
             this, &ComponentsManager::initAndOpenMatchesViewerDialogFromSession);
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openMatchesViewerDialogFromSessionAndImages,
             this, &ComponentsManager::initAndOpenMatchesViewerDialogFromSessionAndImages);

  connect(this->mainWindowPresenter(), &MainWindowPresenter::openMatchesViewerDialogFromSession,
          this->matchesViewerPresenter(), &MatchViewerPresenter::openFromSession);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openMatchesViewerDialogFromSessionAndImages,
          this->matchesViewerPresenter(), &MatchViewerPresenter::openFromSessionAndImages);

  this->matchesViewerPresenter()->setHelp(this->helpDialog());
}

void ComponentsManager::initAndOpenExportFeaturesDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openExportFeaturesDialog,
             this, &ComponentsManager::initAndOpenExportFeaturesDialog);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openExportFeaturesDialog,
          this->exportFeaturesPresenter(), &PhotoMatchPresenter::open);

  this->exportFeaturesPresenter()->setHelp(this->helpDialog());
  this->exportFeaturesPresenter()->open();
}

void ComponentsManager::initAndOpenExportMatchesDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openExportMatchesDialog,
             this, &ComponentsManager::initAndOpenExportMatchesDialog);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openExportMatchesDialog,
          this->exportMatchesPresenter(), &PhotoMatchPresenter::open);

  this->exportMatchesPresenter()->setHelp(this->helpDialog());
  this->exportMatchesPresenter()->open();
}

void ComponentsManager::initAndOpenGroundTruthEditorDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openGroundTruthEditorDialog,
             this, &ComponentsManager::initAndOpenGroundTruthEditorDialog);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openGroundTruthEditorDialog,
          this->groundTruthPresenter(), &PhotoMatchPresenter::open);
  connect(this->groundTruthPresenter(), SIGNAL(groundTruthAdded()), this->mainWindowPresenter(), SLOT(groundTruthAdded()));

  this->groundTruthPresenter()->setHelp(this->helpDialog());
  this->groundTruthPresenter()->open();
}

void ComponentsManager::initAndOpenHomographyViewerDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openHomographyViewerDialog,
             this, &ComponentsManager::initAndOpenHomographyViewerDialog);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openHomographyViewerDialog,
          this->homographyViewerPresenter(), &PhotoMatchPresenter::open);

  this->homographyViewerPresenter()->setHelp(this->helpDialog());
  this->homographyViewerPresenter()->open();
}

void ComponentsManager::initAndOpenPRCurvesViewerDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openPRCurvesViewerDialog,
             this, &ComponentsManager::initAndOpenPRCurvesViewerDialog);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openPRCurvesViewerDialog,
          this->curvesPRViewerPresenter(), &PhotoMatchPresenter::open);

  this->curvesPRViewerPresenter()->setHelp(this->helpDialog());
  this->curvesPRViewerPresenter()->open();
}

void ComponentsManager::initAndOpenROCCurvesViewerDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openROCCurvesViewerDialog,
             this, &ComponentsManager::initAndOpenROCCurvesViewerDialog);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openPRCurvesViewerDialog,
          this->curvesROCViewerPresenter(), &PhotoMatchPresenter::open);

  this->curvesROCViewerPresenter()->setHelp(this->helpDialog());
  this->curvesROCViewerPresenter()->open();
}

void ComponentsManager::initAndOpenDETCurvesViewerDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openDETCurvesViewerDialog,
             this, &ComponentsManager::initAndOpenDETCurvesViewerDialog);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openPRCurvesViewerDialog,
          this->curvesDETViewerPresenter(), &PhotoMatchPresenter::open);

  this->curvesDETViewerPresenter()->setHelp(this->helpDialog());
  this->curvesDETViewerPresenter()->open();
}

void ComponentsManager::initAndOpenAboutDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openAboutDialog,
             this, &ComponentsManager::initAndOpenAboutDialog);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openAboutDialog,
          this->aboutDialog(), &AboutDialog::open);
  this->aboutDialog()->open();
}

void ComponentsManager::initAndOpenSettingsDialog()
{
  this->initSettingsDialog();
  this->settingsPresenter()->open();
}

void ComponentsManager::initAndOpenViewSettingsDialog()
{
  this->initSettingsDialog();
  this->settingsPresenter()->openViewSettings();
}

void ComponentsManager::initAndOpenQualityControlDialog()
{
  this->initSettingsDialog();
  this->settingsPresenter()->openQualityControlSettings();
}

void ComponentsManager::initAndOpenToolSettingsDialog()
{
  this->initSettingsDialog();
  this->settingsPresenter()->openToolSettings();
}

void ComponentsManager::initSettingsDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openSettingsDialog,
             this, &ComponentsManager::initAndOpenSettingsDialog);
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openViewSettingsDialog,
             this, &ComponentsManager::initAndOpenViewSettingsDialog);
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openQualityControlSettingsDialog,
             this, &ComponentsManager::initAndOpenQualityControlDialog);
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openToolSettingsDialog,
             this, &ComponentsManager::initAndOpenToolSettingsDialog);

  connect(this->mainWindowPresenter(), &MainWindowPresenter::openSettingsDialog,
          this->settingsPresenter(), &PhotoMatchPresenter::open);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openViewSettingsDialog,
          this->settingsPresenter(), &SettingsPresenter::openViewSettings);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openQualityControlSettingsDialog,
          this->settingsPresenter(), &SettingsPresenter::openQualityControlSettings);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openToolSettingsDialog,
          this->settingsPresenter(), &SettingsPresenter::openToolSettings);

  this->settingsPresenter()->setHelp(this->helpDialog());
}

void ComponentsManager::initAndOpenMultiviewMatchingAssessmentDialog()
{
  disconnect(mMainWindowPresenter, &MainWindowPresenter::openMultiviewMatchingAssessmentDialog,
             this, &ComponentsManager::initAndOpenMultiviewMatchingAssessmentDialog);
  connect(mMainWindowPresenter, &MainWindowPresenter::openMultiviewMatchingAssessmentDialog,
          this->multiviewMatchingAssessmentPresenter(), &PhotoMatchPresenter::open);

  this->multiviewMatchingAssessmentPresenter()->open();
}


} // namespace photomatch
