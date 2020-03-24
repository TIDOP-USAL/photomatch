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


#include "ProjectModel.h"

#include <QDir>

namespace photomatch
{

ProjectModelImp::ProjectModelImp(ProjectController *projectIO, Project *project, QObject *parent)
  : ProjectModel(parent),
    mProjectIO(projectIO),
    mProject(project),
    mPrjFile(""),
    bUnsavedChanges(false)
{
  init();
}

ProjectModelImp::~ProjectModelImp()
{

}

QString ProjectModelImp::name() const
{
  return mProject->name();
}

void ProjectModelImp::setName(const QString &name)
{
  mProject->setName(name);
  bUnsavedChanges = true;
}

QString ProjectModelImp::description() const
{
  return mProject->description();
}

void ProjectModelImp::setDescription(const QString &description)
{
  mProject->setDescription(description);
  bUnsavedChanges = true;
}

QString ProjectModelImp::projectFolder() const
{
  return mProject->projectFolder();
}

void ProjectModelImp::setProjectFolder(const QString &dir)
{
  mProject->setProjectFolder(dir);
  bUnsavedChanges = true;
}

QString ProjectModelImp::version() const
{
  return mProject->version();
}

QString ProjectModelImp::groundTruth() const
{
  return mProject->groundTruth();
}

void ProjectModelImp::setGroundTruth(const QString &groundTruth)
{
  mProject->setGroundTruth(groundTruth);
}

void ProjectModelImp::addImage(const std::shared_ptr<Image> &img)
{
  mProject->addImage(img);
  bUnsavedChanges = true;
}

void ProjectModelImp::deleteImage(const QString &img)
{
  mProject->deleteImage(img);
  bUnsavedChanges = true;
}

void ProjectModelImp::deleteImage(size_t imgId)
{
  mProject->deleteImage(imgId);
  bUnsavedChanges = true;
}

const std::shared_ptr<Image> ProjectModelImp::findImage(const QString &path) const
{
  return mProject->findImage(path);
}

const std::shared_ptr<Image> ProjectModelImp::findImageById(size_t id) const
{
  return mProject->findImageById(id);
}

const std::shared_ptr<Image> ProjectModelImp::findImageByName(const QString &imgName) const
{
  return mProject->findImageByName(imgName);
}

size_t ProjectModelImp::findImageId(const QString &path) const
{
  return mProject->findImageId(path);
}

Project::image_const_iterator ProjectModelImp::imageBegin() const
{
  return mProject->imageBegin();
}

Project::image_const_iterator ProjectModelImp::imageEnd() const
{
  return mProject->imageEnd();
}

size_t ProjectModelImp::imagesCount() const
{
  return mProject->imagesCount();
}

void ProjectModelImp::addSession(const QString &name, const QString &description)
{
  mProject->addSession(name, description);
  bUnsavedChanges = true;
}

void ProjectModelImp::addSession(const std::shared_ptr<Session> &session)
{
  mProject->addSession(session);
  bUnsavedChanges = true;
}

void ProjectModelImp::deleteSession(const QString &nameSession)
{
  mProject->deleteSession(nameSession);
  bUnsavedChanges = true;
}

void ProjectModelImp::deleteSession(size_t sessionId)
{
  mProject->deleteSession(sessionId);
  bUnsavedChanges = true;
}

std::shared_ptr<Session> ProjectModelImp::findSession(const QString &sessionName)
{
  return mProject->findSession(sessionName);
}

const std::shared_ptr<Session> ProjectModelImp::findSession(const QString &sessionName) const
{
  return mProject->findSession(sessionName);
}

size_t ProjectModelImp::findSessionId(const QString &sessionName)
{
  return mProject->findSessionId(sessionName);
}

size_t ProjectModelImp::findSessionId(const QString &sessionName) const
{
  return mProject->findSessionId(sessionName);
}

Project::session_const_iterator ProjectModelImp::sessionBegin() const
{
  return mProject->sessionBegin();
}

Project::session_const_iterator ProjectModelImp::sessionEnd() const
{
  return mProject->sessionEnd();
}

size_t ProjectModelImp::sessionCount() const
{
  return mProject->sessionCount();
}

const std::shared_ptr<Session> ProjectModelImp::currentSession() const
{
  return mProject->currentSession();
}

void ProjectModelImp::setCurrentSession(const QString &sessionName)
{
  mProject->setCurrentSession(sessionName);
  bUnsavedChanges = true;
}

void ProjectModelImp::setPreprocess(const std::shared_ptr<Preprocess> &preprocess)
{
  this->currentSession()->setPreprocess(preprocess);
  bUnsavedChanges = true;
}

void ProjectModelImp::deletePreprocess()
{
  this->currentSession()->setPreprocess(nullptr);
  bUnsavedChanges = true;
}

void ProjectModelImp::setDetector(const std::shared_ptr<Feature> &detector)
{
  this->currentSession()->setDetector(detector);
  bUnsavedChanges = true;
}

void ProjectModelImp::deleteDetector()
{
  this->currentSession()->setDetector(nullptr);
  bUnsavedChanges = true;
}

void ProjectModelImp::setDescriptor(const std::shared_ptr<Feature> &descriptor)
{
  this->currentSession()->setDescriptor(descriptor);
  bUnsavedChanges = true;
}

void ProjectModelImp::deleteDescriptor()
{
  this->currentSession()->setDescriptor(nullptr);
  bUnsavedChanges = true;
}

void ProjectModelImp::setMatcher(const std::shared_ptr<MatchingMethod> &matcher)
{
  this->currentSession()->setMatchingMethod(matcher);
  bUnsavedChanges = true;
}

void ProjectModelImp::deleteMatcher()
{
  this->currentSession()->setMatchingMethod(nullptr);
  bUnsavedChanges = true;
}

void ProjectModelImp::setRobustMatcherRefinement(const std::shared_ptr<RobustMatcher> &robustMatcherRefinement)
{
  this->currentSession()->setMatchingStrategy(robustMatcherRefinement);
  bUnsavedChanges = true;
}

int ProjectModelImp::maxImageSize() const
{
  return this->currentSession()->maxImageSize();
}

void ProjectModelImp::setMaxImageSize(int size)
{
  this->currentSession()->setMaxImageSize(size);
  bUnsavedChanges = true;
}

bool ProjectModelImp::fullImageSize() const
{
  return this->currentSession()->fullImageSize();
}

void ProjectModelImp::setFullImageSize(bool fullImageSize)
{
  this->currentSession()->setFullImageSize(fullImageSize);
  bUnsavedChanges = true;
}

void ProjectModelImp::addPreprocessedImage(const QString &image)
{
  this->currentSession()->addPreprocessImage(image);
  bUnsavedChanges = true;
}

void ProjectModelImp::deletePreprocessedImage(const QString &image)
{
  this->currentSession()->deletePreprocessImage(image);
  bUnsavedChanges = true;
}

void ProjectModelImp::clearPreprocessedImages()
{
  this->currentSession()->deletePreprocessImages();
  bUnsavedChanges = true;
}

void ProjectModelImp::addFeatures(const QString &feat)
{
  this->currentSession()->addFeatures(feat);
  bUnsavedChanges = true;
}

void ProjectModelImp::deleteFeatures(const QString &feat)
{
  this->currentSession()->deleteFeatures(feat);
  bUnsavedChanges = true;
}

void ProjectModelImp::clearFeatures()
{
  this->currentSession()->deleteFeatures();
  bUnsavedChanges = true;
}

void ProjectModelImp::addMatches(const QString &img1, const QString &img2, const QString &matchsFile)
{
  this->currentSession()->addMatches(img1, img2, matchsFile);
  bUnsavedChanges = true;
}

void ProjectModelImp::deleteMatches(const QString &img1, const QString &img2, const QString &matchsFile)
{
  this->currentSession()->deleteMatches(img1, img2, matchsFile);
  bUnsavedChanges = true;
}

void ProjectModelImp::clearMatches()
{
  this->currentSession()->deleteMatches();
  bUnsavedChanges = true;
}

QString ProjectModelImp::passPoints() const
{
  return this->currentSession()->passPoints();
}

void ProjectModelImp::setPassPoints(const QString &passPoint)
{
  this->currentSession()->setPassPoints(passPoint);
  bUnsavedChanges = true;
}

void ProjectModelImp::clear()
{
  mProject->clear();
  mPrjFile = "";
  bUnsavedChanges = false;
}

QString ProjectModelImp::path() const
{
  return mPrjFile;
}

void ProjectModelImp::load(const QString &file)
{
  mPrjFile = file;
  mProjectIO->read(file, *mProject);
  bUnsavedChanges = false;
}

void ProjectModelImp::save()
{
  saveAs(mPrjFile);
}

void ProjectModelImp::saveAs(const QString &file)
{
  mPrjFile = file;
  mProjectIO->write(file, *mProject);

  bUnsavedChanges = false;
}

bool ProjectModelImp::checkUnsavedChanges() const
{
  return bUnsavedChanges;
}

bool ProjectModelImp::checkOldVersion(const QString &file) const
{
  return mProjectIO->checkOldVersion(file);
}

void ProjectModelImp::oldVersionBak(const QString &file) const
{
  mProjectIO->oldVersionBak(file);
}

void ProjectModelImp::addImages(const QStringList &fileNames)
{
  for (const auto &file : fileNames){
    std::shared_ptr<Image> photo(new Image(file));

    ///TODO: Lectura de metadatos EXIF

    mProject->addImage(photo);
  }
}

void ProjectModelImp::deleteImages(const QStringList &images)
{
  for (const auto &image : images){
    deleteImage(image);
  }
}

void photomatch::ProjectModelImp::init()
{
}

} // namespace photomatch




