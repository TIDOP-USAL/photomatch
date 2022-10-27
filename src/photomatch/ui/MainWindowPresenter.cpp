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


#include "MainWindowPresenter.h"

#include "photomatch/ui/MainWindowView.h"
#include "photomatch/ui/MainWindowModel.h"
#include "photomatch/ui/ProjectModel.h"
#include "photomatch/ui/settings/SettingsModel.h"
#include "photomatch/ui/settings/SettingsPresenter.h"
#include "photomatch/ui/settings/SettingsView.h"
#include "photomatch/ui/utils/TabHandler.h"
#include "photomatch/ui/utils/GraphicViewer.h"
#include "photomatch/ui/HelpDialog.h"
#include "photomatch/widgets/StartPageWidget.h"

/* TidopLib */
#include <tidop/core/messages.h>

/* Qt */
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

namespace photomatch
{

MainWindowPresenter::MainWindowPresenter(MainWindowView *view,
                                         MainWindowModel *model,
                                         ProjectModel *projectModel,
                                         SettingsModel *settingsModel)
  : PhotoMatchPresenter(),
    mView(view),
    mModel(model),
    mProjectModel(projectModel),
    mSettingsModel(settingsModel),
    mTabHandler(nullptr),
    mStartPageWidget(nullptr)
{
  this->init();
  this->initSignalAndSlots();
}

MainWindowPresenter::~MainWindowPresenter()
{
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

  emit openNewProjectDialog();
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
  mStartPageWidget->setHistory(QStringList());
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
}

void MainWindowPresenter::exit()
{
  ///TODO: Se cierra la aplicación
  /// - Comprobar que no haya ningún procesos corriendo
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

void MainWindowPresenter::openStartPage()
{
  initStartPage();

  const QSignalBlocker blocker(mTabHandler);
  int id = -1;
  for (int i = 0; i < mTabHandler->count(); i++){
    if (mTabHandler->tabText(i) == mStartPageWidget->windowTitle()){
      id = -1;
      mTabHandler->setCurrentIndex(id);
      break;
    }
  }

  if (id == -1){
    id = mTabHandler->addTab(mStartPageWidget, mStartPageWidget->windowTitle());
    mTabHandler->setCurrentIndex(id);
    mTabHandler->setTabToolTip(id, mStartPageWidget->windowTitle());
  }
}

void MainWindowPresenter::openGitHub()
{
  QDesktopServices::openUrl(QUrl("https://github.com/TIDOP-USAL/photomatch"));
}

void MainWindowPresenter::openKeypointsViewer()
{
  emit openKeypointsViewerDialogFromSession(mProjectModel->currentSession()->name());
}

void MainWindowPresenter::openMatchesViewer()
{
  emit openMatchesViewerDialogFromSession(mProjectModel->currentSession()->name());
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
    mView->setFlag(MainWindowView::Flag::loading_images, true);

    connect(mView, SIGNAL(imagesLoaded()),   this,  SLOT(onLoadImages()));
  }
}

void MainWindowPresenter::openOnlineHelp()
{
  QDesktopServices::openUrl(QUrl("https://elliestath.github.io/HelpTest/site/"));
}

void MainWindowPresenter::loadProject()
{
  mView->clear();

  mView->setProjectTitle(mProjectModel->name());
  mView->setFlag(MainWindowView::Flag::project_exists, true);

  QString prjFile = mProjectModel->path();

  /// Se añade al historial de proyectos recientes
  mSettingsModel->addToHistory(prjFile);
  mView->updateHistory(mSettingsModel->history());
  mStartPageWidget->setHistory(mSettingsModel->history());

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
    mView->setFlag(MainWindowView::Flag::loading_images, true);
    connect(mView, SIGNAL(imagesLoaded()),   this,  SLOT(onLoadImages()));
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
  try {
    //QString image_path = mProjectModel->findImageByName(image)->path();
    mTabHandler->setImage(image);
  } catch (std::exception &e) {
    tl::MessageManager::release(e.what(), tl::MessageLevel::msg_error);
  }
}

void MainWindowPresenter::activeImage(const QString &image)
{
  try {
    QString image_path = mProjectModel->findImageByName(image)->path();

    std::list<std::pair<QString, QString>> properties = mModel->exif(image_path);
    mView->setProperties(properties);
    mView->setActiveImage(image);
  } catch (std::exception &e) {
    tl::MessageManager::release(e.what(), tl::MessageLevel::msg_error);
  }
}

void MainWindowPresenter::activeImages(const QStringList &images)
{
  mView->setActiveImages(images);
}

void MainWindowPresenter::deleteImages(const QStringList &images)
{
  //mProjectModel->deleteImages(images);
  TL_TODO("Se tienen que eliminar del proyecto las imagenes procesadas, y los ficheros de keypoints y de matches")
  for (const auto &image : images) {
    //mView->deleteImage(image);
    this->deleteImage(image);
    TL_TODO("Se tienen que eliminar de la vista las imagenes procesadas, y los ficheros de keypoints y de matches")
  }
}

void MainWindowPresenter::deleteImage(const QString &image)
{
  try {
    QString image_path = mProjectModel->findImageByName(image)->path();
    mProjectModel->deleteImage(image_path);
    mView->deleteImage(image);
    mView->setFlag(MainWindowView::Flag::project_modified, true);
    mView->setFlag(MainWindowView::Flag::images_added, mProjectModel->imagesCount() > 0);
  } catch (std::exception &e) {
    tl::MessageManager::release(e.what(), tl::MessageLevel::msg_error);
  }
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
        Acebsf *acebsf = dynamic_cast<Acebsf *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), QString("ACEBSF")));
        properties.push_back(std::make_pair(QString("Block Size"), QString::number(acebsf->blockSize().width()).append("x").append(QString::number(acebsf->blockSize().height()))));
        properties.push_back(std::make_pair(QString("L"), QString::number(acebsf->l())));
        properties.push_back(std::make_pair(QString("K1"), QString::number(acebsf->k1())));
        properties.push_back(std::make_pair(QString("K2"), QString::number(acebsf->k2())));
      } else if (preprocess->type() == Preprocess::Type::clahe){
        Clahe *clahe = dynamic_cast<Clahe *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), QString("CLAHE")));
        properties.push_back(std::make_pair(QString("Clip Limit"), QString::number(clahe->clipLimit())));
        properties.push_back(std::make_pair(QString("Grid Size"),
                                            QString::number(clahe->tilesGridSize().width())
                                            .append("x")
                                            .append(QString::number(clahe->tilesGridSize().height()))));
      } else if (preprocess->type() == Preprocess::Type::cmbfhe){
        Cmbfhe *cmbfhe = dynamic_cast<Cmbfhe *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "CMBFHE"));
        properties.push_back(std::make_pair(QString("Block Size"),
                                            QString::number(cmbfhe->blockSize().width()).append("x").append(QString::number(cmbfhe->blockSize().height()))));
      } else if (preprocess->type() == Preprocess::Type::decolor){
        properties.push_back(std::make_pair(QString("Name"), "Decolor"));
      } else if (preprocess->type() == Preprocess::Type::dhe){
        Dhe *dhe = dynamic_cast<Dhe *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "DHE"));
        properties.push_back(std::make_pair(QString("X"), QString::number(dhe->x())));
      } else if (preprocess->type() == Preprocess::Type::fahe){
        Fahe *fahe = dynamic_cast<Fahe *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "FAHE"));
        properties.push_back(std::make_pair(QString("Block Size"),
                                            QString::number(fahe->blockSize().width())
                                            .append("x")
                                            .append(QString::number(fahe->blockSize().height()))));
      } else if (preprocess->type() == Preprocess::Type::hmclahe){
        Hmclahe *hmclahe = dynamic_cast<Hmclahe *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "HMCLAHE"));
        properties.push_back(std::make_pair(QString("Block Size"),
                                            QString::number(hmclahe->blockSize().width())
                                            .append("x")
                                            .append(QString::number(hmclahe->blockSize().height()))));
        properties.push_back(std::make_pair(QString("L"), QString::number(hmclahe->l())));
        properties.push_back(std::make_pair(QString("Phi"), QString::number(hmclahe->phi())));
      } else if (preprocess->type() == Preprocess::Type::lce_bsescs){
        LceBsescs *lceBsescs = dynamic_cast<LceBsescs *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "LCE_BSESCS"));
        properties.push_back(std::make_pair(QString("Block Size"),
                                            QString::number(lceBsescs->blockSize().width())
                                            .append("x")
                                            .append(QString::number(lceBsescs->blockSize().height()))));
      } else if (preprocess->type() == Preprocess::Type::msrcp){
        Msrcp *msrcp = dynamic_cast<Msrcp *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "MSRCP"));
        properties.push_back(std::make_pair(QString("Small Scale"), QString::number(msrcp->smallScale())));
        properties.push_back(std::make_pair(QString("Mid Scale"), QString::number(msrcp->midScale())));
        properties.push_back(std::make_pair(QString("Large Scale"), QString::number(msrcp->largeScale())));
      } else if (preprocess->type() == Preprocess::Type::noshp){
        Noshp *noshp = dynamic_cast<Noshp *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "NOSHP"));
        properties.push_back(std::make_pair(QString("Block Size"),
                                            QString::number(noshp->blockSize().width())
                                            .append("x")
                                            .append(QString::number(noshp->blockSize().height()))));
      } else if (preprocess->type() == Preprocess::Type::pohe){
        Pohe *pohe = dynamic_cast<Pohe *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "POHE"));
        properties.push_back(std::make_pair(QString("Block Size"),
                                            QString::number(pohe->blockSize().width())
                                            .append("x")
                                            .append(QString::number(pohe->blockSize().height()))));
      } else if (preprocess->type() == Preprocess::Type::rswhe){
        Rswhe *rswhe = dynamic_cast<Rswhe *>(preprocess.get());
        properties.push_back(std::make_pair(QString("Name"), "RSWHE"));
        properties.push_back(std::make_pair(QString("Histogram Divisions"), QString::number(rswhe->histogramDivisions())));
        properties.push_back(std::make_pair(QString("Histogram Cut"), QString::number(static_cast<int>(rswhe->histogramCut()))));
      } else if (preprocess->type() == Preprocess::Type::wallis){
        Wallis *wallis = dynamic_cast<Wallis *>(preprocess.get());
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
    Agast *agast = dynamic_cast<Agast *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("AGAST")));
    properties.push_back(std::make_pair(QString("Threshold"), QString(agast->threshold())));
    properties.push_back(std::make_pair(QString("Nonmax Suppression"), agast->nonmaxSuppression() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Detector Type"), QString(agast->detectorType())));
  } else if (detector->type() == Feature::Type::akaze){
    Akaze *akaze = dynamic_cast<Akaze *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("AKAZE")));
    properties.push_back(std::make_pair(QString("Descriptor Type"), QString(akaze->descriptorType())));
    properties.push_back(std::make_pair(QString("Descriptor Size"), QString::number(akaze->descriptorSize())));
    properties.push_back(std::make_pair(QString("Descriptor Channels"), QString::number(akaze->descriptorChannels())));
    properties.push_back(std::make_pair(QString("Threshold"), QString::number(akaze->threshold())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(akaze->octaves())));
    properties.push_back(std::make_pair(QString("Octave Layers"), QString::number(akaze->octaveLayers())));
    properties.push_back(std::make_pair(QString("Diffusivity"), akaze->diffusivity()));
  } else if (detector->type() == Feature::Type::brisk){
    Brisk *brisk = dynamic_cast<Brisk *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("BRISK")));
    properties.push_back(std::make_pair(QString("Threshold"), QString::number(brisk->threshold())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(brisk->octaves())));
    properties.push_back(std::make_pair(QString("Pattern Scale"), QString::number(brisk->patternScale())));
  } else if (detector->type() == Feature::Type::fast){
    Fast *fast = dynamic_cast<Fast *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("FAST")));
    properties.push_back(std::make_pair(QString("Threshold"), QString::number(fast->threshold())));
    properties.push_back(std::make_pair(QString("Nonmax Suppression"), fast->nonmaxSuppression() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Detector Type"), QString(fast->detectorType())));
  } else if (detector->type() == Feature::Type::gftt){
    Gftt *gftt = dynamic_cast<Gftt *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("GFTT")));
    properties.push_back(std::make_pair(QString("Max Features"), QString::number(gftt->maxFeatures())));
    properties.push_back(std::make_pair(QString("Quality Level"), QString::number(gftt->qualityLevel())));
    properties.push_back(std::make_pair(QString("Min Distance"), QString::number(gftt->minDistance())));
    properties.push_back(std::make_pair(QString("Block Size"), QString::number(gftt->blockSize())));
    properties.push_back(std::make_pair(QString("Harris Detector"), gftt->harrisDetector() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("K"), QString::number(gftt->k())));
  } else if (detector->type() == Feature::Type::kaze){
    Kaze *kaze = dynamic_cast<Kaze *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("KAZE")));
    properties.push_back(std::make_pair(QString("Extended Descriptor"), kaze->extendedDescriptor() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Upright"), kaze->uprightDescriptor() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Threshold"), QString::number(kaze->threshold())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(kaze->octaves())));
    properties.push_back(std::make_pair(QString("Octave Layers"), QString::number(kaze->octaveLayers())));
    properties.push_back(std::make_pair(QString("Diffusivity"), kaze->diffusivity()));
  } else if (detector->type() == Feature::Type::msd){
    Msd *msd = dynamic_cast<Msd *>(detector.get());
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
    Mser *mser = dynamic_cast<Mser *>(detector.get());
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
    Orb *orb = dynamic_cast<Orb *>(detector.get());
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
    Sift *sift = dynamic_cast<Sift *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("SIFT")));
    properties.push_back(std::make_pair(QString("Features Number"), QString::number(sift->featuresNumber())));
    properties.push_back(std::make_pair(QString("Octave Layers"), QString::number(sift->octaveLayers())));
    properties.push_back(std::make_pair(QString("Contrast Threshold"), QString::number(sift->contrastThreshold())));
    properties.push_back(std::make_pair(QString("Edge Threshold"), QString::number(sift->edgeThreshold())));
    properties.push_back(std::make_pair(QString("Sigma"), QString::number(sift->sigma())));
  } else if (detector->type() == Feature::Type::star){
    Star *star = dynamic_cast<Star *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("STAR")));
    properties.push_back(std::make_pair(QString("Max Size"), QString::number(star->maxSize())));
    properties.push_back(std::make_pair(QString("Response Threshold"), QString::number(star->responseThreshold())));
    properties.push_back(std::make_pair(QString("Line Threshold Projected"), QString::number(star->lineThresholdProjected())));
    properties.push_back(std::make_pair(QString("Line Threshold Binarized"), QString::number(star->lineThresholdBinarized())));
    properties.push_back(std::make_pair(QString("Suppress Nonmax Size"), QString::number(star->suppressNonmaxSize())));
  } else if (detector->type() == Feature::Type::surf){
    Surf *surf = dynamic_cast<Surf *>(detector.get());
    properties.push_back(std::make_pair(QString("Name"), QString("SURF")));
    properties.push_back(std::make_pair(QString("Hessian Threshold"), QString::number(surf->hessianThreshold())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(surf->octaves())));
    properties.push_back(std::make_pair(QString("Octave Layers"), QString::number(surf->octaveLayers())));
    properties.push_back(std::make_pair(QString("Extended Descriptor"), surf->extendedDescriptor() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Rotated Features"), surf->upright() ? "true" : "false"));
  }

  mView->setProperties(properties);
}

void MainWindowPresenter::selectDescriptor(const QString &session)
{
  ///TODO: ¿Mover a modelo?

  std::shared_ptr<Session> _session = mProjectModel->findSession(session);
  std::shared_ptr<Feature> descriptor = _session->descriptor();

  std::list<std::pair<QString, QString>> properties;
  if (descriptor->type() == Feature::Type::akaze){
    Akaze *akaze = dynamic_cast<Akaze *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("AKAZE")));
    properties.push_back(std::make_pair(QString("Descriptor Type"), QString(akaze->descriptorType())));
    properties.push_back(std::make_pair(QString("Descriptor Size"), QString::number(akaze->descriptorSize())));
    properties.push_back(std::make_pair(QString("Descriptor Channels"), QString::number(akaze->descriptorChannels())));
    properties.push_back(std::make_pair(QString("Threshold"), QString::number(akaze->threshold())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(akaze->octaves())));
    properties.push_back(std::make_pair(QString("Octave Layers"), QString::number(akaze->octaveLayers())));
    properties.push_back(std::make_pair(QString("Diffusivity"), akaze->diffusivity()));
  } else if (descriptor->type() == Feature::Type::brief){
    Brief *brief = dynamic_cast<Brief *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("BRIEF")));
    properties.push_back(std::make_pair(QString("Bytes"), brief->bytes()));
    properties.push_back(std::make_pair(QString("Use Orientation"), brief->useOrientation() ? "true" : "false"));
  } else if (descriptor->type() == Feature::Type::brisk){
    Brisk *brisk = dynamic_cast<Brisk *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("BRISK")));
    properties.push_back(std::make_pair(QString("Threshold"), QString::number(brisk->threshold())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(brisk->octaves())));
    properties.push_back(std::make_pair(QString("Pattern Scale"), QString::number(brisk->patternScale())));
  } else if (descriptor->type() == Feature::Type::daisy){
    Daisy *daisy = dynamic_cast<Daisy *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("DAISY")));
    properties.push_back(std::make_pair(QString("Q Radius"), QString::number(daisy->radius())));
    properties.push_back(std::make_pair(QString("Q Theta"), QString::number(daisy->qRadius())));
    properties.push_back(std::make_pair(QString("Q Hist Scale"), QString::number(daisy->qTheta())));
    properties.push_back(std::make_pair(QString("Q Radius"), QString::number(daisy->qHist())));
    properties.push_back(std::make_pair(QString("Norm"), daisy->norm()));
    properties.push_back(std::make_pair(QString("Interpolation"), daisy->interpolation() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Use Orientation"), daisy->useOrientation() ? "true" : "false"));
  } else if (descriptor->type() == Feature::Type::freak){
    Freak *freak = dynamic_cast<Freak *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("FREAK")));
    properties.push_back(std::make_pair(QString("Orientation Normalized"), freak->orientationNormalized() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Scale Normalized"), freak->scaleNormalized() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("PatternScale"), QString::number(freak->patternScale())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(freak->octaves())));
  } else if (descriptor->type() == Feature::Type::hog){
    Hog *hog = dynamic_cast<Hog *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("HOG")));
    properties.push_back(std::make_pair(QString("Window Size"), QString::number(hog->winSize().width()).append("x").append(QString::number(hog->winSize().height()))));
    properties.push_back(std::make_pair(QString("Block Size"), QString::number(hog->blockSize().width()).append("x").append(QString::number(hog->blockSize().height()))));
    properties.push_back(std::make_pair(QString("Block Stride"), QString::number(hog->blockStride().width()).append("x").append(QString::number(hog->blockStride().height()))));
    properties.push_back(std::make_pair(QString("Cell Size"), QString::number(hog->cellSize().width()).append("x").append(QString::number(hog->cellSize().height()))));
    properties.push_back(std::make_pair(QString("Nbins"), QString::number(hog->nbins())));
    properties.push_back(std::make_pair(QString("DerivAperture"), QString::number(hog->derivAperture())));
  } else if (descriptor->type() == Feature::Type::kaze){
    Kaze *kaze = dynamic_cast<Kaze *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("KAZE")));
    properties.push_back(std::make_pair(QString("Extended Descriptor"), kaze->extendedDescriptor() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Upright"), kaze->uprightDescriptor() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Threshold"), QString::number(kaze->threshold())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(kaze->octaves())));
    properties.push_back(std::make_pair(QString("Octave Layers"), QString::number(kaze->octaveLayers())));
    properties.push_back(std::make_pair(QString("Diffusivity"), kaze->diffusivity()));
  } else if (descriptor->type() == Feature::Type::latch){
    Latch *latch = dynamic_cast<Latch *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("LATCH")));
    properties.push_back(std::make_pair(QString("Bytes"), latch->bytes()));
    properties.push_back(std::make_pair(QString("Rotation Invariance"), latch->rotationInvariance() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Half SSD Size"), QString::number(latch->halfSsdSize())));
  } else if (descriptor->type() == Feature::Type::lucid){
    Lucid *lucid = dynamic_cast<Lucid *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("LUCID")));
    properties.push_back(std::make_pair(QString("LUCID Kernel"), QString::number(lucid->lucidKernel())));
    properties.push_back(std::make_pair(QString("Blur Kernel"), QString::number(lucid->blurKernel())));
  } else if (descriptor->type() == Feature::Type::orb){
    Orb *orb = dynamic_cast<Orb *>(descriptor.get());
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
    Sift *sift = dynamic_cast<Sift *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("SIFT")));
    properties.push_back(std::make_pair(QString("Features Number"), QString::number(sift->featuresNumber())));
    properties.push_back(std::make_pair(QString("Octave Layers"), QString::number(sift->octaveLayers())));
    properties.push_back(std::make_pair(QString("Contrast Threshold"), QString::number(sift->contrastThreshold())));
    properties.push_back(std::make_pair(QString("Edge Threshold"), QString::number(sift->edgeThreshold())));
    properties.push_back(std::make_pair(QString("Sigma"), QString::number(sift->sigma())));
  } else if (descriptor->type() == Feature::Type::surf){
    Surf *surf = dynamic_cast<Surf *>(descriptor.get());
    properties.push_back(std::make_pair(QString("Name"), QString("SURF")));
    properties.push_back(std::make_pair(QString("Hessian Threshold"), QString::number(surf->hessianThreshold())));
    properties.push_back(std::make_pair(QString("Octaves"), QString::number(surf->octaves())));
    properties.push_back(std::make_pair(QString("Octave Layers"), QString::number(surf->octaveLayers())));
    properties.push_back(std::make_pair(QString("Extended Descriptor"), surf->extendedDescriptor() ? "true" : "false"));
    properties.push_back(std::make_pair(QString("Rotated Features"), surf->upright() ? "true" : "false"));
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

void MainWindowPresenter::openImageMatches(const QString &sessionName,
                                           const QString &imgName1,
                                           const QString &imgName2)
{
  std::vector<std::pair<QPointF, QPointF>> matches;
  QString imgPath1 = mProjectModel->findImageByName(imgName1)->path();
  QString imgPath2 = mProjectModel->findImageByName(imgName2)->path();

  if (QFileInfo(imgPath1).exists() == false || QFileInfo(imgPath2).exists() == false)
    return;

  QString name(sessionName);
  name.append("/").append(imgName1).append("-").append(imgName2);
  int idTab = mTabHandler->graphicViewerId(name);
  if (idTab == -1){

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

    GraphicViewerImp *graphicViewer = mTabHandler->addGraphicViewer(name);
    if (graphicViewer){
      QImage imageLeft(imgPath1);
      QImage imageRight(imgPath2);
      int height = imageLeft.height() > imageRight.height() ? imageLeft.height() : imageRight.height();
      QImage pair(imageLeft.width() + imageRight.width(), height, imageLeft.format());

      QPainter painter;
      painter.begin(&pair);
      painter.drawImage(0, 0, imageLeft);
      painter.drawImage(imageLeft.width(), 0, imageRight);
      QPen point_pen(QColor(0, 0, 255), 2.);
      point_pen.setCosmetic(true);
      QPen line_pen(QColor(229, 9, 127), 2.);
      line_pen.setCosmetic(true);
      painter.end();

      graphicViewer->setImage(pair);

      for (size_t i = 0; i < matches.size(); i++){
        graphicViewer->scene()->addLine(matches[i].first.x(), matches[i].first.y(),
                                        imageLeft.width() + matches[i].second.x(),
                                        matches[i].second.y(), line_pen);
        graphicViewer->scene()->addEllipse(matches[i].first.x() - 5, matches[i].first.y() - 5, 10, 10, point_pen);
        graphicViewer->scene()->addEllipse(imageLeft.width() + matches[i].second.x() - 5, matches[i].second.y() - 5, 10, 10, point_pen);
      }

      graphicViewer->zoomExtend();

    }
  } else {
    mTabHandler->setCurrentTab(idTab);
  }
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
      mTabHandler->hideTab(mTabHandler->graphicViewerId(preprocess));
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

          /// Cierre de ficheros abiertos
          QString name(session->name());
          name.append("/").append(QFileInfo(pair.second).baseName());
          mTabHandler->hideTab(mTabHandler->graphicViewerId(name));
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
  mView->setFlag(MainWindowView::Flag::processing, false);
}

void MainWindowPresenter::processRunning()
{
  mView->setFlag(MainWindowView::Flag::processing, true);
}

void MainWindowPresenter::onLoadImages()
{
  mView->setFlag(MainWindowView::Flag::loading_images, false);
  disconnect(mView, SIGNAL(imagesLoaded()),   this,  SLOT(onLoadImages()));
}

void MainWindowPresenter::help()
{
  mHelpDialog->navigateHome();
  mHelpDialog->show();
}

void MainWindowPresenter::open()
{
  mView->showMaximized();
}

void MainWindowPresenter::setHelp(HelpDialog *help)
{
  mHelpDialog = help;
}

void MainWindowPresenter::init()
{
  //mProjectModel = new ProjectModel(mProjectIO, mProject);
  //mSettingsModel = new SettingsModel(mSettings, mSettingsRW);
  //mSettingsModel->read();

  //initHelpDialog();

  mTabHandler = mView->tabHandler();
  openStartPage(); /// Show Start Page

  /* Projects history */
  mView->updateHistory(mSettingsModel->history());
  mStartPageWidget->setHistory(mSettingsModel->history());
}

void MainWindowPresenter::initSignalAndSlots()
{
/* Menú Archivo */

  connect(mView, &MainWindowView::openNew,                this, &MainWindowPresenter::openNew);
  connect(mView, &MainWindowView::openProject,            this, &MainWindowPresenter::openProject);
  connect(mView, &MainWindowView::openProjectFromHistory, this, &MainWindowPresenter::openFromHistory);  ///TODO: falta test señal
  connect(mView, &MainWindowView::clearHistory,           this, &MainWindowPresenter::deleteHistory);
  connect(mView, &MainWindowView::openExportFeatures,     this, &MainWindowPresenter::openExportFeaturesDialog);
  connect(mView, &MainWindowView::openExportMatches,      this, &MainWindowPresenter::openExportMatchesDialog);
  connect(mView, &MainWindowView::saveProject,            this, &MainWindowPresenter::saveProject);
  connect(mView, &MainWindowView::saveProjectAs,          this, &MainWindowPresenter::saveProjectAs);
  connect(mView, &MainWindowView::closeProject,           this, &MainWindowPresenter::closeProject);
  connect(mView, &MainWindowView::exit,                   this, &MainWindowPresenter::exit);

  /* Menú View */

  connect(mView,   &MainWindowView::openStartPage,        this, &MainWindowPresenter::openStartPage);
  connect(mView,   &MainWindowView::openSettings,         this, &MainWindowPresenter::openSettingsDialog);
  connect(mView,   &MainWindowView::openViewSettings,     this, &MainWindowPresenter::openViewSettingsDialog);

  /* Quality Control */

  connect(mView,  SIGNAL(openKeypointsViewer()),      this, SLOT(openKeypointsViewer()));
  connect(mView,  SIGNAL(openMatchesViewer()),        this, SLOT(openMatchesViewer()));
  connect(mView,  &MainWindowView::openMultiviewMatchingAssessment,  this, &MainWindowPresenter::openMultiviewMatchingAssessmentDialog);
  connect(mView,  &MainWindowView::groundTruthEditor,        this, &MainWindowPresenter::openGroundTruthEditorDialog);
  connect(mView,  &MainWindowView::homography,               this, &MainWindowPresenter::openHomographyViewerDialog);
  connect(mView,  &MainWindowView::prCurves,                 this, &MainWindowPresenter::openPRCurvesViewerDialog);
  connect(mView,  &MainWindowView::rocCurves,                this, &MainWindowPresenter::openROCCurvesViewerDialog);
  connect(mView,  &MainWindowView::detCurves,                this, &MainWindowPresenter::openDETCurvesViewerDialog);
  connect(mView,  &MainWindowView::openQualityControlSettings, this, &MainWindowPresenter::openQualityControlSettingsDialog);

  /* Menú herramientas */

  connect(mView,   &MainWindowView::loadImages,            this, &MainWindowPresenter::loadImages);
  connect(mView,   &MainWindowView::newSession,            this, &MainWindowPresenter::openNewSessionDialog);
  connect(mView,   &MainWindowView::openPreprocess,        this, &MainWindowPresenter::openPreprocessDialog);
  connect(mView,   &MainWindowView::openFeatureExtraction, this, &MainWindowPresenter::openFeatureExtractionDialog);
  connect(mView,   &MainWindowView::openFeatureMatching,   this, &MainWindowPresenter::openFeatureMatchingDialog);
  connect(mView,   &MainWindowView::openToolSettings,      this, &MainWindowPresenter::openToolSettingsDialog);

  /* Menú Ayuda */

  connect(mView, &MainWindowView::openHelpDialog,     this, &MainWindowPresenter::help);
  connect(mView, &MainWindowView::openOnlineHelp,     this, &MainWindowPresenter::openOnlineHelp);
  connect(mView, &MainWindowView::openAboutDialog,    this, &MainWindowPresenter::openAboutDialog);

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

  connect(mView, SIGNAL(openImageMatches(QString,QString,QString)),   this, SLOT(openImageMatches(QString,QString,QString)));

  connect(mView, SIGNAL(activeSessionChange(QString)), this, SLOT(activeSession(QString)));
  connect(mView, SIGNAL(delete_session(QString)),      this, SLOT(deleteSession(QString)));

  connect(mView, SIGNAL(openKeypointsViewer(QString, QString)),         this, SIGNAL(openKeypointsViewerDialogFromSessionAndImage(QString, QString)));
  connect(mView, SIGNAL(openMatchesViewer(QString, QString, QString)),  this, SIGNAL(openMatchesViewerDialogFromSessionAndImages(QString, QString, QString)));

}

void MainWindowPresenter::initStartPage()
{
  if (mStartPageWidget == nullptr){
    mStartPageWidget = new StartPageWidget(mView);

    connect(mStartPageWidget,   &StartPageWidget::openNew,                this, &MainWindowPresenter::openNew);
    connect(mStartPageWidget,   &StartPageWidget::openProject,            this, &MainWindowPresenter::openProject);
    connect(mStartPageWidget,   &StartPageWidget::openSettings,           this, &MainWindowPresenter::openSettingsDialog);
    connect(mStartPageWidget,   &StartPageWidget::openGitHub,             this, &MainWindowPresenter::openGitHub);
    connect(mStartPageWidget,   &StartPageWidget::clearHistory,           this, &MainWindowPresenter::deleteHistory);
    connect(mStartPageWidget,   &StartPageWidget::openProjectFromHistory, this, &MainWindowPresenter::openFromHistory);
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

      mView->addFeatures(_session->name(), detector->name(), descriptor->name(), _session->features());

      return true;
    }

  }
  return false;
}

bool MainWindowPresenter::loadMatches(const QString &session)
{
  if (std::shared_ptr<Session> _session = mProjectModel->findSession(session)){

    std::shared_ptr<MatchingMethod> match = _session->matchingMethod();

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

