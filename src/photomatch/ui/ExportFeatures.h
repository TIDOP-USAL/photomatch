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

#ifndef PHOTOMATCH_EXPORT_FEATURES_INTERFACES_H
#define PHOTOMATCH_EXPORT_FEATURES_INTERFACES_H

#include "photomatch/ui/mvp.h"

namespace photomatch
{


class ExportFeaturesModel
  : public IModel
{

  Q_OBJECT

public:

  ExportFeaturesModel() {}
  virtual ~ExportFeaturesModel() override = default;

  virtual QStringList sessions() const = 0;
  virtual QString activeSessionName() const = 0;
  virtual QStringList formats() const = 0;
  virtual QStringList features(const QString &sessionName) const = 0;

public slots:

  virtual void exportFeatures(const QString &sessionName,
                              const QStringList &features,
                              const QString &path,
                              const QString &format) const = 0;

};


class ExportFeaturesView
  : public IDialogView
{

  Q_OBJECT

public:

  ExportFeaturesView(QWidget *parent) : IDialogView(parent) {}
  virtual ~ExportFeaturesView() override = default;

  virtual QString session() const = 0;
  virtual QString format() const = 0;
  virtual QStringList exportFiles() const = 0;
  virtual QString exportPath() const = 0;
  virtual bool exportAll() const = 0;

public slots:

  virtual void setSessions(const QStringList &sessions) = 0;
  virtual void setSessionToExport(const QString &session) = 0;
  virtual void setFormats(const QStringList &formats) = 0;
  virtual void setCurrentFormat(const QString &format) = 0;
  virtual void setExportAll(bool active) = 0;
  virtual void setExportPath(const QString &path) = 0;
  virtual void setImageFiles(const QStringList &images) = 0;

signals:

  void sessionChange(QString);
  void formatChange(QString);
  //void exportKeypoints();
};

class ExportFeaturesPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  ExportFeaturesPresenter(){}
  virtual ~ExportFeaturesPresenter() override = default;

public slots:

  virtual void save() = 0;
  virtual void sessionChange(const QString &session) = 0;

};

} // namespace photomatch

#endif // PHOTOMATCH_EXPORT_FEATURES_INTERFACES_H
