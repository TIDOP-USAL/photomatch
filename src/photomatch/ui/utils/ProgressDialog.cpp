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

  ui->pushButtonBgProcessing->setEnabled(false);

  connect(ui->pushButtonBgProcessing, SIGNAL(clicked(bool)), this, SLOT(onMinimized()));
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
  ui->pushButton->setText(tr("Cancel"));
  ui->pushButtonBgProcessing->setEnabled(true);
  this->show();
}

void ProgressDialog::setFinished()
{
  ui->pushButton->setText(tr("Close"));
  if (!this->isVisible()){
    this->show();
  }
  ui->pushButtonBgProcessing->setDisabled(true);
}

void ProgressDialog::setTitle(QString title)
{
  ui->progressBar->setWindowTitle(title);
}

void ProgressDialog::onMinimized()
{
  this->hide();
}

void ProgressDialog::on_pushButton_clicked()
{
  emit cancel();
  close();
}

} // namespace photomatch
