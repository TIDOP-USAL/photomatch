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


#ifndef PHOTOMATCH_EXPORT_MATCHES_PRESENTER_H
#define PHOTOMATCH_EXPORT_MATCHES_PRESENTER_H

#include <QObject>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IExportMatchesView;
class IExportMatchesModel;
class HelpDialog;

class IExportMatchesPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IExportMatchesPresenter(){}
  virtual ~IExportMatchesPresenter() override = default;

public slots:

  virtual void save() = 0;
  virtual void sessionChange(const QString &session) = 0;

};


class ExportMatchesPresenter
  : public IExportMatchesPresenter
{

  Q_OBJECT

public:

  ExportMatchesPresenter(IExportMatchesView *view,
                         IExportMatchesModel *model);
  ~ExportMatchesPresenter() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(std::shared_ptr<HelpDialog> &help) override;

private:

  void init() override;

// IExportMatchesPresenter interface

public:

  void save() override;
  void sessionChange(const QString &session) override;

protected:

  IExportMatchesView *mView;
  IExportMatchesModel *mModel;
  std::shared_ptr<HelpDialog> mHelp;
};



} // namespace photomatch

#endif // PHOTOMATCH_EXPORT_MATCHES_PRESENTER_H
