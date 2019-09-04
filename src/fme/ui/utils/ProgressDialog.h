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
  virtual void setProcess(Process *process) = 0;
  virtual void setFinished(bool finished) = 0;
  virtual void setConsole(QTextEdit *console) = 0;
  virtual void setConsoleVisible(bool visible) = 0;
  virtual void writeinConsole(QString text) = 0;
  virtual void clearConsole() = 0;

public slots:

  virtual void onSatutsChanged(int step, QString message) = 0;
  virtual void onSatutsChangedNext() = 0;

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
  void setProcess(Process *process) override;
  void setFinished(bool finished) override;
  void setConsole(QTextEdit *console) override;
  void setConsoleVisible(bool visible) override;
  void writeinConsole(QString text) override;
  void clearConsole() override;

public slots:

  void onSatutsChanged(int step, QString message) override;
  void onSatutsChangedNext() override;

private slots:

  void on_pushButton_clicked();
  void on_pushButton_save_clicked();

private:

  Ui::ProgressDialog *ui;
  Process *mProcess;
  QTextEdit *mConsole;

};

} // namespace fme

#endif // FME_PROGRESS_DIALOG_H
