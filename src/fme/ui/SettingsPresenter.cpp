#include "SettingsPresenter.h"

#include "SettingsModel.h"
#include "SettingsView.h"

namespace fme
{

SettingsPresenter::SettingsPresenter(ISettingsView *view, ISettingsModel *model)
  : ISettingsPresenter(),
    mView(view),
    mModel(model)
{

}

void SettingsPresenter::help()
{
}

void SettingsPresenter::open()
{
}

void SettingsPresenter::init()
{
}

void SettingsPresenter::save()
{
}

void SettingsPresenter::discart()
{
}

} // End namespace fme
