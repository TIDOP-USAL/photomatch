#ifndef FME_SETTINGS_H
#define FME_SETTINGS_H

#include "fme/fme_global.h"

#include <QString>

class QSettings;

namespace fme
{

class FME_EXPORT ISettings
{

public:

  ISettings() {}
  virtual ~ISettings() = default;

  /*!
   * \brief getLanguage
   * \return
   */
  virtual QString language() const = 0;

  /*!
   * \brief setLanguage
   * \param[in] language
   */
  virtual void setLanguage(const QString &language) = 0;

  /*!
   * \brief Recupera la configuración por defecto
   */
  virtual void reset() = 0;
};

class FME_EXPORT ISettingsRW
{

public:

  ISettingsRW() {}
  virtual ~ISettingsRW() = default;

  /*!
   * \brief read
   * \return
   */
  virtual void read(ISettings &settings) = 0;

  /*!
   * \brief write
   * \return
   */
  virtual void write(const ISettings &settings) = 0;
};


class FME_EXPORT Settings
  : public ISettings
{

public:

  Settings();
  ~Settings() override {}

// ISettings interface

public:

  QString language() const override;
  void setLanguage(const QString &language) override;
  void reset() override;

protected:

  QString mLanguage;
};


class FME_EXPORT SettingsRW
  : public ISettingsRW
{

public:

  explicit SettingsRW();
  ~SettingsRW() override;

// ISettingsRW interface

public:

  void read(ISettings &settings) override;
  void write(const ISettings &settings) override;

protected:

  QSettings *mSettingsRW;

};

} // namespace fme

#endif // FME_SETTINGS_H
