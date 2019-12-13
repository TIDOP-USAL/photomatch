#include "MainWindowPresenter.h"

#include "MainWindowView.h"
#include "MainWindowModel.h"

#include "ProjectModel.h"

#include "NewProjectPresenter.h"
#include "NewProjectView.h"

#include "NewSessionPresenter.h"
#include "NewSessionView.h"

#include "SettingsModel.h"
#include "SettingsPresenter.h"
#include "SettingsView.h"

#include "photomatch/ui/PreprocessModel.h"
#include "photomatch/ui/PreprocessView.h"
#include "photomatch/ui/PreprocessPresenter.h"
#include "photomatch/ui/FeatureExtractorModel.h"
#include "photomatch/ui/FeatureExtractorView.h"
#include "photomatch/ui/FeatureExtractorPresenter.h"
#include "photomatch/ui/DescriptorMatcherModel.h"  ///TODO: por ahora no tiene ninguna utilidad
#include "photomatch/ui/DescriptorMatcherView.h"
#include "photomatch/ui/DescriptorMatcherPresenter.h"
#include "photomatch/ui/FeaturesViewerModel.h"
#include "photomatch/ui/FeaturesViewerView.h"
#include "photomatch/ui/FeaturesViewerPresenter.h"
#include "photomatch/ui/MatchViewerModel.h"
#include "photomatch/ui/MatchViewerView.h"
#include "photomatch/ui/MatchViewerPresenter.h"
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
//#include "photomatch/ui/utils/KeyPointGraphicsItem.h"
#include "photomatch/ui/ExportFeaturesModel.h"
#include "photomatch/ui/ExportFeaturesView.h"
#include "photomatch/ui/ExportFeaturesPresenter.h"
#include "photomatch/ui/ExportMatchesModel.h"
#include "photomatch/ui/ExportMatchesView.h"
#include "photomatch/ui/ExportMatchesPresenter.h"
//#include "photomatch/ui/BatchModel.h"
//#include "photomatch/ui/BatchView.h"
//#include "photomatch/ui/BatchPresenter.h"
#include "photomatch/core/project.h"

/* TidopLib */
#include <tidop/core/messages.h>

/* Qt */
#include <QFileDialog>
#include <QMessageBox>
#include <QImageReader>
#include <QProgressBar>
#include <QMenu>

