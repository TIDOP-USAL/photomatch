#ifndef PHOTOMATCH_ABOUT_DIALOG_H
#define PHOTOMATCH_ABOUT_DIALOG_H

#include "photomatch/photomatch_global.h"

#include <QDialog>

namespace Ui {
class AboutDialog;
}

namespace photomatch
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

} // namespace photomatch

#endif // PHOTOMATCH_ABOUT_DIALOG_H
