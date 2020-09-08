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


#include "NewSessionView.h"

#include <QLineEdit>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>
#include <QIcon>
#include <QApplication>

namespace photomatch
{

NewSessionViewImp::NewSessionViewImp(QWidget *parent)
  : NewSessionView(parent),
    mLabelSessionName(new QLabel(this)),
    mLineEditSessionName(new QLineEdit(this)),
    mLabelSessionDescription(new QLabel(this)),
    mTextEditSessionDescription(new QTextEdit(this)),
    mButtonBox(new QDialogButtonBox(this)),
    bNameExist(false)
{
  this->initUI();
  this->initSignalAndSlots();
}

NewSessionViewImp::~NewSessionViewImp()
{

}

void NewSessionViewImp::initUI()
{
  this->setObjectName(QString("NewSessionView"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(450,250);

  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  layout->addWidget(mLabelSessionName, 0, 0);
  layout->addWidget(mLineEditSessionName, 0, 1, 1, 2);

  layout->addWidget(mLabelSessionDescription, 1, 0);
  layout->addWidget(mTextEditSessionDescription, 2, 0, 1, 3);

  mButtonBox->setOrientation(Qt::Orientation::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Save | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
  layout->addWidget(mButtonBox, 4, 0, 1, 3);

  this->retranslate();
  this->update();
}

void NewSessionViewImp::initSignalAndSlots()
{
  connect(mLineEditSessionName, &QLineEdit::textChanged, this, &NewSessionViewImp::update);
  connect(mLineEditSessionName, &QLineEdit::textChanged, this, &NewSessionView::sessionNameChange);

  connect(mButtonBox,  &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(mButtonBox,  &QDialogButtonBox::rejected, this, &QDialog::reject);
  connect(mButtonBox->button(QDialogButtonBox::Help),    &QAbstractButton::clicked, this, &PhotoMatchDialogView::help);
}

void NewSessionViewImp::clear()
{
  mLineEditSessionName->clear();
  mTextEditSessionDescription->clear();
}

void NewSessionViewImp::update()
{
  bool bSave = !mLineEditSessionName->text().isEmpty();
  mButtonBox->button(QDialogButtonBox::Save)->setEnabled(bSave && !bNameExist);
}

void NewSessionViewImp::retranslate()
{
  this->setWindowTitle(QApplication::translate("NewSessionView", "New Session", nullptr));
  mLabelSessionName->setText(QApplication::translate("NewSessionView", "Session Name", nullptr));
  mLabelSessionDescription->setText(QApplication::translate("NewSessionView", "Description", nullptr));
  mButtonBox->button(QDialogButtonBox::Save)->setText(QApplication::translate("NewSessionView", "Save", nullptr));
  mButtonBox->button(QDialogButtonBox::Cancel)->setText(QApplication::translate("NewSessionView", "Cancel", nullptr));
  mButtonBox->button(QDialogButtonBox::Help)->setText(QApplication::translate("NewSessionView", "Help", nullptr));
}

QString NewSessionViewImp::sessionName() const
{
  return mLineEditSessionName->text();
}

QString NewSessionViewImp::sessionDescription() const
{
  return mTextEditSessionDescription->toPlainText();
}

void NewSessionViewImp::setExistingName(bool nameExist)
{
  bNameExist = nameExist;
  QPalette palette;
  if (bNameExist){
    palette.setColor(QPalette::Text, Qt::red);
  } else {
    palette.setColor(QPalette::Text, Qt::black);
  }
  mLineEditSessionName->setPalette(palette);
  update();
}

} // namespace photomatch