namespace photomatch
{

MainWindowPresenter::MainWindowPresenter(MainWindowView *view, MainWindowModel *model)
  : IPresenter(),
    mView(view),
    mModel(model),
    mProject(new Project),
    mProjectIO(new ProjectRW),
    mProjectModel(nullptr),
    mNewProjectPresenter(nullptr),
    mNewSessionPresenter(nullptr),
    mExportFeaturesPresenter(nullptr),
    mExportFeaturesModel(nullptr),
    mExportMatchesPresenter(nullptr),
    mExportMatchesModel(nullptr),
    mSettings(new Settings),
    mSettingsRW(new SettingsRW),
    mSettingsModel(nullptr),
    mSettingsPresenter(nullptr),
    mPreprocessModel(nullptr),
    mPreprocessPresenter(nullptr),
    mFeatureExtractorModel(nullptr),
    mFeatureExtractorPresenter(nullptr),
    mDescriptorMatcherModel(nullptr),
    mDescriptorMatcherPresenter(nullptr),
    //mBatchmodel(nullptr),
    //mBatchPresenter(nullptr),
    mFeaturesViewerPresenter(nullptr),
    mFeaturesViewerModel(nullptr),
    mMatchesViewerPresenter(nullptr),
    mMatchesViewerModel(nullptr),
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
    //mHelpDialog(nullptr),
    mProgressHandler(nullptr),
    mProgressDialog(nullptr)
{
  init();

  /* Menú Archivo */

  connect(mView, SIGNAL(openNew()),                       this, SLOT(openNew()));
  connect(mView, SIGNAL(openProject()),                   this, SLOT(openProject()));
  connect(mView, SIGNAL(openProjectFromHistory(QString)), this, SLOT(openFromHistory(QString)));  ///TODO: falta test señal
  connect(mView, SIGNAL(clearHistory()),                  this, SLOT(deleteHistory()));
  connect(mView, SIGNAL(exportTiePoints()),               this, SLOT(exportFeatures()));
  connect(mView, SIGNAL(exportMatches()),                 this, SLOT(exportMatches()));
//  connect(mView, SIGNAL(exportTiePointsCvXml()),          this, SLOT(exportTiePointsCvXml()));
//  connect(mView, SIGNAL(exportTiePointsCvYml()),          this, SLOT(exportTiePointsCvYml()));
//  connect(mView, SIGNAL(exportMatchesCvYml()),            this, SLOT(exportMatchesCvYml()));
//  connect(mView, SIGNAL(exportMatchesCvXml()),            this, SLOT(exportMatchesCvXml()));
//  connect(mView, SIGNAL(exportMatchesTxt()),              this, SLOT(exportMatchesTxt()));
  connect(mView, SIGNAL(saveProject()),                   this, SLOT(saveProject()));
  connect(mView, SIGNAL(saveProjectAs()),                 this, SLOT(saveProjectAs()));
  connect(mView, SIGNAL(closeProject()),                  this, SLOT(closeProject()));
  connect(mView, SIGNAL(exit()),                          this, SLOT(exit()));

  /* Menú View */

  connect(mView,   SIGNAL(openSettings()),            this, SLOT(openSettings()));
  connect(mView,   SIGNAL(openViewSettings()),        this, SLOT(openViewSettings()));

  /* Quality Control */

  connect(mView,  SIGNAL(featuresViewer()),           this, SLOT(openKeypointsViewer()));
  connect(mView,  SIGNAL(matchesViewer()),            this, SLOT(openMatchesViewer()));
  connect(mView,  SIGNAL(groundTruthEditor()),        this, SLOT(groundTruthEditor()));
  connect(mView,  SIGNAL(homography()),               this, SLOT(openHomographyViewer()));
  connect(mView,  SIGNAL(repeatability()),            this, SLOT(openRepeatability()));
  connect(mView,  SIGNAL(prCurves()),                 this, SLOT(openPRCurvesViewer()));
  connect(mView,  SIGNAL(rocCurves()),                this, SLOT(openROCCurvesViewer()));
  connect(mView,  SIGNAL(detCurves()),                this, SLOT(openDETCurvesViewer()));
  connect(mView,  SIGNAL(openQualityControlSettings()),
          this,   SLOT(openQualityControlSettings()));

  /* Menú herramientas */

  connect(mView,   SIGNAL(loadImages()),              this, SLOT(loadImages()));
  connect(mView,   SIGNAL(newSession()),              this, SLOT(newSession()));
  connect(mView,   SIGNAL(openPreprocess()),          this, SLOT(openPreprocess()));
  connect(mView,   SIGNAL(openFeatureExtraction()),   this, SLOT(openFeatureExtraction()));
  connect(mView,   SIGNAL(openFeatureMatching()),     this, SLOT(openFeatureMatching()));
  //connect(mView,   SIGNAL(openBatch()),               this, SLOT(openBatch()));
  connect(mView,   SIGNAL(openToolSettings()),        this, SLOT(openToolSettings()));

  /* Menú Ayuda */

  connect(mView, SIGNAL(openHelpDialog()),            this, SLOT(help()));
  connect(mView, SIGNAL(openAboutDialog()),           this, SLOT(openAboutDialog()));

  /* Panel de vistas en miniatura */

  connect(mView, SIGNAL(openImage(QString)),          this, SLOT(openImage(QString)));
  connect(mView, SIGNAL(selectImage(QString)),        this, SLOT(activeImage(QString)));
  connect(mView, SIGNAL(selectImages(QStringList)),   this, SLOT(activeImages(QStringList)));
  connect(mView, SIGNAL(deleteImages(QStringList)),   this, SLOT(deleteImages(QStringList)));
  connect(mView, SIGNAL(selectSession(QString)),      this, SLOT(selectSession(QString)));

  connect(mView, SIGNAL(selectPreprocess(QString)),   this, SLOT(selectPreprocess(QString)));
  connect(mView, SIGNAL(selectFeatures(QString)),     this, SLOT(selectFeatures(QString)));
  connect(mView, SIGNAL(selectDetector(QString)),     this, SLOT(selectDetector(QString)));
  connect(mView, SIGNAL(selectDescriptor(QString)),   this, SLOT(selectDescriptor(QString)));
  connect(mView, SIGNAL(selectImageFeatures(QString)),   this, SLOT(selectImageFeatures(QString)));

  /* Visor de imagenes */
  connect(mView, SIGNAL(loadKeyPoints(QString)),      this, SLOT(loadKeyPoints(QString)));
  connect(mView, SIGNAL(openImageMatches(QString,QString,QString)),   this, SLOT(openImageMatches(QString,QString,QString)));

  //connect(mProjectModel, SIGNAL(projectModified()), this, SLOT(updateProject()));

  connect(mView, SIGNAL(activeSessionChange(QString)), this, SLOT(activeSession(QString)));
  connect(mView, SIGNAL(delete_session(QString)),      this, SLOT(deleteSession(QString)));

  connect(mView, SIGNAL(openFeatures(QString, QString)),      this, SLOT(openKeypointsViewer(QString, QString)));
}

MainWindowPresenter::~MainWindowPresenter()
{
  if (mProjectIO) {
    delete mProjectIO;
    mProjectIO =nullptr;
  }

  if (mProject){
    delete mProject;
    mProject = nullptr;
  }

  if (mProjectModel) {
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

  if (mPreprocessModel){
    delete mPreprocessModel;
    mPreprocessModel = nullptr;
  }

  if (mPreprocessPresenter){
    delete mPreprocessPresenter;
    mPreprocessPresenter = nullptr;
  }

  if (mFeatureExtractorModel){
    delete mFeatureExtractorModel;
    mFeatureExtractorModel = nullptr;
  }

  if (mFeatureExtractorPresenter){
    delete mFeatureExtractorPresenter;
    mFeatureExtractorPresenter = nullptr;
  }

  if (mDescriptorMatcherModel){
    delete mDescriptorMatcherModel;
    mDescriptorMatcherModel = nullptr;
  }

  if (mDescriptorMatcherPresenter){
    delete mDescriptorMatcherPresenter;
    mDescriptorMatcherPresenter = nullptr;
  }

//  if (mBatchmodel){
//    delete mBatchmodel;
//    mBatchmodel = nullptr;
//  }

//  if (mBatchPresenter){
//    delete mBatchPresenter;
//    mBatchPresenter = nullptr;
//  }

  if (mProgressHandler){
    delete mProgressHandler;
    mProgressHandler = nullptr;
  }

  if (mProgressDialog){
    delete mProgressDialog;
    mProgressDialog = nullptr;
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
}

void MainWindowPresenter::openNew()
{
  if(mProjectModel->checkUnsavedChanges()) {
    int i_ret = QMessageBox(QMessageBox::Information,
                            tr("Save Changes"),
                            tr("There are unsaved changes. Do you want to save them?"),
                            QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel).exec();
    if (i_ret == QMessageBox::Yes) {
      saveProject();
    } else if (i_ret == QMessageBox::Cancel) {
      return;
    }
  }

  mView->clear();

  initNewProjectDialog();

  mNewProjectPresenter->open();
}

void MainWindowPresenter::openProject()
{
  QString file = QFileDialog::getOpenFileName(Q_NULLPTR,
                                              tr("Open PhotoMatch project"),
                                              mModel->defaultPath(),
                                              tr("PhotoMatch project (*.xml)"));
  if (!file.isEmpty()) {
    // Se comprueba si hay un proyecto abierto con cambios sin guardar
    if (mProjectModel->checkUnsavedChanges()) {
      int i_ret = QMessageBox(QMessageBox::Information,
                              tr("Save Changes"),
                              tr("There are unsaved changes. Do you want to save them?"),
                              QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel).exec();
      if (i_ret == QMessageBox::Yes) {
        saveProject();
      } else if (i_ret == QMessageBox::Cancel) {
        return;
      }
    }

    mProjectModel->clear();

    if (mProjectModel->checkOldVersion(file)){
      int i_ret = QMessageBox(QMessageBox::Information,
                              tr("It is loading an old project"),
                              tr("If you accept, a copy of the old project will be created"),
                              QMessageBox::Yes|QMessageBox::No).exec();
      if (i_ret == QMessageBox::Yes) {
        mProjectModel->oldVersionBak(file);
        mView->setFlag(MainWindowView::Flag::project_modified, true);
      } else if (i_ret == QMessageBox::Cancel) {
        return;
      }

    }
    mProjectModel->load(file);
    ///TODO: o cambiar el nombre o hacerlo de otra forma
    loadProject();
  }
}

void MainWindowPresenter::openFromHistory(const QString &file)
{
  if (QFileInfo(file).exists()) {

    // Se comprueba si hay un proyecto abierto con cambios sin guardar
    if(mProjectModel->checkUnsavedChanges()) {
      int i_ret = QMessageBox(QMessageBox::Information,
                              tr("Save Changes"),
                              tr("There are unsaved changes. Do you want to save them?"),
                              QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel).exec();
      if (i_ret == QMessageBox::Yes) {
        saveProject();
      } else if (i_ret == QMessageBox::Cancel) {
        return;
      }
    }

    mProjectModel->clear();

    if (mProjectModel->checkOldVersion(file)){
      int i_ret = QMessageBox(QMessageBox::Information,
                              tr("It is loading an old project"),
                              tr("If you accept, a copy of the old project will be created"),
                              QMessageBox::Yes|QMessageBox::No).exec();
      if (i_ret == QMessageBox::Yes) {
        mProjectModel->oldVersionBak(file);
        mView->setFlag(MainWindowView::Flag::project_modified, true);
      } else if (i_ret == QMessageBox::Cancel) {
        return;
      }

    }

    mProjectModel->load(file);
    loadProject();

  } else {
    QByteArray ba = file.toLocal8Bit();
    const char *cfile = ba.data();
    msgWarning("Project file not found: %s", cfile);
  }
}

void MainWindowPresenter::deleteHistory()
{
  mSettingsModel->clearHistory();
  mView->deleteHistory();
}

void MainWindowPresenter::saveProject()
{
  mProjectModel->save();
  mView->setFlag(MainWindowView::Flag::project_modified, false);
}

void MainWindowPresenter::saveProjectAs()
{
  QString file = QFileDialog::getSaveFileName(Q_NULLPTR,
                                              tr("Save project as..."),
                                              mModel->defaultPath(),
                                              tr("PhotoMatch project (*.xml)"));
  if (file.isEmpty() == false) {
    mProjectModel->saveAs(file);
    mView->setFlag(MainWindowView::Flag::project_modified, false);
  }
}

void MainWindowPresenter::exportFeatures()
{
  initExportFeaturesDialog();

  mExportFeaturesPresenter->open();
}

void MainWindowPresenter::exportMatches()
{
  initExportMatchesDialog();

  mExportMatchesPresenter->open();
}

//void MainWindowPresenter::exportTiePointsCvXml()
//{
//  QString pathName = QFileDialog::getExistingDirectory(nullptr,
//                                                       tr("Export directory"),
//                                                       "",
//                                                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

//  if (!pathName.isEmpty()) {

//    TL_TODO("Permitir exportar otras sesiones a parte de la activa")
//    //mModel->exportTiePointsCvXml(pathName);

//  }
//}

//void MainWindowPresenter::exportTiePointsCvYml()
//{
//  QString pathName = QFileDialog::getExistingDirectory(nullptr,
//                                                       tr("Export directory"),
//                                                       "",
//                                                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

//  if (!pathName.isEmpty()) {

//  }
//}

//void MainWindowPresenter::exportMatchesCvYml()
//{
//  QString pathName = QFileDialog::getExistingDirectory(nullptr,
//                                                       tr("Export directory"),
//                                                       "",
//                                                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

//  if (!pathName.isEmpty()) {

//  }
//}

//void MainWindowPresenter::exportMatchesCvXml()
//{
//  QString pathName = QFileDialog::getExistingDirectory(nullptr,
//                                                       tr("Export directory"),
//                                                       "",
//                                                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

//  if (!pathName.isEmpty()) {

//  }
//}

//void MainWindowPresenter::exportMatchesTxt()
//{
//  QString pathName = QFileDialog::getExistingDirectory(nullptr,
//                                                       tr("Export directory"),
//                                                       "",
//                                                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

//  if (!pathName.isEmpty()) {

//  }
//}

void MainWindowPresenter::closeProject()
{
  if(mProjectModel->checkUnsavedChanges()){
    int i_ret = QMessageBox(QMessageBox::Information,
                            tr("Save Changes"),
                            tr("There are unsaved changes. Do you want to save the changes before closing the project?"),
                            QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel).exec();
    if (i_ret == QMessageBox::Yes) {
      saveProject();
    } else if (i_ret == QMessageBox::Cancel) {
      return;
    }
  }

  mProjectModel->clear();
///TODO:  mModel->finishLog();
  mView->clear();
  mView->setWindowTitle(QString("PhotoMatch"));
}

void MainWindowPresenter::exit()
{
  ///TODO: Se cierra la aplicación
  /// - Comprobar que no haya ningún procesos corriendo
  /// - Si hay cambios sin guardar se debe preguntar
  if(mProjectModel->checkUnsavedChanges()){
    int i_ret = QMessageBox(QMessageBox::Information,
                            tr("Save Changes"),
                            tr("There are unsaved changes. Do you want to save the changes before closing the project?"),
                            QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel).exec();
    if (i_ret == QMessageBox::Yes) {
      saveProject();
      //mView->saveWindowState();
    } else if (i_ret == QMessageBox::Cancel) {
      return;
    }
  }

  mView->close();
}

void MainWindowPresenter::openSettings()
{
  initSettingsDialog();
  mSettingsPresenter->open();
}

void MainWindowPresenter::openViewSettings()
{
  initSettingsDialog();
  mSettingsPresenter->openPage(1);
}

void MainWindowPresenter::openKeypointsViewer()
{
  initFeaturesViewer();
  mFeaturesViewerPresenter->open();
}

void MainWindowPresenter::openKeypointsViewer(const QString &session, const QString &image)
{
  initFeaturesViewer();
  mFeaturesViewerPresenter->setSession(session);
  mFeaturesViewerPresenter->open();
  mFeaturesViewerPresenter->setImageActive(image);
  
}

void MainWindowPresenter::openMatchesViewer()
{
  initMatchesViewer();
  mMatchesViewerPresenter->open();
}

void MainWindowPresenter::groundTruthEditor()
{
  initGroundTruthEditor();
  mGroundTruthPresenter->open();
}

void MainWindowPresenter::openHomographyViewer()
{
  initHomographyViewer();
  mHomographyViewerPresenter->open();
}

void MainWindowPresenter::openRepeatability()
{
  initRepeatability();
  mRepeatabilityPresenter->open();
}

void MainWindowPresenter::openPRCurvesViewer()
{
  initPRCurvesViewer();
  mCurvesPRViewerPresenter->open();
}

void MainWindowPresenter::openROCCurvesViewer()
{
  initROCCurvesViewer();
  mCurvesROCViewerPresenter->open();
}

void MainWindowPresenter::openDETCurvesViewer()
{
  initDETCurvesViewer();
  mCurvesDETViewerPresenter->open();
}

void MainWindowPresenter::openQualityControlSettings()
{
  initSettingsDialog();
  mSettingsPresenter->openPage(3);
}

void MainWindowPresenter::loadImages()
{
  QStringList fileNames = QFileDialog::getOpenFileNames(Q_NULLPTR,
                                                        tr("Add images"),
                                                        mProjectModel->projectFolder(),
                                                        tr("Image files (*.tif *.tiff *.jpg *.png);;TIFF (*.tif *.tiff);;png (*.png);;JPEG (*.jpg)"));
  if (fileNames.size() > 0) {

    mProjectModel->addImages(fileNames);

    mView->addImages(fileNames);

    msgInfo("Load images");

    mView->setFlag(MainWindowView::Flag::project_modified, true);
    mView->setFlag(MainWindowView::Flag::images_added, true);
  }
}

void MainWindowPresenter::newSession()
{
  initNewSessionDialog();

  mNewSessionPresenter->open();
}

void MainWindowPresenter::openPreprocess()
{
  initPreprocessDialog();
  mPreprocessPresenter->open();
}

void MainWindowPresenter::openFeatureExtraction()
{
  initFeatureExtractionDialog();
  mFeatureExtractorPresenter->open();
}

void MainWindowPresenter::openFeatureMatching()
{
  initFeatureMatching();
  mDescriptorMatcherPresenter->open();
}

//void MainWindowPresenter::openBatch()
//{
//  initBatch();
//  mBatchPresenter->open();
//}

void MainWindowPresenter::openToolSettings()
{
  initSettingsDialog();
  mSettingsPresenter->openPage(2);
}

void MainWindowPresenter::openAboutDialog()
{
  initAboutDialog();
  mAboutDialog->show();
}

void MainWindowPresenter::loadProject()
{
  mView->clear();

  QString prjFile = mProjectModel->path();

  /// Se añade al historial de proyectos recientes
  mSettingsModel->addToHistory(prjFile);
  mView->updateHistory(mSettingsModel->history());


  mView->setProjectTitle(mProjectModel->name());
  mView->setFlag(MainWindowView::Flag::project_exists, true);
  QString msg = tr("Load project: ").append(prjFile);
  mView->setStatusBarMsg(msg);
  QByteArray ba = prjFile.toLocal8Bit();
  const char *cfile = ba.data();
  msgInfo("Load project: %s", cfile);

  if (mProjectModel->groundTruth().isEmpty() == false)
    mView->setFlag(MainWindowView::Flag::ground_truth, true);

  QStringList images;
  TL_TODO("Los iteradores sobre las imagenes deberian ser constantes unicamente para evitar que se modifiquen las imagenes. El problema es que no se notificaria al proyecto que ha cambiado")
  for(auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    images.push_back((*it)->path());
  }

  if (images.size() > 0){
    mView->addImages(images);
    mView->setFlag(MainWindowView::Flag::images_added, true);
  }

  if (mProjectModel->sessionCount() > 0 && mProjectModel->currentSession() == nullptr){
    auto it = mProjectModel->sessionBegin();
    mProjectModel->setCurrentSession((*it)->name());
  }

  for (auto it = mProjectModel->sessionBegin(); it != mProjectModel->sessionEnd(); it++){


    bool bActive = mProjectModel->currentSession()->name().compare((*it)->name()) == 0;

    mView->addSession((*it)->name(), (*it)->description());
    if (bActive) mView->setActiveSession((*it)->name());
    mView->setFlag(MainWindowView::Flag::session_created, true);

    bool bPreprocess = loadPreprocess((*it)->name());
    if (bPreprocess){
      bool bFeatures = loadFeatures((*it)->name());
      if (bFeatures){
        loadMatches((*it)->name());
      }
    }

  }

}

void MainWindowPresenter::updateProject()
{

}

void MainWindowPresenter::openImage(const QString &image)
{
  mView->showImage(image);
//  if (mView->showKeyPoints()){
//    this->loadKeyPoints(image);
//  }
}

void MainWindowPresenter::activeImage(const QString &image)
{
  std::list<std::pair<QString, QString>> properties = mModel->exif(image);
  mView->setProperties(properties);
  mView->setActiveImage(image);
}

void MainWindowPresenter::activeImages(const QStringList &images)
{
  mView->setActiveImages(images);
}

void MainWindowPresenter::deleteImages(const QStringList &images)
{
  mProjectModel->deleteImages(images);
  TL_TODO("Se tienen que eliminar del proyecto las imagenes procesadas, y los ficheros de keypoints y de matches")
  for (const auto &image : images){
    mView->deleteImage(image);
    TL_TODO("Se tienen que eliminar de la vista las imagenes procesadas, y los ficheros de keypoints y de matches")
  }
  mView->setFlag(MainWindowView::Flag::project_modified, true);

  mView->setFlag(MainWindowView::Flag::images_added, mProjectModel->imagesCount() > 0);
}

void MainWindowPresenter::loadSession(const QString &session)
{
  std::shared_ptr<Session> _session = mProjectModel->findSession(session);

  mView->addSession(_session->name(), _session->description());

  mView->setFlag(MainWindowView::Flag::session_created, true);
  mView->setFlag(MainWindowView::Flag::project_modified, true);
  mView->setFlag(MainWindowView::Flag::preprocess, false);
  mView->setFlag(MainWindowView::Flag::feature_extraction, false);
  mView->setFlag(MainWindowView::Flag::feature_matching, false);
}

void MainWindowPresenter::selectSession(const QString &session)
{
  TL_TODO("recuperar información de la sesión y mostrarla en la ventana de propiedades")
}

void MainWindowPresenter::activeSession(const QString &session)
{
  mProjectModel->setCurrentSession(session);
  mView->setActiveSession(session);
  mView->setFlag(MainWindowView::Flag::project_modified, true);

  TL_TODO("Por ahora pero hay que revisarlo")
  updatePreprocess();
  updateFeatures();
  updateMatches();
}

void MainWindowPresenter::selectPreprocess(const QString &session)
{
  std::shared_ptr<Session> _session = mProjectModel->findSession(session);
  if (_session){
    std::shared_ptr<Preprocess> preprocess = _session->preprocess();
    if (preprocess){
      std::list<std::pair<QString, QString>> properties;
      if (preprocess->type() == Preprocess::Type::acebsf){
        IAcebsf *acebsf = dynamic_cast<IAcebsf *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), QString("ACEBSF")));
        properties.push_back(std::make_pair(QString("Block Size"), QString::number(acebsf->blockSize().width()).append("x").append(QString::number(acebsf->blockSize().height()))));
        properties.push_back(std::make_pair(QString("L"), QString::number(acebsf->l())));
        properties.push_back(std::make_pair(QString("K1"), QString::number(acebsf->k1())));
        properties.push_back(std::make_pair(QString("K2"), QString::number(acebsf->k2())));
      } else if (preprocess->type() == Preprocess::Type::clahe){
        IClahe *clahe = dynamic_cast<IClahe *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), QString("CLAHE")));
        properties.push_back(std::make_pair(QString("Clip Limit"), QString::number(clahe->clipLimit())));
        properties.push_back(std::make_pair(QString("Grid Size"),
                                            QString::number(clahe->tilesGridSize().width())
                                            .append("x")
                                            .append(QString::number(clahe->tilesGridSize().height()))));
      } else if (preprocess->type() == Preprocess::Type::cmbfhe){
        ICmbfhe *cmbfhe = dynamic_cast<ICmbfhe *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "CMBFHE"));
        properties.push_back(std::make_pair(QString("Block Size"),
                                            QString::number(cmbfhe->blockSize().width()).append("x").append(QString::number(cmbfhe->blockSize().height()))));
      } else if (preprocess->type() == Preprocess::Type::decolor){
        properties.push_back(std::make_pair(QString("Name"), "Decolor"));
      } else if (preprocess->type() == Preprocess::Type::dhe){
        IDhe *dhe = dynamic_cast<IDhe *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "DHE"));
        properties.push_back(std::make_pair(QString("X"), QString::number(dhe->x())));
      } else if (preprocess->type() == Preprocess::Type::fahe){
        IFahe *fahe = dynamic_cast<IFahe *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "FAHE"));
        properties.push_back(std::make_pair(QString("Block Size"),
                                            QString::number(fahe->blockSize().width())
                                            .append("x")
                                            .append(QString::number(fahe->blockSize().height()))));
      } else if (preprocess->type() == Preprocess::Type::hmclahe){
        IHmclahe *hmclahe = dynamic_cast<IHmclahe *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "HMCLAHE"));
        properties.push_back(std::make_pair(QString("Block Size"),
                                            QString::number(hmclahe->blockSize().width())
                                            .append("x")
                                            .append(QString::number(hmclahe->blockSize().height()))));
        properties.push_back(std::make_pair(QString("L"), QString::number(hmclahe->l())));
        properties.push_back(std::make_pair(QString("Phi"), QString::number(hmclahe->phi())));
      } else if (preprocess->type() == Preprocess::Type::lce_bsescs){
        ILceBsescs *lceBsescs = dynamic_cast<ILceBsescs *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "LCE_BSESCS"));
        properties.push_back(std::make_pair(QString("Block Size"),
                                            QString::number(lceBsescs->blockSize().width())
                                            .append("x")
                                            .append(QString::number(lceBsescs->blockSize().height()))));
      } else if (preprocess->type() == Preprocess::Type::msrcp){
        IMsrcp *msrcp = dynamic_cast<IMsrcp *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "MSRCP"));
        properties.push_back(std::make_pair(QString("Small Scale"), QString::number(msrcp->smallScale())));
        properties.push_back(std::make_pair(QString("Mid Scale"), QString::number(msrcp->midScale())));
        properties.push_back(std::make_pair(QString("Large Scale"), QString::number(msrcp->largeScale())));
      } else if (preprocess->type() == Preprocess::Type::noshp){
        INoshp *noshp = dynamic_cast<INoshp *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "NOSHP"));
        properties.push_back(std::make_pair(QString("Block Size"),
                                            QString::number(noshp->blockSize().width())
                                            .append("x")
                                            .append(QString::number(noshp->blockSize().height()))));
      } else if (preprocess->type() == Preprocess::Type::pohe){
        IPohe *pohe = dynamic_cast<IPohe *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "POHE"));
        properties.push_back(std::make_pair(QString("Block Size"),
                                            QString::number(pohe->blockSize().width())
                                            .append("x")
                                            .append(QString::number(pohe->blockSize().height()))));
      } else if (preprocess->type() == Preprocess::Type::rswhe){
        IRswhe *rswhe = dynamic_cast<IRswhe *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "RSWHE"));
        properties.push_back(std::make_pair(QString("Histogram Divisions"), QString::number(rswhe->histogramDivisions())));
        properties.push_back(std::make_pair(QString("Histogram Cut"), QString::number(static_cast<int>(rswhe->histogramCut()))));
      } else if (preprocess->type() == Preprocess::Type::wallis){
        IWallis *wallis = dynamic_cast<IWallis *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "WALLIS"));
        properties.push_back(std::make_pair(QString("Contrast"), QString::number(wallis->contrast())));
        properties.push_back(std::make_pair(QString("Brightness"), QString::number(wallis->brightness())));
        properties.push_back(std::make_pair(QString("Imposed Average"), QString::number(wallis->imposedAverage())));
        properties.push_back(std::make_pair(QString("Imposed Local Std Dev"), QString::number(wallis->imposedLocalStdDev())));
        properties.push_back(std::make_pair(QString("Kernel Size"), QString::number(wallis->kernelSize())));
      }
      mView->setProperties(properties);
    }
  }
}

