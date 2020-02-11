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


#ifndef PHOTOMATCH_EXPORT_MATCHES_VIEW_H
#define PHOTOMATCH_EXPORT_MATCHES_VIEW_H

#include "photomatch/ui/mvp.h"

class QLabel;
class QComboBox;
class QDialogButtonBox;
class QLineEdit;

namespace photomatch
{

class IExportMatchesView
  : public IDialogView
{

  Q_OBJECT

public:

  IExportMatchesView(QWidget *parent) : IDialogView(parent) {}
  virtual ~IExportMatchesView() override = default;

public slots:

  virtual void setSessions(const QStringList &sessions) = 0;
  virtual void setActiveSession(const QString &session) = 0;

signals:

  void sessionChange(QString);
};


class ExportMatchesView
  : public IExportMatchesView
{

  Q_OBJECT

public:

  ExportMatchesView(QWidget *parent = nullptr);
  virtual ~ExportMatchesView() override;

// IExportMatchesView interface

public slots:

  void setSessions(const QStringList &sessions) override;
  void setActiveSession(const QString &session) override;

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

protected:

  QLabel *mLabelSession;
  QComboBox *mComboBoxSession;
  QDialogButtonBox *mButtonBox;
};


} // namespace photomatch

#endif // PHOTOMATCH_EXPORT_MATCHES_VIEW_H
