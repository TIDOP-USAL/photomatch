#include <QDebug>
#include <QFileDialog>
#include <QFile>

#include "ProgressDialog.h"
#include "ui_ProgressDialog.h"

namespace fme
{

ProgressDialog::ProgressDialog(QWidget *parent)
  : IProgressDialog(parent),
    ui(new Ui::ProgressDialog)
{

  this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
  this->setWindowFlags(this->windowFlags() | Qt::WindowMinimizeButtonHint);
  this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
  ui->setupUi(this);

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

//void ProgressDialog::setProcess(Process *process)
//{
//  mProcess = process;

//  connect(process, SIGNAL(finished()),                 this,    SLOT(onProcessFinished()));
//  connect(process, SIGNAL(statusChanged(int,QString)), this,    SLOT(onStatusChanged(int,QString)));
//  connect(process, SIGNAL(statusChangedNext()),        this,    SLOT(onStatusChangedNext()));
//  connect(process, SIGNAL(error(int,QString)),         this,    SLOT(onError(int,QString)));
//  //connect(this,    SIGNAL(cancel()),                   process, SLOT(stop()));
//}

void ProgressDialog::setFinished(bool finished)
{
  if(finished){
    ui->pushButton->setText(tr("Close"));
    //ui->pushButton_save->setVisible(true);
  } else{
    ui->pushButton->setText(tr("Cancel"));
    //ui->pushButton_save->setVisible(false);
  }
}

void ProgressDialog::onStatusChanged(int step, QString message)
{
  ui->progressBar->setValue(step);
  ui->labelStatus->setText(message);
}

void ProgressDialog::onStatusChangedNext()
{
  int value = ui->progressBar->value()+1;
  ui->progressBar->setValue(value);
}

void ProgressDialog::onMinimized()
{
  this->hide();
}

//void ProgressDialog::onProcessFinished()
//{
//  this->show();
//}

void ProgressDialog::on_pushButton_clicked()
{
  emit cancel();
  close();
}

} // namespace fme


//void fme::ProgressDialog::closeEvent(QCloseEvent *event)
//{
//}

//void fme::ProgressDialog::changeEvent(QEvent *event)
//{
//  QEvent::Type type = event->type();
//  if(type == QEvent::WindowStateChange) {
//    bool bTopLevel = this->isTopLevel();
//    if (bTopLevel == false){
//      this->hide();
//    }
//  }
//  QDialog::changeEvent(event);
//}
