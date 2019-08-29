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

#include "fme/ui/PreprocessPresenter.h"
#include "fme/ui/PreprocessModel.h"
#include "fme/ui/PreprocessView.h"
#include "fme/ui/FeatureExtractorPresenter.h"
#include "fme/ui/FeatureExtractorModel.h"
#include "fme/ui/FeatureExtractorView.h"
#include "fme/ui/DescriptorMatcherPresenter.h"
#include "fme/ui/DescriptorMatcherModel.h"  ///TODO: por ahora no tiene ninguna utilidad
#include "fme/ui/DescriptorMatcherView.h"

#include "fme/core/project.h"

/* TidopLib */
#include <tidop/core/messages.h>

/* Qt */
#include <QFileDialog>
#include <QMessageBox>

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
    mDescriptorMatcherPresenter(nullptr)
{
  init();

  /* Menú Archivo */

  connect(mView, SIGNAL(openNew()),                       this, SLOT(openNew()));
  connect(mView, SIGNAL(openProject()),                   this, SLOT(openProject()));
  connect(mView, SIGNAL(openProjectFromHistory(QString)), this, SLOT(openFromHistory(QString)));  ///TODO: falta test señal
  connect(mView, SIGNAL(clearHistory()),                  this, SLOT(deleteHistory()));
  connect(mView, SIGNAL(saveProject()),                   this, SLOT(saveProject()));
  connect(mView, SIGNAL(saveProjectAs()),                 this, SLOT(saveProjectAs()));
  connect(mView, SIGNAL(closeProject()),                  this, SLOT(closeProject()));
  connect(mView, SIGNAL(exit()),                          this, SLOT(exit()));

  /* Menú View */

  /* Menú herramientas */

  connect(mView,   SIGNAL(loadImages()),              this, SLOT(loadImages()));
  connect(mView,   SIGNAL(newSession()),              this, SLOT(newSession()));
  connect(mView,   SIGNAL(openAssistant()),           this, SLOT(openAssistant()));
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

  //connect(mProjectModel, SIGNAL(projectModified()), this, SLOT(updateProject()));
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

void MainWindowPresenter::openAssistant()
{

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

  QStringList images;
  TL_TODO("Los iteradores sobre las imagenes deberian ser constantes unicamente para evitar que se modifiquen las imagenes. El problema es que no se notificaria al proyecto que ha cambiado")
  for(auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    images.push_back((*it)->path());
  }

  if (images.size() > 0){
    mView->addImages(images);
    mView->setFlag(MainWindowView::Flag::images_added, true);
  }

  TL_TODO("Lo mismo que para las imagenes... ")
  if (mProjectModel->currentSession()){
    QString currentSession = mProjectModel->currentSession()->name();
    for (auto it = mProjectModel->sessionBegin(); it != mProjectModel->sessionEnd(); it++){
      //loadSession((*it)->name());
      //(currentSession.compare((*it)->name()) == 0)
      mView->addSession((*it)->name(), (*it)->description());
      mView->setFlag(MainWindowView::Flag::session_created, true);

      std::shared_ptr<Preprocess> preprocess = (*it)->preprocess();
      if (preprocess){
        mView->setFlag(MainWindowView::Flag::preprocess, true);

        std::shared_ptr<Feature> detector = (*it)->detector();
        std::shared_ptr<Feature> descriptor = (*it)->descriptor();
        if (detector && descriptor){
          mView->setFlag(MainWindowView::Flag::feature_extraction, true);

          /// Preprocess
          QString preprocess_name;
          if (preprocess->type() == Preprocess::Type::acebsf){
            preprocess_name = "ACEBSF";
          } else if (preprocess->type() == Preprocess::Type::clahe){
            preprocess_name = "CLAHE";
          } else if (preprocess->type() == Preprocess::Type::cmbfhe){
            preprocess_name = "CMBFHE";
          } else if (preprocess->type() == Preprocess::Type::dhe){
            preprocess_name = "DHE";
          } else if (preprocess->type() == Preprocess::Type::fahe){
            preprocess_name = "FAHE";
          } else if (preprocess->type() == Preprocess::Type::hmclahe){
            preprocess_name = "HMCLAHE";
          } else if (preprocess->type() == Preprocess::Type::lce_bsescs){
            preprocess_name = "LCE_BSESCS";
          } else if (preprocess->type() == Preprocess::Type::msrcp){
            preprocess_name = "MSRCP";
          } else if (preprocess->type() == Preprocess::Type::noshp){
            preprocess_name = "NOSHP";
          } else if (preprocess->type() == Preprocess::Type::pohe){
            preprocess_name = "POHE";
          } else if (preprocess->type() == Preprocess::Type::rswhe){
            preprocess_name = "RSWHE";
          } else if (preprocess->type() == Preprocess::Type::wallis){
            preprocess_name = "WALLIS";
          }
          mView->addPreprocess((*it)->name(), preprocess_name);

          /// Detector
          QString detector_name;
          if (detector->type() == Feature::Type::agast){
            detector_name = "AGAST";
          } else if (detector->type() == Feature::Type::akaze){
            detector_name = "AKAZE";
          } else if (detector->type() == Feature::Type::brisk){
            detector_name = "BRISK";
          } else if (detector->type() == Feature::Type::fast){
            detector_name = "FAST";
          } else if (detector->type() == Feature::Type::gftt){
            detector_name = "GFTT";
          } else if (detector->type() == Feature::Type::kaze){
            detector_name = "KAZE";
          } else if (detector->type() == Feature::Type::msd){
            detector_name = "MSD";
          } else if (detector->type() == Feature::Type::mser){
            detector_name = "MSER";
          } else if (detector->type() == Feature::Type::orb){
            detector_name = "ORB";
          } else if (detector->type() == Feature::Type::sift){
            detector_name = "SIFT";
          } else if (detector->type() == Feature::Type::star){
            detector_name = "STAR";
          } else if (detector->type() == Feature::Type::surf){
            detector_name = "SURF";
          }

          mView->addDetector((*it)->name(), detector_name);

          /// Descriptor
          QString descriptor_name;
          if (descriptor->type() == Feature::Type::akaze){
            descriptor_name = "AKAZE";
          } else if (descriptor->type() == Feature::Type::brief){
            descriptor_name = "BRIEF";
          } else if (descriptor->type() == Feature::Type::brisk){
            descriptor_name = "BRISK";
          } else if (descriptor->type() == Feature::Type::daisy){
            descriptor_name = "DAISY";
          } else if (descriptor->type() == Feature::Type::freak){
            descriptor_name = "FREAK";
          } else if (descriptor->type() == Feature::Type::hog){
            descriptor_name = "HOG";
          } else if (descriptor->type() == Feature::Type::kaze){
            descriptor_name = "KAZE";
          } else if (descriptor->type() == Feature::Type::latch){
            descriptor_name = "LATCH";
          } else if (descriptor->type() == Feature::Type::lucid){
            descriptor_name = "LUCID";
          } else if (descriptor->type() == Feature::Type::orb){
            descriptor_name = "ORB";
          } else if (descriptor->type() == Feature::Type::sift){
            descriptor_name = "SIFT";
          } else if (descriptor->type() == Feature::Type::surf){
            descriptor_name = "SURF";
          }
          mView->addDescriptor((*it)->name(), descriptor_name);

        }
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
}

void MainWindowPresenter::selectSession(const QString &session)
{
  ///TODO: recuperar información de la sesión y mostrarla en la ventana de propiedades
}

void MainWindowPresenter::loadPreprocess()
{
  std::shared_ptr<Session> _session = mProjectModel->currentSession();

  std::shared_ptr<Preprocess> preprocess = _session->preprocess();
  if (preprocess){
    mView->setFlag(MainWindowView::Flag::preprocess, true);
    mView->setFlag(MainWindowView::Flag::project_modified, true);
  }
}

void MainWindowPresenter::loadFeatures()
{
  std::shared_ptr<Session> _session = mProjectModel->currentSession();
  std::shared_ptr<Feature> detector = _session->detector();
  std::shared_ptr<Feature> descriptor = _session->descriptor();
  if (detector && descriptor){
    mView->setFlag(MainWindowView::Flag::feature_extraction, true);
    mView->setFlag(MainWindowView::Flag::project_modified, true);
  }
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

    connect(mPreprocessPresenter, SIGNAL(preprocessFinished()), this, SLOT(loadPreprocess()));
  }
}

void MainWindowPresenter::initFeatureExtractionDialog()
{
  if (mFeatureExtractorPresenter == nullptr){
    mFeatureExtractorModel = new FeatureExtractorModel;
    IFeatureExtractorView *featureExtractorView = new FeatureExtractorView(mView);
    mFeatureExtractorPresenter = new FeatureExtractorPresenter(featureExtractorView, mFeatureExtractorModel, mProjectModel, mSettingsModel);

    connect(mFeatureExtractorPresenter, SIGNAL(featureExtractorFinished()), this, SLOT(loadFeatures()));
  }
}

void MainWindowPresenter::initFeatureMatching()
{
  if (mDescriptorMatcherPresenter == nullptr){
    mDescriptorMatcherModel = new DescriptorMatcherModel;
    IDescriptorMatcherView *descriptorMatcherView = new DescriptorMatcherView(mView);
    mDescriptorMatcherPresenter = new DescriptorMatcherPresenter(descriptorMatcherView, mDescriptorMatcherModel, mProjectModel, mSettingsModel);
  }
}

} // namespace fme

