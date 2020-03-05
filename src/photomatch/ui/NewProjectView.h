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


#ifndef PHOTOMATCH_NEW_PROJECT_VIEW_H
#define PHOTOMATCH_NEW_PROJECT_VIEW_H

#include "photomatch/ui/mvp.h"

class QLineEdit;
class QCheckBox;
class QDialogButtonBox;
class QTextEdit;
class QPushButton;

namespace photomatch
{

/*!
 * \brief INewProjectView
 */
class INewProjectView
  : public IDialogView
{

  Q_OBJECT

public:

  INewProjectView(QWidget *parent) : IDialogView(parent) {}
  virtual ~INewProjectView() override = default;

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

protected slots:

  virtual void onClickButtonSelectPath() = 0;

};

class NewProjectView 
  : public INewProjectView
{
  Q_OBJECT

public:

  explicit NewProjectView(QWidget *parent = nullptr);
  ~NewProjectView() override;

// INewProjectView interface

public:

  QString projectName() const override;
  QString projectPath() const override;
  void setProjectPath(const QString &path) override;
  QString projectDescription() const override;
  bool createProjectFolder() const override;

protected slots:

  void onClickButtonSelectPath() override;

// IDialogView interface

private:

  void initUI() override;
  void initSignalAndSlots() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

protected:

  QLineEdit *mLineEditProjectName;
  QLineEdit *mLineEditProjectPath;
  QLineEdit *mLineEditProjectFile;
  QTextEdit *mTextEditDescription;
  QCheckBox *mCheckBoxProjectFolder;
  QPushButton *mPushButtonProjectPath;
  QDialogButtonBox *mButtonBox;

};

} // namespace photomatch


#endif // PHOTOMATCH_NEW_PROJECT_VIEW_H
