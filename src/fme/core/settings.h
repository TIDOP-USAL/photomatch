#ifndef FME_SETTINGS_H
#define FME_SETTINGS_H

#include "fme/fme_global.h"

#include <QString>

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

};

class FME_EXPORT ISettingsRW
{

public:

  ISettingsRW() {}
  virtual ~ISettingsRW() = default;


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

protected:

  QString mLanguage;
};


} // namespace fme

#endif // FME_SETTINGS_H
