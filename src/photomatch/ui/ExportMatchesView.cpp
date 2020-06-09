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


#include "ExportMatchesView.h"

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

namespace photomatch
{

ExportMatchesViewImp::ExportMatchesViewImp(QWidget *parent)
  : ExportMatchesView(parent)
{
  this->initUI();
  this->initSignalAndSlots();
}

void ExportMatchesViewImp::initUI()
{
  this->setObjectName(QStringLiteral("ExportMatchesView"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(440, 140);

  QGridLayout *gridLayout = new QGridLayout();
  this->setLayout(gridLayout);

  mLabelSession = new QLabel(this);
  mLabelSession->setMaximumSize(QSize(71, 16777215));
  gridLayout->addWidget(mLabelSession, 0, 0, 1, 1);

  mComboBoxSession = new QComboBox(this);
  gridLayout->addWidget(mComboBoxSession, 0, 1, 1, 2);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok|QDialogButtonBox::Help);
  gridLayout->addWidget(mButtonBox, 3, 0, 1, 3);

  this->retranslate();
  this->update();
}

void ExportMatchesViewImp::initSignalAndSlots()
{
  connect(mComboBoxSession, &QComboBox::currentTextChanged, this, &ExportMatchesView::sessionChange);

  connect(mButtonBox,                                   &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(mButtonBox,                                   &QDialogButtonBox::rejected, this, &QDialog::reject);
  connect(mButtonBox->button(QDialogButtonBox::Help),   &QAbstractButton::clicked,   this, &IDialogView::help);
}

void ExportMatchesViewImp::clear()
{
  const QSignalBlocker blockerComboBoxSession(mComboBoxSession);

  mComboBoxSession->clear();

  update();
}

void ExportMatchesViewImp::update()
{

}

void ExportMatchesViewImp::retranslate()
{
  this->setWindowTitle(QApplication::translate("ExportMatchesView", "Export Matches", nullptr));
  mLabelSession->setText(QApplication::translate("ExportMatchesView", "Session:", nullptr));

  mButtonBox->button(QDialogButtonBox::Cancel)->setText(QApplication::translate("ExportMatchesView", "Cancel", nullptr));
  mButtonBox->button(QDialogButtonBox::Ok)->setText(QApplication::translate("ExportMatchesView", "Export", nullptr));
  mButtonBox->button(QDialogButtonBox::Help)->setText(QApplication::translate("ExportMatchesView", "Help", nullptr));
}

ExportMatchesViewImp::~ExportMatchesViewImp()
{

}

void ExportMatchesViewImp::setSessions(const QStringList &sessions)
{
  const QSignalBlocker blockerComboBoxSession(mComboBoxSession);
  mComboBoxSession->clear();
  mComboBoxSession->addItems(sessions);
}

void ExportMatchesViewImp::setActiveSession(const QString &session)
{
  const QSignalBlocker blockerComboBoxSession(mComboBoxSession);
  mComboBoxSession->setCurrentText(session);
}

} // namespace photomatch




