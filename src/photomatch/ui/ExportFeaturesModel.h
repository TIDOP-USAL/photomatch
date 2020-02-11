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


#ifndef PHOTOMATCH_EXPORT_FEATURES_MODEL_H
#define PHOTOMATCH_EXPORT_FEATURES_MODEL_H


#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel;

class IExportFeaturesModel
  : public IModel
{

  Q_OBJECT

public:

  IExportFeaturesModel() {}
  virtual ~IExportFeaturesModel() override = default;

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

class ExportFeaturesModel
  : public IExportFeaturesModel
{

  Q_OBJECT

public:

  ExportFeaturesModel(IProjectModel *mProjectModel);
  ~ExportFeaturesModel() override;

  QStringList sessions() const override;
  QString activeSessionName() const override;
  QStringList formats() const override;
  QStringList features(const QString &sessionName) const override;

public slots:

  void exportFeatures(const QString &sessionName,
                      const QStringList &features,
                      const QString &path,
                      const QString &format) const override;

// IModel interface

private:

  void init() override;

protected:

  IProjectModel *mProjectModel;

};

} // namespace photomatch

#endif // PHOTOMATCH_EXPORT_FEATURES_MODEL_H
