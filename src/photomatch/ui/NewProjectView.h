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


#ifndef PHOTOMATCH_NEW_PROJECT_VIEW_H
#define PHOTOMATCH_NEW_PROJECT_VIEW_H

#include "photomatch/ui/NewProject.h"

class QLineEdit;
class QCheckBox;
class QDialogButtonBox;
class QTextEdit;
class QPushButton;
class QLabel;

namespace photomatch
{

class NewProjectViewImp
  : public NewProjectView
{
  Q_OBJECT

public:

  explicit NewProjectViewImp(QWidget *parent = nullptr);
  ~NewProjectViewImp() override = default;

// NewProjectView interface

public:

  QString projectName() const override;
  QString projectPath() const override;
  void setProjectPath(const QString &path) override;
  QString projectDescription() const override;
  bool createProjectFolder() const override;
  void setExistingProject(bool prjExist) override;

protected slots:

  void onClickButtonSelectPath() override;

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

  QLabel *mLabelProjectName;
  QLineEdit *mLineEditProjectName;
  QLabel *mLabelProjectPath;
  QLineEdit *mLineEditProjectPath;
  QLabel *mLabelProjectFile;
  QLineEdit *mLineEditProjectFile;
  QLabel *mLabelDescription;
  QTextEdit *mTextEditDescription;
  QCheckBox *mCheckBoxProjectFolder;
  QPushButton *mPushButtonProjectPath;
  QDialogButtonBox *mButtonBox;
  bool bPrjExist;
};

} // namespace photomatch


#endif // PHOTOMATCH_NEW_PROJECT_VIEW_H
