#ifndef ABOUTFME_H
#define ABOUTFME_H

#include <QDialog>

namespace Ui {
class AboutFME;
}

class AboutFME : public QDialog
{
    Q_OBJECT

public:
    explicit AboutFME(QWidget *parent = 0);
    ~AboutFME();

private:
    Ui::AboutFME *ui;
};

#endif // ABOUTFME_H
