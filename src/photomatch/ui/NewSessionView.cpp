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
    mLineEditSessionName(new QLineEdit(this)),
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
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(450,250);

  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  layout->addWidget(new QLabel(tr("Session Name")), 0, 0);
  layout->addWidget(mLineEditSessionName, 0, 1, 1, 2);

  layout->addWidget(new QLabel(tr("Description")), 1, 0);
  layout->addWidget(mTextEditSessionDescription, 2, 0, 1, 3);

  mButtonBox->setOrientation(Qt::Orientation::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Save | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
  mButtonBox->button(QDialogButtonBox::Save)->setText("Save");
  mButtonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");
  layout->addWidget(mButtonBox, 4, 0, 1, 3);

  this->retranslate();
  this->update();
}

void NewSessionViewImp::initSignalAndSlots()
{
  connect(mLineEditSessionName, SIGNAL(textChanged(QString)), this, SLOT(update()));
  connect(mLineEditSessionName, SIGNAL(textChanged(QString)), this, SIGNAL(sessionNameChange(QString)));

  connect(mButtonBox,  SIGNAL(accepted()), this, SLOT(accept()));
  connect(mButtonBox,  SIGNAL(rejected()), this, SLOT(reject()));
  connect(mButtonBox->button(QDialogButtonBox::Help),    SIGNAL(clicked(bool)), this, SIGNAL(help()));
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
  this->setWindowTitle(QApplication::translate("NewSessionViewImp", "New Session", nullptr));
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
