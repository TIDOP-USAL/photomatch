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


#ifndef PHOTOMATCH_CURVES_VIEWER_PRESENTER_H
#define PHOTOMATCH_CURVES_VIEWER_PRESENTER_H

#include <memory>

#include <QObject>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class ICurvesViewerView;
class ICurvesViewerModel;
class HelpDialog;

class ICurvesViewerPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  ICurvesViewerPresenter() : IPresenter() {}
  virtual ~ICurvesViewerPresenter() override {}

protected slots:

  virtual void loadLeftImage(const QString &image) = 0;
  virtual void loadRightImage(const QString &image) = 0;
  virtual void activeSession(const QString &session) = 0;
  virtual void disableSession(const QString &session) = 0;
  virtual void computeCurve(const QString &session, const QString &imageLeft, const QString &imageRight) = 0;
  virtual void deleteCurve(const QString &session) = 0;
};

class CurvesViewerPresenter
  : public ICurvesViewerPresenter
{

  Q_OBJECT

public:

  CurvesViewerPresenter(ICurvesViewerView *view,
                        ICurvesViewerModel *model);
  ~CurvesViewerPresenter() override {}

//ICurvesViewerPresenter interface

protected slots:

  void loadLeftImage(const QString &image) override;
  void loadRightImage(const QString &image) override;
  void activeSession(const QString &session) override;
  void disableSession(const QString &session) override;
  void computeCurve(const QString &session, const QString &imageLeft, const QString &imageRight) override;
  void deleteCurve(const QString &session) override;


// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(std::shared_ptr<HelpDialog> &help) override;

private:

  void init() override;

private:

  ICurvesViewerView *mView;
  ICurvesViewerModel *mModel;
  std::shared_ptr<HelpDialog> mHelp;
};

} // namespace photomatch

#endif // PHOTOMATCH_CURVES_VIEWER_PRESENTER_H