void MainWindowPresenter::selectFeatures(const QString &session)
{
  std::shared_ptr<Session> _session = mProjectModel->findSession(session);
  std::shared_ptr<Feature> detector = _session->detector();
  std::shared_ptr<Feature> descriptor = _session->descriptor();

  QString detector_name = detector->name();
  QString descriptor_name = descriptor->name();

  std::list<std::pair<QString, QString>> properties;
  properties.push_back(std::make_pair(QString("Detector"), detector_name));
  properties.push_back(std::make_pair(QString("Descriptor"), descriptor_name));
  mView->setProperties(properties);
}

void MainWindowPresenter::selectDetector(const QString &session)
{
  std::shared_ptr<Session> _session = mProjectModel->findSession(session);
  std::shared_ptr<Feature> detector = _session->detector();

  std::list<std::pair<QString, QString>> properties;
  if (detector->type() == Feature::Type::agast){
    IAgast *agast = dynamic_cast<IAgast *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("AGAST")));
    properties.push_back(std::make_pair(QString("Threshold"), QString(agast->threshold())));
    properties.push_back(std::make_pair(QString("Nonmax Suppression"), agast->nonmaxSuppression() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Detector Type"), QString(agast->detectorType())));
  } else if (detector->type() == Feature::Type::akaze){
    IAkaze *akaze = dynamic_cast<IAkaze *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("AKAZE")));
    properties.push_back(std::make_pair(QString("Descriptor Type"), QString(akaze->descriptorType())));
    properties.push_back(std::make_pair(QString("Descriptor Size"), QString::number(akaze->descriptorSize())));
    properties.push_back(std::make_pair(QString("Descriptor Channels"), QString::number(akaze->descriptorChannels())));
    properties.push_back(std::make_pair(QString("Threshold"), QString::number(akaze->threshold())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(akaze->octaves())));
    properties.push_back(std::make_pair(QString("Octave Layers"), QString::number(akaze->octaveLayers())));
    properties.push_back(std::make_pair(QString("Diffusivity"), akaze->diffusivity()));
  } else if (detector->type() == Feature::Type::brisk){
    IBrisk *brisk = dynamic_cast<IBrisk *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("BRISK")));
    properties.push_back(std::make_pair(QString("Threshold"), QString::number(brisk->threshold())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(brisk->octaves())));
    properties.push_back(std::make_pair(QString("Pattern Scale"), QString::number(brisk->patternScale())));
  } else if (detector->type() == Feature::Type::fast){
    IFast *fast = dynamic_cast<IFast *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("FAST")));
    properties.push_back(std::make_pair(QString("Threshold"), QString::number(fast->threshold())));
    properties.push_back(std::make_pair(QString("Nonmax Suppression"), fast->nonmaxSuppression() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Detector Type"), QString(fast->detectorType())));
  } else if (detector->type() == Feature::Type::gftt){
    IGftt *gftt = dynamic_cast<IGftt *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("GFTT")));
    properties.push_back(std::make_pair(QString("Max Features"), QString::number(gftt->maxFeatures())));
    properties.push_back(std::make_pair(QString("Quality Level"), QString::number(gftt->qualityLevel())));
    properties.push_back(std::make_pair(QString("Min Distance"), QString::number(gftt->minDistance())));
    properties.push_back(std::make_pair(QString("Block Size"), QString::number(gftt->blockSize())));
    properties.push_back(std::make_pair(QString("Harris Detector"), gftt->harrisDetector() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("K"), QString::number(gftt->k())));
  } else if (detector->type() == Feature::Type::kaze){
    IKaze *kaze = dynamic_cast<IKaze *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("KAZE")));
    properties.push_back(std::make_pair(QString("Extended Descriptor"), kaze->extendedDescriptor() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Upright"), kaze->upright() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Threshold"), QString::number(kaze->threshold())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(kaze->octaves())));
    properties.push_back(std::make_pair(QString("Octave Layers"), QString::number(kaze->octaveLayers())));
    properties.push_back(std::make_pair(QString("Diffusivity"), kaze->diffusivity()));
  } else if (detector->type() == Feature::Type::msd){
    IMsd *msd = dynamic_cast<IMsd *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("MSD")));
    properties.push_back(std::make_pair(QString("Threshold Saliency"), QString::number(msd->thresholdSaliency())));
    properties.push_back(std::make_pair(QString("Patch Radius"), QString::number(msd->knn())));
    properties.push_back(std::make_pair(QString("Search Area Radius"), QString::number(msd->searchAreaRadius())));
    properties.push_back(std::make_pair(QString("Scale Factor"), QString::number(msd->scaleFactor())));
    properties.push_back(std::make_pair(QString("NMS Radius"), QString::number(msd->NMSRadius())));
    properties.push_back(std::make_pair(QString("NScales"), QString::number(msd->nScales())));
    properties.push_back(std::make_pair(QString("NMS Scale Radius"), QString::number(msd->NMSScaleRadius())));
    properties.push_back(std::make_pair(QString("Compute Orientation"), msd->computeOrientation() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Affine MSD"), msd->affineMSD() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Affine Tilts"),QString::number(msd->affineTilts())));
  } else if (detector->type() == Feature::Type::mser){
    IMser *mser = dynamic_cast<IMser *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("MSER")));
    properties.push_back(std::make_pair(QString("Delta"), QString::number(mser->delta())));
    properties.push_back(std::make_pair(QString("Min Area"), QString::number(mser->minArea())));
    properties.push_back(std::make_pair(QString("Max Area"), QString::number(mser->maxArea())));
    properties.push_back(std::make_pair(QString("Max Variation"), QString::number(mser->maxVariation())));
    properties.push_back(std::make_pair(QString("Min Diversity"), QString::number(mser->minDiversity())));
    properties.push_back(std::make_pair(QString("Max Evolution"), QString::number(mser->maxEvolution())));
    properties.push_back(std::make_pair(QString("Area Threshold"), QString::number(mser->areaThreshold())));
    properties.push_back(std::make_pair(QString("Min Margin"), QString::number(mser->minMargin())));
    properties.push_back(std::make_pair(QString("Edge Blur Size"), QString::number(mser->edgeBlurSize())));
  } else if (detector->type() == Feature::Type::orb){
    IOrb *orb = dynamic_cast<IOrb *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("ORB")));
    properties.push_back(std::make_pair(QString("Features Number"), QString::number(orb->featuresNumber())));
    properties.push_back(std::make_pair(QString("Scale Factor"), QString::number(orb->scaleFactor())));
    properties.push_back(std::make_pair(QString("Levels Number"), QString::number(orb->levelsNumber())));
    properties.push_back(std::make_pair(QString("Edge Threshold"), QString::number(orb->edgeThreshold())));
    properties.push_back(std::make_pair(QString("Wta k"), QString::number(orb->wta_k())));
    properties.push_back(std::make_pair(QString("Score Type"), orb->scoreType()));
    properties.push_back(std::make_pair(QString("Patch Size"), QString::number(orb->patchSize())));
    properties.push_back(std::make_pair(QString("Fast Threshold"), QString::number(orb->fastThreshold())));
  } else if (detector->type() == Feature::Type::sift){
    ISift *sift = dynamic_cast<ISift *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("SIFT")));
    properties.push_back(std::make_pair(QString("Features Number"), QString::number(sift->featuresNumber())));
    properties.push_back(std::make_pair(QString("Octave Layers"), QString::number(sift->octaveLayers())));
    properties.push_back(std::make_pair(QString("Contrast Threshold"), QString::number(sift->contrastThreshold())));
    properties.push_back(std::make_pair(QString("Edge Threshold"), QString::number(sift->edgeThreshold())));
    properties.push_back(std::make_pair(QString("Sigma"), QString::number(sift->sigma())));
  } else if (detector->type() == Feature::Type::star){
    IStar *star = dynamic_cast<IStar *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("STAR")));
    properties.push_back(std::make_pair(QString("Max Size"), QString::number(star->maxSize())));
    properties.push_back(std::make_pair(QString("Response Threshold"), QString::number(star->responseThreshold())));
    properties.push_back(std::make_pair(QString("Line Threshold Projected"), QString::number(star->lineThresholdProjected())));
    properties.push_back(std::make_pair(QString("Line Threshold Binarized"), QString::number(star->lineThresholdBinarized())));
    properties.push_back(std::make_pair(QString("Suppress Nonmax Size"), QString::number(star->suppressNonmaxSize())));
  } else if (detector->type() == Feature::Type::surf){
    ISurf *surf = dynamic_cast<ISurf *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("SURF")));
    properties.push_back(std::make_pair(QString("Hessian Threshold"), QString::number(surf->hessianThreshold())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(surf->octaves())));
    properties.push_back(std::make_pair(QString("Octave Layers"), QString::number(surf->octaveLayers())));
    properties.push_back(std::make_pair(QString("Extended Descriptor"), surf->extendedDescriptor() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Rotated Features"), surf->rotatedFeatures() ? "true" : "false"));
  }

  mView->setProperties(properties);
}

