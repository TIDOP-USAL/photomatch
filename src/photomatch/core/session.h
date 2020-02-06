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


#ifndef PHOTOMATCH_SESSION_H
#define PHOTOMATCH_SESSION_H

#include "photomatch/photomatch_global.h"

#include <memory>
#include <vector>
#include <map>

#include <QString>

namespace photomatch
{

class Preprocess;
class Feature;
class MatchingMethod;
class MatchingStrategy;

class PHOTOMATCH_EXPORT Session
{

public:

  Session(){}
  virtual ~Session() = default;

  /*!
   * \brief Devuelve el nombre de la sesión
   * \return Nombre de la sesión
   */
  virtual QString name() const = 0;

  /*!
   * \brief Establece el nombre de la sesión
   * \param[in] name Nombre de la sesión
   */
  virtual void setName(const QString &name) = 0;

  /*!
   * \brief Devuelve la descripción de la sesión
   * \return Descripción de la sesión
   */
  virtual QString description() const = 0;

  /*!
   * \brief Establece la descripción de la sesión
   * \param[in] description Descripción de la sesión
   */
  virtual void setDescription(const QString &description) = 0;

  /*!
   * \brief Devuelve el tamaño máximo de imagen
   * \return
   */
  virtual int maxImageSize() const = 0;

  /*!
   * \brief Establece el tamaño máximo de imagen
   * \param[in] size Tamaño máximo de imagen
   */
  virtual void setMaxImageSize(int size) = 0;

  /*!
   * \brief Utiliza el tamaño completo de imagen
   * \param[in] fullImageSize
   */
  virtual void setFullImageSize(bool fullImageSize) = 0;

  /*!
   * \brief Comprueba si esta activo el uso de la imagen a tamaño completo
   * \return
   */
  virtual bool fullImageSize() const = 0;

  virtual std::shared_ptr<Preprocess> preprocess() = 0;

  virtual void setPreprocess(const std::shared_ptr<Preprocess> &preprocess) = 0;

  virtual std::shared_ptr<Feature> detector() = 0;
  virtual void setDetector(const std::shared_ptr<Feature> &detector) = 0;

  virtual std::shared_ptr<Feature> descriptor() = 0;
  virtual void setDescriptor(const std::shared_ptr<Feature> &descriptor) = 0;

  virtual std::shared_ptr<MatchingMethod> matchingMethod() = 0;
  virtual void setMatchingMethod(const std::shared_ptr<MatchingMethod> &matchingMethod) = 0;

  virtual std::shared_ptr<MatchingStrategy> matchingStrategy() = 0;
  virtual void setMatchingStrategy(const std::shared_ptr<MatchingStrategy> &matchingStrategy) = 0;

  virtual void addPreprocessImage(const QString &img) = 0;
  virtual void deletePreprocessImage(const QString &img) = 0;
  virtual void deletePreprocessImages() = 0;
  virtual std::vector<QString> preprocessImages() const = 0;
  virtual QString preprocessImage(const QString &image) const = 0;

  virtual void addFeatures(const QString &feat) = 0;
  virtual void deleteFeatures(const QString &feat) = 0;
  virtual void deleteFeatures() = 0;
  virtual std::vector<QString> features() const = 0;
  virtual QString features(const QString &image) const = 0;

  virtual void addMatches(const QString &img1, const QString &img2, const QString &fileMatch) = 0;
  virtual void deleteMatches(const QString &img1, const QString &img2, const QString &fileMatch) = 0;
  virtual void deleteMatches(const QString &img1) = 0;
  virtual void deleteMatches() = 0;
  virtual std::map<QString, std::vector<std::pair<QString, QString>>> matches() const = 0;
  virtual std::vector<std::pair<QString, QString>> matches(const QString &image) const = 0;

  virtual QString passPoints() const = 0;
  virtual void setPassPoints(const QString &passPoint) = 0;

  /*!
   * \brief Limpia la sesión
   */
  virtual void clear() = 0;

};


class PHOTOMATCH_EXPORT SessionImp
  : public Session
{

public:

  SessionImp();
  SessionImp(const QString &name, const QString &description);
  ~SessionImp() override = default;

// ISession interface

public:

  QString name() const override;
  void setName(const QString &name) override;
  QString description() const override;
  void setDescription(const QString &description) override;
  int maxImageSize() const override;
  void setMaxImageSize(int size) override;
  void setFullImageSize(bool fullImageSize) override;
  bool fullImageSize() const override;
  std::shared_ptr<Preprocess> preprocess() override;
  void setPreprocess(const std::shared_ptr<Preprocess> &preprocess) override;
  std::shared_ptr<Feature> detector() override;
  void setDetector(const std::shared_ptr<Feature> &detector) override;
  std::shared_ptr<Feature> descriptor() override;
  void setDescriptor(const std::shared_ptr<Feature> &descriptor) override;
  std::shared_ptr<MatchingMethod> matchingMethod() override;
  void setMatchingMethod(const std::shared_ptr<MatchingMethod> &matchingMethod) override;
  std::shared_ptr<MatchingStrategy> matchingStrategy() override;
  void setMatchingStrategy(const std::shared_ptr<MatchingStrategy> &matchingStrategy) override;

  void addPreprocessImage(const QString &img) override;
  void deletePreprocessImage(const QString &img) override;
  void deletePreprocessImages() override;
  std::vector<QString> preprocessImages() const override;
  QString preprocessImage(const QString &image) const override;

  void addFeatures(const QString &feat) override;
  void deleteFeatures(const QString &feat) override;
  void deleteFeatures() override;
  std::vector<QString> features() const override;
  QString features(const QString &image) const override;

  void addMatches(const QString &img1, const QString &img2, const QString &fileMatch) override;
  void deleteMatches(const QString &img1, const QString &img2, const QString &fileMatch) override;
  void deleteMatches(const QString &img1) override;
  void deleteMatches() override;
  std::map<QString, std::vector<std::pair<QString, QString>>> matches() const override;
  std::vector<std::pair<QString, QString>> matches(const QString &image) const override;

  QString passPoints() const override;
  void setPassPoints(const QString &passPoint) override;

  void clear() override;

protected:

  QString mName;
  QString mDescription;
  int mMaxImageSize;
  std::shared_ptr<Preprocess> mPreprocess;
  std::shared_ptr<Feature> mFeatureDetector;
  std::shared_ptr<Feature> mFeatureDescriptor;
  std::shared_ptr<MatchingMethod> mMatchingMethod;
  std::shared_ptr<MatchingStrategy> mMatchingStrategy;
  std::vector<QString> mPreprocessImages;
  std::vector<QString> mFeatures;
  std::map<QString, std::vector<std::pair<QString, QString>>> mImagesPairs;
  QString mPassPoints;
};

} // namespace photomatch

#endif // PHOTOMATCH_SESSION_H
