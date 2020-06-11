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


#include "NewProjectView.h"

#include <QFileDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>
#include <QApplication>

namespace photomatch
{

NewProjectViewImp::NewProjectViewImp(QWidget *parent)
  : NewProjectView(parent),
    mLabelProjectName(new QLabel(this)),
    mLineEditProjectName(new QLineEdit(this)),
    mLabelProjectPath(new QLabel(this)),
    mLineEditProjectPath(new QLineEdit(this)),
    mLabelProjectFile(new QLabel(this)),
    mLineEditProjectFile(new QLineEdit(this)),
    mLabelDescription(new QLabel(this)),
    mTextEditDescription(new QTextEdit(this)),
    mCheckBoxProjectFolder(new QCheckBox(this)),
    mPushButtonProjectPath(new QPushButton(this)),
    mButtonBox(new QDialogButtonBox(this)),
    bPrjExist(false)
{
  this->initUI();
  this->initSignalAndSlots();
}

// PhotoMatchDialogView interface

// private:

void NewProjectViewImp::initUI()
{
  this->setObjectName(QString("NewProjectView"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(450,300);

  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  layout->addWidget(mLabelProjectName, 0, 0);
  layout->addWidget(mLineEditProjectName, 0, 1, 1, 2);

  layout->addWidget(mLabelProjectPath, 1, 0);
  layout->addWidget(mLineEditProjectPath, 1, 1);
  mPushButtonProjectPath->setMaximumSize(QSize(31,28));
  mPushButtonProjectPath->setText("...");
  layout->addWidget(mPushButtonProjectPath, 1, 2);

  layout->addWidget(mLabelProjectFile, 2, 0);
  mLineEditProjectFile->setEnabled(false);
  layout->addWidget(mLineEditProjectFile, 2, 1, 1, 2);

  mCheckBoxProjectFolder->setChecked(true);
  layout->addWidget(mCheckBoxProjectFolder, 3, 0, 1, 3);

  layout->addWidget(mLabelDescription, 4, 0);

  layout->addWidget(mTextEditDescription, 5, 0, 1, 3);

  mButtonBox->setOrientation(Qt::Orientation::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Save | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
  layout->addWidget(mButtonBox, 7, 0, 1, 3);

  this->retranslate();
  this->update();
}

void NewProjectViewImp::initSignalAndSlots()
{
  connect(mLineEditProjectName,   &QLineEdit::textChanged,   this, &NewProjectViewImp::update);
  connect(mLineEditProjectName,   &QLineEdit::textChanged,   this, &NewProjectView::projectNameChange);
  connect(mLineEditProjectPath,   &QLineEdit::textChanged,   this, &NewProjectViewImp::update);
  connect(mCheckBoxProjectFolder, &QCheckBox::stateChanged,  this, &NewProjectViewImp::update);
  connect(mCheckBoxProjectFolder, &QCheckBox::stateChanged,  this, &NewProjectView::projectNameChange);
  connect(mPushButtonProjectPath, &QAbstractButton::clicked, this, &NewProjectViewImp::onClickButtonSelectPath);

  connect(mButtonBox,  &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(mButtonBox,  &QDialogButtonBox::rejected, this, &QDialog::reject);
  connect(mButtonBox->button(QDialogButtonBox::Help), &QAbstractButton::clicked, this, &PhotoMatchDialogView::help);
}

// public slots:

void NewProjectViewImp::clear()
{
  mLineEditProjectName->clear();
  mLineEditProjectPath->clear();
  mLineEditProjectFile->clear();
  mTextEditDescription->clear();
  mCheckBoxProjectFolder->setChecked(true);
}

// private slots:

void NewProjectViewImp::update()
{
  bool bSave = !mLineEditProjectName->text().isEmpty() &&
               !mLineEditProjectPath->text().isEmpty();
  mButtonBox->button(QDialogButtonBox::Save)->setEnabled(bSave && !bPrjExist);

  if (bSave){
    QString file(mLineEditProjectPath->text());
    if (mCheckBoxProjectFolder->isChecked()){
      file.append(QDir::separator()).append(mLineEditProjectName->text());
    }
    file.append(QDir::separator()).append(mLineEditProjectName->text()).append(".xml");
    mLineEditProjectFile->setText(QDir::cleanPath(file));
  } else
    mLineEditProjectFile->setText("");
}

void NewProjectViewImp::retranslate()
{
  this->setWindowTitle(QApplication::translate("NewProjectViewImp", "New Project", nullptr));
  mLabelProjectName->setText(QApplication::translate("NewProjectViewImp", "Project Name", nullptr));
  mLabelProjectPath->setText(QApplication::translate("NewProjectViewImp", "Project Path", nullptr));
  mLabelProjectFile->setText(QApplication::translate("NewProjectViewImp", "Project File", nullptr));
  mCheckBoxProjectFolder->setText(QApplication::translate("NewProjectViewImp", "Create folder with project name", nullptr));
  mLabelDescription->setText(QApplication::translate("NewProjectViewImp", "Description", nullptr));

  mButtonBox->button(QDialogButtonBox::Save)->setText(QApplication::translate("NewProjectViewImp", "Save", nullptr));
  mButtonBox->button(QDialogButtonBox::Cancel)->setText(QApplication::translate("NewProjectViewImp", "Cancel", nullptr));
  mButtonBox->button(QDialogButtonBox::Help)->setText(QApplication::translate("NewProjectViewImp", "Help", nullptr));
}

// NewProjectView interface

// public:

QString NewProjectViewImp::projectName() const
{
  return mLineEditProjectName->text();
}

QString NewProjectViewImp::projectPath() const
{
  return mLineEditProjectPath->text();
}

void NewProjectViewImp::setProjectPath(const QString &path)
{
  mLineEditProjectPath->setText(path);
}

QString NewProjectViewImp::projectDescription() const
{
  return mTextEditDescription->toPlainText();
}

bool NewProjectViewImp::createProjectFolder() const
{
  return mCheckBoxProjectFolder->isChecked();
}

void NewProjectViewImp::setExistingProject(bool prjExist)
{
  bPrjExist = prjExist;
  QPalette palette;
  if (bPrjExist){
    palette.setColor(QPalette::Text, Qt::red);
  } else {
    palette.setColor(QPalette::Text, Qt::black);
  }
  mLineEditProjectName->setPalette(palette);
  this->update();
}

// protected slots:

void NewProjectViewImp::onClickButtonSelectPath()
{
  QString pathName = QFileDialog::getExistingDirectory(this,
    tr("Project path"),
    mLineEditProjectPath->text(),
    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (!pathName.isEmpty()) {
    mLineEditProjectPath->setText(pathName);
  }
}

} // namespace photomatch
