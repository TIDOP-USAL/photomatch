#include "ComponentsManager.h"

#include "photomatch/ui/MainWindowModel.h"
#include "photomatch/ui/MainWindowView.h"
#include "photomatch/ui/MainWindowPresenter.h"

#include "photomatch/ui/ProjectModel.h"

#include "photomatch/ui/NewProjectPresenter.h"
#include "photomatch/ui/NewProjectView.h"

#include "photomatch/ui/NewSessionPresenter.h"
#include "photomatch/ui/NewSessionView.h"

#include "photomatch/ui/ExportFeaturesModel.h"
#include "photomatch/ui/ExportFeaturesView.h"
#include "photomatch/ui/ExportFeaturesPresenter.h"
#include "photomatch/ui/ExportMatchesModel.h"
#include "photomatch/ui/ExportMatchesView.h"
#include "photomatch/ui/ExportMatchesPresenter.h"

#include "photomatch/ui/SettingsModel.h"
#include "photomatch/ui/SettingsView.h"
#include "photomatch/ui/SettingsPresenter.h"

#include "photomatch/ui/PreprocessView.h"
#include "photomatch/ui/PreprocessPresenter.h"
#include "photomatch/ui/FeatureExtractorView.h"
#include "photomatch/ui/FeatureExtractorPresenter.h"
#include "photomatch/ui/DescriptorMatcherView.h"
#include "photomatch/ui/DescriptorMatcherPresenter.h"

#include "photomatch/ui/FeaturesViewerModel.h"
#include "photomatch/ui/FeaturesViewerView.h"
#include "photomatch/ui/FeaturesViewerPresenter.h"

#include "photomatch/ui/MatchViewerModel.h"
#include "photomatch/ui/MatchViewerView.h"
#include "photomatch/ui/MatchViewerPresenter.h"

#include "photomatch/ui/MultiViewModel.h"
#include "photomatch/ui/MultiViewView.h"
#include "photomatch/ui/MultiViewPresenter.h"

#include "photomatch/ui/GroundTruthModel.h"
#include "photomatch/ui/GroundTruthView.h"
#include "photomatch/ui/GroundTruthPresenter.h"

#include "photomatch/ui/HomographyViewerModel.h"
#include "photomatch/ui/HomographyViewerView.h"
#include "photomatch/ui/HomographyViewerPresenter.h"

#include "photomatch/ui/CurvesViewerModel.h"
#include "photomatch/ui/CurvesViewerView.h"
#include "photomatch/ui/CurvesViewerPresenter.h"

#include "photomatch/ui/RepeatabilityModel.h"
#include "photomatch/ui/RepeatabilityView.h"
#include "photomatch/ui/RepeatabilityPresenter.h"

#include "photomatch/ui/AboutDialog.h"
#include "photomatch/ui/HelpDialog.h"

#include "photomatch/ui/utils/Progress.h"
#include "photomatch/ui/utils/ProgressDialog.h"

