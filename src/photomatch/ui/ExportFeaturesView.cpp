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

ExportFeaturesView::ExportFeaturesView(QWidget *parent)
  : IExportFeaturesView(parent)
{
  init();

  connect(mComboBoxSession,        SIGNAL(currentTextChanged(QString)), this, SIGNAL(sessionChange(QString)));
  connect(mComboBoxFormat,         SIGNAL(currentTextChanged(QString)), this, SIGNAL(formatChange(QString)));
  connect(mLineEditExportPath,     SIGNAL(textChanged(QString)),        this, SLOT(update()));
  connect(mCheckBoxExportAll,      SIGNAL(clicked(bool)),               this, SLOT(update()));
  connect(mPushButtonExportFormat, SIGNAL(clicked(bool)),               this, SLOT(onPushButtonExportFormat()));
  connect(mListWidgetfeatures,     SIGNAL(itemSelectionChanged()),      this, SLOT(update()));

  connect(mButtonBox,                                   SIGNAL(rejected()),      this, SLOT(reject()));
  connect(mButtonBox->button(QDialogButtonBox::Ok),     SIGNAL(clicked(bool)),   this, SLOT(accept()));
  connect(mButtonBox->button(QDialogButtonBox::Help),   SIGNAL(clicked(bool)),   this, SIGNAL(help()));
}

ExportFeaturesView::~ExportFeaturesView()
{

}

void ExportFeaturesView::onPushButtonExportFormat()
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

QString ExportFeaturesView::session() const
{
  return mComboBoxSession->currentText();
}

QString ExportFeaturesView::format() const
{
  return mComboBoxFormat->currentText();
}

QStringList ExportFeaturesView::exportFiles() const
{
  QStringList files_to_export;

  for (auto &feat : mListWidgetfeatures->selectedItems()){
    files_to_export.push_back(feat->text());
  }

  return files_to_export;
}

QString ExportFeaturesView::exportPath() const
{
  return mLineEditExportPath->text();
}

bool ExportFeaturesView::exportAll() const
{
  return mCheckBoxExportAll->isChecked();
}

void ExportFeaturesView::setSessions(const QStringList &sessions)
{
  const QSignalBlocker blockerComboBoxSession(mComboBoxSession);
  mComboBoxSession->clear();
  mComboBoxSession->addItems(sessions);
}

void ExportFeaturesView::setSessionToExport(const QString &session)
{
  const QSignalBlocker blockerComboBoxSession(mComboBoxSession);
  mComboBoxSession->setCurrentText(session);
}

void ExportFeaturesView::setFormats(const QStringList &formats)
{
  const QSignalBlocker blockerComboBoxFormat(mComboBoxFormat);
  mComboBoxFormat->clear();
  mComboBoxFormat->addItems(formats);
}

void ExportFeaturesView::setCurrentFormat(const QString &format)
{
  const QSignalBlocker blockerComboBoxFormat(mComboBoxFormat);
  mComboBoxFormat->setCurrentText(format);
}

void ExportFeaturesView::setExportAll(bool active)
{
  mCheckBoxExportAll->setChecked(active);

  update();
}

void ExportFeaturesView::setExportPath(const QString &path)
{
  mLineEditExportPath->setText(path);
}

void ExportFeaturesView::setImageFiles(const QStringList &images)
{
  mListWidgetfeatures->clear();
  mListWidgetfeatures->addItems(images);
  update();
}

void ExportFeaturesView::init()
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

  retranslate();

  update();
}

void ExportFeaturesView::clear()
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

void ExportFeaturesView::update()
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

void ExportFeaturesView::retranslate()
{
  this->setWindowTitle(QApplication::translate("ExportFeaturesView", "Export Keypoints", nullptr));
  mLabelSession->setText(QApplication::translate("ExportFeaturesView", "Session:", nullptr));
  mLabelFormat->setText(QApplication::translate("ExportFeaturesView", "Format:", nullptr));
  mLabelExportPath->setText(QApplication::translate("ExportFeaturesView", "Export path:", nullptr));
//  mComboBoxFormat->setItemText(0, QApplication::translate("ExportFeaturesView", "OpenCV XML", nullptr));
//  mComboBoxFormat->setItemText(1, QApplication::translate("ExportFeaturesView", "OpenCV YML", nullptr));

  mCheckBoxExportAll->setText(QApplication::translate("ExportFeaturesView", "Export all", nullptr));

  mButtonBox->button(QDialogButtonBox::Cancel)->setText(QApplication::translate("ExportFeaturesView", "Cancel", nullptr));
  mButtonBox->button(QDialogButtonBox::Ok)->setText(QApplication::translate("ExportFeaturesView", "Save", nullptr));
  mButtonBox->button(QDialogButtonBox::Help)->setText(QApplication::translate("ExportFeaturesView", "Help", nullptr));
}

} // namespace photomatch




