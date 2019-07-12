#include "ProjectModel.h"

#include <QDir>

namespace fme
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
  //emit nameChange(name);
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

std::shared_ptr<Image> ProjectModel::findImage(const QString &path)
{
  return mProject->findImage(path);
}

const std::shared_ptr<Image> ProjectModel::findImage(const QString &path) const
{
  return mProject->findImage(path);
}

size_t ProjectModel::findImageId(const QString &path)
{
  return mProject->findImageId(path);
}

size_t ProjectModel::findImageId(const QString &path) const
{
  return mProject->findImageId(path);
}

ProjectModel::image_iterator ProjectModel::imageBegin()
{
  return mProject->imageBegin();
}

ProjectModel::image_const_iterator ProjectModel::imageBegin() const
{
  return mProject->imageBegin();
}

ProjectModel::image_iterator ProjectModel::imageEnd()
{
  return mProject->imageEnd();
}

ProjectModel::image_const_iterator ProjectModel::imageEnd() const
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

ProjectModel::session_iterator ProjectModel::sessionBegin()
{
  return mProject->sessionBegin();
}

ProjectModel::session_const_iterator ProjectModel::sessionBegin() const
{
  return mProject->sessionBegin();
}

ProjectModel::session_iterator ProjectModel::sessionEnd()
{
  return mProject->sessionEnd();
}

ProjectModel::session_const_iterator ProjectModel::sessionEnd() const
{
  return mProject->sessionEnd();
}

size_t ProjectModel::sessionCount() const
{
  return mProject->sessionCount();
}

std::shared_ptr<Session> ProjectModel::currentSession()
{
  return mProject->currentSession();
}

const std::shared_ptr<Session> ProjectModel::currentSession() const
{
  return mProject->currentSession();
}

void ProjectModel::setCurrentSession(const QString &sessionName)
{
  mProject->setCurrentSession(sessionName);
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

  ///TODO: Señal de proyecto guardado
  /// emit modifiedProject(false);
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

void fme::ProjectModel::init()
{
}

} // namespace fme




