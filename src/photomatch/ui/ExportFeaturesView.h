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

#include "photomatch/ui/ExportFeatures.h"

class QLabel;
class QComboBox;
class QDialogButtonBox;
class QCheckBox;
class QListWidget;
class QLineEdit;

namespace photomatch
{


class ExportFeaturesViewImp
  : public ExportFeaturesView
{

  Q_OBJECT

public:

  ExportFeaturesViewImp(QWidget *parent = nullptr);
  virtual ~ExportFeaturesViewImp() override;

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

  void initUI() override;
  void initSignalAndSlots() override;

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
