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
class Match;
class IRobustMatcherRefinement;

class PHOTOMATCH_EXPORT ISession
{

public:

  ISession(){}
  virtual ~ISession() = default;

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

  virtual std::shared_ptr<Match> matcher() = 0;
  virtual void setMatcher(const std::shared_ptr<Match> &matcher) = 0;

  virtual std::shared_ptr<IRobustMatcherRefinement> robustMatcherRefinement() = 0;
  virtual void setRobustMatcherRefinement(const std::shared_ptr<IRobustMatcherRefinement> &robustMatcherRefinement) = 0;

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


class PHOTOMATCH_EXPORT Session
  : public ISession
{

public:

  Session();
  Session(const QString &name, const QString &description);
  ~Session() override = default;

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
  std::shared_ptr<Match> matcher() override;
  void setMatcher(const std::shared_ptr<Match> &matcher) override;
  std::shared_ptr<IRobustMatcherRefinement> robustMatcherRefinement() override;
  void setRobustMatcherRefinement(const std::shared_ptr<IRobustMatcherRefinement> &robustMatcherRefinement) override;

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
  std::shared_ptr<Match> mMatcher;
  std::shared_ptr<IRobustMatcherRefinement> mRobustMatcherRefinement;
  std::vector<QString> mPreprocessImages;
  std::vector<QString> mFeatures;
  std::map<QString, std::vector<std::pair<QString, QString>>> mImagesPairs;
  QString mPassPoints;
};

} // namespace photomatch

#endif // PHOTOMATCH_SESSION_H
