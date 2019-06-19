#include "MainWindowModel.h"

namespace fme
{

MainWindowModel::MainWindowModel()
{

}

bool MainWindowModel::checkUnsavedChanges() const
{
  //return Project::getInstance().checkUnsavedChanges();
  return false;
}

void MainWindowModel::init()
{
}

} // namespace fme