#include "photomatch/core/project.h"

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

    connect(mMainWindowPresenter, SIGNAL(openNewProjectDialog()),        this, SLOT(initAndOpenNewProjectDialog()));
    connect(mMainWindowPresenter, SIGNAL(openNewSessionDialog()),        this, SLOT(initAndOpenNewSessionDialog()));
    connect(mMainWindowPresenter, SIGNAL(openPreprocessDialog()),        this, SLOT(initAndOpenPreprocessDialog()));
    connect(mMainWindowPresenter, SIGNAL(openFeatureExtractionDialog()), this, SLOT(initAndOpenFeatureExtractionDialog()));
    connect(mMainWindowPresenter, SIGNAL(openFeatureMatchingDialog()),   this, SLOT(initAndOpenFeatureMatchingDialog()));
    connect(mMainWindowPresenter, SIGNAL(openKeypointsViewerDialogFromSession(QString)),   this, SLOT(initAndOpenKeypointsViewerDialogFromSession(QString)));
    connect(mMainWindowPresenter, SIGNAL(openKeypointsViewerDialogFromSessionAndImage(QString, QString)), this, SLOT(initAndOpenKeypointsViewerDialogFromSessionAndImage(QString, QString)));
    connect(mMainWindowPresenter, SIGNAL(openMatchesViewerDialogFromSession(QString)),     this, SLOT(initAndOpenMatchesViewerDialogFromSession(QString)));
    connect(mMainWindowPresenter, SIGNAL(openMatchesViewerDialogFromSessionAndImages(QString, QString, QString)),     this, SLOT(initAndOpenMatchesViewerDialogFromSessionAndImages(QString, QString, QString)));
    connect(mMainWindowPresenter, SIGNAL(openExportFeaturesDialog()),    this, SLOT(initAndOpenExportFeaturesDialog()));
    connect(mMainWindowPresenter, SIGNAL(openExportMatchesDialog()),     this, SLOT(initAndOpenExportMatchesDialog()));
    connect(mMainWindowPresenter, SIGNAL(openGroundTruthEditorDialog()), this, SLOT(initAndOpenGroundTruthEditorDialog()));
    connect(mMainWindowPresenter, SIGNAL(openHomographyViewerDialog()),  this, SLOT(initAndOpenHomographyViewerDialog()));
    connect(mMainWindowPresenter, SIGNAL(openPRCurvesViewerDialog()),  this, SLOT(initAndOpenPRCurvesViewerDialog()));
    connect(mMainWindowPresenter, SIGNAL(openROCCurvesViewerDialog()),  this, SLOT(initAndOpenROCCurvesViewerDialog()));
    connect(mMainWindowPresenter, SIGNAL(openDETCurvesViewerDialog()),  this, SLOT(initAndOpenDETCurvesViewerDialog()));
    connect(mMainWindowPresenter, SIGNAL(openAboutDialog()),            this, SLOT(initAndOpenAboutDialog()));
    connect(mMainWindowPresenter, SIGNAL(openSettingsDialog()),         this, SLOT(initAndOpenSettingsDialog()));
    connect(mMainWindowPresenter, SIGNAL(openViewSettingsDialog()),     this, SLOT(initAndOpenViewSettingsDialog()));
    connect(mMainWindowPresenter, SIGNAL(openQualityControlSettingsDialog()),         this, SLOT(initAndOpenQualityControlDialog()));
    connect(mMainWindowPresenter, SIGNAL(openToolSettingsDialog()),     this, SLOT(initAndOpenToolSettingsDialog()));
    connect(mMainWindowPresenter, SIGNAL(openMultiviewMatchingAssessmentDialog()),     this, SLOT(initAndOpenMultiviewMatchingAssessmentDialog()));
  }
  return mMainWindowPresenter;
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
    SettingsView *view = new SettingsViewImp(this->mainWindowView());
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

    connect(mProgressHandler, SIGNAL(rangeChange(int, int)),      this->progressDialog(), SLOT(setRange(int, int)));
    connect(mProgressHandler, SIGNAL(valueChange(int)),           this->progressDialog(), SLOT(setValue(int)));
    connect(mProgressHandler, SIGNAL(initialized()),              this->progressDialog(), SLOT(setInitialized()));
    connect(mProgressHandler, SIGNAL(finished()),                 this->progressDialog(), SLOT(setFinished()));
    connect(mProgressHandler, SIGNAL(titleChange(QString)),       this->progressDialog(), SLOT(setWindowTitle(QString)));
    connect(mProgressHandler, SIGNAL(descriptionChange(QString)), this->progressDialog(), SLOT(setStatusText(QString)));

    QProgressBar *statusBarProgress = this->mainWindowView()->progressBar();

    connect(mProgressHandler, SIGNAL(rangeChange(int, int)),      statusBarProgress, SLOT(setRange(int, int)));
    connect(mProgressHandler, SIGNAL(valueChange(int)),           statusBarProgress, SLOT(setValue(int)));
    connect(mProgressHandler, SIGNAL(initialized()),              statusBarProgress, SLOT(show()));
    connect(mProgressHandler, SIGNAL(finished()),                 statusBarProgress, SLOT(hide()));

  }
  return mProgressHandler;
}

