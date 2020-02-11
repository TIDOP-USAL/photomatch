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


#ifndef PHOTOMATCH_EXPORT_FEATURES_VIEW_H
#define PHOTOMATCH_EXPORT_FEATURES_VIEW_H

#include "photomatch/ui/mvp.h"

class QLabel;
class QComboBox;
class QDialogButtonBox;
class QCheckBox;
class QListWidget;
class QLineEdit;

namespace photomatch
{

class IExportFeaturesView
  : public IDialogView
{

  Q_OBJECT

public:

  IExportFeaturesView(QWidget *parent) : IDialogView(parent) {}
  virtual ~IExportFeaturesView() override = default;

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


class ExportFeaturesView
  : public IExportFeaturesView
{

  Q_OBJECT

public:

  ExportFeaturesView(QWidget *parent = nullptr);
  virtual ~ExportFeaturesView() override;

protected slots:

  void onPushButtonExportFormat();

// IExportFeaturesView interface

public:

  QString session() const override;
  QString format() const override;
  QStringList exportFiles() const override;
  QString exportPath() const override;
  bool exportAll() const override;

public slots:

  void setSessions(const QStringList &sessions) override;
  void setSessionToExport(const QString &session) override;
  void setFormats(const QStringList &formats) override;
  void setCurrentFormat(const QString &format) override;
  void setExportAll(bool active) override;
  void setExportPath(const QString &path) override;
  void setImageFiles(const QStringList &images) override;

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
  QLabel *mLabelFormat;
  QComboBox *mComboBoxFormat;
  QLabel *mLabelExportPath;
  QLineEdit *mLineEditExportPath;
  QPushButton *mPushButtonExportFormat;
  QCheckBox *mCheckBoxExportAll;
  QListWidget *mListWidgetfeatures;
  QDialogButtonBox *mButtonBox;
};


} // namespace photomatch

#endif // PHOTOMATCH_EXPORT_FEATURES_VIEW_H
