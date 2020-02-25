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
    mProjectIO(new ProjectControllerImp),
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
    mMultiviewModel(nullptr),
    mMultiviewPresenter(nullptr),
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

  if (mProjectIO) {
    delete mProjectIO;
    mProjectIO =nullptr;
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

  if (mMultiviewModel){
    delete mMultiviewModel;
    mMultiviewModel = nullptr;
  }

  if (mMultiviewPresenter){
    delete mMultiviewPresenter;
    mMultiviewPresenter = nullptr;
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

    connect(mMainWindowPresenter, SIGNAL(openNewProjectDialog()),        this, SLOT(initAndOpenNewProjectDialog()));
    connect(mMainWindowPresenter, SIGNAL(openNewSessionDialog()),        this, SLOT(initAndOpenNewSessionDialog()));
    connect(mMainWindowPresenter, SIGNAL(openPreprocessDialog()),        this, SLOT(initAndOpenPreprocessDialog()));
    connect(mMainWindowPresenter, SIGNAL(openFeatureExtractionDialog()), this, SLOT(initAndOpenFeatureExtractionDialog()));
    connect(mMainWindowPresenter, SIGNAL(openFeatureMatchingDialog()),   this, SLOT(initAndOpenFeatureMatchingDialog()));
    connect(mMainWindowPresenter, SIGNAL(openKeypointsViewerDialog()),   this, SLOT(initAndOpenKeypointsViewerDialog()));
    connect(mMainWindowPresenter, SIGNAL(openKeypointsViewerDialog(QString, QString)), this, SLOT(initAndOpenKeypointsViewerDialog(QString, QString)));
    connect(mMainWindowPresenter, SIGNAL(openMatchesViewerDialog()),     this, SLOT(initAndOpenMatchesViewerDialog()));
    connect(mMainWindowPresenter, SIGNAL(openMatchesViewerDialog(QString, QString)),     this, SLOT(initAndOpenMatchesViewerDialog(QString, QString)));
  }
  return mMainWindowPresenter;
}

IProjectModel *ComponentsManager::projectModel()
{
  if (mProjectModel == nullptr){
    mProjectModel = new ProjectModel(mProjectIO, mProject);
  }
  return mProjectModel;
}

//Settings *ComponentsManager::settings()
//{
//  return mSettings;
//}

//SettingsController *ComponentsManager::settingsRW()
//{
//  return mSettingsRW;
//}

ISettingsModel *ComponentsManager::settingsModel()
{
  if (mSettingsModel == nullptr){
    mSettingsModel = new SettingsModel(mSettings, mSettingsRW);
    mSettingsModel->read();
  }
  return mSettingsModel;
}

ISettingsPresenter *ComponentsManager::settingsPresenter()
{
  if (mSettingsPresenter == nullptr){
    mSettingsPresenter = new SettingsPresenter(new SettingsView(this->mainWindowView()), this->settingsModel());
    mSettingsPresenter->setHelp(this->helpDialog());
  }
  return mSettingsPresenter;
}

INewProjectPresenter *ComponentsManager::newProjectPresenter()
{
  if (mNewProjectPresenter == nullptr){
    INewProjectView *newProjectView = new NewProjectView(this->mainWindowView());
    mNewProjectPresenter = new NewProjectPresenter(newProjectView, this->projectModel());
    mNewProjectPresenter->setHelp(this->helpDialog());

    connect(mMainWindowPresenter, SIGNAL(openNewProjectDialog()), mNewProjectPresenter, SLOT(open()));
    connect(mNewProjectPresenter, SIGNAL(projectCreate()),        mMainWindowPresenter, SLOT(loadProject()));
  }
  return mNewProjectPresenter;
}

INewSessionPresenter *ComponentsManager::newSessionPresenter()
{
  if (mNewSessionPresenter == nullptr){
    INewSessionView *newSessionView = new NewSessionView(this->mainWindowView());
    mNewSessionPresenter = new NewSessionPresenter(newSessionView, this->projectModel());
    mNewSessionPresenter->setHelp(this->helpDialog());

    connect(mMainWindowPresenter, SIGNAL(openNewSessionDialog()), mNewSessionPresenter, SLOT(open()));
    connect(mNewSessionPresenter, SIGNAL(sessionCreate(QString)), mMainWindowPresenter, SLOT(loadSession(QString)));
    connect(mNewSessionPresenter, SIGNAL(sessionCreate(QString)), mMainWindowPresenter, SLOT(activeSession(QString)));
  }
  return mNewSessionPresenter;
}

