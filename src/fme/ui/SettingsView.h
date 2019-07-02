#ifndef FME_SETTINGS_VIEW_H
#define FME_SETTINGS_VIEW_H

#include "mvp.h"

namespace fme
{

class ISettingsView
  : public IDialogView
{

  Q_OBJECT

public:

  ISettingsView(QWidget *parent = nullptr) : IDialogView(parent) {}
  virtual ~ISettingsView(){}

  virtual void setLanguages(const QStringList &languages) = 0;
  virtual void setActiveLanguage(const QString &language) = 0;

signals:

  void languageChange(QString);


};

class SettingsView
  : public ISettingsView
{
  Q_OBJECT

public:

  SettingsView(QWidget *parent = nullptr);
  ~SettingsView() override;

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;

// ISettingsView interface

public:

  void setLanguages(const QStringList &languages) override;
  void setActiveLanguage(const QString &language) override;
};

} // namespace fme

#endif // FME_SETTINGS_VIEW_H
