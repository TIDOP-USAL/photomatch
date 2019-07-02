#include "SettingsView.h"

namespace fme
{

SettingsView::SettingsView(QWidget *parent)
  : ISettingsView(parent)
{
  init();
}

SettingsView::~SettingsView()
{

}

void SettingsView::init()
{
}

void SettingsView::clear()
{
}

void SettingsView::update()
{
}

void SettingsView::setLanguages(const QStringList &languages)
{
}

void SettingsView::setActiveLanguage(const QString &language)
{
}

} // namespace fme