IProgressDialog *ComponentsManager::progressDialog()
{
  if (mProgressDialog == nullptr){
    mProgressDialog = new ProgressDialog;
  }
  return mProgressDialog;
}

void ComponentsManager::initAndOpenNewProjectDialog()
{
  disconnect(this->mainWindowPresenter(), SIGNAL(openNewProjectDialog()), this, SLOT(initAndOpenNewProjectDialog()));

  connect(this->mainWindowPresenter(), SIGNAL(openNewProjectDialog()), this->newProjectPresenter(), SLOT(open()));
  connect(this->newProjectPresenter(), SIGNAL(projectCreate()),        this->mainWindowPresenter(), SLOT(loadProject()));

  this->newProjectPresenter()->setHelp(this->helpDialog());
  this->newProjectPresenter()->open();
}

void ComponentsManager::initAndOpenNewSessionDialog()
{
  disconnect(this->mainWindowPresenter(), SIGNAL(openNewSessionDialog()), this, SLOT(initAndOpenNewSessionDialog()));

  connect(this->mainWindowPresenter(), SIGNAL(openNewSessionDialog()), this->newSessionPresenter(), SLOT(open()));
  connect(this->newSessionPresenter(), SIGNAL(sessionCreate(QString)), this->mainWindowPresenter(), SLOT(loadSession(QString)));
  connect(this->newSessionPresenter(), SIGNAL(sessionCreate(QString)), this->mainWindowPresenter(), SLOT(activeSession(QString)));

  this->newSessionPresenter()->setHelp(this->helpDialog());
  this->newSessionPresenter()->open();
}

void ComponentsManager::initAndOpenPreprocessDialog()
{
  disconnect(this->mainWindowPresenter(), SIGNAL(openPreprocessDialog()), this, SLOT(initAndOpenPreprocessDialog()));
  connect(this->mainWindowPresenter(), SIGNAL(openPreprocessDialog()),  this->preprocessPresenter(), SLOT(open()));
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
  disconnect(this->mainWindowPresenter(), SIGNAL(openFeatureExtractionDialog()), this, SLOT(initAndOpenFeatureExtractionDialog()));
  connect(this->mainWindowPresenter(), SIGNAL(openFeatureExtractionDialog()), this->featureExtractorPresenter(), SLOT(open()));

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
  disconnect(this->mainWindowPresenter(), SIGNAL(openFeatureMatchingDialog()), this, SLOT(initAndOpenFeatureMatchingDialog()));
  connect(this->mainWindowPresenter(), SIGNAL(openFeatureMatchingDialog()),   this->descriptorMatcherPresenter(), SLOT(open()));

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
  disconnect(this->mainWindowPresenter(), SIGNAL(openExportFeaturesDialog()), this, SLOT(initAndOpenExportFeaturesDialog()));
  connect(this->mainWindowPresenter(), SIGNAL(openExportFeaturesDialog()), this->exportFeaturesPresenter(), SLOT(open()));
  this->exportFeaturesPresenter()->setHelp(this->helpDialog());
  this->exportFeaturesPresenter()->open();
}

void ComponentsManager::initAndOpenExportMatchesDialog()
{
  disconnect(this->mainWindowPresenter(), SIGNAL(openExportMatchesDialog()),     this, SLOT(initAndOpenExportMatchesDialog()));
  connect(this->mainWindowPresenter(), SIGNAL(openExportMatchesDialog()), this->exportMatchesPresenter(), SLOT(open()));

  this->exportMatchesPresenter()->setHelp(this->helpDialog());
  this->exportMatchesPresenter()->open();
}

