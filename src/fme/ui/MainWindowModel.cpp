#include "MainWindowModel.h"

#include <QStandardPaths>
#include <QDir>

namespace fme
{

MainWindowModel::MainWindowModel()
  : mPrjDefaultPath("")
{
  init();
}

QString MainWindowModel::defaultPath() const
{
  return mPrjDefaultPath;
}

void MainWindowModel::init()
{
  mPrjDefaultPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
  mPrjDefaultPath.append("/FME/Projects");

  //TL_TODO("Solución provisional para cargar el idioma activo")
  //OptionsModel options;

  QDir dir(mPrjDefaultPath);
  if (!dir.exists()) {
    dir.mkpath(".");
  }
}

} // namespace fme