IExportFeaturesPresenter *ComponentsManager::exportFeaturesPresenter()
{
  if (mExportFeaturesPresenter == nullptr){
    IExportFeaturesView *exportFeaturesView = new ExportFeaturesView(this->mainWindowView());
    mExportFeaturesPresenter = new ExportFeaturesPresenter(exportFeaturesView, this->exportFeaturesModel());
    mExportFeaturesPresenter->setHelp(this->helpDialog());
  }
  return mExportFeaturesPresenter;
}

IExportFeaturesModel *ComponentsManager::exportFeaturesModel()
{
  if (mExportFeaturesModel == nullptr){
    mExportFeaturesModel = new ExportFeaturesModel(this->projectModel());
  }
  return mExportFeaturesModel;
}

IExportMatchesPresenter *ComponentsManager::exportMatchesPresenter()
{
  if (mExportMatchesPresenter == nullptr){
    IExportMatchesView *exportMatchesView = new ExportMatchesView(this->mainWindowView());
    mExportMatchesPresenter = new ExportMatchesPresenter(exportMatchesView, mExportMatchesModel);
    mExportMatchesPresenter->setHelp(this->helpDialog());
  }
  return mExportMatchesPresenter;
}

IExportMatchesModel *ComponentsManager::exportMatchesModel()
{
  if (mExportMatchesModel == nullptr){
    mExportMatchesModel = new ExportMatchesModel(this->projectModel());
  }
  return mExportMatchesModel;
}

IPreprocessPresenter *ComponentsManager::preprocessPresenter()
{
  if (mPreprocessPresenter == nullptr){
    IPreprocessView *preprocessView = new PreprocessView(this->mainWindowView());
    mPreprocessPresenter = new PreprocessPresenter(preprocessView,
                                                   //this->preprocessModel(),
                                                   this->projectModel(),
                                                   this->settingsModel());

    connect(mMainWindowPresenter, SIGNAL(openPreprocessDialog()),  mPreprocessPresenter, SLOT(open()));
    connect(mPreprocessPresenter, SIGNAL(running()),   mMainWindowPresenter, SLOT(processRunning()));
    connect(mPreprocessPresenter, SIGNAL(running()),   mMainWindowPresenter, SLOT(deletePreprocess()));
    connect(mPreprocessPresenter, SIGNAL(finished()),  mMainWindowPresenter, SLOT(processFinish()));
    connect(mPreprocessPresenter, SIGNAL(imagePreprocessed(QString)),  mMainWindowPresenter, SLOT(updatePreprocess()));

    connect(this->progressDialog(), SIGNAL(cancel()),     mPreprocessPresenter, SLOT(cancel()));

    mPreprocessPresenter->setProgressHandler(this->progressHandler());
    mPreprocessPresenter->setHelp(this->helpDialog());
  }
  return mPreprocessPresenter;
}

IFeatureExtractorPresenter *ComponentsManager::featureExtractorPresenter()
{
  if (mFeatureExtractorPresenter == nullptr){
    IFeatureExtractorView *featureExtractorView = new FeatureExtractorView(this->mainWindowView());
    mFeatureExtractorPresenter = new FeatureExtractorPresenter(featureExtractorView,
                                                               mProjectModel,
                                                               mSettingsModel);

    connect(mMainWindowPresenter, SIGNAL(openFeatureExtractionDialog()), mFeatureExtractorPresenter, SLOT(open()));

    connect(mFeatureExtractorPresenter, SIGNAL(running()),                  mMainWindowPresenter, SLOT(processRunning()));
    connect(mFeatureExtractorPresenter, SIGNAL(running()),                  mMainWindowPresenter, SLOT(deleteFeatures()));
    connect(mFeatureExtractorPresenter, SIGNAL(finished()),                 mMainWindowPresenter, SLOT(processFinish()));
    connect(mFeatureExtractorPresenter, SIGNAL(imagePreprocessed(QString)), mMainWindowPresenter, SLOT(updatePreprocess()));
    connect(mFeatureExtractorPresenter, SIGNAL(featuresExtracted(QString)), mMainWindowPresenter, SLOT(updateFeatures()));

    //initProgress();

    connect(this->progressDialog(), SIGNAL(cancel()),     mFeatureExtractorPresenter, SLOT(cancel()));

    mFeatureExtractorPresenter->setProgressHandler(this->progressHandler());
    mFeatureExtractorPresenter->setHelp(this->helpDialog());
  }
  return mFeatureExtractorPresenter;
}

