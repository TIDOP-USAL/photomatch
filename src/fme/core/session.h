#ifndef FME_SESSION_H
#define FME_SESSION_H

#include "fme/fme_global.h"

#include <memory>

#include <QString>

#include "fme/core/features/features.h"

namespace fme
{

class Preprocess;

class FME_EXPORT ISession
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

  virtual std::shared_ptr<Preprocess> preprocess() = 0;

  virtual void setPreprocess(const std::shared_ptr<Preprocess> &preprocess) = 0;

  virtual std::shared_ptr<Feature> detector() = 0;
  virtual void setDetector(const std::shared_ptr<Feature> &detector) = 0;

  virtual std::shared_ptr<Feature> descriptor() = 0;
  virtual void setDescriptor(const std::shared_ptr<Feature> &descriptor) = 0;

  /*!
   * \brief Limpia la sesión
   */
  virtual void clear() = 0;

};


class FME_EXPORT Session
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
  std::shared_ptr<Preprocess> preprocess() override;
  void setPreprocess(const std::shared_ptr<Preprocess> &preprocess) override;
  std::shared_ptr<Feature> detector() override;
  void setDetector(const std::shared_ptr<Feature> &detector) override;
  std::shared_ptr<Feature> descriptor() override;
  void setDescriptor(const std::shared_ptr<Feature> &descriptor) override;

  void clear() override;

protected:

  QString mName;
  QString mDescription;
  std::shared_ptr<Preprocess> mPreprocess;
  std::shared_ptr<Feature> mFeatureDetector;
  std::shared_ptr<Feature> mFeatureDescriptor;
};

} // namespace fme

#endif // FME_SESSION_H
