#include "ProjectModel.h"

#include <QDir>

namespace photomatch
{

ProjectModel::ProjectModel(IProjectRW *projectIO, IProject *project, QObject *parent)
  : IProjectModel(parent),
    mProjectIO(projectIO),
    mProject(project),
    mPrjFile(""),
    bUnsavedChanges(false)
{
  init();
}

ProjectModel::~ProjectModel()
{

}

QString ProjectModel::name() const
{
  return mProject->name();
}

void ProjectModel::setName(const QString &name)
{
  mProject->setName(name);
  bUnsavedChanges = true;
}

QString ProjectModel::description() const
{
  return mProject->description();
}

void ProjectModel::setDescription(const QString &description)
{
  mProject->setDescription(description);
  bUnsavedChanges = true;
}

QString ProjectModel::projectFolder() const
{
  return mProject->projectFolder();
}

void ProjectModel::setProjectFolder(const QString &dir)
{
  mProject->setProjectFolder(dir);
  bUnsavedChanges = true;
}

QString ProjectModel::version() const
{
  return mProject->version();
}

QString ProjectModel::groundTruth() const
{
  return mProject->groundTruth();
}

void ProjectModel::setGroundTruth(const QString &groundTruth)
{
  mProject->setGroundTruth(groundTruth);
}

void ProjectModel::addImage(const std::shared_ptr<Image> &img)
{
  mProject->addImage(img);
  bUnsavedChanges = true;
}

void ProjectModel::deleteImage(const QString &img)
{
  mProject->deleteImage(img);
  bUnsavedChanges = true;
}

void ProjectModel::deleteImage(size_t imgId)
{
  mProject->deleteImage(imgId);
  bUnsavedChanges = true;
}

const std::shared_ptr<Image> ProjectModel::findImage(const QString &path) const
{
  return mProject->findImage(path);
}

const std::shared_ptr<Image> ProjectModel::findImageById(size_t id) const
{
  return mProject->findImageById(id);
}

const std::shared_ptr<Image> ProjectModel::findImageByName(const QString &imgName) const
{
  return mProject->findImageByName(imgName);
}

size_t ProjectModel::findImageId(const QString &path) const
{
  return mProject->findImageId(path);
}

IProject::image_const_iterator ProjectModel::imageBegin() const
{
  return mProject->imageBegin();
}

IProject::image_const_iterator ProjectModel::imageEnd() const
{
  return mProject->imageEnd();
}

size_t ProjectModel::imagesCount() const
{
  return mProject->imagesCount();
}

void ProjectModel::addSession(const QString &name, const QString &description)
{
  mProject->addSession(name, description);
  bUnsavedChanges = true;
}

void ProjectModel::addSession(const std::shared_ptr<Session> &session)
{
  mProject->addSession(session);
  bUnsavedChanges = true;
}

void ProjectModel::deleteSession(const QString &nameSession)
{
  mProject->deleteSession(nameSession);
  bUnsavedChanges = true;
}

void ProjectModel::deleteSession(size_t sessionId)
{
  mProject->deleteSession(sessionId);
  bUnsavedChanges = true;
}

std::shared_ptr<Session> ProjectModel::findSession(const QString &sessionName)
{
  return mProject->findSession(sessionName);
}

const std::shared_ptr<Session> ProjectModel::findSession(const QString &sessionName) const
{
  return mProject->findSession(sessionName);
}

size_t ProjectModel::findSessionId(const QString &sessionName)
{
  return mProject->findSessionId(sessionName);
}

size_t ProjectModel::findSessionId(const QString &sessionName) const
{
  return mProject->findSessionId(sessionName);
}

IProject::session_const_iterator ProjectModel::sessionBegin() const
{
  return mProject->sessionBegin();
}

IProject::session_const_iterator ProjectModel::sessionEnd() const
{
  return mProject->sessionEnd();
}

size_t ProjectModel::sessionCount() const
{
  return mProject->sessionCount();
}

const std::shared_ptr<Session> ProjectModel::currentSession() const
{
  return mProject->currentSession();
}

void ProjectModel::setCurrentSession(const QString &sessionName)
{
  mProject->setCurrentSession(sessionName);
  bUnsavedChanges = true;
}

void ProjectModel::setPreprocess(const std::shared_ptr<Preprocess> &preprocess)
{
  this->currentSession()->setPreprocess(preprocess);
  bUnsavedChanges = true;
}

void ProjectModel::deletePreprocess()
{
  this->currentSession()->setPreprocess(nullptr);
  bUnsavedChanges = true;
}

void ProjectModel::setDetector(const std::shared_ptr<Feature> &detector)
{
  this->currentSession()->setDetector(detector);
  bUnsavedChanges = true;
}

void ProjectModel::deleteDetector()
{
  this->currentSession()->setDetector(nullptr);
  bUnsavedChanges = true;
}

void ProjectModel::setDescriptor(const std::shared_ptr<Feature> &descriptor)
{
  this->currentSession()->setDescriptor(descriptor);
  bUnsavedChanges = true;
}

void ProjectModel::deleteDescriptor()
{
  this->currentSession()->setDescriptor(nullptr);
  bUnsavedChanges = true;
}

void ProjectModel::setMatcher(const std::shared_ptr<Match> &matcher)
{
  this->currentSession()->setMatcher(matcher);
  bUnsavedChanges = true;
}

void ProjectModel::deleteMatcher()
{
  this->currentSession()->setMatcher(nullptr);
  bUnsavedChanges = true;
}

void ProjectModel::setRobustMatcherRefinement(const std::shared_ptr<IRobustMatcherRefinement> &robustMatcherRefinement)
{
  this->currentSession()->setRobustMatcherRefinement(robustMatcherRefinement);
  bUnsavedChanges = true;
}

int ProjectModel::maxImageSize() const
{
  return this->currentSession()->maxImageSize();
}

void ProjectModel::setMaxImageSize(int size)
{
  this->currentSession()->setMaxImageSize(size);
  bUnsavedChanges = true;
}

bool ProjectModel::fullImageSize() const
{
  return this->currentSession()->fullImageSize();
}

void ProjectModel::setFullImageSize(bool fullImageSize)
{
  this->currentSession()->setFullImageSize(fullImageSize);
  bUnsavedChanges = true;
}

void ProjectModel::addPreprocessedImage(const QString &image)
{
  this->currentSession()->addPreprocessImage(image);
  bUnsavedChanges = true;
}

void ProjectModel::deletePreprocessedImage(const QString &image)
{
  this->currentSession()->deletePreprocessImage(image);
  bUnsavedChanges = true;
}

void ProjectModel::clearPreprocessedImages()
{
  this->currentSession()->deletePreprocessImages();
  bUnsavedChanges = true;
}

void ProjectModel::addFeatures(const QString &feat)
{
  this->currentSession()->addFeatures(feat);
  bUnsavedChanges = true;
}

void ProjectModel::deleteFeatures(const QString &feat)
{
  this->currentSession()->deleteFeatures(feat);
  bUnsavedChanges = true;
}

void ProjectModel::clearFeatures()
{
  this->currentSession()->deleteFeatures();
  bUnsavedChanges = true;
}

void ProjectModel::addMatches(const QString &img1, const QString &img2, const QString &matchsFile)
{
  this->currentSession()->addMatches(img1, img2, matchsFile);
  bUnsavedChanges = true;
}

void ProjectModel::deleteMatches(const QString &img1, const QString &img2, const QString &matchsFile)
{
  this->currentSession()->deleteMatches(img1, img2, matchsFile);
  bUnsavedChanges = true;
}

void ProjectModel::clearMatches()
{
  this->currentSession()->deleteMatches();
  bUnsavedChanges = true;
}

QString ProjectModel::passPoints() const
{
  return this->currentSession()->passPoints();
}

void ProjectModel::setPassPoints(const QString &passPoint)
{
  this->currentSession()->setPassPoints(passPoint);
  bUnsavedChanges = true;
}

void ProjectModel::clear()
{
  mProject->clear();
  mPrjFile = "";
  bUnsavedChanges = false;
}

QString ProjectModel::path() const
{
  return mPrjFile;
}

void ProjectModel::load(const QString &file)
{
  mPrjFile = file;
  mProjectIO->read(file, *mProject);
  bUnsavedChanges = false;
}

void ProjectModel::save()
{
  saveAs(mPrjFile);
}

void ProjectModel::saveAs(const QString &file)
{
  mPrjFile = file;
  mProjectIO->write(file, *mProject);

  bUnsavedChanges = false;
}

bool ProjectModel::checkUnsavedChanges() const
{
  return bUnsavedChanges;
}

bool ProjectModel::checkOldVersion(const QString &file) const
{
  return mProjectIO->checkOldVersion(file);
}

void ProjectModel::oldVersionBak(const QString &file) const
{
  mProjectIO->oldVersionBak(file);
}

void ProjectModel::addImages(const QStringList &fileNames)
{
  for (const auto &file : fileNames){
    std::shared_ptr<Image> photo(new Image(file));

    ///TODO: Lectura de metadatos EXIF

    mProject->addImage(photo);
  }
}

void ProjectModel::deleteImages(const QStringList &images)
{
  for (const auto &image : images){
    deleteImage(image);
  }
}

void photomatch::ProjectModel::init()
{
}

} // namespace photomatch




