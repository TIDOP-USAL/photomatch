#include "MainWindowView.h"
#include "MainWindowModel.h"
#include "MainWindowPresenter.h"

#include <QApplication>

#include "fme/fme_global.h"

#ifdef HAVE_VLD
#include "vld.h"
#endif

using namespace fme;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  MainWindowView view;
  MainWindowModel model;
  MainWindowPresenter presenter(&view, &model);
  presenter.open();

  bool r = a.exec();

  return r;
}
