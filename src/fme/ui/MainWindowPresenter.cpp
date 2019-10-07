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

#include "fme/ui/PreprocessModel.h"
#include "fme/ui/PreprocessView.h"
#include "fme/ui/PreprocessPresenter.h"
#include "fme/ui/FeatureExtractorModel.h"
#include "fme/ui/FeatureExtractorView.h"
#include "fme/ui/FeatureExtractorPresenter.h"
#include "fme/ui/DescriptorMatcherModel.h"  ///TODO: por ahora no tiene ninguna utilidad
#include "fme/ui/DescriptorMatcherView.h"
#include "fme/ui/DescriptorMatcherPresenter.h"
#include "fme/ui/MatchViewerModel.h"
#include "fme/ui/MatchViewerView.h"
#include "fme/ui/MatchViewerPresenter.h"
#include "fme/ui/GroundTruthModel.h"
#include "fme/ui/GroundTruthView.h"
#include "fme/ui/GroundTruthPresenter.h"
#include "fme/ui/HomographyViewerModel.h"
#include "fme/ui/HomographyViewerView.h"
#include "fme/ui/HomographyViewerPresenter.h"
#include "fme/ui/CurvesViewerModel.h"
#include "fme/ui/CurvesViewerView.h"
#include "fme/ui/CurvesViewerPresenter.h"

#include "fme/ui/utils/Progress.h"
#include "fme/ui/utils/ProgressDialog.h"
#include "fme/ui/utils/KeyPointGraphicsItem.h"

#include "fme/core/project.h"

/* TidopLib */
#include <tidop/core/messages.h>

/* Qt */
#include <QFileDialog>
#include <QMessageBox>
#include <QImageReader>
#include <QProgressBar>

namespace fme
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
    mMatchesViewerPresenter(nullptr),
    mMatchesViewerModel(nullptr),
    mGroundTruthPresenter(nullptr),
    mGroundTruthModel(nullptr),
    mHomographyViewerPresenter(nullptr),
    mHomographyViewerModel(nullptr),
    mCurvesPRViewerPresenter(nullptr),
    mCurvesROCViewerPresenter(nullptr),
    mCurvesViewerModel(nullptr),
    mProgressHandler(nullptr),
    mProgressDialog(nullptr)
{
  init();

  /* Menú Archivo */

  connect(mView, SIGNAL(openNew()),                       this, SLOT(openNew()));
  connect(mView, SIGNAL(openProject()),                   this, SLOT(openProject()));
  connect(mView, SIGNAL(openProjectFromHistory(QString)), this, SLOT(openFromHistory(QString)));  ///TODO: falta test señal
  connect(mView, SIGNAL(clearHistory()),                  this, SLOT(deleteHistory()));
  //connect(mView, SIGNAL(exportTiePoints()),               this, SLOT(exportTiePoints()));
  connect(mView, SIGNAL(exportTiePointsCvXml()),          this, SLOT(exportTiePointsCvXml()));
  connect(mView, SIGNAL(exportTiePointsCvYml()),          this, SLOT(exportTiePointsCvYml()));
  connect(mView, SIGNAL(exportMatchesCvYml()),            this, SLOT(exportMatchesCvYml()));
  connect(mView, SIGNAL(exportMatchesCvXml()),            this, SLOT(exportMatchesCvXml()));
  connect(mView, SIGNAL(exportMatchesTxt()),              this, SLOT(exportMatchesTxt()));
  connect(mView, SIGNAL(saveProject()),                   this, SLOT(saveProject()));
  connect(mView, SIGNAL(saveProjectAs()),                 this, SLOT(saveProjectAs()));
  connect(mView, SIGNAL(closeProject()),                  this, SLOT(closeProject()));
  connect(mView, SIGNAL(exit()),                          this, SLOT(exit()));

  /* Menú View */

  /* Quality Control */

  connect(mView,  SIGNAL(matchesViewer()),            this, SLOT(openMatchesViewer()));
  connect(mView,  SIGNAL(createGroundTruth()),        this, SLOT(createGroundTruth()));
  connect(mView,  SIGNAL(importGroundTruth()),        this, SLOT(importGroundTruth()));
  connect(mView,  SIGNAL(homography()),               this, SLOT(openHomographyViewer()));
  //connect(mView,  SIGNAL(repeteability()),            this, SLOT(repeteability()));
  connect(mView,  SIGNAL(prCurves()),                 this, SLOT(openPRCurvesViewer()));
  connect(mView,  SIGNAL(rocCurves()),                this, SLOT(openROCCurvesViewer()));

  /* Menú herramientas */

  connect(mView,   SIGNAL(loadImages()),              this, SLOT(loadImages()));
  connect(mView,   SIGNAL(newSession()),              this, SLOT(newSession()));
  connect(mView,   SIGNAL(openPreprocess()),          this, SLOT(openPreprocess()));
  connect(mView,   SIGNAL(openFeatureExtraction()),   this, SLOT(openFeatureExtraction()));
  connect(mView,   SIGNAL(openFeatureMatching()),     this, SLOT(openFeatureMatching()));
  connect(mView,   SIGNAL(openSettings()),            this, SLOT(openSettings()));

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

  if (mProgressHandler){
    delete mProgressHandler;
    mProgressHandler = nullptr;
  }

  if (mProgressDialog){
    delete mProgressDialog;
    mProgressDialog = nullptr;
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

  if (mCurvesROCViewerPresenter){
    delete mCurvesROCViewerPresenter;
    mCurvesROCViewerPresenter = nullptr;
  }

  if (mCurvesViewerModel){
    delete mCurvesViewerModel;
    mCurvesViewerModel = nullptr;
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
                                              tr("Open FME project"),
                                              mModel->defaultPath(),
                                              tr("FME project (*.xml)"));
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
                                              tr("FME project (*.xml)"));
  if (file.isEmpty() == false) {
    mProjectModel->saveAs(file);
    mView->setFlag(MainWindowView::Flag::project_modified, false);
  }
}

