#ifndef FME_SETTINGS_MODEL_H
#define FME_SETTINGS_MODEL_H

#include <QObject>
#include <QSettings>

#include "fme/core/settings.h"
#include "fme/ui/mvp.h"

namespace fme
{

class ISettingsModel
  : public IModel,
    public ISettings
{

  Q_OBJECT

public:

  ISettingsModel(QObject *parent = nullptr) : IModel(parent) {}

  /*!
   * \brief read
   * \return
   */
  virtual void read() = 0;

  /*!
   * \brief write
   * \return
   */
  virtual void write() = 0;

  /*!
   * \brief Comprueba si hay cambios sin guardar en el proyecto
   * \return
   */
  virtual bool checkUnsavedChanges() const = 0;
};

class SettingsModel
  : public ISettingsModel
{

  Q_OBJECT

public:

  explicit SettingsModel(ISettings *settings, QObject *parent = nullptr);
  ~SettingsModel() override;

// ISettings interface

public:

  QString language() const override;
  void setLanguage(const QString &language) override;

// IModel interface

private:

  void init() override;

// ISettingsModel interface

public:

  void read() override;
  void write() override;
  bool checkUnsavedChanges() const override;

protected:

  ISettings *mSettings;
  QSettings *mSettingsRW;
  bool bUnsavedChanges;
};

} // namespace fme

#endif // FME_SETTINGS_MODEL_H
