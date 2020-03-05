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


#include <QDebug>
#include <QFileDialog>
#include <QFile>

#include "ProgressDialog.h"
#include "ui_ProgressDialog.h"

namespace photomatch
{

ProgressDialog::ProgressDialog(QWidget *parent)
  : IProgressDialog(parent),
    ui(new Ui::ProgressDialog)
{

  this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
  this->setWindowFlags(this->windowFlags() & ~Qt::WindowMaximizeButtonHint);
  this->setWindowFlags(this->windowFlags() & ~Qt::WindowCloseButtonHint);
  this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);

  ui->setupUi(this);
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));

  ui->pushButtonMinimize->setEnabled(false);

  connect(ui->pushButtonMinimize, SIGNAL(clicked(bool)), this, SLOT(onMinimized()));
  connect(ui->pushButtonCancel, SIGNAL(clicked(bool)), this, SLOT(onPushButtonCancelClicked()));
  connect(ui->pushButtonClose, SIGNAL(clicked(bool)), this, SLOT(close()));
}

ProgressDialog::~ProgressDialog()
{
  delete ui;
}

void ProgressDialog::setStatusText(QString text)
{
  ui->labelStatus->setText(text);
}

void ProgressDialog::setRange(int min, int max)
{
  ui->progressBar->setRange(min, max);
}

void ProgressDialog::setValue(int value)
{
  ui->progressBar->setValue(value);
}

void ProgressDialog::setInitialized()
{
  //ui->pushButton->setText(tr("Cancel"));
  ui->pushButtonCancel->setVisible(true);
  ui->pushButtonClose->setVisible(false);
  ui->pushButtonMinimize->setEnabled(true);
  this->show();
}

void ProgressDialog::setFinished()
{
  ui->pushButtonCancel->setVisible(false);
  ui->pushButtonClose->setVisible(true);
  ui->pushButtonClose->setText(tr("Close"));
  if (!this->isVisible()){
    this->show();
  }
  ui->pushButtonMinimize->setDisabled(true);
}

void ProgressDialog::setTitle(QString title)
{
  ui->progressBar->setWindowTitle(title);
}

void ProgressDialog::onMinimized()
{
  this->hide();
}

void ProgressDialog::onPushButtonCancelClicked()
{
  emit cancel();
  close();
}

} // namespace photomatch