void MainWindowPresenter::exportTiePointsCvXml()
{
  QString pathName = QFileDialog::getExistingDirectory(nullptr,
                                                       tr("Export directory"),
                                                       "",
                                                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (!pathName.isEmpty()) {

  }
}

void MainWindowPresenter::exportTiePointsCvYml()
{
  QString pathName = QFileDialog::getExistingDirectory(nullptr,
                                                       tr("Export directory"),
                                                       "",
                                                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (!pathName.isEmpty()) {

  }
}

void MainWindowPresenter::exportMatchesCvYml()
{
  QString pathName = QFileDialog::getExistingDirectory(nullptr,
                                                       tr("Export directory"),
                                                       "",
                                                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (!pathName.isEmpty()) {

  }
}

void MainWindowPresenter::exportMatchesCvXml()
{
  QString pathName = QFileDialog::getExistingDirectory(nullptr,
                                                       tr("Export directory"),
                                                       "",
                                                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (!pathName.isEmpty()) {

  }
}

void MainWindowPresenter::exportMatchesTxt()
{
  QString pathName = QFileDialog::getExistingDirectory(nullptr,
                                                       tr("Export directory"),
                                                       "",
                                                       QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (!pathName.isEmpty()) {

  }
}

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
  mView->setWindowTitle(QString("FME"));
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

void MainWindowPresenter::openMatchesViewer()
{
  initMatchesViewer();
  mMatchesViewerPresenter->open();
}

void MainWindowPresenter::createGroundTruth()
{
  initCreateGroundTruth();
  mGroundTruthPresenter->open();
}

void MainWindowPresenter::importGroundTruth()
{
  QString file = QFileDialog::getOpenFileName(Q_NULLPTR,
                                              tr("Import Ground Truth"),
                                              mProjectModel->path(),
                                              tr("Ground Truth (*.txt)"));
  if (!file.isEmpty()) {

    mProjectModel->setGroundTruth(file);

    mView->setFlag(MainWindowView::Flag::ground_truth, true);
    mView->setFlag(MainWindowView::Flag::project_modified, true);

  }
}

void MainWindowPresenter::openHomographyViewer()
{
  initHomographyViewer();
  mHomographyViewerPresenter->open();
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

void MainWindowPresenter::loadImages()
{
  QStringList fileNames = QFileDialog::getOpenFileNames(Q_NULLPTR,
                                                        tr("Add images"),
                                                        mProjectModel->projectFolder(),
                                                        tr("Image files (*.tif *.jpg *.png);;TIFF (*.tif);;png (*.png);;JPEG (*.jpg)"));
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

void MainWindowPresenter::openSettings()
{
  initSettingsDialog();
  mSettingsPresenter->open();
}

void MainWindowPresenter::openAboutDialog()
{

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

  if (mProjectModel->currentSession() == nullptr){
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
  if (mView->showKeyPoints()){
    this->loadKeyPoints(image);
  }
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
  for (const auto &image : images){
    mView->deleteImage(image);
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
  std::shared_ptr<Preprocess> preprocess = _session->preprocess();

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

  /// Una escala para cada imagen por si tienen tamaño diferente
  double scale1 = 1.;
  double scale2 = 1.;
  if (mProjectModel->fullImageSize() == false){
    int maxSize = mProjectModel->maxImageSize();
    QImageReader imageReader1(imgPath1);
    QSize size = imageReader1.size();
    int w = size.width();
    int h = size.height();
    if (w > h){
      scale1 = w / static_cast<double>(maxSize);
    } else {
      scale1 = h / static_cast<double>(maxSize);
    }
    if (scale1 < 1.) scale1 = 1.;

    QImageReader imageReader2(imgPath2);
    size = imageReader2.size();
    w = size.width();
    h = size.height();
    if (w > h){
      scale2 = w / static_cast<double>(maxSize);
    } else {
      scale2 = h / static_cast<double>(maxSize);
    }
    if (scale2 < 1.) scale2 = 1.;

  }

  if (std::shared_ptr<Session> session = mProjectModel->findSession(sessionName)){

    std::vector<std::pair<QString, QString>> pairs = session->matches(imgName1);
    if (!pairs.empty()){
      for (auto &pair : pairs){
        if (pair.first.compare(imgName2) == 0){
          matches = mModel->loadMatches(pair.second, session->features(imgName1), session->features(imgName2));

          for (size_t i = 0; i < matches.size(); i++){
            matches[i].first *= scale1;
            matches[i].second *= scale2;
          }

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
  QString features = fileInfo.path();
  features.append("\\").append(mProjectModel->currentSession()->name());
  features.append("\\features\\");
  features.append(fileInfo.fileName()).append(".xml");

  std::vector<std::tuple<QPointF, double, double>> keyPoints = mModel->loadKeyPoints(features);

  if (keyPoints.size() > 0){

    double scale = 1.;
    if (mProjectModel->fullImageSize() == false){
      int maxSize = mProjectModel->maxImageSize();
      QImageReader imageReader(image);
      QSize size = imageReader.size();
      int w = size.width();
      int h = size.height();
      if (w > h){
        scale = w / static_cast<double>(maxSize);
      } else {
        scale = h / static_cast<double>(maxSize);
      }
      if (scale < 1.) scale = 1.;
    }

    for (size_t i = 0; i < keyPoints.size(); i++){
      QPointF point;
      double size, angle;
      std::tie(point, size, angle) = keyPoints[i];
      point *= scale;
      mView->addKeyPoint(point, size * scale, angle);
    }

  }

}

void MainWindowPresenter::processFinish()
{
  mView->setFlag(MainWindowView::Flag::processing, false);
}

void MainWindowPresenter::processRunning()
{
  mView->setFlag(MainWindowView::Flag::processing, true);
}

void MainWindowPresenter::help()
{
}

void MainWindowPresenter::open()
{
  mView->showMaximized();
}

void MainWindowPresenter::init()
{
  mProjectModel = new ProjectModel(mProjectIO, mProject);
  mSettingsModel = new SettingsModel(mSettings, mSettingsRW);
  mSettingsModel->read();

  mView->updateHistory(mSettingsModel->history());
}

void MainWindowPresenter::initNewProjectDialog()
{
  if (mNewProjectPresenter == nullptr){
    INewProjectView *newProjectView = new NewProjectView(mView);
    mNewProjectPresenter = new NewProjectPresenter(newProjectView, mProjectModel);
    //mNewProjectPresenter->setHelp(mHelp);

    connect(mNewProjectPresenter, SIGNAL(projectCreate()), this, SLOT(loadProject()));
  }
}

void MainWindowPresenter::initNewSessionDialog()
{
  if (mNewSessionPresenter == nullptr){
    INewSessionView *newSessionView = new NewSessionView(mView);
    mNewSessionPresenter = new NewSessionPresenter(newSessionView, mProjectModel);

    connect(mNewSessionPresenter, SIGNAL(sessionCreate(QString)), this, SLOT(loadSession(QString)));
    connect(mNewSessionPresenter, SIGNAL(sessionCreate(QString)), this, SLOT(activeSession(QString)));
  }
}

void MainWindowPresenter::initSettingsDialog()
{
  if (mSettingsPresenter == nullptr){
    ISettingsView *view = new SettingsView(mView);
    //mSettingsModel = new SettingsModel(mSettings, mSettingsRW);
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
    connect(mPreprocessPresenter, SIGNAL(finished()),  this, SLOT(processFinish()));
    connect(mPreprocessPresenter, SIGNAL(imagePreprocessed(QString)),  this, SLOT(updatePreprocess()));

    initProgress();

    ///TODO: Esto aqui...
    ///connect(mProgressHandler, SIGNAL(cancel()), mMultiProcess, SLOT(stop()));
    //connect(mProgressDialog, SIGNAL(cancel()),     mPreprocessPresenter, SLOT(cancel()));
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
    connect(mFeatureExtractorPresenter, SIGNAL(finished()), this, SLOT(processFinish()));
    connect(mFeatureExtractorPresenter, SIGNAL(featuresExtracted(QString)), this, SLOT(updateFeatures()));

    initProgress();

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
    connect(mDescriptorMatcherPresenter, SIGNAL(finished()), this, SLOT(processFinish()));
    connect(mDescriptorMatcherPresenter, SIGNAL(matchCompute(QString)), this, SLOT(updateMatches()));

    initProgress();

    mDescriptorMatcherPresenter->setProgressHandler(mProgressHandler);
  }
}

void MainWindowPresenter::initProgress()
{
  if (mProgressHandler == nullptr){
    mProgressDialog = new ProgressDialog;

    QProgressBar *statusBarProgress = mView->progressBar();

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

void MainWindowPresenter::initMatchesViewer()
{
  if (mMatchesViewerPresenter == nullptr) {
    mMatchesViewerModel = new MatchViewerModel(mProjectModel);
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    IMatchViewerView *matchViewerView = new MatchViewerView(mView, f);
    mMatchesViewerPresenter = new MatchViewerPresenter(matchViewerView, mMatchesViewerModel);
    //mMatchesViewerPresenter->setHelp(mHelp);
  }
}

void MainWindowPresenter::initCreateGroundTruth()
{
  if (mGroundTruthPresenter == nullptr){
    mGroundTruthModel = new GroundTruthModel(mProjectModel);
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    IGroundTruthView *groundTruthView = new GroundTruthView(mView, f);
    mGroundTruthPresenter = new GroundTruthPresenter(groundTruthView, mGroundTruthModel);
  }
}

void MainWindowPresenter::initHomographyViewer()
{
  if (mHomographyViewerPresenter == nullptr) {
    mHomographyViewerModel = new HomographyViewerModel(mProjectModel);
    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    IHomographyViewerView *homographyViewerView = new HomographyViewerView(mView, f);
    mHomographyViewerPresenter = new HomographyViewerPresenter(homographyViewerView, mHomographyViewerModel);
    //mMatchesViewerPresenter->setHelp(mHelp);
  }
}

void MainWindowPresenter::initPRCurvesViewer()
{
  if (mCurvesViewerModel == nullptr) {
    mCurvesViewerModel = new PRCurvesViewerModel(mProjectModel);
  }

  if (mCurvesPRViewerPresenter == nullptr) {

    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    CurvesViewerView *curvesViewerView = new PRCurvesViewer(mView, f);
    mCurvesPRViewerPresenter = new CurvesViewerPresenter(curvesViewerView, mCurvesViewerModel);
//    //mMatchesViewerPresenter->setHelp(mHelp);
  }
}

void MainWindowPresenter::initROCCurvesViewer()
{
  if (mCurvesViewerModel == nullptr) {
    mCurvesViewerModel = new ROCCurvesViewerModel(mProjectModel);
  }

  if (mCurvesROCViewerPresenter == nullptr) {

    Qt::WindowFlags f(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
    CurvesViewerView *curvesViewerView = new ROCCurvesViewer(mView, f);
    mCurvesROCViewerPresenter = new CurvesViewerPresenter(curvesViewerView, mCurvesViewerModel);
//    //mMatchesViewerPresenter->setHelp(mHelp);
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

} // namespace fme

