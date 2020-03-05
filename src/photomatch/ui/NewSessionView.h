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


#ifndef PHOTOMATCH_NEW_SESSION_VIEW_H
#define PHOTOMATCH_NEW_SESSION_VIEW_H

#include "photomatch/ui/mvp.h"

class QLineEdit;
class QTextEdit;
class QDialogButtonBox;

namespace photomatch
{

class INewSessionView
  : public IDialogView
{

  Q_OBJECT

public:

  INewSessionView(QWidget *parent) : IDialogView(parent) {}
  virtual ~INewSessionView() override {}

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

class NewSessionView
  : public INewSessionView
{
  Q_OBJECT

public:

  NewSessionView(QWidget *parent = nullptr);
  ~NewSessionView() override;

// IDialogView interface

private:

  void initUI() override;
  void initSignalAndSlots() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

// INewSessionView interface

public:

  QString sessionName() const override;
  QString sessionDescription() const override;
  void setExistingName(bool nameExist) override;

protected:

  QLineEdit *mLineEditSessionName;
  QTextEdit *mTextEditSessionDescription;
  QDialogButtonBox *mButtonBox;
  bool bNameExist;
};

} // namespace photomatch

#endif // PHOTOMATCH_NEW_SESSION_VIEW_H