void MainWindowPresenter::selectDescriptor(const QString &session)
{
  std::shared_ptr<Session> _session = mProjectModel->findSession(session);
  std::shared_ptr<Feature> descriptor = _session->descriptor();

  std::list<std::pair<QString, QString>> properties;
  if (descriptor->type() == Feature::Type::akaze){
    IAkaze *akaze = dynamic_cast<IAkaze *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("AKAZE")));
    properties.push_back(std::make_pair(QString("Descriptor Type"), QString(akaze->descriptorType())));
    properties.push_back(std::make_pair(QString("Descriptor Size"), QString::number(akaze->descriptorSize())));
    properties.push_back(std::make_pair(QString("Descriptor Channels"), QString::number(akaze->descriptorChannels())));
    properties.push_back(std::make_pair(QString("Threshold"), QString::number(akaze->threshold())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(akaze->octaves())));
    properties.push_back(std::make_pair(QString("Octave Layers"), QString::number(akaze->octaveLayers())));
    properties.push_back(std::make_pair(QString("Diffusivity"), akaze->diffusivity()));
  } else if (descriptor->type() == Feature::Type::brief){
    IBrief *brief = dynamic_cast<IBrief *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("BRIEF")));
    properties.push_back(std::make_pair(QString("Bytes"), brief->bytes()));
    properties.push_back(std::make_pair(QString("Use Orientation"), brief->useOrientation() ? "true" : "false"));
  } else if (descriptor->type() == Feature::Type::brisk){
    IBrisk *brisk = dynamic_cast<IBrisk *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("BRISK")));
    properties.push_back(std::make_pair(QString("Threshold"), QString::number(brisk->threshold())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(brisk->octaves())));
    properties.push_back(std::make_pair(QString("Pattern Scale"), QString::number(brisk->patternScale())));
  } else if (descriptor->type() == Feature::Type::daisy){
    IDaisy *daisy = dynamic_cast<IDaisy *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("DAISY")));
    properties.push_back(std::make_pair(QString("Q Radius"), QString::number(daisy->radius())));
    properties.push_back(std::make_pair(QString("Q Theta"), QString::number(daisy->qRadius())));
    properties.push_back(std::make_pair(QString("Q Hist Scale"), QString::number(daisy->qTheta())));
    properties.push_back(std::make_pair(QString("Q Radius"), QString::number(daisy->qHist())));
    properties.push_back(std::make_pair(QString("Norm"), daisy->norm()));
    properties.push_back(std::make_pair(QString("Interpolation"), daisy->interpolation() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Use Orientation"), daisy->useOrientation() ? "true" : "false"));
  } else if (descriptor->type() == Feature::Type::freak){
    IFreak *freak = dynamic_cast<IFreak *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("FREAK")));
    properties.push_back(std::make_pair(QString("Orientation Normalized"), freak->orientationNormalized() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Scale Normalized"), freak->scaleNormalized() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("PatternScale"), QString::number(freak->patternScale())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(freak->octaves())));
  } else if (descriptor->type() == Feature::Type::hog){
    IHog *hog = dynamic_cast<IHog *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("HOG")));
    properties.push_back(std::make_pair(QString("Window Size"), QString::number(hog->winSize().width()).append("x").append(QString::number(hog->winSize().height()))));
    properties.push_back(std::make_pair(QString("Block Size"), QString::number(hog->blockSize().width()).append("x").append(QString::number(hog->blockSize().height()))));
    properties.push_back(std::make_pair(QString("Block Stride"), QString::number(hog->blockStride().width()).append("x").append(QString::number(hog->blockStride().height()))));
    properties.push_back(std::make_pair(QString("Cell Size"), QString::number(hog->cellSize().width()).append("x").append(QString::number(hog->cellSize().height()))));
    properties.push_back(std::make_pair(QString("Nbins"), QString::number(hog->nbins())));
    properties.push_back(std::make_pair(QString("DerivAperture"), QString::number(hog->derivAperture())));
  } else if (descriptor->type() == Feature::Type::kaze){
    IKaze *kaze = dynamic_cast<IKaze *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("KAZE")));
    properties.push_back(std::make_pair(QString("Extended Descriptor"), kaze->extendedDescriptor() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Upright"), kaze->upright() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Threshold"), QString::number(kaze->threshold())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(kaze->octaves())));
    properties.push_back(std::make_pair(QString("Octave Layers"), QString::number(kaze->octaveLayers())));
    properties.push_back(std::make_pair(QString("Diffusivity"), kaze->diffusivity()));
  } else if (descriptor->type() == Feature::Type::latch){
    ILatch *latch = dynamic_cast<ILatch *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("LATCH")));
    properties.push_back(std::make_pair(QString("Bytes"), latch->bytes()));
    properties.push_back(std::make_pair(QString("Rotation Invariance"), latch->rotationInvariance() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Half SSD Size"), QString::number(latch->halfSsdSize())));
  } else if (descriptor->type() == Feature::Type::lucid){
    ILucid *lucid = dynamic_cast<ILucid *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("LUCID")));
    properties.push_back(std::make_pair(QString("LUCID Kernel"), QString::number(lucid->lucidKernel())));
    properties.push_back(std::make_pair(QString("Blur Kernel"), QString::number(lucid->blurKernel())));
  } else if (descriptor->type() == Feature::Type::orb){
    IOrb *orb = dynamic_cast<IOrb *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("ORB")));
    properties.push_back(std::make_pair(QString("Features Number"), QString::number(orb->featuresNumber())));
    properties.push_back(std::make_pair(QString("Scale Factor"), QString::number(orb->scaleFactor())));
    properties.push_back(std::make_pair(QString("Levels Number"), QString::number(orb->levelsNumber())));
    properties.push_back(std::make_pair(QString("Edge Threshold"), QString::number(orb->edgeThreshold())));
    properties.push_back(std::make_pair(QString("Wta k"), QString::number(orb->wta_k())));
    properties.push_back(std::make_pair(QString("Score Type"), orb->scoreType()));
    properties.push_back(std::make_pair(QString("Patch Size"), QString::number(orb->patchSize())));
    properties.push_back(std::make_pair(QString("Fast Threshold"), QString::number(orb->fastThreshold())));
  } else if (descriptor->type() == Feature::Type::sift){
    ISift *sift = dynamic_cast<ISift *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("SIFT")));
    properties.push_back(std::make_pair(QString("Features Number"), QString::number(sift->featuresNumber())));
    properties.push_back(std::make_pair(QString("Octave Layers"), QString::number(sift->octaveLayers())));
    properties.push_back(std::make_pair(QString("Contrast Threshold"), QString::number(sift->contrastThreshold())));
    properties.push_back(std::make_pair(QString("Edge Threshold"), QString::number(sift->edgeThreshold())));
    properties.push_back(std::make_pair(QString("Sigma"), QString::number(sift->sigma())));
  } else if (descriptor->type() == Feature::Type::surf){
    ISurf *surf = dynamic_cast<ISurf *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("SURF")));
    properties.push_back(std::make_pair(QString("Hessian Threshold"), QString::number(surf->hessianThreshold())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(surf->octaves())));
    properties.push_back(std::make_pair(QString("Octave Layers"), QString::number(surf->octaveLayers())));
    properties.push_back(std::make_pair(QString("Extended Descriptor"), surf->extendedDescriptor() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Rotated Features"), surf->rotatedFeatures() ? "true" : "false"));
  }

  mView->setProperties(properties);
}