IDescriptorMatcherPresenter *ComponentsManager::descriptorMatcherPresenter()
{
  if (mDescriptorMatcherPresenter == nullptr){
    IDescriptorMatcherView *descriptorMatcherView = new DescriptorMatcherView(this->mainWindowView());
    mDescriptorMatcherPresenter = new DescriptorMatcherPresenter(descriptorMatcherView,
                                                                 this->projectModel(),
                                                                 mSettingsModel);

    connect(mMainWindowPresenter, SIGNAL(openFeatureMatchingDialog()),   mDescriptorMatcherPresenter, SLOT(open()));

    connect(mDescriptorMatcherPresenter, SIGNAL(running()),             mMainWindowPresenter, SLOT(processRunning()));
    connect(mDescriptorMatcherPresenter, SIGNAL(running()),             mMainWindowPresenter, SLOT(deleteMatches()));
    connect(mDescriptorMatcherPresenter, SIGNAL(finished()),            mMainWindowPresenter, SLOT(processFinish()));
    connect(mDescriptorMatcherPresenter, SIGNAL(matchCompute(QString)), mMainWindowPresenter, SLOT(updateMatches()));

    //initProgress();

    connect(this->progressDialog(), SIGNAL(cancel()),     mDescriptorMatcherPresenter, SLOT(cancel()));

    mDescriptorMatcherPresenter->setProgressHandler(this->progressHandler());
    mDescriptorMatcherPresenter->setHelp(this->helpDialog());
  }
  return mDescriptorMatcherPresenter;
}

IFeaturesViewerPresenter *ComponentsManager::featuresViewerPresenter()
{
  if (mFeaturesViewerPresenter == nullptr) {

    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    IFeaturesViewerView *featuresViewerView = new FeaturesViewerView(this->mainWindowView(), f);
    mFeaturesViewerPresenter = new FeaturesViewerPresenter(featuresViewerView,
                                                           this->featuresViewerModel(),
                                                           this->settingsModel());
    mFeaturesViewerPresenter->setHelp(this->helpDialog());

    connect(mMainWindowPresenter, SIGNAL(openKeypointsViewerDialog()),                 mFeaturesViewerPresenter, SLOT(open()));
    connect(mMainWindowPresenter, SIGNAL(openKeypointsViewerDialog(QString, QString)), mFeaturesViewerPresenter, SLOT(openImageFromSession(QString, QString)));
  }
  return mFeaturesViewerPresenter;
}

IFeaturesViewerModel *ComponentsManager::featuresViewerModel()
{
  if (mFeaturesViewerModel == nullptr) {
    mFeaturesViewerModel = new FeaturesViewerModel(this->projectModel());
  }
  return mFeaturesViewerModel;
}


IMatchViewerPresenter *ComponentsManager::matchesViewerPresenter()
{
  if (mMatchesViewerPresenter == nullptr) {
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    IMatchViewerView *matchViewerView = new MatchViewerView(this->mainWindowView(), f);
    mMatchesViewerPresenter = new MatchViewerPresenter(matchViewerView,
                                                       this->matchesViewerModel(),
                                                       this->settingsModel());
    mMatchesViewerPresenter->setHelp(this->helpDialog());

    connect(mMainWindowPresenter, SIGNAL(openMatchesViewerDialog()),                         mMatchesViewerPresenter, SLOT(open()));
    connect(mMainWindowPresenter, SIGNAL(openMatchesViewerDialog(QString,QString,QString)),  mMatchesViewerPresenter, SLOT(open(QString,QString,QString)));
  }
  return mMatchesViewerPresenter;
}

IMatchViewerModel *ComponentsManager::matchesViewerModel()
{
  if (mMatchesViewerModel == nullptr) {
    mMatchesViewerModel = new MatchViewerModel(this->projectModel());
  }
  return mMatchesViewerModel;
}

IMultiViewModel *ComponentsManager::multiviewModel()
{
  if (mMultiviewModel == nullptr) {
    mMultiviewModel = new MultiviewModel(mProjectModel);
  }
  return mMultiviewModel;
}

