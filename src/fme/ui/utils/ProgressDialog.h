#ifndef FME_PROGRESS_DIALOG_H
#define FME_PROGRESS_DIALOG_H

#include <QDialog>
#include <QTextEdit>

#include "process.h"   /// TODO: esto es solo para Visual Studio. No se para que se utiliza
#include "fme/process/Process.h"

namespace Ui
{
  class ProgressDialog;
}

namespace fme
{

class IProgressDialog
  : public QDialog
{
  Q_OBJECT

public:

  explicit IProgressDialog(QWidget *parent = nullptr) : QDialog(parent){}
  virtual ~IProgressDialog() = default;

  virtual void setStatusText(QString text) = 0;
  virtual void setRange(int min, int max) = 0;
  virtual void setValue(int value) = 0;
  //virtual void setProcess(Process *process) = 0;
  virtual void setFinished(bool finished) = 0;

public slots:

  virtual void onStatusChanged(int step, QString message) = 0;
  virtual void onStatusChangedNext() = 0;
  //virtual void onProcessFinished() = 0;
  virtual void onMinimized() = 0;

signals:

  void cancel();

};

class ProgressDialog
  : public IProgressDialog
{
  Q_OBJECT

public:

  explicit ProgressDialog(QWidget *parent = nullptr);
  ~ProgressDialog()  override;

  void setStatusText(QString text) override;
  void setRange(int min, int max) override;
  void setValue(int value) override;
  //void setProcess(Process *process) override;
  void setFinished(bool finished) override;

public slots:

  void onStatusChanged(int step, QString message) override;
  void onStatusChangedNext() override;
  //void onProcessFinished() override;
  void onMinimized() override;

private slots:

  void on_pushButton_clicked();

// QWidget interface

protected:

  //void closeEvent(QCloseEvent *event) override;

private:

  Ui::ProgressDialog *ui;
  Process *mProcess;


  // QWidget interface
protected:
  //void changeEvent(QEvent *) override;
};

} // namespace fme

#endif // FME_PROGRESS_DIALOG_H
