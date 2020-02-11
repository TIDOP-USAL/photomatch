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


#ifndef PHOTOMATCH_EXPORT_MATCHES_MODEL_H
#define PHOTOMATCH_EXPORT_MATCHES_MODEL_H


#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel;

class IExportMatchesModel
  : public IModel
{

  Q_OBJECT

public:

  IExportMatchesModel() {}
  virtual ~IExportMatchesModel() override = default;

  virtual QStringList sessions() const = 0;
  virtual QString sessionName() const = 0;
  virtual QStringList formats() const = 0;

public slots:

  virtual void exportMatches(const QString &file, const QString &format) const = 0;
  virtual void setSessionName(const QString &session) = 0;

};

class ExportMatchesModel
  : public IExportMatchesModel
{

  Q_OBJECT

public:

  ExportMatchesModel(IProjectModel *mProjectModel);
  ~ExportMatchesModel() override;

  QStringList sessions() const override;
  QString sessionName() const override;
  QStringList formats() const override;

public slots:

  void exportMatches(const QString &file, const QString &format) const override;
  void setSessionName(const QString &session) override;

// IModel interface

private:

  void init() override;

protected:

  IProjectModel *mProjectModel;
  QString mSession;

};

} // namespace photomatch

#endif // PHOTOMATCH_EXPORT_MATCHES_MODEL_H