IMultiViewPresenter *ComponentsManager::multiviewPresenter()
{
  if (mMultiviewPresenter == nullptr){

    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    IMultiviewView *multiviewView = new MultiviewView(this->mainWindowView(), f);
    mMultiviewPresenter = new MultiViewPresenter(multiviewView, this->multiviewModel());
    mMultiviewPresenter->setHelp(this->helpDialog());
  }
  return mMultiviewPresenter;
}

IGroundTruthPresenter *ComponentsManager::groundTruthPresenter()
{
  if (mGroundTruthPresenter == nullptr){

    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    IGroundTruthView *groundTruthView = new GroundTruthView(this->mainWindowView(), f);
    mGroundTruthPresenter = new GroundTruthPresenter(groundTruthView,
                                                     this->groundTruthModel(),
                                                     this->settingsModel());
    mGroundTruthPresenter->setHelp(this->helpDialog());

    connect(mGroundTruthPresenter, SIGNAL(groundTruthAdded()), this->mMainWindowPresenter, SLOT(groundTruthAdded()));
  }
  return mGroundTruthPresenter;
}

IGroundTruthModel *ComponentsManager::groundTruthModel()
{
  if (mGroundTruthModel == nullptr){
    mGroundTruthModel = new GroundTruthModel(this->projectModel());
  }
  return mGroundTruthModel;
}

IHomographyViewerPresenter *ComponentsManager::homographyViewerPresenter()
{
  if (mHomographyViewerPresenter == nullptr) {
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    IHomographyViewerView *homographyViewerView = new HomographyViewerView(this->mainWindowView(), f);
    mHomographyViewerPresenter = new HomographyViewerPresenter(homographyViewerView,
                                                               this->homographyViewerModel(),
                                                               this->settingsModel());
    mHomographyViewerPresenter->setHelp(this->helpDialog());
  }
  return mHomographyViewerPresenter;
}

IHomographyViewerModel *ComponentsManager::homographyViewerModel()
{
  if (mHomographyViewerModel == nullptr){
    mHomographyViewerModel = new HomographyViewerModel(mProjectModel);
  }
  return mHomographyViewerModel;
}

ICurvesViewerPresenter *ComponentsManager::curvesPRViewerPresenter()
{
  if (mCurvesPRViewerPresenter == nullptr) {

    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    CurvesViewerView *curvesViewerView = new PRCurvesViewer(this->mainWindowView(), f);
    mCurvesPRViewerPresenter = new CurvesViewerPresenter(curvesViewerView, this->curvesPRViewerModel());
    mCurvesPRViewerPresenter->setHelp(this->helpDialog());
  }
  return mCurvesPRViewerPresenter;
}

ICurvesViewerModel *ComponentsManager::curvesPRViewerModel()
{
  if (mCurvesPRViewerModel == nullptr){
    mCurvesPRViewerModel = new PRCurvesViewerModel(mProjectModel);
  }
  return mCurvesPRViewerModel;
}

ICurvesViewerPresenter *ComponentsManager::curvesROCViewerPresenter()
{
  if (mCurvesROCViewerPresenter == nullptr) {
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    CurvesViewerView *curvesViewerView = new ROCCurvesViewer(this->mainWindowView(), f);
    mCurvesROCViewerPresenter = new CurvesViewerPresenter(curvesViewerView, this->curvesROCViewerModel());
    mCurvesROCViewerPresenter->setHelp(this->helpDialog());
  }
  return mCurvesROCViewerPresenter;
}

ICurvesViewerModel *ComponentsManager::curvesROCViewerModel()
{
  if (mCurvesROCViewerModel == nullptr){
    mCurvesROCViewerModel = new ROCCurvesViewerModel(mProjectModel);
  }
  return mCurvesROCViewerModel;
}

ICurvesViewerPresenter *ComponentsManager::curvesDETViewerPresenter()
{
  if (mCurvesDETViewerPresenter == nullptr) {
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    CurvesViewerView *curvesViewerView = new DETCurvesViewer(this->mainWindowView(), f);
    mCurvesDETViewerPresenter = new CurvesViewerPresenter(curvesViewerView, this->curvesDETViewerModel());
    mCurvesDETViewerPresenter->setHelp(this->helpDialog());
  }
  return mCurvesDETViewerPresenter;
}

ICurvesViewerModel *ComponentsManager::curvesDETViewerModel()
{
  if (mCurvesDETViewerModel == nullptr){
    mCurvesDETViewerModel = new DETCurvesViewerModel(mProjectModel);
  }
  return mCurvesDETViewerModel;
}