void MainWindowPresenter::selectImageFeatures(const QString &imageFeatures)
{
  std::vector<QPointF> feat = mModel->loadKeyPointsCoordinates(imageFeatures);
  std::list<std::pair<QString, QString>> properties;
  properties.push_back(std::make_pair(QString("Features"), QString::number(feat.size())));
  mView->setProperties(properties);
}

void MainWindowPresenter::openImageMatches(const QString &sessionName, const QString &imgName1, const QString &imgName2)
{
  std::vector<std::pair<QPointF, QPointF>> matches;
  QString imgPath1 = mProjectModel->findImageByName(imgName1)->path();
  QString imgPath2 = mProjectModel->findImageByName(imgName2)->path();

  if (QFileInfo(imgPath1).exists() == false || QFileInfo(imgPath2).exists() == false)
    return;

  if (std::shared_ptr<Session> session = mProjectModel->findSession(sessionName)){

    std::vector<std::pair<QString, QString>> pairs = session->matches(imgName1);
    if (!pairs.empty()){
      for (auto &pair : pairs){
        if (pair.first.compare(imgName2) == 0){
          matches = mModel->loadMatches(pair.second, session->features(imgName1), session->features(imgName2));

          break;
        }
      }
    }
  }

  mView->showMatches(imgPath1, imgPath2, matches);
}

