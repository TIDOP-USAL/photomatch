#include "MainWindowView.h"
#include "ui_MainWindowView.h"

namespace fme
{

MainWindowView::MainWindowView(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindowView)
{
  ui->setupUi(this);

  init();

  /* Menú Archivo */
  connect(ui->actionNewProject,       SIGNAL(triggered(bool)),   this,   SIGNAL(openNew()));
  connect(ui->actionOpenProject,      SIGNAL(triggered(bool)),   this,   SIGNAL(openProject()));
  connect(ui->actionClearHistory,     SIGNAL(triggered(bool)),   this,   SIGNAL(clearHistory()));
  connect(ui->actionSaveProject,      SIGNAL(triggered(bool)),   this,   SIGNAL(saveProject()));
  connect(ui->actionSaveProjectAs,    SIGNAL(triggered(bool)),   this,   SIGNAL(saveProjectAs()));
  connect(ui->actionCloseProject,     SIGNAL(triggered(bool)),   this,   SIGNAL(closeProject()));
  connect(ui->actionExit,             SIGNAL(triggered(bool)),   this,   SIGNAL(exit()));

}

MainWindowView::~MainWindowView()
{
  delete ui;
}

void MainWindowView::clear()
{

}

void MainWindowView::setProjectTitle(const QString &title)
{
  setWindowTitle(title);

//  ui->treeWidget->header()->close();

//  QTreeWidgetItem *itemProject = ui->treeWidget->topLevelItem(0);
//  if (itemProject == nullptr) {
//    itemProject = new QTreeWidgetItem();
//    //itemProject->setIcon(0, QIcon(":/ico/img/48x48/digiflights.png"));
//    ui->treeWidget->addTopLevelItem(itemProject);
//    itemProject->setExpanded(true);
//  }

//  itemProject->setText(0, tr("Project: ").append(title));
}

void MainWindowView::changeEvent(QEvent *e)
{
  QMainWindow::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}

void MainWindowView::init()
{

}

} // namespace fme
