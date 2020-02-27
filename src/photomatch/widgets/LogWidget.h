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


#ifndef PHOTOMATCH_LOG_WIDGET_H
#define PHOTOMATCH_LOG_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

#include <mutex>

#include <tidop/core/defs.h>
#include <tidop/core/flags.h>
#include <tidop/core/messages.h>

class QDateTimeEdit;
class QListWidget;
class QGridLayout;

namespace photomatch
{

class PHOTOMATCH_EXPORT LogWidget
  : public PhotoMatchWidget,
    public tl::MessageManager::Listener
{
  Q_OBJECT

public:

  explicit LogWidget(QWidget *parent = nullptr);
  ~LogWidget() override;

  /*!
   * \brief Filter the messages displayed in the console
   * \param[in] level Log level
   */
  void filter(tl::MessageLevel level);

  /*!
   * \brief Set log level
   * \param[in] level Log level
   */
  void setLogLevel(tl::MessageLevel level);

  void print(const char *msg, const char *date, tl::MessageLevel level);
  void refresh();

public slots:

  virtual void clear();

private slots:

  void onPushButtonShowLogWarningToggled(bool active);
  void onPushButtonShowLogErrorsToggled(bool active);
  void onPushButtonShowLogInfoToggled(bool active);
  void onPushButtonShowLogDebugToggled(bool active);
  void onRowsInserted(const QModelIndex &parent,int start,int end,QPrivateSignal);
  void onRowsRemoved(const QModelIndex &parent,int start,int end,QPrivateSignal);

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  void initUI() override;
  void initSignalAndSlots() override;

// Listener interface

public:

  void onMsgDebug(const char *msg, const char *date) override;
  void onMsgInfo(const char *msg, const char *date) override;
  void onMsgWarning(const char *msg, const char *date) override;
  void onMsgError(const char *msg, const char *date) override;

private:

  static tl::EnumFlags<tl::MessageLevel> sLevel;
  static tl::EnumFlags<tl::MessageLevel> sFilterLevel;
  static std::mutex mtx;

  QGridLayout *mGridLayout;
  QListWidget *mListWidget;
  QAction* mMsgErrorAction;
  QAction* mMsgWarningAction;
  QAction* mMsgInfoAction;
  QAction* mClearAction;
  //QDateTimeEdit *mDateTimeEdit;

};

} // namespace photomatch

#endif // PHOTOMATCH_LOG_WIDGET_H