void MainWindowPresenter::updatePreprocess()
{
  std::shared_ptr<Session> _session = mProjectModel->currentSession();
  if (_session){
    bool project_modified = loadPreprocess(_session->name());
    if (project_modified)
      mView->setFlag(MainWindowView::Flag::project_modified, true);
  }
}

void MainWindowPresenter::updateFeatures()
{
  std::shared_ptr<Session> _session = mProjectModel->currentSession();
  if (_session){
    bool project_modified = loadFeatures(_session->name());
    if (project_modified)
      mView->setFlag(MainWindowView::Flag::project_modified, project_modified);
  }
}

void MainWindowPresenter::updateMatches()
{
  std::shared_ptr<Session> _session = mProjectModel->currentSession();
  if (_session){
    bool project_modified = loadMatches(_session->name());
    if (project_modified)
      mView->setFlag(MainWindowView::Flag::project_modified, project_modified);
  }
}

void MainWindowPresenter::loadKeyPoints(const QString &image)
{
  QFileInfo fileInfo(image);
  QString features = mProjectModel->currentSession()->features(fileInfo.baseName());

  std::vector<std::tuple<QPointF, double, double>> keyPoints = mModel->loadKeyPoints(features);

  if (keyPoints.size() > 0){

    for (size_t i = 0; i < keyPoints.size(); i++){
      QPointF point;
      double size, angle;
      std::tie(point, size, angle) = keyPoints[i];
      //point *= scale;
      mView->addKeyPoint(point, size/* * scale*/, angle);
    }

  }

}

void MainWindowPresenter::deleteSession(const QString &sessionName)
{
  mProjectModel->deleteSession(sessionName);
  mView->deleteSession(sessionName);
  if (std::shared_ptr<Session> session = (*mProjectModel->sessionBegin())){
    mView->setActiveSession(session->name());
    mProjectModel->setCurrentSession(session->name());
  }

  mView->setFlag(MainWindowView::Flag::project_modified, true);
}

void MainWindowPresenter::deletePreprocess()
{
  if (std::shared_ptr<Session> session = mProjectModel->currentSession()){

    for (auto &preprocess : session->preprocessImages()){
      mView->deletePreprocess(session->name(), preprocess);
      QFile::remove(preprocess);
    }

    mProjectModel->clearPreprocessedImages();

    this->deleteFeatures();

    mView->setFlag(MainWindowView::Flag::project_modified, true);
    mView->setFlag(MainWindowView::Flag::feature_extraction, false);
  }
}