void ComponentsManager::initAndOpenGroundTruthEditorDialog()
{
  disconnect(this->mainWindowPresenter(), SIGNAL(openGroundTruthEditorDialog()), this, SLOT(initAndOpenGroundTruthEditorDialog()));
  connect(this->mainWindowPresenter(), SIGNAL(openGroundTruthEditorDialog()), this->groundTruthPresenter(), SLOT(open()));
  connect(this->groundTruthPresenter(), SIGNAL(groundTruthAdded()), this->mainWindowPresenter(), SLOT(groundTruthAdded()));

  this->groundTruthPresenter()->setHelp(this->helpDialog());
  this->groundTruthPresenter()->open();
}

void ComponentsManager::initAndOpenHomographyViewerDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openHomographyViewerDialog,
             this, &ComponentsManager::initAndOpenHomographyViewerDialog);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openHomographyViewerDialog,
          this->homographyViewerPresenter(), &IPresenter::open);

  this->homographyViewerPresenter()->setHelp(this->helpDialog());
  this->homographyViewerPresenter()->open();
}

void ComponentsManager::initAndOpenPRCurvesViewerDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openPRCurvesViewerDialog,
             this, &ComponentsManager::initAndOpenPRCurvesViewerDialog);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openPRCurvesViewerDialog,
          this->curvesPRViewerPresenter(), &IPresenter::open);

  this->curvesPRViewerPresenter()->setHelp(this->helpDialog());
  this->curvesPRViewerPresenter()->open();
}

void ComponentsManager::initAndOpenROCCurvesViewerDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openROCCurvesViewerDialog,
             this, &ComponentsManager::initAndOpenROCCurvesViewerDialog);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openPRCurvesViewerDialog,
          this->curvesROCViewerPresenter(), &IPresenter::open);

  this->curvesROCViewerPresenter()->setHelp(this->helpDialog());
  this->curvesROCViewerPresenter()->open();
}

void ComponentsManager::initAndOpenDETCurvesViewerDialog()
{
  disconnect(this->mainWindowPresenter(), &MainWindowPresenter::openDETCurvesViewerDialog,
             this, &ComponentsManager::initAndOpenDETCurvesViewerDialog);
  connect(this->mainWindowPresenter(), &MainWindowPresenter::openPRCurvesViewerDialog,
          this->curvesDETViewerPresenter(), &IPresenter::open);

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
  disconnect(this->mainWindowPresenter(), SIGNAL(openSettingsDialog()), this, SLOT(initAndOpenSettingsDialog()));
  disconnect(this->mainWindowPresenter(), SIGNAL(openViewSettingsDialog()), this, SLOT(initAndOpenViewSettingsDialog()));
  disconnect(this->mainWindowPresenter(), SIGNAL(openQualityControlSettingsDialog()), this, SLOT(initAndOpenQualityControlDialog()));
  disconnect(this->mainWindowPresenter(), SIGNAL(openToolSettingsDialog()), this, SLOT(initAndOpenToolSettingsDialog()));

  connect(this->mainWindowPresenter(), SIGNAL(openSettingsDialog()), this->settingsPresenter(), SLOT(open()));
  connect(this->mainWindowPresenter(), SIGNAL(openViewSettingsDialog()), this->settingsPresenter(), SLOT(openViewSettings()));
  connect(this->mainWindowPresenter(), SIGNAL(openQualityControlSettingsDialog()), this->settingsPresenter(), SLOT(openQualityControlSettings()));
  connect(this->mainWindowPresenter(), SIGNAL(openToolSettingsDialog()), this->settingsPresenter(), SLOT(openToolSettings()));

  this->settingsPresenter()->setHelp(this->helpDialog());
}

void ComponentsManager::initAndOpenMultiviewMatchingAssessmentDialog()
{
  disconnect(mMainWindowPresenter, SIGNAL(openMultiviewMatchingAssessmentDialog()), this, SLOT(initAndOpenMultiviewMatchingAssessmentDialog()));
  connect(mMainWindowPresenter, SIGNAL(openMultiviewMatchingAssessmentDialog()), this->multiviewMatchingAssessmentPresenter(), SLOT(open()));

  this->multiviewMatchingAssessmentPresenter()->open();
}


} // namespace photomatch
