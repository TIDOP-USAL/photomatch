#ifndef FME_ABOUT_DIALOG_H
#define FME_ABOUT_DIALOG_H

#include "fme/fme_global.h"

#include <QDialog>

namespace Ui {
class AboutDialog;
}

namespace fme
{

class AboutDialog : public QDialog
{
  Q_OBJECT

public:
  explicit AboutDialog(QWidget *parent = nullptr);
  ~AboutDialog();

protected:
  void changeEvent(QEvent *e);

private:
  Ui::AboutDialog *ui;

};

} // namespace fme

#endif // FME_ABOUT_DIALOG_H