void MainWindowPresenter::deleteFeatures()
{
  if (std::shared_ptr<Session> session = mProjectModel->currentSession()){
    
    for (auto &feat : session->features()) {
      mView->deleteFeatures(session->name(), feat);
      QFile::remove(feat);
    }
    mProjectModel->clearFeatures();

    mView->setFlag(MainWindowView::Flag::project_modified, true);

    this->deleteMatches();

    mProjectModel->deleteMatcher();
    mView->setFlag(MainWindowView::Flag::feature_matching, false);
  }
}

void MainWindowPresenter::deleteMatches()
{
  if (std::shared_ptr<Session> session = mProjectModel->currentSession()){

    for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
      std::vector<std::pair<QString, QString>> pairs = session->matches((*it)->name());
      if (!pairs.empty()){
        for (auto &pair : pairs){
          mView->deleteMatches(session->name(), pair.second);
          QFile::remove(pair.second);
        }
      }
    }

    mProjectModel->clearMatches();
  }
}

void MainWindowPresenter::groundTruthAdded()
{
  mView->setFlag(MainWindowView::Flag::ground_truth, true);
  mView->setFlag(MainWindowView::Flag::project_modified, true);
}

void MainWindowPresenter::processFinish()
{
  if (mPreprocessPresenter){
    disconnect(mProgressDialog, SIGNAL(cancel()),     mPreprocessPresenter, SLOT(cancel()));
  }

  if (mFeatureExtractorPresenter){
    disconnect(mProgressDialog, SIGNAL(cancel()),     mFeatureExtractorPresenter, SLOT(cancel()));
  }

  if (mDescriptorMatcherPresenter){
    disconnect(mProgressDialog, SIGNAL(cancel()),     mDescriptorMatcherPresenter, SLOT(cancel()));
  }

  mView->setFlag(MainWindowView::Flag::processing, false);
}

void MainWindowPresenter::processRunning()
{
  mView->setFlag(MainWindowView::Flag::processing, true);
}

void MainWindowPresenter::help()
{
  //mHelpDialog->showMaximized();
}

void MainWindowPresenter::open()
{
  mView->showMaximized();
}

void MainWindowPresenter::setHelp(std::shared_ptr<HelpDialog> &help)
{

}

void MainWindowPresenter::init()
{
  mProjectModel = new ProjectModel(mProjectIO, mProject);
  mSettingsModel = new SettingsModel(mSettings, mSettingsRW);
  mSettingsModel->read();

  initHelpDialog();

  mView->updateHistory(mSettingsModel->history());
}

void MainWindowPresenter::initNewProjectDialog()
{
  if (mNewProjectPresenter == nullptr){
    INewProjectView *newProjectView = new NewProjectView(mView);
    mNewProjectPresenter = new NewProjectPresenter(newProjectView, mProjectModel);
    //mNewProjectPresenter->setHelp(mHelpDialog);

    connect(mNewProjectPresenter, SIGNAL(projectCreate()), this, SLOT(loadProject()));
  }
}

void MainWindowPresenter::initNewSessionDialog()
{
  if (mNewSessionPresenter == nullptr){
    INewSessionView *newSessionView = new NewSessionView(mView);
    mNewSessionPresenter = new NewSessionPresenter(newSessionView, mProjectModel);
    //mNewSessionPresenter->setHelp(mHelpDialog);

    connect(mNewSessionPresenter, SIGNAL(sessionCreate(QString)), this, SLOT(loadSession(QString)));
    connect(mNewSessionPresenter, SIGNAL(sessionCreate(QString)), this, SLOT(activeSession(QString)));
  }
}

void MainWindowPresenter::initExportFeaturesDialog()
{
  if (mExportFeaturesPresenter == nullptr){
    IExportFeaturesView *exportFeaturesView = new ExportFeaturesView(mView);
    mExportFeaturesModel = new ExportFeaturesModel(mProjectModel);
    mExportFeaturesPresenter = new ExportFeaturesPresenter(exportFeaturesView, mExportFeaturesModel);
  }
}

void MainWindowPresenter::initExportMatchesDialog()
{
  if (mExportMatchesPresenter == nullptr){
    IExportMatchesView *exportMatchesView = new ExportMatchesView(mView);
    mExportMatchesModel = new ExportMatchesModel(mProjectModel);
    mExportMatchesPresenter = new ExportMatchesPresenter(exportMatchesView, mExportMatchesModel);
  }
}

void MainWindowPresenter::initSettingsDialog()
{
  if (mSettingsPresenter == nullptr){
    ISettingsView *view = new SettingsView(mView);
    mSettingsModel = new SettingsModel(mSettings, mSettingsRW);
    mSettingsPresenter = new SettingsPresenter(view, mSettingsModel);
    //mSettingsPresenter->setHelp(mHelp);
  }
}

void MainWindowPresenter::initPreprocessDialog()
{
  if (mPreprocessPresenter == nullptr){
    mPreprocessModel = new PreprocessModel;
    IPreprocessView *preprocessView = new PreprocessView(mView);
    mPreprocessPresenter = new PreprocessPresenter(preprocessView, mPreprocessModel, mProjectModel, mSettingsModel);

    connect(mPreprocessPresenter, SIGNAL(running()),   this, SLOT(processRunning()));
    connect(mPreprocessPresenter, SIGNAL(running()),   this, SLOT(deletePreprocess()));
    connect(mPreprocessPresenter, SIGNAL(finished()),  this, SLOT(processFinish()));
    connect(mPreprocessPresenter, SIGNAL(imagePreprocessed(QString)),  this, SLOT(updatePreprocess()));

    initProgress();

    connect(mProgressDialog, SIGNAL(cancel()),     mPreprocessPresenter, SLOT(cancel()));

    mPreprocessPresenter->setProgressHandler(mProgressHandler);
  }
}

void MainWindowPresenter::initFeatureExtractionDialog()
{
  if (mFeatureExtractorPresenter == nullptr){
    mFeatureExtractorModel = new FeatureExtractorModel;
    IFeatureExtractorView *featureExtractorView = new FeatureExtractorView(mView);
    mFeatureExtractorPresenter = new FeatureExtractorPresenter(featureExtractorView, mFeatureExtractorModel, mProjectModel, mSettingsModel);

    connect(mFeatureExtractorPresenter, SIGNAL(running()),  this, SLOT(processRunning()));
    connect(mFeatureExtractorPresenter, SIGNAL(running()),  this, SLOT(deleteFeatures()));
    connect(mFeatureExtractorPresenter, SIGNAL(finished()), this, SLOT(processFinish()));
    connect(mFeatureExtractorPresenter, SIGNAL(imagePreprocessed(QString)), this, SLOT(updatePreprocess()));
    connect(mFeatureExtractorPresenter, SIGNAL(featuresExtracted(QString)), this, SLOT(updateFeatures()));

    initProgress();

    connect(mProgressDialog, SIGNAL(cancel()),     mFeatureExtractorPresenter, SLOT(cancel()));

    mFeatureExtractorPresenter->setProgressHandler(mProgressHandler);
  }
}

void MainWindowPresenter::initFeatureMatching()
{
  if (mDescriptorMatcherPresenter == nullptr){
    mDescriptorMatcherModel = new DescriptorMatcherModel;
    IDescriptorMatcherView *descriptorMatcherView = new DescriptorMatcherView(mView);
    mDescriptorMatcherPresenter = new DescriptorMatcherPresenter(descriptorMatcherView, mDescriptorMatcherModel, mProjectModel, mSettingsModel);

    connect(mDescriptorMatcherPresenter, SIGNAL(running()),  this, SLOT(processRunning()));
    connect(mDescriptorMatcherPresenter, SIGNAL(running()),  this, SLOT(deleteMatches()));
    connect(mDescriptorMatcherPresenter, SIGNAL(finished()), this, SLOT(processFinish()));
    connect(mDescriptorMatcherPresenter, SIGNAL(matchCompute(QString)), this, SLOT(updateMatches()));

    initProgress();

    connect(mProgressDialog, SIGNAL(cancel()),     mDescriptorMatcherPresenter, SLOT(cancel()));

    mDescriptorMatcherPresenter->setProgressHandler(mProgressHandler);
  }
}

//void MainWindowPresenter::initBatch()
//{
//  if (mBatchPresenter == nullptr){
//    mBatchmodel = new BatchModel;
//    IBatchView *descriptorMatcherView = new BatchView(mView);
//    mBatchPresenter = new BatchPresenter(descriptorMatcherView, mBatchmodel, mProjectModel, mSettingsModel);
//  }
//}

