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

#ifndef PHOTOMATCH_NEWSESSION_INTERFACES_H
#define PHOTOMATCH_NEWSESSION_INTERFACES_H

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class NewSessionView
  : public PhotoMatchDialogView
{

  Q_OBJECT

public:

  NewSessionView(QWidget *parent) : PhotoMatchDialogView(parent) {}
  virtual ~NewSessionView() override {}

  /*!
   * \brief Devuelve el nombre de la sesión
   * \return Nombre de la sesión
   */
  virtual QString sessionName() const = 0;

  /*!
   * \brief Devuelve la descripción de la sesión
   * \return Descripción de la sesión
   */
  virtual QString sessionDescription() const = 0;

  virtual void setExistingName(bool nameExist) = 0;

signals:

  void sessionNameChange(QString);
};


class NewSessionPresenter
  : public PhotoMatchPresenter
{
  Q_OBJECT

public:

  NewSessionPresenter() {}
  virtual ~NewSessionPresenter() {}

signals:

  /*!
   * \brief Señal que se emite cuando se crea la sesión
   */
  void sessionCreate(QString);

protected slots:

  /*!
   * \brief Guarda la sesión en el proyecto
   */
  virtual void saveProject() = 0;

  /*!
   * \brief Descarta los cambios en el proyecto
   */
  virtual void discartProject() = 0;

  /*!
   * \brief Comprueba si ya existe una sesión con el mismo nombre
   * \param[in] name Session name
   */
  virtual void checkSessionName(const QString &name) = 0;
};


} // namespace photomatch

#endif // PHOTOMATCH_NEWSESSION_INTERFACES_H
