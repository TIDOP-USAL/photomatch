#ifndef FME_SESSION_H
#define FME_SESSION_H

#include "fme/fme_global.h"

#include <QString>

namespace fme
{

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
  void clear() override;

protected:

  QString mName;
  QString mDescription;

};

} // namespace fme

#endif // FME_SESSION_H
