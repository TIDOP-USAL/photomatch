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


#ifndef PHOTOMATCH_PROJECT_MODEL_H
#define PHOTOMATCH_PROJECT_MODEL_H

#include <QObject>

#include "photomatch/core/project.h"
#include "photomatch/ui/mvp.h"

namespace photomatch
{

class ProjectModel
  : public IModel/*,
    public IProject*/
{

  Q_OBJECT

public:

  ProjectModel(QObject *parent = nullptr) : IModel(parent) {}

  /*!
   * \brief Project file path
   * \return Project file path
   */
  virtual QString path() const = 0;

  /*!
   * \brief Load a project
   * \param[in] file Project file
   */
  virtual void load(const QString &file) = 0;

  /*!
   * \brief Save the project
   */
  virtual void save() = 0;

  /*!
   * \brief Save a project as ...
   * \param[in] file Project file
   */
  virtual void saveAs(const QString &file) = 0;

  /*!
   * \brief Check for changes without saving in the project
   * \return
   */
  virtual bool checkUnsavedChanges() const = 0;

  /*!
   * \brief Check if a project is an old version
   * \param[in] file Project file
   * \return
   */
  virtual bool checkOldVersion(const QString &file) const = 0;

  /*!
   * \brief Create a copy of a project from an old version with the same name and a suffix with the version
   * \param[in] file Project file
   */
  virtual void oldVersionBak(const QString &file) const = 0;

  /*!
   * \brief Returns the name of the project
   * \return Project's name
   */
  virtual QString name() const = 0;

  /*!
   * \brief Set the project name
   * \param[in] name Project's name
   */
  virtual void setName(const QString &name) = 0;

  /*!
   * \brief Returns the project description
   * \return Project description
   */
  virtual QString description() const = 0;

  /*!
   * \brief Set the project description
   * \param[in] description Project description
   */
  virtual void setDescription(const QString &description) = 0;

  /*!
   * \brief Returns the project directory
   * \return Project directory
   */
  virtual QString projectFolder() const = 0;

  /*!
   * \brief Set the project directory
   * \param[in] path Project Directory
   */
  virtual void setProjectFolder(const QString &dir) = 0;

  /*!
   * \brief Project File Version
   * The project file version is used to update old projects
   * \return Project File Version
   */
  virtual QString version() const = 0;

  /*!
   * \brief Set Ground Truth
   * \param[in] groundTruth Ground Truth
   */
  virtual void setGroundTruth(const QString &groundTruth) = 0;

  /*!
   * \brief Returns the Ground Truth
   * \return Ground Truth
   */
  virtual QString groundTruth() const = 0;

  /*!
   * \brief Add an image to the project
   * \param[in] img Image
   */
  virtual void addImage(const std::shared_ptr<Image> &img) = 0;

  /*!
   * \brief Delete an image from the project
   * \param[in] img Image path to be deleted
   */
  virtual void deleteImage(const QString &img) = 0;

  /*!
   * \brief Delete an image from the project
   * \param[in] imgId ID image to be deleted
   */
  virtual void deleteImage(size_t imgId) = 0;

  /*!
   * \brief Search for an image in the project
   * \param[in] path Image path
   * \return Image object or null pointer if not found
   */
  virtual const std::shared_ptr<Image> findImage(const QString &path) const = 0;

  virtual const std::shared_ptr<Image> findImageById(size_t id) const = 0;
  virtual const std::shared_ptr<Image> findImageByName(const QString &imgName) const = 0;

  /*!
   * \brief Search for an image in the project
   * \param[in] path Image path
   * \return Image ID o std::numeric_limits<size_t>().max() if it is not found
   */
  virtual size_t findImageId(const QString &path) const = 0;

  /*!
   * \brief Returns a constant iterator at the beginning of the image list
   * \return Iterator to the first element of the image list
   */
  virtual Project::image_const_iterator imageBegin() const = 0;

  /*!
   * \brief Return a constant iterator to the next element after the last image
   * \return Constant Iterator to the next element after the last image
   */
  virtual Project::image_const_iterator imageEnd() const = 0;

  /*!
   * \brief Number of images of the project
   * \return
   */
  virtual size_t imagesCount() const = 0;

  /*!
   * \brief Add images
   * \param[in] fileNames Image list to be added
   */
  virtual void addImages(const QStringList &fileNames) = 0;

  /*!
   * \brief Delete images
   * \param[in] images Image list to be deleted
   */
  virtual void deleteImages(const QStringList &images) = 0;

  /*!
   * \brief Add a session
   * \param[in] name Session name
   * \param[in] description Session description
   */
  virtual void addSession(const QString &name, const QString &description) = 0;

  /*!
   * \brief Add a session
   * \param[in] session Session
   */
  virtual void addSession(const std::shared_ptr<Session> &session) = 0;

  /*!
   * \brief Delete a session
   * \param[in] nameSession Session name
   */
  virtual void deleteSession(const QString &nameSession) = 0;

  /*!
   * \brief Delete a session
   * \param[in] sessionId Session ID
   */
  virtual void deleteSession(size_t sessionId) = 0;

  /*!
   * \brief Search for a session in the project
   * \param[in] sessionName Session name
   * \return
   */
  virtual std::shared_ptr<Session> findSession(const QString &sessionName) = 0;

  /*!
   * \brief Search for a session in the project
   * \param[in] sessionName Session name
   * \return
   */
  virtual const std::shared_ptr<Session> findSession(const QString &sessionName) const = 0;

  /*!
   * \brief Search for the session ID in the project
   * \param[in] sessionName Session name
   * \return
   */
  virtual size_t findSessionId(const QString &sessionName) = 0;

  /*!
   * \brief Search for the session ID in the project
   * \param[in] sessionName Session name
   * \return
   */
  virtual size_t findSessionId(const QString &sessionName) const = 0;

  /*!
   * \brief Returns a constant iterator at the beginning of the session list
   * \return Iterador al primer elemento del listado de sessiones
   */
  virtual Project::session_const_iterator sessionBegin() const = 0;

  /*!
   * \brief Return a constant iterator to the next item after the last session
   * \return Constant Iterator to the next element after the last session
   */
  virtual Project::session_const_iterator sessionEnd() const = 0;

  /*!
   * \brief Number of project sessions
   * \return
   */
  virtual size_t sessionCount() const = 0;

  /*!
   * \brief Returns current session
   * \return
   */
  virtual const std::shared_ptr<Session> currentSession() const = 0;

  /*!
   * \brief Set current session
   * \param[in] sessionName Session name
   */
  virtual void setCurrentSession(const QString &sessionName) = 0;

  /*!
   * \brief Set Preprocess
   * \param[in] preprocess Preprocess
   */
  virtual void setPreprocess(const std::shared_ptr<Preprocess> &preprocess) = 0;

  /*!
   * \brief Delete Preprocess
   */
  virtual void deletePreprocess() = 0;

  /*!
   * \brief Set Detector
   * \param[in] detector Detector
   */
  virtual void setDetector(const std::shared_ptr<Feature> &detector) = 0;

  /*!
   * \brief Delete Detector
   */
  virtual void deleteDetector() = 0;

  /*!
   * \brief Set Descriptor
   * \param[in] descriptor Descriptor
   */
  virtual void setDescriptor(const std::shared_ptr<Feature> &descriptor) = 0;

  /*!
   * \brief Delete Descriptor
   */
  virtual void deleteDescriptor() = 0;

  /*!
   * \brief setMatcher
   * \param[in] matcher
   */
  virtual void setMatcher(const std::shared_ptr<MatchingMethod> &matcher) = 0;

  /*!
   * \brief deleteMatcher
   */
  virtual void deleteMatcher() = 0;

  /*!
   * \brief Set Robust Matcher Refinement
   * \param[in] robustMatcherRefinement
   */
  virtual void setRobustMatcherRefinement(const std::shared_ptr<RobustMatcher> &robustMatcherRefinement) = 0;

  /*!
   * \brief Returns Maximum image size
   * \return Maximum image size
   */
  virtual int maxImageSize() const = 0;

  /*!
   * \brief Set maximum image size
   * \param[in] size Maximum image size
   */
  virtual void setMaxImageSize(int size) = 0;

  /*!
   * \brief Full image size
   * \return Full image size
   */
  virtual bool fullImageSize() const = 0;

  /*!
   * \brief Set full image size
   * \param[in] fullImageSize Full image size
   */
  virtual void setFullImageSize(bool fullImageSize) = 0;

  /*!
   * \brief Add Preprocessed Image
   * \param[in] image Preprocessed Image
   */
  virtual void addPreprocessedImage(const QString &image) = 0;

  /*!
   * \brief Delete Preprocessed Image
   * \param[in] image Preprocessed Image
   */
  virtual void deletePreprocessedImage(const QString &image) = 0;

  /*!
   * \brief clear preprocessed images
   */
  virtual void clearPreprocessedImages() = 0;

  /*!
   * \brief Add features
   * \param[in] feat Features
   */
  virtual void addFeatures(const QString &feat) = 0;

  /*!
   * \brief Delete features
   * \param[in] feat Features
   */
  virtual void deleteFeatures(const QString &feat) = 0;

  /*!
   * \brief Clear features
   */
  virtual void clearFeatures() = 0;

  /*!
   * \brief Add Matches
   * \param[in] img1 Image 1
   * \param[in] img2 Image 2
   * \param[in] matchsFile Matchs file
   */
  virtual void addMatches(const QString &img1, const QString &img2, const QString &matchsFile) = 0;

  /*!
   * \brief Delete matches
   * \param img1 Image 1
   * \param img2 Image 2
   * \param matchsFile atchs file
   */
  virtual void deleteMatches(const QString &img1, const QString &img2, const QString &matchsFile) = 0;

  /*!
   * \brief clear matches
   */
  virtual void clearMatches() = 0;

  /*!
   * \brief Pass points
   * \return Pass points
   */
  virtual QString passPoints() const = 0;

  /*!
   * \brief Set pass points
   * \param[in] passPoint Pass points
   */
  virtual void setPassPoints(const QString &passPoint) = 0;

  virtual void clear() = 0;

};



class ProjectModelImp
  : public ProjectModel
{

  Q_OBJECT

public:

  explicit ProjectModelImp(ProjectController *projectIO, Project *project, QObject *parent = nullptr);
  ~ProjectModelImp() override;

signals:

public slots:

// IProject interface

public:

  QString name() const override;
  void setName(const QString &name) override;
  QString description() const override;
  void setDescription(const QString &description) override;
  QString projectFolder() const override;
  void setProjectFolder(const QString &dir) override;
  QString version() const override;
  QString groundTruth() const override;
  void setGroundTruth(const QString &groundTruth) override;
  void addImage(const std::shared_ptr<Image> &img) override;
  void deleteImage(const QString &img) override;
  void deleteImage(size_t imgId) override;
  const std::shared_ptr<Image> findImage(const QString &path) const override;
  const std::shared_ptr<Image> findImageById(size_t id) const override;
  const std::shared_ptr<Image> findImageByName(const QString &imgName) const override;
  size_t findImageId(const QString &path) const override;
  Project::image_const_iterator imageBegin() const override;
  Project::image_const_iterator imageEnd() const override;
  size_t imagesCount() const override;
  void addSession(const QString &name, const QString &description) override;
  void addSession(const std::shared_ptr<Session> &session) override;
  void deleteSession(const QString &nameSession) override;
  void deleteSession(size_t sessionId) override;
  std::shared_ptr<Session> findSession(const QString &sessionName) override;
  const std::shared_ptr<Session> findSession(const QString &sessionName) const override;
  size_t findSessionId(const QString &sessionName) override;
  size_t findSessionId(const QString &sessionName) const override;
  Project::session_const_iterator sessionBegin() const override;
  Project::session_const_iterator sessionEnd() const override;
  size_t sessionCount() const override;
  const std::shared_ptr<Session> currentSession() const override;
  void setCurrentSession(const QString &sessionName) override;
  void setPreprocess(const std::shared_ptr<Preprocess> &preprocess) override;
  void deletePreprocess() override;
  void setDetector(const std::shared_ptr<Feature> &detector) override;
  void deleteDetector() override;
  void setDescriptor(const std::shared_ptr<Feature> &descriptor) override;
  void deleteDescriptor() override;
  void setMatcher(const std::shared_ptr<MatchingMethod> &matcher) override;
  void deleteMatcher() override;
  void setRobustMatcherRefinement(const std::shared_ptr<RobustMatcher> &robustMatcherRefinement) override;
  int maxImageSize() const override;
  void setMaxImageSize(int size) override;
  bool fullImageSize() const override;
  void setFullImageSize(bool fullImageSize) override;
  void addPreprocessedImage(const QString &image) override;
  void deletePreprocessedImage(const QString &image) override;
  void clearPreprocessedImages() override;
  void addFeatures(const QString &feat) override;
  void deleteFeatures(const QString &feat) override;
  void clearFeatures() override;
  void addMatches(const QString &img1, const QString &img2, const QString &matchsFile) override;
  void deleteMatches(const QString &img1, const QString &img2, const QString &matchsFile) override;
  void clearMatches() override;
  QString passPoints() const override;
  void setPassPoints(const QString &passPoint) override;

  void clear() override;

// IProjectModel interface

public:

  QString path() const override;
  void load(const QString &file) override;
  void save() override;
  void saveAs(const QString &file) override;
  bool checkUnsavedChanges() const override;
  bool checkOldVersion(const QString &file) const override;
  void oldVersionBak(const QString &file) const override;
  void addImages(const QStringList &fileNames) override;
  void deleteImages(const QStringList &images) override;

// IModel interface

private:

  void init() override;

protected:

  ProjectController *mProjectIO;
  Project *mProject;
  QString mPrjFile;
  bool bUnsavedChanges;

};

} // namespace photomatch

#endif // PHOTOMATCH_PROJECT_MODEL_H