IRepeatabilityPresenter *ComponentsManager::repeatabilityPresenter()
{
  if (mRepeatabilityPresenter == nullptr){
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    IRepeatabilityView *repeatabilityView = new RepeatabilityView(this->mainWindowView(), f);
    mRepeatabilityPresenter = new RepeatabilityPresenter(repeatabilityView, this->repeatabilityModel());
    mRepeatabilityPresenter->setHelp(this->helpDialog());
  }
  return mRepeatabilityPresenter;
}

IRepeatabilityModel *ComponentsManager::repeatabilityModel()
{
  if (mRepeatabilityModel == nullptr) {
    mRepeatabilityModel = new RepeatabilityModel(mProjectModel);
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
  disconnect(mMainWindowPresenter, SIGNAL(openNewProjectDialog()), this, SLOT(initAndOpenNewProjectDialog()));
  this->newProjectPresenter()->open();
}

void ComponentsManager::initAndOpenNewSessionDialog()
{
  disconnect(mMainWindowPresenter, SIGNAL(openNewSessionDialog()), this, SLOT(initAndOpenNewSessionDialog()));
  this->newSessionPresenter()->open();
}

void ComponentsManager::initAndOpenPreprocessDialog()
{
  disconnect(mMainWindowPresenter, SIGNAL(openPreprocessDialog()), this, SLOT(initAndOpenPreprocessDialog()));
  this->preprocessPresenter()->open();
}

void ComponentsManager::initAndOpenFeatureExtractionDialog()
{
  disconnect(mMainWindowPresenter, SIGNAL(openFeatureExtractionDialog()), this, SLOT(initAndOpenFeatureExtractionDialog()));
  this->featureExtractorPresenter()->open();
}

void ComponentsManager::initAndOpenFeatureMatchingDialog()
{
  disconnect(mMainWindowPresenter, SIGNAL(openFeatureMatchingDialog()), this, SLOT(initAndOpenFeatureMatchingDialog()));
  this->descriptorMatcherPresenter()->open();
}

void ComponentsManager::initAndOpenKeypointsViewerDialog()
{
  disconnect(mMainWindowPresenter, SIGNAL(openKeypointsViewerDialog()), this, SLOT(initAndOpenKeypointsViewerDialog()));
  disconnect(mMainWindowPresenter, SIGNAL(openKeypointsViewerDialog(QString, QString)), this, SLOT(initAndOpenKeypointsViewerDialog(QString, QString)));
  this->featuresViewerPresenter()->setSession(this->projectModel()->currentSession()->name());
  this->featuresViewerPresenter()->open();
}

void ComponentsManager::initAndOpenKeypointsViewerDialog(const QString &session, const QString &image)
{
  disconnect(mMainWindowPresenter, SIGNAL(openKeypointsViewerDialog()), this, SLOT(initAndOpenKeypointsViewerDialog()));
  disconnect(mMainWindowPresenter, SIGNAL(openKeypointsViewerDialog(QString, QString)), this, SLOT(initAndOpenKeypointsViewerDialog(QString, QString)));
  this->featuresViewerPresenter()->setSession(session);
  this->featuresViewerPresenter()->open();
  this->featuresViewerPresenter()->setImageActive(image);
}

void ComponentsManager::initAndOpenMatchesViewerDialog()
{
  disconnect(mMainWindowPresenter, SIGNAL(openMatchesViewerDialog()),                   this, SLOT(initAndOpenMatchesViewerDialog()));
  disconnect(mMainWindowPresenter, SIGNAL(openMatchesViewerDialog(QString, QString)),   this, SLOT(initAndOpenMatchesViewerDialog(QString, QString)));
  this->matchesViewerPresenter()->open();
}

void ComponentsManager::initAndOpenMatchesViewerDialog(const QString &session, const QString &leftImage, const QString &rightImage)
{
  disconnect(mMainWindowPresenter, SIGNAL(openMatchesViewerDialog()),                   this, SLOT(initAndOpenMatchesViewerDialog()));
  disconnect(mMainWindowPresenter, SIGNAL(openMatchesViewerDialog(QString, QString)),   this, SLOT(initAndOpenMatchesViewerDialog(QString, QString)));
  this->matchesViewerPresenter()->setSession(session);
  this->matchesViewerPresenter()->open();
  this->matchesViewerPresenter()->setLeftImage(leftImage);
  this->matchesViewerPresenter()->setRightImage(rightImage);
}


} // namespace photomatch
