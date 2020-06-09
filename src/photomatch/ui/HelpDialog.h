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


#ifndef PHOTOMATCH_HELP_DIALOG_H
#define PHOTOMATCH_HELP_DIALOG_H

#include "photomatch/photomatch_global.h"

#include "mvp.h"

#include <QTextBrowser>

class QHelpEngine;

class HelpBrowser
  : public QTextBrowser
{

public:

  HelpBrowser(QHelpEngine *helpEngine,
              QWidget *parent = nullptr);

  QVariant loadResource (int type, const QUrl& name);


private:

  QHelpEngine *mHelpEngine;
};




namespace photomatch
{

class HelpDialog
  : public QDialog
{

  Q_OBJECT

public:

  HelpDialog(QWidget *parent = nullptr);
  ~HelpDialog() override;

 public slots:

 /*!
  * \brief navigateHome
  */
 void navigateHome();

  /*!
   * \brief setPage
   * \param page
   */
  void setPage(const QString &page);

private slots:

  /*!
   * \brief navigateBackward
   */
  void navigateBackward();
  
  /*!
   * \brief navigateForward
   */
  void navigateForward();

  /*!
   * \brief setContentSource
   * \param[in] index Índice de la página
   */
  void setContentSource(const QModelIndex &index);
  
  /*!
   * \brief setIndexSource
   * \param[in] index Índice de la página
   */
  void setIndexSource(const QModelIndex &index);
 
  /*!
   * \brief searchInvoked
   */
  void searchInvoked();

  /*!
   * \brief searchFinished
   * \param[in] hits
   */
  void searchFinished(int hits);

// IDialogView interface

private:

  void init();

private slots:

  void retranslate();

private:

  QHelpEngine *mHelpEngine;
  HelpBrowser *mHelpBrowser;
  QTextBrowser *mSearchResultsWidget;
  QAction *mNavigateForwardAction;
};

} // namespace photomatch


#endif // PHOTOMATCH_HELP_DIALOG_H
