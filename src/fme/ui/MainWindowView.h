#ifndef FME_MAINWINDOW_H
#define FME_MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindowView;
}

namespace fme
{



class MainWindowView
  : public QMainWindow
{
  Q_OBJECT

public:

  explicit MainWindowView(QWidget *parent = nullptr);
  ~MainWindowView();

  void clear();

signals:

  /* Menu File */

  void openNew();
  void openProject();
  void openFromHistory(QString);
  void clearHistory();
  void saveProject();
  void saveProjectAs();
  void closeProject();
  void exit();

protected:

  void changeEvent(QEvent *e);

private:

  void init();

private:

  Ui::MainWindowView *ui;
};

} // namespace fme

#endif // FME_MAINWINDOW_H
