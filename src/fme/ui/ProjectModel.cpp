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

void fme::ProjectModel::init()
{
}

} // namespace fme