void MainWindowPresenter::initProgress()
{
  if (mProgressHandler == nullptr){
    mProgressDialog = new ProgressDialog;

    QProgressBar *statusBarProgress = mView->progressBar();
//    QAction *mAction = new QAction(tr(""), statusBarProgress);
//    QMenu *contextMenuProgressBar = new QMenu(statusBarProgress);
//    contextMenuProgressBar->addAction(mAction);
//    statusBarProgress->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
//    statusBarProgress->setContextMenu(contextMenuProgressBar);

//    connect(mAction, SIGNAL(triggered(bool)),   statusBarProgress,   SLOT(hide()));
//    connect(mAction, SIGNAL(triggered(bool)),   mProgressDialog,     SLOT(show()));

    mProgressHandler = new ProgressHandler;

    connect(mProgressHandler, SIGNAL(rangeChange(int, int)),      mProgressDialog, SLOT(setRange(int, int)));
    connect(mProgressHandler, SIGNAL(valueChange(int)),           mProgressDialog, SLOT(setValue(int)));
    connect(mProgressHandler, SIGNAL(initialized()),              mProgressDialog, SLOT(setInitialized()));
    connect(mProgressHandler, SIGNAL(finished()),                 mProgressDialog, SLOT(setFinished()));
    connect(mProgressHandler, SIGNAL(titleChange(QString)),       mProgressDialog, SLOT(setWindowTitle(QString)));
    connect(mProgressHandler, SIGNAL(descriptionChange(QString)), mProgressDialog, SLOT(setStatusText(QString)));

    connect(mProgressHandler, SIGNAL(rangeChange(int, int)),      statusBarProgress, SLOT(setRange(int, int)));
    connect(mProgressHandler, SIGNAL(valueChange(int)),           statusBarProgress, SLOT(setValue(int)));
    connect(mProgressHandler, SIGNAL(initialized()),              statusBarProgress, SLOT(show()));
    connect(mProgressHandler, SIGNAL(finished()),                 statusBarProgress, SLOT(hide()));

  }
}

void MainWindowPresenter::initFeaturesViewer()
{
  if (mFeaturesViewerPresenter == nullptr) {
    mFeaturesViewerModel = new FeaturesViewerModel(mProjectModel);
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    IFeaturesViewerView *featuresViewerView = new FeaturesViewerView(mView, f);
    mFeaturesViewerPresenter = new FeaturesViewerPresenter(featuresViewerView, mFeaturesViewerModel, mSettingsModel);
    //mMatchesViewerPresenter->setHelp(mHelpDialog);
  }
}

void MainWindowPresenter::initMatchesViewer()
{
  if (mMatchesViewerPresenter == nullptr) {
    mMatchesViewerModel = new MatchViewerModel(mProjectModel);
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    IMatchViewerView *matchViewerView = new MatchViewerView(mView, f);
    mMatchesViewerPresenter = new MatchViewerPresenter(matchViewerView, mMatchesViewerModel, mSettingsModel);
    //mMatchesViewerPresenter->setHelp(mHelpDialog);
  }
}

void MainWindowPresenter::initGroundTruthEditor()
{
  if (mGroundTruthPresenter == nullptr){
    mGroundTruthModel = new GroundTruthModel(mProjectModel);
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    IGroundTruthView *groundTruthView = new GroundTruthView(mView, f);
    mGroundTruthPresenter = new GroundTruthPresenter(groundTruthView, mGroundTruthModel, mSettingsModel);
    //mGroundTruthPresenter->setHelp(mHelpDialog);

    connect(mGroundTruthPresenter, SIGNAL(groundTruthAdded()), this, SLOT(groundTruthAdded()));
  }
}

void MainWindowPresenter::initHomographyViewer()
{
  if (mHomographyViewerPresenter == nullptr) {
    mHomographyViewerModel = new HomographyViewerModel(mProjectModel);
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    IHomographyViewerView *homographyViewerView = new HomographyViewerView(mView, f);
    mHomographyViewerPresenter = new HomographyViewerPresenter(homographyViewerView, mHomographyViewerModel, mSettingsModel);
    //mMatchesViewerPresenter->setHelp(mHelpDialog);
  }
}

void MainWindowPresenter::initRepeatability()
{
  if (mRepeatabilityPresenter == nullptr){
    mRepeatabilityModel = new RepeatabilityModel(mProjectModel);
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    IRepeatabilityView *repeatabilityView = new RepeatabilityView(mView, f);
    mRepeatabilityPresenter = new RepeatabilityPresenter(repeatabilityView, mRepeatabilityModel);
    //mRepeatabilityPresenter->setHelp(mHelpDialog);
  }
}

void MainWindowPresenter::initPRCurvesViewer()
{
  if (mCurvesPRViewerPresenter == nullptr) {
    mCurvesPRViewerModel = new PRCurvesViewerModel(mProjectModel);
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    CurvesViewerView *curvesViewerView = new PRCurvesViewer(mView, f);
    mCurvesPRViewerPresenter = new CurvesViewerPresenter(curvesViewerView, mCurvesPRViewerModel);
    //mMatchesViewerPresenter->setHelp(mHelpDialog);
  }
}

void MainWindowPresenter::initROCCurvesViewer()
{
  if (mCurvesROCViewerPresenter == nullptr) {
    mCurvesROCViewerModel = new ROCCurvesViewerModel(mProjectModel);
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    CurvesViewerView *curvesViewerView = new ROCCurvesViewer(mView, f);
    mCurvesROCViewerPresenter = new CurvesViewerPresenter(curvesViewerView, mCurvesROCViewerModel);
    //mMatchesViewerPresenter->setHelp(mHelpDialog);
  }
}

void MainWindowPresenter::initDETCurvesViewer()
{
  if (mCurvesDETViewerPresenter == nullptr) {
    mCurvesDETViewerModel = new DETCurvesViewerModel(mProjectModel);
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    CurvesViewerView *curvesViewerView = new DETCurvesViewer(mView, f);
    mCurvesDETViewerPresenter = new CurvesViewerPresenter(curvesViewerView, mCurvesDETViewerModel);
    //mMatchesViewerPresenter->setHelp(mHelpDialog);
  }
}

void MainWindowPresenter::initAboutDialog()
{
  if (mAboutDialog == nullptr) {
    mAboutDialog = new AboutDialog(mView);
  }
}

void MainWindowPresenter::initHelpDialog()
{
  if (mHelpDialog == nullptr) {
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    mHelpDialog = std::make_shared<HelpDialog>(new HelpDialog(mView, f));
  }
}

bool MainWindowPresenter::loadPreprocess(const QString &session)
{
  std::shared_ptr<Session> _session = mProjectModel->findSession(session);
  if (_session){
    std::shared_ptr<Preprocess> preprocess = _session->preprocess();

    QString currentSession = mProjectModel->currentSession()->name();
    if (currentSession.compare(session) == 0){
      mView->setFlag(MainWindowView::Flag::preprocess, preprocess != nullptr);
    }

    if (preprocess){

      /// Preprocess
      QString preprocess_name = preprocess->name();
      mView->addPreprocess(_session->name(), preprocess_name, _session->preprocessImages());

      return true;

    }
  }
  return false;
}

bool MainWindowPresenter::loadFeatures(const QString &session)
{
  if (std::shared_ptr<Session> _session = mProjectModel->findSession(session)){

    std::shared_ptr<Feature> detector = _session->detector();
    std::shared_ptr<Feature> descriptor = _session->descriptor();

    QString currentSession = mProjectModel->currentSession()->name();
    if (currentSession.compare(session) == 0){
      mView->setFlag(MainWindowView::Flag::feature_extraction, detector && descriptor && _session->features().empty() == false);
    }

    if (detector && descriptor){

      //mView->setFlag(MainWindowView::Flag::feature_extraction, true);
      mView->addFeatures(_session->name(), detector->name(), descriptor->name(), _session->features());

      return true;
    }

  }
  return false;
}

bool MainWindowPresenter::loadMatches(const QString &session)
{
  if (std::shared_ptr<Session> _session = mProjectModel->findSession(session)){

    std::shared_ptr<Match> match = _session->matcher();

    QString currentSession = mProjectModel->currentSession()->name();
    if (currentSession.compare(session) == 0){
      mView->setFlag(MainWindowView::Flag::feature_matching, match != nullptr);
    }

    if (match){

      for (auto &matches : _session->matches()){
        QString img1 = matches.first;
        for (size_t i = 0; i < matches.second.size(); i++){
          QString img2 = matches.second[i].first;
          QString file = matches.second[i].second;
          mView->addMatches(_session->name(), match->name(), img1, img2, file);
        }
      }

      return true;
    }
  }
  return false;
}

} // namespace photomatch

