#include <QDebug>
#include <QFileDialog>
#include <QFile>

#include "ProgressDialog.h"
#include "ui_ProgressDialog.h"

ProgressDialog::ProgressDialog( QWidget *parent):
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{

    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);
//    setWindowIcon(QIcon(":/Images/Icon.png"));
    setRange(0,3);
    ui->pushButton_save->setVisible(false);
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
    ui->progressBar->setRange(min,max);
}

void ProgressDialog::setValue(int value)
{
    ui->progressBar->setValue(value);
}

void ProgressDialog::setProcess(Process *process)
{
    mProcess = process;

    connect(process, SIGNAL(finished()),this,SLOT(onProcessFinished()));
    connect(process, SIGNAL(statusChanged(int,QString)),this,SLOT(onSatutsChanged(int,QString)));
    connect(process, SIGNAL(statusChangedNext()),this,SLOT(onSatutsChangedNext()));
    connect(process, SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
    connect(this,SIGNAL(cancel()),process,SLOT(stop()));
}

void ProgressDialog::setFinished(bool finished)
{
    if(finished){
        ui->pushButton->setText(tr("Close"));
        ui->pushButton_save->setVisible(true);
    }
    else{
        ui->pushButton->setText(tr("Cancel"));
        ui->pushButton_save->setVisible(false);
    }
}

void ProgressDialog::setConsole(QTextEdit *console)
{
    mConsole = console;
    ui->frame_console->layout()->setContentsMargins(0,0,0,0);
    ui->frame_console->layout()->addWidget(console);
}

void ProgressDialog::setConsoleVisible(bool visible)
{
    ui->frame_console->setVisible(visible);
}

void ProgressDialog::onSatutsChanged(int step, QString message)
{
    ui->progressBar->setValue(step);
    ui->labelStatus->setText(message);
}
void ProgressDialog::onSatutsChangedNext(){
    ui->progressBar->setValue(ui->progressBar->value()+1);
}

void ProgressDialog::on_pushButton_clicked()
{
    emit cancel();
    close();
}


void ProgressDialog::on_pushButton_save_clicked()
{


    QString savePath = QFileDialog::getSaveFileName(this,
                                                    tr("Text file"),
                                                    "C://",
                                                    trUtf8("(*.txt)"));

    if(!savePath.isEmpty()){
        QFile file(savePath);
        file.open(QFile::WriteOnly);
        file.write(mConsole->toPlainText().toLatin1());

        QString outputPath = savePath.left(savePath.lastIndexOf(QRegExp("/"))+1);
    }

}
void ProgressDialog::writeinConsole(QString text){
    mConsole->append(text+"\n");
}
void ProgressDialog::clearConsole(){
    mConsole->clear();
}
