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

#ifndef PHOTOMATCH_NEWPROJECT_INTERFACES_H
#define PHOTOMATCH_NEWPROJECT_INTERFACES_H

#include "photomatch/ui/mvp.h"

namespace photomatch
{


/*!
 * \brief INewProjectView
 */
class NewProjectView
  : public IDialogView
{

  Q_OBJECT

public:

  NewProjectView(QWidget *parent) : IDialogView(parent) {}
  ~NewProjectView() override = default;

  /*!
   * \brief Devuelve el nombre del proyecto
   * \return Nombre del proyecto
   */
  virtual QString projectName() const = 0;

  /*!
   * \brief Devuelve la ruta del proyecto
   * \return Ruta del proyecto
   */
  virtual QString projectPath() const = 0;

  /*!
   * \brief Establece la ruta del proyecto
   * \param path Ruta del proyecto
   */
  virtual void setProjectPath(const QString &path) = 0;

  /*!
   * \brief Devuelve la descripción del proyecto
   * \return Descripción del proyecto
   */
  virtual QString projectDescription() const = 0;

  virtual bool createProjectFolder() const = 0;
  virtual void setExistingProject(bool prjExist) = 0;

protected slots:

  virtual void onClickButtonSelectPath() = 0;

signals:

  void projectNameChange();
};


/*!
 * \brief The INewProjectPresenter class
 */
class NewProjectPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  NewProjectPresenter(){}

  virtual ~NewProjectPresenter() override = default;

signals:

  /*!
   * \brief Señal que se emite cuando se crea el proyecto
   */
  void projectCreate();

protected slots:

  /*!
   * \brief Guarda el proyecto
   */
  virtual void saveProject() = 0;

  /*!
   * \brief Descarta los cambios en el proyecto
   */
  virtual void discartProject() = 0;

  /*!
   * \brief Comprueba si ya existe un proyecto con el mismo nombre
   */
  virtual void checkProjectName() const = 0;

};

} // namespace photomatch

#endif // PHOTOMATCH_NEWPROJECT_INTERFACES_H
