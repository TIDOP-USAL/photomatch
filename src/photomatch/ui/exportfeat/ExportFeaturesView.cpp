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


#include "ExportFeaturesView.h"

#include <QFileDialog>
#include <QIcon>
#include <QGridLayout>
#include <QLabel>
#include <QApplication>
#include <QComboBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QCheckBox>
#include <QListWidget>
#include <QLineEdit>
#include <QStandardPaths>

namespace photomatch
{

ExportFeaturesViewImp::ExportFeaturesViewImp(QWidget *parent)
  : ExportFeaturesView(parent)
{
  this->initUI();
  this->initSignalAndSlots();
}

ExportFeaturesViewImp::~ExportFeaturesViewImp()
{

}

void ExportFeaturesViewImp::initUI()
{
  this->setObjectName(QStringLiteral("ExportFeaturesView"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(540, 440);

  QGridLayout *gridLayout = new QGridLayout();
  this->setLayout(gridLayout);

  mLabelSession = new QLabel(this);
  mLabelSession->setMaximumSize(QSize(71, 16777215));
  gridLayout->addWidget(mLabelSession, 0, 0, 1, 1);

  mComboBoxSession = new QComboBox(this);
  gridLayout->addWidget(mComboBoxSession, 0, 1, 1, 2);

  mLabelFormat = new QLabel(this);
  mLabelFormat->setMaximumSize(QSize(71, 16777215));
  gridLayout->addWidget(mLabelFormat, 1, 0, 1, 1);

  mComboBoxFormat = new QComboBox(this);
  gridLayout->addWidget(mComboBoxFormat, 1, 1, 1, 2);

  mLabelExportPath = new QLabel(this);
  gridLayout->addWidget(mLabelExportPath, 2, 0, 1, 1);

  mLineEditExportPath = new QLineEdit(this);
  gridLayout->addWidget(mLineEditExportPath, 2, 1, 1, 1);

  mPushButtonExportFormat = new QPushButton(this);
  mPushButtonExportFormat->setMaximumSize(QSize(23, 16777215));
  mPushButtonExportFormat->setText("...");
  gridLayout->addWidget(mPushButtonExportFormat, 2, 2, 1, 1);

  mCheckBoxExportAll = new QCheckBox(this);
  mCheckBoxExportAll->setChecked(true);
  gridLayout->addWidget(mCheckBoxExportAll, 3, 0, 1, 3);

  mListWidgetfeatures = new QListWidget(this);
  mListWidgetfeatures->setSelectionMode(QAbstractItemView::MultiSelection);
  gridLayout->addWidget(mListWidgetfeatures, 4, 0, 1, 3);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok|QDialogButtonBox::Help);
  gridLayout->addWidget(mButtonBox, 5, 0, 1, 3);

  this->retranslate();
  this->update();
}

void ExportFeaturesViewImp::initSignalAndSlots()
{
  connect(mComboBoxSession,        &QComboBox::currentTextChanged,     this, &ExportFeaturesView::sessionChange);
  connect(mComboBoxFormat,         &QComboBox::currentTextChanged,     this, &ExportFeaturesView::formatChange);
  connect(mLineEditExportPath,     &QLineEdit::textChanged,            this, &ExportFeaturesViewImp::update);
  connect(mCheckBoxExportAll,      &QAbstractButton::clicked,          this, &ExportFeaturesViewImp::update);
  connect(mPushButtonExportFormat, &QAbstractButton::clicked,          this, &ExportFeaturesViewImp::onPushButtonExportFormat);
  connect(mListWidgetfeatures,     &QListWidget::itemSelectionChanged, this, &ExportFeaturesViewImp::update);

  connect(mButtonBox,                                   &QDialogButtonBox::rejected, this, &QDialog::reject);
  connect(mButtonBox->button(QDialogButtonBox::Ok),     &QAbstractButton::clicked,   this, &QDialog::accept);
  connect(mButtonBox->button(QDialogButtonBox::Help),   &QAbstractButton::clicked,   this, &PhotoMatchDialogView::help);
}

void ExportFeaturesViewImp::clear()
{
  const QSignalBlocker blockerComboBoxSession(mComboBoxSession);
  const QSignalBlocker blockerComboBoxFormat(mComboBoxFormat);
  const QSignalBlocker blockerLineEditExportPath(mLineEditExportPath);
  const QSignalBlocker blockerCheckBoxExportAll(mCheckBoxExportAll);

  mComboBoxSession->clear();
  mComboBoxFormat->clear();
  mCheckBoxExportAll->setChecked(true);
  mListWidgetfeatures->clear();
  mLineEditExportPath->clear();

  update();
}

void ExportFeaturesViewImp::update()
{
  if (mCheckBoxExportAll->isChecked()){
    mListWidgetfeatures->selectAll();
    mListWidgetfeatures->setDisabled(true);
  } else {
    mListWidgetfeatures->setDisabled(false);
  }

  bool bSave = !mLineEditExportPath->text().isEmpty() &&
               mListWidgetfeatures->selectedItems().size() != 0;
  mButtonBox->button(QDialogButtonBox::Ok)->setEnabled(bSave);
}

void ExportFeaturesViewImp::retranslate()
{
  this->setWindowTitle(QApplication::translate("ExportFeaturesView", "Export Keypoints", nullptr));
  mLabelSession->setText(QApplication::translate("ExportFeaturesView", "Session:", nullptr));
  mLabelFormat->setText(QApplication::translate("ExportFeaturesView", "Format:", nullptr));
  mLabelExportPath->setText(QApplication::translate("ExportFeaturesView", "Export path:", nullptr));
  mCheckBoxExportAll->setText(QApplication::translate("ExportFeaturesView", "Export all", nullptr));
  mButtonBox->button(QDialogButtonBox::Cancel)->setText(QApplication::translate("ExportFeaturesView", "Cancel", nullptr));
  mButtonBox->button(QDialogButtonBox::Ok)->setText(QApplication::translate("ExportFeaturesView", "Save", nullptr));
  mButtonBox->button(QDialogButtonBox::Help)->setText(QApplication::translate("ExportFeaturesView", "Help", nullptr));
}

void ExportFeaturesViewImp::onPushButtonExportFormat()
{
  QString pathName = QFileDialog::getExistingDirectory(this,
    tr("Export folder"),
    QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),
    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (!pathName.isEmpty()) {
    mLineEditExportPath->setText(pathName);
  }

  update();
}

QString ExportFeaturesViewImp::session() const
{
  return mComboBoxSession->currentText();
}

QString ExportFeaturesViewImp::format() const
{
  return mComboBoxFormat->currentText();
}

QStringList ExportFeaturesViewImp::exportFiles() const
{
  QStringList files_to_export;

  for (auto &feat : mListWidgetfeatures->selectedItems()){
    files_to_export.push_back(feat->text());
  }

  return files_to_export;
}

QString ExportFeaturesViewImp::exportPath() const
{
  return mLineEditExportPath->text();
}

bool ExportFeaturesViewImp::exportAll() const
{
  return mCheckBoxExportAll->isChecked();
}

void ExportFeaturesViewImp::setSessions(const QStringList &sessions)
{
  const QSignalBlocker blockerComboBoxSession(mComboBoxSession);
  mComboBoxSession->clear();
  mComboBoxSession->addItems(sessions);
}

void ExportFeaturesViewImp::setSessionToExport(const QString &session)
{
  const QSignalBlocker blockerComboBoxSession(mComboBoxSession);
  mComboBoxSession->setCurrentText(session);
}

void ExportFeaturesViewImp::setFormats(const QStringList &formats)
{
  const QSignalBlocker blockerComboBoxFormat(mComboBoxFormat);
  mComboBoxFormat->clear();
  mComboBoxFormat->addItems(formats);
}

void ExportFeaturesViewImp::setCurrentFormat(const QString &format)
{
  const QSignalBlocker blockerComboBoxFormat(mComboBoxFormat);
  mComboBoxFormat->setCurrentText(format);
}

void ExportFeaturesViewImp::setExportAll(bool active)
{
  mCheckBoxExportAll->setChecked(active);

  update();
}

void ExportFeaturesViewImp::setExportPath(const QString &path)
{
  mLineEditExportPath->setText(path);
}

void ExportFeaturesViewImp::setImageFiles(const QStringList &images)
{
  mListWidgetfeatures->clear();
  mListWidgetfeatures->addItems(images);
  update();
}

} // namespace photomatch




