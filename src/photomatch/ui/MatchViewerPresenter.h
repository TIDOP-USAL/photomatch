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


#ifndef PHOTOMATCH_MATCH_VIEWER_PRESENTER_H
#define PHOTOMATCH_MATCH_VIEWER_PRESENTER_H

#include <memory>

#include <QObject>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IMatchViewerView;
class IMatchViewerModel;
class ISettingsModel;
class HelpDialog;

/*!
 * \brief The IMatchViewerPresenter class
 */
class IMatchViewerPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IMatchViewerPresenter(){}
  virtual ~IMatchViewerPresenter() {}

public slots:

  virtual void setSession(const QString &session) = 0;
  virtual void setLeftImage(const QString &image) = 0;
  virtual void setRightImage(const QString &image) = 0;
  //virtual void openImageFromSession(const QString &session, const QString &image) = 0;

protected slots:

  //virtual void loadLeftImage(const QString &image) = 0;
  //virtual void loadRightImage(const QString &image) = 0;
  virtual void loadMatches(const QString &imageLeft, const QString &imageRight) = 0;
  virtual void deleteMatch(const QString &imageLeft, const QString &imageRight, int query_id, int train_id) = 0;
};


class MatchViewerPresenter
  : public IMatchViewerPresenter
{
  Q_OBJECT

public:

  MatchViewerPresenter(IMatchViewerView *view,
                       IMatchViewerModel *model,
                       ISettingsModel *settings);

  ~MatchViewerPresenter() override;

// IMatchViewerPresenter interface

public slots:

  void setSession(const QString &session) override;
  void setLeftImage(const QString &image) override;
  void setRightImage(const QString &image) override;
  //void openImageFromSession(const QString &session, const QString &image) override;

protected slots:

//  void loadLeftImage(const QString &image) override;
//  void loadRightImage(const QString &image) override;
  void loadMatches(const QString &imageLeft, const QString &imageRight) override;
  void deleteMatch(const QString &imageLeft, const QString &imageRight, int query_id, int train_id) override;

  //void save();
  //void discart();

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(HelpDialog *help) override;

private:

  void init() override;



public slots:

// IMatchViewerPresenter interface


protected slots:

private:

  IMatchViewerView *mView;
  IMatchViewerModel *mModel;
  ISettingsModel *mSettingsModel;
  HelpDialog *mHelp;

};

} // namespace photomatch

#endif // PHOTOMATCH_MATCH_VIEWER_PRESENTER_H
